/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "ArgsHandler.h"

void ArgsHandler::handle(int argc, char *argv[])
{
}

std::string ArgsHandler::getStringFile()
{
  return "OAL";
}

bool ArgsHandler::isDebugActive()
{
  return _isDebugging;
}
