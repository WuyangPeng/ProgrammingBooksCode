# Microsoft Developer Studio Project File - Name="findfirstfile_sequence_motivation_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=findfirstfile_sequence_motivation_test - Win32 Debug Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "findfirstfile_sequence_motivation_test.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "findfirstfile_sequence_motivation_test.mak" CFG="findfirstfile_sequence_motivation_test - Win32 Debug Unicode"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "findfirstfile_sequence_motivation_test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "findfirstfile_sequence_motivation_test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "findfirstfile_sequence_motivation_test - Win32 Debug Unicode" (based on "Win32 (x86) Application")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe


!IF  "$(CFG)" == "findfirstfile_sequence_motivation_test - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "$(PANTHEIOS_ROOT)/include" /I "$(STLSOFT_INCLUDE)" /I "$(STLSOFT_INCLUDE)\inprogress\\" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Findfirstfile_sequence_motivation_test.debug.exe" /libpath:"$(PANTHEIOS_ROOT)/lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "findfirstfile_sequence_motivation_test - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(PANTHEIOS_ROOT)/include" /I "$(STLSOFT_INCLUDE)" /I "$(STLSOFT_INCLUDE)\inprogress\\" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Findfirstfile_sequence_motivation_test.debug.exe" /pdbtype:sept /libpath:"$(PANTHEIOS_ROOT)/lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "findfirstfile_sequence_motivation_test - Win32 Debug Unicode"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "findfirstfile_sequence_motivation_test___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "findfirstfile_sequence_motivation_test___Win32_Debug_Unicode"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugUnicode"
# PROP Intermediate_Dir "DebugUnicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(PANTHEIOS_ROOT)/include" /I "$(STLSOFT_INCLUDE)" /I "$(STLSOFT_INCLUDE)\inprogress\\" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /FR /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(PANTHEIOS_ROOT)/include" /I "$(STLSOFT_INCLUDE)" /I "$(STLSOFT_INCLUDE)\inprogress\\" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /D "UNICODE" /D "_UNICODE" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Findfirstfile_sequence_motivation_test.debug.exe" /pdbtype:sept /libpath:"$(PANTHEIOS_ROOT)/lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"DebugUnicode/Findfirstfile_sequence_motivation_test.debug.exe" /pdbtype:sept /libpath:"$(PANTHEIOS_ROOT)/lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF

# Begin Target

# Name "findfirstfile_sequence_motivation_test - Win32 Release"
# Name "findfirstfile_sequence_motivation_test - Win32 Debug"
# Name "findfirstfile_sequence_motivation_test - Win32 Debug Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\findfirstfile_sequence_motivation_test.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "STLSoft Header Files"

# PROP Default_Filter ""
# Begin Group "STLSoft"

# PROP Default_Filter ""
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\util\std\algorithm.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\algorithms.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\allocator_base.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\allocator_selector.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\auto_buffer.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\meta\base_type_traits.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\char_traits.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\collections\collections.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\constraints.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\cstring_maker.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\util\exception_string.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\exception_string_access.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\exceptions.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\integer_to_string.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\meta\is_function_pointer_type.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\meta\is_pointer_type.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\meta\is_same_type.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\iterator.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\util\std\iterator_generators.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\util\std\library_discriminator.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\meta.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\minmax.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\internal\cccap\msvc.h
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\meta\n_types.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\algorithms\pod.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\sap_cast.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\shim_string.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\sign_traits.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\simple_string.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\size_traits.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\util\std_swap.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\stlsoft.h
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft_meta.h
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\string_access.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\string_access_fwd.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\string_traits_fwd.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\time_string_access.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\tokeniser_functions.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\union_cast.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\meta\yesno.hpp
# End Source File
# End Group
# Begin Group "COMSTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=$(STLSOFT)\include\comstl\bstr_functions.h
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\comstl\comstl.h
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\comstl\string_access.hpp
# End Source File
# End Group
# Begin Group "WinSTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\error_desc.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\error_functions.h
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\exceptions.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\file_path_buffer.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\filesystem_traits.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\findfile_sequence.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\functions.h
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\processheap_allocator.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\reg_defs.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\reg_traits.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\registry_functions.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\string_access.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\system_version.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\time_format_functions.h
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\time_string_access.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\window_functions.h
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\windows_ident.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\windows_type_conversions.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\winstl.h
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl_reg_defs.h
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl_reg_traits.h
# End Source File
# End Group
# End Group
# Begin Group "Pantheios Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(PANTHEIOS_ROOT)\include\pantheios\implicit_link\be_Win32Debugger.h"
# End Source File
# Begin Source File

SOURCE="$(PANTHEIOS_ROOT)\include\pantheios\implicit_link\bec_Win32Debugger.h"
# End Source File
# Begin Source File

SOURCE="$(PANTHEIOS_ROOT)\include\pantheios\implicit_link\core.h"
# End Source File
# Begin Source File

SOURCE="$(PANTHEIOS_ROOT)\include\pantheios\implicit_link\fe_simple.h"
# End Source File
# Begin Source File

SOURCE="$(PANTHEIOS_ROOT)\include\pantheios\implicit_link\implicit_link_base_.h"
# End Source File
# Begin Source File

SOURCE="$(PANTHEIOS_ROOT)\include\pantheios\cpp\initialiser.hpp"
# End Source File
# Begin Source File

SOURCE="$(PANTHEIOS_ROOT)\include\pantheios\cpp\log_dispatch_functions.hpp"
# End Source File
# Begin Source File

SOURCE="$(PANTHEIOS_ROOT)\include\pantheios\c\log_functions.h"
# End Source File
# Begin Source File

SOURCE="$(PANTHEIOS_ROOT)\include\pantheios\cpp\log_functions.hpp"
# End Source File
# Begin Source File

SOURCE="$(PANTHEIOS_ROOT)\include\pantheios\cpp\log_sev_functions.hpp"
# End Source File
# Begin Source File

SOURCE="$(PANTHEIOS_ROOT)\include\pantheios\pantheios.h"
# End Source File
# Begin Source File

SOURCE="$(PANTHEIOS_ROOT)\include\pantheios\pantheios.hpp"
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
