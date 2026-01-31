cmake_minimum_required(VERSION 3.10)

project(orderbook_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(orderbook_engine
    src/main.cpp
)

target_include_directories(orderbook_engine
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
