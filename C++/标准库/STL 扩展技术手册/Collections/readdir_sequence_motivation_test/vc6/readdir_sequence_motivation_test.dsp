# Microsoft Developer Studio Project File - Name="readdir_sequence_motivation_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=readdir_sequence_motivation_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "readdir_sequence_motivation_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "readdir_sequence_motivation_test.mak" CFG="readdir_sequence_motivation_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "readdir_sequence_motivation_test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "readdir_sequence_motivation_test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "readdir_sequence_motivation_test - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "$(STLSOFT_INCLUDE)" /I "$(STLSOFT_INCLUDE)\inprogress\\" /I "$(UNIXEM)\include" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Readdir_sequence_motivation_test.debug.exe" /libpath:"$(UNIXEM)\lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "readdir_sequence_motivation_test - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(STLSOFT_INCLUDE)" /I "$(STLSOFT_INCLUDE)\inprogress\\" /I "$(UNIXEM)\include" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Readdir_sequence_motivation_test.debug.exe" /pdbtype:sept /libpath:"$(UNIXEM)\lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "readdir_sequence_motivation_test - Win32 Release"
# Name "readdir_sequence_motivation_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\readdir_sequence_motivation_test.cpp
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

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\char_traits.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\constraints.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\function_pointer_adaptors.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\iterator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\util\std\iterator_generators.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\malloc_allocator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\meta.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\minmax.hpp
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

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\scoped_handle.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\sign_traits.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\simple_algorithms.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\simple_string.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\size_traits.hpp
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

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft_char_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft_constraints.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft_malloc_allocator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft_meta.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft_new_allocator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft_sign_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft_simple_algorithms.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft_size_traits.h
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

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\unixstl\string_access.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\string_access_fwd.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\string_traits_fwd.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\type_traits.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\stlsoft\meta\yesno.hpp
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

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\unixstl\path.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\unixstl\readdir_sequence.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\unixstl.h
# End Source File
# End Group
# End Group
# Begin Group "UNIXEm Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\freelibs\unixem\include\dirent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\freelibs\unixem\include\unixem\implicit_link.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\freelibs\unixem\include\unistd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\freelibs\unixem\include\unixem\unixem.h
# End Source File
# End Group
# Begin Group "Example Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\readdir_sequence.hpp
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
