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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/d09b55ec/main.o \
	${OBJECTDIR}/_ext/cf9a8a83/puertos.o \
	${OBJECTDIR}/_ext/cf9a8a83/simulacion.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp11_leds

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp11_leds: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp11_leds ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/d09b55ec/main.o: ../../Descargas/AllegroEx3Bitmaps/main.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/d09b55ec
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/d09b55ec/main.o ../../Descargas/AllegroEx3Bitmaps/main.c

${OBJECTDIR}/_ext/cf9a8a83/puertos.o: ../../NetBeansProjects/TP-11/TP-10/puertos.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/cf9a8a83
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cf9a8a83/puertos.o ../../NetBeansProjects/TP-11/TP-10/puertos.c

${OBJECTDIR}/_ext/cf9a8a83/simulacion.o: ../../NetBeansProjects/TP-11/TP-10/simulacion.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/cf9a8a83
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cf9a8a83/simulacion.o ../../NetBeansProjects/TP-11/TP-10/simulacion.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tp11_leds

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
