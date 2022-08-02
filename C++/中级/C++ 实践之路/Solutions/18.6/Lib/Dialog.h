#if !defined DIALOG_H
#define DIALOG_H
// (c) Bartosz Milewski 2000
#include "Window.h"
#include "Exception.h"
#include <memory>

namespace Dialog
{

	BOOL CALLBACK ModelessProc (HWND win, UINT message, WPARAM wParam, LPARAM lParam);
	BOOL CALLBACK ModalProc (HWND win, UINT message, WPARAM wParam, LPARAM lParam);

	class Controller
	{
		friend BOOL CALLBACK ModelessProc (HWND win, UINT message, WPARAM wParam, LPARAM lParam);
		friend BOOL CALLBACK ModalProc (HWND win, UINT message, WPARAM wParam, LPARAM lParam);
	public:
		virtual ~Controller () {}
		virtual void OnInitDialog () throw (Win::Exception) {};
		virtual bool OnCommand (int ctrlId, int notifyCode) throw (Win::Exception) 
			{ return false; }
		virtual void EndOk () throw () = 0;
		virtual void EndCancel () throw ()= 0;

	protected:
		Win::Dow GetWindow () const throw () { return _win; }
	private:
		void SetWindow (Win::Dow win) { _win = win; }

		Win::Dow	_win;
	};

	//-------- User part ------------

	// User controller inerits from this
	class ModalController: public Controller
	{
	protected:
		void EndOk () throw () { ::EndDialog (GetWindow (), 1); }
		void EndCancel () throw () { ::EndDialog (GetWindow (), 0); }
	};

	// User controller inerits from this
	class ModelessController: public Controller
	{
	protected:
		void EndOk () throw () { ::DestroyWindow (GetWindow ()); }
		void EndCancel () throw () { ::DestroyWindow (GetWindow ()); }
	};

	// User constructs this object and passes it User controller
	class Modal
	{
	public:
		Modal (Win::Dow winParent, int dlgId, ModalController & ctrl)
		{
			_result = ::DialogBoxParam (winParent.GetInstance (),
										MAKEINTRESOURCE (dlgId),
										winParent,
										static_cast<DLGPROC>(ModalProc),
										reinterpret_cast<LPARAM>(&ctrl));
		}

		bool IsOk () throw () { return (_result == -1)? false: _result != 0; }

	private:
		int _result;
	};

	// User constructs this object and passes it User controller and User factory
	class Modeless
	{
	public:
		Modeless (Win::Dow winParent, int dlgId, std::auto_ptr<ModelessController> & apCtrl)
			: _winDlg (::CreateDialogParam ( winParent.GetInstance (),
											 MAKEINTRESOURCE (dlgId),
											 winParent,
											 static_cast<DLGPROC>(ModelessProc),
											 reinterpret_cast<LPARAM>(&apCtrl)))
		{
			if (_winDlg == 0)
				throw Win::Exception ("Internal error: Cannot create modeless dialog.");
		}
		operator HWND () const throw () { return _winDlg; }

	private:
		Win::Dow _winDlg;
	};
}

#endif
