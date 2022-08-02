
# DM838
#
# Updated: 4th December 2003

CPPC		=	dmc
CC			=	dmc
LN			=	dmc

INCLUDES	=	-I- -I.. -I$(STLSOFT_INCLUDE)

DEFINES		=	-DNDEBUG -DCOMP_NAME="Digital Mars 8.38"


target:	\
		poab_so_test.exe	\
		poab_test.exe		\
		poab_so.dll			\
		\

clean:
	@-if exist *.obj del *.obj
	@-if exist *.dll del *.dll
	@-if exist *.lib del *.lib
	@-if exist *.map del *.map
	@-if exist *.exe del *.exe

run:
	poab_test.exe
	poab_so_test.exe

poab_factory.obj:	..\poab_factory.cpp
	$(CPPC) -c -o+speed $(DEFINES) $(INCLUDES) -o$@ $?

poab_server.obj:	..\poab_server.c
	$(CC) -c -o+speed $(DEFINES) $(INCLUDES) -o$@ $?

poab_factory_so.obj:	..\poab_factory.cpp
	$(CPPC) -WD -c -DSHARED_CLIENT -o+speed $(DEFINES) $(INCLUDES) -o$@ $?

poab_server_so.obj:	..\poab_server.c
	$(CC) -WD -c -DSHARED_CLIENT -o+speed $(DEFINES) $(INCLUDES) -o$@ $?

poab_test.obj:	..\poab_test.cpp
	$(CPPC) -c -o+speed $(DEFINES) $(INCLUDES) -o$@ $?

poab_so_test.obj:	..\poab_test.cpp
	$(CPPC) -DSHARED_CLIENT -c -o+speed $(DEFINES) $(INCLUDES) -o$@ $?


poab_test.exe:	poab_test.obj poab_factory.obj poab_server.obj
	$(LN) -o$@ poab_test.obj poab_factory.obj poab_server.obj 

poab_so.dll:	poab_factory_so.obj poab_server_so.obj
	$(LN) -WD $@ $** kernel32.lib

poab_so.lib:	poab_so.dll
	implib /system poab_so.lib poab_so.dll

poab_so_test.exe:	poab_so_test.obj poab_so.lib
	$(LN) -o$@ poab_so_test.obj poab_so.lib 

