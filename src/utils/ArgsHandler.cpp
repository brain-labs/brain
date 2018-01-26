/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include <iostream>
#include <fstream>
#include <streambuf>

#include "ArgsHandler.h"

const std::string BRAIN_VERSION =  "1.0";
const std::string BRAIN_FORMAT = "Please execute Brain with the command: brain \
<options...> <filename>\n";
const std::string BRAIN_HELP = "Use the identifier '--help' to get information \
about the settings\n";
const std::string BRAIN_OPT_ERR = "You can not use more than one type of \
optimization at time.\n";
const std::string BRAIN_DEFAULT_FILE_NAME = "a";

void ArgsHandler::handle(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "Brain version "
                  << BRAIN_VERSION << "." << std::endl
                  << BRAIN_FORMAT
                  << BRAIN_HELP;
        exit(-1);
    }

    _file_name = BRAIN_DEFAULT_FILE_NAME;

    for (int i = 1; i < argc; i++) {
        std::string str(argv[i]);

        if (str.compare("--help") == 0 || str.compare("-help") == 0) {
            std::cout << "\n"
                      << BRAIN_FORMAT << "\n\n"
                      << "--code=<\"inline code\">\tSets inline brain code\n"
                      << "--io=repl\t\tSets the IO module to REPLs style\n"
#ifndef INCOMPATIBLE_LLVM
                      << "--out=<filename>\tSets the output filename\n"
#endif // INCOMPATIBLE_LLVM
                      << "--version\t\tShows the current version of Brain\n"
                      << "--size=<number>\t\tSets the number of cells used by \
the interpreter\n"
                      << "--size-cell=<number>\tSets the number of bits \
(8, 16, 32, 64) of each cell\n"
                      << "-emit-llvm\t\tEmits LLVM IR code for the given input\n"
                      << "-emit-ast\t\tEmits the AST for the given input\n"
                      << "-emit-code\t\tEmits an optimized code for the given \
input\n"
#ifndef INCOMPATIBLE_LLVM
                      << "-c\t\t\tGenerates object file\n"
                      << "-S\t\t\tGenerates assembly file\n"
#endif // INCOMPATIBLE_LLVM
                      << "-v\t\t\tUses verbose mode for the output\n"
                      << "-O0\t\t\tGenerates output code with no optmizations\n"
                      << "-O1\t\t\tOptimizes Brain generated output code \
(Default)\n"
                      << "\n";
            exit(0);
        }
        else if (str.compare("--version") == 0) {
            std::cout << "Brain version " << BRAIN_VERSION << "."
                      << std::endl
                      << BRAIN_HELP;
            exit(0);
        }
        else if (str.compare("-emit-llvm") == 0) {
            ArgsOptions::instance()->add_option(BO_IS_EMITTING_LLVM);
        }
        else if (str.compare("-emit-ast") == 0) {
            ArgsOptions::instance()->add_option(BO_IS_EMITTING_AST);
        }
        else if (str.compare("-emit-code") == 0) {
            ArgsOptions::instance()->add_option(BO_IS_EMITTING_CODE);
        }
        else if (str.compare("-v") == 0) {
            ArgsOptions::instance()->add_option(BO_IS_VERBOSE);
        }
#ifndef INCOMPATIBLE_LLVM
        else if (str.compare("-c") == 0) {
            ArgsOptions::instance()->add_option(BO_IS_GEN_OBJ);
        }
        else if (str.compare("-S") == 0) {
            ArgsOptions::instance()->add_option(BO_IS_GEN_ASM);
        }
        else if (str.size() > 5 && str.compare(0, 6, "--out=") == 0) {
            _output_file_name = str.substr(6, str.size()-6);
            if(_output_file_name.empty()) {
                std::cout << "Output filename missing." << std::endl;
                exit(-1);
            }
        }
#endif // INCOMPATIBLE_LLVM
        else if (str.compare("-O0") == 0) {
            if (ArgsOptions::instance()->has_option(BO_IS_OPTIMIZING_O1)) {
                std::cout << BRAIN_OPT_ERR;
                exit(-1);
            }

            ArgsOptions::instance()->add_option(BO_IS_OPTIMIZING_O0);
        }
        else if (str.compare("-O1") == 0) {
            if (ArgsOptions::instance()->has_option(BO_IS_OPTIMIZING_O0)) {
                std::cout << BRAIN_OPT_ERR;
                exit(-1);
            }

            ArgsOptions::instance()->add_option(BO_IS_OPTIMIZING_O1);
        }
        else if (str.size() > 6 && str.compare(0, 7, "--size=") == 0) {
            /* Specified a size, Brain will create its arrays with the next
             * parameter.
             */
            int cells_size = std::atoi(str.substr(7, str.size()-7).c_str());
            ArgsOptions::instance()->set_cells_size(cells_size);
        }
        else if (str.size() > 11 && str.compare(0, 12, "--size-cell=") == 0) {
            /* Specified a cell size of 8, 16, 32 or 64 bits.
             * The default is 32 bits.
             */
            int cell_bitsize = std::atoi(str.substr(12, str.size()-12).c_str());
            ArgsOptions::instance()->set_cell_bitsize(cell_bitsize);
        }
        else if (str.size() > 6 && str.compare(0, 7, "--code=") == 0) {
            _string_file = str.substr(7, str.size()-7);
        }
        else if (str.size() > 4 && str.compare(0, 5, "--io=") == 0) {
            if (str.substr(5, str.size()-5).compare("repl") == 0) {
                ArgsOptions::instance()->set_io_option(IO_REPL);
            } else {
                std::cout << "Unknown IO option." << std::endl;
                exit(-1);
            }
        }
        else if ((str.size() > 2 && str.substr(str.size()-2, 2) == ".b") ||
                 (str.size() > 3 && str.substr(str.size()-3, 3) == ".bf") ||
                 (str.size() > 3 && str.substr(str.size()-3, 3) == ".br") ||
                 (str.size() > 4 && str.substr(str.size()-4, 4) == ".wit") ||
                 (str.size() > 6 && str.substr(str.size()-6, 6) == ".brain")) {
            std::ifstream t(str);
            std::string str_file((std::istreambuf_iterator<char>(t)),
                                 std::istreambuf_iterator<char>());
            if (str_file.empty()) {
                std::cout << "No such file '" << str << std::endl
                          << BRAIN_FORMAT;
                exit(-1);
            }
            _string_file = str_file;
            _file_name = str;
        }
        else if (str.find("-") == 0) {
            std::cout << "Unsupported option \"" << str << "\"" 
                      << std::endl
                      << BRAIN_HELP;
            exit(-1);
        }
        else {
            std::cout << "No such file '" << str << "'"
                      << std::endl
                      << BRAIN_FORMAT
                      << BRAIN_HELP;
            exit(-1);
        }
    }

    if (_string_file.empty()) {
        std::cout << "No input files"
                 << std::endl
                 << BRAIN_FORMAT;
        exit(-1);
    }

