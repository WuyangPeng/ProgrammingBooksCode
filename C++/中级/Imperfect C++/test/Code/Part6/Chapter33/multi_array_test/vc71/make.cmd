cl -DITERATIONS=100000 -DxUSE_STRINGS -DNDEBUG -EHsc -Ox -O2 -nologo -Ob2 -GL -G7 -Ip:\sdks\boost\boost_1_30_0 -Femulti_array_test_vc71.exe   ..\multi_array_test.cpp 
cl -DITERATIONS=75000  -DUSE_STRINGS  -DNDEBUG -EHsc -Ox -O2 -nologo -Ob2 -GL -G7 -Ip:\sdks\boost\boost_1_30_0 -Femulti_array_test_vc71_s.exe ..\multi_array_test.cpp 
