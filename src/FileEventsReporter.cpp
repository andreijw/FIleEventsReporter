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

#include <string>
#include <iostream>

#include "Constants.h"
#include "StringValidationHelper.h"

using namespace std;

static bool validateArguments(int argc, char* argv[], Constants::Command& command){
    // Ensure the user has provided the correct number of arguments.
	if (argc < Constants::CLI_ARGUMENTS)
	{
		cerr << "Usage: FileEventsReporter [start unload]" << endl;
		return false;
	}

    // Validate the input command
    if (!StringValidationHelper::isCommandValid(argv[1], command))
    {
        cerr << "Invalid input command " << argv[1] << endl;
        return false;
    }

	return true;
}

int main(int argc, char* argv[])
{
	Constants::Command command = Constants::Command::INVALID;
	// Validate the input arguments
	if (!validateArguments(argc, argv, command)) {
		return 1;
	}

	switch (command) {
		case Constants::Command::START:
            std::cout << "Starting FileEventsReporter..." << std::endl;
            // Add logic to start the FileEventsMiniFilter
            break;
        case Constants::Command::UNLOAD:
            std::cout << "Unloading FileEventsReporter..." << std::endl;
            // Add logic to unload the FileEventsMiniFilter
            break;
        case Constants::Command::EXIT:
            std::cout << "Exiting FileEventsReporter..." << std::endl;
            // Add logic to exit the program gracefully
            break;
		 default:
            cerr << "Unknown command: " << argv[1] << endl;
            return 1;
	}

    // Wait for all threads to finish
	cout << "FileEventsReporter execution complete" << endl;
	return 0;
}