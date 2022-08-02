#include "Output.h"
// Bartosz Milewski (c) 2000

Output TheOutput;

void Output::Error (char const * str)
{
	::MessageBox (_win, str, "WinCalc Error", MB_OK | MB_ICONERROR);
}

