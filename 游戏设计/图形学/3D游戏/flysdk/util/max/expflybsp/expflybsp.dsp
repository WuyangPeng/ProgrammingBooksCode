# Microsoft Developer Studio Project File - Name="expflybsp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=expflybsp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "expflybsp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "expflybsp.mak" CFG="expflybsp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "expflybsp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "expflybsp - Win32 ReleaseMax3" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "expflybsp - Win32 ReleaseMax2" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "expflybsp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "\maxsdk3\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "MAX3" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 maxutil.lib core.lib dxguid.lib gdi32.lib comctl32.lib util.lib mesh.lib gfx.lib geom.lib user32.lib opengl32.lib opengl32.lib dxguid.lib dplayx.lib dinput.lib dsound.lib winmm.lib ole32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"\3DSMAX3\Plugins\expflybsp3.dle" /pdbtype:sept /libpath:"\maxsdk3\lib"
# SUBTRACT LINK32 /map

!ELSEIF  "$(CFG)" == "expflybsp - Win32 ReleaseMax3"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "expflybsp___Win32_ReleaseMax3"
# PROP BASE Intermediate_Dir "expflybsp___Win32_ReleaseMax3"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMax3"
# PROP Intermediate_Dir "ReleaseMax3"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "\maxsdk\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /W3 /GX /O2 /I "\maxsdk3\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "MAX3" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 maxutil.lib ddraw.lib glu32.lib core.lib dxguid.lib gdi32.lib comctl32.lib util.lib mesh.lib gfx.lib geom.lib user32.lib opengl32.lib dplayx.lib dinput.lib dsound.lib winmm.lib ole32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../../expflybsp3.dle" /libpath:"\maxsdk\lib"
# ADD LINK32 maxutil.lib ddraw.lib glu32.lib core.lib dxguid.lib gdi32.lib comctl32.lib util.lib mesh.lib gfx.lib geom.lib user32.lib opengl32.lib dplayx.lib dinput.lib dsound.lib winmm.lib ole32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../../expflybsp3.dle" /libpath:"\maxsdk3\lib"

!ELSEIF  "$(CFG)" == "expflybsp - Win32 ReleaseMax2"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "expflybsp___Win32_ReleaseMax2"
# PROP BASE Intermediate_Dir "expflybsp___Win32_ReleaseMax2"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMax2"
# PROP Intermediate_Dir "ReleaseMax2"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "\maxsdk\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /W3 /GX /O2 /I "\maxsdk2\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "MAX2" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=xilink6.exe
# ADD BASE LINK32 maxutil.lib ddraw.lib glu32.lib core.lib dxguid.lib gdi32.lib comctl32.lib util.lib mesh.lib gfx.lib geom.lib user32.lib opengl32.lib dplayx.lib dinput.lib dsound.lib winmm.lib ole32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../../expflybsp3.dle" /libpath:"\maxsdk\lib"
# ADD LINK32 ddraw.lib glu32.lib core.lib dxguid.lib gdi32.lib comctl32.lib util.lib mesh.lib gfx.lib geom.lib user32.lib opengl32.lib dplayx.lib dinput.lib dsound.lib winmm.lib ole32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../../expflybsp2.dle" /libpath:"\maxsdk2\lib"

!ENDIF 

# Begin Target

# Name "expflybsp - Win32 Debug"
# Name "expflybsp - Win32 ReleaseMax3"
# Name "expflybsp - Win32 ReleaseMax2"
# Begin Source File

SOURCE=.\enum_scene.cpp
# End Source File
# Begin Source File

SOURCE=.\enum_scene.h
# End Source File
# Begin Source File

SOURCE=.\expflybsp.cpp
# End Source File
# Begin Source File

SOURCE=.\expflybsp.def
# End Source File
# Begin Source File

SOURCE=.\expflybsp.h
# End Source File
# Begin Source File

SOURCE=.\expflybsp.rc
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\scene_max.cpp
# End Source File
# Begin Source File

SOURCE=.\scene_max.h
# End Source File
# Begin Source File

SOURCE=..\..\..\lib\Fly3D.lib
# End Source File
# End Target
# End Project
