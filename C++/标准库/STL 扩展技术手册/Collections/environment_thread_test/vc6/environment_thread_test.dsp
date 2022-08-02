# Microsoft Developer Studio Project File - Name="environment_thread_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=environment_thread_test - Win32 Debug none
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "environment_thread_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "environment_thread_test.mak" CFG="environment_thread_test - Win32 Debug none"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "environment_thread_test - Win32 Debug _putenv" (based on "Win32 (x86) Application")
!MESSAGE "environment_thread_test - Win32 Release _putenv" (based on "Win32 (x86) Application")
!MESSAGE "environment_thread_test - Win32 Debug setenv" (based on "Win32 (x86) Application")
!MESSAGE "environment_thread_test - Win32 Release setenv" (based on "Win32 (x86) Application")
!MESSAGE "environment_thread_test - Win32 Debug _putenv equal" (based on "Win32 (x86) Application")
!MESSAGE "environment_thread_test - Win32 Release _putenv equal" (based on "Win32 (x86) Application")
!MESSAGE "environment_thread_test - Win32 Debug none" (based on "Win32 (x86) Application")
!MESSAGE "environment_thread_test - Win32 Release none" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "environment_thread_test - Win32 Debug _putenv"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Win32_Debug__putenv"
# PROP BASE Intermediate_Dir "Win32_Debug__putenv"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Win32_Debug__putenv"
# PROP Intermediate_Dir "Win32_Debug__putenv"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "$(STLSOFT)/include" /I "$(PTHREADS_WIN32)" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(STLSOFT)/include" /I "$(PTHREADS_WIN32)" /D "_DEBUG" /D "WIN32" /D "STRICT" /D "_CONSOLE" /D "PLATFORMSTL_ENVMAP_ERASE_BY_PUTENV" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 pthreadVC.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Environment_thread_test.debug.exe" /pdbtype:sept /libpath:"$(PTHREADS_WIN32)"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 pthreadVC.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Environment_thread_test.debug.exe" /pdbtype:sept /libpath:"$(PTHREADS_WIN32)"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "environment_thread_test - Win32 Release _putenv"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Win32_Release__putenv"
# PROP BASE Intermediate_Dir "Win32_Release__putenv"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win32_Release__putenv"
# PROP Intermediate_Dir "Win32_Release__putenv"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "$(STLSOFT)/include" /I "$(PTHREADS_WIN32)" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "$(STLSOFT)/include" /I "$(PTHREADS_WIN32)" /D "NDEBUG" /D "WIN32" /D "STRICT" /D "_CONSOLE" /D "PLATFORMSTL_ENVMAP_ERASE_BY_PUTENV" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 pthreadVC.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Environment_thread_test.debug.exe" /libpath:"$(PTHREADS_WIN32)"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 pthreadVC.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Environment_thread_test.debug.exe" /libpath:"$(PTHREADS_WIN32)"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "environment_thread_test - Win32 Debug setenv"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Win32_Debug_setenv"
# PROP BASE Intermediate_Dir "Win32_Debug_setenv"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Win32_Debug_setenv"
# PROP Intermediate_Dir "Win32_Debug_setenv"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "$(STLSOFT)/include" /I "$(PTHREADS_WIN32)" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /GZ /c
# ADD CPP /nologo /Ze /W3 /Gm /GX /Zi /Od /I "$(STLSOFT)/include" /I "$(PTHREADS_WIN32)" /I "$(UNIXEM)/include" /D "_DEBUG" /D "unix" /D "WIN32" /D "STRICT" /D "_CONSOLE" /D "PLATFORMSTL_ENVMAP_ERASE_BY_SETENV" /D "_STLSOFT_FORCE_ANY_COMPILER" /D "__SVR4" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 pthreadVC.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Environment_thread_test.debug.exe" /pdbtype:sept /libpath:"$(PTHREADS_WIN32)"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 pthreadVC.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Environment_thread_test.debug.exe" /pdbtype:sept /libpath:"$(PTHREADS_WIN32)" /libpath:"$(UNIXEM)/lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "environment_thread_test - Win32 Release setenv"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Win32_Release_setenv"
# PROP BASE Intermediate_Dir "Win32_Release_setenv"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win32_Release_setenv"
# PROP Intermediate_Dir "Win32_Release_setenv"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "$(STLSOFT)/include" /I "$(PTHREADS_WIN32)" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "$(STLSOFT)/include" /I "$(PTHREADS_WIN32)" /I "$(UNIXEM)/include" /D "NDEBUG" /D "unix" /D "WIN32" /D "STRICT" /D "_CONSOLE" /D "PLATFORMSTL_ENVMAP_ERASE_BY_SETENV" /D "_STLSOFT_FORCE_ANY_COMPILER" /D "__SVR4" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 pthreadVC.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Environment_thread_test.debug.exe" /libpath:"$(PTHREADS_WIN32)"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 pthreadVC.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Environment_thread_test.debug.exe" /libpath:"$(PTHREADS_WIN32)" /libpath:"$(UNIXEM)/lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "environment_thread_test - Win32 Debug _putenv equal"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Win32_Debug__putenv_equal"
# PROP BASE Intermediate_Dir "Win32_Debug__putenv_equal"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Win32_Debug__putenv_equal"
# PROP Intermediate_Dir "Win32_Debug__putenv_equal"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /I "$(STLSOFT)/include" /I "$(PTHREADS_WIN32)" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(STLSOFT)/include" /I "$(PTHREADS_WIN32)" /D "_DEBUG" /D "WIN32" /D "STRICT" /D "_CONSOLE" /D "PLATFORMSTL_ENVMAP_ERASE_BY_PUTENV_EQUAL" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 pthreadVC.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Environment_thread_test.debug.exe" /pdbtype:sept /libpath:"$(PTHREADS_WIN32)"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 pthreadVC.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Environment_thread_test.debug.exe" /pdbtype:sept /libpath:"$(PTHREADS_WIN32)"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "environment_thread_test - Win32 Release _putenv equal"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Win32_Release__putenv_equal"
# PROP BASE Intermediate_Dir "Win32_Release__putenv_equal"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Win32_Release__putenv_equal"
# PROP Intermediate_Dir "Win32_Release__putenv_equal"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "$(STLSOFT)/include" /I "$(PTHREADS_WIN32)" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "$(STLSOFT)/include" /I "$(PTHREADS_WIN32)" /D "NDEBUG" /D "WIN32" /D "STRICT" /D "_CONSOLE" /D "PLATFORMSTL_ENVMAP_ERASE_BY_PUTENV_EQUAL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 pthreadVC.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Environment_thread_test.debug.exe" /libpath:"$(PTHREADS_WIN32)"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 pthreadVC.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Environment_thread_test.debug.exe" /libpath:"$(PTHREADS_WIN32)"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "environment_thread_test - Win32 Debug none"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "environment_thread_test___Win32_Debug_none"
# PROP BASE Intermediate_Dir "environment_thread_test___Win32_Debug_none"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "environment_thread_test___Win32_Debug_none"
# PROP Intermediate_Dir "environment_thread_test___Win32_Debug_none"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(STLSOFT)/include" /I "$(PTHREADS_WIN32)" /D "_DEBUG" /D "WIN32" /D "STRICT" /D "_CONSOLE" /D "PLATFORMSTL_ENVMAP_ERASE_BY_PUTENV" /FR /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(STLSOFT)/include" /I "$(PTHREADS_WIN32)" /D "_DEBUG" /D "WIN32" /D "STRICT" /D "_CONSOLE" /D "PLATFORMSTL_ENVVAR_STDC_ONLY" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 pthreadVC.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Environment_thread_test.debug.exe" /pdbtype:sept /libpath:"$(PTHREADS_WIN32)"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 pthreadVC.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Environment_thread_test.debug.exe" /pdbtype:sept /libpath:"$(PTHREADS_WIN32)"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "environment_thread_test - Win32 Release none"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "environment_thread_test___Win32_Release_none"
# PROP BASE Intermediate_Dir "environment_thread_test___Win32_Release_none"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "environment_thread_test___Win32_Release_none"
# PROP Intermediate_Dir "environment_thread_test___Win32_Release_none"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "$(STLSOFT)/include" /I "$(PTHREADS_WIN32)" /D "NDEBUG" /D "WIN32" /D "STRICT" /D "_CONSOLE" /D "PLATFORMSTL_ENVMAP_ERASE_BY_PUTENV" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "$(STLSOFT)/include" /I "$(PTHREADS_WIN32)" /D "NDEBUG" /D "WIN32" /D "STRICT" /D "_CONSOLE" /D "PLATFORMSTL_ENVVAR_STDC_ONLY" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 pthreadVC.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Environment_thread_test.debug.exe" /libpath:"$(PTHREADS_WIN32)"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 pthreadVC.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Environment_thread_test.debug.exe" /libpath:"$(PTHREADS_WIN32)"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "environment_thread_test - Win32 Debug _putenv"
# Name "environment_thread_test - Win32 Release _putenv"
# Name "environment_thread_test - Win32 Debug setenv"
# Name "environment_thread_test - Win32 Release setenv"
# Name "environment_thread_test - Win32 Debug _putenv equal"
# Name "environment_thread_test - Win32 Release _putenv equal"
# Name "environment_thread_test - Win32 Debug none"
# Name "environment_thread_test - Win32 Release none"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\environment_thread_test.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "STLSoft Header Files"

