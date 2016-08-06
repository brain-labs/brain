/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#ifndef ARGS_HANDLER_H
#define ARGS_HANDLER_H

#include "ArgsOptions.h"

#include <string>

/**
 * @brief Consumes the arguments passed to brain and do whatever actions it's
 * supposed to.
 */
class ArgsHandler
{
protected:
    /// The source file passed to Brain.
    std::string _string_file;
    /**
     * @brief Called in the constructor to handle all the arguments passed to
     * Brain.
     */
    void handle(int argc, char *argv[]);
public:
    ArgsHandler(int argc, char *argv[]) { handle(argc, argv); }
    /**
     * @brief Returns the content of the source file passed to Brain as a
     * string.
     */
    std::string get_string_file();
};

#endif // ARGS_HANDLER_H
