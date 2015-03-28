cmake_minimum_required (VERSION 2.8)

if(UNIX)
    MESSAGE(STATUS "Unix system detected.")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif()

project(Robocup)
option(MyOption "CAMERA_MOCK" OFF)
include_directories(/usr/local/include)

################################
# GTest
################################
ADD_SUBDIRECTORY (gtest-1.7.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


subdirs(
  RemoteControl 
  Logging 
  ArduinoController 
  StringUtil 
  Console 
  CommandScript
  Sensors
  Command
  Setting
  RaspiCamera
  Vision
  Robot
  tests/Vision
  tests
  )
