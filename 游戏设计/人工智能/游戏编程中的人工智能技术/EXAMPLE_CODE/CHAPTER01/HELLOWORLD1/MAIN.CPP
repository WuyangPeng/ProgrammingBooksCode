#include <windows.h>

//-----------------------------------------------------------------------
//  
//  Name: HelloWorld example project
//  
//  Author: Mat Buckland 2002
//
//  Desc: HelloWorld in a dialogue box
//
//------------------------------------------------------------------------

int WINAPI WinMain(	HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int nCmdShow)
{
    MessageBox(NULL, "Hello World!", "MsgBox", 0);
    
	return 0;
}