/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include <iostream>
#include <fstream>
#include <streambuf>

#include "ArgsHandler.h"

#define BRAIN_VERSION 0.5
#define BRAIN_FORMAT "Please execute Brain with the command: brain filename\n"
#define BRAIN_HELP "Use the identifier '--help' for getting information about the settings\n";

void ArgsHandler::handle(int argc, char *argv[])
{
  if (argc < 2)
  {
    std::cout << "Brain version " << BRAIN_VERSION << ". "
              << BRAIN_FORMAT
              << BRAIN_HELP;
    exit(-1);
  }

  for (int i = 1; i < argc; i++)
  {
    std::string str(argv[i]);
    if (str.compare("--help") == 0 || str.compare("-help") == 0)
    {
      std::cout << "\n"
                << "-emit-llvm\tDumps the LLVM IR code before executing\n"
                << "-emit-expr\tDumps the Expressions generated before executing\n"
                << "-O0\t\tGenerates output code with no optmizations\n"
                << "-O1\t\tOptimizes Brain generated output code (Default)\n" 
                << "\n";
      exit(0);
    }
    else if (str.compare("-emit-llvm") == 0)
    {
      _isEmitingLLVM = true;
    }
    else if (str.compare("-emit-expr") == 0)
    {
      _isEmitingExpr = true;
    }
    else if (str.compare("-O0") == 0)
    {
      _isOptimizing = false;
    }
    else if (str.compare("-O1") == 0)
    {
      _isOptimizing = true;
    }
    else if (str.substr(str.size()-2,2) == ".b")
    {
      // TODO: Make it a list
      std::ifstream t(str);
      std::string strFile((std::istreambuf_iterator<char>(t)),
                       std::istreambuf_iterator<char>());
     if (strFile.empty())
     {
       std::cout << "No such file '" << str << "'\n"
                 << BRAIN_FORMAT;
       exit(-1);
     }
      _stringFile = strFile;
    }
    else if (str.find("-") == 0)
    {
      std::cout << "Unsupported option '" << str << "'\n"
                << BRAIN_HELP;
       exit(-1);
    }
    else
    {
      std::cout << "No such file '" << str << "'\n"
                << BRAIN_FORMAT
                << BRAIN_HELP;
       exit(-1);
    }
  }
}

std::string ArgsHandler::getStringFile()
{
  return _stringFile;
}

bool ArgsHandler::isEmitLLVMActive()
{
  return _isEmitingLLVM;
}

bool ArgsHandler::isEmitExprActive()
{
  return _isEmitingExpr;
}

bool ArgsHandler::isOptimizing()
{
  return _isOptimizing;
}

