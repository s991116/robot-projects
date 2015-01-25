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
	${OBJECTDIR}/AddDistanceCommand.o \
	${OBJECTDIR}/CheckWithBreak.o \
	${OBJECTDIR}/Command.o \
	${OBJECTDIR}/DirectComCommand.o \
	${OBJECTDIR}/DistanceCheck.o \
	${OBJECTDIR}/DistanceSensorCheck.o \
	${OBJECTDIR}/LineCheck.o \
	${OBJECTDIR}/LoggingSetting.o \
	${OBJECTDIR}/MoveFixedDirCommand.o \
	${OBJECTDIR}/PortCheck.o \
	${OBJECTDIR}/ResetMoveCommand.o \
	${OBJECTDIR}/SensorFactory.o \
	${OBJECTDIR}/SensorInfo.o \
	${OBJECTDIR}/Setting.o \
	${OBJECTDIR}/SnapshotCommand.o \
	${OBJECTDIR}/SpeedCommand.o \
	${OBJECTDIR}/StartDistanceCommand.o \
	${OBJECTDIR}/SwitchCheck.o \
	${OBJECTDIR}/WaitCommand.o


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
LDLIBSOPTIONS=-L../ArduinoController -L../CameraDetector ../StringLibrary/dist/Debug/None-Linux-x86/libstringlibrary.a -Wl,-rpath,../VisionNavigation/dist/Debug/None-Linux-x86 -L../VisionNavigation/dist/Debug/None-Linux-x86 -lVisionNavigation

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSensors.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSensors.${CND_DLIB_EXT}: ../StringLibrary/dist/Debug/None-Linux-x86/libstringlibrary.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSensors.${CND_DLIB_EXT}: ../VisionNavigation/dist/Debug/None-Linux-x86/libVisionNavigation.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSensors.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSensors.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/AddDistanceCommand.o: AddDistanceCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AddDistanceCommand.o AddDistanceCommand.cpp

${OBJECTDIR}/CheckWithBreak.o: CheckWithBreak.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CheckWithBreak.o CheckWithBreak.cpp

${OBJECTDIR}/Command.o: Command.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Command.o Command.cpp

${OBJECTDIR}/DirectComCommand.o: DirectComCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DirectComCommand.o DirectComCommand.cpp

${OBJECTDIR}/DistanceCheck.o: DistanceCheck.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DistanceCheck.o DistanceCheck.cpp

${OBJECTDIR}/DistanceSensorCheck.o: DistanceSensorCheck.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DistanceSensorCheck.o DistanceSensorCheck.cpp

${OBJECTDIR}/LineCheck.o: LineCheck.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LineCheck.o LineCheck.cpp

${OBJECTDIR}/LoggingSetting.o: LoggingSetting.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LoggingSetting.o LoggingSetting.cpp

${OBJECTDIR}/MoveFixedDirCommand.o: MoveFixedDirCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MoveFixedDirCommand.o MoveFixedDirCommand.cpp

${OBJECTDIR}/PortCheck.o: PortCheck.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PortCheck.o PortCheck.cpp

${OBJECTDIR}/ResetMoveCommand.o: ResetMoveCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ResetMoveCommand.o ResetMoveCommand.cpp

${OBJECTDIR}/SensorFactory.o: SensorFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SensorFactory.o SensorFactory.cpp

${OBJECTDIR}/SensorInfo.o: SensorInfo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SensorInfo.o SensorInfo.cpp

${OBJECTDIR}/Setting.o: Setting.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Setting.o Setting.cpp

${OBJECTDIR}/SnapshotCommand.o: SnapshotCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SnapshotCommand.o SnapshotCommand.cpp

${OBJECTDIR}/SpeedCommand.o: SpeedCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SpeedCommand.o SpeedCommand.cpp

${OBJECTDIR}/StartDistanceCommand.o: StartDistanceCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/StartDistanceCommand.o StartDistanceCommand.cpp

${OBJECTDIR}/SwitchCheck.o: SwitchCheck.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SwitchCheck.o SwitchCheck.cpp

${OBJECTDIR}/WaitCommand.o: WaitCommand.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Logging -I../ArduinoController -I../CameraDetector -I../StringLibrary -I../VisionNavigation -I. -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/WaitCommand.o WaitCommand.cpp

# Subprojects
.build-subprojects:
	cd ../StringLibrary && ${MAKE}  -f Makefile CONF=Debug
	cd ../VisionNavigation && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libSensors.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../StringLibrary && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../VisionNavigation && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
