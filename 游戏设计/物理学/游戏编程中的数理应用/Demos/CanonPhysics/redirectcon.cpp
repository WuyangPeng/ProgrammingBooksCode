#include "redirectcon.h"

#include <windows.h>
#include <io.h>
#include <fcntl.h>

#include <iostream>
using namespace std;

#define MAX_CONSOLE_LINES 250;

void con::RedirectIOToConsole(const char *title)
{
	int hConHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;

	// Allocate a console for this app
	AllocConsole();

	// Set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

	// Redirect unbuffered STDOUT to the console	
	hConHandle = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);

	// Set the console title.
	SetConsoleTitle(title);

	ios::sync_with_stdio();
}
