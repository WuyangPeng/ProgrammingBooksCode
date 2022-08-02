# Microsoft Developer Studio Project File - Name="AISteroids" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=AISteroids - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AISteroids.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AISteroids.mak" CFG="AISteroids - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AISteroids - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "AISteroids - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=snCl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AISteroids - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=snBsc.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=snLink.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "AISteroids - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=snBsc.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=snLink.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "AISteroids - Win32 Release"
# Name "AISteroids - Win32 Debug"
# Begin Group "AI Controllers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\AIControl.cpp
# End Source File
# Begin Source File

SOURCE=..\AIControl.h
# End Source File
# Begin Source File

SOURCE=..\FSMAIControl.cpp
# End Source File
# Begin Source File

SOURCE=..\FSMAIControl.h
# End Source File
# Begin Source File

SOURCE=..\NNAIControl.cpp
# End Source File
# Begin Source File

SOURCE=..\NNAIControl.h
# End Source File
# End Group
# Begin Group "AI Method Files"

# PROP Default_Filter ""
# Begin Group "Neural Net"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\NNetwork.cpp
# End Source File
# Begin Source File

SOURCE=..\NNetwork.h
# End Source File
# Begin Source File

SOURCE=..\StateNNEvade.cpp
# End Source File
# Begin Source File

SOURCE=..\StateNNEvade.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\FSM.h
# End Source File
# Begin Source File

SOURCE=..\FSMMachine.cpp
# End Source File
# Begin Source File

SOURCE=..\FSMMachine.h
# End Source File
# Begin Source File

SOURCE=..\FSMState.h
# End Source File
# Begin Source File

SOURCE=..\StateApproach.cpp
# End Source File
# Begin Source File

SOURCE=..\StateApproach.h
# End Source File
# Begin Source File

SOURCE=..\StateAttack.cpp
# End Source File
# Begin Source File

SOURCE=..\StateAttack.h
# End Source File
# Begin Source File

SOURCE=..\StateEvade.cpp
# End Source File
# Begin Source File

SOURCE=..\StateEvade.h
# End Source File
# Begin Source File

SOURCE=..\StateGetPowerup.cpp
# End Source File
# Begin Source File

SOURCE=..\StateGetPowerup.h
# End Source File
# Begin Source File

SOURCE=..\StateIdle.cpp
# End Source File
# Begin Source File

SOURCE=..\StateIdle.h
# End Source File
# End Group
# Begin Group "Utilities"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Point3.h
# End Source File
# Begin Source File

SOURCE=..\Sphere3.h
# End Source File
# Begin Source File

SOURCE=..\utility.cpp
# End Source File
# Begin Source File

SOURCE=..\utility.h
# End Source File
# End Group
# Begin Group "Game Objects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Ast.cpp
# End Source File
# Begin Source File

SOURCE=..\Ast.h
# End Source File
# Begin Source File

SOURCE=..\Bullet.cpp
# End Source File
# Begin Source File

SOURCE=..\Bullet.h
# End Source File
# Begin Source File

SOURCE=..\Exp.cpp
# End Source File
# Begin Source File

SOURCE=..\Exp.h
# End Source File
# Begin Source File

SOURCE=..\GameObj.cpp
# End Source File
# Begin Source File

SOURCE=..\GameObj.h
# End Source File
# Begin Source File

SOURCE=..\Powerup.cpp
# End Source File
# Begin Source File

SOURCE=..\Powerup.h
# End Source File
# Begin Source File

SOURCE=..\Ship.cpp
# End Source File
# Begin Source File

SOURCE=..\Ship.h
# End Source File
# Begin Source File

SOURCE=..\Target.cpp
# End Source File
# Begin Source File

SOURCE=..\Target.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\asteroids.cpp
# End Source File
# Begin Source File

SOURCE=..\Control.h
# End Source File
# Begin Source File

SOURCE=..\GameSession.cpp
# End Source File
# Begin Source File

SOURCE=..\GameSession.h
# End Source File
# Begin Source File

SOURCE=..\HumanControl.cpp
# End Source File
# Begin Source File

SOURCE=..\HumanControl.h
# End Source File
# End Target
# End Project
