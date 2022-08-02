//###################################################################################
//#																					#
//#			Chapter 4 - UberServer													#		
//#																					#
//#						Demonstrates MUD Server										#
//#																					#
//#						Todd Barron, 10/11/2000										#
//#																					#
//###################################################################################

// Standard Includes
#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include "..\\..\\SocketObject\\SocketObject.h"
#include "..\\Packets.h"

// Defines
#define MAX_PLAYERS			10
#define	MAX_CREATURES		100
#define	MAX_LOCATIONS		20
#define MAX_ITEMS			100

//
// Game structures
//
struct stPlayerInformation
{
	SocketObject	ClientSocketObject;
	int				iActive;
	int				iLocation;
	int				iGold;
	int				iWeapon;
	int				iHitPoints;
	int				iID;
	char			szName[16];
};

struct stCreatureInformation
{
	int	iLocation;
	int	iID;
};

struct stLocationInformation
{
	int		iExitID[4];				// N,S,E,W
	char	szDescription[1024];
	int		iID;
};

struct stItemInformation
{
	int		iLocation;
	int		iOwner;
	int		iType;
	int		iID;
	int		iActive;
	char	szDescription[16];
};

//
// Global variables
//
SocketObject			g_ServerSocketObject;			// Server Socket Object
stPlayerInformation		g_Clients[ MAX_PLAYERS ];		// Client Data
stCreatureInformation	g_Creatures[ MAX_CREATURES ];	// Creature data
stLocationInformation	g_Locations[ MAX_LOCATIONS ];	// Location data
stItemInformation		g_Items[ MAX_ITEMS ];			// Item data
int						iListenPort;

// Thread variables
HANDLE	g_hListenThread;
DWORD	dwListenThreadID;
int		iGameOver;

//
// Function Prototypes
//
void vServerInit( void );
void vListenThread( void );
void vServerCleanup( void );
void vServerMainLoop( void );

//
// ----> Main Program Function (REQUIRED)
//
int main( int argc, char *argv[] )
{
	if( argc != 2 ) {
		cout << "----------------------------------------------------" << endl;
		cout << "               UberServer Help                      " << endl;
		cout << "----------------------------------------------------" << endl;
		cout << "Usage: UberServer [listen port]" << endl;
		cout << "" << endl;
		cout << "Example: UberServer 6000" << endl;
		cout << "" << endl;
		return( 0 );
	}
	
	iListenPort = atoi( argv[1] );
	
	vServerInit();
	vServerMainLoop();
	
	return( 1 );
}

//
// Server Initialization Function
//
void vServerInit( void )
{
	int				i,j;
	FILE			*fp;
	char			szBuffer[1024];

	//
	// Initialize variables
	//
	
	// Init Player Information
	for( i = 0; i < MAX_PLAYERS; i++ ) {
		g_Clients[i].iActive = 0;
		g_Clients[i].iGold = 0;
		g_Clients[i].iHitPoints = 100;
		g_Clients[i].iLocation = 0;
		g_Clients[i].iWeapon = 0;
		sprintf(g_Clients[i].szName,"Player %d",i);
	}
	// Init Locations
	for( i = 0; i < MAX_LOCATIONS; i++ ) {
		// Set exits to default
		for( j = 0; j < 4; j++ ) {
			g_Locations[i].iExitID[j] = -1;
		}
		sprintf(g_Locations[i].szDescription,"Location %d\n", i);
		// Read in data for the location
		sprintf(szBuffer,"Data//location%d.txt",i);
		fp = fopen(szBuffer,"r");
		if( fp == NULL ) 
			continue;
		//
		// Read in the exit IDs
		//
		for( j = 0; j < 4; j++ ) {
			fgets(szBuffer,1024,fp);
			szBuffer[strlen(szBuffer)-1] = '\0';
			g_Locations[i].iExitID[j] = atoi(szBuffer);
		}
		
		sprintf(g_Locations[i].szDescription,"");
		while( !feof(fp) ) {
			fgets(szBuffer,1024,fp);
			if( !feof(fp) ) {
				szBuffer[strlen(szBuffer)-1] = '\0';
				strcat(g_Locations[i].szDescription,szBuffer);
				strcat(g_Locations[i].szDescription,"\n");
			}
		}
		fclose(fp);
	}
	// Init Item Information
	for( i = 0; i < MAX_ITEMS; i++ ) {
		g_Items[i].iLocation = 0;
		g_Items[i].iActive = 0;
		g_Items[i].iOwner = -1;
		g_Items[i].iType = 0;
		g_Items[i].iID = i;
		sprintf(g_Items[i].szDescription,"Item %d",i);
	}

	sprintf(g_Items[0].szDescription,"Big Axe");
	g_Items[0].iActive = 1;
	g_Items[0].iLocation = 0;

	sprintf(g_Items[1].szDescription,"Ladel");
	g_Items[1].iActive = 1;
	g_Items[1].iLocation = 3;

	sprintf(g_Items[2].szDescription,"Bread");
	g_Items[2].iActive = 1;
	g_Items[2].iLocation = 3;

	sprintf(g_Items[3].szDescription,"Rock");
	g_Items[3].iActive = 1;
	g_Items[3].iLocation = 1;

	sprintf(g_Items[4].szDescription,"Broken Key");
	g_Items[4].iActive = 1;
	g_Items[4].iLocation = 2;
	
	iGameOver = 0;
	
	//
	// Attempt to start the server
	//
	cout << "Attempting to start server on port " << iListenPort << endl;
	
	if ( g_ServerSocketObject.Bind( iListenPort ) ) {
		// Increment ListenPort
		iListenPort++;
		// Create listen thread	
		g_hListenThread = CreateThread(	NULL,
			NULL,
			(LPTHREAD_START_ROUTINE)&vListenThread,
			NULL,
			NULL,
			&dwListenThreadID);
	}
	else {
		cout << "--> Failed to start server <--" << endl;	
	}
}

