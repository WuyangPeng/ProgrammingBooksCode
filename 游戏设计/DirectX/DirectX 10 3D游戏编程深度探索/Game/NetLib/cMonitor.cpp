/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/


// cMonitor.cpp: implementation of the cMonitor class.
//
//////////////////////////////////////////////////////////////////////

#include "cMonitor.h"
#include "cNetError.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cMonitor::cMonitor()
{
  // This mutex will help the two threads share their toys.
  d_mutex = CreateMutex( NULL, false, NULL );
  if( d_mutex == NULL )
    throw cNetError( L"cMonitor() - Mutex creation failed." );
}

cMonitor::~cMonitor()
{
  if( d_mutex != NULL )
  {
    CloseHandle( d_mutex );
    d_mutex = NULL;
  }
}


void cMonitor::MutexOn() const
{
  WaitForSingleObject( d_mutex, INFINITE );  
}


void cMonitor::MutexOff() const
{
  ReleaseMutex( d_mutex );
}

