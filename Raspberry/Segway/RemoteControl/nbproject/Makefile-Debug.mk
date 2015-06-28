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
CND_PLATFORM=GNU-Linux-x86
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
	${OBJECTDIR}/GyroState.o \
	${OBJECTDIR}/MainState.o \
	${OBJECTDIR}/MotorState.o \
	${OBJECTDIR}/MotorTuningController.o \
	${OBJECTDIR}/State.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=c++0x
CXXFLAGS=-std=c++0x

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=../StringUtil/dist/Debug/GNU-Linux-x86/libstringutil.a ../SoundPlayer/dist/Debug/GNU-Linux-x86/libsoundplayer.a ../PiCamera/dist/Debug/GNU-Linux-x86/libpicamera.a ../RobotController/dist/Debug/GNU-Linux-x86/librobotcontroller.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol: ../StringUtil/dist/Debug/GNU-Linux-x86/libstringutil.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol: ../SoundPlayer/dist/Debug/GNU-Linux-x86/libsoundplayer.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol: ../PiCamera/dist/Debug/GNU-Linux-x86/libpicamera.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol: ../RobotController/dist/Debug/GNU-Linux-x86/librobotcontroller.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol ${OBJECTFILES} ${LDLIBSOPTIONS} -lncurses

${OBJECTDIR}/GyroState.o: GyroState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../SoundPlayer -I../PiCamera -I../RobotController -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GyroState.o GyroState.cpp

${OBJECTDIR}/MainState.o: MainState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../SoundPlayer -I../PiCamera -I../RobotController -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MainState.o MainState.cpp

${OBJECTDIR}/MotorState.o: MotorState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../SoundPlayer -I../PiCamera -I../RobotController -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MotorState.o MotorState.cpp

${OBJECTDIR}/MotorTuningController.o: MotorTuningController.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../SoundPlayer -I../PiCamera -I../RobotController -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MotorTuningController.o MotorTuningController.cpp

${OBJECTDIR}/State.o: State.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../SoundPlayer -I../PiCamera -I../RobotController -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/State.o State.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../SoundPlayer -I../PiCamera -I../RobotController -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../StringUtil && ${MAKE}  -f Makefile CONF=Debug
	cd ../SoundPlayer && ${MAKE}  -f Makefile CONF=Debug
	cd ../PiCamera && ${MAKE}  -f Makefile CONF=Debug
	cd ../RobotController && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol

# Subprojects
.clean-subprojects:
	cd ../StringUtil && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../SoundPlayer && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../PiCamera && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../RobotController && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
