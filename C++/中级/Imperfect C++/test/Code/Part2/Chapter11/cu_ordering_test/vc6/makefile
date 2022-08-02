

CPPC					=	cl
LINK					=	link

CPPC_F_OPT_SPEED		=	-O2 -Ox
CPPC_F_NOLOGO			=	
CPPC_F_EXCEPTIONS_ON	=	-EHsc
CPPC_F_EXCEPTIONS_OFF	=	

CPPC_FLAGS				=	-c $(CPPC_F_OPT_SPEED) $(CPPC_F_NOLOGO)

CPPC_NAMED_TARGET_OBJ	=	-Fo$*.obj

STLSOFT_INCLUDE			=	$(STLSOFT_INCLUDE)

INCLUDES				=	-I$(STLSOFT_INCLUDE)



target:		\
			\
			cu_ordering_test.exe		\
			\

.cpp.obj:
	$(CPPC) $(CPPC_FLAGS) $(CPPC_F_EXCEPTIONS_OFF) $(INCLUDES) -DUSE_OWN_STRING -o$*.obj $?

clean:
	@-if exist *.exe del *.exe
	@-if exist *.obj del *.obj
	@-if exist *.map del *.map

run:
	@cu_ordering_test.exe


cu_ordering_test.obj:	..\cu_ordering_test.cpp
	$(CPPC) $(CPPC_FLAGS) $(CPPC_F_EXCEPTIONS_OFF) $(INCLUDES) -DUSE_OWN_STRING $(CPPC_NAMED_TARGET_OBJ) $?

cu_ordering_test_2.obj:	..\cu_ordering_test_2.cpp
	$(CPPC) $(CPPC_FLAGS) $(CPPC_F_EXCEPTIONS_OFF) $(INCLUDES) -DUSE_OWN_STRING $(CPPC_NAMED_TARGET_OBJ) $?

cu_ordering_test.exe:	cu_ordering_test.obj cu_ordering_test_2.obj makefile
	$(LINK) -out:$@ cu_ordering_test.obj cu_ordering_test_2.obj 
