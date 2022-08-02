#
# list5-9 mak
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
LLATC32_list5x9dexe =  -Tpe -ap -c
RLATC32_list5x9dexe =  -w32
BLATC32_list5x9dexe =
CNIEAT_list5x9dexe = -ID:\BC45\INCLUDE -D
LNIEAT_list5x9dexe = -x
LEAT_list5x9dexe = $(LLATC32_list5x9dexe)
REAT_list5x9dexe = $(RLATC32_list5x9dexe)
BEAT_list5x9dexe = $(BLATC32_list5x9dexe)

#
# Dependency List
#
Dep_list5x9 = \
	list5-9.exe

list5-9 : BccW32.cfg $(Dep_list5x9)
  echo MakeNode

Dep_list5x9dexe = \
	genexc.obj\
	rational.obj\
	list5-9.obj

list5-9.exe : $(Dep_list5x9dexe)
  $(TLINK32) @&&|
 /v $(IDE_LFLAGS32) $(LEAT_list5x9dexe) $(LNIEAT_list5x9dexe) +
D:\BC45\LIB\c0x32.obj+
genexc.obj+
rational.obj+
list5-9.obj
$<,$*
D:\BC45\LIB\bidsf.lib+
D:\BC45\LIB\import32.lib+
D:\BC45\LIB\cw32mt.lib

|

genexc.obj :  genexc.cpp
  $(BCC32) -c @&&|
 $(CEAT_list5x9dexe) $(CNIEAT_list5x9dexe) -o$@ genexc.cpp
|

rational.obj :  rational.cpp
  $(BCC32) -c @&&|
 $(CEAT_list5x9dexe) $(CNIEAT_list5x9dexe) -o$@ rational.cpp
|

list5-9.obj :  list5-9.cpp
  $(BCC32) -c @&&|
 $(CEAT_list5x9dexe) $(CNIEAT_list5x9dexe) -o$@ list5-9.cpp
|

# Compiler configuration file
BccW32.cfg :
	Copy &&|
-R
-v
-vi
-H
-H=list5-9.csm
-WM
-WC
-v-
-R-
| $@


