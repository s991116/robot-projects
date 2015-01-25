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
	${OBJECTDIR}/DetectObjectTest.o


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
LDLIBSOPTIONS=-L../../OpenCV-2.3.1/build/lib ../cppunit-1.12.1/src/cppunit/.libs/libcppunit.a -Wl,-rpath,../VisionNavigation/dist/Debug/GNU-Linux-x86 -L../VisionNavigation/dist/Debug/GNU-Linux-x86 -lVisionNavigation

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libVisionNavigationTest.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libVisionNavigationTest.${CND_DLIB_EXT}: ../cppunit-1.12.1/src/cppunit/.libs/libcppunit.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libVisionNavigationTest.${CND_DLIB_EXT}: ../VisionNavigation/dist/Debug/GNU-Linux-x86/libVisionNavigation.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libVisionNavigationTest.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libVisionNavigationTest.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -L$(HOME)/git/raspberrypi/userland/build/lib -lmmal_core -lmmal -l mmal_util -lvcos -lbcm_host -I/usr/include/opencv -lopencv_highgui -lopencv_core -lopencv_legacy -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_imgproc -shared -fPIC

${OBJECTDIR}/DetectObjectTest.o: DetectObjectTest.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../cppunit-1.12.1/include/cppunit -I../VisionNavigation -I../CameraDetector -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DetectObjectTest.o DetectObjectTest.cpp

# Subprojects
.build-subprojects:
	cd ../VisionNavigation && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libVisionNavigationTest.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../VisionNavigation && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
