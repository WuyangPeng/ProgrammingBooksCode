/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/


// cUnreliableQueueIn.h: interface for the cUnreliableQueueIn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUNRELIABLEQUEUEIN_H__8E4CCAC1_D4DB_11D3_AE4F_00E029031C67__INCLUDED_)
#define AFX_CUNRELIABLEQUEUEIN_H__8E4CCAC1_D4DB_11D3_AE4F_00E029031C67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "cMonitor.h"
#include "cDataPacket.h"
#include <list>
using namespace std;


class cUnreliableQueueIn : public cMonitor
{
  list<cDataPacket *> d_packets;
  DWORD               d_currentPacketID;

public:
	cUnreliableQueueIn();
	virtual ~cUnreliableQueueIn();

  void        Clear();
	void        AddPacket( DWORD packetID, char *pData, unsigned short len, DWORD receiveTime );
	cDataPacket *GetPacket();
};

#endif // !defined(AFX_CUNRELIABLEQUEUEIN_H__8E4CCAC1_D4DB_11D3_AE4F_00E029031C67__INCLUDED_)
