# Microsoft Developer Studio Project File - Name="synch_object_cost_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=synch_object_cost_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "synch_object_cost_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "synch_object_cost_test.mak" CFG="synch_object_cost_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "synch_object_cost_test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "synch_object_cost_test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "synch_object_cost_test - Win32 Release"

# PROP BASE Use_MFC 1
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
# ADD CPP /nologo /W3 /GX /O2 /I "$(STLSOFT_INCLUDE)" /I "$(SYNESIS_DEV)\include\unixem" /I "$(PTHREADS_WIN32)" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /D "unixx" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 pthreadVC.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /machine:I386 /libpath:"$(SYNESIS_DEV)\Bin"

!ELSEIF  "$(CFG)" == "synch_object_cost_test - Win32 Debug"

# PROP BASE Use_MFC 1
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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "$(STLSOFT_INCLUDE)" /I "$(SYNESIS_DEV)\include\unixem" /I "$(PTHREADS_WIN32)" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /D "unix" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 pthreadVC.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(SYNESIS_DEV)\Bin"

!ENDIF 

# Begin Target

# Name "synch_object_cost_test - Win32 Release"
# Name "synch_object_cost_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\synch_object_cost_test.cpp
# End Source File
# Begin Source File

SOURCE=..\synch_object_cost_test_2.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "PTHREADS Header Files"

# PROP Default_Filter ""
# End Group
# Begin Group "STLSoft Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_msvc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_limit_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_static_initialisers.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\unixstl_atomic_functions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\unixstl_spin_mutex.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl_performance_counter.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
