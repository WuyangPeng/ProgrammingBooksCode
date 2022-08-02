#
# list5-8 mak
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
LLATC32_list5x8dexe =  -Tpe -ap -c -LD:\BC45\LIB
RLATC32_list5x8dexe =  -w32
BLATC32_list5x8dexe =
CNIEAT_list5x8dexe = -ID:\BC45\INCLUDE;C:\STL\INCLUDE; -D__BC401_STL
LNIEAT_list5x8dexe = -x
LEAT_list5x8dexe = $(LLATC32_list5x8dexe)
REAT_list5x8dexe = $(RLATC32_list5x8dexe)
BEAT_list5x8dexe = $(BLATC32_list5x8dexe)

#
# Dependency List
#
Dep_list5x8 = \
	list5-8.exe

list5-8 : BccW32.cfg $(Dep_list5x8)
  echo MakeNode

Dep_list5x8dexe = \
	genexc.obj\
	rational.obj\
	list5-8.obj

list5-8.exe : $(Dep_list5x8dexe)
  $(TLINK32) @&&|
 /v $(IDE_LFLAGS32) $(LEAT_list5x8dexe) $(LNIEAT_list5x8dexe) +
D:\BC45\LIB\c0x32.obj+
genexc.obj+
rational.obj+
list5-8.obj
$<,$*
D:\BC45\LIB\bidsf.lib+
D:\BC45\LIB\import32.lib+
D:\BC45\LIB\cw32mt.lib

|

genexc.obj :  genexc.cpp
  $(BCC32) -c @&&|
 $(CEAT_list5x8dexe) $(CNIEAT_list5x8dexe) -o$@ genexc.cpp
|

rational.obj :  rational.cpp
  $(BCC32) -c @&&|
 $(CEAT_list5x8dexe) $(CNIEAT_list5x8dexe) -o$@ rational.cpp
|

list5-8.obj :  list5-8.cpp
  $(BCC32) -c @&&|
 $(CEAT_list5x8dexe) $(CNIEAT_list5x8dexe) -o$@ list5-8.cpp
|

# Compiler configuration file
BccW32.cfg :
	Copy &&|
-R
-v
-vi
-H
-H=list5-8.csm
-WM
-WC
| $@


