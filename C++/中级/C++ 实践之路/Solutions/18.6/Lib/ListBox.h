#if !defined (LISTBOX_H)
#define LISTBOX_H
// Bartosz Milewski (c) 2000
#include "Controls.h"
#include <string>

namespace Win
{
	class ListBox: public SimpleCtrl
	{
	public:
		ListBox (HWND winParent, int id)
			: SimpleCtrl (winParent, id)
		{}
		ListBox (HWND win = 0) : SimpleCtrl (win) {}
		void Init (HWND winParent, int id)
		{
			SimpleCtrl::Init (winParent, id);
		}
		~ListBox ()
		{
			Clear ();
		}
		void Init (HWND win)
		{
			SimpleCtrl::Init (win);
		}
		bool IsSelection ()
		{
			return SendMsg (LB_GETCURSEL) != LB_ERR;
		}
		int GetCount ()
		{
			return SendMsg (LB_GETCOUNT);
		}
		void Clear ()
		{
			SendMsg (LB_RESETCONTENT);
		}
		void InsertString (int idx, std::string const & str)
		{
			SendMsg (LB_INSERTSTRING, idx, reinterpret_cast<LPARAM> (str.c_str ()));
		}
		int AddString (std::string const & str)
		{
			return SendMsg (LB_ADDSTRING, 0, reinterpret_cast<LPARAM> (str.c_str ()));
		}
		void DeleteString (int idx)
		{
			SendMsg (LB_DELETESTRING, idx);
		}
		void ReplaceString (int idx, std::string const & str)
		{
			DeleteString (idx);
			InsertString (idx, str);
		}
		int GetData (int idx)
		{
			return SendMsg (LB_GETITEMDATA, idx);
		}
		void SetData (int idx, int value)
		{
			SendMsg (LB_SETITEMDATA, idx, value);
		}
		int GetTextLen (int idx)
		{
			return SendMsg (LB_GETTEXTLEN, idx);
		}
		std::string GetText (int idx)
		{
			int len = GetTextLen (idx);
			std::string str;
			str.reserve (len + 1);
			str.resize (len);
			SendMsg (LB_GETTEXT, idx, reinterpret_cast<LPARAM> (&str[0]));
			return str;
		}
		void ListDirectory (Win::Dow dlg, 
			char * pathBuf, 
			int idStatic = 0, // to display drive and directory
			unsigned fileTypes = DDL_DIRECTORY | DDL_DRIVES)
		{
			if (::DlgDirList (dlg, pathBuf, GetId (), idStatic, fileTypes) == 0)
				throw Win::Exception (pathBuf);
		}
		// true, if directory
		bool GetSelectedPath (Win::Dow dlg,
			char * pathBuf,
			int bufLen)
		{
			return DlgDirSelectEx (dlg, pathBuf, bufLen, GetId ()) != 0;
		}
	};


	class ListBoxMaker: public ControlMaker
	{
	public:
		ListBoxMaker (HWND winParent, int id)
			: ControlMaker ("LISTBOX", winParent, id)
		{
			_style |= LBS_NOINTEGRALHEIGHT;
		}
	};
}

#endif
