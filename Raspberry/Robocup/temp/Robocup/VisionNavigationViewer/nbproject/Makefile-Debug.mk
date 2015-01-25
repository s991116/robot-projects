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
LDLIBSOPTIONS=-L../CameraDetector -L../VisionNavigation ../RaspicamCV/libraspicamcv.a -Wl,-rpath,../CameraDetector/dist/Debug -L../CameraDetector/dist/Debug -lCameraDetector -Wl,-rpath,../VisionNavigation/dist/Debug/None-Linux-x86 -L../VisionNavigation/dist/Debug/None-Linux-x86 -lVisionNavigation -Wl,-rpath,../Sensors/dist/Debug/None-Linux-x86 -L../Sensors/dist/Debug/None-Linux-x86 -lSensors -Wl,-rpath,../CommandScript/dist/Debug -L../CommandScript/dist/Debug -lCommandScript ../StringLibrary/dist/Debug/None-Linux-x86/libstringlibrary.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/visionnavigationviewer

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/visionnavigationviewer: ../RaspicamCV/libraspicamcv.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/visionnavigationviewer: ../CameraDetector/dist/Debug//libCameraDetector.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/visionnavigationviewer: ../VisionNavigation/dist/Debug/None-Linux-x86/libVisionNavigation.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/visionnavigationviewer: ../Sensors/dist/Debug/None-Linux-x86/libSensors.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/visionnavigationviewer: ../CommandScript/dist/Debug//libCommandScript.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/visionnavigationviewer: ../StringLibrary/dist/Debug/None-Linux-x86/libstringlibrary.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/visionnavigationviewer: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/visionnavigationviewer ${OBJECTFILES} ${LDLIBSOPTIONS} -L$(HOME)/git/raspberrypi/userland/build/lib -lmmal_core -lmmal -l mmal_util -lvcos -lbcm_host -I/usr/include/opencv -lopencv_highgui -lopencv_core -lopencv_legacy -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_imgproc

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../CameraDetector -I../VisionNavigation -I../Sensors -I../CommandScript -I../StringLibrary -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../CameraDetector && ${MAKE}  -f Makefile CONF=Debug
	cd ../VisionNavigation && ${MAKE}  -f Makefile CONF=Debug
	cd ../Sensors && ${MAKE}  -f Makefile CONF=Debug
	cd ../CommandScript && ${MAKE}  -f Makefile CONF=Debug
	cd ../StringLibrary && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/visionnavigationviewer

# Subprojects
.clean-subprojects:
	cd ../CameraDetector && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../VisionNavigation && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Sensors && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../CommandScript && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../StringLibrary && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
