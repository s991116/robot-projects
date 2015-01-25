cmake_minimum_required (VERSION 2.8)

include_directories(${CMAKE_SOURCE_DIR}/RemoteControl/include) 
include_directories(${CMAKE_SOURCE_DIR}/Logging/include) 
include_directories(${CMAKE_SOURCE_DIR}/CommandScript/include) 
include_directories(${CMAKE_SOURCE_DIR}/Command/include) 
include_directories(${CMAKE_SOURCE_DIR}/Sensors/include)
include_directories(${CMAKE_SOURCE_DIR}/Setting/include)

add_executable (RemoteControl src/RemoteControl.cpp src/View.cpp)

target_link_libraries(RemoteControl Logging CommandScript)

