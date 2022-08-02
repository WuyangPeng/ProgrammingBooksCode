//###################################################################################
//#																					#
//#			Chapter 4 - UberClient Program											#		
//#																					#
//#						Game Client													#
//#																					#
//#						Todd Barron, 10/09/2000										#
//#																					#
//###################################################################################

// Standard Includes
#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include "..\\..\\SocketObject\\SocketObject.h"
#include "..\\Packets.h"

void vClientConnection( char *szServerIP, int iServerListenPort );

//
// ----> Main Program Function (REQUIRED)
//
int main( int argc, char *argv[] )
{
	if( argc < 3 ) {
		cout << "----------------------------------------------------" << endl;
		cout << "               UberClient Help                      " << endl;
		cout << "----------------------------------------------------" << endl;
		cout << "Usage: UberClient [server ip] [server port]" << endl;
		cout << "" << endl;
		cout << "Example: UberClient 198.168.0.1 6000" << endl;
		cout << "" << endl;
		return( 0 );
	}
	
	//
	// User selected client, connect to given port and IP address
	//
	else {
		vClientConnection( argv[1], atoi( argv[2] ) );	
	}
	
	return( 1 );
}

// Function for client
void vClientConnection( char *szServerIP, int iServerListenPort )
{
	SocketObject				ClientSocketObject;		// Client Socket Object
	int							iBytesReceived = 0;		// # of Bytes Received
	int							iBytesSent = 0;			// # of Bytes Sent
	char						szCommand[128];			// Chat Buffer
	char						szPacketBuffer[128000];
	int							i;
	int							iMyID = 0;
	stPlayerIDResponsePacket	stPlayerIDPacket;	
	stPacketHeader				stHeaderPacket;
	stPlayerCommandPacket		stPlayerCommand;
	stTextResponsePacket		stTextResponse;
	int							iLastPacketSent = 0;
		
	cout << "Connecting to " << szServerIP << ", Port " << iServerListenPort << endl;
	
	// Connect to the IP and Port 
	if( ClientSocketObject.Connect( szServerIP, iServerListenPort ) )
	{
		// Loop until we get an ID packet back from the server
		while( 1 ) {
			iBytesReceived = ClientSocketObject.vGetPacket(szPacketBuffer);
			//  Process the Packet
			if( iBytesReceived ) {
				// Check the header
				memcpy(&stHeaderPacket,szPacketBuffer,sizeof(stHeaderPacket));
				// Check if type equals ID packet
				if( stHeaderPacket.iType == PACKET_PLAYERID ) {
					memcpy(&stPlayerIDPacket,szPacketBuffer,sizeof(stPlayerIDPacket));
					iMyID = stPlayerIDPacket.iID;
					break;
				}
			}
		}

		printf("\n\n\n\n\n\n=========================================\n");
		printf("Welcome to UberAdventure!\n");
		printf("\n");
		printf("Use the command of ? for help\n");
		printf("\n");
		printf("You are player# %d\n", iMyID);
		printf("=========================================\n");
		
		//
		// Issue first packet to look around for player
		//
		// Setup Header Information
		stPlayerCommand.stHeader.iID = iLastPacketSent;
		stPlayerCommand.stHeader.iType = PACKET_PLAYERCOMMAND;
		stPlayerCommand.stHeader.iLength = 96;
		stPlayerCommand.stHeader.iSender = iMyID;
		stPlayerCommand.stHeader.iCheckSum = ((iLastPacketSent+PACKET_PLAYERCOMMAND+96));
					
		sprintf(stPlayerCommand.szTarget,"around");
		sprintf(stPlayerCommand.szCommand,"look");
		sprintf(stPlayerCommand.szPlayerID,"%d",iMyID);
		memcpy(szPacketBuffer,&stPlayerCommand,sizeof(stPlayerCommand));
		// Send data
		iBytesSent = ClientSocketObject.Send(szPacketBuffer, sizeof(stPlayerCommand), 0);
		iLastPacketSent++;
		
		// Check for server disconnection
		if( iBytesSent == -1 ) {
			cout << "Server No Longer Online" << endl;
			exit(1);
		}
		else {
			// Loop until we get a response from the server
			while( 1 ) {
				iBytesReceived = ClientSocketObject.vGetPacket(szPacketBuffer);
				//  Process the Packet
				if( iBytesReceived ) {
					// Check the header
					memcpy(&stHeaderPacket,szPacketBuffer,sizeof(stHeaderPacket));
					// Check if a text response packet
					if( stHeaderPacket.iType == PACKET_TEXTRESPONSE ) {
						memcpy(&stTextResponse,&szPacketBuffer,sizeof(stTextResponse));
						printf("=========================================\n");
						printf("%s",stTextResponse.szResponse);
						printf("=========================================\n");
						break;
					}
				}
			}
		}

		// Play Game Loop
		while( 1 ) 
		{
			printf("\nCommand: ");
			gets(szCommand);

			// Find the end of the command segment
			i = 0;
			while( szCommand[i] != 32 ) {
				if( szCommand[i] == '\0' ) {
					// Invalid target
					i = -1;
					break;
				}
				i++;
			}
			//
			// Send The Packet
			//

			// Setup Header Information
			stPlayerCommand.stHeader.iID = iLastPacketSent;
			stPlayerCommand.stHeader.iType = PACKET_PLAYERCOMMAND;
			stPlayerCommand.stHeader.iLength = 96;
			stPlayerCommand.stHeader.iSender = iMyID;
			stPlayerCommand.stHeader.iCheckSum = ((iLastPacketSent+PACKET_PLAYERCOMMAND+96));

			// Fill in target if one was specified
			if( i != -1 ) {
				sprintf(stPlayerCommand.szTarget,&szCommand[(i+1)]);
			}
			else {
				sprintf(stPlayerCommand.szTarget,"");
			}
			sprintf(stPlayerCommand.szCommand,szCommand);
			stPlayerCommand.szCommand[i] = '\0';
			sprintf(stPlayerCommand.szPlayerID,"%d",iMyID);
			memcpy(szPacketBuffer,&stPlayerCommand,sizeof(stPlayerCommand));
			// Send data
			iBytesSent = ClientSocketObject.Send(szPacketBuffer, sizeof(stPlayerCommand), 0);
			iLastPacketSent++;
			
			// Check for server disconnection
			if( iBytesSent == -1 ) {
				cout << "Server No Longer Online" << endl;
				break;
			}
			else {
				// Loop until we get a response from the server
				while( 1 ) {
					iBytesReceived = ClientSocketObject.vGetPacket(szPacketBuffer);
					//  Process the Packet
					if( iBytesReceived ) {
						// Check the header
						memcpy(&stHeaderPacket,szPacketBuffer,sizeof(stHeaderPacket));
						// Check if a text response packet
						if( stHeaderPacket.iType == PACKET_TEXTRESPONSE ) {
							memcpy(&stTextResponse,&szPacketBuffer,sizeof(stTextResponse));
							printf("=========================================\n");
							printf("%s",stTextResponse.szResponse);
							printf("=========================================\n");
							break;
						}
					}
				}
			}
		}
		
		// Disconnect from the server
		ClientSocketObject.Disconnect();
		
		cout << "Disconnected From Server" << endl;
	}
	else {
		cout << "Failed to Connect" << endl;
	}
}
