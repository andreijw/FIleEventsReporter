# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.12)

# Project name, version and description
project(FileEventsReporter VERSION 1.0 DESCRIPTION "RPC File Events Reporter" LANGUAGES CXX)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("FileEventsReporter" VERSION 1.0 DESCRIPTION "RPC File Events Reporter" LANGUAGES CXX)

# Include library files.
add_executable (file-events-reporter "${CMAKE_SOURCE_DIR}/src/FileEventsReporter.cpp")
target_include_directories(file-events-reporter PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_compile_features(file-events-reporter PUBLIC cxx_std_20)

# Configure the .env file
configure_file("${CMAKE_SOURCE_DIR}/.env" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Link against stdc++fs if needed
if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.1)
    target_link_libraries(file-events-reporter stdc++fs)
endif()

# Link against Threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(file-events-reporter Threads::Threads)

set_property(TARGET file-events-reporter PROPERTY CXX_STANDARD 20)

# TODO: Add tests and install targets if needed.
# Enable testing
enable_testing()

# Add tests
# add_executable(file-finder-tests "${CMAKE_SOURCE_DIR}/tests/test_a.cpp")
# add_test(NAME FileFinderTests COMMAND file-finder-tests)