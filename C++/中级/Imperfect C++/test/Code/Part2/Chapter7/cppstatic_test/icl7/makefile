
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
	@.\cppstatic_test.exe
	

.\cppstatic.obj:	..\cppstatic.cpp ..\cppstatic.h
	$(CPPC) $(CPPC_ARGS) ..\cppstatic.cpp -o$*.obj

.\cppstatic_test.obj:	..\cppstatic_test.cpp ..\cppstatic.h
	$(CPPC) $(CPPC_ARGS) ..\cppstatic_test.cpp -o$*.obj

..\cppstatic_$(COMP_IDENT).lib:	.\cppstatic.obj
	if exist $@ del $@
	$(AR) -out:$@ $(LIB_ARGS) .\cppstatic.obj
	
.\cppstatic_test.exe:	.\cppstatic_test.obj ..\cppstatic_$(COMP_IDENT).lib
	$(LINK) -out:$@ $(LINK_ARGS) $**


.\cppstatic_test_with_bc56.exe:	.\cppstatic_test.obj ..\cppstatic_bc56.lib
	-$(LINK) -out:$@ $(LINK_ARGS) $**

.\cppstatic_test_with_cw8.exe:	.\cppstatic_test.obj ..\cppstatic_cw8.lib
	-$(LINK) -out:$@ $(LINK_ARGS) $**

.\cppstatic_test_with_dmeta.exe:	.\cppstatic_test.obj ..\cppstatic_dmbeta.lib
	-$(LINK) -out:$@ $(LINK_ARGS) $**

.\cppstatic_test_with_gcc32.exe:	.\cppstatic_test.obj ..\cppstatic_gcc32.lib
	-$(LINK) -out:$@ $(LINK_ARGS) $**

.\cppstatic_test_with_icl7.exe:	.\cppstatic_test.obj ..\cppstatic_icl7.lib
	-$(LINK) -out:$@ $(LINK_ARGS) $**

.\cppstatic_test_with_vc6.exe:	.\cppstatic_test.obj ..\cppstatic_vc6.lib
	-$(LINK) -out:$@ $(LINK_ARGS) $**
