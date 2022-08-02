# Microsoft Developer Studio Project File - Name="string_slice_functions_first_form" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=string_slice_functions_first_form - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "string_slice_functions_first_form.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "string_slice_functions_first_form.mak" CFG="string_slice_functions_first_form - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "string_slice_functions_first_form - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "string_slice_functions_first_form - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "string_slice_functions_first_form - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "$(STLSOFT_INCLUDE)\\" /I "$(STLSOFT_INCLUDE)\inprogress\\" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /version:1.0 /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "string_slice_functions_first_form - Win32 Debug"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "$(STLSOFT_INCLUDE)\\" /I "$(STLSOFT_INCLUDE)\inprogress\\" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /version:1.0 /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "string_slice_functions_first_form - Win32 Release"
# Name "string_slice_functions_first_form - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\string_slice_functions_first_form.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "STLSoft Header Files"

# PROP Default_Filter ""
# Begin Group "Core"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\std\c\base_.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\minmax.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft__undefs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_allocator_base.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_auto_buffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_borland.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_como.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_dmc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_gcc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_intel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_msvc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_mwerks.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_unknown.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_vectorc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_watcom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_constraints.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_iterator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_meta.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_new_allocator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_null_allocator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_sap_cast.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_sign_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_simple_algorithms.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_size_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_static_array.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_type_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\std\c\string.hpp
# End Source File
# End Group
# Begin Group "Redirect"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\allocator_base.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\array_policies.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\auto_buffer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\char_traits.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\constraints.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\fast_string_concatenator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\integer_to_string.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\iterator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\meta.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\new_allocator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\null_allocator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\sap_cast.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\sign_traits.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\simple_algorithms.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\simple_string.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\size_traits.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\static_array.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\static_string.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_access.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_tokeniser.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_traits.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\type_traits.hpp
# End Source File
# End Group
# Begin Group "String Classes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\research\stlsoft\slice_string.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cstring_maker.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_environment_block.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_fast_string_concatenator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_fixed_substring.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_frame_string.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_shim_string.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_simple_string.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_static_string.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\research\stlsoft_string_buffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_string_tokeniser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_view.hpp
# End Source File
# End Group
# Begin Group "String Functions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\exception_string_access.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_integer_to_string.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_string_access.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_case_functions.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_container_slice_functions.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_slice_functions.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_split_functions.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_trim_functions.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_utility.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_view_slice_functions.hpp
# End Source File
# End Group
# Begin Group "String Traits"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\ctype_traits.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_array_policies.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_char_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_string_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_access_fwd.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_traits_fwd.hpp
# End Source File
# End Group
# Begin Group "String Function Objects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_functionals.hpp
# End Source File
# End Group
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
