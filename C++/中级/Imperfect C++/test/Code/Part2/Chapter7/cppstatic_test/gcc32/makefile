# Updated: 27th November 2003

COMP_IDENT	=	gcc32
CPPC		=	g++
LIB			=	ar
LINK		=	g++

INCLUDES	=	-I.. -I$(STLSOFT_INCLUDE)

CPPC_ARGS	=	-c $(INCLUDES)

LIB_ARGS	=	-q

target:		\
			\
			..\cppstatic_$(COMP_IDENT).lib	\
			..\cppstatic_$(COMP_IDENT).lib	\
			.\cppstatic_test.exe	\
			\


targetx:	\
			\
			.\cppstatic_test_with_bc56.exe	\
			.\cppstatic_test_with_cw8.exe		\
			.\cppstatic_test_with_dmeta.exe	\
			.\cppstatic_test_with_gcc32.exe	\
			.\cppstatic_test_with_icl7.exe	\
			.\cppstatic_test_with_vc6.exe		\
			\

clean:
	@if exist *.o del /F *.o
	@if exist *.exe del /F *.exe
	@if exist *.ilc del /F *.ilc
	@if exist *.ild del /F *.ild
	@if exist *.ilf del /F *.ilf
	@if exist *.ils del /F *.ils
	@if exist *.map del /F *.map
	@if exist *.tds del /F *.tds
	@if exist *.scc del /F *.scc

run:
	@.\cppstatic_test.exe
	

.\cppstatic.o:	..\cppstatic.cpp ..\cppstatic.h
	$(CPPC) $(CPPC_ARGS) ..\cppstatic.cpp -o$*.o

.\cppstatic_test.o:	..\cppstatic_test.cpp ..\cppstatic.h
	$(CPPC) $(CPPC_ARGS) ..\cppstatic_test.cpp -o$*.o

..\cppstatic_$(COMP_IDENT).lib:	.\cppstatic.o
	if exist $@ del $@
	$(LIB) $(LIB_ARGS) $@ .\cppstatic.o
	
.\cppstatic_test.exe:	.\cppstatic_test.o ..\cppstatic_$(COMP_IDENT).lib
	$(LINK) -o$@ $(LINK_ARGS) $**


.\cppstatic_test_with_bc56.exe:	.\cppstatic_test.o ..\cppstatic_bc56.lib
	-$(LINK) -o$@ $(LINK_ARGS) $**

.\cppstatic_test_with_cw8.exe:	.\cppstatic_test.o ..\cppstatic_cw8.lib
	-$(LINK) -o$@ $(LINK_ARGS) $**

.\cppstatic_test_with_dmeta.exe:	.\cppstatic_test.o ..\cppstatic_dmbeta.lib
	-$(LINK) -o$@ $(LINK_ARGS) $**

.\cppstatic_test_with_gcc32.exe:	.\cppstatic_test.o ..\cppstatic_gcc32.lib
	-$(LINK) -o$@ $(LINK_ARGS) $**

.\cppstatic_test_with_icl7.exe:	.\cppstatic_test.o ..\cppstatic_icl7.lib
	-$(LINK) -o$@ $(LINK_ARGS) $**

.\cppstatic_test_with_vc6.exe:	.\cppstatic_test.o ..\cppstatic_vc6.lib
	-$(LINK) -o$@ $(LINK_ARGS) $**

