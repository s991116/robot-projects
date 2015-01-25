cmake_minimum_required (VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/RaspiCamera/include)

file (GLOB ALL_SOURCE src/*.cpp)
add_library (RaspiCamera ${ALL_SOURCE})
