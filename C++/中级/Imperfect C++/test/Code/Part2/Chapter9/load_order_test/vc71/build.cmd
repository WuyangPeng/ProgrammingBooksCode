@echo off
cl -c -nologo -MD -Foload_order_1.obj ..\load_order_1.cpp
cl -c -nologo -MD -Foload_order_2.obj ..\load_order_2.cpp
cl -c -nologo -MD -Foload_order_test.obj ..\load_order_test.cpp
link -nologo -dll -implib:load_order_1.lib -out:load_order_1.dll load_order_1.obj
link -nologo -dll -implib:load_order_2.lib -out:load_order_2.dll load_order_2.obj
link -nologo load_order_test.obj load_order_2.lib load_order_1.lib
dir
