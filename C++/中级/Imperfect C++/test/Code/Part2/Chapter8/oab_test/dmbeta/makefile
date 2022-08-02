# Updated: 28th November 2003

COMP_IDENT	=	dmbeta
CPPC		=	dmc
AR			=	dmc
LINK		=	dmc

INCLUDES	=	-I.. -I$(STLSOFT_INCLUDE) -I$(SYNESIS_DEV)\include

CPPC_ARGS	=	-c -WD $(INCLUDES)

LIB_ARGS	=	-WD

LINK_ARGS	=	

target:		\
			\
			.\oab_server.dll	\
			.\oab_client.exe	\
			\

targetx:	\
			\
			.\test\bc56\oab_client.exe	\
			.\test\cw8\oab_client.exe	\
			.\test\dmbeta\oab_client.exe	\
			.\test\gcc32\oab_client.exe	\
			.\test\icl7\oab_client.exe	\
			.\test\vc6\oab_client.exe	\
			\
			..\bc56\test\$(COMP_IDENT)\oab_server.dll	\
			..\cw8\test\\$(COMP_IDENT)\oab_server.dll	\
			..\dmbeta\test\\$(COMP_IDENT)\oab_server.dll	\
			..\gcc32\test\\$(COMP_IDENT)\oab_server.dll	\
			..\icl7\test\\$(COMP_IDENT)\oab_server.dll	\
			..\vc6\test\\$(COMP_IDENT)\oab_server.dll	\
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
	@.\oab_client.exe
	

.\oab_server.obj:	..\oab_server.cpp ..\oab.h
	$(CPPC) $(CPPC_ARGS) ..\oab_server.cpp -o$*.obj

.\oab_client.obj:	..\oab_client.cpp ..\oab.h
	$(CPPC) $(CPPC_ARGS) ..\oab_client.cpp -o$*.obj

.\oab_server.dll:	.\oab_server.obj
	if exist $@ del $@
	$(AR) $(LIB_ARGS) $@ .\oab_server.obj kernel32.lib

.\oab_server.lib:
	implib /system oab_server.lib oab_server.dll
#	implib oab_server.lib oab_server.dll
	
.\oab_client.exe:	.\oab_client.obj .\oab_server.lib
	$(LINK) -o $@ $(LINK_ARGS) $**


.\test\bc56\oab_client.exe:	.\oab_client.exe
	copy $? $@ /y
.\test\cw8\oab_client.exe:	.\oab_client.exe
	copy $? $@ /y
.\test\dmbeta\oab_client.exe:	.\oab_client.exe
	copy $? $@ /y
.\test\gcc32\oab_client.exe:	.\oab_client.exe
	copy $? $@ /y
.\test\icl7\oab_client.exe:	.\oab_client.exe
	copy $? $@ /y
.\test\vc6\oab_client.exe:	.\oab_client.exe
	copy $? $@ /y


..\bc56\test\$(COMP_IDENT)\oab_server.dll:	.\oab_server.dll
	copy $? $@ /y
..\cw8\test\\$(COMP_IDENT)\oab_server.dll:	.\oab_server.dll
	copy $? $@ /y
..\dmbeta\test\\$(COMP_IDENT)\oab_server.dll:	.\oab_server.dll
	copy $? $@ /y
..\gcc32\test\\$(COMP_IDENT)\oab_server.dll:	.\oab_server.dll
	copy $? $@ /y
..\icl7\test\\$(COMP_IDENT)\oab_server.dll:	.\oab_server.dll
	copy $? $@ /y
..\vc6\test\\$(COMP_IDENT)\oab_server.dll:	.\oab_server.dll
	copy $? $@ /y
