################################################################################
# File:     makefile
#
# Purpose:  Makefile for Metrowerks CodeWarrior C/C++ Compiler version 8
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

CC                   =   mwcc
CPPC                 =   mwcc
AR                   =   mwld
LD                   =   mwld

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


CC_ARGS              =   -c -I- $(INCLUDES) $(CC_DEFS)
CPPC_ARGS            =   -c -I- $(INCLUDES) $(CPPC_DEFS)
LD_ARGS              =    $(LIBS)


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
	$(LD) $(LD_ARGS) -o $@ .\glob_sequence_constructor_ambiguity_test.obj

# Objects

.\glob_sequence_constructor_ambiguity_test.obj:	..\glob_sequence_constructor_ambiguity_test.cpp makefile
	$(CPPC) $(CPPC_ARGS) -o $@ ..\glob_sequence_constructor_ambiguity_test.cpp

################################################################################

