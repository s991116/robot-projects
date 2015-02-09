cmake_minimum_required (VERSION 2.8)

project(Robocup)
option(MyOption "CAMERA_MOCK" OFF)
include_directories(/usr/local/include)

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
  )

