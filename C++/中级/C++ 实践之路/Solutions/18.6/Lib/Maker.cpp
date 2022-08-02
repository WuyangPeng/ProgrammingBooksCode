#include "Maker.h"
// Bartosz Milewski (c) 2000

using namespace Win;

Maker::Maker (char const * className, HINSTANCE hInst)
  : _style (WS_OVERLAPPEDWINDOW),
	_exStyle (0),
	_className (className),
	_x (CW_USEDEFAULT),		// horizontal position
	_y (0),					// vertical position
	_width (CW_USEDEFAULT),	// window width 
	_height (0),			// window height
	_hWndParent (0),		// parent or owner window
	_hMenu (0),				// menu, or child-window identifier
	_data (0),				// window-creation data
	_hInst (hInst)
{}

HWND Maker::Create (Win::Controller & ctrl, char const * title)
{
	HWND hwnd = ::CreateWindowEx (
		_exStyle,
		_className,
		title,
		_style,
		_x,
		_y,
		_width,
		_height,
		_hWndParent,
		_hMenu,
		_hInst,
		&ctrl);

	if (hwnd == 0)
		throw "Window Creation Failed";
	return hwnd;
}

ChildMaker::ChildMaker (char const * className, Win::Dow winParent, int childId)
    : Maker (className, winParent.GetInstance ())
{
    _style = WS_CHILD;
    _hWndParent = winParent;
    _hMenu = reinterpret_cast<HMENU> (childId);
}

HWND ChildMaker::Create (char const * text)
{
	HWND win = ::CreateWindowEx (
		_exStyle,
		_className,
		text,
		_style,
		_x,
		_y,
		_width,
		_height,
		_hWndParent,
		_hMenu,
		_hInst,
		0);

	if (win == 0)
		throw "Internal error: Child Window Creation Failed.";
	return win;
}

