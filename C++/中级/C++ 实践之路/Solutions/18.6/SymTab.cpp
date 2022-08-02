#include "SymTab.h"
// (c) Bartosz Milewski 2000
#include "Serial.h"
#include <cassert>
#include <iostream>

std::size_t SymbolTable::ForceAdd (std::string const & str)
{
	_dictionary [str] = _id;
	return _id++;
}

std::size_t SymbolTable::Find (std::string const & str) const
{
	std::map<std::string, std::size_t>::const_iterator it;
	it = _dictionary.find (str);
	if (it != _dictionary.end ())
		return it->second;
	return idNotFound;
}

std::string SymbolTable::GetVariableName (std::size_t id) const
{
	std::map<std::string, std::size_t>::const_iterator it;
	for (it = _dictionary.begin (); it != _dictionary.end (); ++it)
		if (it->second == id)
			return it->first;
	return std::string ("Error");
}

void SymbolTable::Serialize (Serializer & out) const
{
	out.PutLong (_dictionary.size ());
	std::map<std::string, std::size_t>::const_iterator it;
	for (it = _dictionary.begin ();
				it != _dictionary.end (); ++it)
	{
		out.PutString (it->first);
		out.PutLong (it->second);
	}
	out.PutLong (_id);
}

void SymbolTable::DeSerialize (DeSerializer & in)
{
	_dictionary.clear ();
	int len = in.GetLong ();
	for (int i = 0; i < len; ++i)
	{
		std::string str = in.GetString ();
		std::size_t id = in.GetLong ();
		_dictionary [str] = id;
	}
	_id = in.GetLong ();
}
