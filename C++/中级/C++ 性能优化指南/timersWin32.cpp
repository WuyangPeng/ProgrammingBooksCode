# include <iostream>
# include <time.h>
# include <Windows.h>
# include "test_driver.h"

int test_timers_Win32(int testno, unsigned long)
{
	typedef unsigned counter_t;
	counter_t const nCalls = 100000000;
	bool rc = true;
	switch (testno)
	{
	default: return -1;
	case 0:  return 3;
	case 1:  return 1;	//	no module test

	case 2:	
		{//	time() latency
			ULONG start = GetTickCount();
			time_t count;
			for (counter_t i = 0; i < nCalls; ++i)
				count = time(0);
			ULONG stop = GetTickCount();
			std::cout << stop - start << "mS for 100m time() calls" << std::endl;
		}
		{//	clock() latency
			ULONG start = GetTickCount();
			clock_t count;
			for (counter_t i = 0; i < nCalls; ++i)
				count = clock();
			ULONG stop = GetTickCount();
			std::cout << stop - start << "mS for 100m clock() calls" << std::endl;
		}
		{// GetTickCount() latency
			ULONG start = GetTickCount();
			ULONG count;
			for (counter_t i = 0; i < nCalls; ++i)
				count = GetTickCount();
			ULONG stop = GetTickCount();
			std::cout << stop - start << "mS for 100m GetTickCount() calls" << std::endl;
		}
		{// QueryPerformanceCounter() latency
			LARGE_INTEGER freq;
			QueryPerformanceFrequency(&freq);
			ULONG start = GetTickCount();
			LARGE_INTEGER count3;
			for (counter_t i = 0; i < nCalls; ++i)
				QueryPerformanceCounter(&count3);
			ULONG stop = GetTickCount();
			std::cout << stop - start << "mS for 100m QueryPerformanceCounter() calls" << std::endl;
		}
		{//	GetSystemTimeAsFileTime() latency
			ULONG start = GetTickCount();
			FILETIME ft;
			for (counter_t i = 0; i < nCalls; ++i)
				GetSystemTimeAsFileTime(&ft);
			ULONG stop = GetTickCount();
			std::cout << stop - start << "mS for 100m GetSystemTimeAsFileTime() calls" << std::endl;
		}
#	if _MSC_VER > 1600
		{//	GetSystemTimePreciseAsFileTime() latency
			ULONG start = GetTickCount();
			FILETIME ft;
			for (counter_t i = 0; i < nCalls; ++i)
				GetSystemTimePreciseAsFileTime(&ft);
			ULONG stop = GetTickCount();
			std::cout << stop - start << "mS for 100m GetSystemTimePreciseAsFileTime() calls" << std::endl;
		}
#	endif
		{//	timeGetTime() latency
			DWORD time;
			ULONG start = GetTickCount();
			for (counter_t i = 0; i < nCalls; ++i)
				time = timeGetTime();
			ULONG stop = GetTickCount();
			std::cout << stop - start << "mS for 100m timeGetTime() calls" << std::endl;
			break;
		}
		{// GetTickCount64() latency
			ULONGLONG ticks;
			ULONG start = GetTickCount();
			for (counter_t i = 0; i < nCalls; ++i)
				ticks = GetTickCount64();
			ULONG stop = GetTickCount();
			std::cout << stop - start << "mS for 100m GetTickCount64() calls" << std::endl;
		}
		break;

	case 3:
		{//	clock() mean resolution
			unsigned nz_count = 0, nz_sum = 0;
			clock_t last, next;
			for (last = clock(); nz_count < 100; last = next) {
				next = clock();
				if (next != last) {
					nz_count += 1;
					nz_sum += (next - last);
				}
			}
			std::cout << "clock() mean resolution "
				<< (double)nz_sum / nz_count
				<< " ticks" << std::endl;
			std::cout << "clock() TICKS_PER_SEC " 
				<< CLOCKS_PER_SEC 
				<< " ticks" << std::endl;
		}
		{//	GetTickCount() mean resolution
			unsigned nz_count = 0, nz_sum = 0;
			ULONG last, next;
			for (last = GetTickCount(); nz_count < 100; last = next) {
				next = GetTickCount();
				if (next != last) {
					nz_count += 1;
					nz_sum += (next - last);
				}
			}
			std::cout << "GetTickCount() mean resolution "
				<< (double)nz_sum / nz_count
				<< " ticks" << std::endl;
		}
		{//	QueryPerformanceCounter() mean resolution
			unsigned nz_count = 0, nz_sum = 0;
			LARGE_INTEGER last, next;
			QueryPerformanceCounter(&last);
			for (/*empty*/; nz_count < 100; last = next) {
				QueryPerformanceCounter(&next);
				if (next.LowPart != last.LowPart) {
					nz_count += 1;
					nz_sum   += (next.LowPart - last.LowPart);
				}
			}
			std::cout << "QueryPerformanceCounter() mean resolution "
				<< (double)nz_sum / nz_count
				<< " ticks" << std::endl;
			LARGE_INTEGER freq;
			if (QueryPerformanceFrequency(&freq) == TRUE)
				std::cout << "QueryPerformanceFrequency() is "
							<< freq.QuadPart << "/sec" << std::endl;
		}
		{//	GetSystemTimeAsFileTime() mean resolution
			unsigned nz_count = 0, nz_sum = 0;
			FILETIME last, next;
			GetSystemTimeAsFileTime(&last);
			for (/*empty*/; nz_count < 100; last = next) {
				GetSystemTimeAsFileTime(&next);
				if (next.dwLowDateTime != last.dwLowDateTime) {
					nz_count += 1;
					nz_sum += (next.dwLowDateTime - last.dwLowDateTime);
				}
			}
			std::cout << "GetSystemTimeAsFileTime() mean resolution "
				<< (double)nz_sum / nz_count
				<< " ticks" << std::endl;
		}
#	if _MSC_VER > 1600
		{// GetSystemTimePreciseAsFileTime() mean resolution
			unsigned nz_count = 0, nz_sum = 0;
			FILETIME last, next;
			GetSystemTimePreciseAsFileTime(&last);
			for (/*empty*/; nz_count < 100; last = next) {
				GetSystemTimePreciseAsFileTime(&next);
				if (next.dwLowDateTime != last.dwLowDateTime) {
					nz_count += 1;
					nz_sum += (next.dwLowDateTime - last.dwLowDateTime);
				}
			}
			std::cout << "GetSystemTimePreciseAsFileTime() mean resolution "
				<< (double)nz_sum / nz_count
				<< " ticks" << std::endl;
		}
		{// timeGetTime() mean resolution
			unsigned nz_count = 0, nz_sum = 0;
			ULONG last, next;
			for (last = timeGetTime(); nz_count < 100; last = next) {
				next = timeGetTime();
				if (next != last) {
					nz_count += 1;
					nz_sum += (next - last);
				}
			}
			std::cout << "timeGetTime() mean resolution "
				<< (double)nz_sum / nz_count
				<< " ticks" << std::endl;
		}
#	endif
		{// GetTickCount64() mean resolution
			unsigned nz_count = 0, nz_sum = 0;
			ULONGLONG last, next;
			for (last = GetTickCount64(); nz_count < 100; last = next) {
				next = GetTickCount64();
				if (next != last) {
					nz_count += 1;
					nz_sum += (next - last);
				}
			}
			std::cout << "GetTickCount64() mean resolution "
				<< (double)nz_sum / nz_count
				<< " ticks" << std::endl;
		}
		break;
	}
	return rc ? 1 : 0;
}


int test_timers_Win32(int test_no, unsigned long);
int test_timers11(int test_no, unsigned long);
int test_stopwatch03(int test_no, unsigned long);
int test_stopwatch11(int test_no, unsigned long);

int (*funclist[])(int, unsigned long) = {
	test_timers_Win32, 
# if _MSC_VER > 1600
    test_timers11,
# endif
	test_stopwatch03, 
# if _MSC_VER > 1600
	test_stopwatch11,
# endif
	0
};

int main(int argc, char** argv) {
	test_driver(funclist, argc, argv);
    return 0;
}// end main