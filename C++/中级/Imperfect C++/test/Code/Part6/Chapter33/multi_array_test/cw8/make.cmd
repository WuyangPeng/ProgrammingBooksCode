mwcc -w nonotused -DITERATIONS=100000 -DxUSE_STRINGS -DNDEBUG -opt full -proc Pentium4 -I- -IH:\STLSoft\Identities\STLSoft\stlsoft -I%BOOST_INCLUDE% -o multi_array_test_cw.exe   ..\multi_array_test.cpp
mwcc -w nonotused -DITERATIONS=75000  -DUSE_STRINGS  -DNDEBUG -opt full -proc Pentium4 -I- -IH:\STLSoft\Identities\STLSoft\stlsoft -I%BOOST_INCLUDE% -o multi_array_test_cw_s.exe ..\multi_array_test.cpp
