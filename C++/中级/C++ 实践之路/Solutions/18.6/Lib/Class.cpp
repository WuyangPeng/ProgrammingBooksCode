#include "Class.h"
// Bartosz Milewski (c) 2000
#include "Procedure.h"

Win::ClassMaker::ClassMaker (char const * className, HINSTANCE hInst)
{
	_class.lpfnWndProc = Win::Procedure;// mandatory
	_class.hInstance = hInst;         // mandatory
	_class.lpszClassName = className; // mandatory
	_class.cbSize = sizeof (WNDCLASSEX);
	_class.hCursor = ::LoadCursor (0, IDC_ARROW);
	_class.hbrBackground = reinterpret_cast<HBRUSH> (COLOR_WINDOW + 1);
	_class.style = 0;
	_class.cbClsExtra = 0;
	_class.cbWndExtra = 0;
	_class.hIcon = 0;
	_class.hIconSm = 0;
	_class.lpszMenuName = 0;
}

void Win::ClassMaker::SetIcons (int id)
{
	_stdIcon.Load (_class.hInstance, id);
	_smallIcon.Load (_class.hInstance, id);
	_class.hIcon = _stdIcon;
	_class.hIconSm = _smallIcon;
}

void Win::ClassMaker::SetBkColor (int r, int g, int b)
{
	_class.hbrBackground = ::CreateSolidBrush (RGB (r, g, b));
}