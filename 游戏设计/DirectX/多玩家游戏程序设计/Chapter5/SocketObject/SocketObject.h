//###################################################################################
//#																					#
//#			Chapter 7 - Socket Object Class Definition								#		
//#																					#
//#						Class to Handle Client/Server Communication					#
//#																					#
//#						Todd Barron, 08/06/2000										#
//#																					#
//###################################################################################

#ifndef SOCKET_OBJECT

#define SOCKET_OBJECT

// Windows Sockets Include, Also need ws2_32.lib included in project
#include <winsock.h>
#include <stdio.h>

// Class Object
class SocketObject  
{
	private:

	public:
		SOCKET						skSocket;
		int							iStatus;
		
		// Constructor
		SocketObject();
		// Desctrucot
		~SocketObject();

		// Accept a client's request to connect
		bool Accept(SocketObject& skAcceptSocket);
		// Listen for clients to connect to
		int Listen(void);
		// Open a server listening port
		int Bind(int iPort);
		// Close connection
		void Disconnect();
		// Connect to a server
		bool Connect(char* szServerAddress, int iPort);

		int Recv(char *szBuffer, int iBufLen, int iFlags);
		int Send(char *szBuffer, int iBufLen, int iFlags);
};

#endif
