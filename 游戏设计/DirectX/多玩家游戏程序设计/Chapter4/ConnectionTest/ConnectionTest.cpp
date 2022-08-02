//###################################################################################
//#																					#
//#			Chapter 4 - Connection Program											#		
//#																					#
//#						Listens for Connections or Establishes Connections			#
//#																					#
//#						Todd Barron, 08/06/2000										#
//#																					#
//###################################################################################

// Standard Includes
#include <iostream.h>
#include "..\\socketobject\\SocketObject.h"

void vServerConnection( int iListenPort );
void vClientConnection( char *szServerIP, int iServerListenPort );

//
// ----> Main Program Function (REQUIRED)
//
int main( int argc, char *argv[] )
{
	if( argc < 3 ) {
		cout << "----------------------------------------------------" << endl;
		cout << "               ConnectionTest Help                  " << endl;
		cout << "----------------------------------------------------" << endl;
		cout << "Usage: ConnectionTest [client/server] [ip,port/port]" << endl;
		cout << "" << endl;
		cout << "Example: ConnectionTest client 198.168.0.1 6000" << endl;
		cout << "" << endl;
		cout << "Example: ConnectionTest server 6000" << endl;
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
void vServerConnection( int iListenPort  )
{
	SocketObject	ServerSocketObject;		
	SocketObject	ClientSocketObject;		
	
	cout << "<Server> Attempting to listen on Port " << iListenPort << endl;
	
	// Attempt to start the server on port 6000
	if ( ServerSocketObject.Bind( iListenPort ) )
	{
		cout << "<Server> Listening" << endl;
		
		// Listen for connection on the Listen port, 
		ServerSocketObject.Listen();
		
		// Accept the connection
		ServerSocketObject.Accept( ClientSocketObject );
		
		cout << "<Server> Client Connected to Port " << iListenPort << endl;
		
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
	
	cout << "<Client> Connecting to " << szServerIP << ", Port " << iServerListenPort << endl;
	
	// Connect to the IP and Port 
	if( ClientSocketObject.Connect( szServerIP, iServerListenPort ) )
	{
		cout << "<Client> Connected" << endl;
		
		// Disconnect from the server
		ClientSocketObject.Disconnect();
		
		cout << "<Client> Disconnected From Server" << endl;
	}
	else {
		cout << "<Client> Failed to Connect" << endl;
	}
}


