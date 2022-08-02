#if !defined (MSGLOOP_H)
#define MSGLOOP_H
// (c) Bartosz Milewski 2000
#include <windows.h>
#include <list>

namespace Win
{
	class MsgPrepro
	{
		typedef std::list<HWND>::iterator DlgIter;
	public:
		MsgPrepro ()
			: _hAccel (0), _winTop (0)
		{}
		void SetKbdAccelerator (HWND hwndTop, HACCEL hAccel) 
		{
			_winTop = hwndTop;
			_hAccel = hAccel;
		}
		// Use with modeless dialogs
		void AddDialogFilter (HWND hDlg) { _dlgList.push_back (hDlg); }
		void RemoveDialogFilter (HWND hDlg);
		int Pump ();
		void PumpPeek ();
		void PumpWindow (HWND win);
	private:
		std::list<HWND> _dlgList;
		HACCEL	_hAccel;
		HWND	_winTop;
	};
}

#endif
