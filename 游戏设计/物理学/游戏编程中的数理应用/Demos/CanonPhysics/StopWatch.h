// StopWatch.h
// Stopwatch class for high resolution timing.
// Starstone Software Systems, Inc.
// Code by Richard S. Wright Jr.
// March 23, 1999
// Original use - timer for frame rate calculation in Silicon Sky Demo

#ifndef SS_STOPWATCH_HEADER
#define SS_STOPWATCH_HEADER

#include <windows.h>

///////////////////////////////////////////////////////////////////////////////
// Starstone Simple Stopwatch class. Use this for high resolution timing 
// purposes (or, even low resolution timings)
class SS_StopWatch
{
	public:
		SS_StopWatch(void)	// Constructor
		{
			QueryPerformanceFrequency(&m_CounterFrequency);
			QueryPerformanceCounter(&m_LastCount);
		}

		// Resets timer (difference) to zero
		void Reset(void) { QueryPerformanceCounter(&m_LastCount); }					
		
		// Get elapsed time in seconds
		double GetElapsedSeconds(void)
		{
			LARGE_INTEGER lCurrent;
			QueryPerformanceCounter(&lCurrent);
			return double((lCurrent.QuadPart - m_LastCount.QuadPart) / double(m_CounterFrequency.QuadPart));
		}	
	
	protected:
		LARGE_INTEGER m_CounterFrequency;
		LARGE_INTEGER m_LastCount;
};

#pragma inline_depth()

#endif