// Thread to listen for new connections
void vListenThread( void )
{
	int							i;
	int							iRet;
	int							iBytesSent;
	stPlayerIDResponsePacket	stResponsePacket;
	char						szSendBuffer[32768];
	
	cout << "Listen Thread Created" << endl;	
	
	while( !iGameOver ) {
		// Look for empty players
		for( i = 0;( i < MAX_PLAYERS && !iGameOver ); i++ ) {
			// Found a free player socket, listen for a connection
			if( !g_Clients[i].iActive ) {
				// Listen for new connection
				g_ServerSocketObject.Listen();
				// Accept the connection
				iRet = g_ServerSocketObject.Accept( g_Clients[i].ClientSocketObject );
				if( iRet == INVALID_SOCKET ) {
					cout << "Failed to accept new client on port " << iListenPort << endl;
					continue;
				}
				cout << "Accepted new client on port " << (iListenPort+i) << endl;
				g_Clients[i].iActive = 1;
				// Tell client their id#
				stResponsePacket.iID = i;
				stResponsePacket.stHeader.iSender = 0;
				stResponsePacket.stHeader.iID = 0;
				stResponsePacket.stHeader.iType = PACKET_PLAYERID;
				stResponsePacket.stHeader.iLength = 4;
				stResponsePacket.stHeader.iCheckSum = g_Clients[i].ClientSocketObject.iCalculateChecksum(stResponsePacket.stHeader);
				
				memcpy(szSendBuffer,&stResponsePacket,sizeof(stResponsePacket.stHeader)+4);
				
				iBytesSent = g_Clients[i].ClientSocketObject.Send(szSendBuffer,sizeof(stResponsePacket.stHeader)+4,0);
			}
		}	
		Sleep(2000);
	}
}

// Function called to cleanup program
void vServerCleanup( void ) 
{
	int i;
	
	// Set game over
	iGameOver = 1;
	
	// Wait for threads to finish up
	cout << "Waiting on Listen Thread" << endl;
	WaitForSingleObject(g_hListenThread,INFINITE);
	// Close the Listen Thread
	CloseHandle(g_hListenThread);
	
	// Free the client connections
	for( i = 0; i < MAX_PLAYERS; i++ ) {
		// Check for connected players
		if( g_Clients[i].iActive ) {
			// Shutdown player
			g_Clients[i].ClientSocketObject.Disconnect();
		}
	}
	
	WSACleanup();

	cout << "<<-- Server Shutdown -->>" << endl;
}

