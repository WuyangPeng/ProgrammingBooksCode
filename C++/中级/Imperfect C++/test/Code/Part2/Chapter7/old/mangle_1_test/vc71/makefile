
CPPC			=	cl
LINK			=	link
LIB				=	lib

CPPC_FLAGS		=	-c

INCLUDES		=	-I..

target:			\
				cmangle_vc71.lib	\
				mangle_vc71.lib	\
				\

clean:
	@-if exist *.obj del *.obj
	@-if exist *.exe del *.exe
	@-if exist *.lib del *.lib

cmangle.obj:	..\cmangle.c
	$(CPPC) $(CPPC_FLAGS) $(INCLUDES) ..\cmangle.c

cmangle_vc71.lib:	cmangle.obj
	$(LIB) $** -out:$@

