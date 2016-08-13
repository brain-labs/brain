/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#ifndef AST_INFO_H
#define AST_INFO_H

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

/**
 * @brief The abstract syntax tree.
 */
class ASTInfo
{
private:
    /**
     * @brief Private constructor of ASTInfo, denoting that this is a Singleton.
     */
    ASTInfo() {}

    /// Singleton object.
    static ASTInfo *_instance;
public:
    ASTInfo(ASTInfo const&) = delete;
    ASTInfo& operator=(ASTInfo const&) = delete;
    /**
     * @brief Returns the instance of ASTInfo class if the member _instance is
     * nullptr, otherwise it creates a new ASTInfo object and returns it.
     * @return A pointer to the ASTInfo instance.
     */
    static ASTInfo* instance();
    /**
     * @brief
     * @param M
     * @param B
     */
    void code_gen(llvm::Module *M, llvm::IRBuilder<> &B);
    /**
     * @brief
     * @return
     */
    llvm::GlobalVariable* get_index_ptr();
    /**
     * @brief
     * @return
     */
    llvm::GlobalVariable* get_cells_ptr(); 
    /**
     * @brief
     */
    bool is_using_io_lib;
};

#endif // AST_INFO_H

