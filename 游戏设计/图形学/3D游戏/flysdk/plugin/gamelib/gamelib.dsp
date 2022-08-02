# Microsoft Developer Studio Project File - Name="gamelib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=gamelib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gamelib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gamelib.mak" CFG="gamelib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gamelib - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "gamelib - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gamelib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GAMELIB_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GAMELIB_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 winspool.lib advapi32.lib shell32.lib oleaut32.lib odbc32.lib odbccp32.lib dxguid.lib dsound.lib dinput.lib dplay.lib opengl32.lib glu32.lib winmm.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib ole32.lib uuid.lib /nologo /dll /machine:I386 /out:"../gamelib.dll"

!ELSEIF  "$(CFG)" == "gamelib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "gamelib___Win32_Debug"
# PROP BASE Intermediate_Dir "gamelib___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GAMELIB_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "GAMELIB_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dxguid.lib dsound.lib dinput.lib dplay.lib opengl32.lib glu32.lib winmm.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib /nologo /dll /debug /machine:I386 /out:"../gamelib.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "gamelib - Win32 Release"
# Name "gamelib - Win32 Debug"
# Begin Source File

SOURCE=.\cartoon_mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\cartoon_mesh.h
# End Source File
# Begin Source File

SOURCE=.\color_particle.cpp
# End Source File
# Begin Source File

SOURCE=.\color_particle.h
# End Source File
# Begin Source File

SOURCE=.\dpblend_sphere.cpp
# End Source File
# Begin Source File

SOURCE=.\dpblend_sphere.h
# End Source File
# Begin Source File

SOURCE=.\exp_sphere.cpp
# End Source File
# Begin Source File

SOURCE=.\exp_sphere.h
# End Source File
# Begin Source File

SOURCE=.\explode.cpp
# End Source File
# Begin Source File

SOURCE=.\explode.h
# End Source File
# Begin Source File

SOURCE=.\fao_mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\fao_mesh.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\Fly3D.h
# End Source File
# Begin Source File

SOURCE=.\gamelib.cpp
# End Source File
# Begin Source File

SOURCE=.\gamelib.def
# End Source File
# Begin Source File

SOURCE=.\gamelib.h
# End Source File
# Begin Source File

SOURCE=.\ps.cpp
# End Source File
# Begin Source File

SOURCE=.\ps.h
# End Source File
# Begin Source File

SOURCE=.\shadow.cpp
# End Source File
# Begin Source File

SOURCE=.\shadow.h
# End Source File
# Begin Source File

SOURCE=.\sound.cpp
# End Source File
# Begin Source File

SOURCE=.\sound.h
# End Source File
# Begin Source File

SOURCE=.\subdiv_mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\subdiv_mesh.h
# End Source File
# Begin Source File

SOURCE=..\..\lib\Fly3D.lib
# End Source File
# End Target
# End Project
