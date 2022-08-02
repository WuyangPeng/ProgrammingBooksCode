
# GCC 2.95
#
# Updated: 4th December 2003

CPPC		=	g++
CC			=	gcc
LN			=	g++

INCLUDES	=	-I.. -I$(STLSOFT_INCLUDE)

DEFINES		=	-DNDEBUG -DCOMP_NAME="GCC 2.95"


target:	\
		poab_so_test.exe	\
		poab_test.exe		\
		poab_so.dll			\
		\

clean:
	@-if exist *.o del *.o
	@-if exist *.dll del *.dll
	@-if exist *.lib del *.lib
	@-if exist *.exe del *.exe

run:
	poab_test.exe
	poab_so_test.exe

poab_factory.o:	..\poab_factory.cpp
	$(CPPC) -c -O7 $(DEFINES) $(INCLUDES) -o $@ $?

poab_server.o:	..\poab_server.c
	$(CC) -c -O7 $(DEFINES) $(INCLUDES) -o $@ $?

poab_test.o:	..\poab_test.cpp
	$(CPPC) -c -O7 $(DEFINES) $(INCLUDES) -o $@ $?

poab_so_test.o:	..\poab_test.cpp
	$(CPPC) -DSHARED_CLIENT -c -O7 $(DEFINES) $(INCLUDES) -o $@ $?


poab_test.exe:	poab_test.o poab_factory.o poab_server.o
	$(LN) -O7 -o $@ poab_test.o poab_factory.o poab_server.o

poab_so.dll:	poab_factory.o poab_server.o
	$(LN) -Wl,--out-implib,.\poab_so.lib  -shared -o $@ poab_factory.o poab_server.o

poab_so.lib:	poab_so.dll

poab_so_test.exe:	poab_so_test.o poab_so.lib
	$(LN) -o $@ poab_so_test.o poab_so.lib
