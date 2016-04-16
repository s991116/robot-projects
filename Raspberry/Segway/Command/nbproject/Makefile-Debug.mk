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
	${OBJECTDIR}/CalibrateGyro.o \
	${OBJECTDIR}/Command.o \
	${OBJECTDIR}/FollowLineCommand.o \
	${OBJECTDIR}/NavigateCommand.o \
	${OBJECTDIR}/SegwayCommand.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcommand.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcommand.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcommand.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcommand.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcommand.a

${OBJECTDIR}/CalibrateGyro.o: CalibrateGyro.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../RobotController -I../Sensor -I../RobotHead -I../Vision -I../Setting -I../PiCamera -I../Logging -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CalibrateGyro.o CalibrateGyro.cpp

${OBJECTDIR}/Command.o: Command.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../RobotController -I../Sensor -I../RobotHead -I../Vision -I../Setting -I../PiCamera -I../Logging -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Command.o Command.cpp

${OBJECTDIR}/FollowLineCommand.o: FollowLineCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../RobotController -I../Sensor -I../RobotHead -I../Vision -I../Setting -I../PiCamera -I../Logging -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FollowLineCommand.o FollowLineCommand.cpp

${OBJECTDIR}/NavigateCommand.o: NavigateCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../RobotController -I../Sensor -I../RobotHead -I../Vision -I../Setting -I../PiCamera -I../Logging -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/NavigateCommand.o NavigateCommand.cpp

${OBJECTDIR}/SegwayCommand.o: SegwayCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../RobotController -I../Sensor -I../RobotHead -I../Vision -I../Setting -I../PiCamera -I../Logging -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SegwayCommand.o SegwayCommand.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libcommand.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
