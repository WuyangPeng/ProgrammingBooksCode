

CPPC					=	wpp386
LINK					=	wcl386

CPPC_F_OPT_SPEED		=	-oxt
CPPC_F_NOLOGO			=	
CPPC_F_EXCEPTIONS_ON	=	
CPPC_F_EXCEPTIONS_OFF	=	

CPPC_FLAGS				=	$(CPPC_F_OPT_SPEED) $(CPPC_F_NOLOGO)

CPPC_NAMED_TARGET_OBJ	=	-fo$*.obj

STLSOFT_INCLUDE			=	$(STLSOFT_INCLUDE)

INCLUDES				=	-I$(STLSOFT_INCLUDE)



target:		\
			\
			inter_cu_ordering_test.exe		\
			\

.cpp.obj:
	$(CPPC) $(CPPC_FLAGS) $(CPPC_F_EXCEPTIONS_OFF) $(INCLUDES) -DUSE_OWN_STRING -o$*.obj $?

clean:
	@-if exist *.exe del *.exe
	@-if exist *.obj del *.obj
	@-if exist *.map del *.map

run:
	@inter_cu_ordering_test.exe


inter_cu_ordering_test.obj:	..\inter_cu_ordering_test.cpp
	$(CPPC) $(CPPC_FLAGS) $(CPPC_F_EXCEPTIONS_OFF) $(INCLUDES) -DUSE_OWN_STRING $(CPPC_NAMED_TARGET_OBJ) $?

object2.obj:	..\object2.cpp
	$(CPPC) $(CPPC_FLAGS) $(CPPC_F_EXCEPTIONS_OFF) $(INCLUDES) -DUSE_OWN_STRING $(CPPC_NAMED_TARGET_OBJ) $?

object3.obj:	..\object3.cpp
	$(CPPC) $(CPPC_FLAGS) $(CPPC_F_EXCEPTIONS_OFF) $(INCLUDES) -DUSE_OWN_STRING $(CPPC_NAMED_TARGET_OBJ) $?

inter_cu_ordering_test.exe:	inter_cu_ordering_test.obj object2.obj object3.obj makefile
	$(LINK) inter_cu_ordering_test.obj object2.obj object3.obj
