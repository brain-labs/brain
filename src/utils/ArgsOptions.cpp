/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Brain, 2016.
 */

#include "ArgsOptions.h"

// Forward declarations
ArgsOptions *ArgsOptions::_instance = nullptr;

ArgsOptions* ArgsOptions::instance()
{
    if (!ArgsOptions::_instance) {
        ArgsOptions::_instance = new ArgsOptions();
        ArgsOptions::_instance->set_cells_size(100);
        ArgsOptions::_instance->set_io_option(IO_REGULAR);
        ArgsOptions::_instance->set_cell_bitsize(32);
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

void ArgsOptions::set_cells_size(int cells_size)
{
    _k_cells_size = cells_size;
}

int ArgsOptions::get_cells_size()
{
    return _k_cells_size;
}

void ArgsOptions::set_cell_bitsize(int cell_bitsize)
{
    switch (cell_bitsize) {
        case 8:
        case 16:
        // 32 is the default
        case 64:
          _k_cell_bitsize = cell_bitsize;
          break;
        default:
          _k_cell_bitsize = 32;
          break;
    }
}

int ArgsOptions::get_cell_bitsize()
{
    return _k_cell_bitsize;
}

void ArgsOptions::set_io_option(int type_io)
{
    _type_io = type_io;
}

int ArgsOptions::get_io_option()
{
    return _type_io;
}

