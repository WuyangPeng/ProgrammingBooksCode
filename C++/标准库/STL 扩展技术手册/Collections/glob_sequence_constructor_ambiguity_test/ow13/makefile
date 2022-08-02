################################################################################
# File:     makefile
#
# Purpose:  Makefile for Watcom C/C++ Compiler version 1.3
#
# Status:   Auto-Generated (by Synesis Software's makemake.py) - DO NOT EDIT!!
#
# Created:  
# Updated:  
#
################################################################################


################################################################################
# Environment check
#


################################################################################
# Macros
#

CC                   =   wcc386
CPPC                 =   wpp386
AR                   =   lib386
LD                   =   wcl386

INCLUDES             =   \
                         \
                         -I.. \
                         \
                         \


LIBS                 =   \
                         \
                         \


COMMON_DEFINES       =   \
                         \
                         \


CC_DEFS              =   \
                         \
                         $(COMMON_DEFINES) \
                         \


CPPC_DEFS            =   \
                         \
                         $(COMMON_DEFINES) \
                         \


CC_ARGS              =   -zq $(INCLUDES) $(CC_DEFS)
CPPC_ARGS            =   -zq -xs $(INCLUDES) $(CPPC_DEFS)
LD_ARGS              =   -zq $(LIBS)


################################################################################
# Targets
#

all:                 target

usage:
	-@echo "make [target | test | clean]"

target:  \
                         .\glob_sequence_constructor_ambiguity_test.exe \
 \

compile: \
.\glob_sequence_constructor_ambiguity_test.obj \
 \

test: target
	.\glob_sequence_constructor_ambiguity_test.exe

clean:
	if exist .\glob_sequence_constructor_ambiguity_test.exe del /f .\glob_sequence_constructor_ambiguity_test.exe
	if exist *.obj del /f *.obj
	if exist *.tds del /f *.tds
	if exist *.map del /f *.map

# Executables

.\glob_sequence_constructor_ambiguity_test.exe: .\glob_sequence_constructor_ambiguity_test.obj makefile
	$(LD) $(LD_ARGS) -fe=$@ .\glob_sequence_constructor_ambiguity_test.obj

# Objects

.\glob_sequence_constructor_ambiguity_test.obj:	..\glob_sequence_constructor_ambiguity_test.cpp makefile
	$(CPPC) $(CPPC_ARGS) -fo=$@ ..\glob_sequence_constructor_ambiguity_test.cpp

################################################################################

