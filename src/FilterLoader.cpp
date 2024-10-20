/**
* @file FilterLoader.cpp
* 
* This file contains the implementation of the FilterLoader class.
* see FilterLoader.h for more details.
* 
*/
#include "FilterLoader.h"

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
        // Add logic to load the minifilter
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
        // Add logic to unload the minifilter
        return true;
    }
}
