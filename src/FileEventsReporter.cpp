/**
* @file FileEventsReporter.cpp
* 
* This file contains the main function for the FileEventsReporter program.
* The FileEventsReporter program is a command line utility will load / unload the FileEventsMiniFilter.
* 
* The user can enter commands while the program is running. ["start", "unload"]. To load the minifilter and start reporting on event actions or to unload it and exit. Additionally, the cli can take the "exit"
* command to exit the program during the execution. This will clear up any resources and exit the program gracefully. This will also unload the minifilter.
* 
* The program uses the FileEventsMinifilter class to scan the RPC file events on the system.
*/

#include <chrono>
#include <iostream>
#include <limits>
#include <string>
#include <thread>

#include "Constants.h"
#include "FilterLoader.h"
#include "StringValidationHelper.h"

using namespace std;

/// @brief Validate the User input arguments
/// @param argc 
/// @param argv 
/// @return True if the arguments are valid, false otherwise
static bool validateArguments(int argc, char* argv[]){
    // Ensure the user has provided the correct number of arguments.
	if (argc != Constants::CLI_ARGUMENTS)
	{
		cerr << Constants::USAGE_MESSAGE << endl;
		return false;
	}
	return true;
}

/// @brief Check to see if user input is available
/// @return True if user input is available, false otherwise
bool userInputAvailable() {
    return !std::cin.eof();
}

/// @brief CLI Main entry point
/// @param argc 
/// @param argv 
/// @return Exit code.
int main(int argc, char* argv[])
{
	// Validate the input arguments
	if (!validateArguments(argc, argv)) {
		return 1;
	}

    FilterLoader::FilterLoader filterLoader;
    bool cliRunning = true;
    
    // Generate filter settings from environment variables / user input
    /** ToDO **/
    // filterLoader.GenerateFilterSettings();

    // Main loop
    cout << Constants::USAGE_MESSAGE << endl;
    string commandString;
    Constants::Command command;
    while (cliRunning) {
        // Validate the input command
        if (userInputAvailable()) { // Non-cross-platform call. May need to update to curses.h or have platform specific calls for this.
            getline(cin, commandString);     
            if (!StringValidationHelper::isCommandValid(commandString, command))
            {
                cerr << Constants::INVALID_INPUT_COMMAND << endl;
                continue;
            }

            switch (command) {
                case Constants::Command::START:
                    std::cout << Constants::START_MESSAGE << std::endl;
                    filterLoader.StartFilter();
                    break;
                case Constants::Command::UNLOAD:
                    std::cout << Constants::UNLOAD_MESSAGE << std::endl;
                    filterLoader.StopFiler();
                    break;
                case Constants::Command::EXIT:
                    std::cout << Constants::EXIT_MESSAGE << std::endl;
                    filterLoader.StopFiler();
                    cliRunning = false;
                    break;
                default:
                    cerr << Constants::INVALID_COMMAND_MESSAGE << argv[1] << endl;
                    return 1;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Sleep for 100ms to prevent busy waiting
    }

    // Wait for all threads to finish
	cout << Constants::EXECUTION_COMPLETE << endl;
	return 0;
}
