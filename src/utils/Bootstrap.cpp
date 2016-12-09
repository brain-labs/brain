/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "Bootstrap.h"

using namespace llvm;

// forward declaration of static member.
Bootstrap* Bootstrap::_instance = nullptr;

Bootstrap::Bootstrap()
{
}

Bootstrap* Bootstrap::instance()
{
    if (_instance == nullptr) {
        _instance = new Bootstrap;
    }

    return _instance;
}

int Bootstrap::init(int argc, char** argv)
{
    ArgsHandler args_handler(argc, argv);
    Parser parser(args_handler.get_string_file());

    io_lib = std::string(getenv("HOME")) + "/.brain/lib/";
    io_lib += ArgsOptions::instance()->get_io_option() == IO_REPL ? "io_repl.ll" : "io.ll"; 

    if (ArgsOptions::instance()->has_option(BO_IS_EMITTING_CODE)) {
        parser.ast_code_gen();
        std::cout << "\n";
        return 0;
    }

    module_name = args_handler.get_file_name();

    // Create the context and the module
    llvm::LLVMContext llvm_context;

    llvm::SMDiagnostic err;
    std::unique_ptr<llvm::Module> io_module;

    if (ASTInfo::instance()->is_using_io_lib) {
        io_module = llvm::parseIRFile(llvm::StringRef(io_lib), err,
                                      llvm_context);

    	if (!io_module) {
            err.print(argv[0], llvm::errs());
            return -1;
    	}
    }

    llvm::ErrorOr<llvm::Module *> module_or_err = new llvm::Module(module_name,
                                                                   llvm_context);
    auto Owner = std::unique_ptr<llvm::Module>(module_or_err.get());
    auto *module = Owner.get();

    // Create the main function: "i32 @main()"
    auto *MainF = llvm::cast<llvm::Function>(module->getOrInsertFunction("main", llvm::Type::getInt32Ty(llvm_context), (llvm::Type *)0));

    // Create the entry block
    auto *basic_block = llvm::BasicBlock::Create(llvm_context,
                                                 // Conventionnaly called:
                                                 "EntryBlock",
                                                 // Add it to "main" function
                                                 MainF);

    // Create a builder to add instructions.
    llvm::IRBuilder<> builder(basic_block);
    // Insert the block to function.
    builder.SetInsertPoint(basic_block);

    // Generate IR code from parser.
    parser.code_gen(module, builder);

    // Return 0 to the "main" function.
    builder.CreateRet(builder.getInt32(0));

    if (ArgsOptions::instance()->has_option(BO_IS_EMITTING_AST)) {
        std::cout << "=== Debug Information ===" << "\n";
        parser.debug_description(0);
    }

    if(ArgsOptions::instance()->has_option(BO_IS_EMITTING_LLVM)) {
        std::cout << "=== LLVM IR ===" << "\n";
        std::string dumpStr;
        llvm::raw_string_ostream dumpStrOstream(dumpStr);
        module->print(dumpStrOstream, nullptr);
        if (io_module) {
	    io_module->print(dumpStrOstream, nullptr);
        }
        std::cout << dumpStr;
    }

    // Default initialization.
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

#ifndef INCOMPATIBLE_LLVM
    if (ArgsOptions::instance()->has_option(BO_IS_GEN_OBJ) ||
        ArgsOptions::instance()->has_option(BO_IS_GEN_ASM)) {
        llvm::Module *module_c = new llvm::Module(module_name, llvm_context);
        Linker::linkModules(*module_c, std::move(Owner));
        if (io_module) {
            Linker::linkModules(*module_c, std::move(io_module));
        }

        std::string target_triple = sys::getDefaultTargetTriple();
        module_c->setTargetTriple(target_triple);
        std::string error;
        auto target = TargetRegistry::lookupTarget(target_triple, error);
        if (!target) {
            llvm::errs() << error;
            return 1;
        }
   
        std::string cpu = "generic";
        std::string features = "";

        TargetOptions opt;
        Reloc::Model rm;
        auto the_target_machine = target->createTargetMachine(target_triple, cpu, features, opt, rm);

        module_c->setDataLayout(the_target_machine->createDataLayout());

        std::error_code ec;
        raw_fd_ostream dest(args_handler.get_output_file_name(), ec, sys::fs::F_None);

        if (ec) {
            llvm::errs() << "Could not open file: " << ec.message();
            return 1;
        }

        legacy::PassManager pass;
        auto filetype = ArgsOptions::instance()->has_option(BO_IS_GEN_OBJ) ?
                            TargetMachine::CGFT_ObjectFile :
                            TargetMachine::CGFT_AssemblyFile;

        if (the_target_machine->addPassesToEmitFile(pass, dest, filetype)) {
            llvm::errs() << "The target nachine can't emit a file of this type";
            return 1;
        }

        pass.run(*module_c);
        dest.flush();
    }
    else {
#endif // INCOMPATIBLE_LLVM

        // Create the execution engine.
        std::string error_str;
        engine_builder = new llvm::EngineBuilder(std::move(Owner));
        execution_engine = engine_builder->setErrorStr(&error_str)
		.setMCJITMemoryManager(std::unique_ptr<llvm::SectionMemoryManager>
                                          (new llvm::SectionMemoryManager())).create();

        if (io_module) {
            execution_engine->addModule(std::move(io_module));
        }

        if (!error_str.empty()) {
            std::cout << error_str << "\n";
            return -1;
        }

        // Finalize the execution engine before use it
        execution_engine->finalizeObject();

        if (ArgsOptions::instance()->has_option(BO_IS_EMITTING_AST) ||
	    ArgsOptions::instance()->has_option(BO_IS_EMITTING_LLVM)) {
            // Run the program
            std::cout << "=== Program Output ===" << "\n";
        }

        // No args.
        std::vector<llvm::GenericValue> Args(0);
        llvm::GenericValue gv = execution_engine->runFunction(MainF, Args);
#ifndef INCOMPATIBLE_LLVM
    }
#endif // INCOMPATIBLE_LLVM

    llvm::llvm_shutdown();

    return 0;
}
