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
	${OBJECTDIR}/LineDetectInfoTest.o \
	${OBJECTDIR}/LineDetectTest.o


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
LDLIBSOPTIONS=-L../../OpenCV-2.3.1/build ../cppunit-1.12.1/src/cppunit/.libs/libcppunit.a -Wl,-rpath,../CameraDetector/dist/Debug/GNU-Linux-x86 -L../CameraDetector/dist/Debug/GNU-Linux-x86 -lCameraDetector ../RaspicamCV/libraspicamcv.a -Wl,-rpath,../Sensors/dist/Debug/GNU-Linux-x86 -L../Sensors/dist/Debug/GNU-Linux-x86 -lSensors -Wl,-rpath,../Logging/dist/Debug/GNU-Linux-x86 -L../Logging/dist/Debug/GNU-Linux-x86 -lLogging -Wl,-rpath,../VisionNavigation/dist/Debug/GNU-Linux-x86 -L../VisionNavigation/dist/Debug/GNU-Linux-x86 -lVisionNavigation

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCameraDetectorTest.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCameraDetectorTest.${CND_DLIB_EXT}: ../cppunit-1.12.1/src/cppunit/.libs/libcppunit.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCameraDetectorTest.${CND_DLIB_EXT}: ../CameraDetector/dist/Debug/GNU-Linux-x86/libCameraDetector.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCameraDetectorTest.${CND_DLIB_EXT}: ../RaspicamCV/libraspicamcv.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCameraDetectorTest.${CND_DLIB_EXT}: ../Sensors/dist/Debug/GNU-Linux-x86/libSensors.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCameraDetectorTest.${CND_DLIB_EXT}: ../Logging/dist/Debug/GNU-Linux-x86/libLogging.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCameraDetectorTest.${CND_DLIB_EXT}: ../VisionNavigation/dist/Debug/GNU-Linux-x86/libVisionNavigation.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCameraDetectorTest.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCameraDetectorTest.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/LineDetectInfoTest.o: LineDetectInfoTest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../cppunit-1.12.1/include/cppunit -II/ffmpeg_compiled/usr/local/include -I/usr/include -I../CameraDetector -I../Logging -I../Sensors -I../VisionNavigation -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LineDetectInfoTest.o LineDetectInfoTest.cpp

${OBJECTDIR}/LineDetectTest.o: LineDetectTest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../cppunit-1.12.1/include/cppunit -II/ffmpeg_compiled/usr/local/include -I/usr/include -I../CameraDetector -I../Logging -I../Sensors -I../VisionNavigation -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LineDetectTest.o LineDetectTest.cpp

# Subprojects
.build-subprojects:
	cd ../CameraDetector && ${MAKE}  -f Makefile CONF=Debug
	cd ../Sensors && ${MAKE}  -f Makefile CONF=Debug
	cd ../Logging && ${MAKE}  -f Makefile CONF=Debug
	cd ../VisionNavigation && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libCameraDetectorTest.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../CameraDetector && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Sensors && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Logging && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../VisionNavigation && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
