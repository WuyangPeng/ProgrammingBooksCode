#if !defined (EDIT_H)
#define EDIT_H
// (c) Bartosz Milewski 2000
#include "controls.h"
#include <string>

namespace Win
{
	class StaticText: public SimpleCtrl
	{
	public:
		StaticText (HWND winParent, int id)
			: SimpleCtrl (winParent, id)
		{}
	};

	class EditReadOnly: public SimpleCtrl
	{
	public:
		EditReadOnly (HWND winParent, int id)
			: SimpleCtrl (winParent, id)
		{}

		void Select (int offStart, int offEnd)
		{
			SendMsg (EM_SETSEL, (WPARAM) offStart, (LPARAM) offEnd);
		}
	};

	class Edit: public SimpleCtrl
	{
	public:
		Edit (HWND winParent, int id)
			: SimpleCtrl (winParent, id)
		{}

		Edit (HWND win = 0) : SimpleCtrl (win) {}

		void Append (char const * buf);

		void Select (int offStart, int offEnd)
		{
			SendMsg (EM_SETSEL, (WPARAM) offStart, (LPARAM) offEnd);
		}

		void SetReadonly (bool flag)
		{
			SendMsg (EM_SETREADONLY, (WPARAM) (flag ? TRUE : FALSE), 0);
		}

		// code is the HIWORD (wParam)
		static bool IsChanged (int code)
		{ 
			return code == EN_CHANGE;
		}

		int GetLen () const
		{
			return SendMsg (WM_GETTEXTLENGTH);
		}

		int GetLineCount ()
		{
			return SendMsg (EM_GETLINECOUNT);
		}

		void GetText (char * buf, int len) const
		{
			SendMsg (WM_GETTEXT, (WPARAM) len, (LPARAM) buf);
		}

		std::string GetText () const;

		void Select ()
		{
			SendMsg (EM_SETSEL, 0, -1);
		}

		void SelectLine (int lineIdx);
		void ReplaceSelection (char const * info)
		{
			SendMsg (EM_REPLACESEL, 0, reinterpret_cast<LPARAM>(info));
		}
		void Clear ();
	};

	class EditMaker: public ControlMaker
	{
	public:
		EditMaker (HWND winParent, int id) : ControlMaker ("EDIT", winParent, id)
		{}
		void MakeReadOnly () { _style |= ES_READONLY; }
		void WantReturn () { _style |= ES_WANTRETURN; }
	};
}
#endif
