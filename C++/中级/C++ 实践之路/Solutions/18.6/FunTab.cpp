#include "FunTab.h"
// (c) Bartosz Milewski 2000
#include "SymTab.h"
#include "Output.h"
#include <cassert>
#include <sstream>
#include <cmath>

namespace Function
{
	double CoTan (double x);

	class Entry 
	{ 
	public: 
		PtrFun pFun; 
		char* strFun; 
	};
	
	Entry Array [] =
	{ 
		std::log,  	"log",
		std::log10, "log10",
		std::exp,  	"exp",
		std::sqrt, 	"sqrt",
		std::sin,  	"sin",
		std::cos,  	"cos",
		std::tan,  	"tan",
		CoTan,  	"cotan",
		std::sinh, 	"sinh",
		std::cosh, 	"cosh",
		std::tanh, 	"tanh",
		std::asin, 	"asin",
		std::acos, 	"acos",
		std::atan, 	"atan"
	};
	
	Table::Table (SymbolTable & symTab)
		: _size (sizeof Array / sizeof Array [0])
	{
		_pFun = new PtrFun [_size];
		for (std::size_t i = 0; i < _size; ++i)
		{
			_pFun [i] = Array [i].pFun;
			std::size_t j = symTab.ForceAdd (Array[i].strFun);
			assert (i == j);
		}
	}
	
	Table::~Table () 
	{ 
		delete []_pFun; 
	} 
	
	double CoTan (double x) 
	{
		double y = std::tan (x);
		if (y == 0)
		{
			std::ostringstream out;
			out << "cotan of " << x << " undefined";
			TheOutput.Error (out.str ());
			return HUGE_VAL;
		}
		return 1.0 / y;
	}
}
