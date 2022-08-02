#if !defined (STORE_H)
#define STORE_H
// (c) Bartosz Milewski 2000
#include "SymTab.h"
#include "Serial.h"
#include <vector>
#include <cassert>

class Store: public Serializable
{
public:
	explicit Store (SymbolTable & symTab);
	bool IsInit (std::size_t id) const
	{
		assert (id != SymbolTable::idNotFound);
		return id < _isInit.size () && _isInit [id];
	}
	double Value (std::size_t id) const
	{
		assert (id != SymbolTable::idNotFound);
		assert (IsInit (id));
		return _cell [id];
	}
	void SetValue (std::size_t id, double val);
	void AddValue (std::size_t id, double val);
	bool HasValueChanged (std::size_t id) 
	{
		assert (id < _isChanged.size ());
		return _isChanged [id];
	}
	std::size_t FindNewVariable ();
	void ResetChange (std::size_t id)
	{
		assert (id < _isChanged.size ());
		_isChanged [id] = false;
	}
	void Serialize (Serializer & out) const;
	void DeSerialize (DeSerializer & in);
private:
	std::vector<double>	_cell;
	std::vector<bool>	_isInit;
	std::vector<bool>	_isChanged;
};

#endif
