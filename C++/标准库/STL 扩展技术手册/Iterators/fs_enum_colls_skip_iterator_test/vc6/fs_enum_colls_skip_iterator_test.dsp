# Microsoft Developer Studio Project File - Name="fs_enum_colls_skip_iterator_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=fs_enum_colls_skip_iterator_test - Win32 Debug pseudoUNIX
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "fs_enum_colls_skip_iterator_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "fs_enum_colls_skip_iterator_test.mak" CFG="fs_enum_colls_skip_iterator_test - Win32 Debug pseudoUNIX"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fs_enum_colls_skip_iterator_test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "fs_enum_colls_skip_iterator_test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "fs_enum_colls_skip_iterator_test - Win32 Debug pseudoUNIX" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "fs_enum_colls_skip_iterator_test - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Fs_enum_colls_skip_iterator_test.debug.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "fs_enum_colls_skip_iterator_test - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(STLSOFT_INCLUDE)" /I "$(STLSOFT_INCLUDE)\inprogress\\" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Fs_enum_colls_skip_iterator_test.debug.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "fs_enum_colls_skip_iterator_test - Win32 Debug pseudoUNIX"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "$(STLSOFT_INCLUDE)" /I "$(STLSOFT_INCLUDE)\inprogress\\" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(STLSOFT_INCLUDE)" /I "$(STLSOFT_INCLUDE)\inprogress\\" /I "$(UNIXEM)/include" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /D "unix" /D "_STLSOFT_FORCE_ANY_COMPILER" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Fs_enum_colls_skip_iterator_test.debug.exe" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib unixem.1.vc6.debug.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Fs_enum_colls_skip_iterator_test.debug.exe" /pdbtype:sept /libpath:"$(UNIXEM)/lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "fs_enum_colls_skip_iterator_test - Win32 Release"
# Name "fs_enum_colls_skip_iterator_test - Win32 Debug"
# Name "fs_enum_colls_skip_iterator_test - Win32 Debug pseudoUNIX"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\fs_enum_colls_skip_iterator_test.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "STLSoft Header Files"

# PROP Default_Filter ""
# Begin Group "STLSoft"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\util\std\algorithm.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\allocator_base.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\allocator_selector.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\auto_buffer.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\char_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\constraints.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\exceptions.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\iterator.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\util\std\iterator_generators.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\meta.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\minmax.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\new_allocator.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\algorithms\pod.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\sap_cast.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\sign_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\simple_algorithms.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\simple_string.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\size_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\util\std_swap.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft_allocator_base.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft_cccap_msvc.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft_char_traits.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft_constraints.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft_meta.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft_new_allocator.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft_sign_traits.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft_simple_algorithms.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft_size_traits.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft_string_access.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\string_access.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\string_access_fwd.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\string_traits_fwd.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\tokeniser_functions.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\type_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\meta\yesno.hpp"
# End Source File
# End Group
# Begin Group "PlatformSTL Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT)/include\platformstl\platformstl.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\platformstl\platformstl.hpp"
# End Source File
# End Group
# Begin Group "UNIXSTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT)/include\unixstl\exceptions.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\unixstl\file_path_buffer.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\unixstl\filesystem_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\unixstl\path.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\unixstl\readdir_sequence.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\unixstl\string_access.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\unixstl.h"
# End Source File
# End Group
# Begin Group "WinSTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT)/include\winstl\error_functions.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\winstl\exceptions.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\winstl\file_path_buffer.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\winstl\filesystem_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\winstl\findfile_sequence.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\winstl\processheap_allocator.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\winstl\system_version.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\winstl.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\winstl_exceptions.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\winstl_processheap_allocator.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)/include\winstl_system_version.h"
# End Source File
# End Group
# End Group
# Begin Group "UNIXEm Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\freelibs\unixem\1.6.x\include\dirent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\freelibs\unixem\1.6.x\include\dlfcn.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\freelibs\unixem\1.6.x\include\unistd.h
# End Source File
# End Group
# Begin Source File

SOURCE="$(STLSOFT)/include\stlsoft\skip_iterator.hpp"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
