#include "Store.h"
// (c) Bartosz Milewski 2000
#include "SymTab.h"
#include "Serial.h"
#include <iostream>
#include <cmath>

Store::Store (SymbolTable & symTab)
{
	// add predefined constants
	// Note: if more needed, do a more general job
	std::cerr << "e = " << std::exp (1) << std::endl;
	std::size_t id = symTab.ForceAdd ("e");
	AddValue (id, std::exp (1));
	std::cerr << "pi = " << 2 * std::acos (0.0) << std::endl;
	id = symTab.ForceAdd ("pi");
	AddValue (id, 2.0 * std::acos (0.0));
}

void Store::SetValue (std::size_t id, double val)
{
	assert (id != SymbolTable::idNotFound);
	if (id < _cell.size ())
	{
		_cell [id] = val;
		_isInit [id] = true;
		_isChanged [id] = true;
	}
	else
	{
		AddValue (id, val);
	}
}

void Store::AddValue (std::size_t id, double val)
{
	assert (id != SymbolTable::idNotFound);
	_cell.resize (id + 1);
	_isInit.resize (id + 1);
	_isChanged.resize (id + 1);
	_cell [id] = val;
	_isInit [id] = true;
	_isChanged [id] = true;
}

std::size_t Store::FindNewVariable ()
{
	std::size_t len = _isChanged.size ();
	for (std::size_t i = 0; i < len; ++i)
		if (_isChanged [i])
			return i;
	return SymbolTable::idNotFound;
}

void Store::Serialize (Serializer & out) const
{
	std::size_t len = _cell.size ();
	out.PutLong (len);
	for (std::size_t i = 0; i < len; ++i)
	{
		out.PutDouble (_cell [i]);
		out.PutBool (_isInit [i]);
	}
}

void Store::DeSerialize (DeSerializer & in)
{
	_cell.clear ();
	_isInit.clear ();
	std::size_t len = in.GetLong ();
	_cell.resize (len);
	_isInit.resize (len);
	_isChanged.resize (len);
	for (std::size_t i = 0; i < len; ++i)
	{
		_cell [i] = in.GetDouble ();
		_isInit [i] = in.GetBool ();
		_isChanged [i] = true;
	}
}

