#include "Serial.h"
// Bartosz Milewski (c) 2000
using std::ios_base;

const long TruePattern = 0xfab1fab2;
const long FalsePattern = 0xbad1bad2;

Serializer::Serializer (std::string const & nameFile)
	: _stream (nameFile.c_str (), ios_base::out | ios_base::binary)
{
	if (!_stream.is_open ())
		throw "couldn't open file";
}

void Serializer::PutLong (long x)
{
	_stream.write (reinterpret_cast<char *> (&x), sizeof (long));
	if (_stream.bad())
		throw "file write failed";
}

void Serializer::PutDouble (double x)
{
	_stream.write (reinterpret_cast<char *> (&x), sizeof (double));
	if (_stream.bad())
		throw "file write failed";
}

void Serializer::PutString (std::string const & str)
{
	int len = str.length ();
	PutLong (len);
	_stream.write (str.data (), len);
	if (_stream.bad())
		throw "file write failed";
}

void Serializer::PutBool (bool x)
{
	long l = x? TruePattern: FalsePattern;
	PutLong (l);
	if (_stream.bad ())
		throw "file write failed";
}

DeSerializer::DeSerializer (std::string const & nameFile)
	: _stream (nameFile.c_str (), ios_base::in | ios_base::binary)
{
	if (!_stream.is_open ())
		throw "couldn't open file";
}

long DeSerializer::GetLong ()
{
	if (_stream.eof())
		throw "unexpected end of file";
	long l;
	_stream.read (reinterpret_cast<char *> (&l), sizeof (long));
	if (_stream.bad())
		throw "file read failed";
	return l;
}

double DeSerializer::GetDouble ()
{
	double d;
	if (_stream.eof())
		throw "unexpected end of file";
	_stream.read (reinterpret_cast<char *> (&d), sizeof (double));
	if (_stream.bad())
		throw "file read failed";
	return d;
}

std::string DeSerializer::GetString ()
{
	long len = GetLong ();
	std::string str;
	str.resize (len);
	_stream.read (&str [0], len);
	if (_stream.bad())
		throw "file read failed";
	return str;
}

bool DeSerializer::GetBool ()
{
	long b = GetLong ();
	if (_stream.bad())
		throw "file read failed";
	if (b == TruePattern)
		return true;
	else if (b == FalsePattern)
		return false;
	else
		throw "data corruption";
	return false;
}
