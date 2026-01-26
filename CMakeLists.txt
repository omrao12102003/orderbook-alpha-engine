cmake_minimum_required(VERSION 3.15)

project(OrderBookAlphaEngine
    VERSION 1.0.0
    DESCRIPTION "Ultra-Low Latency Market Microstructure & Order Book Alpha Engine"
    LANGUAGES CXX
)

# Enforce modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -flto")

# Include directories
include_directories(include)

# Placeholder executable
add_executable(orderbook_engine
    src/main.cpp
)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")

