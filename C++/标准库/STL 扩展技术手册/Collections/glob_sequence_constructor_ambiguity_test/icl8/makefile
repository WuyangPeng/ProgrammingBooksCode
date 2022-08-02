################################################################################
# File:     makefile
#
# Purpose:  Makefile for Intel C/C++ Compiler version 8.0
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

CC                   =   icl
CPPC                 =   icl
AR                   =   xilib
LD                   =   xilink

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


CC_ARGS              =   -c -nologo $(INCLUDES) $(CC_DEFS)
CPPC_ARGS            =   -c -nologo -GX $(INCLUDES) $(CPPC_DEFS)
LD_ARGS              =   -nologo $(LIBS)


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
	$(LD) $(LD_ARGS) -out:$@ .\glob_sequence_constructor_ambiguity_test.obj

# Objects

.\glob_sequence_constructor_ambiguity_test.obj:	..\glob_sequence_constructor_ambiguity_test.cpp makefile
	$(CPPC) $(CPPC_ARGS) -Fo$@ ..\glob_sequence_constructor_ambiguity_test.cpp

################################################################################

