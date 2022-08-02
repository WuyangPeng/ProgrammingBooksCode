#include <iostream>
#include <time.h>

using namespace std;

// generate random numbers
class randomNumber
{
	public:
		// initialize the random number generator
		randomNumber(long s = 0);

		// return a 32-bit random integer m, 1 <= m <= 2^31-2
		long random();

		// return a 32-bit random integer m, 0 <= m <= n-1,
		// where n <= 2^31-1
		long random(long n);

		// return a real number x, 0 <= x < 1
		double frandom();

	private:
		static const long A;
		static const long M;
		static const long Q;
		static const long R;

		long seed;
};

const long randomNumber::A = 48271;
const long randomNumber::M = 2147483647;
const long randomNumber::Q = M / A;
const long randomNumber::R = M % A;

randomNumber::randomNumber(long s)
{
	if (s < 0)
		s = 0;

	if (s == 0)
	{
		// get time of day in seconds since 12:00 AM,
		// January 1, 1970
		long t_time = time(NULL);

		// mix-up bits by squaring
		t_time *= t_time;
		// result can overflow. handle cases
		// > 0, < 0, = 0
		if (t_time > 0)
			s = t_time ^ 0x5EECE66DL;
		else if (t_time < 0)
			s = (t_time & 0x7fffffff) ^ 0x5EECE66DL;
		else
			s = 0x5EECE66DL;
	}

	seed = s;
}

long randomNumber::random()
{
	long tmpSeed = A * ( seed % Q ) - R * ( seed / Q );

	if( tmpSeed >= 0 )
		 seed = tmpSeed;
	else
		 seed = tmpSeed + M;

	return seed;
}

long randomNumber::random(long n)
{
	double fraction = double(random())/double(M);

	return int(fraction * n);
}

double randomNumber::frandom()
{
	return double(random())/double(M);
}
