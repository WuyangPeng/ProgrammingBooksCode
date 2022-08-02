icl -DNDEBUG -DITERATIONS=100000 -DxUSE_STRINGS -Ox -O2 -nologo -Ob2 -GS -G7 -I%BOOST_INCLUDE% -Femulti_array_test_icl.exe   ..\multi_array_test.cpp
icl -DNDEBUG -DITERATIONS=75000  -DUSE_STRINGS  -Ox -O2 -nologo -Ob2 -GS -G7 -I%BOOST_INCLUDE% -Femulti_array_test_icl_s.exe ..\multi_array_test.cpp
