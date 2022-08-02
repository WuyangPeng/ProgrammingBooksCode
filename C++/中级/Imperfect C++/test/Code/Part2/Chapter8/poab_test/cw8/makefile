
# CW8
#
# Updated: 4th December 2003

CPPC		=	mwcc
CC			=	mwcc
LN			=	mwld

INCLUDES	=	-I- -I.. -I$(STLSOFT_INCLUDE)

DEFINES		=	-DNDEBUG -DCOMP_NAME="CodeWarrior 8"


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
	$(CPPC) -c -O4 $(DEFINES) $(INCLUDES) -o $@ $?

poab_server.obj:	..\poab_server.c
	$(CC) -c -O4 $(DEFINES) $(INCLUDES) -o $@ $?

poab_test.obj:	..\poab_test.cpp
	$(CPPC) -c -O4 $(DEFINES) $(INCLUDES) -o $@ $?

poab_so_test.obj:	..\poab_test.cpp
	$(CPPC) -DSHARED_CLIENT -c -O4 $(DEFINES) $(INCLUDES) -o $@ $?


poab_test.exe:	poab_test.obj poab_factory.obj poab_server.obj
	$(LN) -o $@ poab_test.obj poab_factory.obj poab_server.obj 

poab_so.dll:	poab_factory.obj poab_server.obj
	$(LN) -shared $** -o $@

poab_so.lib:	poab_so.dll

poab_so_test.exe:	poab_so_test.obj poab_so.lib
	$(LN) -o $@ poab_so_test.obj poab_so.lib 

