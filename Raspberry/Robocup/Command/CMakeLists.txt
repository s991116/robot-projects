cmake_minimum_required (VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/Command/include) 
include_directories(${CMAKE_SOURCE_DIR}/Setting/include) 

file (GLOB ALL_SOURCE src/*.cpp)
add_library (Command ${ALL_SOURCE})

#target_link_libraries(CommandScript Logging Setting)

