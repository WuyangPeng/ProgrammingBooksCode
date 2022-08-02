# Microsoft Developer Studio Project File - Name="filesys_enum_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=filesys_enum_test - Win32 Debug pseudoUNIX
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "filesys_enum_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "filesys_enum_test.mak" CFG="filesys_enum_test - Win32 Debug pseudoUNIX"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "filesys_enum_test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "filesys_enum_test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "filesys_enum_test - Win32 Debug pseudoUNIX" (based on "Win32 (x86) Application")
!MESSAGE "filesys_enum_test - Win32 Release pseudoUNIX" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "filesys_enum_test - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "$(STLSOFT_INCLUDE)" /I "$(STLSOFT_INCLUDE)\inprogress\\" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Filesys_enum_test.debug.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "filesys_enum_test - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(STLSOFT_INCLUDE)" /I "$(STLSOFT_INCLUDE)\inprogress\\" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /GZ  /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Filesys_enum_test.debug.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "filesys_enum_test - Win32 Debug pseudoUNIX"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug pseudoUNIX"
# PROP BASE Intermediate_Dir "Debug pseudoUNIX"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugUNIX"
# PROP Intermediate_Dir "DebugUNIX"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "$(STLSOFT_INCLUDE)" /I "$(STLSOFT_INCLUDE)\inprogress\\" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /GZ  /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(UNIXEM)/include" /I "$(STLSOFT_INCLUDE)" /I "$(STLSOFT_INCLUDE)\inprogress\\" /D "_DEBUG" /D "WIN32" /D "STRICT" /D "_CONSOLE" /D "unix" /D "_STLSOFT_FORCE_ANY_COMPILER" /YX /FD /GZ  /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Filesys_enum_test.debug.exe" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib unixem.vc6.debug.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"DebugUNIX/Filesys_enum_test.debug.exe" /pdbtype:sept /libpath:"$(UNIXEM)/lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "filesys_enum_test - Win32 Release pseudoUNIX"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release pseudoUNIX"
# PROP BASE Intermediate_Dir "Release pseudoUNIX"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUNIX"
# PROP Intermediate_Dir "ReleaseUNIX"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "$(STLSOFT_INCLUDE)" /I "$(STLSOFT_INCLUDE)\inprogress\\" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "$(UNIXEM)/include" /I "$(STLSOFT_INCLUDE)" /I "$(STLSOFT_INCLUDE)\inprogress\\" /D "NDEBUG" /D "WIN32" /D "STRICT" /D "_CONSOLE" /D "unix" /D "_STLSOFT_FORCE_ANY_COMPILER" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Filesys_enum_test.debug.exe"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib unixem.vc6.debug.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Filesys_enum_test.debug.exe" /libpath:"$(UNIXEM)/lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "filesys_enum_test - Win32 Release"
# Name "filesys_enum_test - Win32 Debug"
# Name "filesys_enum_test - Win32 Debug pseudoUNIX"
# Name "filesys_enum_test - Win32 Release pseudoUNIX"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\filesys_enum_test.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "STLSoft Header Files"

# PROP Default_Filter ""
# Begin Group "STLSoft"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\util\std\algorithm.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\allocator_base.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\allocator_selector.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\auto_buffer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\constraints.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\iterator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\meta.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\new_allocator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\algorithms\pod.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\sap_cast.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\util\std_swap.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft_allocator_base.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft_cccap_msvc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft_constraints.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft_meta.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft_new_allocator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft_string_access.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft_type_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\string_access.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\string_access_fwd.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\winstl\system_version.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\tokeniser_functions.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\type_traits.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\meta\yesno.hpp
# End Source File
# End Group
# Begin Group "PlatformSTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\platformstl\platformstl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\platformstl\platformstl.hpp
# End Source File
# End Group
# Begin Group "UNIXSTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\unixstl\file_path_buffer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\unixstl\filesystem_traits.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\unixstl\glob_sequence.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\unixstl\string_access.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\unixstl.h
# End Source File
# End Group
# Begin Group "WinSTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\winstl\file_path_buffer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\winstl\filesystem_traits.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\winstl\findfile_sequence.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\winstl\processheap_allocator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\winstl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\winstl_filesystem_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\winstl_processheap_allocator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\winstl_system_version.h
# End Source File
# End Group
# End Group
# Begin Group "UNIXEm Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\freelibs\unixem\include\dirent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\freelibs\unixem\include\glob.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\freelibs\unixem\include\unistd.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
