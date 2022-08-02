# Microsoft Developer Studio Project File - Name="enumerator_sequence_motivation_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=enumerator_sequence_motivation_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "enumerator_sequence_motivation_test.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "enumerator_sequence_motivation_test.mak" CFG="enumerator_sequence_motivation_test - Win32 Debug"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "enumerator_sequence_motivation_test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "enumerator_sequence_motivation_test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe


!IF  "$(CFG)" == "enumerator_sequence_motivation_test - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "$(STLSOFT)/include" /I "$(RECLS_ROOT)/include" /I "$(SYNESIS_DEV)/include" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 mmcombsc.lib ole32.lib oleaut32.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Enum_sequence_motivation_test.debug.exe" /libpath:"$(RECLS_ROOT)/lib" /libpath:"$(SYNESIS_DEV)/lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "enumerator_sequence_motivation_test - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(STLSOFT)/include" /I "$(RECLS_ROOT)/include" /I "$(SYNESIS_DEV)/include" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 mmcombsc.lib ole32.lib oleaut32.lib user32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Enum_sequence_motivation_test.debug.exe" /pdbtype:sept /libpath:"$(RECLS_ROOT)/lib" /libpath:"$(SYNESIS_DEV)/lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF

# Begin Target

# Name "enumerator_sequence_motivation_test - Win32 Release"
# Name "enumerator_sequence_motivation_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\enumerator_sequence_motivation_test.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\freelibs\recls\current\mappings\COM\recls.com_i.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Synesis Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\M3CstTyp.h"
# End Source File
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\M3DbgExt.h"
# End Source File
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\M3Msvc.h"
# End Source File
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\MLBase.h"
# End Source File
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\MLCpp.h"
# End Source File
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\MLLimits.h"
# End Source File
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\MOBase.h"
# End Source File
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\MOBStr.h"
# End Source File
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\MOBStrFn.h"
# End Source File
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\MRBase.h"
# End Source File
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\MRString.h"
# End Source File
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\SLBase.h"
# End Source File
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\SLBasUDf.h"
# End Source File
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\SWrn001o.h"
# End Source File
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\SWrn001u.h"
# End Source File
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\SWrn004o.h"
# End Source File
# Begin Source File

SOURCE="$(SYNESIS_DEV)\include\SWrn004u.h"
# End Source File
# End Group
# Begin Group "STLSoft Header Files"

# PROP Default_Filter ""
# Begin Group "STLSoft"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\util\std\algorithm.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\algorithms.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\allocator_base.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\allocator_selector.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\auto_buffer.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\char_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\constraints.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\exceptions.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\inert.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\meta\is_function_pointer_type.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\iterator.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\util\std\iterator_generators.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\util\std\library_discriminator.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\meta.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\minmax.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\internal\cccap\msvc.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\meta\n_types.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\operator_bool.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\algorithms\pod.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\sap_cast.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\shim_string.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\sign_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\simple_string.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\size_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\util\std_swap.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\stlsoft.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft_meta.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\string_access.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\string_access_fwd.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\string_traits_fwd.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\type_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\meta\yesno.hpp"
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\meta\base_type_traits.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\collections\collections.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\util\exception_string.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\meta\is_pointer_type.hpp
# End Source File
# Begin Source File

SOURCE=$(STLSOFT)\include\stlsoft\meta\is_same_type.hpp
# End Source File
# End Group
# Begin Group "COMSTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT)\include\comstl.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\comstl\comstl.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\comstl\creation_functions.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\comstl\enumeration_policies.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\comstl\enumerator_sequence.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\comstl\exceptions.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\comstl\initialisers.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\comstl\interface_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\comstl\internal\interface_traits_std.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\comstl\memory_functions.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\comstl\method_cast.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\comstl\olestring_functions.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\comstl\refcount_functions.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\comstl\value_policies.hpp"
# End Source File
# End Group
# Begin Group "WinSTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT)\include\winstl\control_functions.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\winstl\listbox_sequence.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\winstl\message_functions.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\winstl\processheap_allocator.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\winstl.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\winstl\winstl.h"
# End Source File
# End Group
# Begin Group "RangeLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT)\include\rangelib\operator_adaptors.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\rangelib\range_categories.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\rangelib\rangelib.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\rangelib\sequence_range.hpp"
# End Source File
# End Group
# End Group
# Begin Group "recls Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(RECLS_ROOT)\mappings\COM\recls.com.h"
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
