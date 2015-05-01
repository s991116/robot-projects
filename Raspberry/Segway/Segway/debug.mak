#Generated by VisualGDB (http://visualgdb.com)
#DO NOT EDIT THIS FILE MANUALLY UNLESS YOU ABSOLUTELY NEED TO
#USE VISUALGDB PROJECT PROPERTIES DIALOG INSTEAD

BINARYDIR := Debug

#Toolchain
CC := gcc
CXX := g++
LD := $(CXX)
AR := ar
OBJCOPY := objcopy

#Additional flags
PREPROCESSOR_MACROS := DEBUG
INCLUDE_DIRS := /tmp/VisualGDB/c/git/Raspberry/Segway/PiCamera /tmp/VisualGDB/c/git/Raspberry/Segway/Controller
LIBRARY_DIRS := /tmp/VisualGDB/c/git/Raspberry/Segway/PiCamera/Debug /opt/vc/lib /tmp/VisualGDB/c/git/Raspberry/Segway/Controller/Debug
LIBRARY_NAMES := PiCamera mmal_core mmal_util mmal opencv_core opencv_highgui raspicam_cv raspicam Controller
ADDITIONAL_LINKER_INPUTS := 
MACOS_FRAMEWORKS := 
LINUX_PACKAGES := 

CFLAGS := -ggdb -ffunction-sections -O0 -std=c++0x
CXXFLAGS := -ggdb -ffunction-sections -O0 -std=c++0x
ASFLAGS := 
LDFLAGS := -Wl,-gc-sections
COMMONFLAGS := 

START_GROUP := -Wl,--start-group
END_GROUP := -Wl,--end-group

#Additional options detected from testing the toolchain
USE_DEL_TO_CLEAN := 1
CP_NOT_AVAILABLE := 1
IS_LINUX_PROJECT := 1