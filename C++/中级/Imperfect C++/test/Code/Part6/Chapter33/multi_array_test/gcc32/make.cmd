g++ -DITERATIONS=100000 -DxUSE_STRINGS -DNDEBUG -IH:\STLSoft\Identities\STLSoft\stlsoft -I%BOOST_INCLUDE% -O7 -mcpu=i686 -omulti_array_test_gcc.exe   ..\multi_array_test.cpp
g++ -DITERATIONS=75000  -DUSE_STRINGS  -DNDEBUG -IH:\STLSoft\Identities\STLSoft\stlsoft -I%BOOST_INCLUDE% -O7 -mcpu=i686 -omulti_array_test_gcc_s.exe ..\multi_array_test.cpp
