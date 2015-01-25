#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=None-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/DetectObject.o \
	${OBJECTDIR}/FindLineSetting.o \
	${OBJECTDIR}/FollowLineCommand.o \
	${OBJECTDIR}/FollowLineSetting.o \
	${OBJECTDIR}/LineDetect.o \
	${OBJECTDIR}/LineDetectSetting.o \
	${OBJECTDIR}/LineInfo.o \
	${OBJECTDIR}/LinePosition.o \
	${OBJECTDIR}/NavigateToBall.o \
	${OBJECTDIR}/NavigateToLine.o \
	${OBJECTDIR}/Position.o \
	${OBJECTDIR}/SearchForLine.o \
	${OBJECTDIR}/TurnToCenterLine.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../StringLibrary/dist/Debug/None-Linux-x86/libstringlibrary.a -Wl,-rpath,../Logging/dist/Debug/GNU-Linux-x86 -L../Logging/dist/Debug/GNU-Linux-x86 -lLogging -Wl,-rpath,../ArduinoController/dist/Debug/GNU-Linux-x86 -L../ArduinoController/dist/Debug/GNU-Linux-x86 -lArduinoController -Wl,-rpath,../CameraDetector/dist/Debug/GNU-Linux-x86 -L../CameraDetector/dist/Debug/GNU-Linux-x86 -lCameraDetector

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libVisionNavigation.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libVisionNavigation.${CND_DLIB_EXT}: ../StringLibrary/dist/Debug/None-Linux-x86/libstringlibrary.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libVisionNavigation.${CND_DLIB_EXT}: ../Logging/dist/Debug/GNU-Linux-x86/libLogging.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libVisionNavigation.${CND_DLIB_EXT}: ../ArduinoController/dist/Debug/GNU-Linux-x86/libArduinoController.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libVisionNavigation.${CND_DLIB_EXT}: ../CameraDetector/dist/Debug/GNU-Linux-x86/libCameraDetector.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libVisionNavigation.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libVisionNavigation.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/DetectObject.o: DetectObject.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringLibrary -I../Logging -I../ArduinoController -I../Sensors -I../CameraDetector -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DetectObject.o DetectObject.cpp

${OBJECTDIR}/FindLineSetting.o: FindLineSetting.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringLibrary -I../Logging -I../ArduinoController -I../Sensors -I../CameraDetector -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FindLineSetting.o FindLineSetting.cpp

${OBJECTDIR}/FollowLineCommand.o: FollowLineCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringLibrary -I../Logging -I../ArduinoController -I../Sensors -I../CameraDetector -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FollowLineCommand.o FollowLineCommand.cpp

${OBJECTDIR}/FollowLineSetting.o: FollowLineSetting.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringLibrary -I../Logging -I../ArduinoController -I../Sensors -I../CameraDetector -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FollowLineSetting.o FollowLineSetting.cpp

${OBJECTDIR}/LineDetect.o: LineDetect.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringLibrary -I../Logging -I../ArduinoController -I../Sensors -I../CameraDetector -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LineDetect.o LineDetect.cpp

${OBJECTDIR}/LineDetectSetting.o: LineDetectSetting.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringLibrary -I../Logging -I../ArduinoController -I../Sensors -I../CameraDetector -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LineDetectSetting.o LineDetectSetting.cpp

${OBJECTDIR}/LineInfo.o: LineInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringLibrary -I../Logging -I../ArduinoController -I../Sensors -I../CameraDetector -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LineInfo.o LineInfo.cpp

${OBJECTDIR}/LinePosition.o: LinePosition.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringLibrary -I../Logging -I../ArduinoController -I../Sensors -I../CameraDetector -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LinePosition.o LinePosition.cpp

${OBJECTDIR}/NavigateToBall.o: NavigateToBall.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringLibrary -I../Logging -I../ArduinoController -I../Sensors -I../CameraDetector -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NavigateToBall.o NavigateToBall.cpp

${OBJECTDIR}/NavigateToLine.o: NavigateToLine.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringLibrary -I../Logging -I../ArduinoController -I../Sensors -I../CameraDetector -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NavigateToLine.o NavigateToLine.cpp

${OBJECTDIR}/Position.o: Position.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringLibrary -I../Logging -I../ArduinoController -I../Sensors -I../CameraDetector -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Position.o Position.cpp

${OBJECTDIR}/SearchForLine.o: SearchForLine.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringLibrary -I../Logging -I../ArduinoController -I../Sensors -I../CameraDetector -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SearchForLine.o SearchForLine.cpp

${OBJECTDIR}/TurnToCenterLine.o: TurnToCenterLine.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringLibrary -I../Logging -I../ArduinoController -I../Sensors -I../CameraDetector -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TurnToCenterLine.o TurnToCenterLine.cpp

# Subprojects
.build-subprojects:
	cd ../StringLibrary && ${MAKE}  -f Makefile CONF=Debug
	cd ../Logging && ${MAKE}  -f Makefile CONF=Debug
	cd ../ArduinoController && ${MAKE}  -f Makefile CONF=Debug
	cd ../CameraDetector && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libVisionNavigation.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../StringLibrary && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Logging && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../ArduinoController && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../CameraDetector && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
