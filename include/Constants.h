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
    // CLI Arguments
    constexpr int CLI_ARGUMENTS = 1;

    // Commands
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

    const std::string MinifilterName = "FileEventsReporterDriver";
    const std::string MinifilterDisplayName = "FileEventsReporterDriver";
    const std::string MinifilterDriverPath = "C:\\Users\\andre\\Desktop\\Progamming\\FIleEventsReporter\\FileEventsReporterDriver\\x64\\Debug\\FileEventsReporterDriver\\FileEventsReporterDriver.sys";

    // Output Messages
    const std::string USAGE_MESSAGE = "Usage: FileEventsReporter [start unload exit]";
    const std::string INVALID_INPUT_COMMAND = "Invalid input command";
    const std::string EXECUTION_COMPLETE = "FileEventsReporter execution complete";
    const std::string EXIT_MESSAGE = "Exiting FileEventsReporter...";
    const std::string START_MESSAGE = "Starting FileEventsReporter...";
    const std::string UNLOAD_MESSAGE = "Unloading FileEventsReporter...";
    const std::string INVALID_COMMAND_MESSAGE = "Invalid command. Please enter a valid command.";

    // FilterLoader Messages
    const std::string FILTER_LOADED_MESSAGE = "Filter loaded successfully";
    const std::string FILTER_UNLOADED_MESSAGE = "Filter unloaded successfully";
    const std::string FAILED_TO_LOAD_FILTER_MESSAGE = "Failed to load filter";
    const std::string FAILED_TO_CREATE_SERVICE_MANAGER = "Failed to create service manager";
    const std::string FAILED_TO_CREATE_SERVICE = "Failed to create service";
    const std::string FAILED_TO_STOP_SERVICE = "Failed to stop service";
};