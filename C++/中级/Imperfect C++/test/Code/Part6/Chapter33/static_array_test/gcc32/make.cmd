g++ -O7 -mcpu=i686 -DNDEBUG -DITERATIONS=175000 -DxUSE_STRINGS -IH:\STLSoft\Identities\STLSoft\stlsoft -Ip:\sdks\boost\boost_1_30_0 -o static_array_test_gcc.exe   ..\static_array_test.cpp 
g++ -O7 -mcpu=i686 -DNDEBUG -DITERATIONS=100000  -DUSE_STRINGS  -IH:\STLSoft\Identities\STLSoft\stlsoft -Ip:\sdks\boost\boost_1_30_0 -o static_array_test_gcc_s.exe ..\static_array_test.cpp 
