cmake_minimum_required (VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/Sensors/include) 
include_directories(${CMAKE_SOURCE_DIR}/ArduinoController/include) 
include_directories(${CMAKE_SOURCE_DIR}/StringUtil/include)
include_directories(${CMAKE_SOURCE_DIR}/Setting/include)

file (GLOB ALL_SOURCE src/*.cpp)
add_library (Sensors ${ALL_SOURCE})

#target_link_libraries(CommandScript Logging Setting)

