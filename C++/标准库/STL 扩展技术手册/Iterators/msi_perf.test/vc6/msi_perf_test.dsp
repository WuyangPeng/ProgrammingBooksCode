# Microsoft Developer Studio Project File - Name="msi_perf_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=msi_perf_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "msi_perf_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "msi_perf_test.mak" CFG="msi_perf_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "msi_perf_test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "msi_perf_test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "msi_perf_test - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "$(STLSOFT)/include" /D "WIN32" /D "NDEBUG" /D "_STLSOFT_FORCE_ANY_COMPILER" /D "STRICT" /D "_CONSOLE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /machine:I386 /out:"Release/Msi_perf_test.debug.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "msi_perf_test - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(STLSOFT)/include" /D "WIN32" /D "_DEBUG" /D "_STLSOFT_FORCE_ANY_COMPILER" /D "STRICT" /D "_CONSOLE" /YX /FD /GZ  /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /map /debug /machine:I386 /out:"Debug/Msi_perf_test.debug.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "msi_perf_test - Win32 Release"
# Name "msi_perf_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\msi_perf_test.cpp
# End Source File
# Begin Source File

SOURCE=..\slice_fn.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\memory\allocator_features.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\memory\allocator_selector.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\algorithms\std\alt.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\memory\auto_buffer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\meta\capabilities.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\collections\util\collections.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\util\constraints.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\meta\is_const_type.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\util\std\iterator_helper.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\util\std\library_discriminator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\iterators\member_selector_iterator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\meta\util\meta_.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\internal\cccap\msvc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\meta\n_types.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\platformstl\platformstl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\platformstl\platformstl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\algorithms\pod.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\meta\size_of.hpp
# End Source File
# Begin Source File

SOURCE=..\slice.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\util\std_swap.hpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\stlsoft.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\winstl\winstl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\STLSoft\Releases\current\STLSoft\include\stlsoft\meta\yesno.hpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
