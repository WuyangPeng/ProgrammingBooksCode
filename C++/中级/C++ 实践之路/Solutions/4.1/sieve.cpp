#include <iostream>

class Sieve
{
public:
	virtual int NextNumber () = 0;
};

class SourceSieve: public Sieve
{
public:
	SourceSieve () : _i (1) {}
	int NextNumber ();
private:
	int _i;
};

class Sieve2: public Sieve
{
public:
	Sieve2 (Sieve & src) : _src (src) {}
	int NextNumber ();
private:
	Sieve & _src;
};

class Sieve3: public Sieve
{
public:
	Sieve3 (Sieve & src) : _src (src) {}
	int NextNumber ();
private:
	Sieve & _src;
};

class Sieve5: public Sieve
{
public:
	Sieve5 (Sieve & src) : _src (src) {}
	int NextNumber ();
private:
	Sieve & _src;
};

class Sieve7: public Sieve
{
public:
	Sieve7 (Sieve & src) : _src (src) {}
	int NextNumber ();
private:
	Sieve & _src;
};

int SourceSieve::NextNumber ()
{
	if (_i > 100)
		return -1; // end
	return _i++;
}

int Sieve2::NextNumber ()
{
	int i;
	do
	{
		i = _src.NextNumber ();
	} while (i % 2 == 0 && i != 2 && i != -1);
	return i;
}

int Sieve3::NextNumber ()
{
	int i;
	do
	{
		i = _src.NextNumber ();
	} while (i % 3 == 0 && i != 3 && i != -1);
	return i;
}

int Sieve5::NextNumber ()
{
	int i;
	do
	{
		i = _src.NextNumber ();
	} while (i % 5 == 0 && i != 5 && i != -1);
	return i;
}

int Sieve7::NextNumber ()
{
	int i;
	do
	{
		i = _src.NextNumber ();
	} while (i % 7 == 0 && i != 7 && i != -1);
	return i;
}

int main ()
{
	SourceSieve src;
	Sieve2 s2 (src);
	Sieve3 s3 (s2);
	Sieve5 s5 (s3);
	Sieve7 s7 (s5);
	int i;
	for (;;)
	{
		i = s7.NextNumber ();
		if (i == -1)
			break;
		std::cout << i << " ";
	}	
}