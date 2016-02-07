cmake_minimum_required (VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/Logging/include)
include_directories(${CMAKE_SOURCE_DIR}/Console/include)
include_directories(${CMAKE_SOURCE_DIR}/StringUtil/include)

file (GLOB ALL_SOURCE src/*.cpp)
add_library (Logging ${ALL_SOURCE})

target_link_libraries(Logging Console StringUtil)