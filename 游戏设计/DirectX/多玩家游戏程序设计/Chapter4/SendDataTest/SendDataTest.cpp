//###################################################################################
//#																					#
//#			Chapter 4 - SendDataTest Program										#		
//#																					#
//#						Listens for Connections or Establishes Connections			#
//#																					#
//#						Todd Barron, 09/03/2000										#
//#																					#
//###################################################################################

// Standard Includes
#include <iostream.h>
#include "..\\SocketObject\\SocketObject.h"

void vServerConnection( int iListenPort );
void vClientConnection( char *szServerIP, int iServerListenPort );

//
// ----> Main Program Function (REQUIRED)
//
int main( int argc, char *argv[] )
{
	if( argc < 3 ) {
		cout << "----------------------------------------------------" << endl;
		cout << "               SendDataTest Help                    " << endl;
		cout << "----------------------------------------------------" << endl;
		cout << "Usage: SendDataTest [client/server] [ip,port/port]" << endl;
		cout << "" << endl;
		cout << "Example: SendDataTest client 198.168.0.1 6000" << endl;
		cout << "" << endl;
		cout << "Example: SendDataTest server 6000" << endl;
		cout << "" << endl;
		return( 0 );
	}
	
	//
	// If user selected server, listen on the given port 
	//
	if( !stricmp( argv[1], "server" ) )
	{
		vServerConnection( atoi( argv[2] ) );
	}
	//
	// User selected client, connect to given port and IP address
	//
	else {
		vClientConnection( argv[2], atoi( argv[3] ) );	
	}

	WSACleanup();
	
	return( 1 );
}

// Function for server
void vServerConnection( int iListenPort )
{
	SocketObject	ServerSocketObject;		
	SocketObject	ClientSocketObject;	
	char			DataPacket[128];		// Data Packet to Receive
	int				iBytesReceived = 0;		// # of Bytes Received
	
	cout << "<Server> Attempting to listen on Port " << iListenPort << endl;
	
	// Attempt to start the server
	if ( ServerSocketObject.Bind( iListenPort ) )
	{
		
		// Listen for connection on the Listen port
		ServerSocketObject.Listen();
		
		// Accept the connection
		ServerSocketObject.Accept( ClientSocketObject );
		
		cout << "<Server> Client Connected to Port " << iListenPort << endl;

		// Receive Data
		iBytesReceived = ClientSocketObject.Recv(DataPacket, 128, 0);

		cout << "<Server> Received " << iBytesReceived << " Bytes" << endl;
		
		cout << "<Server> Data Received = " << DataPacket << endl;
		
		// Disconnect the client
		ClientSocketObject.Disconnect();
		
		cout << "<Server> Client Disconnected" << endl;
	}
	else {
		cout << "<Server> Failed to Listen" << endl;
	}
}

// Function for client
void vClientConnection( char *szServerIP, int iServerListenPort )
{
	SocketObject	ClientSocketObject;
	char			DataPacket[128];		// Data Packet to Transmit
	int				iBytesSent = 0;			// # of Bytes Sent
	
	cout << "<Client> Connecting to " << szServerIP << ", Port " << iServerListenPort << endl;
	
	// Connect to the IP and Port 
	if( ClientSocketObject.Connect( szServerIP, iServerListenPort ) )
	{
		cout << "<Client> Connected" << endl;

		// Populate the data packet
		strcpy(DataPacket, "TestData from Client");
			
		// Send data
		iBytesSent = ClientSocketObject.Send(DataPacket, 128, 0);

		cout << "<Client> Transmitted " << iBytesSent << " Bytes" << endl;
		
		// Disconnect from the server
		ClientSocketObject.Disconnect();
		
		cout << "<Client> Disconnected From Server" << endl;
	}
	else {
		cout << "<Client> Failed to Connect" << endl;
	}
}





