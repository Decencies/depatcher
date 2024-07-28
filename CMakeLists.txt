cmake_minimum_required(VERSION 3.28)
project(depatcher)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES
        src/mod.cpp
        include/mod.hpp)

link_directories(lib)
include_directories(include)
add_library(depatcher STATIC ${SOURCES})

add_subdirectory(loader)