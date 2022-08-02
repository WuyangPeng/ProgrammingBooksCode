# Microsoft Developer Studio Project File - Name="flyEditor" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=flyEditor - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "flyEditor.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "flyEditor.mak" CFG="flyEditor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "flyEditor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "flyEditor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "flyEditor - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 dxguid.lib dsound.lib dinput.lib dplay.lib opengl32.lib glu32.lib winmm.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib /nologo /subsystem:windows /machine:I386 /out:"../../flyEditor.exe"

!ELSEIF  "$(CFG)" == "flyEditor - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x416 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x416 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dxguid.lib dsound.lib dinput.lib dplay.lib opengl32.lib glu32.lib winmm.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386 /out:"../../flyEditor.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "flyEditor - Win32 Release"
# Name "flyEditor - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DlgEditList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditValue.cpp
# End Source File
# Begin Source File

SOURCE=.\flyEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\flyEditorDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\flyEditorView.cpp
# End Source File
# Begin Source File

SOURCE=.\flyRenderView.cpp
# End Source File
# Begin Source File

SOURCE=.\LeftView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DlgEditList.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditValue.h
# End Source File
# Begin Source File

SOURCE=.\flyEditor.h
# End Source File
# Begin Source File

SOURCE=.\flyEditorDoc.h
# End Source File
# Begin Source File

SOURCE=.\flyEditorView.h
# End Source File
# Begin Source File

SOURCE=.\flyRenderView.h
# End Source File
# Begin Source File

SOURCE=.\LeftView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\fly.ICO
# End Source File
# Begin Source File

SOURCE=.\fly3dtyp.ico
# End Source File
# Begin Source File

SOURCE=.\flyEditor.rc
# End Source File
# Begin Source File

SOURCE=.\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\flyEditor.reg
# End Source File
# End Target
# End Project
