cmake_minimum_required (VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/CommandScript/include) 
include_directories(${CMAKE_SOURCE_DIR}/Logging/include) 
include_directories(${CMAKE_SOURCE_DIR}/RemoteControl/include) 
include_directories(${CMAKE_SOURCE_DIR}/Command/include) 
include_directories(${CMAKE_SOURCE_DIR}/Sensors/include) 
include_directories(${CMAKE_SOURCE_DIR}/ArduinoController/include) 
include_directories(${CMAKE_SOURCE_DIR}/Console/include)
include_directories(${CMAKE_SOURCE_DIR}/Setting/include)
include_directories(/opt/local/include)

file (GLOB ALL_SOURCE src/*.cpp)
add_library (CommandScript ${ALL_SOURCE})

