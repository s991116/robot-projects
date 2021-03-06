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
	${OBJECTDIR}/ComPort.o \
	${OBJECTDIR}/ComStream.o \
	${OBJECTDIR}/CommunicationHandler.o \
	${OBJECTDIR}/Distance.o \
	${OBJECTDIR}/Gyro.o \
	${OBJECTDIR}/Motor.o \
	${OBJECTDIR}/Navigate.o \
	${OBJECTDIR}/SerialComRaspi.o \
	${OBJECTDIR}/SerialProtocol.o \
	${OBJECTDIR}/Servo.o

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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librobotcontroller.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librobotcontroller.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librobotcontroller.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librobotcontroller.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librobotcontroller.a

${OBJECTDIR}/ComPort.o: ComPort.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ComPort.o ComPort.cpp

${OBJECTDIR}/ComStream.o: ComStream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ComStream.o ComStream.cpp

${OBJECTDIR}/CommunicationHandler.o: CommunicationHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CommunicationHandler.o CommunicationHandler.cpp

${OBJECTDIR}/Distance.o: Distance.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Distance.o Distance.cpp

${OBJECTDIR}/Gyro.o: Gyro.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Gyro.o Gyro.cpp

${OBJECTDIR}/Motor.o: Motor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Motor.o Motor.cpp

${OBJECTDIR}/Navigate.o: Navigate.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Navigate.o Navigate.cpp

${OBJECTDIR}/SerialComRaspi.o: SerialComRaspi.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SerialComRaspi.o SerialComRaspi.cpp

${OBJECTDIR}/SerialProtocol.o: SerialProtocol.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SerialProtocol.o SerialProtocol.cpp

${OBJECTDIR}/Servo.o: Servo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Servo.o Servo.cpp

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-conf ${TESTFILES}
${TESTDIR}/TestFiles/f1: ${TESTDIR}/HardwareControllerTest.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc}  -pthread -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS} ../StringUtil/dist/Debug/GNU-Linux-x86/libstringutil.a ../googletest/dist/Debug/GNU-Linux-x86/libgoogletest.a -lwiringPi 


${TESTDIR}/HardwareControllerTest.o: HardwareControllerTest.cpp 
	${MKDIR} -p ${TESTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -I../../gtest-1.7.0/include -I. -I../../gtest-1.7.0 -I../../gtest-1.7.0/include -MMD -MP -MF "$@.d" -o ${TESTDIR}/HardwareControllerTest.o HardwareControllerTest.cpp


${OBJECTDIR}/ComPort_nomain.o: ${OBJECTDIR}/ComPort.o ComPort.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ComPort.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ComPort_nomain.o ComPort.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ComPort.o ${OBJECTDIR}/ComPort_nomain.o;\
	fi

${OBJECTDIR}/ComStream_nomain.o: ${OBJECTDIR}/ComStream.o ComStream.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/ComStream.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ComStream_nomain.o ComStream.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/ComStream.o ${OBJECTDIR}/ComStream_nomain.o;\
	fi

${OBJECTDIR}/CommunicationHandler_nomain.o: ${OBJECTDIR}/CommunicationHandler.o CommunicationHandler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/CommunicationHandler.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CommunicationHandler_nomain.o CommunicationHandler.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/CommunicationHandler.o ${OBJECTDIR}/CommunicationHandler_nomain.o;\
	fi

${OBJECTDIR}/Distance_nomain.o: ${OBJECTDIR}/Distance.o Distance.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Distance.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Distance_nomain.o Distance.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Distance.o ${OBJECTDIR}/Distance_nomain.o;\
	fi

${OBJECTDIR}/Gyro_nomain.o: ${OBJECTDIR}/Gyro.o Gyro.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Gyro.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Gyro_nomain.o Gyro.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Gyro.o ${OBJECTDIR}/Gyro_nomain.o;\
	fi

${OBJECTDIR}/Motor_nomain.o: ${OBJECTDIR}/Motor.o Motor.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Motor.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Motor_nomain.o Motor.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Motor.o ${OBJECTDIR}/Motor_nomain.o;\
	fi

${OBJECTDIR}/Navigate_nomain.o: ${OBJECTDIR}/Navigate.o Navigate.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Navigate.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Navigate_nomain.o Navigate.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Navigate.o ${OBJECTDIR}/Navigate_nomain.o;\
	fi

${OBJECTDIR}/SerialComRaspi_nomain.o: ${OBJECTDIR}/SerialComRaspi.o SerialComRaspi.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SerialComRaspi.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SerialComRaspi_nomain.o SerialComRaspi.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SerialComRaspi.o ${OBJECTDIR}/SerialComRaspi_nomain.o;\
	fi

${OBJECTDIR}/SerialProtocol_nomain.o: ${OBJECTDIR}/SerialProtocol.o SerialProtocol.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/SerialProtocol.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SerialProtocol_nomain.o SerialProtocol.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/SerialProtocol.o ${OBJECTDIR}/SerialProtocol_nomain.o;\
	fi

${OBJECTDIR}/Servo_nomain.o: ${OBJECTDIR}/Servo.o Servo.cpp 
	${MKDIR} -p ${OBJECTDIR}
	@NMOUTPUT=`${NM} ${OBJECTDIR}/Servo.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -g -I../StringUtil -I../../gtest-1.7.0/include -I../SerialMessageDataProtocol -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Servo_nomain.o Servo.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/Servo.o ${OBJECTDIR}/Servo_nomain.o;\
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
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/librobotcontroller.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
