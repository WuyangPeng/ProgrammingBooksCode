#include "MsgLoop.h"
// (c) Bartosz Milewski 2000
#include "Exception.h"

using namespace Win;

void MsgPrepro::RemoveDialogFilter (HWND hDlg)
{
	_dlgList.remove (hDlg);
}

int MsgPrepro::Pump ()
{
    MSG  msg;
	int status;
    while ((status = ::GetMessage (&msg, 0, 0, 0 )) != 0)
    {
		if (status == -1)
			throw Exception ("Error in the Windows message loop");
		DlgIter it;
		for (it = _dlgList.begin (); it != _dlgList.end (); ++it)
		{
			if (::IsDialogMessage (*it, &msg))
				break;
		}
		if (it == _dlgList.end ())
		{
			if (_hAccel == 0 || !::TranslateAccelerator (_winTop, _hAccel, &msg))
			{
				::TranslateMessage (&msg);
				::DispatchMessage (&msg);
			}
		}
    }
    return msg.wParam;
}

// Peek at the queue and process any messages
void MsgPrepro::PumpPeek ()
{
    MSG  msg;
	int status;
    while ((status = ::PeekMessage (&msg, 0, 0, 0, PM_REMOVE)) != 0)
    {
		if (status == -1)
			throw Exception ("Error in the Windows peek message loop");
		DlgIter it;
		for (it = _dlgList.begin (); it != _dlgList.end (); ++it)
		{
			if (::IsDialogMessage (*it, &msg))
				break;
		}
		if (it == _dlgList.end ())
		{
			if (_hAccel == 0 || !::TranslateAccelerator (_winTop, _hAccel, &msg))
			{
				::TranslateMessage (&msg);
				::DispatchMessage (&msg);
			}
		}
    }
}

// Peek at the queue and process only messages
// to the specified window. Don't translate accellerators
void MsgPrepro::PumpWindow (HWND win)
{
    MSG  msg;
	int status;
    while ((status = ::PeekMessage (&msg, win, 0, 0, PM_REMOVE )) != 0)
    {
		if (status == -1)
			throw Exception ("Error in the Windows peek message loop");
		::TranslateMessage (&msg);
		::DispatchMessage (&msg);
    }
}

