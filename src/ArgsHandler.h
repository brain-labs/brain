/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef ARGS_HANDLER_H
#define ARGS_HANDLER_H

#include <string>

class ArgsHandler 
{
  protected:
    std::string _stringFile;
    bool _isDebugging;
    void handle(int argc, char *argv[]);
  public:
    ArgsHandler(int argc, char *argv[]) { handle(argc, argv); }
    std::string getStringFile();
    bool isDebugActive();
};

#endif
