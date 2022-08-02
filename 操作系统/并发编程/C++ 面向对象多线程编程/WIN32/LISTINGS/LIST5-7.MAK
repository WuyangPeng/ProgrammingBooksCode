#
# list5-7 mak
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
LLATC32_list5x7dexe =  -Tpe -ap -c
RLATC32_list5x7dexe =  -w32
BLATC32_list5x7dexe =
CNIEAT_list5x7dexe = -ID:\BC45\INCLUDE -D
LNIEAT_list5x7dexe = -x
LEAT_list5x7dexe = $(LLATC32_list5x7dexe)
REAT_list5x7dexe = $(RLATC32_list5x7dexe)
BEAT_list5x7dexe = $(BLATC32_list5x7dexe)

#
# Dependency List
#
Dep_list5x7 = \
	list5-7.exe

list5-7 : BccW32.cfg $(Dep_list5x7)
  echo MakeNode

Dep_list5x7dexe = \
	list5-7.obj

list5-7.exe : $(Dep_list5x7dexe)
  $(TLINK32) @&&|
 /v $(IDE_LFLAGS32) $(LEAT_list5x7dexe) $(LNIEAT_list5x7dexe) +
D:\BC45\LIB\c0x32.obj+
list5-7.obj
$<,$*
D:\BC45\LIB\bidsf.lib+
D:\BC45\LIB\import32.lib+
D:\BC45\LIB\cw32mt.lib

|

list5-7.obj :  list5-7.cpp
  $(BCC32) -c @&&|
 $(CEAT_list5x7dexe) $(CNIEAT_list5x7dexe) -o$@ list5-7.cpp
|

# Compiler configuration file
BccW32.cfg :
	Copy &&|
-R
-v
-vi
-H
-H=list5-7.csm
-WM
-WC
-v-
-R-
| $@


