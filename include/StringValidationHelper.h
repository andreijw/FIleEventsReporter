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

namespace StringValidationHelper {
	/**
	* @brief Check to see if the string is a valid command
	* 
	* @param str The string to validate
	* @return bool True if the string is a valid command, false otherwise
	*/
	bool isCommandValid(const char* str) {
		// Check to see if the string is empty
		if (str == nullptr || str[0] == '\0') {
			return false;
		}

        // Check to see if the string is a valid command
		return std::any_of(Constants::VALID_COMMANDS.begin(), Constants::VALID_COMMANDS.end(),
            [str](const std::string& command) { return command == str; });
	}
};