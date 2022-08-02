#
# list6-2 mak
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
LLATC32_list6x2dexe =  -Tpe -ap -c
RLATC32_list6x2dexe =  -w32
BLATC32_list6x2dexe =
CNIEAT_list6x2dexe = -ID:\BC45\INCLUDE;C:\STL\INCLUDE -D__BC401_STL
LNIEAT_list6x2dexe = -x
LEAT_list6x2dexe = $(LLATC32_list6x2dexe)
REAT_list6x2dexe = $(RLATC32_list6x2dexe)
BEAT_list6x2dexe = $(BLATC32_list6x2dexe)

#
# Dependency List
#
Dep_list6x2 = \
	list6-2.exe

list6-2 : BccW32.cfg $(Dep_list6x2)
  echo MakeNode

Dep_list6x2dexe = \
	list6-2.obj

list6-2.exe : $(Dep_list6x2dexe)
  $(TLINK32) @&&|
 /v $(IDE_LFLAGS32) $(LEAT_list6x2dexe) $(LNIEAT_list6x2dexe) +
D:\BC45\LIB\c0x32.obj+
list6-2.obj
$<,$*
D:\BC45\LIB\bidsf.lib+
D:\BC45\LIB\import32.lib+
D:\BC45\LIB\cw32mt.lib

|

list6-2.obj :  list6-2.cpp
  $(BCC32) -c @&&|
 $(CEAT_list6x2dexe) $(CNIEAT_list6x2dexe) -o$@ list6-2.cpp
|

# Compiler configuration file
BccW32.cfg :
	Copy &&|
-R
-v
-vi
-H
-H=list6-2.csm
-v-
-R-
-H-
-WM
-WC
| $@


