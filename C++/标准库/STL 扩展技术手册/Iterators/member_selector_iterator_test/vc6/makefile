################################################################################
# File:     makefile
#
# Purpose:  Makefile for Visual C++ Compiler version 6.0
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

CC                   =   cl
CPPC                 =   cl
AR                   =   lib
LD                   =   link

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


CC_ARGS              =   -c -nologo $(INCLUDES) $(CC_DEFS)
CPPC_ARGS            =   -c -nologo -GX $(INCLUDES) $(CPPC_DEFS)
LD_ARGS              =   -nologo $(LIBS)


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
	$(LD) $(LD_ARGS) -out:$@ .\member_selector_iterator_test.obj

# Objects

.\member_selector_iterator_test.obj:	..\member_selector_iterator_test.cpp makefile
	$(CPPC) $(CPPC_ARGS) -Fo$@ ..\member_selector_iterator_test.cpp

################################################################################

