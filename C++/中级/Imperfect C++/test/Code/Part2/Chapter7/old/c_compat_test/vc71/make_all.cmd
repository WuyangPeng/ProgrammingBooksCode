
@echo vc71 from bc56
@cl -nologo c_compat_test.obj ..\bc56\c_compat.obj -Fecc_vc71_from_bc56.exe
@echo vc71 from cw8
@cl -nologo c_compat_test.obj ..\cw8\c_compat.obj -Fecc_vc71_from_cw8.exe
@echo vc71 from dmbeta
@cl -nologo c_compat_test.obj ..\dmbeta\c_compat.obj -Fecc_vc71_from_dmbeta.exe
@echo vc71 from icl7
@cl -nologo c_compat_test.obj ..\icl7\c_compat.obj -Fecc_vc71_from_icl7.exe
