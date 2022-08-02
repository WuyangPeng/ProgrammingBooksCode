#if !defined (FUNTAB_H)
#define FUNTAB_H
#include <cstddef>
// (c) Bartosz Milewski 2000

class SymbolTable;

typedef double (*PtrFun) (double);

namespace Function
{
	class Table
	{
	public:
		Table (SymbolTable & symTab);
		~Table ();
		std::size_t Size () const { return _size; }
		PtrFun GetFun (std::size_t id) const { return _pFun [id]; }
	private:
		PtrFun		  * _pFun;
		std::size_t		_size;
	};
}
#endif
