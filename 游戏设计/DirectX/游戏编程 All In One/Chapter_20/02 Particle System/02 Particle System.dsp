# Microsoft Developer Studio Project File - Name="02 Particle System" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=02 Particle System - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "02 Particle System.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "02 Particle System.mak" CFG="02 Particle System - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "02 Particle System - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "02 Particle System - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "02 Particle System - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x816 /d "NDEBUG"
# ADD RSC /l 0x816 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "02 Particle System - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x816 /d "_DEBUG"
# ADD RSC /l 0x816 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "02 Particle System - Win32 Release"
# Name "02 Particle System - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\mrABO.cpp
# End Source File
# Begin Source File

SOURCE=.\mrAnimation.cpp
# End Source File
# Begin Source File

SOURCE=.\mrCDPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\mrEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\mrInputManager.cpp
# End Source File
# Begin Source File

SOURCE=.\mrJoystick.cpp
# End Source File
# Begin Source File

SOURCE=.\mrKeyboard.cpp
# End Source File
# Begin Source File

SOURCE=.\mrMatrix22.cpp
# End Source File
# Begin Source File

SOURCE=.\mrMouse.cpp
# End Source File
# Begin Source File

SOURCE=.\mrParticle.cpp
# End Source File
# Begin Source File

SOURCE=.\mrParticleSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\mrRGBAImage.cpp
# End Source File
# Begin Source File

SOURCE=.\mrScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\mrSound.cpp
# End Source File
# Begin Source File

SOURCE=.\mrSoundPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\mrSurface.cpp
# End Source File
# Begin Source File

SOURCE=.\mrTemplateSet.cpp
# End Source File
# Begin Source File

SOURCE=.\mrTexture.cpp
# End Source File
# Begin Source File

SOURCE=.\mrTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\mrVector2D.cpp
# End Source File
# Begin Source File

SOURCE=.\mrWindow.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Mirus.h
# End Source File
# Begin Source File

SOURCE=.\mrABO.h
# End Source File
# Begin Source File

SOURCE=.\mrAnimation.h
# End Source File
# Begin Source File

SOURCE=.\mrCDPlayer.h
# End Source File
# Begin Source File

SOURCE=.\mrDataTypes.h
# End Source File
# Begin Source File

SOURCE=.\mrEntity.h
# End Source File
# Begin Source File

SOURCE=.\mrError.h
# End Source File
# Begin Source File

SOURCE=.\mrInputManager.h
# End Source File
# Begin Source File

SOURCE=.\mrJoystick.h
# End Source File
# Begin Source File

SOURCE=.\mrKeyboard.h
# End Source File
# Begin Source File

SOURCE=.\mrMatrix22.h
# End Source File
# Begin Source File

SOURCE=.\mrMouse.h
# End Source File
# Begin Source File

SOURCE=.\mrParticle.h
# End Source File
# Begin Source File

SOURCE=.\mrParticleSystem.h
# End Source File
# Begin Source File

SOURCE=.\mrRGBAImage.h
# End Source File
# Begin Source File

SOURCE=.\mrScreen.h
# End Source File
# Begin Source File

SOURCE=.\mrSound.h
# End Source File
# Begin Source File

SOURCE=.\mrSoundPlayer.h
# End Source File
# Begin Source File

SOURCE=.\mrSurface.h
# End Source File
# Begin Source File

SOURCE=.\mrTemplateSet.h
# End Source File
# Begin Source File

SOURCE=.\mrTexture.h
# End Source File
# Begin Source File

SOURCE=.\mrTimer.h
# End Source File
# Begin Source File

SOURCE=.\mrVector2D.h
# End Source File
# Begin Source File

SOURCE=.\mrWindow.h
# End Source File
# End Group
# End Target
# End Project
