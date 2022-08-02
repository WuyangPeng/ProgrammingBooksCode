#if !defined (SYMTAB_H)
#define SYMTAB_H
// (c) Bartosz Milewski 2000
#include <map>
#include <string>
#include "Serial.h"

// String table maps strings to ints
// and ints to strings

class SymbolTable: public Serializable
{
public:
	static const std::size_t idNotFound = 0xffffffff;
	SymbolTable () : _id (0) {}
	std::size_t ForceAdd (std::string const & str);
	std::size_t Find (std::string const & str) const;
	std::string GetVariableName (std::size_t id) const;
	void Serialize (Serializer & out) const;
	void DeSerialize (DeSerializer & in);
private:
	std::map<std::string, std::size_t> _dictionary;
	std::size_t _id;
};

#endif
