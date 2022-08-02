# Updated: 28th November 2003

COMP_IDENT	=	wc12
CPPC		=	wpp386
AR			=	wcl386
LINK		=	wcl386

INCLUDES	=	-I.. -I$(STLSOFT_INCLUDE) -I$(SYNESIS_DEV)\include

CPPC_ARGS	=	-zq $(INCLUDES)

LIB_ARGS	=	-zq 

LINK_ARGS	=	-zq

target:		\
			\
			.\cppdynamic.dll	\
			.\cppdynamic_test.exe	\
			\

targetx:	\
			\
			.\test\bc56\cppdynamic_test.exe	\
			.\test\cw8\cppdynamic_test.exe	\
			.\test\dmbeta\cppdynamic_test.exe	\
			.\test\gcc32\cppdynamic_test.exe	\
			.\test\icl7\cppdynamic_test.exe	\
			.\test\vc6\cppdynamic_test.exe	\
			\
			..\bc56\test\$(COMP_IDENT)\cppdynamic.dll	\
			..\cw8\test\\$(COMP_IDENT)\cppdynamic.dll	\
			..\dmbeta\test\\$(COMP_IDENT)\cppdynamic.dll	\
			..\gcc32\test\\$(COMP_IDENT)\cppdynamic.dll	\
			..\icl7\test\\$(COMP_IDENT)\cppdynamic.dll	\
			..\vc6\test\\$(COMP_IDENT)\cppdynamic.dll	\
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
	@.\cppdynamic_test.exe
	

.\cppdynamic.obj:	..\cppdynamic.cpp ..\cppdynamic.h
	$(CPPC) -bd $(CPPC_ARGS) ..\cppdynamic.cpp -fo=$*.obj

.\cppdynamic_test.obj:	..\cppdynamic_test.cpp ..\cppdynamic.h
	$(CPPC) $(CPPC_ARGS) ..\cppdynamic_test.cpp -fo=$*.obj

.\cppdynamic.dll:	.\cppdynamic.obj
	$(AR) -bd $(LIB_ARGS) -fe=$@ .\cppdynamic.obj
	wlib -b -c -n -p=512 -q cppdynamic.lib +cppdynamic.dll
	
.\cppdynamic_test.exe:	.\cppdynamic_test.obj .\cppdynamic.lib
	$(LINK) -bc -fe=$@ $(LINK_ARGS) $**


.\test\bc56\cppdynamic_test.exe:	.\cppdynamic_test.exe
	copy $? $@ /y
.\test\cw8\cppdynamic_test.exe:	.\cppdynamic_test.exe
	copy $? $@ /y
.\test\dmbeta\cppdynamic_test.exe:	.\cppdynamic_test.exe
	copy $? $@ /y
.\test\gcc32\cppdynamic_test.exe:	.\cppdynamic_test.exe
	copy $? $@ /y
.\test\icl7\cppdynamic_test.exe:	.\cppdynamic_test.exe
	copy $? $@ /y
.\test\vc6\cppdynamic_test.exe:	.\cppdynamic_test.exe
	copy $? $@ /y


..\bc56\test\$(COMP_IDENT)\cppdynamic.dll:	.\cppdynamic.dll
	copy $? $@ /y
..\cw8\test\\$(COMP_IDENT)\cppdynamic.dll:	.\cppdynamic.dll
	copy $? $@ /y
..\dmbeta\test\\$(COMP_IDENT)\cppdynamic.dll:	.\cppdynamic.dll
	copy $? $@ /y
..\gcc32\test\\$(COMP_IDENT)\cppdynamic.dll:	.\cppdynamic.dll
	copy $? $@ /y
..\icl7\test\\$(COMP_IDENT)\cppdynamic.dll:	.\cppdynamic.dll
	copy $? $@ /y
..\vc6\test\\$(COMP_IDENT)\cppdynamic.dll:	.\cppdynamic.dll
	copy $? $@ /y
