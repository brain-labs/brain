/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#ifndef AST_INFO_H
#define AST_INFO_H

/**
 * @brief The abstract syntax tree.
 */
class ASTInfo
{
private:
    /**
     * @brief Private constructor of ASTInfo, denoting that this is a Singleton.
     */
    ASTInfo() : debug_index(0) {}

    static ASTInfo *_instance;
public:
    ///
    long debug_index;
    ASTInfo(ASTInfo const&) = delete;
    ASTInfo& operator=(ASTInfo const&) = delete;
    /**
     * @brief Returns the instance of ASTInfo class if the member _instance is
     * nullptr, otherwise it creates a new ASTInfo object and returns it.
     * @return A pointer to the ASTInfo instance.
     */
    static ASTInfo* instance();
};

#endif // AST_INFO_H

