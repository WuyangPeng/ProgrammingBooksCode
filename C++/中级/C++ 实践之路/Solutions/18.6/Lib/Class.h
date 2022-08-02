#if !defined (CLASS_H)
#define CLASS_H
// Bartosz Milewski (c) 2000
#include "Icon.h"
#include <windows.h>

namespace Win
{
	class ClassMaker
	{
	public:
		ClassMaker (char const * className,	HINSTANCE hInst);
		void Register ()
		{
			if (::RegisterClassEx (&_class) == 0)
				throw "RegisterClass failed";
		}
		void SetIcons (int id);
		void SetBkColor (int r, int g, int b);
	private:
		WNDCLASSEX _class;
		StdIcon    _stdIcon;
		SmallIcon  _smallIcon;
	};
}

#endif
