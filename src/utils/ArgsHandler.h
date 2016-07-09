/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#ifndef ARGS_HANDLER_H
#define ARGS_HANDLER_H

#include <string>

#include "ArgsOptions.h"

/**
 * @brief Consumes the arguments passed to brain and do whatever actions it's supposed to.
 */
class ArgsHandler 
{
protected:
    std::string _string_file;
    /**
     * @brief
     */
    void handle(int argc, char *argv[]);
public:
    ArgsHandler(int argc, char *argv[]) { handle(argc, argv); }
    /**
     * @brief
     */
    std::string get_string_file();
};

#endif // ARGS_HANDLER_H
