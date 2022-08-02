#include "CTimer.h"

//---------------------- default constructor ------------------------------
//
//-------------------------------------------------------------------------

CTimer::CTimer(): m_FPS(0),
				          m_TimeElapsed(0.0f),
				          m_FrameTime(0),
				          m_LastTime(0),
				          m_PerfCountFreq(0)
{
	//how many ticks per sec do we get
	QueryPerformanceFrequency( (LARGE_INTEGER*) &m_PerfCountFreq);
	
	m_TimeScale = 1.0f/m_PerfCountFreq;
}

//---------------------- constructor -------------------------------------
//
//	use to specify FPS
//
//-------------------------------------------------------------------------

CTimer::CTimer(float fps): m_FPS(fps),
						               m_TimeElapsed(0.0f),
						               m_LastTime(0),
						               m_PerfCountFreq(0)
{

	//how many ticks per sec do we get
	QueryPerformanceFrequency( (LARGE_INTEGER*) &m_PerfCountFreq);

	m_TimeScale = 1.0f/m_PerfCountFreq;

	//calculate ticks per frame
	m_FrameTime = (LONGLONG)(m_PerfCountFreq / m_FPS);
}


//------------------------Start()-----------------------------------------
//
//	call this immediately prior to game loop. Starts the timer (obviously!)
//
//--------------------------------------------------------------------------
void CTimer::Start()
{
	//get the time
	QueryPerformanceCounter( (LARGE_INTEGER*) &m_LastTime);

	//update time to render next frame
	m_NextTime = m_LastTime + m_FrameTime;

	return;
}

//-------------------------ReadyForNextFrame()-------------------------------
//
//	returns true if it is time to move on to the next frame step. To be used if
//	FPS is set.
//
//----------------------------------------------------------------------------
bool CTimer::ReadyForNextFrame()
{
	if (!m_FPS)
  {
    MessageBox(NULL, "No FPS set in timer", "Doh!", 0);

    return false;
  }
  
  QueryPerformanceCounter( (LARGE_INTEGER*) &m_CurrentTime);

	if (m_CurrentTime > m_NextTime)
	{

		m_TimeElapsed	= (m_CurrentTime - m_LastTime) * m_TimeScale;
		m_LastTime		= m_CurrentTime;

		//update time to render next frame
		m_NextTime = m_CurrentTime + m_FrameTime;

		return true;
	}

	return false;
}

//--------------------------- TimeElapsed --------------------------------
//
//	returns time elapsed since last call to this function. Use in main
//	when calculations are to be based on dt.
//
//-------------------------------------------------------------------------
double CTimer::TimeElapsed()
{
	QueryPerformanceCounter( (LARGE_INTEGER*) &m_CurrentTime);
	
	m_TimeElapsed	= (m_CurrentTime - m_LastTime) * m_TimeScale;
	
	m_LastTime		= m_CurrentTime;

	return m_TimeElapsed;
		
}
