#if !defined (COMMANDER_H)
#define COMMANDER_H
// Bartosz Milewski (c) 2000
#include "Cmd.h"
#include "Window.h"
class Calculator;

class Commander
{
public:
	Commander (Win::Dow win, Calculator & calc) 
	: _calc (calc), _win (win)
	{}
	void Program_About ();
	Cmd::Status can_Program_About () const { return Cmd::Enabled; }
	void Program_Exit ();
	Cmd::Status can_Program_Exit () const { return Cmd::Enabled; }
	void Memory_Clear ();
	Cmd::Status can_Memory_Clear () const;
	void Memory_Save ();
	Cmd::Status can_Memory_Save () const { return Cmd::Enabled; }
	void Memory_Load ();
	Cmd::Status can_Memory_Load () const { return Cmd::Enabled; }
private:
	Win::Dow	 _win;
	Calculator & _calc;
};

typedef Cmd::VectorExec<Commander> CmdVector;

namespace Cmd
{
	extern const Cmd::Item<Commander> Table [];
}

#endif
