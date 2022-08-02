#if !defined (SERIAL_H)
#define SERIAL_H
// Bartosz Milewski (c) 2000
#include <string>
#include <fstream>

class Serializer
{
public:
	Serializer (std::string const & nameFile);
	void PutLong (long x);
	void PutDouble (double x);
	void PutString (std::string const & str);
	void PutBool (bool x);
private:
	std::ofstream _stream;
};

class DeSerializer
{
public:
	DeSerializer (std::string const & nameFile);
	long GetLong ();
	double GetDouble ();
	std::string GetString ();
	bool GetBool ();
private:
	std::ifstream _stream;
};

class Serializable
{
public:
	virtual void Serialize (Serializer & out) const = 0;
	virtual void DeSerialize (DeSerializer & in) = 0;
};

#endif
