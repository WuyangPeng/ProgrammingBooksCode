# Microsoft Developer Studio Project File - Name="Fly3D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Fly3D - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Fly3D.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Fly3D.mak" CFG="Fly3D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Fly3D - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Fly3D - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Fly3D - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "FLY_EXPORTS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG"
# ADD RSC /l 0x416 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 dxguid.lib dsound.lib dinput.lib dplay.lib opengl32.lib glu32.lib winmm.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../Fly3D.dll"
# Begin Special Build Tool
OutDir=.\Release
TargetName=Fly3D
SOURCE="$(InputPath)"
PostBuild_Cmds=if exist "$(OutDir)\$(TargetName).lib" copy "$(OutDir)\$(TargetName).lib" "$(TargetName).lib"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "Fly3D - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "\mssdk\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "FLY_EXPORTS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG"
# ADD RSC /l 0x416 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dxguid.lib dsound.lib dinput.lib dplay.lib opengl32.lib glu32.lib winmm.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"../Fly3D.dll" /pdbtype:sept /libpath:"\mssdk\lib"
# Begin Special Build Tool
OutDir=.\Debug
TargetName=Fly3D
SOURCE="$(InputPath)"
PostBuild_Cmds=if exist "$(OutDir)\$(TargetName).lib" copy "$(OutDir)\$(TargetName).lib" "$(TargetName).lib"
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Fly3D - Win32 Release"
# Name "Fly3D - Win32 Debug"
# Begin Source File

SOURCE=.\ImpExp3ds\3dsExport.cpp
# End Source File
# Begin Source File

SOURCE=.\3dsImpExp.h
# End Source File
# Begin Source File

SOURCE=.\ImpExp3ds\3dsImport.cpp
# End Source File
# Begin Source File

SOURCE=.\directX\dx.cpp
# End Source File
# Begin Source File

SOURCE=.\dx.h
# End Source File
# Begin Source File

SOURCE=.\directX\dxwave.cpp
# End Source File
# Begin Source File

SOURCE=.\directX\dxwave.h
# End Source File
# Begin Source File

SOURCE=.\Fly3D.h
# End Source File
# Begin Source File

SOURCE=.\flyEngine\flyBezier.cpp
# End Source File
# Begin Source File

SOURCE=.\flyEngine\flyBsp.cpp
# End Source File
# Begin Source File

SOURCE=.\flyEngine\flyClasslib.cpp
# End Source File
# Begin Source File

SOURCE=.\flyEngine\flyConsole.cpp
# End Source File
# Begin Source File

SOURCE=.\flyEngine\flyDLL.cpp
# End Source File
# Begin Source File

SOURCE=.\flyEngine\flyDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\flyEngine\flyEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\flyEngine\flyLight.cpp
# End Source File
# Begin Source File

SOURCE=.\flyEngine\flyMesh.cpp
# End Source File
# Begin Source File

SOURCE=.\flyEngine\flyMultiplayer.cpp
# End Source File
# Begin Source File

SOURCE=.\flyEngine\flyMultiplayer.h
# End Source File
# Begin Source File

SOURCE=.\flyEngine\flyMultiplayer.rc
# End Source File
# Begin Source File

SOURCE=.\FlyPak\FlyPak.cpp
# End Source File
# Begin Source File

SOURCE=.\flypak.h
# End Source File
# Begin Source File

SOURCE=.\FlyPak\FlyPakUtil.cpp
# End Source File
# Begin Source File

SOURCE=.\flyEngine\flyParticle.cpp
# End Source File
# Begin Source File

SOURCE=.\flyEngine\flySound.cpp
# End Source File
# Begin Source File

SOURCE=.\flyEngine\flyStripfan.cpp
# End Source File
# Begin Source File

SOURCE=.\glext.h
# End Source File
# Begin Source File

SOURCE=.\jpg.h
# End Source File
# Begin Source File

SOURCE=.\picture\Picture.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\picture\PictureGL.cpp
# End Source File
# Begin Source File

SOURCE=.\render\Render.cpp
# End Source File
# Begin Source File

SOURCE=.\render.h
# End Source File
# Begin Source File

SOURCE=.\render\RenderGL.cpp
# End Source File
# Begin Source File

SOURCE=.\vecmat.h
# End Source File
# Begin Source File

SOURCE=.\picture\jpg.lib
# End Source File
# End Target
# End Project
