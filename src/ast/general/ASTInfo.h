/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef AST_INFO_H
#define AST_INFO_H

class ASTInfo 
{
  private:
    ASTInfo() : debugIndex(0) {}
    static ASTInfo *_instance;
  public:
    long debugIndex;
    ASTInfo(ASTInfo const&) = delete;
    ASTInfo& operator=(ASTInfo const&) = delete;
    static ASTInfo* instance();
};

#endif

