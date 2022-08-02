#include "Commander.h"
// Bartosz Milewski (c) 2000
#include "Calc.h"
#include "Notify.h"
#include "Output.h"
#include "AboutDlg.h"
#include "SaveDlg.h"
#include "LoadDlg.h"
#include "Resource.h"
#include "Exception.h"

namespace Cmd
{
	const Cmd::Item<Commander> Table [] =
	{
		{ "Program_About",	&Commander::Program_About,
							&Commander::can_Program_About,
							"About this program"},
		{ "Program_Exit",	&Commander::Program_Exit,
							&Commander::can_Program_Exit,
							"Exit program"},
		{ "Memory_Clear",	&Commander::Memory_Clear,
							&Commander::can_Memory_Clear,
							"Clear memory"},
		{ "Memory_Save",	&Commander::Memory_Save,
							&Commander::can_Memory_Save,
							"Save memory to file"},
		{ "Memory_Load",	&Commander::Memory_Load,
							&Commander::can_Memory_Load, 
							"Load memory from file"},
		{ 0, 0, 0, 0}
	};
}

void Commander::Program_About ()
{
	AboutCtrl ctrl;
	Dialog::Modal dialog (_win, IDD_ABOUT, ctrl);
}

void Commander::Program_Exit ()
{
	throw Win::ExitException ();
}

Cmd::Status Commander::can_Memory_Clear () const 
{
	if (_calc.HasVariables ())
		return Cmd::Enabled;
	return Cmd::Disabled;
}

void Commander::Memory_Clear ()
{
	_calc.ClearMemory ();
	// tell parent to clear memory display
	_win.SendMsg (UM_MEMCLEAR);
}

void Commander::Memory_Save ()
{
	SaveCtrl ctrl;
	Dialog::Modal dialog (_win, IDD_SAVE, ctrl);
	if (dialog.IsOk ())
	{
		std::string const & path = ctrl.GetPath ();
		Serializer out (path);
		_calc.Serialize (out);
	}
}

void Commander::Memory_Load ()
{
	LoadCtrl ctrl;
	Dialog::Modal dialog (_win, IDD_LOAD, ctrl);
	if (dialog.IsOk ())
	{
		std::string const & path = ctrl.GetPath ();
		DeSerializer in (path);
		_calc.DeSerialize (in);
		// tell parent to clear memory display
		_win.SendMsg (UM_MEMCLEAR);
	}
}
