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
LDLIBSOPTIONS=../cppunit-1.12.1/src/cppunit/.libs/libcppunit.a -Wl,-rpath,../Logging/dist/Debug/GNU-Linux-x86 -L../Logging/dist/Debug/GNU-Linux-x86 -lLogging -Wl,-rpath,../Sensors/dist/Debug/GNU-Linux-x86 -L../Sensors/dist/Debug/GNU-Linux-x86 -lSensors -Wl,-rpath,../ArduinoController/dist/Debug/GNU-Linux-x86 -L../ArduinoController/dist/Debug/GNU-Linux-x86 -lArduinoController -Wl,-rpath,../CommandTest/dist/Debug/GNU-Linux-x86 -L../CommandTest/dist/Debug/GNU-Linux-x86 -lCommandTest -Wl,-rpath,../CameraDetectorTest/dist/Debug/GNU-Linux-x86 -L../CameraDetectorTest/dist/Debug/GNU-Linux-x86 -lCameraDetectorTest -Wl,-rpath,../VisionNavigationTest/dist/Debug/GNU-Linux-x86 -L../VisionNavigationTest/dist/Debug/GNU-Linux-x86 -lVisionNavigationTest -Wl,-rpath,../VisionNavigation/dist/Debug/GNU-Linux-x86 -L../VisionNavigation/dist/Debug/GNU-Linux-x86 -lVisionNavigation

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testrunner

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testrunner: ../cppunit-1.12.1/src/cppunit/.libs/libcppunit.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testrunner: ../Logging/dist/Debug/GNU-Linux-x86/libLogging.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testrunner: ../Sensors/dist/Debug/GNU-Linux-x86/libSensors.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testrunner: ../ArduinoController/dist/Debug/GNU-Linux-x86/libArduinoController.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testrunner: ../CommandTest/dist/Debug/GNU-Linux-x86/libCommandTest.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testrunner: ../CameraDetectorTest/dist/Debug/GNU-Linux-x86/libCameraDetectorTest.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testrunner: ../VisionNavigationTest/dist/Debug/GNU-Linux-x86/libVisionNavigationTest.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testrunner: ../VisionNavigation/dist/Debug/GNU-Linux-x86/libVisionNavigation.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testrunner: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testrunner ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../cppunit-1.12.1/include/cppunit -I../CommandTest -I../ArduinoCommand -I../CameraDetectorTest -I../CommandScript -I../Sensors -I../VisionNavigationTest -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../Logging && ${MAKE}  -f Makefile CONF=Debug
	cd ../Sensors && ${MAKE}  -f Makefile CONF=Debug
	cd ../ArduinoController && ${MAKE}  -f Makefile CONF=Debug
	cd ../CommandTest && ${MAKE}  -f Makefile CONF=Debug
	cd ../CameraDetectorTest && ${MAKE}  -f Makefile CONF=Debug
	cd ../VisionNavigationTest && ${MAKE}  -f Makefile CONF=Debug
	cd ../VisionNavigation && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/testrunner

# Subprojects
.clean-subprojects:
	cd ../Logging && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Sensors && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../ArduinoController && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../CommandTest && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../CameraDetectorTest && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../VisionNavigationTest && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../VisionNavigation && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
