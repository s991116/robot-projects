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
	${OBJECTDIR}/ConsolLog.o \
	${OBJECTDIR}/EmptyLog.o \
	${OBJECTDIR}/FileLogger.o \
	${OBJECTDIR}/ProxyLog.o


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
LDLIBSOPTIONS=../StringLibrary/dist/Debug/None-Linux-x86/libstringlibrary.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libLogging.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libLogging.${CND_DLIB_EXT}: ../StringLibrary/dist/Debug/None-Linux-x86/libstringlibrary.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libLogging.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libLogging.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/ConsolLog.o: ConsolLog.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../CommandScript -I../StringLibrary -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ConsolLog.o ConsolLog.cpp

${OBJECTDIR}/EmptyLog.o: EmptyLog.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../CommandScript -I../StringLibrary -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EmptyLog.o EmptyLog.cpp

${OBJECTDIR}/FileLogger.o: FileLogger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../CommandScript -I../StringLibrary -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FileLogger.o FileLogger.cpp

${OBJECTDIR}/ProxyLog.o: ProxyLog.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../CommandScript -I../StringLibrary -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ProxyLog.o ProxyLog.cpp

# Subprojects
.build-subprojects:
	cd ../StringLibrary && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libLogging.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../StringLibrary && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
