
CPPC		=	bcc32
CC			=	bcc32
AR			=	tlib
LN			=	bcc32

CPPC_FLAGS	=	-q -c
CC_FLAGS	=	-q -c
LN_FLAGS	=	-q

INCLUDES	=	-I..


target:		\
			static_interdep_test.exe	\
			\


static_interdep_test.obj: ..\static_interdep_test.cpp ..\stat_interdep.h
	$(CPPC) $(CPPC_FLAGS) $(INCLUDES) -o $@ ..\static_interdep_test.cpp

stat_interdep_1.obj: ..\stat_interdep_1.c ..\stat_interdep.h
	$(CC) $(CPPC_FLAGS) $(INCLUDES) -o $@ ..\stat_interdep_1.c

stat_interdep_2.obj: ..\stat_interdep_2.c ..\stat_interdep.h
	$(CC) $(CPPC_FLAGS) $(INCLUDES) -o $@ ..\stat_interdep_2.c

static_interdep_1.lib: stat_interdep_1.obj
	$(AR) $@ +$**

static_interdep_2.lib: stat_interdep_2.obj
	$(AR) $@ +$**


static_interdep_test.exe: static_interdep_test.obj static_interdep_1.lib static_interdep_2.lib
	$(LN) -e$@ $**