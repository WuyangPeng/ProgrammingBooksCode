# Microsoft Developer Studio Project File - Name="pod_vector_speed_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=pod_vector_speed_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pod_vector_speed_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pod_vector_speed_test.mak" CFG="pod_vector_speed_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pod_vector_speed_test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "pod_vector_speed_test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pod_vector_speed_test - Win32 Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "$(STLSOFT_INCLUDE)\\" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /YX /c
# SUBTRACT CPP /Z<none>
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /version:1.0 /subsystem:console /map /machine:I386

!ELSEIF  "$(CFG)" == "pod_vector_speed_test - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "$(STLSOFT_INCLUDE)\\" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /GZ /c
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

# Name "pod_vector_speed_test - Win32 Release"
# Name "pod_vector_speed_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\pod_vector_speed_test.cpp
DEP_CPP_POD_V=\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_64bit_integers.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft__undefs.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_allocator_base.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_auto_buffer.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cc_obsolete.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_borland.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_como.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_dmc.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_gcc.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_intel.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_msvc.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_mwerks.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_unknown.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_vectorc.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_watcom.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_constraints.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_iterator.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_limit_traits.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_malloc_allocator.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_meta.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_pod_vector.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_simple_algorithms.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_static_initialisers.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_type_traits.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\unixstl.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\unixstl_performance_counter.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl.h"\
	"..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl_performance_counter.h"\
	

!IF  "$(CFG)" == "pod_vector_speed_test - Win32 Release"

!ELSEIF  "$(CFG)" == "pod_vector_speed_test - Win32 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_64bit_integers.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft__undefs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_allocator_base.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_auto_buffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cc_obsolete.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_borland.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_como.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_dmc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_gcc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_intel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_msvc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_mwerks.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_unknown.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_vectorc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_watcom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_constraints.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_iterator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_limit_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_malloc_allocator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_meta.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_pod_vector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_simple_algorithms.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_static_initialisers.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_type_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\unixstl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\unixstl_performance_counter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl_performance_counter.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
