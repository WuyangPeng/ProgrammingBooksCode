# Microsoft Developer Studio Project File - Name="01 BreakThrough" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=01 BreakThrough - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "01 BreakThrough.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "01 BreakThrough.mak" CFG="01 BreakThrough - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "01 BreakThrough - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "01 BreakThrough - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "01 BreakThrough - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x816 /d "NDEBUG"
# ADD RSC /l 0x816 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib d3d8.lib dxguid.lib dsound.lib dinput8.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "01 BreakThrough - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x816 /d "_DEBUG"
# ADD RSC /l 0x816 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib d3d8.lib dxguid.lib dsound.lib dinput8.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "01 BreakThrough - Win32 Release"
# Name "01 BreakThrough - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BreakThrough.cpp
# End Source File
# Begin Source File

SOURCE=.\btBall.cpp
# End Source File
# Begin Source File

SOURCE=.\btBlock.cpp
# End Source File
# Begin Source File

SOURCE=.\btGame.cpp
# End Source File
# Begin Source File

SOURCE=.\btPaddle.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrABO.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrAnimation.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrCDPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrInputManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrJoystick.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrKeyboard.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrMatrix22.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrMouse.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrParticle.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrParticleSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrRGBAImage.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrSound.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrSoundPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrSurface.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrTemplateSet.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrVector2D.cpp
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrWindow.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\btBall.h
# End Source File
# Begin Source File

SOURCE=.\btBlock.h
# End Source File
# Begin Source File

SOURCE=.\btGame.h
# End Source File
# Begin Source File

SOURCE=.\btPaddle.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\Mirus.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrABO.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrAnimation.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrCDPlayer.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrDataTypes.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrEntity.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrError.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrInputManager.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrJoystick.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrKeyboard.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrMatrix22.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrMouse.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrParticle.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrParticleSystem.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrRGBAImage.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrScreen.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrSound.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrSoundPlayer.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrSurface.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrTemplateSet.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrTexture.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrTimer.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrVector2D.h
# End Source File
# Begin Source File

SOURCE=.\Mirus\mrWindow.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
