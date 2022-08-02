icl -nologo -DNDEBUG -DITERATIONS=175000 -DxUSE_STRINGS -I%STLSOFT% -I%BOOST_INCLUDE% -Ox -O2 -Ob2 -GS -G7 -Festatic_array_test_icl.exe   ..\static_array_test.cpp
icl -nologo -DNDEBUG -DITERATIONS=100000  -DUSE_STRINGS  -I%STLSOFT% -I%BOOST_INCLUDE% -Ox -O2 -Ob2 -GS -G7 -Festatic_array_test_icl_s.exe ..\static_array_test.cpp
