
# BC55
#
# Updated: 4th December 2003

CPPC		=	bcc32
CC			=	bcc32
LN			=	bcc32

CPPC_FLAGS	=	-q
CC_FLAGS	=	-q

INCLUDES	=	-I.. -I$(STLSOFT_INCLUDE) -I$(INCLUDE)

DEFINES		=	-DNDEBUG -DCOMP_NAME="Borland 5.5"


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

run:
	poab_test.exe
	poab_so_test.exe

poab_factory.obj:	..\poab_factory.cpp
	$(CPPC) $(CPPC_FLAGS) -c -o+speed $(DEFINES) $(INCLUDES) -o$@ $?

poab_server.obj:	..\poab_server.c
	$(CC) $(CC_FLAGS) -c -o+speed $(DEFINES) $(INCLUDES) -o$@ $?

poab_test.obj:	..\poab_test.cpp
	$(CPPC) $(CPPC_FLAGS) -c -o+speed $(DEFINES) $(INCLUDES) -o$@ $?

poab_so_test.obj:	..\poab_test.cpp
	$(CPPC) $(CPPC_FLAGS) -DSHARED_CLIENT -c -o+speed $(DEFINES) $(INCLUDES) -o$@ $?


poab_test.exe:	poab_test.obj poab_factory.obj poab_server.obj
	$(LN) -L$(LIB) -e$@ poab_test.obj poab_factory.obj poab_server.obj 

poab_so.dll:	poab_factory.obj poab_server.obj
	$(LN) -WD -lGi -L$(LIB) -e$@ $**

poab_so.def:	poab_so.dll
	impdef -a $@ $**
poab_so.lib:	poab_so.def
	implib $@ $**

poab_so_test.exe:	poab_so_test.obj poab_so.lib
	$(LN) -L$(LIB) -e$@ poab_so_test.obj poab_so.lib 

