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
    if (str.compare("--help") == 0)
    {
      std::cout << "\n"
                << "--debug  activates debug mode\n" 
                << "\n";
      exit(0);
    }
    else if (str.compare("--debug") == 0)
    {
      _isDebugging = true;
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

bool ArgsHandler::isDebugActive()
{
  return _isDebugging;
}

