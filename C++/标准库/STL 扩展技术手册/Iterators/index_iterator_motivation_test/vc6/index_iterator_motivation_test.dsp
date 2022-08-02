# Microsoft Developer Studio Project File - Name="index_iterator_motivation_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=index_iterator_motivation_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "index_iterator_motivation_test.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "index_iterator_motivation_test.mak" CFG="index_iterator_motivation_test - Win32 Debug"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "index_iterator_motivation_test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "index_iterator_motivation_test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe


!IF  "$(CFG)" == "index_iterator_motivation_test - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "$(STLSOFT)/include" /I "$(RECLS_ROOT)/include" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 wininet.lib recls.1.vc6.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Indexed_iterator_motivation_test.debug.exe" /libpath:"$(RECLS_ROOT)/lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "index_iterator_motivation_test - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(STLSOFT)/include" /I "$(RECLS_ROOT)/include" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wininet.lib recls.1.vc6.debug.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Indexed_iterator_motivation_test.debug.exe" /pdbtype:sept /libpath:"$(RECLS_ROOT)/lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF

# Begin Target

# Name "index_iterator_motivation_test - Win32 Release"
# Name "index_iterator_motivation_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\index_iterator_motivation_test.cpp
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

SOURCE=$(STLSOFT)\include\stlsoft\constraints.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\integer_to_string.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\meta\is_function_pointer_type.hpp
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

SOURCE=$(STLSOFT)\include\stlsoft\proxy_iterator.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\proxy_sequence.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\sap_cast.hpp
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

SOURCE=$(STLSOFT)\include\stlsoft_proxy_iterator.h
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft_proxy_sequence.h
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

SOURCE=$(STLSOFT)\include\stlsoft\meta\yesno.hpp
# End Source File
# End Group
# Begin Group "PlatformSTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=$(STLSOFT)\include\platformstl\file_path_buffer.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\platformstl\platformstl.h
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\platformstl\platformstl.hpp
# End Source File
# End Group
# Begin Group "WinSTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\file_path_buffer.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\processheap_allocator.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\winstl\winstl.h
# End Source File
# End Group
# End Group
# Begin Group "recls Header Files"

# PROP Default_Filter ""
# Begin Group "recls/STL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=$(RECLS_ROOT)\include\recls\stl\recls.hpp
# End Source File
# Begin Source File

SOURCE=$(RECLS_ROOT)\include\recls\stl\search_sequence.hpp
# End Source File
# Begin Source File

SOURCE=$(RECLS_ROOT)\include\recls\stl\traits.hpp
# End Source File
# End Group
# Begin Source File

SOURCE=$(RECLS_ROOT)\include\recls\internal\compiler.h
# End Source File
# Begin Source File

SOURCE=$(RECLS_ROOT)\include\recls\internal\compiler_msvc.h
# End Source File
# Begin Source File

SOURCE=$(RECLS_ROOT)\include\recls\ftp.h
# End Source File
# Begin Source File

SOURCE=$(RECLS_ROOT)\include\recls\internal\language.h
# End Source File
# Begin Source File

SOURCE=$(RECLS_ROOT)\include\recls\internal\platform.h
# End Source File
# Begin Source File

SOURCE=$(RECLS_ROOT)\include\recls\internal\platform_types.h
# End Source File
# Begin Source File

SOURCE=$(RECLS_ROOT)\include\recls\recls.h
# End Source File
# Begin Source File

SOURCE=$(RECLS_ROOT)\include\recls\internal\retcodes.h
# End Source File
# Begin Source File

SOURCE=$(RECLS_ROOT)\include\recls\win32.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
