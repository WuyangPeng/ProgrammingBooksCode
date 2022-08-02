#if !defined (CTRL_H)
#define CTRL_H
// Bartosz Milewski (c) 2000
#include "Control.h"
#include "View.h"
#include "Calc.h"
#include <memory>

class TopController: public Win::Controller
{
public:
	bool OnCreate (Win::CreateData const * create, bool & success) throw ();
	bool OnDestroy () throw ()
	{
		::PostQuitMessage (0);
		return true;
	}
	bool OnCommand (int cmdId, bool isAccel) throw ();
	bool OnControl (Win::Dow control, int controlId, int notifyCode) throw ();
	bool OnFocus (Win::Dow winPrev) throw ();
	bool OnSize (int width, int height, int flags) throw ();
private:
	std::auto_ptr<View>	_view;
	// this is the Model
	Calculator	 _calc;
};

#endif
