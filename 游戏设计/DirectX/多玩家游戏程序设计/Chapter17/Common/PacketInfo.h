//-----------------------------------------------------------------------------------
// Packet Structures
//-----------------------------------------------------------------------------------
#define PACKET_TYPE_GENERIC				0
#define PACKET_TYPE_CHAT				1
#define PACKET_TYPE_ANGLE				2
#define PACKET_TYPE_VELOCITY			3
#define PACKET_TYPE_POSITION			4
#define PACKET_TYPE_CHANGEPOSITION		5
#define PACKET_TYPE_ATTITUDE			6

#define PACKET_TYPE_ZONECHANGE			18
#define PACKET_TYPE_REQUESTPLAYERINFO	19
#define PACKET_TYPE_ADDPLAYER			20	
#define PACKET_TYPE_REMOVEPLAYER		21	
#define PACKET_TYPE_TIMECHANGE			30

#define PACKET_TYPE_REQUESTPASSWORD		50
#define PACKET_TYPE_SUBMITPASSWORD		51

#define PACKET_TYPE_BOOTPLAYER			52
#define PACKET_TYPE_MESSAGE				53

#define PACKET_TYPE_CREATEPLAYER		75
#define PACKET_TYPE_DESTROYPLAYER		76

#define PACKET_TYPE_GAMEUPDATE			100

class	PacketGeneric
{
	public:
		DWORD	dwType;
		DWORD	dwSize;
		int		iPlayerID;
};

class	PacketChat : public PacketGeneric
{
	public:
		char	szText[128];
};

class	PacketAngle : public PacketGeneric
{
	public:
		float	fAngle;
};

class	PacketVelocity : public PacketGeneric
{
	public:
		float	fVelocity;
};

class	PacketPosition : public PacketGeneric
{
	public:
		float	fx;
		float	fz;
};

class	PacketAttitude : public PacketGeneric
{
	public:
		float	fVelocity;
		float	fx;
		float	fz;
		float	fRot;
};

class	PacketPlayerInfo : public PacketGeneric
{
	public:
		int							iPlayerID;
		CLIENT_PLAYER_INFORMATION	piInfo;
};

class	PacketRequestPlayerInfo : public PacketGeneric
{
	public:
		int	iPlayerID;
};

class	PacketRemovePlayer : public PacketGeneric
{
	public:
		int	iPlayerID;
};

class	PacketZoneChange : public PacketGeneric
{
	public:
		int		iZone;
		int		iZoneMap;
		float	fXPos;
		float	fZPos;
		float	fRot;
		long	lNumbPlayers;
};

class	PacketTimeChange : public PacketGeneric
{
	public:
		int		iTime;
};

class	PacketPasswordSubmit : public PacketGeneric
{
	public:
		char szPassword[32];
};

class	PacketMessage : public PacketGeneric
{
	public:
		char		szMessage[64];
		D3DCOLOR	color;
};
