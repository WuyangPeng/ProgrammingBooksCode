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
			..\cstatic_$(COMP_IDENT).lib	\
			..\cstatic_$(COMP_IDENT).lib	\
			.\cstatic_test.exe	\
			\


targetx:	\
			\
			.\cstatic_test_with_bc56.exe	\
			.\cstatic_test_with_cw8.exe		\
			.\cstatic_test_with_dmeta.exe	\
			.\cstatic_test_with_gcc32.exe	\
			.\cstatic_test_with_icl7.exe	\
			.\cstatic_test_with_vc6.exe		\
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
	@.\cstatic_test.exe
	

.\cstatic.o:	..\cstatic.cpp ..\cstatic.h
	$(CPPC) $(CPPC_ARGS) ..\cstatic.cpp -o$*.o

.\cstatic_test.o:	..\cstatic_test.cpp ..\cstatic.h
	$(CPPC) $(CPPC_ARGS) ..\cstatic_test.cpp -o$*.o

..\cstatic_$(COMP_IDENT).lib:	.\cstatic.o
	if exist $@ del $@
	$(LIB) $(LIB_ARGS) $@ .\cstatic.o
	
.\cstatic_test.exe:	.\cstatic_test.o ..\cstatic_$(COMP_IDENT).lib
	$(LINK) -o$@ $(LINK_ARGS) $**


.\cstatic_test_with_bc56.exe:	.\cstatic_test.o ..\cstatic_bc56.lib
	-$(LINK) -o$@ $(LINK_ARGS) $**

.\cstatic_test_with_cw8.exe:	.\cstatic_test.o ..\cstatic_cw8.lib
	-$(LINK) -o$@ $(LINK_ARGS) $**

.\cstatic_test_with_dmeta.exe:	.\cstatic_test.o ..\cstatic_dmbeta.lib
	-$(LINK) -o$@ $(LINK_ARGS) $**

.\cstatic_test_with_gcc32.exe:	.\cstatic_test.o ..\cstatic_gcc32.lib
	-$(LINK) -o$@ $(LINK_ARGS) $**

.\cstatic_test_with_icl7.exe:	.\cstatic_test.o ..\cstatic_icl7.lib
	-$(LINK) -o$@ $(LINK_ARGS) $**

.\cstatic_test_with_vc6.exe:	.\cstatic_test.o ..\cstatic_vc6.lib
	-$(LINK) -o$@ $(LINK_ARGS) $**

