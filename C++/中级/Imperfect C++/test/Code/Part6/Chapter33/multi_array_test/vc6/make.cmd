cl -DITERATIONS=100000 -DxUSE_STRINGS -DNDEBUG -EHsc -Ox -O2 -nologo -Ob2 -G6 -I%BOOST_INCLUDE% -Femulti_array_test_vc6.exe   ..\multi_array_test.cpp
cl -DITERATIONS=75000  -DUSE_STRINGS  -DNDEBUG -EHsc -Ox -O2 -nologo -Ob2 -G6 -I%BOOST_INCLUDE% -Femulti_array_test_vc6_s.exe ..\multi_array_test.cpp
