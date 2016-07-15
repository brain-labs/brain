/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "ArgsOptions.h"

ArgsOptions *ArgsOptions::_instance = nullptr;

ArgsOptions* ArgsOptions::instance()
{
    if (!ArgsOptions::_instance) {
        ArgsOptions::_instance = new ArgsOptions();
    }

    return _instance;
}

void ArgsOptions::add_option(BrainOption option)
{
    _options |= option;
}

bool ArgsOptions::has_option(BrainOption option)
{
    return (_options & option) == option;
}

BrainOption ArgsOptions::get_optimization()
{
    // default value
    if ((_options & BO_IS_OPTIMIZING_O1) == 0 &&
        (_options & BO_IS_OPTIMIZING_O0) == 0) {
        return BO_IS_OPTIMIZING_O1;
    }
    else if ((_options & BO_IS_OPTIMIZING_O1) == BO_IS_OPTIMIZING_O1) {
        return BO_IS_OPTIMIZING_O1;
    }
    else {
        return BO_IS_OPTIMIZING_O0;
    }
}
