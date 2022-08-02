//###################################################################################
//#																					#
//#			Chapter 4 - SimpleChat Program											#		
//#																					#
//#						Demonstrates Two-Way Communication							#
//#																					#
//#						Todd Barron, 09/05/2000										#
//#																					#
//###################################################################################

// Standard Includes
#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include "..\\SocketObject\\SocketObject.h"

struct stChatPacket
{
	stPacketHeader	stHeader;
	char			szChatMessage[128];
};

void vServerConnection( int iListenPort );
void vClientConnection( char *szServerIP, int iServerListenPort );

//
// ----> Main Program Function (REQUIRED)
//
int main( int argc, char *argv[] )
{
	if( argc < 3 ) {
		cout << "----------------------------------------------------" << endl;
		cout << "               SimpleChat Help                      " << endl;
		cout << "----------------------------------------------------" << endl;
		cout << "Usage: SimpleChat Help [client/server] [ip,port/port,port]" << endl;
		cout << "" << endl;
		cout << "Example: SimpleChat Help client 198.168.0.1 6000" << endl;
		cout << "" << endl;
		cout << "Example: SimpleChat Help server 6000 6001" << endl;
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
	
	return( 1 );
}

// Function for server
void vServerConnection( int iListenPort )
{
	SocketObject	ServerSocketObject;		// Server Socket Object
	SocketObject	ClientSocketObject;		// Client Socket Object
	char			DataPacket[128];		// Data Packet to Transmit
	int				iBytesReceived = 0;		// # of Bytes Received
	int				iBytesSent = 0;			// # of Bytes Sent
	char			szCommand[128];			// Chat Buffer
	char			szTempChar;
	int				i;
	stChatPacket	ChatPacket;
	char			szPacketBuffer[32768];
	
	cout << "<Server> Attempting to listen on Port " << iListenPort << endl;
	
	// Attempt to start the server
	if ( ServerSocketObject.Bind( iListenPort ) ) {
		
		// Listen for connection on the Listen port
		ServerSocketObject.Listen( );
		
		// Accept the connection
		ServerSocketObject.Accept( ClientSocketObject );
		
		cout << "<Server> Client Connected to Port " << iListenPort << endl;
		
		// Loop forever or until a break is issued
		while( 1 ) {
			printf("\n<Server> ");
			
			// Loop through getting up to 127 characters to transmit, leave room for \n code
			for( i = 0; i < 127; i++ ) {
				// Loop until a key is pressed
				while( !_kbhit() ) {
					// Check for incomming data
					iBytesReceived = ClientSocketObject.vGetPacket(szPacketBuffer);
					if( iBytesReceived > 0 ) {
						// Copy the received data into the chat packet
						memcpy(&ChatPacket,szPacketBuffer,sizeof(ChatPacket));
						strcpy(DataPacket,ChatPacket.szChatMessage);
						if( !stricmp( DataPacket, "/exit" ) ) {
							break;
						}
						else {
							cout << endl << "<Client> " << DataPacket << endl;
							printf("<Server> ");
						}
					}
				}
				// Quit chatting if /exit command given
				if( !stricmp( DataPacket, "/exit" ) ) {
					break;
				}
				// Get next key from keyboard input buffer
				szTempChar = getche();
				// Add the keypress to our command string
				szCommand[i] = szTempChar;
				// Check for enter key
				if( szTempChar == 13 ) {
					break;
				}
			}
			// Check for user initiated exit code
			if( !stricmp( DataPacket, "/exit" ) ) {
				break;
			}
			// Null Terminate the command
			szCommand[i] = '\0';
			// Populate the packet
			strcpy(DataPacket,szCommand);
			
			// Quit chatting if /exit command given
			if( !stricmp( szCommand, "/exit" ) ) {
				break;
			}
			else {	
				// Load the packet data
				ChatPacket.stHeader.iID = 0;
				ChatPacket.stHeader.iType = 0;
				ChatPacket.stHeader.iLength = 128;
				ChatPacket.stHeader.iSender = 0;
				strcpy(ChatPacket.szChatMessage,DataPacket);
				ChatPacket.stHeader.iCheckSum = 128;
				// Load the packet buffer
				memcpy(szPacketBuffer,&ChatPacket,sizeof(stChatPacket));
				// Send the data
				iBytesSent = ClientSocketObject.Send(szPacketBuffer,sizeof(stPacketHeader)+128,0);
				// Check if client has disconnected
				if( iBytesSent == -1 ) {
					cout << "<Server> Client No Longer Online" << endl;
					break;
				}	
			}
		}
		
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
	SocketObject	ClientSocketObject;		// Client Socket Object
	char			DataPacket[128];		// Data Packet to Transmit
	int				iBytesReceived = 0;		// # of Bytes Received
	int				iBytesSent = 0;			// # of Bytes Sent
	char			szCommand[128];			// Chat Buffer
	char			szTempChar;
	int				i;
	char			szPacketBuffer[32768];
	stChatPacket	ChatPacket;
	
	cout << "<Client> Connecting to " << szServerIP << ", Port " << iServerListenPort << endl;
	
	// Connect to the IP and Port 
	if( ClientSocketObject.Connect( szServerIP, iServerListenPort ) ) {
		cout << "<Client> Connected" << endl;
		
		// Keep Chatting until a /exit is given
		while( 1 ) {
			printf("\n<Client> ");
			
			// Loop through getting up to 127 characters to transmit, leave room for \n code
			for( i = 0; i < 127; i++ ) {
				// Loop until a key is pressed
				while( !_kbhit() ) {
					// Check for incomming data
					iBytesReceived = ClientSocketObject.vGetPacket(szPacketBuffer);
					if( iBytesReceived ) {
						// Copy the received data into the chat packet
						memcpy(&ChatPacket,szPacketBuffer,sizeof(ChatPacket));
						strcpy(DataPacket,ChatPacket.szChatMessage);
						cout << endl << "<Server> " << DataPacket << endl;
						printf("<Client> ");
					}
				}
				// Get next key from keyboard input buffer
				szTempChar = getche();
				// Add the keypress to our command string
				szCommand[i] = szTempChar;
				// Check for enter key
				if( szTempChar == 13 ) 
					break;
			}
			// Null Terminate the command
			szCommand[i] = '\0';
			// Populate the packet
			strcpy(DataPacket,szCommand);
			// Quit chatting if /exit command given
			if( !stricmp( szCommand, "/exit" ) ) {
				break;
			}
			else {	
				// Load the packet data
				ChatPacket.stHeader.iID = 0;
				ChatPacket.stHeader.iType = 0;
				ChatPacket.stHeader.iLength = 128;
				ChatPacket.stHeader.iSender = 0;
				strcpy(ChatPacket.szChatMessage,DataPacket);
				ChatPacket.stHeader.iCheckSum = 128;
				// Load the packet buffer
				memcpy(szPacketBuffer,&ChatPacket,sizeof(stChatPacket));
				// Send the data
				iBytesSent = ClientSocketObject.Send(szPacketBuffer,sizeof(stPacketHeader)+128,0);
				// Check if client has disconnected
				if( iBytesSent == -1 ) {
					cout << "<Server> Client No Longer Online" << endl;
					break;
				}	
				
				// Check for server disconnection
				if( iBytesSent == -1 ) {
					cout << "<Client> Server No Longer Online" << endl;
					break;
				}	
				
				// Quit chatting if /exit command given
				if( !stricmp( szCommand, "/exit" ) ) {
					break;
				}
			}
		}
		
		// Disconnect from the server
		ClientSocketObject.Disconnect();
		
		cout << "<Client> Disconnected From Server" << endl;
	}
	else {
		cout << "<Client> Failed to Connect" << endl;
	}
}
