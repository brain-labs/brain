/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#ifndef BOOTSTRAP_H
#define BOOTSTRAP_H

#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>

#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/SourceMgr.h>
#include "llvm/Support/TargetRegistry.h"

#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#ifdef IS_DEBUG
#include <llvm/IR/Verifier.h>
#endif // IS_DEBUG

#ifndef INCOMPATIBLE_LLVM
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Linker/Linker.h"
#endif // INCOMPATIBLE_LLVM

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <streambuf>
#include <memory>

#include "../parser/Parser.h"
#include "../ast/general/ASTInfo.h"
#include "ArgsHandler.h"
#include "ArgsOptions.h"

/**
 * @brief Class that starts Brain, it has all the needed components to
 * initialize the Brain interpreter.
 */
class Bootstrap
{
private:
    /// The path to the default lib in Brain.
    std::string io_lib;
    /// The name of the main module
    std::string module_name;
    ///
    llvm::ExecutionEngine *execution_engine;
    ///
    llvm::EngineBuilder *engine_builder;
    /**
     * @brief Private constructor of ASTInfo, denoting that this is a Singleton.
     */
    Bootstrap();

    static Bootstrap* _instance;
public:
    ~Bootstrap(); 

    /**
     * @brief Returns the instance of Bootstrap class if the member _instance is
     * nullptr, otherwise it creates a new Bootstrap object and returns it.
     * @return A pointer to the Bootstrap instance.
     */
    static Bootstrap* instance();
    /**
     * @brief Initializes Brain by passing the arguments to be handled and
     * parsing the source file.
     * @param argc The integer representing how many arguments were passed.
     * @param argv The array of characters representing the arguments passed.
     */
    int init(int argc, char** argv);
};

#endif // BOOTSTRAP_H
