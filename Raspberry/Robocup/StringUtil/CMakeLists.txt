cmake_minimum_required (VERSION 2.8)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /usr/local/lib/cmake/)

include_directories(include)

project (StringUtil)

file (GLOB ALL_SOURCE src/*.cpp)
add_library (StringUtil ${ALL_SOURCE})