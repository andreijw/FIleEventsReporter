/**
* @file StringValidationHelper.h
* 
* This file contains some helper string validation functions.
* 
*/
#pragma once

#include <string>
#include <algorithm>

#include "Constants.h"
#include "CommandHelper.h"

namespace StringValidationHelper {
	/**
	* @brief Check to see if the string is a valid command
	* 
	* @param str The string to validate
	* @return bool True if the string is a valid command, false otherwise
	*/
	bool isCommandValid(const std::string str, Constants::Command& command) {
		// Check to see if the string is empty
		if (str.empty()) {
			return false;
		}

        // Check to see if the string is a valid command
		command = CommandHelper::getCommandFromString(str);
		return command != Constants::Command::INVALID;
	}
};