#
# List5-1.mak
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
LLATC32_list5x1dexe =  -Tpe -ap -c
RLATC32_list5x1dexe =  -w32
BLATC32_list5x1dexe =
CNIEAT_list5x1dexe = -ID:\BC45\INCLUDE -D
LNIEAT_list5x1dexe = -x
LEAT_list5x1dexe = $(LLATC32_list5x1dexe)
REAT_list5x1dexe = $(RLATC32_list5x1dexe)
BEAT_list5x1dexe = $(BLATC32_list5x1dexe)

#
# Dependency List
#
Dep_list5x1 = \
	list5-1.exe

list5-1 : BccW32.cfg $(Dep_list5x1)
  echo MakeNode

Dep_list5x1dexe = \
	ctmutex.obj\
	rational.obj\
	mtration.obj\
	genexc.obj\
	list5-1.obj

list5-1.exe : $(Dep_list5x1dexe)
  $(TLINK32) @&&|
 /v $(IDE_LFLAGS32) $(LEAT_list5x1dexe) $(LNIEAT_list5x1dexe) +
D:\BC45\LIB\c0x32.obj+
ctmutex.obj+
rational.obj+
mtration.obj+
genexc.obj+
list5-1.obj
$<,$*
D:\BC45\LIB\bidsf.lib+
D:\BC45\LIB\import32.lib+
D:\BC45\LIB\cw32mt.lib

|

ctmutex.obj :  ctmutex.cpp
  $(BCC32) -c @&&|
 $(CEAT_list5x1dexe) $(CNIEAT_list5x1dexe) -o$@ ctmutex.cpp
|

rational.obj :  rational.cpp
  $(BCC32) -c @&&|
 $(CEAT_list5x1dexe) $(CNIEAT_list5x1dexe) -o$@ rational.cpp
|

mtration.obj :  mtration.cpp
  $(BCC32) -c @&&|
 $(CEAT_list5x1dexe) $(CNIEAT_list5x1dexe) -o$@ mtration.cpp
|

genexc.obj :  genexc.cpp
  $(BCC32) -c @&&|
 $(CEAT_list5x1dexe) $(CNIEAT_list5x1dexe) -o$@ genexc.cpp
|

list5-1.obj :  list5-1.cpp
  $(BCC32) -c @&&|
 $(CEAT_list5x1dexe) $(CNIEAT_list5x1dexe) -o$@ list5-1.cpp
|

# Compiler configuration file
BccW32.cfg :
	Copy &&|
-R
-v
-vi
-H
-H=list5-1.csm
-WM
-WC
-v-
-R-
| $@


