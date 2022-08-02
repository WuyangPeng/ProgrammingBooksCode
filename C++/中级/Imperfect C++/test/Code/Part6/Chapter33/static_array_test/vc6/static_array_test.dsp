# Microsoft Developer Studio Project File - Name="static_array_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=static_array_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "static_array_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "static_array_test.mak" CFG="static_array_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "static_array_test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "static_array_test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "static_array_test - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "$(STLSOFT_INCLUDE)\\" /I "$(BOOST_INCLUDE)\\" /D "WIN32" /D "NDEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /c
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

!ELSEIF  "$(CFG)" == "static_array_test - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "$(STLSOFT_INCLUDE)\\" /I "$(BOOST_INCLUDE)\\" /D "WIN32" /D "_DEBUG" /D "STRICT" /D "_CONSOLE" /YX /FD /GZ /c
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

# Name "static_array_test - Win32 Release"
# Name "static_array_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\static_array_test.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Boost Header Files"

# PROP Default_Filter ""
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

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_allocator_base.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_array_policies.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_auto_buffer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_cccap_msvc.h
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

SOURCE=..\..\..\..\..\..\..\..\..\STLSoft\Identities\STLSoft\stlsoft\stlsoft_frame_array.h
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
