/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <streambuf>

#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>

#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/SourceMgr.h>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/IRReader/IRReader.h>

#include "parser/Parser.h"
#include "utils/ArgsHandler.h"
#include "utils/ArgsOptions.h"

#define MODULE_NAME "brainModule"
#define IO_LIB "/usr/local/include/brain/io.ll"

int main(int argc, char **argv)
{
    ArgsHandler args_handler(argc, argv);
    Parser parser(args_handler.get_string_file());
 
    // Create the context and the module
    llvm::LLVMContext C;

    llvm::SMDiagnostic Err;
    std::unique_ptr<llvm::Module> Mod = llvm::parseIRFile(llvm::StringRef(IO_LIB), Err, C);
    if (!Mod)
    {
        Err.print(argv[0], llvm::errs());
        return -1;
    }

    llvm::ErrorOr<llvm::Module *> ModuleOrErr = new llvm::Module(MODULE_NAME, C);
    std::unique_ptr<llvm::Module> Owner = std::unique_ptr<llvm::Module>(ModuleOrErr.get());
    llvm::Module *M = Owner.get();

    // Create the main function: "i32 @main()"
    llvm::Function *MainF = llvm::cast<llvm::Function>(M->getOrInsertFunction("main", llvm::Type::getInt32Ty(C), (llvm::Type *)0));

    // Create the entry block
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(C,
                                      "EntryBlock", // Conventionnaly called "EntryBlock"
                                      MainF // Add it to "main" function
                                      );
    llvm::IRBuilder<> B(BB); // Create a builder to add instructions
    B.SetInsertPoint(BB); // Insert the block to function

    // Generate IR code from parser
    parser.code_gen(M, B);
  
    // Return 0 to the "main" function
    B.CreateRet(B.getInt32(0));

    if (ArgsOptions::instance()->has_option(BO_IS_EMITTING_AST))
    {
        std::cout << "\n" << "=== Debug Information ===" << "\n";
        parser.debug_description(0);
    }

    if(ArgsOptions::instance()->has_option(BO_IS_EMITTING_LLVM))
    { 
        std::cout << "\n" << "=== LLVM IR ===" << "\n"; 
        // Print (dump) the module
        M->dump();
        Mod->dump();
    }

    // Default initialisation
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    // Create the execution engine
    std::string ErrStr;
    llvm::EngineBuilder *EB = new llvm::EngineBuilder(std::move(Owner));
    llvm::ExecutionEngine *EE = EB->setErrorStr(&ErrStr)
    .setMCJITMemoryManager(std::unique_ptr<llvm::SectionMemoryManager>(new llvm::SectionMemoryManager()))
    .create();

    EE->addModule(std::move(Mod));

    if (!ErrStr.empty()) {
        std::cout << ErrStr << "\n";
        exit(0);
    }

    // Finalize the execution engine before use it
    EE->finalizeObject();

    if (ArgsOptions::instance()->has_option(BO_IS_EMITTING_AST) || ArgsOptions::instance()->has_option(BO_IS_EMITTING_LLVM))
    {
        // Run the program
        std::cout << "\n" << "=== Program Output ===" << "\n";
    }

    std::vector<llvm::GenericValue> Args(0); // No args
    llvm::GenericValue gv = EE->runFunction(MainF, Args);
  
    // Clean up and shutdown
    delete EE;
    llvm::llvm_shutdown();
  
    return 0;
}

