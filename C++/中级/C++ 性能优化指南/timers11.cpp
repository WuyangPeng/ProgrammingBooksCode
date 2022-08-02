# include <iostream>
# include <chrono>
# include "stopwatch11.h"

int test_timers11(int testno, unsigned long)
{
	typedef unsigned counter_t;
	counter_t const nCalls = 100000000;
	bool rc = true;
	switch (testno)
	{
	default: return -1;
	case 1:  return 1;	//	no module test
	case 0:  return 3;

	case 2: {
				std::chrono::system_clock::time_point tp;
				Stopwatch sw("100m std::chrono::system_clock::now() calls");
				for (counter_t i = 0; i < nCalls; ++i)
					tp = std::chrono::system_clock::now();
				break;
			}

	case 3: {
				 std::chrono::high_resolution_clock::time_point tp;
				 Stopwatch sw("100m std::chrono::high_resolution_clock::now() calls");
				 for (counter_t i = 0; i < nCalls; ++i)
					 tp = std::chrono::high_resolution_clock::now();
				 break;
			}
	}
	return rc ? 1 : 0;
}
