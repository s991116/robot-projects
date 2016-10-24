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
	${OBJECTDIR}/ArduinoDataHandler.o \
	${OBJECTDIR}/ArduinoSerial.o \
	${OBJECTDIR}/DataHandler.o \
	${OBJECTDIR}/DataPackets.o \
	${OBJECTDIR}/MessageDataProtocol.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libserialmessagedataprotocol.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libserialmessagedataprotocol.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libserialmessagedataprotocol.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libserialmessagedataprotocol.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libserialmessagedataprotocol.a

${OBJECTDIR}/ArduinoDataHandler.o: ArduinoDataHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ArduinoDataHandler.o ArduinoDataHandler.cpp

${OBJECTDIR}/ArduinoSerial.o: ArduinoSerial.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ArduinoSerial.o ArduinoSerial.cpp

${OBJECTDIR}/DataHandler.o: DataHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DataHandler.o DataHandler.cpp

${OBJECTDIR}/DataPackets.o: DataPackets.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DataPackets.o DataPackets.cpp

${OBJECTDIR}/MessageDataProtocol.o: MessageDataProtocol.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MessageDataProtocol.o MessageDataProtocol.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/Mocks/HandlerMock.o ${TESTDIR}/Mocks/SerialBufferMock.o ${TESTDIR}/Mocks/SerialComMock.o ${TESTDIR}/Mocks/SerialConnectorMock.o ${TESTDIR}/_ext/275589469/gtest-all.o ${TESTDIR}/tests/testRunner.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}   -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} -L../../gtest-1.7.0/make -lpthread 


${TESTDIR}/Mocks/HandlerMock.o: Mocks/HandlerMock.cpp 
	${MKDIR} -p ${TESTDIR}/Mocks
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../gtest-1.7.0/include -I. -I../../gtest-1.7.0/src -I../../gtest-1.7.0 -IMocks -MMD -MP -MF "$@.d" -o ${TESTDIR}/Mocks/HandlerMock.o Mocks/HandlerMock.cpp


${TESTDIR}/Mocks/SerialBufferMock.o: Mocks/SerialBufferMock.cpp 
	${MKDIR} -p ${TESTDIR}/Mocks
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../gtest-1.7.0/include -I. -I../../gtest-1.7.0/src -I../../gtest-1.7.0 -IMocks -MMD -MP -MF "$@.d" -o ${TESTDIR}/Mocks/SerialBufferMock.o Mocks/SerialBufferMock.cpp


${TESTDIR}/Mocks/SerialComMock.o: Mocks/SerialComMock.cpp 
	${MKDIR} -p ${TESTDIR}/Mocks
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../gtest-1.7.0/include -I. -I../../gtest-1.7.0/src -I../../gtest-1.7.0 -IMocks -MMD -MP -MF "$@.d" -o ${TESTDIR}/Mocks/SerialComMock.o Mocks/SerialComMock.cpp


${TESTDIR}/Mocks/SerialConnectorMock.o: Mocks/SerialConnectorMock.cpp 
	${MKDIR} -p ${TESTDIR}/Mocks
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../gtest-1.7.0/include -I. -I../../gtest-1.7.0/src -I../../gtest-1.7.0 -IMocks -MMD -MP -MF "$@.d" -o ${TESTDIR}/Mocks/SerialConnectorMock.o Mocks/SerialConnectorMock.cpp


${TESTDIR}/_ext/275589469/gtest-all.o: ../../gtest-1.7.0/src/gtest-all.cc 
	${MKDIR} -p ${TESTDIR}/_ext/275589469
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../gtest-1.7.0/include -I. -I../../gtest-1.7.0/src -I../../gtest-1.7.0 -IMocks -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/275589469/gtest-all.o ../../gtest-1.7.0/src/gtest-all.cc


${TESTDIR}/tests/testRunner.o: tests/testRunner.cpp 
	${MKDIR} -p ${TESTDIR}/tests
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../../gtest-1.7.0/include -I. -I../../gtest-1.7.0/src -I../../gtest-1.7.0 -IMocks -MMD -MP -MF "$@.d" -o ${TESTDIR}/tests/testRunner.o tests/testRunner.cpp


${OBJECTDIR}/ArduinoDataHandler_nomain.o: ${OBJECTDIR}/ArduinoDataHandler.o ArduinoDataHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ArduinoDataHandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ArduinoDataHandler_nomain.o ArduinoDataHandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ArduinoDataHandler.o ${OBJECTDIR}/ArduinoDataHandler_nomain.o;\
	fi

${OBJECTDIR}/ArduinoSerial_nomain.o: ${OBJECTDIR}/ArduinoSerial.o ArduinoSerial.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ArduinoSerial.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ArduinoSerial_nomain.o ArduinoSerial.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ArduinoSerial.o ${OBJECTDIR}/ArduinoSerial_nomain.o;\
	fi

${OBJECTDIR}/DataHandler_nomain.o: ${OBJECTDIR}/DataHandler.o DataHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DataHandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DataHandler_nomain.o DataHandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/DataHandler.o ${OBJECTDIR}/DataHandler_nomain.o;\
	fi

${OBJECTDIR}/DataPackets_nomain.o: ${OBJECTDIR}/DataPackets.o DataPackets.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/DataPackets.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/DataPackets_nomain.o DataPackets.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/DataPackets.o ${OBJECTDIR}/DataPackets_nomain.o;\
	fi

${OBJECTDIR}/MessageDataProtocol_nomain.o: ${OBJECTDIR}/MessageDataProtocol.o MessageDataProtocol.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/MessageDataProtocol.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MessageDataProtocol_nomain.o MessageDataProtocol.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/MessageDataProtocol.o ${OBJECTDIR}/MessageDataProtocol_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libserialmessagedataprotocol.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
