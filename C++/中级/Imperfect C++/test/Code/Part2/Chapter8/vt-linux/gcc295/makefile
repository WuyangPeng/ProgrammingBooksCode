
CPPC	=	g++
CC	=	gcc
AR	=	g++

target:		\
		vtcli_cpp.exe	\
		vtcli_c.exe		\
		\

run: vtcli_cpp.exe vtcli_c.exe
	vtcli_cpp.exe
	vtcli_c.exe



vtcli_cpp.o:	..\vtcli_cpp.cpp ..\vt.h
	@echo Compiling C++ client
	$(CPPC) -o $@ -c ..\vtcli_cpp.cpp

vtcli_c.o:	..\vtcli_c.c ..\vt.h
	@echo Compiling C client
	$(CC) -fpack-struct -o $@ -c ..\vtcli_c.c

vt.o:	..\vt.cpp ..\vt.h
	@echo "Compiling server (C++)"
	$(CPPC) -o $@ -c ..\vt.cpp


vtcli_cpp.exe:	vtcli_cpp.o vt.o
	@echo Linking C++ executable
	$(AR) -o $@ vtcli_cpp.o vt.o

vtcli_c.exe:	vtcli_c.o vt.o
	@echo Linking C executable
	$(AR) -o $@ vtcli_c.o vt.o

clean:
	rm -f *.o
	rm -f vtcli_c.exe vtcli_cpp.exe a.out

