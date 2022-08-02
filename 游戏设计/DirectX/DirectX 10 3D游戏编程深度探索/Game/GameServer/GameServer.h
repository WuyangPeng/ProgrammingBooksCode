/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _GAMESERVER_H
#define _GAMESERVER_H

class cGameServer 
: public iGameObject
{
public:
	void Tick();
	void Initialize();
	void Shutdown();
	cGameServer();
	virtual ~cGameServer();

	//==========--------------------------	iGameObject
	virtual objID GetID(){ return g_gameServer; }
	virtual void SetID( objID id ) {}
	virtual UINT ProcMsg( const sMsg& msg );

	void ReliableSendToAllPlayers( cNetMessage& msg );
	void ReliableSendToAllPlayersExcept( cNetMessage& msg, objID exception );
	void UnreliableSendToAllPlayers( cNetMessage& msg );
	void ReliableSendToPlayer( cNetMessage& msg, objID player );
	void UnreliableSendToPlayer( cNetMessage& msg, objID player );

};

#endif // _GAMESERVER_H
