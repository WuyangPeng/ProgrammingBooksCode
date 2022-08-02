#ifndef _TIMER_H_
#define _TIMER_H_

// Timer class used for calculating and/or restricting framerate

class Timer
{
private:
	LARGE_INTEGER freq;
	LARGE_INTEGER start;

public:
	Timer()
	{
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);
	}
	~Timer() { }

	// Resets timer to zero
	void Reset()
	{
		QueryPerformanceCounter(&start);
	}					
	
	// Get elapsed time in seconds
	float getElapsedTime()
	{
		// Get the current count
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);

		return (float)(current.QuadPart - start.QuadPart) / freq.QuadPart;
	}	

};


#endif
