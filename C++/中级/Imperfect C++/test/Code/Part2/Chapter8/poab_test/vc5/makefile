
# VC5
#
# Updated: 5th December 2003

CPPC		=	cl
CC			=	cl
LN			=	link

CPPC_FLAGS	=	-nologo -GX
CC_FLAGS	=	-nologo
LN_FLAGS	=	-nologo


INCLUDES	=	-I.. -I$(STLSOFT_INCLUDE)

DEFINES		=	-DNDEBUG -DCOMP_NAME="Visual C++ 5"


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
	$(CPPC) $(CPPC_FLAGS) -c -O2 -Og -Ox -Ob2 $(DEFINES) $(INCLUDES) -Fo$@ $?

poab_server.obj:	..\poab_server.c
	$(CC) $(CC_FLAGS) -c -O2 -Og -Ox -Ob2 $(DEFINES) $(INCLUDES) -Fo$@ $?

poab_test.obj:	..\poab_test.cpp
	$(CPPC) $(CPPC_FLAGS) -c -O2 -Og -Ox -Ob2 $(DEFINES) $(INCLUDES) -Fo$@ $?

poab_so_test.obj:	..\poab_test.cpp
	$(CPPC) $(CPPC_FLAGS) -DSHARED_CLIENT -c -O2 -Og -Ox -Ob2 $(DEFINES) $(INCLUDES) -Fo$@ $?


poab_test.exe:	poab_test.obj poab_factory.obj poab_server.obj
	$(LN) $(LN_FLAGS) -out:$@ poab_test.obj poab_factory.obj poab_server.obj 

poab_so.dll:	poab_factory.obj poab_server.obj
	$(LN) $(LN_FLAGS) -dll $** -out:$@

poab_so.lib:	poab_so.dll

poab_so_test.exe:	poab_so_test.obj poab_so.lib
	$(LN) $(LN_FLAGS) -out:$@ poab_so_test.obj poab_so.lib 

