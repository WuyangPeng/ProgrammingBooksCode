#if !defined (CALC_H)
#define CALC_H
// Bartosz Milewski (c) 2000
#include "SymTab.h"
#include "FunTab.h"
#include "Store.h"
#include "Serial.h"

class Calculator: public Serializable
{
	friend class Parser;
public:
	Calculator ()
		: _funTab (_symTab), _store (_symTab)
	{}
	void Serialize (Serializer & out) const;
	void DeSerialize (DeSerializer & in);
	// Memory access
	bool HasValueChanged (std::size_t id) 
	{
		return _store.HasValueChanged (id);
	}
	std::string GetVariableName (std::size_t id)
	{
		return _symTab.GetVariableName (id);
	}
	double GetVariableValue (std::size_t id) const
	{
		return _store.Value (id);
	}
	std::size_t FindNewVariable ()
	{
		return _store.FindNewVariable ();
	}
	void ResetChange (std::size_t id)
	{
		_store.ResetChange (id);
	}
private:
	Store & GetStore () { return _store; }
	PtrFun GetFun (std::size_t id) const
	{
		return _funTab.GetFun (id);
	}
	bool IsFunction (std::size_t id) const 
	{
		return id < _funTab.Size (); 
	}
	std::size_t AddSymbol (std::string const & str)
	{
		return _symTab.ForceAdd (str);
	}
	std::size_t FindSymbol (std::string const & str) const
	{
		return _symTab.Find (str);
	}

	SymbolTable     _symTab;
	Function::Table _funTab;
	Store           _store;
};

#endif
