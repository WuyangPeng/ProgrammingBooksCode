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
                         -I$(STLSOFT)/include \
                         -I$(STLSOFT_1_9_X)/include \
                         -I$(STLSOFT_XMLSTL)/include \
                         -I$(BOOST_INCLUDE) \
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


CC_OPT               =   \
                         \
                         -O2 -Ox -GL \
                         \


CPPC_OPT             =   \
                         \
                         -O2 -Ox -GL \
                         \


CC_ARGS              =   -c -nologo $(INCLUDES) $(CC_DEFS) $(CC_OPT)
CPPC_ARGS            =   -c -nologo -GX $(INCLUDES) $(CPPC_DEFS) $(CPPC_OPT)
LD_ARGS              =   -nologo $(LIBS)


################################################################################
# Targets
#

all:                 target

usage:
	-@echo "make [target | test | clean]"

target:  \
                         .\string_tokeniser_1_speed_test.exe \
 \

compile: \
.\string_tokeniser_1_speed_test.obj \
.\strtok_boost.obj \
.\strtok_current.obj \
.\strtok_current_1_9.obj \
.\strtok_current_1_9_s_v.obj \
.\strtok_current_1_9_v_s.obj \
.\strtok_current_1_9_v_v.obj \
.\strtok_find_next_token.obj \
.\strtok_ptr_only.obj \
.\strtok_sstream.obj \
.\strtok_strtok.obj \
.\strtok_strtok_r.obj \
 \

test: target
	.\string_tokeniser_1_speed_test.exe

clean:
	if exist .\string_tokeniser_1_speed_test.exe del /f .\string_tokeniser_1_speed_test.exe
	if exist *.obj del /f *.obj
	if exist *.tds del /f *.tds
	if exist *.map del /f *.map

# Executables

.\string_tokeniser_1_speed_test.exe: .\string_tokeniser_1_speed_test.obj .\strtok_boost.obj .\strtok_current.obj .\strtok_current_1_9.obj .\strtok_current_1_9_s_v.obj .\strtok_current_1_9_v_s.obj .\strtok_current_1_9_v_v.obj .\strtok_find_next_token.obj .\strtok_ptr_only.obj .\strtok_sstream.obj .\strtok_strtok.obj .\strtok_strtok_r.obj makefile
	$(LD) $(LD_ARGS) -out:$@ .\string_tokeniser_1_speed_test.obj .\strtok_boost.obj .\strtok_current.obj .\strtok_current_1_9.obj .\strtok_current_1_9_s_v.obj .\strtok_current_1_9_v_s.obj .\strtok_current_1_9_v_v.obj .\strtok_find_next_token.obj .\strtok_ptr_only.obj .\strtok_sstream.obj .\strtok_strtok.obj .\strtok_strtok_r.obj

# Objects

.\string_tokeniser_1_speed_test.obj:	..\string_tokeniser_1_speed_test.cpp makefile
	$(CPPC) $(CPPC_ARGS) -Fo$@ ..\string_tokeniser_1_speed_test.cpp
.\strtok_boost.obj:	..\strtok_boost.cpp makefile
	$(CPPC) $(CPPC_ARGS) -Fo$@ ..\strtok_boost.cpp
.\strtok_current.obj:	..\strtok_current.cpp makefile
	$(CPPC) $(CPPC_ARGS) -Fo$@ ..\strtok_current.cpp
.\strtok_current_1_9.obj:	..\strtok_current_1_9.cpp makefile
	$(CPPC) $(CPPC_ARGS) -Fo$@ ..\strtok_current_1_9.cpp
.\strtok_current_1_9_s_v.obj:	..\strtok_current_1_9_s_v.cpp makefile
	$(CPPC) $(CPPC_ARGS) -Fo$@ ..\strtok_current_1_9_s_v.cpp
.\strtok_current_1_9_v_s.obj:	..\strtok_current_1_9_v_s.cpp makefile
	$(CPPC) $(CPPC_ARGS) -Fo$@ ..\strtok_current_1_9_v_s.cpp
.\strtok_current_1_9_v_v.obj:	..\strtok_current_1_9_v_v.cpp makefile
	$(CPPC) $(CPPC_ARGS) -Fo$@ ..\strtok_current_1_9_v_v.cpp
.\strtok_find_next_token.obj:	..\strtok_find_next_token.cpp makefile
	$(CPPC) $(CPPC_ARGS) -Fo$@ ..\strtok_find_next_token.cpp
.\strtok_ptr_only.obj:	..\strtok_ptr_only.cpp makefile
	$(CPPC) $(CPPC_ARGS) -Fo$@ ..\strtok_ptr_only.cpp
.\strtok_sstream.obj:	..\strtok_sstream.cpp makefile
	$(CPPC) $(CPPC_ARGS) -Fo$@ ..\strtok_sstream.cpp
.\strtok_strtok.obj:	..\strtok_strtok.cpp makefile
	$(CPPC) $(CPPC_ARGS) -Fo$@ ..\strtok_strtok.cpp
.\strtok_strtok_r.obj:	..\strtok_strtok_r.cpp makefile
	$(CPPC) $(CPPC_ARGS) -Fo$@ ..\strtok_strtok_r.cpp

################################################################################

