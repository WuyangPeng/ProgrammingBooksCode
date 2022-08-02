################################################################################
# File:     makefile
#
# Purpose:  Makefile for Digital Mars C/C++ Compiler version beta
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

CC                   =   dmc
CPPC                 =   dmc
AR                   =   lib
LD                   =   dmc

INCLUDES             =   \
                         \
                         -I.. \
                         \
                         -I$(STLSOFT_INCLUDE) \
                         -I$(STLSOFT_INCLUDE)\inprogress \
                         -I$(STLSOFT_INCLUDE)\research \
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


CC_ARGS              =   -c -L/NOI $(INCLUDES) $(CC_DEFS)
CPPC_ARGS            =   -c -Ae $(INCLUDES) $(CPPC_DEFS)
LD_ARGS              =   /NOI $(LIBS)


################################################################################
# Targets
#

all:                 target

usage:
	-@echo "make [target | test | clean]"

target:  \
                         .\strtok_intra_thread_test.exe \
 \

compile: \
.\strtok_intra_thread_test.obj \
 \

test: target
	.\strtok_intra_thread_test.exe

clean:
	if exist .\strtok_intra_thread_test.exe del /f .\strtok_intra_thread_test.exe
	if exist *.obj del /f *.obj
	if exist *.tds del /f *.tds
	if exist *.map del /f *.map

# Executables

.\strtok_intra_thread_test.exe: .\strtok_intra_thread_test.obj makefile
	$(LD) $(LD_ARGS) -o$@ .\strtok_intra_thread_test.obj

# Objects

.\strtok_intra_thread_test.obj:	..\strtok_intra_thread_test.c makefile
	$(CC) $(CC_ARGS) -o$@ ..\strtok_intra_thread_test.c

################################################################################

