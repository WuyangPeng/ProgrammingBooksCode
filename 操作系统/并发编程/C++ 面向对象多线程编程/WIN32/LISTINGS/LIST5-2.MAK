#
# list5-2 mak
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
LLATC32_list5x2dexe =  -Tpe -ap -c
RLATC32_list5x2dexe =  -w32
BLATC32_list5x2dexe = 
CNIEAT_list5x2dexe = -ID:\BC45\INCLUDE -D
LNIEAT_list5x2dexe = -x
LEAT_list5x2dexe = $(LLATC32_list5x2dexe)
REAT_list5x2dexe = $(RLATC32_list5x2dexe)
BEAT_list5x2dexe = $(BLATC32_list5x2dexe)

#
# Dependency List
#
Dep_list5x2 = \
	list5-2.exe

list5-2 : BccW32.cfg $(Dep_list5x2)
  echo MakeNode

Dep_list5x2dexe = \
	list5-2.obj

list5-2.exe : $(Dep_list5x2dexe)
  $(TLINK32) @&&|
 /v $(IDE_LFLAGS32) $(LEAT_list5x2dexe) $(LNIEAT_list5x2dexe) +
D:\BC45\LIB\c0x32.obj+
list5-2.obj
$<,$*
D:\BC45\LIB\bidsf.lib+
D:\BC45\LIB\import32.lib+
D:\BC45\LIB\cw32mt.lib

|

list5-2.obj :  list5-2.cpp
  $(BCC32) -c @&&|
 $(CEAT_list5x2dexe) $(CNIEAT_list5x2dexe) -o$@ list5-2.cpp
|

# Compiler configuration file
BccW32.cfg :
	Copy &&|
-R
-v
-vi
-H
-H=list5-2.csm
-WM
-WC
| $@


