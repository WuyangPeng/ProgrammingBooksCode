# Microsoft Developer Studio Project File - Name="slice_functions_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=slice_functions_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "slice_functions_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "slice_functions_test.mak" CFG="slice_functions_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "slice_functions_test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "slice_functions_test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "slice_functions_test - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "$(STLSOFT_INCLUDE)\\" /I "$(STLSOFT_INCLUDE)\inprogress\\" /I "$(ACE)" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 atl.lib ace.lib /nologo /version:1.0 /subsystem:console /machine:I386 /libpath:"$(ACE)\ace"

!ELSEIF  "$(CFG)" == "slice_functions_test - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "$(STLSOFT_INCLUDE)\\" /I "$(STLSOFT_INCLUDE)\inprogress\\" /I "$(ACE)" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 atl.lib aced.lib /nologo /version:1.0 /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"$(ACE)\ace"

!ENDIF 

# Begin Target

# Name "slice_functions_test - Win32 Release"
# Name "slice_functions_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\slice_functions_test.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "STLSoft Header Files"

# PROP Default_Filter ""
# Begin Group "STLSoft"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\allocator_base.hpp
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

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\iterator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\malloc_allocator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\meta.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\minmax.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\new_allocator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\sap_cast.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\shim_string.hpp
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

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_allocator_base.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_auto_buffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_msvc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_char_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_constraints.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_iterator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_malloc_allocator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_meta.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_new_allocator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_sap_cast.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_shim_string.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_sign_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_simple_algorithms.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_simple_string.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_size_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_string_access.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_type_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_access.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_access_fwd.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\string_traits_fwd.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\acestl\time_string_access.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\stlsoft\type_traits.hpp
# End Source File
# End Group
# Begin Group "ACESTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\acestl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\acestl\acestl.hpp
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Addr.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\INET_Addr.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\acestl\inet_addr_string_access.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\acestl\string_access.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\inprogress\acestl\string_string_access.hpp
# End Source File
# End Group
# Begin Group "ATLSTL"

# PROP Default_Filter ""
# End Group
# Begin Group "COMSTL"

# PROP Default_Filter ""
# End Group
# Begin Group "MFCSTL"

# PROP Default_Filter ""
# End Group
# Begin Group "UNIXSTL"

# PROP Default_Filter ""
# End Group
# Begin Group "WinSTL"

# PROP Default_Filter ""
# End Group
# End Group
# Begin Group "ACE Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\ACE.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\ACE.i"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\ACE_export.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\ace_wchar.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\ace_wchar.inl"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Auto_Ptr.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Auto_Ptr.i"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Base_Thread_Adapter.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Basic_Types.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\config-all.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\config-win32-common.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\config-win32-msvc-6.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\config-win32-msvc.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\config-win32.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\config.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Default_Constants.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Event_Handler.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Flag_Manip.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Flag_Manip.i"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Free_List.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Free_List.i"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Global_Macros.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Handle_Ops.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Handle_Ops.i"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Init_ACE.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Init_ACE.i"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Lib_Find.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Lib_Find.i"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Log_Msg.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Log_Priority.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Malloc_Allocator.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Malloc_Base.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Malloc_T.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Malloc_T.i"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Managed_Object.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Managed_Object.i"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Mem_Map.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Memory_Pool.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Min_Max.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Node.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Object_Manager.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\OS.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\OS_Dirent.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\OS_Errno.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\OS_Export.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\OS_Log_Msg_Attributes.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\OS_Memory.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\OS_String.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\OS_TLI.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\post.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\pre.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Sock_Connect.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Sock_Connect.i"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\streams.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\String_Base.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\String_Base.i"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\String_Base_Const.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Synch.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Synch_T.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Synch_T.i"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Thread.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Thread_Adapter.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Time_Value.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Unbounded_Set.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\ACE_wrappers-5.3\ace\Unbounded_Set.inl"
# End Source File
# Begin Source File

SOURCE="P:\sdks\Microsoft SDK\include\WSPiApi.h"
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
