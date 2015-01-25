cmake_minimum_required (VERSION 2.8)

project(Robocup)

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
  )