#ifndef INCOMPATIBLE_LLVM
    solve_output_file_name();
#endif // INCOMPATIBLE_LLVM
}

std::string ArgsHandler::get_string_file()
{
  return _string_file;
}

std::string ArgsHandler::get_file_name()
{
    return _file_name;
}

std::string ArgsHandler::get_output_file_name()
{
    return _output_file_name;
}

void ArgsHandler::solve_output_file_name()
{
    if (!_output_file_name.empty() &&
        !ArgsOptions::instance()->has_option(BO_IS_GEN_ASM) &&
        !ArgsOptions::instance()->has_option(BO_IS_GEN_OBJ)) {
        std::cout << "--out=<filename> must be used together with -c or -S\n"
                  << BRAIN_HELP;
        exit(-1);
    } else if (!_output_file_name.empty()) {
        return;
    } else if (!ArgsOptions::instance()->has_option(BO_IS_GEN_ASM) &&
               !ArgsOptions::instance()->has_option(BO_IS_GEN_OBJ)) {
        return;
    }

    std::string ext = ArgsOptions::instance()->has_option(BO_IS_GEN_ASM) ?
                      "s" : "o";

    if (_file_name.empty()) {
        _output_file_name = "out." + ext;
    } else {
        _output_file_name = _file_name.substr(0,
                                _file_name.find_last_of(".") + 1) + ext;
    }
}
