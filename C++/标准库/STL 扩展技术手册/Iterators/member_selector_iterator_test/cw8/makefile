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

!ifndef STLSOFT_INCLUDE
!error STLSOFT_INCLUDE must be defined
!endif # STLSOFT_INCLUDE

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


CC_ARGS              =   -c -I- $(INCLUDES) $(CC_DEFS)
CPPC_ARGS            =   -c -I- $(INCLUDES) $(CPPC_DEFS)
LD_ARGS              =    $(LIBS)


################################################################################
# Targets
#

all:                 target

usage:
	-@echo "make [target | test | clean]"

target:                  \
                         .\member_selector_iterator_test.exe \
                         \

test: target
	.\member_selector_iterator_test.exe

clean:
	if exist .\member_selector_iterator_test.exe del /f .\member_selector_iterator_test.exe
	if exist *.obj del /f *.obj
	if exist *.tds del /f *.tds
	if exist *.map del /f *.map

# Executables

.\member_selector_iterator_test.exe: .\member_selector_iterator_test.obj makefile
	$(LD) $(LD_ARGS) -o $@ .\member_selector_iterator_test.obj

# Objects

.\member_selector_iterator_test.obj:	..\member_selector_iterator_test.cpp makefile
	$(CPPC) $(CPPC_ARGS) -o $@ ..\member_selector_iterator_test.cpp

################################################################################

