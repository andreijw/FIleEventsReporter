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
#include <unordered_map>

namespace Constants{
    constexpr int CLI_ARGUMENTS = 2;

    enum class Command {
        START,
        UNLOAD,
        EXIT,
        INVALID
    };

    const std::unordered_map<std::string, Command> COMMAND_MAP = {
        {"start", Command::START},
        {"unload", Command::UNLOAD},
        {"exit", Command::EXIT}
    };
};