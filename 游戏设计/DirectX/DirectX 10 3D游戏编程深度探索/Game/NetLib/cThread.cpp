/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

// cThread.cpp: implementation of the cThread class.
//
//////////////////////////////////////////////////////////////////////

#include "cThread.h"
#include "cNetError.h"

//////////////////////////////////////////////////////////////////////

static DWORD WINAPI cThreadProc( cThread *pThis )
{
  return pThis->ThreadProc();
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cThread::cThread() : cMonitor()
{
  d_threadID = 0;
  d_threadHandle = NULL;
  d_bIsRunning = false;
}


cThread::~cThread()
{
  End();
}


void cThread::Begin()
{
  // Start the thread.
  d_threadHandle = CreateThread( NULL,
                                 0,
                                 (LPTHREAD_START_ROUTINE)cThreadProc,
                                 this,
                                 0,
                                 (LPDWORD)&d_threadID );
  if( d_threadHandle == NULL )
    throw cNetError( L"cThread() - Thread creation failed." );
  d_bIsRunning = true;
}


void cThread::End()
{
  if( d_threadHandle != NULL )
  {
    d_bIsRunning = false;
    WaitForSingleObject( d_threadHandle, INFINITE );
    CloseHandle( d_threadHandle );
    d_threadHandle = NULL;
  }
}


DWORD cThread::ThreadProc()
{
  return 0;
}
////////////////////////////////////////////////////////////////////////////////

void cThread::SetError( const TCHAR *pBuffer )
{
  if( pBuffer == NULL )
    wcscpy_s( d_errorBuffer, 1000, L"Unspecified." );
  else
  {
    if( sizeof( d_errorBuffer ) > wcslen( pBuffer ) )
      wcscpy_s( d_errorBuffer, 1000, pBuffer );
    else
    {
      wcsncpy_s( d_errorBuffer, 1000, pBuffer, sizeof( d_errorBuffer ) );
      d_errorBuffer[ sizeof( d_errorBuffer ) - 1 ] = '\0';
    }
  }
}


const TCHAR *cThread::Error()
{
  return (const TCHAR *)d_errorBuffer;
}


bool cThread::IsRunning()
{
  return d_bIsRunning;
}

