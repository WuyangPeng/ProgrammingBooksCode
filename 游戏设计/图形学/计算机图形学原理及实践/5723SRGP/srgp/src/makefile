.AUTODEPEND

#		*Translator Definitions*
CC = bcc +SRGP.CFG
TASM = TASM
TLIB = tlib
TLINK = tlink
LIBPATH = C:\BIN\BORLANDC\LIB;.
INCLUDEPATH = C:\BIN\BORLANDC\INCLUDE;.


#		*Implicit Rules*
.c.obj:
  $(CC) -c {$< }

.cpp.obj:
  $(CC) -c {$< }

#		*List Macros*
Link_Exclude =  \
 srgp.res

Link_Include =  \
 srgp.def \
 attrib.obj \
 canvas.obj \
 color_wi.obj \
 cursor.obj \
 echo_win.obj \
 error.obj \
 input.obj \
 input_wi.obj \
 inquire.obj \
 font.obj \
 mem.obj \
 output.obj \
 state.obj \
 state_wi.obj \
 raster.obj

#		*Explicit Rules*

winsrgp.lib: srgp.cfg $(Link_Include)
	$(TLIB) winsrgp.lib @&&|
-+attrib 	-+canvas 	-+color_wi 	-+cursor &
-+echo_win	-+error		-+input		-+input_wi &
-+inquire	-+font		-+mem		-+output &
-+state		-+state_wi	-+raster
|

example: example.obj winsrgp.lib $(Link_Exclude)
  $(TLINK) /v/x/c/P-/Twe/L$(LIBPATH) @&&|
c0wl.obj+
example.obj
example
		# no map file
winsrgp.lib+
mathwl.lib+
import.lib+
cwl.lib
srgp.def
|
  RC  srgp.res example.exe


#		*Individual File Dependencies*

#srgp.res: srgp.cfg srgp.rc 
#	RC -R -I$(INCLUDEPATH) -FO srgp.res SRGP.RC

#		*Compiler Configuration File*
srgp.cfg:
  copy &&|
-R
-ml!
-2
-v
-G
-O
-Og
-Oe
-Om
-Ov
-Ol
-Op
-Oi
-Z
-d
-W
-vi-
-w-par
-wpro
-weas
-wpre
-w-rpt
-w-pia
-I$(INCLUDEPATH)
-L$(LIBPATH)
-DIBM_PC
-P-.C
| srgp.cfg
