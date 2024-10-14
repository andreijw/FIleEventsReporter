/**
* @file CommandHelper.h
* 
* This file contains some helper string functions to generate commands
* 
*/
#pragma once

#include <string>
#include "Constants.h"

namespace CommandHelper {
    inline Constants::Command getCommandFromString(const std::string& commandStr) {
        auto it = Constants::COMMAND_MAP.find(commandStr);
        if (it != Constants::COMMAND_MAP.end()) {
            return it->second;
        }
        return Constants::Command::INVALID;
    }
}