// Main Server Game Function
void vServerMainLoop( void ) 
{
	char					szPacketBuffer[32768];
	int						iBytesReceived;
	int						iBytesSent;
	stPlayerCommandPacket	stPlayerCommand;
	stPacketHeader			stHeader;
	stTextResponsePacket	stTextResponse;
	int						iPlayer,i,j,iFirstItem,iFirstPlayer;
	int						iDontUpdateLocation = 0;

	cout << "<<-- Server Started -->>" << endl;
	
	while(1) {
		Sleep(50);
		// Cycle through clients
		for(j = 0 ; j < MAX_PLAYERS ; j++ ) {
			// Only check client if they are active
			if( g_Clients[j].iActive ) {
				// Check for packets		
				iBytesReceived = g_Clients[j].ClientSocketObject.vGetPacket(szPacketBuffer);
				//  Process the Packet
				if( iBytesReceived ) {
					// Check the header
					memcpy(&stHeader,szPacketBuffer,sizeof(stHeader));
					//
					// Check if type equals Command packet
					//
					if( stHeader.iType == PACKET_PLAYERCOMMAND ) {
						sprintf(stTextResponse.szResponse,"");
						// Copy over the packet
						memcpy(&stPlayerCommand,szPacketBuffer,sizeof(stPlayerCommand));
						// Get the player id
						iPlayer = atoi(stPlayerCommand.szPlayerID);
						cout << iPlayer << "] " << stPlayerCommand.szCommand << " " << stPlayerCommand.szTarget << endl;
						
						// Figure out the command
						if( !stricmp(stPlayerCommand.szCommand,"move") || !stricmp(stPlayerCommand.szCommand,"go") || !stricmp(stPlayerCommand.szCommand,"walk") ) {
							if( !stricmp(stPlayerCommand.szTarget,"north") ) {
								if( g_Locations[g_Clients[iPlayer].iLocation].iExitID[0] != -1 ) {
									// Move player to location to the north
									g_Clients[iPlayer].iLocation = g_Locations[g_Clients[iPlayer].iLocation].iExitID[0];
									cout << "Player " << iPlayer << "'s New Location = " << g_Clients[iPlayer].iLocation << endl;
								}
								else {
									// Create the response
									sprintf(stTextResponse.szResponse,"You cannot go that way!\n\n");
								}
							}
							else if( !stricmp(stPlayerCommand.szTarget,"south") ) {
								if( g_Locations[g_Clients[iPlayer].iLocation].iExitID[2] != -1 ) {
									// Move player to location to the north
									g_Clients[iPlayer].iLocation = g_Locations[g_Clients[iPlayer].iLocation].iExitID[2];
									cout << "Player " << iPlayer << "'s New Location = " << g_Clients[iPlayer].iLocation << endl;
								}
								else {
									// Create the response
									sprintf(stTextResponse.szResponse,"You cannot go that way!\n\n");
								}
							}
							else if( !stricmp(stPlayerCommand.szTarget,"east") ) {
								if( g_Locations[g_Clients[iPlayer].iLocation].iExitID[1] != -1 ) {
									// Move player to location to the north
									g_Clients[iPlayer].iLocation = g_Locations[g_Clients[iPlayer].iLocation].iExitID[1];
									cout << "Player " << iPlayer << "'s New Location = " << g_Clients[iPlayer].iLocation << endl;
								}
								else {
									// Create the response
									sprintf(stTextResponse.szResponse,"You cannot go that way!\n\n");
								}
							}
							else if( !stricmp(stPlayerCommand.szTarget,"west") ) {
								if( g_Locations[g_Clients[iPlayer].iLocation].iExitID[3] != -1 ) {
									// Move player to location to the north
									g_Clients[iPlayer].iLocation = g_Locations[g_Clients[iPlayer].iLocation].iExitID[3];
									cout << "Player " << iPlayer << "'s New Location = " << g_Clients[iPlayer].iLocation << endl;
								}
								else {
									// Create the response
									sprintf(stTextResponse.szResponse,"You cannot go that way!\n\n");
								}
							}
						}
						else if( !stricmp(stPlayerCommand.szCommand,"look") ) {
						}
						// Logic for picking up items
						else if( !stricmp(stPlayerCommand.szCommand,"take") || !stricmp(stPlayerCommand.szCommand,"get") ) {
							// Check if target matches any items in area
							for( i = 0; i < MAX_ITEMS; i++ ) {
								if( g_Items[i].iActive ) {
									if( (g_Items[i].iLocation == g_Clients[iPlayer].iLocation) && (g_Items[i].iOwner == -1) ) {
										if( !stricmp(g_Items[i].szDescription,stPlayerCommand.szTarget) ) {
											printf("Item %d Owner previously = %d\n",i,g_Items[i].iOwner); 
											g_Items[i].iOwner = iPlayer;
											// Create the response
											sprintf(stTextResponse.szResponse,"You take the %s.\n",g_Items[i].szDescription);
											printf("Item %d Owner now = %d\n",i,g_Items[i].iOwner); 
											break;
										}
									}
								}
							}
							if( i == MAX_ITEMS ) {
								sprintf(stTextResponse.szResponse,"There is no %s to take!\n\n",stPlayerCommand.szTarget);
							}
						}
						// Logic for dropping items
						else if( !stricmp(stPlayerCommand.szCommand,"drop") ) {
							// Make sure player owns the item to drop it
							for( i = 0; i < MAX_ITEMS; i++ ) {
								if( g_Items[i].iActive ) {
									if( g_Items[i].iOwner == iPlayer && !stricmp(g_Items[i].szDescription,stPlayerCommand.szTarget) ) {
										g_Items[i].iOwner = -1;
										g_Items[i].iLocation = g_Clients[iPlayer].iLocation;
										// Create the response
										sprintf(stTextResponse.szResponse,"You drop the %s.\n",g_Items[i].szDescription);
										break;
									}
								}
							}
							iDontUpdateLocation = 1;
						}
						// Logic for showing a players inventory
						else if( !stricmp(stPlayerCommand.szCommand,"show") ) {
							if( !stricmp(stPlayerCommand.szTarget,"inventory") ) {
								sprintf(stTextResponse.szResponse,"Inventory\n---------\n");
								for( i = 0; i < MAX_ITEMS; i++ ) {
									if( g_Items[i].iActive ) {
										if( g_Items[i].iOwner == iPlayer ) {
											strcat(stTextResponse.szResponse,g_Items[i].szDescription);	
											strcat(stTextResponse.szResponse,"\n");	
										}
									}
								}
								iDontUpdateLocation = 1;
							}
						}
						else if( !stricmp(stPlayerCommand.szCommand,"?") ) {
							strcat(stTextResponse.szResponse,"COMMAND SUMMARY\n\n");
							strcat(stTextResponse.szResponse,"go/move/walk x = Go in specified direction\n");
							strcat(stTextResponse.szResponse,"get/take x = Pick up specified item\n");
							strcat(stTextResponse.szResponse,"drop x = Drop specified item\n");
							strcat(stTextResponse.szResponse,"show inventory = Show current items owned\n");
							strcat(stTextResponse.szResponse,"look around = Refresh surroundings\n");
							iDontUpdateLocation = 1;
						}
						else {
							// Create the response
							sprintf(stTextResponse.szResponse,"Unrecognized Command!\n\n");
						}

						if( !iDontUpdateLocation ) {
							// Display surroundings
							strcat(stTextResponse.szResponse,g_Locations[g_Clients[iPlayer].iLocation].szDescription);

							// Display items in area
							iFirstItem = 1;
							for( i = 0; i < MAX_ITEMS; i++ ) {
								if( g_Items[i].iActive ) {
									if( (g_Items[i].iLocation == g_Clients[iPlayer].iLocation) && (g_Items[i].iOwner == -1) ) {
										if( iFirstItem ) {
											strcat(stTextResponse.szResponse,"\nItems In Area: ");
											strcat(stTextResponse.szResponse,g_Items[i].szDescription);
											iFirstItem = 0;
										}
										else {
											strcat(stTextResponse.szResponse,",");
											strcat(stTextResponse.szResponse,g_Items[i].szDescription);
										}
									}
								}
							}
							// If any items were found, add a linefeed
							if( !iFirstItem ) {
								strcat(stTextResponse.szResponse,"\n");
							}

							// Display players in area
							iFirstPlayer = 1;
							for( i = 0; i < MAX_PLAYERS; i++ ) {
								// Dont show the player being present
								if( i != iPlayer ) {
									// Check if player active
									if( g_Clients[i].iActive ) {
										// Check if player in the same area
										if( (g_Clients[i].iLocation == g_Clients[iPlayer].iLocation) ) {
											if( iFirstPlayer ) {
												strcat(stTextResponse.szResponse,"\nPlayers In Area: ");
												strcat(stTextResponse.szResponse,g_Clients[i].szName);
												iFirstPlayer = 0;
											}
											else {
												strcat(stTextResponse.szResponse,",");
												strcat(stTextResponse.szResponse,g_Clients[i].szName);
											}
										}
									}
								}
							}
							// If any players were found, add a linefeed
							if( !iFirstPlayer) {
								strcat(stTextResponse.szResponse,"\n");
							}
						}
						else {
							iDontUpdateLocation = 0;
						}
						//
						// Send the response
						//
						

						// Create the header
						stTextResponse.stHeader.iID = 0;
						stTextResponse.stHeader.iType = PACKET_TEXTRESPONSE;
						stTextResponse.stHeader.iLength = (strlen(stTextResponse.szResponse)+1);
						stTextResponse.stHeader.iSender = 0;
						stTextResponse.stHeader.iCheckSum = g_Clients[iPlayer].ClientSocketObject.iCalculateChecksum(stTextResponse.stHeader);

						// Load the packet buffer
						memcpy(szPacketBuffer,&stTextResponse,sizeof(stTextResponse));
						// Send the data
						iBytesSent = g_Clients[iPlayer].ClientSocketObject.Send(szPacketBuffer,sizeof(stHeader)+stTextResponse.stHeader.iLength,0);
					}
					else {
						printf("%d) Unknown Packet Type, %d Bytes.\n",stHeader.iType,iBytesReceived);
					}
				}
			}
		}
	};

	Sleep(15000);
	vServerCleanup();
}

