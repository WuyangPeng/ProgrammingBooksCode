#if !defined (TOOLS_H)
#define TOOLS_H
// Bartosz Milewski (c) 2000
#include <windows.h>

namespace Win
{
	class StockObject
	{
	public:
		StockObject (int type)
			: _obj (::GetStockObject (type))
		{}
		operator HGDIOBJ () const { return _obj; }
	protected:
		HGDIOBJ _obj;
	};

	class StockObjectHolder
	{
	public:
		StockObjectHolder (HDC hdc, int type)
			: _hdc (hdc)
		{
			_hObjOld = ::SelectObject (_hdc, StockObject (type));
		}

		~StockObjectHolder ()
		{
			::SelectObject (_hdc, _hObjOld);
		}
	private:
		HGDIOBJ  _hObjOld;
		HDC      _hdc;
	};
}

namespace Pen
{
	class Color
	{
	public:
		Color (int r, int g, int b, int style = PS_SOLID)
		{
			_hPen = ::CreatePen (style, 0, RGB (r, g, b));
		}
		~Color ()
		{
			::DeleteObject (_hPen);
		}
		operator HPEN () { return _hPen; }
	private:
		HPEN    _hPen;
	};

	class Holder
	{
	public:
		Holder (HDC hdc, HPEN hPen)
			: _hdc (hdc)
		{
			_hPenOld = reinterpret_cast<HPEN> (
						::SelectObject (_hdc, hPen)); 
		}
		~Holder ()
		{
			::SelectObject (_hdc, _hPenOld);
		}
	private:
		HDC     _hdc;
		HPEN    _hPenOld;

	public:
		class White : public Win::StockObjectHolder
		{
		public:
			White (HDC hdc)
				: Win::StockObjectHolder (hdc, WHITE_PEN)
			{}
		};
		
		class Black : public Win::StockObjectHolder
		{
		public:
			Black (HDC hdc)
				: Win::StockObjectHolder (hdc, BLACK_PEN)
			{}
		};
		
		class Instant
		{
		public:
			Instant (HDC hdc, int r, int g, int b)
						: _hdc (hdc)
			{
				_hPen = ::CreatePen (PS_SOLID, 0, RGB (r, g, b));
				_hPenOld = reinterpret_cast<HPEN> (
							::SelectObject (_hdc, _hPen));
			}
			~Instant ()
			{
				::SelectObject (_hdc, _hPenOld);
				::DeleteObject (_hPen);
			}
		private:
			HDC     _hdc;
			HPEN    _hPen;
			HPEN    _hPenOld;
		};
	};
}

namespace Brush
{
	class Stock: public Win::StockObject
	{
	public:
		Stock (int type) : Win::StockObject (type) {}
		operator HBRUSH () const { return reinterpret_cast<HBRUSH> (_obj); }
	};

	class Color
	{
	public:
		Color (int r, int g, int b, int style = PS_SOLID)
		{
			_hBrush = ::CreateSolidBrush (RGB (r, g, b));
		}
		~Color ()
		{
			::DeleteObject (_hBrush);
		}
		operator HBRUSH () { return _hBrush; }
	private:
		HBRUSH  _hBrush;
	};

	class Holder
	{
	public:
		Holder (HDC hdc, HBRUSH hBrush)
			: _hdc (hdc)
		{
			_hBrushOld = reinterpret_cast<HBRUSH> (::SelectObject (_hdc, hBrush));
		}
		~Holder ()
		{
			::SelectObject (_hdc, _hBrushOld);
		}
	private:
		HDC     _hdc;
		HBRUSH  _hBrushOld;
	public:
		// specialized classes
		class White : public Win::StockObjectHolder
		{
		public:
			White (HDC hdc): Win::StockObjectHolder (hdc, WHITE_BRUSH) {}
		};

		class Black : public Win::StockObjectHolder
		{
		public:
			Black (HDC hdc): Win::StockObjectHolder (hdc, BLACK_BRUSH) {}
		};

		class Instant
		{
		public:
			Instant (HDC hdc, int r, int g, int b)
				: _hdc (hdc)
			{
				_hBrush = ::CreateSolidBrush (RGB (r, g, b));
				_hBrushOld = reinterpret_cast<HBRUSH> (::SelectObject (_hdc, _hBrush));
			}
			~Instant ()
			{
				::SelectObject (_hdc, _hBrushOld);
				::DeleteObject (_hBrush);
			}
		private:
			HDC     _hdc;
			HBRUSH  _hBrush;
			HBRUSH  _hBrushOld;
		};
	};
}

namespace Font
{
	class Stock: public Win::StockObject
	{
	public:
		Stock (int type) : Win::StockObject (type) {}
		operator HFONT () const 
		{
			return reinterpret_cast<HFONT> (_obj);
		}
		void GetTextSize (int &width, int &height);
	};

	class SysFixed: public Stock
	{
	public:
			SysFixed () : Stock (SYSTEM_FIXED_FONT) {}
	};

	class OemFixed: public Stock
	{
	public:
		OemFixed () : Stock (OEM_FIXED_FONT) {}
	};

	class Holder
	{
	public:
		Holder (HDC hdc, HFONT font)
			: _hdc (hdc)
		{
			_fontOld = reinterpret_cast<HFONT> (::SelectObject (_hdc, font));
		}
		~Holder ()
		{
			::SelectObject (_hdc, _fontOld);
		}
	private:
		HDC     _hdc;
		HFONT   _fontOld;
	public:
		class Color
		{
		public:
			Color (HDC hdc, int r, int g, int b)
				: _hdc (hdc), 
				_oldColor (::SetTextColor (_hdc, RGB (r, g, b)))
			{}
			~Color ()
			{
				::SetTextColor (_hdc, _oldColor);
			}
		private:
			HDC            _hdc;
			COLORREF    _oldColor;
		};

		class Background
		{
		public:
			Background (HDC hdc, int r, int g, int b)
					: _hdc (hdc),
					_oldColor (::SetBkColor (_hdc, RGB (r, g, b)))
			{}
			~Background ()
			{
				::SetBkColor (_hdc, _oldColor);
			}
		private:
			HDC            _hdc;
			COLORREF    _oldColor;
		};

		class SysFixed : public Win::StockObjectHolder
		{
		public:
			SysFixed (HDC hdc)
					: Win::StockObjectHolder (hdc, SYSTEM_FIXED_FONT) 
			{}
		};
	}; 
}
#endif
