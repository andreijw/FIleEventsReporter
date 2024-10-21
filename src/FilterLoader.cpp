/**
* @file FilterLoader.cpp
* 
* This file contains the implementation of the FilterLoader class.
* see FilterLoader.h for more details.
* 
*/

#include <iostream>
#include <windows.h>

#include "FilterLoader.h"
#include "Constants.h"

namespace FilterLoader
{
    FilterLoader::FilterLoader()
    {
        m_filterLoaded = false;
    }

    FilterLoader::~FilterLoader(){}

    /// @brief Start the kernel filter to log IO operations
    /// @return Success or failure of the operation
    bool FilterLoader::StartFilter()
    {
        return LoadFilter();
    }

    /// @brief Stop the filter from logging IO operations
    /// @return Success or failure of the operation
    bool FilterLoader::StopFiler()
    {
        return UnloadFilter();
    }

    /// @brief Actually load the filter
    /// @return Success or failure of the operation
    bool FilterLoader::LoadFilter()
    {
        if (m_filterLoaded)
        {
            return true;
        }

        SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (hSCManager == NULL) {
            std::cout << "Loading: " << Constants::FAILED_TO_CREATE_SERVICE_MANAGER << std::endl;
            return false;
        }

        SC_HANDLE hService = CreateService(
            hSCManager,
            Constants::MinifilterName.c_str(),
            Constants::MinifilterDisplayName.c_str(),
            SERVICE_START | DELETE | SERVICE_STOP,
            SERVICE_FILE_SYSTEM_DRIVER,
            SERVICE_DEMAND_START,
            SERVICE_ERROR_NORMAL,
            Constants::MinifilterDriverPath.c_str(),
            NULL,
            NULL,
            NULL,
            NULL,
            NULL
        );

        if (hService == NULL) {
            DWORD error = GetLastError();
            if (error == ERROR_SERVICE_EXISTS) {
                std::wstring wideServiceName = std::wstring(Constants::MinifilterName.begin(), Constants::MinifilterName.end());
                hService = OpenServiceW(hSCManager, wideServiceName.c_str(), SERVICE_START | DELETE | SERVICE_STOP);
            } else {
                std::cout << Constants::FAILED_TO_CREATE_SERVICE << std::endl;
                CloseServiceHandle(hSCManager);
                return false;            
            }
        }

        if (!StartService(hService, 0, NULL)) {
            DWORD error = GetLastError();
            if (error != ERROR_SERVICE_ALREADY_RUNNING) {
                std::cout << Constants::FAILED_TO_LOAD_FILTER_MESSAGE << " Error: " << error << std::endl;
                DeleteService(hService);
                CloseServiceHandle(hService);
                CloseServiceHandle(hSCManager);
                return false;            
            }
        }

        m_filterLoaded = true;
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return true;
    }

    /// @brief Actually unload the filter
    /// @return Success or failure of the operation
    bool FilterLoader::UnloadFilter()
    {
        if (!m_filterLoaded)
        {
            return true;
        }

        SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
        if (hSCManager == NULL) {
             std::cout << "Unloading: " << Constants::FAILED_TO_CREATE_SERVICE_MANAGER << std::endl;
            return false;
        }

        SC_HANDLE hService = OpenService(hSCManager, Constants::MinifilterName.c_str(), SERVICE_STOP | DELETE);
        if (hService == NULL) {
            std::cout << Constants::FAILED_TO_CREATE_SERVICE << std::endl;
            CloseServiceHandle(hSCManager);
            return false;
        }

        SERVICE_STATUS status;
        if (!ControlService(hService, SERVICE_CONTROL_STOP, &status)) {
            DWORD error = GetLastError();
            if (error != ERROR_SERVICE_NOT_ACTIVE) {
                std::cout << Constants::FAILED_TO_STOP_SERVICE << " Error: " << error << std::endl;
            }
        }

        DeleteService(hService);
        m_filterLoaded = false;
        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return true;
    }
}
