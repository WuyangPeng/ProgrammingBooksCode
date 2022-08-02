# Microsoft Developer Studio Project File - Name="path_exists_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=path_exists_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "path_exists_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "path_exists_test.mak" CFG="path_exists_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "path_exists_test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "path_exists_test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "path_exists_test - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "$(STLSOFT_INCLUDE)\\" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "path_exists_test - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "$(STLSOFT_INCLUDE)\\" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "path_exists_test - Win32 Release"
# Name "path_exists_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\path_exists_test.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_allocator_base.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_auto_buffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_msvc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_char_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_constraints.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_iterator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_meta.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_new_allocator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_sign_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_simple_algorithms.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_simple_string.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_size_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_string_access.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_type_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl_control_functions.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl_filesystem_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl_findfile_sequence.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl_functionals.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl_listbox_sequence.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl_processheap_allocator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl_string_access.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl_system_version.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
