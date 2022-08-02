#
# list8-3 mak
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
LLATC32_list8x3dexe =  -Tpe -ap -c
RLATC32_list8x3dexe =  -w32
BLATC32_list8x3dexe =
CNIEAT_list8x3dexe = -ID:\BC45\INCLUDE;C:\STL\INCLUDE -D__BC401_STL
LNIEAT_list8x3dexe = -x
LEAT_list8x3dexe = $(LLATC32_list8x3dexe)
REAT_list8x3dexe = $(RLATC32_list8x3dexe)
BEAT_list8x3dexe = $(BLATC32_list8x3dexe)

#
# Dependency List
#
Dep_list8x3 = \
	list8-3.exe

list8-3 : BccW32.cfg $(Dep_list8x3)
  echo MakeNode

Dep_list8x3dexe = \
	genexc.obj\
	ctmutex.obj\
	ctevent.obj\
	ctqueue.obj\
	list8-3.obj

list8-3.exe : $(Dep_list8x3dexe)
  $(TLINK32) @&&|
 /v $(IDE_LFLAGS32) $(LEAT_list8x3dexe) $(LNIEAT_list8x3dexe) +
D:\BC45\LIB\c0x32.obj+
genexc.obj+
ctmutex.obj+
ctevent.obj+
ctqueue.obj+
list8-3.obj
$<,$*
D:\BC45\LIB\bidsf.lib+
D:\BC45\LIB\import32.lib+
D:\BC45\LIB\cw32.lib

|

genexc.obj :  genexc.cpp
  $(BCC32) -c @&&|
 $(CEAT_list8x3dexe) $(CNIEAT_list8x3dexe) -o$@ genexc.cpp
|

ctmutex.obj :  ctmutex.cpp
  $(BCC32) -c @&&|
 $(CEAT_list8x3dexe) $(CNIEAT_list8x3dexe) -o$@ ctmutex.cpp
|

ctevent.obj :  ctevent.cpp
  $(BCC32) -c @&&|
 $(CEAT_list8x3dexe) $(CNIEAT_list8x3dexe) -o$@ ctevent.cpp
|

ctqueue.obj :  ctqueue.cpp
  $(BCC32) -c @&&|
 $(CEAT_list8x3dexe) $(CNIEAT_list8x3dexe) -o$@ ctqueue.cpp
|

list8-3.obj :  list8-3.cpp
  $(BCC32) -c @&&|
 $(CEAT_list8x3dexe) $(CNIEAT_list8x3dexe) -o$@ list8-3.cpp
|

# Compiler configuration file
BccW32.cfg :
	Copy &&|
-R
-v
-vi
-H
-H=list8-3.csm
-WC
-v-
-R-
-H-
| $@


