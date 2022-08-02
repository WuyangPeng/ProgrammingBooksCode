#
# list8-1 mak
#
.AUTODEPEND


#
#
#
IMPLIB  = Implib
BCC32   = Bcc32 +BccW32.cfg
TLINK32 = TLink32
TLIB    = TLib
BRC32   = Brc32
TASM32  = Tasm32
#
# IDE macros
#


#
# Options
#
IDE_LFLAGS32 =  -LD:\BC45\LIB
LLATC32_list8x1dexe =  -Tpe -ap -c
RLATC32_list8x1dexe =  -w32
BLATC32_list8x1dexe =
CNIEAT_list8x1dexe = -ID:\BC45\INCLUDE;C:\STL\INCLUDE -D_RTLDLL;_BIDSDLL;
LNIEAT_list8x1dexe = -x
LEAT_list8x1dexe = $(LLATC32_list8x1dexe)
REAT_list8x1dexe = $(RLATC32_list8x1dexe)
BEAT_list8x1dexe = $(BLATC32_list8x1dexe)

#
# Dependency List
#
Dep_list8x1 = \
	list8-1.exe

list8-1 : BccW32.cfg $(Dep_list8x1)
  echo MakeNode

Dep_list8x1dexe = \
	rational.obj\
	mtration.obj\
	genexc.obj\
	ctmutex.obj\
	list8-1.obj

list8-1.exe : $(Dep_list8x1dexe)
  $(TLINK32) @&&|
 /v $(IDE_LFLAGS32) $(LEAT_list8x1dexe) $(LNIEAT_list8x1dexe) +
D:\BC45\LIB\c0x32.obj+
rational.obj+
mtration.obj+
genexc.obj+
ctmutex.obj+
list8-1.obj
$<,$*
D:\BC45\LIB\bidsfi.lib+
D:\BC45\LIB\import32.lib+
D:\BC45\LIB\cw32mti.lib

|

rational.obj :  rational.cpp
  $(BCC32) -c @&&|
 $(CEAT_list8x1dexe) $(CNIEAT_list8x1dexe) -o$@ rational.cpp
|

mtration.obj :  mtration.cpp
  $(BCC32) -c @&&|
 $(CEAT_list8x1dexe) $(CNIEAT_list8x1dexe) -o$@ mtration.cpp
|

genexc.obj :  genexc.cpp
  $(BCC32) -c @&&|
 $(CEAT_list8x1dexe) $(CNIEAT_list8x1dexe) -o$@ genexc.cpp
|

ctmutex.obj :  ctmutex.cpp
  $(BCC32) -c @&&|
 $(CEAT_list8x1dexe) $(CNIEAT_list8x1dexe) -o$@ ctmutex.cpp
|

list8-1.obj :  list8-1.cpp
  $(BCC32) -c @&&|
 $(CEAT_list8x1dexe) $(CNIEAT_list8x1dexe) -o$@ list8-1.cpp
|

# Compiler configuration file
BccW32.cfg :
	Copy &&|
-R
-v
-vi
-H
-H=list8-1.csm
-WM
-WC
-H-
-v-
-R-
| $@


