cmake_minimum_required(VERSION 3.10)

project(weatherProject CXX)

set(WEATHER_SOURCES
    main.cpp
    curlFunctions.cpp
    initialConfigRead.cpp
    menuSystem.cpp
    globals.cpp
    apiFunctions.cpp)

# =================================================================
# PROJECT COMPILING
# =================================================================

# 1. Define executable from source files
add_executable(weatherProject ${WEATHER_SOURCES})

# 2. Set header files path
target_include_directories(weatherProject PUBLIC ${PROJECT_SOURCE_DIR}/lib)

# 3. Find and link 3rd-party libraries
find_package(CURL REQUIRED)

target_link_libraries(weatherProject PRIVATE CURL::libcurl)
