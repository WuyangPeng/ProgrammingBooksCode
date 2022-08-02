# Microsoft Developer Studio Project File - Name="acestl_message_queue_sequence_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=acestl_message_queue_sequence_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "acestl_message_queue_sequence_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "acestl_message_queue_sequence_test.mak" CFG="acestl_message_queue_sequence_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "acestl_message_queue_sequence_test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "acestl_message_queue_sequence_test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "acestl_message_queue_sequence_test - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "$(STLSOFT_INCLUDE)" /I "$(ACE)" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ace.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Acestl_message_queue_sequence_test.debug.exe" /libpath:"$(ACE)\ace"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "acestl_message_queue_sequence_test - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "$(STLSOFT_INCLUDE)" /I "$(ACE)" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 aced.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Acestl_message_queue_sequence_test.debug.exe" /pdbtype:sept /libpath:"$(ACE)\ace"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "acestl_message_queue_sequence_test - Win32 Release"
# Name "acestl_message_queue_sequence_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\acestl_message_queue_sequence_test.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "STLSoft Header Files"

# PROP Default_Filter ""
# Begin Group "STLSoft"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Releases\1.8.3\STLSoft\include\stlsoft\iterator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Releases\1.8.3\STLSoft\include\stlsoft\meta.hpp
# End Source File
# Begin Source File

SOURCE="$(STLSOFT_INCLUDE)/stlsoft.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT_INCLUDE)/stlsoft_cccap_msvc.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Releases\1.8.3\STLSoft\include\stlsoft_iterator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Releases\1.8.3\STLSoft\include\stlsoft_meta.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Releases\1.8.3\STLSoft\include\stlsoft\meta\yesno.hpp
# End Source File
# End Group
# Begin Group "ACESTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT_INCLUDE)/acestl\acestl.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT_INCLUDE)/acestl\message_block_functions.hpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\STLSoft\Releases\1.8.3\STLSoft\include\acestl\message_queue_sequence.hpp
# End Source File
# End Group
# End Group
# Begin Group "ACE Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(ACE)\ace\ACE_export.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\ace_wchar.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\ace_wchar.inl"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Base_Thread_Adapter.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Basic_Types.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\config-all.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\config-win32-common.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\config-win32-msvc-6.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\config-win32-msvc.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\config-win32.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\config.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Default_Constants.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Event_Handler.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Global_Macros.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\IO_Cntl_Msg.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Log_Msg.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Log_Priority.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Malloc_Base.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Managed_Object.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Managed_Object.i"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Message_Block.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Message_Block_T.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Message_Block_T.i"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Message_Queue.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Message_Queue_T.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Message_Queue_T.i"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Min_Max.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Notification_Strategy.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Object_Manager.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\OS.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\OS_Dirent.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\OS_Errno.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\OS_Export.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\OS_Log_Msg_Attributes.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\OS_Memory.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\OS_String.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\OS_TLI.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\post.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\pre.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\streams.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Synch.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Synch_T.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Synch_T.i"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Thread.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Thread_Adapter.h"
# End Source File
# Begin Source File

SOURCE="$(ACE)\ace\Time_Value.h"
# End Source File
# Begin Source File

SOURCE="P:\SDKs\Microsoft SDK\include\WSPiApi.h"
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
