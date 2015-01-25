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
	${OBJECTDIR}/CommandScript.o \
	${OBJECTDIR}/ConsolePrint.o \
	${OBJECTDIR}/ParseCommandLine.o


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
LDLIBSOPTIONS=-Wl,-rpath,../CameraDetector/dist/Debug/GNU-Linux-x86 -L../CameraDetector/dist/Debug/GNU-Linux-x86 -lCameraDetector ../StringLibrary/dist/Debug/GNU-Linux-x86/libstringlibrary.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCommandScript.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCommandScript.${CND_DLIB_EXT}: ../CameraDetector/dist/Debug/GNU-Linux-x86/libCameraDetector.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCommandScript.${CND_DLIB_EXT}: ../StringLibrary/dist/Debug/GNU-Linux-x86/libstringlibrary.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCommandScript.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCommandScript.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/CommandScript.o: CommandScript.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../Sensors -I../ArduinoController -I../StringLibrary -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CommandScript.o CommandScript.cpp

${OBJECTDIR}/ConsolePrint.o: ConsolePrint.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../Sensors -I../ArduinoController -I../StringLibrary -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ConsolePrint.o ConsolePrint.cpp

${OBJECTDIR}/ParseCommandLine.o: ParseCommandLine.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../Sensors -I../ArduinoController -I../StringLibrary -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ParseCommandLine.o ParseCommandLine.cpp

# Subprojects
.build-subprojects:
	cd ../CameraDetector && ${MAKE}  -f Makefile CONF=Debug
	cd ../StringLibrary && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCommandScript.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../CameraDetector && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../StringLibrary && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc