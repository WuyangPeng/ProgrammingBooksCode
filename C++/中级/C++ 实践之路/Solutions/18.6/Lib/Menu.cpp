#include "menu.h"
// (c) Bartosz Milewski 2000
#include "Exception.h"
#include <cassert>

using namespace Menu;

DropDown::DropDown (BarItem const * templ, Cmd::Vector & cmdVector)
    : _barItemCnt (0),
	  _template (templ),
	  _cmdVector (cmdVector)
{
    // Count menu bar items
	while (_template [_barItemCnt].kind != END)
		_barItemCnt++;

    // Create menu
    for (int curMenu = 0; curMenu < _barItemCnt; curMenu++)
    {
        assert (_template [curMenu].kind == Menu::POP);
        Menu::Maker curPopup = CreatePopup (_template [curMenu].popup);
		_menu.AddPopup (curPopup, _template [curMenu].displayName);
    }
}

void DropDown::AttachToWindow (HWND win)
{
    if (!::SetMenu (win, _menu.GetHandle ()))
        throw Win::Exception ("Internal error: Cannot attach menu.");
	_menu.Release (); // now owned by the window
}

void DropDown::RefreshPopup (HMENU menu, int barItemNo)
{
	if (barItemNo < 0 || barItemNo >= _barItemCnt)
		throw Win::Exception ("Internal error: Unknow menu initialization");

	Menu::Item const * popup = _template [barItemNo].popup;
	assert (popup != 0);
	int curItem = 0;
	Menu::Manip manip (menu);
    while (popup [curItem].kind != END)
    {
        if (popup [curItem].kind == CMD)
        {
			Cmd::Status cmdStatus = _cmdVector.Test (popup [curItem].cmdName);
			int itemId = _cmdVector.CmdToId (popup [curItem].cmdName);
			switch (cmdStatus)
			{
			case Cmd::Disabled:
				manip.Disable (itemId);
				break;
			case Cmd::Enabled:
				manip.Enable (itemId);
				manip.UnCheck (itemId);
				break;
			case Cmd::Checked:
				manip.Enable (itemId);
				manip.Check (itemId);
				break;
			default:
				throw Win::Exception ("Internal error: Illegal comamnd status");
			}
        }
		curItem++;
    }
}

Menu::Maker DropDown::CreatePopup (Menu::Item const * popupItems)
{
    assert (popupItems != 0);
    
	Menu::PopupMaker popupMaker;
	int curItem = 0;
    while (popupItems [curItem].kind != END)
    {
        if (popupItems [curItem].kind == CMD)
        {
            // Associate controller method with menu item
			popupMaker.AddItem (_cmdVector.CmdToId (popupItems [curItem].cmdName), 
								popupItems [curItem].displayName);
        }
        else
        {
            assert (popupItems [curItem].kind == SEPARATOR);
			popupMaker.AddSeparator ();
        }
		curItem++;
    }
    return popupMaker;
}

Menu::Item const * DropDown::GetPopupTemplate (char const * menuName) const
{
	int curMenu = 0;
	while (_template [curMenu].kind != END)
	{
		if (strcmp (_template [curMenu].name, menuName) == 0)
			break;
		curMenu++;
	}
	assert (_template [curMenu].kind == Menu::POP);
	return _template [curMenu].popup;
}

Context::Context (std::vector<Menu::Item const *> const & templ, Cmd::Vector & cmdVector)
{
	for (std::vector<Menu::Item const *>::const_iterator iter = templ.begin ();
		 iter != templ.end ();
		 ++iter)
	{
		Menu::Item const * curTempl = *iter;
		bool firstSeparator = true;
		bool separatorPending = false;
		int curItem = 0;
		while (curTempl [curItem].kind != END)
		{
			if (curTempl [curItem].kind == CMD)
			{
				// Add only enabled items
				Cmd::Status cmdStatus = cmdVector.Test (curTempl [curItem].cmdName);
				if (cmdStatus != Cmd::Disabled)
				{
					if (!firstSeparator && separatorPending)
					{
						// Add separators only if needed
						AddSeparator ();
						separatorPending = false;
					}
					firstSeparator = false;
					AddItem (cmdVector.CmdToId (curTempl [curItem].cmdName), 
							curTempl [curItem].displayName);
				}
			}
			else
			{
				assert (curTempl [curItem].kind == SEPARATOR);
				if (!firstSeparator && !separatorPending)
				{
					// Remember to add separator before next item if any
					separatorPending = true;
				}
			}
			curItem++;
		}
		if (!firstSeparator && !separatorPending)
		{
			// Remember to add separator before items of next template
			separatorPending = true;
		}
	}
}

