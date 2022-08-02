#include "Ctrl.h"
// Bartosz Milewski (c) 2000
#include "Scanner.h"
#include "Parser.h"
#include "SyntaxErr.h"
#include "Output.h"
#include "Canvas.h"
#include <sstream>

bool TopController::OnCreate (Win::CreateData const * create, bool & success) throw ()
{
	try
	{
		_view.reset (new View (_h, _calc));
		success = true;
		TheOutput.Init (_h);
	}
	catch (Win::Exception & e)
	{
		TheOutput.Error (e.GetMessage ());
		success = false;
	}
	catch (...)
	{
		TheOutput.Error ("Internal Error:\nFailure to initialize.");
		success = false;
	}
	return true;
}

bool TopController::OnCommand (int cmdId, bool isAccel) throw ()
{
	try
	{
		// TBD
	}
	catch (Win::ExitException)
	{
		_h.Destroy ();
	}
	catch (Win::Exception const & e)
	{
		TheOutput.Error (e.GetMessage ());
	}
	catch (...)
	{
		TheOutput.Error ("Internal error");
	}
	return true;
}

bool TopController::OnControl (Win::Dow control, int controlId, int notifyCode) throw ()
{
	if (controlId == IDOK)
	{
		try
		{
			std::string expr = _view->GetInput ();
			std::istringstream in (expr);
			Scanner scanner (in);
			Parser  parser (scanner, _calc);
			parser.Parse ();
			double result = parser.Calculate ();
			_view->UpdateHistory (expr, result);
			_view->UpdateMemory ();
			std::ostringstream out;
			out << result;
			std::string strOut = out.str ();
			_view->SetResult (strOut.c_str ());
		}
		catch (Syntax const & err)
		{
			TheOutput.Error (err.GetString ());
			_view->SetResult ("");
		}
		catch (...)
		{
			TheOutput.Error ("Internal error");
			_view->SetResult ("");
		}
		return true;
	}
	return false;
}

bool TopController::OnFocus (Win::Dow winPrev) throw ()
{
	if (_view.get () != 0)
		_view->SetFocus ();
	return true;
}

bool TopController::OnSize (int width, int height, int flags) throw ()
{
	if (flags != SIZE_MINIMIZED)
	{
		_view->Size (width, height);
		_view->UpdateMemory ();
	}
	return true;
}