# PROP Default_Filter ""
# Begin Group "STLSoft"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\util\std\algorithm.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\allocator_base.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\allocator_selector.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\array_policies.hpp"
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

SOURCE="$(STLSOFT)\include\stlsoft\meta\is_function_pointer_type.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\iterator.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\util\std\library_discriminator.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\meta.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\meta\n_types.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\null_allocator.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\algorithms\pod.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\sap_cast.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\scoped_handle.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\shared_ptr.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\sign_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\size_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\static_array.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\util\std_swap.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft_cccap_msvc.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft_meta.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft_null_allocator.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\string_access.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\string_access_fwd.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\string_split_functions.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\string_view.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\type_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\meta\yesno.hpp"
# End Source File
# End Group
# Begin Group "PlatformSTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT)\include\platformstl\environment_map.hpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.8.x\STLSoft\include\platformstl\environment_variable_traits.hpp
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\platformstl\platformstl.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\platformstl\platformstl.hpp"
# End Source File
# End Group
# Begin Group "WinSTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT)\include\winstl.h"
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE="P:\sdks\pthreads-win32\pthreads-snap-2003-09-18\include\pthread.h"
# End Source File
# Begin Source File

SOURCE="P:\sdks\pthreads-win32\pthreads-snap-2003-09-18\include\sched.h"
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
