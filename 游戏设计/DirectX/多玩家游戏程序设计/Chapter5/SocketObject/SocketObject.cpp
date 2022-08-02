//###################################################################################
//#																					#
//#						Socket Object Member Functions								#		
//#																					#
//#						Class to Handle Client/Server Communication					#
//#																					#
//#						Todd Barron, 08/06/2000										#
//#																					#
//###################################################################################

#include "SocketObject.h"

// Constructor
SocketObject::SocketObject()
{
	WSADATA wsaData;
	WORD	wVersionRequested;

	wVersionRequested = MAKEWORD( 2, 0 );

	skSocket = INVALID_SOCKET;
	iStatus = WSAStartup(wVersionRequested,&wsaData);
}

// Destructor
SocketObject::~SocketObject()
{
	Disconnect();
}

// Connect
bool SocketObject::Connect(char* szServerAddress, int iPort)
{
	struct		sockaddr_in serv_addr;
	LPHOSTENT	lphost;

	memset(&serv_addr,0,sizeof(sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(szServerAddress);

	if (serv_addr.sin_addr.s_addr == INADDR_NONE)
	{
		lphost = gethostbyname(szServerAddress);
		if (lphost != NULL)
			serv_addr.sin_addr.s_addr = ((LPIN_ADDR)lphost->h_addr)->s_addr;
		else
		{
			WSASetLastError(WSAEINVAL);
			return FALSE;
		}
	}

	serv_addr.sin_port = htons(iPort);

	// Open the socket
	skSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(skSocket == INVALID_SOCKET)
	{
		return false;
	}

	int err = connect(skSocket, (struct sockaddr*)&serv_addr,sizeof(sockaddr));
	if(err == SOCKET_ERROR)
	{
		Disconnect();
		return false;
	}

	return true;
}

void SocketObject::Disconnect()
{
	if(skSocket != INVALID_SOCKET)
	{
		closesocket(skSocket);
		skSocket = INVALID_SOCKET;
	}
}

int SocketObject::Bind(int iPort)
{
	sockaddr_in saServerAddress;

	skSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	if(skSocket == INVALID_SOCKET)
	{
		return false;
	}

	memset(&saServerAddress, 0, sizeof(sockaddr_in));

	saServerAddress.sin_family = AF_INET;
	saServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	saServerAddress.sin_port = htons(iPort);

	if( bind(skSocket, (sockaddr*) &saServerAddress, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		Disconnect();
		return false;
	}
	else
		return true;
}

int SocketObject::Listen( void )
{
	return listen( skSocket, 32 );
}

bool SocketObject::Accept( SocketObject &skAcceptSocket )
{
	sockaddr_in saClientAddress;
	int			iClientSize = sizeof(sockaddr_in);
	SOCKADDR	IPAddress;

	skAcceptSocket.skSocket = accept( skSocket, (struct sockaddr*)&saClientAddress, &iClientSize );
	
	if( skAcceptSocket.skSocket == INVALID_SOCKET ) 
	{
		return false;
	}
	else 
	{
		memcpy(&IPAddress,&saClientAddress,sizeof(saClientAddress));
		// Enable this to ouput who is connecting
		//printf("%d.%d.%d.%d is Connecting\n",saClientAddress.sin_addr.S_un.S_un_b.s_b1,saClientAddress.sin_addr.S_un.S_un_b.s_b2,saClientAddress.sin_addr.S_un.S_un_b.s_b3,saClientAddress.sin_addr.S_un.S_un_b.s_b4);
		return true;
	}
}

int SocketObject::Recv( char *szBuffer, int iBufLen, int iFlags)
{
	return recv(skSocket, szBuffer, iBufLen, iFlags);
}

int SocketObject::Send(char *szBuffer, int iBufLen, int iFlags)
{
	return send(skSocket,szBuffer,iBufLen,iFlags);
}

