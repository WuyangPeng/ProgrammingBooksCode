#if !defined (MENU_H)
#define MENU_H
// (c) Bartosz Milewski 2000
#include "Cmd.h"
#include "Exception.h"
#include <vector>
#include <windows.h>

namespace Menu
{
	// The manipulator

	class Manip
	{
	public:
		Manip (HMENU menu)
			: _menu (menu)
		{}

		Manip (HWND win)
			: _menu (::GetMenu (win))
		{}

		operator HMENU () const { return _menu; }
		void Attach (HWND win)
		{
			if (!::SetMenu (win, _menu))
				throw Win::Exception ("Internal error: Cannot activate menu.");
		}
    	static void Refresh (HWND win)
    	{
        	DrawMenuBar(win);
    	}
		// Item manipulation
		void Enable (int id)
		{
			::EnableMenuItem (_menu, id, MF_BYCOMMAND | MF_ENABLED);
		}
		void Disable (int id)
		{
			::EnableMenuItem (_menu, id, MF_BYCOMMAND | MF_GRAYED);
		}
		void Check (int id)
		{
			::CheckMenuItem (_menu, id, MF_BYCOMMAND | MF_CHECKED);
		}
		void UnCheck (int id)
		{
			::CheckMenuItem (_menu, id, MF_BYCOMMAND | MF_UNCHECKED);
		}
	private:
		HMENU   _menu;
	};

	//-----------------------
	// Menu construction kits
	//-----------------------
	
	class Maker;
	
	struct MakerRef
	{
		MakerRef (Maker const & maker)
		: _maker (const_cast<Maker &> (maker)) 
		{}
		Maker & _maker;
	};

	class Maker
	{
	public:
		Maker ()
			: _menu (0)
		{}
		Maker (Maker & maker)
		{
			_menu = maker.Release ();
		}
		~Maker ()
		{
			if (_menu != 0)
				::DestroyMenu (_menu);
		}

		void operator = (Maker & maker)
		{
			if (_menu != maker._menu)
			{
				if (_menu != 0)
					::DestroyMenu (_menu);
				_menu = maker.Release ();
			}
		}
		HMENU GetHandle () const { return _menu; }
		HMENU Release ()
		{
			HMENU hTmp = _menu;
			_menu = 0;
			return hTmp;
		}
		void AddSeparator ()
		{
			if (!::AppendMenu (_menu, MF_SEPARATOR, 0, 0))
				throw Win::Exception ("Internal error: Cannot add menu separator.");
		}
		void AddItem (int itemId, char const * item)
		{
			if (!::AppendMenu (_menu, MF_STRING, itemId, item))
				throw Win::Exception ("Internal error: Cannot add menu item.");
		}
		void AddPopup (Maker & maker, char const * item)
		{
			if (!::AppendMenu (_menu, MF_POPUP, reinterpret_cast<unsigned int>(maker.Release ()), item))
				throw Win::Exception ("Internal error: Cannot add popup menu.");
		}
		// special conversions
		Maker (MakerRef ref): _menu (ref._maker.Release ()) {}

	protected:
		Maker (HMENU menu)
			: _menu (menu)
		{
			if (_menu == 0)
				throw Win::Exception ("Internal error: Cannot create menu.");
		}

	protected:
		HMENU	_menu;
	};

	class BarMaker : public Maker
	{
	public:
		BarMaker ()
			: Maker (::CreateMenu ())
		{}
	};

	class PopupMaker : public Maker
	{
	public:
		PopupMaker ()
			: Maker (::CreatePopupMenu ())
		{}
	};

	class ContextMaker: public PopupMaker
	{
	public:
		void TrackMenu (HWND hwndOwner, int x, int y)
		{
			if (::TrackPopupMenuEx (_menu,
								TPM_LEFTALIGN | TPM_RIGHTBUTTON,
								x, y,
								hwndOwner,
								0) == FALSE)
			{
				throw Win::Exception ("Popup menu tracking failed");
			}
		}
	};

	//----------------------------
	// Templates for menu creation
	//----------------------------

	enum ItemKind
	{
		POP,
		CMD,
		SEPARATOR,
		END
	};

	class Item
	{
	public:
		ItemKind		kind;			// Menu item flags
		char const *	displayName;	// Menu item display string
		char const *	cmdName;		// Command
	};

	class BarItem
	{
	public:
		ItemKind		kind;			// Menu item flags
		char const *    displayName;	// Menu bar item display string 
		char const *	name;			// Menu bar item name
		Item const * 	popup;			// Menu popup definition
	};

	//----------------------
	// Drop Down Menu System
	//----------------------

	class DropDown
	{
	public:
		DropDown (BarItem const * templ, Cmd::Vector & cmdVector);
		void AttachToWindow (HWND win);
		void RefreshPopup (HMENU menu, int barItemNo);
		Item const * GetPopupTemplate (char const * name) const;
		Cmd::Vector & GetCommandVector () { return _cmdVector; }
	private:
		Menu::Maker CreatePopup (Menu::Item const * popupItems);

	private:
		BarMaker		_menu;
		int				_barItemCnt;
		BarItem const * _template;
		Cmd::Vector &	_cmdVector;
	};

	class Context : public ContextMaker
	{
	public:
		Context (std::vector<Menu::Item const *> const & templ, Cmd::Vector & cmdVector);
	};

}

#endif
