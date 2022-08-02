# Microsoft Developer Studio Generated NMAKE File, Based on hover.dsp
!IF "$(CFG)" == ""
CFG=hover - Win32 Debug
!MESSAGE No configuration specified. Defaulting to hover - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "hover - Win32 Release" && "$(CFG)" != "hover - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "hover.mak" CFG="hover - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "hover - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "hover - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "hover - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\hover.exe"

!ELSE 

ALL : "$(OUTDIR)\hover.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\d3dstuff.obj"
	-@erase "$(INTDIR)\physics.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\winmain.obj"
	-@erase "$(OUTDIR)\hover.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\hover.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\hover.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\hover.pdb" /machine:I386 /out:"$(OUTDIR)\hover.exe" 
LINK32_OBJS= \
	"$(INTDIR)\d3dstuff.obj" \
	"$(INTDIR)\physics.obj" \
	"$(INTDIR)\winmain.obj" \
	"..\..\Vc\lib\D3drm.lib" \
	"..\..\Vc\lib\Ddraw.lib" \
	"..\..\Vc\lib\Gdi32.lib" \
	"..\..\Vc\lib\User32.lib" \
	"..\..\Vc\lib\Winmm.lib"

"$(OUTDIR)\hover.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "hover - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\hover.exe"

!ELSE 

ALL : "$(OUTDIR)\hover.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\d3dstuff.obj"
	-@erase "$(INTDIR)\physics.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\winmain.obj"
	-@erase "$(OUTDIR)\hover.exe"
	-@erase "$(OUTDIR)\hover.ilk"
	-@erase "$(OUTDIR)\hover.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\hover.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\hover.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\hover.pdb" /debug /machine:I386 /out:"$(OUTDIR)\hover.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\d3dstuff.obj" \
	"$(INTDIR)\physics.obj" \
	"$(INTDIR)\winmain.obj" \
	"..\..\Vc\lib\D3drm.lib" \
	"..\..\Vc\lib\Ddraw.lib" \
	"..\..\Vc\lib\Gdi32.lib" \
	"..\..\Vc\lib\User32.lib" \
	"..\..\Vc\lib\Winmm.lib"

"$(OUTDIR)\hover.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "hover - Win32 Release" || "$(CFG)" == "hover - Win32 Debug"
SOURCE=.\d3dstuff.cpp
DEP_CPP_D3DST=\
	".\d3dstuff.h"\
	".\mymath.h"\
	

"$(INTDIR)\d3dstuff.obj" : $(SOURCE) $(DEP_CPP_D3DST) "$(INTDIR)"


SOURCE=.\physics.cpp
DEP_CPP_PHYSI=\
	".\mymath.h"\
	".\physics.h"\
	

"$(INTDIR)\physics.obj" : $(SOURCE) $(DEP_CPP_PHYSI) "$(INTDIR)"


SOURCE=.\winmain.cpp
DEP_CPP_WINMA=\
	".\d3dstuff.h"\
	".\mymath.h"\
	".\physics.h"\
	

"$(INTDIR)\winmain.obj" : $(SOURCE) $(DEP_CPP_WINMA) "$(INTDIR)"



!ENDIF 

