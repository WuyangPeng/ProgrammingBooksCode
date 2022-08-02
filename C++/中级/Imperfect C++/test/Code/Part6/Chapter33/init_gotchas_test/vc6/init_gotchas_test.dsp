# Microsoft Developer Studio Project File - Name="init_gotchas_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=init_gotchas_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "init_gotchas_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "init_gotchas_test.mak" CFG="init_gotchas_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "init_gotchas_test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "init_gotchas_test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "init_gotchas_test - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "$(STLSOFT_INCLUDE)\\" /I "$(BOOST_INCLUDE)\\" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "NDEBUG"
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "init_gotchas_test - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "$(STLSOFT_INCLUDE)\\" /I "$(BOOST_INCLUDE)\\" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /FR /YX /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc09 /d "_DEBUG"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /version:1.0 /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "init_gotchas_test - Win32 Release"
# Name "init_gotchas_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\init_gotchas_test.cpp
DEP_CPP_INIT_=\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft__undefs.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_allocator_base.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_array_policies.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cc_obsolete.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_borland.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_como.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_dmc.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_gcc.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_intel.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_msvc.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_mwerks.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_unknown.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_vectorc.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_watcom.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_fixed_array.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_iterator.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_meta.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_new_allocator.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_null_allocator.h"\
	"..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_static_array.h"\
	"P:\sdks\boost\boost_1_30_0\boost\array.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\call_traits.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\checked_delete.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\compressed_pair.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\concept_check.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\config.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\config\posix_features.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\config\select_compiler_config.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\config\select_platform_config.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\config\select_stdlib_config.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\config\suffix.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\detail\call_traits.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\detail\compressed_pair.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\detail\iterator.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\detail\limits.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\detail\ob_call_traits.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\detail\ob_compressed_pair.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\detail\select_type.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\detail\workaround.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\functional.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\iterator.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\iterator_adaptors.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\limits.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\algorithm_namespace.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\arity.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\dtp.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\eti.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\lambda.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\msvc.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\msvc_typename.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\nttp.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\overload_resolution.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\preprocessor.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\static_constant.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\ttp.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\workaround.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\has_xxx.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\ice_cast.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\integral_wrapper.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\lambda_arity_param.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\lambda_support.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\preprocessor\def_params_tail.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\preprocessor\enum.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\preprocessor\filter_params.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\preprocessor\params.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\preprocessor\sub.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\preprocessor\tuple.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\template_arity_fwd.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\type_wrapper.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\value_wknd.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\void_spec.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\yes_no.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\bool.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\bool_fwd.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\if.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\int.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\int_fwd.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\lambda_fwd.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\limits\arity.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\size_t.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\size_t_fwd.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\mpl\void.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\algorithm.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\base.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\collection_concept.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\concept_checks.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\copy_array.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\extent_gen.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\extent_range.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\index_gen.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\index_range.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\iterator.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\iterator_adaptors.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\multi_array_ref.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\range_list.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\storage_order.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\subarray.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\types.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\multi_array\view.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\next_prior.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\noncopyable.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\arithmetic\add.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\arithmetic\inc.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\arithmetic\sub.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\cat.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\comma_if.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\config\config.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\control\detail\edg\while.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\control\detail\msvc\while.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\control\detail\while.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\control\iif.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\control\while.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\debug\error.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\detail\auto_rec.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\detail\check.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\detail\is_binary.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\empty.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\enum_params.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\identity.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\inc.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\iterate.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\adt.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\detail\edg\fold_left.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\detail\edg\fold_right.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\detail\fold_left.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\detail\fold_right.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\fold_left.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\fold_right.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\for_each_i.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\reverse.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\logical\and.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\logical\bitand.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\logical\bool.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\logical\compl.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\repeat.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\repetition\detail\edg\for.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\repetition\detail\for.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\repetition\detail\msvc\for.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\repetition\for.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\tuple\eat.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\tuple\elem.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\tuple\rem.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\preprocessor\tuple\to_list.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\static_assert.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\add_const.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\add_cv.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\add_pointer.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\add_reference.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\add_volatile.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\alignment_of.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\arithmetic_traits.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\broken_compiler_spec.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\composite_traits.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\config.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\conversion_traits.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\bool_trait_def.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\bool_trait_undef.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\cv_traits_impl.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\false_result.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\ice_and.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\ice_eq.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\ice_not.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\ice_or.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\is_function_ptr_helper.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\is_function_ptr_tester.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\is_function_type_tester.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\is_mem_fun_pointer_impl.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\is_mem_fun_pointer_tester.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\size_t_trait_def.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\size_t_trait_undef.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\template_arity_spec.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\type_trait_def.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\type_trait_undef.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\wrap.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\yes_no_type.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\has_nothrow_assign.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\has_nothrow_constructor.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\has_nothrow_copy.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\has_nothrow_destructor.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\has_trivial_assign.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\has_trivial_constructor.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\has_trivial_copy.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\has_trivial_destructor.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\ice.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\intrinsics.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_arithmetic.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_array.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_base_and_derived.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_class.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_compound.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_const.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_convertible.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_empty.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_enum.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_float.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_function.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_fundamental.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_integral.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_member_function_pointer.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_member_pointer.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_object.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_pod.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_pointer.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_polymorphic.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_reference.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_same.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_scalar.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_stateless.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_union.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_void.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\is_volatile.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\object_traits.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\remove_bounds.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\remove_const.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\remove_cv.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\remove_pointer.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\remove_reference.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\remove_volatile.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\same_traits.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\type_traits\type_with_alignment.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\utility.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\utility\addressof.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\utility\base_from_member.hpp"\
	"P:\sdks\boost\boost_1_30_0\boost\utility_fwd.hpp"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Boost Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\arithmetic\add.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\add_const.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\add_cv.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\add_pointer.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\add_reference.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\add_volatile.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\utility\addressof.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\adt.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\algorithm.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\algorithm_namespace.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\alignment_of.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\logical\and.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\arithmetic_traits.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\arity.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\limits\arity.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\array.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\detail\auto_rec.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\base.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\utility\base_from_member.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\logical\bitand.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\bool.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\logical\bool.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\bool_fwd.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\bool_trait_def.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\bool_trait_undef.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\broken_compiler_spec.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\call_traits.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\detail\call_traits.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\cat.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\detail\check.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\checked_delete.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\collection_concept.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\punctuation\comma.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\comma_if.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\punctuation\comma_if.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\logical\compl.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\composite_traits.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\compressed_pair.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\detail\compressed_pair.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\concept_check.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\concept_checks.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\config.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\config\config.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\config.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\conversion_traits.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\copy_array.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\cv_traits_impl.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\preprocessor\def_params_tail.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\config\stdlib\dinkumware.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\dtp.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\tuple\eat.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\tuple\elem.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\empty.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\facilities\empty.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\preprocessor\enum.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\enum_params.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\debug\error.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\eti.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\extent_gen.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\extent_range.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\false_result.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\preprocessor\filter_params.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\detail\edg\fold_left.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\detail\fold_left.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\fold_left.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\detail\edg\fold_right.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\detail\fold_right.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\fold_right.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\repetition\detail\edg\for.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\repetition\detail\for.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\repetition\detail\msvc\for.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\repetition\for.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\for_each_i.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\functional.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\has_nothrow_assign.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\has_nothrow_constructor.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\has_nothrow_copy.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\has_nothrow_destructor.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\has_trivial_assign.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\has_trivial_constructor.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\has_trivial_copy.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\has_trivial_destructor.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\has_xxx.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\ice.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\ice_and.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\ice_cast.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\ice_eq.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\ice_not.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\ice_or.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\facilities\identity.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\identity.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\if.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\control\if.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\control\iif.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\arithmetic\inc.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\inc.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\index_gen.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\index_range.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\int.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\int_fwd.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\integral_wrapper.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\intrinsics.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_arithmetic.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_array.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_base_and_derived.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\detail\is_binary.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_class.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_compound.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_const.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_convertible.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_empty.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_enum.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_float.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_function.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\is_function_ptr_helper.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\is_function_ptr_tester.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\is_function_type_tester.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_fundamental.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_integral.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\is_mem_fun_pointer_impl.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\is_mem_fun_pointer_tester.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_member_function_pointer.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_member_pointer.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_object.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_pod.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_pointer.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_polymorphic.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_reference.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_same.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_scalar.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_stateless.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_union.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_void.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\is_volatile.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\iterate.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\detail\iterator.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\iterator.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\iterator.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\iterator_adaptors.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\iterator_adaptors.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\lambda.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\lambda_arity_param.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\lambda_fwd.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\lambda_support.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\detail\limits.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\limits.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\msvc.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\msvc_typename.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\multi_array_ref.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\next_prior.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\noncopyable.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\nttp.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\detail\ob_call_traits.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\detail\ob_compressed_pair.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\object_traits.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\overload_resolution.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\preprocessor\params.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\config\posix_features.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\preprocessor.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\range_list.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\tuple\rem.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\remove_bounds.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\remove_const.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\remove_cv.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\remove_pointer.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\remove_reference.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\remove_volatile.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\repeat.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\list\reverse.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\same_traits.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\config\select_compiler_config.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\config\select_platform_config.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\config\select_stdlib_config.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\detail\select_type.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\size_t.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\size_t_fwd.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\size_t_trait_def.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\size_t_trait_undef.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\static_assert.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\static_constant.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\storage_order.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\preprocessor\sub.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\arithmetic\sub.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\subarray.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\config\suffix.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\template_arity_fwd.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\template_arity_spec.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\tuple\to_list.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\ttp.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\preprocessor\tuple.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\type_trait_def.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\type_trait_undef.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\type_with_alignment.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\type_wrapper.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\types.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\config\user.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\utility.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\utility_fwd.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\value_wknd.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\multi_array\view.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\config\compiler\visualc.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\void.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\void_spec.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\control\detail\edg\while.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\control\detail\msvc\while.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\control\detail\while.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\preprocessor\control\while.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\config\platform\win32.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\detail\workaround.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\config\workaround.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\wrap.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\mpl\aux_\yes_no.hpp
# End Source File
# Begin Source File

SOURCE=P:\sdks\boost\boost_1_30_0\boost\type_traits\detail\yes_no_type.hpp
# End Source File
# End Group
# Begin Group "STLSoft Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft__undefs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_allocator_base.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_array_policies.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_auto_buffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cc_obsolete.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_borland.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_como.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_dmc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_gcc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_intel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_msvc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_mwerks.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_unknown.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_vectorc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_watcom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_char_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_constraints.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_fixed_array.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_integer_to_string.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_iterator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_limit_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_meta.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_new_allocator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_null_allocator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_sign_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_simple_algorithms.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_simple_string.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_size_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_static_array.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_static_initialisers.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_type_traits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl_performance_counter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\winstl_processheap_allocator.h
# End Source File
# End Group
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
