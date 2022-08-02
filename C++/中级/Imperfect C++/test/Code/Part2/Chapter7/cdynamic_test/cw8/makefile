# Updated: 27th November 2003

COMP_IDENT	=	cw8
CPPC		=	mwcc
AR			=	mwld
LINK		=	mwld

INCLUDES	=	-I- -I.. -I$(STLSOFT_INCLUDE) -I$(SYNESIS_DEV)\include

CPPC_ARGS	=	-c -runtime dllmulti $(INCLUDES)

LIB_ARGS	=	-shared

target:		\
			\
			.\cdynamic.dll	\
			.\cdynamic_test.exe	\
			\

targetx:	\
			\
			.\test\bc56\cdynamic_test.exe	\
			.\test\cw8\cdynamic_test.exe	\
			.\test\dmbeta\cdynamic_test.exe	\
			.\test\gcc32\cdynamic_test.exe	\
			.\test\icl7\cdynamic_test.exe	\
			.\test\vc6\cdynamic_test.exe	\
			\
			..\bc56\test\$(COMP_IDENT)\cdynamic.dll	\
			..\cw8\test\\$(COMP_IDENT)\cdynamic.dll	\
			..\dmbeta\test\\$(COMP_IDENT)\cdynamic.dll	\
			..\gcc32\test\\$(COMP_IDENT)\cdynamic.dll	\
			..\icl7\test\\$(COMP_IDENT)\cdynamic.dll	\
			..\vc6\test\\$(COMP_IDENT)\cdynamic.dll	\
			\

clean:
	@if exist *.obj del /F *.obj
	@if exist *.dll del /F *.dll
	@if exist *.exe del /F *.exe
	@if exist *.lib del /F *.lib
	@if exist *.ilc del /F *.ilc
	@if exist *.ild del /F *.ild
	@if exist *.ilf del /F *.ilf
	@if exist *.ils del /F *.ils
	@if exist *.map del /F *.map
	@if exist *.tds del /F *.tds
	@if exist *.scc del /F *.scc

run:
	@.\cdynamic_test.exe
	

.\cdynamic.obj:	..\cdynamic.cpp ..\cdynamic.h
	$(CPPC) $(CPPC_ARGS) ..\cdynamic.cpp -o $*.obj

.\cdynamic_test.obj:	..\cdynamic_test.cpp ..\cdynamic.h
	$(CPPC) $(CPPC_ARGS) ..\cdynamic_test.cpp -o	$*.obj

.\cdynamic.dll:	.\cdynamic.obj
	if exist $@ del $@
	$(AR) $(LIB_ARGS) -o $@ .\cdynamic.obj
	
.\cdynamic_test.exe:	.\cdynamic_test.obj .\cdynamic.lib
	$(LINK) -o $@ $(LINK_ARGS) $**


.\test\bc56\cdynamic_test.exe:	.\cdynamic_test.exe
	copy $? $@ /y
.\test\cw8\cdynamic_test.exe:	.\cdynamic_test.exe
	copy $? $@ /y
.\test\dmbeta\cdynamic_test.exe:	.\cdynamic_test.exe
	copy $? $@ /y
.\test\gcc32\cdynamic_test.exe:	.\cdynamic_test.exe
	copy $? $@ /y
.\test\icl7\cdynamic_test.exe:	.\cdynamic_test.exe
	copy $? $@ /y
.\test\vc6\cdynamic_test.exe:	.\cdynamic_test.exe
	copy $? $@ /y


..\bc56\test\$(COMP_IDENT)\cdynamic.dll:	.\cdynamic.dll
	copy $? $@ /y
..\cw8\test\\$(COMP_IDENT)\cdynamic.dll:	.\cdynamic.dll
	copy $? $@ /y
..\dmbeta\test\\$(COMP_IDENT)\cdynamic.dll:	.\cdynamic.dll
	copy $? $@ /y
..\gcc32\test\\$(COMP_IDENT)\cdynamic.dll:	.\cdynamic.dll
	copy $? $@ /y
..\icl7\test\\$(COMP_IDENT)\cdynamic.dll:	.\cdynamic.dll
	copy $? $@ /y
..\vc6\test\\$(COMP_IDENT)\cdynamic.dll:	.\cdynamic.dll
	copy $? $@ /y
