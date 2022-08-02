// (c) Bartosz Milewski 2000
#include "Ctrl.h"
#include "Class.h"
#include "Maker.h"
#include "Window.h"
#include "Resource.h"

int WINAPI WinMain
	(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdParam, int cmdShow)
{
	try
	{
		char className [] = "SymCalcClass";
		Win::ClassMaker winClass (className, hInst);
		winClass.SetIcons (IDI_MAIN);
		winClass.Register ();
		Win::Maker maker (className, hInst);
		TopController ctrl;
		Win::Dow win = maker.Create (ctrl, "Symbolic Calculator");
		win.Display (cmdShow);
	
		MSG  msg;
		int status;
		while ((status = ::GetMessage (& msg, 0, 0, 0)) != 0)
		{
			if (status == -1)
				return -1;
			::TranslateMessage (& msg);
			::DispatchMessage (& msg);
		}
		return msg.wParam;
	}
	catch (char const * msg)
	{
		::MessageBox (0, msg, "Internal error", MB_OK | MB_ICONERROR);
	}
	catch (...)
	{
		::MessageBox (0, "Unknown", "Internal error", MB_OK | MB_ICONERROR);
	}
	return 1;
}
