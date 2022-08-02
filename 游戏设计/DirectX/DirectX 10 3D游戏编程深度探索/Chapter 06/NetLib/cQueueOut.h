/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/


// cQueueOut.h: interface for the cQueueOut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CQUEUEOUT_H__4A115C50_D1D4_11D3_AE4F_00E029031C67__INCLUDED_)
#define AFX_CQUEUEOUT_H__4A115C50_D1D4_11D3_AE4F_00E029031C67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "cMonitor.h"
#include "cDataPacket.h"
#include <list>
using namespace std;


class cQueueOut : public cMonitor  
{
protected:
  list<cDataPacket *> d_packets;
  DWORD               d_currentPacketID,
                      d_count;  // number of packets added to this queue.

public:
	cQueueOut();
	virtual ~cQueueOut();

	void        Clear();
	void        AddPacket( char *pData, unsigned short len );
  void        RemovePacket( DWORD packetID );
  bool        GetPacketForResend( DWORD waitTime, cDataPacket *pPacket );
  bool        GetPreviousPacket( DWORD packetID, cDataPacket *pPacket );
  cDataPacket *BorrowPacket( DWORD packetID );
  void        ReturnPacket();
  DWORD       GetLowestID();
  bool        IsEmpty();


  DWORD GetCurrentID()
  {
    return d_currentPacketID;
  }


  DWORD GetCount()
  {
    return d_count;
  }
};

#endif // !defined(AFX_CQUEUEOUT_H__4A115C50_D1D4_11D3_AE4F_00E029031C67__INCLUDED_)
