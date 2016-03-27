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
	${OBJECTDIR}/CameraState.o \
	${OBJECTDIR}/ComState.o \
	${OBJECTDIR}/FaceDetectionPresentation.o \
	${OBJECTDIR}/GyroState.o \
	${OBJECTDIR}/MainState.o \
	${OBJECTDIR}/MotorState.o \
	${OBJECTDIR}/MotorTuningController.o \
	${OBJECTDIR}/ServoState.o \
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
LDLIBSOPTIONS=../StringUtil/dist/Debug/GNU-Linux-x86/libstringutil.a ../SoundPlayer/dist/Debug/GNU-Linux-x86/libsoundplayer.a ../Robot/dist/Debug/GNU-Linux-x86/librobot.a ../PiCamera/dist/Debug/GNU-Linux-x86/libpicamera.a ../RobotController/dist/Debug/GNU-Linux-x86/librobotcontroller.a -lraspicam -lraspicam_cv ../RobotHead/dist/Debug/GNU-Linux-x86/librobothead.a ../Vision/dist/Debug/GNU-Linux-x86/libvision.a ../Logging/dist/Debug/GNU-Linux-x86/liblogging.a ../Setting/dist/Debug/GNU-Linux-x86/libsetting.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol: ../StringUtil/dist/Debug/GNU-Linux-x86/libstringutil.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol: ../SoundPlayer/dist/Debug/GNU-Linux-x86/libsoundplayer.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol: ../Robot/dist/Debug/GNU-Linux-x86/librobot.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol: ../PiCamera/dist/Debug/GNU-Linux-x86/libpicamera.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol: ../RobotController/dist/Debug/GNU-Linux-x86/librobotcontroller.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol: ../RobotHead/dist/Debug/GNU-Linux-x86/librobothead.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol: ../Vision/dist/Debug/GNU-Linux-x86/libvision.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol: ../Logging/dist/Debug/GNU-Linux-x86/liblogging.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol: ../Setting/dist/Debug/GNU-Linux-x86/libsetting.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol ${OBJECTFILES} ${LDLIBSOPTIONS} -lncurses -lopencv_nonfree -lopencv_objdetect -lopencv_features2d -lopencv_imgproc -lopencv_highgui -lopencv_core

${OBJECTDIR}/CameraState.o: CameraState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../SoundPlayer -I../PiCamera -I../RobotController -I../RobotHead -I../Robot -I../Setting -I../Logging -I../Vision -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CameraState.o CameraState.cpp

${OBJECTDIR}/ComState.o: ComState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../SoundPlayer -I../PiCamera -I../RobotController -I../RobotHead -I../Robot -I../Setting -I../Logging -I../Vision -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ComState.o ComState.cpp

${OBJECTDIR}/FaceDetectionPresentation.o: FaceDetectionPresentation.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../SoundPlayer -I../PiCamera -I../RobotController -I../RobotHead -I../Robot -I../Setting -I../Logging -I../Vision -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FaceDetectionPresentation.o FaceDetectionPresentation.cpp

${OBJECTDIR}/GyroState.o: GyroState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../SoundPlayer -I../PiCamera -I../RobotController -I../RobotHead -I../Robot -I../Setting -I../Logging -I../Vision -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/GyroState.o GyroState.cpp

${OBJECTDIR}/MainState.o: MainState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../SoundPlayer -I../PiCamera -I../RobotController -I../RobotHead -I../Robot -I../Setting -I../Logging -I../Vision -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MainState.o MainState.cpp

${OBJECTDIR}/MotorState.o: MotorState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../SoundPlayer -I../PiCamera -I../RobotController -I../RobotHead -I../Robot -I../Setting -I../Logging -I../Vision -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MotorState.o MotorState.cpp

${OBJECTDIR}/MotorTuningController.o: MotorTuningController.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../SoundPlayer -I../PiCamera -I../RobotController -I../RobotHead -I../Robot -I../Setting -I../Logging -I../Vision -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MotorTuningController.o MotorTuningController.cpp

${OBJECTDIR}/ServoState.o: ServoState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../SoundPlayer -I../PiCamera -I../RobotController -I../RobotHead -I../Robot -I../Setting -I../Logging -I../Vision -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ServoState.o ServoState.cpp

${OBJECTDIR}/State.o: State.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../SoundPlayer -I../PiCamera -I../RobotController -I../RobotHead -I../Robot -I../Setting -I../Logging -I../Vision -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/State.o State.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../SoundPlayer -I../PiCamera -I../RobotController -I../RobotHead -I../Robot -I../Setting -I../Logging -I../Vision -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:
	cd ../StringUtil && ${MAKE}  -f Makefile CONF=Debug
	cd ../SoundPlayer && ${MAKE}  -f Makefile CONF=Debug
	cd ../Robot && ${MAKE}  -f Makefile CONF=Debug
	cd ../PiCamera && ${MAKE}  -f Makefile CONF=Debug
	cd ../RobotController && ${MAKE}  -f Makefile CONF=Debug
	cd ../RobotHead && ${MAKE}  -f Makefile CONF=Debug
	cd ../Vision && ${MAKE}  -f Makefile CONF=Debug
	cd ../Logging && ${MAKE}  -f Makefile CONF=Debug
	cd ../Setting && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/remotecontrol

# Subprojects
.clean-subprojects:
	cd ../StringUtil && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../SoundPlayer && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Robot && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../PiCamera && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../RobotController && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../RobotHead && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Vision && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Logging && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Setting && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
