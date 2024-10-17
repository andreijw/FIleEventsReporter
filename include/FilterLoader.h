/**
* @file FilterLoaded.h
* 
* This file contains the declaration of the FilterLoader class.
* The FilterLoader class is responsible for loading and unloading the FileEventsMiniFilter.
*
*/
#pragma once

#include <string>
#include <filesystem>

#include "Constants.h"

namespace FilterLoader{
    class FilterLoader {
        public:
            FilterLoader();
            ~FilterLoader();

            bool StartFilter();
            bool StopFiler();
            bool IsFilterLoaded() const { return m_filterLoaded; }

        private:
            bool LoadFilter();
            bool UnloadFilter();
            bool m_filterLoaded = false;
    };
}