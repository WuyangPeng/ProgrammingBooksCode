#ifndef SAFE_VECTORS
#define SAFE_VECTORS

#include <vector>

#include "d_except.h"

using namespace std;

template <typename T>
class safeVector: public vector<T>
{
	public:
		safeVector(): vector<T>()
		{}

		safeVector(T *first, T *last):
			vector<T>(first,last)
		{}

		safeVector(int n, const T& value = T()):
			vector<T>(n,value)
		{}

		T& operator[] (int i)
		{
			if (i < 0 || i >= size())
				throw indexRangeError(
					"safeVector: index range error", i, size());

			// execute the index operator in the vector base class
			// and pass it the argument i
			return vector<T>::operator[] (i);
		}
};

#endif	// SAFE_VECTORS
