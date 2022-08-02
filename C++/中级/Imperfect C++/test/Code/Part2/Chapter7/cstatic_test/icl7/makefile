
COMP_IDENT	=	icl7
CPPC		=	icl
AR			=	xilib
LINK		=	xilink

INCLUDES	=	-I.. -I$(STLSOFT_INCLUDE)

CPPC_ARGS	=	-c -nologo $(INCLUDES)

LIB_ARGS	=	-nologo 

LINK_ARGS	=	-nologo

#LIBS		=	-L$(AR)

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
	@if exist *.obj del /F *.obj
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
	

.\cstatic.obj:	..\cstatic.cpp ..\cstatic.h
	$(CPPC) $(CPPC_ARGS) ..\cstatic.cpp -o$*.obj

.\cstatic_test.obj:	..\cstatic_test.cpp ..\cstatic.h
	$(CPPC) $(CPPC_ARGS) ..\cstatic_test.cpp -o$*.obj

..\cstatic_$(COMP_IDENT).lib:	.\cstatic.obj
	if exist $@ del $@
	$(AR) -out:$@ $(LIB_ARGS) .\cstatic.obj
	
.\cstatic_test.exe:	.\cstatic_test.obj ..\cstatic_$(COMP_IDENT).lib
	$(LINK) -out:$@ $(LINK_ARGS) $**


.\cstatic_test_with_bc56.exe:	.\cstatic_test.obj ..\cstatic_bc56.lib
	-$(LINK) -out:$@ $(LINK_ARGS) $**

.\cstatic_test_with_cw8.exe:	.\cstatic_test.obj ..\cstatic_cw8.lib
	-$(LINK) -out:$@ $(LINK_ARGS) $**

.\cstatic_test_with_dmeta.exe:	.\cstatic_test.obj ..\cstatic_dmbeta.lib
	-$(LINK) -out:$@ $(LINK_ARGS) $**

.\cstatic_test_with_gcc32.exe:	.\cstatic_test.obj ..\cstatic_gcc32.lib
	-$(LINK) -out:$@ $(LINK_ARGS) $**

.\cstatic_test_with_icl7.exe:	.\cstatic_test.obj ..\cstatic_icl7.lib
	-$(LINK) -out:$@ $(LINK_ARGS) $**

.\cstatic_test_with_vc6.exe:	.\cstatic_test.obj ..\cstatic_vc6.lib
	-$(LINK) -out:$@ $(LINK_ARGS) $**
