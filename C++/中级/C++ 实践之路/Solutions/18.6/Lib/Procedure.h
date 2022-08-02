#if !defined (PROCEDURE_H)
#define PROCEDURE_H
// Bartosz Milewski (c) 2000
#include <windows.h>

namespace Win
{
	// ProcPtr definition
	typedef LRESULT (CALLBACK * ProcPtr)
		(HWND win, UINT message, WPARAM wParam, LPARAM lParam);

	LRESULT CALLBACK Procedure
    	(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	LRESULT CALLBACK SubProcedure
		(HWND win, UINT message, WPARAM wParam, LPARAM lParam);

	class CreateData: public CREATESTRUCT
	{
	public:
		void * GetCreationData () const 
			{ return lpCreateParams; }
		int GetHeight () const { return cy; }
		int GetWidth () const { return cx; }
		int GetX () const { return x; }
		int GetY () const { return y; }
		char const * GetWndName () const { return lpszName; }
	};
}

#endif
