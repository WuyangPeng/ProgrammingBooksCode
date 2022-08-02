
# WC12
#
# Updated: 6th December 2003


CPPC		=	wpp386
CC			=	wcc386
LN			=	wcl386

CPPC_FLAGS	=	-zq -3s
CC_FLAGS	=	-zq -3s
LN_FLAGS	=	-zq -3s

INCLUDES	=	-I.. -I$(STLSOFT_INCLUDE)

DEFINES		=	-DNDEBUG -DCOMP_NAME="Watcom-12"


target:	\
		poab_so_test.exe	\
		poab_test.exe		\
		poab_so.dll			\
		\

clean:
	@-if exist *.obj del *.obj
	@-if exist *.dll del *.dll
	@-if exist *.lib del *.lib
	@-if exist *.exe del *.exe
	@-if exist *.err del *.err

run:
	poab_test.exe
	poab_so_test.exe

poab_factory.obj:	..\poab_factory.cpp
	$(CPPC) $(CPPC_FLAGS) -oeaxt $(DEFINES) $(INCLUDES) -fo=$@ $?
poab_factory_so.obj:	..\poab_factory.cpp
	$(CPPC) $(CPPC_FLAGS) -bd -oeaxt $(DEFINES) $(INCLUDES) -fo=$@ $?

poab_server.obj:	..\poab_server.c
	$(CC) $(CC_FLAGS) -oeaxt $(DEFINES) $(INCLUDES) -fo=$@ $?
poab_server_so.obj:	..\poab_server.c
	$(CC) $(CC_FLAGS) -bd -oeaxt $(DEFINES) $(INCLUDES) -fo=$@ $?

poab_test.obj:	..\poab_test.cpp
	$(CPPC) $(CPPC_FLAGS) -oeaxt $(DEFINES) $(INCLUDES) -fo=$@ $?
poab_so_test.obj:	..\poab_test.cpp
	$(CPPC) $(CPPC_FLAGS) -DSHARED_CLIENT -oeaxt $(DEFINES) $(INCLUDES) -fo=$@ $?


poab_test.exe:	poab_test.obj poab_factory.obj poab_server.obj
	$(LN) $(LN_FLAGS) -fe=$@ poab_test.obj poab_factory.obj poab_server.obj 

poab_so.dll:	poab_factory_so.obj poab_server_so.obj
	$(LN) $(LN_FLAGS) -bd -l=nt_dll -fe=$@ -"op implib" $** kernel32.lib user32.lib

poab_so.lib:	poab_so.dll

poab_so_test.exe:	poab_so_test.obj poab_so.lib
	$(LN) $(LN_FLAGS) -fe=$@ poab_so_test.obj poab_so.lib 


###################################################

#.suffixes:
#.suffixes: .obj .obd .cpp .c
#
#proj_name	=	poab
#dll_name	=	poab_server
#dll_objs	=	poab_server.obj poab_factory.obj
#dll_obds	=	poab_server.obd poab_factory.obd
#
#exe_name	=	poab_test
#exe_objs	=	poab_test.obj
#
#.cpp.obj:
#     wpp386 -zq $<
#
#.c.obj:
#     wcc386 -zq $<
#
#.cpp.obd:
#     wpp386 -zq -bd -fo=$@ $<
#
#.c.obd:
#     wcc386 -zq -bd -fo=$@ $<
#
#target: $(proj_name).exe $(dll_name).dll $(exe_name).exe
#
#clean: .symbolic
#	@if exist *.obj del *.obj
#	@if exist *.obd del *.obd
#	@if exist *.dll del *.dll
#	@if exist *.exe del *.exe
#	@if exist *.err del *.err
#	@if exist *.lib del *.lib
#
#$(proj_name).exe: $(exe_objs) $(dll_objs)
#     wlink op quiet sys nt name $(proj_name) file { $< }
#
#$(dll_name).dll: $(dll_obds)
#     wlink op quiet sys nt_dll name $(dll_name) file { $< } op implib
#
#$(exe_name).exe: $(exe_objs) $(dll_name).dll
#     wlink op quiet sys nt name $(exe_name) file { $(exe_objs) } lib $(dll_name).lib
#

###################################################
