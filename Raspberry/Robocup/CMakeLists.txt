cmake_minimum_required (VERSION 2.8)

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
  temp
  tests/Vision
  tests
  )

