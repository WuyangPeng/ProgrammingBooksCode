# Updated: 29th November 2003

COMP_IDENT	=	bc56
CPPC		=	bcc32
AR			=	bcc32
LINK		=	bcc32

INCLUDES	=	-I.. -I$(STLSOFT_INCLUDE) -I$(SYNESIS_DEV)\include

CPPC_ARGS	=	-c -q $(INCLUDES) -D_DEBUG -v #-DNDEBUG

LIB_ARGS	=	-q -WD -lGi

LINK_ARGS	=	-q

target:		\
			\
			.\oab_server.dll	\
			.\oab_client.exe	\
			\

targetx:	\
			\
			..\bc56\test\$(COMP_IDENT)\oab_server.dll	\
			..\cw8\test\\$(COMP_IDENT)\oab_server.dll	\
			..\dmbeta\test\\$(COMP_IDENT)\oab_server.dll	\
			..\gcc32\test\\$(COMP_IDENT)\oab_server.dll	\
			..\icl7\test\\$(COMP_IDENT)\oab_server.dll	\
			..\vc6\test\\$(COMP_IDENT)\oab_server.dll	\
			\
			.\test\bc56\oab_client.exe	\
			.\test\cw8\oab_client.exe	\
			.\test\dmbeta\oab_client.exe	\
			.\test\gcc32\oab_client.exe	\
			.\test\icl7\oab_client.exe	\
			.\test\vc6\oab_client.exe	\
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
	$(CPPC) -WD $(CPPC_ARGS) ..\oab_server.cpp -o$*.obj

.\oab_client.obj:	..\oab_client.cpp ..\oab.h
	$(CPPC) $(CPPC_ARGS) ..\oab_client.cpp -o$*.obj

.\oab_server.dll:	.\oab_server.obj
	if exist $@ del $@
	$(AR) -e$@ $(LIB_ARGS) .\oab_server.obj

.\oab_client.exe:	.\oab_client.obj .\oab_server.lib
	$(LINK) -e$@ $(LINK_ARGS) $**



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


.\test\bc56\oab_client.exe:	.\oab_client.exe
	copy $? $@ /y

.\test\cw8\oab_server.def:	.\test\cw8\oab_server.dll
	impdef -a $@ $**
.\test\cw8\oab_server.lib:	.\test\cw8\oab_server.def
	implib $@ $**
.\test\cw8\oab_client.exe:	.\oab_client.obj .\test\cw8\oab_server.lib
	$(LINK) -e$@ $(LINK_ARGS) $**

.\test\dmbeta\oab_server.def:	.\test\dmbeta\oab_server.dll
	impdef -a $@ $**
.\test\dmbeta\oab_server.lib:	.\test\dmbeta\oab_server.def
	implib $@ $**
.\test\dmbeta\oab_client.exe:	.\oab_client.obj .\test\dmbeta\oab_server.lib
	$(LINK) -e$@ $(LINK_ARGS) $**

.\test\gcc32\oab_server.def:	.\test\gcc32\oab_server.dll
	impdef -a $@ $**
.\test\gcc32\oab_server.lib:	.\test\gcc32\oab_server.def
	implib $@ $**
.\test\gcc32\oab_client.exe:	.\oab_client.obj .\test\gcc32\oab_server.lib
	$(LINK) -e$@ $(LINK_ARGS) $**

.\test\icl7\oab_server.def:	.\test\icl7\oab_server.dll
	impdef -a $@ $**
.\test\icl7\oab_server.lib:	.\test\icl7\oab_server.def
	implib $@ $**
.\test\icl7\oab_client.exe:	.\oab_client.obj .\test\icl7\oab_server.lib
	$(LINK) -e$@ $(LINK_ARGS) $**

.\test\vc6\oab_server.def:	.\test\vc6\oab_server.dll
	impdef -a $@ $**
.\test\vc6\oab_server.lib:	.\test\vc6\oab_server.def
	implib $@ $**
.\test\vc6\oab_client.exe:	.\oab_client.obj .\test\vc6\oab_server.lib
	$(LINK) -e$@ $(LINK_ARGS) $**

