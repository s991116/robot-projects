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
	${OBJECTDIR}/main.o


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
LDLIBSOPTIONS=-Wl,-rpath,../CommandScript/dist/Debug/GNU-Linux-x86 -L../CommandScript/dist/Debug/GNU-Linux-x86 -lCommandScript -Wl,-rpath,../Logging/dist/Debug/GNU-Linux-x86 -L../Logging/dist/Debug/GNU-Linux-x86 -lLogging -Wl,-rpath,../Sensors/dist/Debug/GNU-Linux-x86 -L../Sensors/dist/Debug/GNU-Linux-x86 -lSensors ../ArduinoController/dist/Debug/GNU-Linux-x86/libarduinocontroller.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/console

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/console: ../CommandScript/dist/Debug/GNU-Linux-x86/libCommandScript.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/console: ../Logging/dist/Debug/GNU-Linux-x86/libLogging.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/console: ../Sensors/dist/Debug/GNU-Linux-x86/libSensors.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/console: ../ArduinoController/dist/Debug/GNU-Linux-x86/libarduinocontroller.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/console: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/console ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../CameraDetector -I../ArduinoController -I../Logging -I../CommandScript -I../Sensors -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../CommandScript && ${MAKE}  -f Makefile CONF=Debug
	cd ../Logging && ${MAKE}  -f Makefile CONF=Debug
	cd ../Sensors && ${MAKE}  -f Makefile CONF=Debug
	cd ../ArduinoController && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/console

# Subprojects
.clean-subprojects:
	cd ../CommandScript && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Logging && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Sensors && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../ArduinoController && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
