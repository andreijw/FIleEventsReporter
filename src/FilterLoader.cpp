/**
* @file FilterLoader.cpp
* 
* This file contains the implementation of the FilterLoader class.
* see FilterLoader.h for more details.
* 
*/
#include "FilterLoader.h"
#include <windows.h>

namespace FilterLoader
{
    FilterLoader::FilterLoader()
    {
        m_filterLoaded = false;
    }

    FilterLoader::~FilterLoader(){}

    bool FilterLoader::StartFilter()
    {
        return LoadFilter();
    }

    bool FilterLoader::StopFiler()
    {
        return UnloadFilter();
    }

    bool FilterLoader::LoadFilter()
    {
        if (m_filterLoaded)
        {
            return true;
        }
        // Add logic to load the minifilter
        return true;
    }

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
