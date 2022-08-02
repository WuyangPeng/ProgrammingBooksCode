# Microsoft Developer Studio Project File - Name="scatter_slice_sequence_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=scatter_slice_sequence_test - Win32 Debug pseudoUNIX
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "scatter_slice_sequence_test.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "scatter_slice_sequence_test.mak" CFG="scatter_slice_sequence_test - Win32 Debug pseudoUNIX"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "scatter_slice_sequence_test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "scatter_slice_sequence_test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "scatter_slice_sequence_test - Win32 Debug pseudoUNIX" (based on "Win32 (x86) Application")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe


!IF  "$(CFG)" == "scatter_slice_sequence_test - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "$(STLSOFT)/include" /I "$(STLSOFT_1_10)/include" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib ws2_32.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Scatter_vector_test.debug.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "scatter_slice_sequence_test - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(STLSOFT)/include" /I "$(STLSOFT_1_10)/include" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib ws2_32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Scatter_vector_test.debug.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "scatter_slice_sequence_test - Win32 Debug pseudoUNIX"

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
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(UNIXEM)/include" /I "$(STLSOFT)/include" /I "$(STLSOFT_1_10)/include" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /D "unix" /D "_STLSOFT_FORCE_ANY_COMPILER" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Scatter_vector_test.debug.exe" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib ws2_32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"DebugUNIX/Scatter_vector_test.debug.exe" /pdbtype:sept /libpath:"$(UNIXEM)/lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF

# Begin Target

# Name "scatter_slice_sequence_test - Win32 Release"
# Name "scatter_slice_sequence_test - Win32 Debug"
# Name "scatter_slice_sequence_test - Win32 Debug pseudoUNIX"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\scatter_slice_sequence_test.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "STLSoft Header Files"

# PROP Default_Filter ""
# Begin Group "STLSoft"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\algorithms.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\memory\allocator_base.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\memory\allocator_features.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\memory\allocator_selector.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\algorithms\std\alt.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\memory\auto_buffer.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\shims\access\string\std\basic_string.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\algorithms\bounded.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\shims\access\string\std\c_string.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\meta\capabilities.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\string\char_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\algorithms\collection.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\collections\util\collections.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\util\constraints.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\string\copy_functions.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\algorithms\debug.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\algorithms\deprecated.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\shims\access\string\std\exception.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\util\exception_string.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\error\exceptions.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\algorithms\std\ext.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\shims\access\string\fwd.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\meta\is_const_type.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\util\std\iterator_helper.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\util\std\library_discriminator.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\iterators\member_selector_iterator.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\meta\util\meta_.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\internal\cccap\msvc.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\meta\n_types.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\algorithms\pod.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\conversion\sap_cast.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\util\sign_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\meta\size_of.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\util\size_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\util\std_swap.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\stlsoft.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\shims\access\string.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\algorithms\unordered.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\stlsoft\meta\yesno.hpp"
# End Source File
# End Group
# Begin Group "PlatformSTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT)\include\platformstl\filesystem\path.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\platformstl\platformstl.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\platformstl\platformstl.hpp"
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.10\STLSoft\include\platformstl\shims\attribute\scatter_slice.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\1.10\STLSoft\include\platformstl\scatter_slice_sequence_2.hpp
# End Source File
# End Group
# Begin Group "UNIXSTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT)\include\unixstl\shims\access\string\dirent.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\unixstl\filesystem\file_path_buffer.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\unixstl\filesystem\filesystem_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\unixstl\filesystem\path.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\unixstl\shims\access\string.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\unixstl\system\system_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\unixstl\unixstl.h"
# End Source File
# End Group
# Begin Group "WinSTL"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(STLSOFT)\include\winstl\error\error_functions.h"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\winstl\error\exceptions.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\winstl\filesystem\file_path_buffer.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\winstl\filesystem\filesystem_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\winstl\filesystem\path.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\winstl\memory\processheap_allocator.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\winstl\system\system_traits.hpp"
# End Source File
# Begin Source File

SOURCE="$(STLSOFT)\include\winstl\winstl.h"
# End Source File
# End Group
# End Group
# Begin Group "UNIXEm Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="$(UNIXEM)\include\dirent.h"
# End Source File
# Begin Source File

SOURCE="$(UNIXEM)\include\dlfcn.h"
# End Source File
# Begin Source File

SOURCE="$(UNIXEM)\include\unixem\implicit_link.h"
# End Source File
# Begin Source File

SOURCE="$(UNIXEM)\include\sys\uio.h"
# End Source File
# Begin Source File

SOURCE="$(UNIXEM)\include\unistd.h"
# End Source File
# Begin Source File

SOURCE="$(UNIXEM)\include\unixem\unixem.h"
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
