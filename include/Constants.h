/**
* 
* @file Constants.h
 * This file contains the constants used in the program.
 *
 * This file contains the constants used in the program.
 *
*/

#pragma once

#include <string>
#include <array>

namespace Constants{
    constexpr int CLI_ARGUMENTS = 2;
    const std::array<std::string, 3> VALID_COMMANDS = {"start", "unload", "exit"};
};