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
	${OBJECTDIR}/_ext/275589469/gtest-all.o \
	${OBJECTDIR}/_ext/275589469/gtest_main.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoogletest.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoogletest.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoogletest.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoogletest.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoogletest.a

${OBJECTDIR}/_ext/275589469/gtest-all.o: ../../gtest-1.7.0/src/gtest-all.cc 
	${MKDIR} -p ${OBJECTDIR}/_ext/275589469
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../gtest-1.7.0/include -I../../gtest-1.7.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/275589469/gtest-all.o ../../gtest-1.7.0/src/gtest-all.cc

${OBJECTDIR}/_ext/275589469/gtest_main.o: ../../gtest-1.7.0/src/gtest_main.cc 
	${MKDIR} -p ${OBJECTDIR}/_ext/275589469
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../gtest-1.7.0/include -I../../gtest-1.7.0 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/275589469/gtest_main.o ../../gtest-1.7.0/src/gtest_main.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libgoogletest.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
