// OGL_Wrapper.cpp: implementation of the OGL_Wrapper class.
//
//////////////////////////////////////////////////////////////////////
#include <ctime>
#include <cmath>
#include <vector>
using namespace std;

#include "OGL_Wrapper.h"
#include "MatCalc.h"

#include "glframe.h"

#define PI 3.141593f

// These defines are used to tell us about the type of TARGA file it is
#define TGA_RGB		 2			// This tells us it's a normal RGB (really BGR) file
#define TGA_A		 3			// This tells us it's an ALPHA file
#define TGA_RLE		10			// This tells us that the targa is Run-Length Encoded (RLE)
#define MAX_TARGA_TEXTURES 29	// This is the max number of targa textures being loaded

// Some new VK_CODES which are not defined by visual studio
#define VK_PERIOD 190
#define VK_DASH 189

#define MAX_CHARS	256			// This define is for the amount of lists we want to create.
#define FONT_HEIGHT	14			// This defines how high we want our font to be

// This is our image structure for our targa data
struct tImageTGA
{
	int channels;			// The channels in the image (3 = RGB : 4 = RGBA)
	int sizeX;				// The width of the image in pixels
	int sizeY;				// The height of the image in pixels
	unsigned char *data;	// The image pixel data
};

// Our texture filenames
char *file_name[30] = { "button_v2.tga", "button_v3.tga", "button_v4.tga", "button_m2.tga", 
						"button_m3.tga", "button_m4.tga", "button_s.tga", "button_hilite.tga",
						"input.tga", "border.tga", "button_enter.tga", "button_back.tga",
						"button_norm.tga", "button_mult.tga", "button_add.tga", "button_sub.tga", 
						"button_cross.tga", "button_dot.tga", "input_left.tga",
						"oper_mult.tga", "oper_add.tga", "oper_sub.tga", "oper_cross.tga", 
						"oper_dot.tga", "button_solve.tga", "solution.tga", "tun_tex5.tga",
						"intro.tga", "head.tga" };
///////////////////////////////////////////////////////////////////////////////////////////
UINT t_Texture[MAX_TARGA_TEXTURES] = { 0, };			// This is our texture data array

OrthonormalFrame camera;								// Our camera
bool key_press[256] = { 0, };					// Buffering key input


///////////////////////////////////////////////////////////////////////////////////////////////////
// Button selection variables
///////////////////////////////////////////////////////////////////////////////////////////////////
RECT  g_rRect;						// This holds the window dimensions
// The angles our buttons are rotated to
int button_angle[7] = { 100, 100, 100, 100, 100, 100, 100};
RECT button[7] = { {0, }, };		// The bounding boxes of our left hand buttons

// The bounding boxes for the enter, back, solve, and clear buttons
RECT button_ent = { 680, 650, 840, 685 };
RECT button_back = { 680, 700, 840, 735 };
RECT button_clear = { 445, 700, 582, 745 };

// Whether or not a particular left hand operand can perform a required operation
bool valid_op[3][6] = { { 1, 1, 1, 1, 0, 1 },
						{ 0, 1, 1, 1, 0, 0 },
						{ 0, 1, 0, 0, 0, 0 } };

///////////////////////////////////////////////////////////////////////////////////////////////////
// Game variables
///////////////////////////////////////////////////////////////////////////////////////////////////
// Our various game states, more or less in order of ascension
enum State { INTRO = 0, PICK_ONE_ENT, PICK_ONE, PICK_ONE_EX, INPUT_ENT, INPUT, INPUT_EX, 
			 OPERATION_ENT, OPERATION, OPERATION_EX, PICK_TWO_ENT, PICK_TWO, PICK_TWO_EX, 
			 SOLVE, SOLVE_EX, SOLUTION, SOLUTION_EX };

// Our left and right hand opernads
enum { VECTOR2 = 0, VECTOR3, VECTOR4, MATRIX2, MATRIX3, MATRIX4, SCALAR };
// Our possible operations
enum { NORMALIZE = 12, MULTIPLY, ADD, SUBTRACT, CROSS, DOT, OPER_OFFSET = 6 };
// Each operand's corresponding dimensions
int component[7][2] = { {2, 1}, {3, 1}, {4, 1}, {2, 2}, {3, 3}, {4, 4}, {1, 1} };
			 
			 
int state = INTRO;			// Holds the current state of the game
int which = 0;				// Holds which button is currently being moved
int selection = -1;			// Holds which button the mouse is hovering over, -1 if none
bool forward = true;		// True if we are moving towards a solution, else false;
int operand[2];				// Holds our left and right hand operands, respectively
int input_x_pos[4] = { 1024, 0, -500, 1024 };		// Keeps track of various window locations
int input_y_pos[2] = { -270, 770 };					// Keeps track of various window locations
int chosen_square = 0;		// Holds which square we are inputting values into

char input_buffer[10];		// Our input buffer
float *pInput;				// Will hold our matrix or vector until it is stored in a MatCalc

// Our left and right operands and our final answer
MatCalc *one, *two, *answer; 

int which_input = 0;		// Which operand we are currently entering values for
int operation = 0;			// The operation that the the user selected


unsigned int g_FontListID = 0;	// Will hold our list IDs for our fonts
//HFONT hOldFont;				// This will save our old font and select it back in at the end.

///////////////////////////////////////////////////////////////////////////////////////////////////
// Tunnel variables
///////////////////////////////////////////////////////////////////////////////////////////////////
// Tunnel struct, holds the coordinates of our vertices
struct glCoord
{
	float x, y, z;
};
// Will hold the values of our tunnel cylinder
glCoord Tunnels[33][33] = { 0, };
// Holds the texture coordinates of our tunnel
struct T_Coord
{
	float u, v;
};
// Will hold the values of our tunnel cylinder's texture coordinates
T_Coord	TexCoord[33][33] = { 0, };

///////////////////////////////////////////////////////////////////////////////////////////////////
// Thread variables
///////////////////////////////////////////////////////////////////////////////////////////////////
float angle = 0;				// Used for distorting the tunnel			
#define threadLength 101		// The length of our mouse trail
#define maxThreads 128			// The max number of threads
int threadCount = 50;			// The current thread count
glCoord threads[maxThreads][threadLength] = { 0, };		// The coordinates of our mouse trail
glCoord rnd[maxThreads] = { 0, };						// A random factor for thread direction

float rd = 0, gr = 0, bl = 0;	// Used to color our threads

GLenum mode = GL_QUADS;			// Either GL_QUADS or GL_LINE_STRIP


// Loads a targa image
tImageTGA *LoadTGA(const char *filename);
int random(int high, int low);


// This is where all of our drawing is done
int OGL_Wrapper::DrawGLScene(bool true_render)
{
	DWORD start_time = GetTickCount();

	// reset the screen and the depth buffer, reset the modelview matrix
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

    // Clear the background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_LINE_SMOOTH);

// Please fasten your seat belts and make sure all inflight luggage is secured
glPushMatrix();
	// Put the camera where it needs to be
	camera.ApplyCameraTransform();


	glEnable(GL_TEXTURE_2D);					// Turn on textures
	glDisable(GL_LIGHTING);						// Turn off lighting
	glEnable(GL_BLEND);							// Turn on blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);		// Standard blending

	RECT rSize = { 0, };
	GetClientRect(hWnd, &rSize);				// Get our window size
	
	POINT cursor_pos = { 0, 0 };
	GetCursorPos(&cursor_pos);					// Get our cursor position
	ScreenToClient(hWnd, &cursor_pos);			// Adjust it for the position of the window

	cursor_pos.x *= (1024.0f / rSize.right);	// Adjust it for the size of the window
	cursor_pos.y *= (768.0f / rSize.bottom);

	///////////////////////////////////////////////////////////////////////////////////////////
	// Tunnel code
	///////////////////////////////////////////////////////////////////////////////////////////
	angle += 2.0f;					// Increment our angle every frame

	float angle2 = angle;

	// Make the mouth of our tunnel wiggle about
	for(int i = 0; i < 33; ++i)
	{
		for(int j = 0; j < 33; ++j)
		{      
			// Change the x values based on the current value of angle
			Tunnels[i][j].x =(3 - j / 12.0f) * cos((2 * PI / 32) * i) + 2 * sin((angle2 + 2 * j) / 29.0f)
							 + cos((angle2 + 2 * j) / 13.0f) - 2 * sin(angle2 / 29.0f) - cos(angle2 / 13.0f);
			// Change the y values based on the current value of angle
			Tunnels[i][j].y =(3 - j / 12.0f) * sin((2 * PI / 32) *i) + 2 * cos((angle2 + 2 * j) / 33.0f)
							 + sin((angle2 + 2 * j) / 17.0f) - 2 * cos(angle2 / 33.0f) - sin(angle2 / 17.0f);
		}  
	}	
	
	// Move the texture coordinates of our tunnel
	for(i = 0; i < 33; ++i)
	{
		for(int j = 0; j < 33; ++j)
		{
			TexCoord[i][j].u = i / 32.0f + cos((angle + 8 * j) / 60) / 2;
			TexCoord[i][j].v = j / 32.0f + (angle + j) / 120;	
		}
	}
	glPushMatrix();	
		glTranslatef(0.0f, 0.0f, -4.2f);				// Move it into the screen

		float c = 0;

		if(GetAsyncKeyState('L') && !key_press['L'])	// If 'L' is pressed...
		{
			key_press['L'] = true;
			mode == GL_QUADS ? mode = GL_LINE_STRIP : mode = GL_QUADS; // ...Change the drawing mode
		}

		glBindTexture(GL_TEXTURE_2D, t_Texture[26]);	// Bind our tunnel texture

		for(i = 0; i < 32; ++i)
		{

			glBegin(mode);								// Begin drawing our tunnel
				for(int j = 0; j < 32; ++j)
				{
					// Darken the end of our tunnel
					j > 24 ? c = .8f - (j - 24) / 10.f : c = .8f;

					glColor3f(c, c, c);
					glTexCoord2f(TexCoord[i][j].u, TexCoord[i][j].v); 
					glVertex3f(Tunnels[i][j].x, Tunnels[i][j].y, Tunnels[i][j].z);

					glTexCoord2f(TexCoord[i + 1][j].u, TexCoord[i + 1][j].v); 
					glVertex3f(Tunnels[i + 1][j].x, Tunnels[i + 1][j].y, Tunnels[i + 1][j].z);

					glTexCoord2f(TexCoord[i + 1][j + 1].u, TexCoord[i + 1][j + 1].v); 
					glVertex3f(Tunnels[i + 1][j + 1].x, Tunnels[i + 1][j + 1].y, Tunnels[i + 1][j + 1].z);

					glTexCoord2f(TexCoord[i][j + 1].u, TexCoord[i][j + 1].v); 
					glVertex3f(Tunnels[i][j + 1].x, Tunnels[i][j + 1].y, Tunnels[i][j + 1].z);
				}
			glEnd();
		}
	glPopMatrix(); 	   
 
	////////////////////////////////////////////////////////////////////////////////
	// Thread code
	////////////////////////////////////////////////////////////////////////////////
	glCoord P;
	// Update the thread positions
	//P.x = cursor_pos.x / 80.0f - 5.0f;      // mouse X
	//P.z = -2;
	//P.y = -(cursor_pos.y / 80.0f - 3.45f);  // mouse Y

	// Calculate our cursor's position in world coordinates at a depth of -2
	P.x = cursor_pos.x / 465.0f - 1.1f;       // mouse X
	P.z = -2;
	P.y = -(cursor_pos.y / 460.0f - .825f);   // mouse Y  

	// Set every thread's starting position to the cursor's position
	for(i = 0; i < threadCount; ++i)
	{
		threads[i][0] = P;
	}

	// Update the threads based on the position of the first vertex in each thread
	for(i = 0; i < threadCount; ++i)
	{
		for(int j = threadLength - 1; j > 0; --j)
		{
			threads[i][j].x = (threads[i][j-1].x * 2 + threads[i][j].x)/2.9f + rnd[i].x * .07f;
			threads[i][j].y = (threads[i][j-1].y * 2 + threads[i][j].y)/2.9f + rnd[i].y * .07f;
			threads[i][j].z = (threads[i][j-1].z * 2 + threads[i][j].z)/2.9f + rnd[i].z * .07f;
		}
	}	  
///////////////////////////////////////
/////////////////////////////////////////

	// Switch from perspective mode to ortho mode for drawing in 2D
	OrthoMode(0, 0, 1024, 768);

	// Our game states
	switch(state)
	{
		// The intro screen
		case INTRO:
		{
			// Draw the intro text
			DrawQuad(27, 0, 0, 1024, 768);
			
			// In the event of a mouse click, move on to PICK_ONE_ENT
			if(GetAsyncKeyState(VK_LBUTTON) || GetAsyncKeyState(VK_RBUTTON))
			{
				key_press[VK_LBUTTON] = key_press[VK_RBUTTON] = true;
				state = PICK_ONE_ENT;
			}
		}
		break;

		// Time to bring out our buttons
		case PICK_ONE_ENT:
		{
			// Make sure we're not messing ourselves up somehow
			if(which < 0)
				which = 0;
			// Keep track of which button is being moved
			if(which < 7)
				button_angle[which] -= 15;
			// Next button
			if(button_angle[which] < 10 && which < 7)
			{
				++which;
			}
			// Roate the button which is currently being moved
			for(int i = 0; i < 7; ++i)
			{
				if(i < which && button_angle[i] > 10)
					button_angle[i] -= 15;
					
				if(button_angle[i] < 10)
					button_angle[i] = 0; 
			}
			// Draw all of our buttons
			for(i = 0; i < 7; ++i)
			{
				glPushMatrix();
					// Move them down
					glTranslatef(-35, 400 + i * 55, 0);
					// Rotate them
					glRotatef(button_angle[i], 0, 0, 1);
					// Draw them
					DrawQuad(i, 0 - i * 20, -55, 450 - i * 20, 0); 
				glPopMatrix();
			}
			
			// If everyone's been rotated, move on	 
			if(button_angle[6] == 0)
				state = PICK_ONE;

		}
		break;

		// Time to pick the left hand operand
		case PICK_ONE:
		{
			// Keeps track of whehter or not our cursor is valid
			bool valid_cursor = false;

			// Draw our buttons and check the cursor's location
			for(int i = 0; i < 7; ++i)
			{
				// Where's our cursor?
				if(CursorInRect(button[i], cursor_pos))
				{
					valid_cursor = true;
					selection = i;
				}

				// Draw our buttons
				glPushMatrix();
					glTranslatef(-35, 400 + i * 55, 0);
					glRotatef(button_angle[i], 0, 0, 1);

					DrawQuad(i, 0 - i * 20, -55, 450 - i * 20, 0 );
				glPopMatrix();
			}
			// If we're on a button, hi-light it
			if(valid_cursor)
			{
				// Draw our green hi-light
				DrawQuad(7, button[selection].left - 50, button[selection].top - 20,
						 button[selection].right + 50, button[selection].bottom + 20 );
			}
			
			// If the left mouse button is pressed...
			if(GetAsyncKeyState(VK_LBUTTON))
			{
				// ...and we're on a button...
				if(valid_cursor)
				{
					// ...then it's time to move on
					forward = true;
					// Store our left operand
					operand[0] = selection;
					// Next state where the buttons go away
					state = PICK_ONE_EX;
					// Initialize our temp array of floats to hold our operand's info
					pInput = new float[component[operand[0]][0] * component[operand[0]][1]];
					// Set everything to zero
					for(int j = 0; j < component[operand[0]][0] * component[operand[0]][1]; ++j)
						pInput[j] = 0;
				}
			}	 
		}
		break;
		// Time to make the buttons go away
		case PICK_ONE_EX:
		{
			// Check for game crashing errors
			if(which > 6)
				which = 6;
			// Move the appropriate button
			if(which > -1)
				button_angle[which] += 15;
			// Next button
			if(button_angle[which] > 60 && which > -1)
					--which;
			// tuen the buttons being moved
			for(int i = 0; i < 7; ++i)
			{
				if(i > which && button_angle[i] < 91)
					button_angle[i] += 15;
					
				if(button_angle[i] > 100)
					button_angle[i] = 100; 
			}
			// Draw our buttons
			for(i = 0; i < 7; ++i)
			{
				glPushMatrix();
					// Move them down
					glTranslatef(-35, 400 + i * 55, 0);
					// Rotate them
					glRotatef(button_angle[i], 0, 0, 1);
					// Draw them
					DrawQuad(i, 0 - i * 20, -55, 450 - i * 20, 0 );
				glPopMatrix();
			}
			// Next state, moving the input window out	 
			if(button_angle[0] == 100)
				state = INPUT_ENT;
		}
		break;
		// Time to move our input window into view
		case INPUT_ENT:
		{
			// Change the window's position
			input_x_pos[0] -= (input_x_pos[0] - 510) / 10;
			// Draw the window
			DrawQuad(8, input_x_pos[0], 320, input_x_pos[0] + 500, 650 );

			// Draw the enter and back buttons
			for(int i = 0; i < 2; ++i)
			{
				DrawQuad(10 + i, input_x_pos[0] + 120, 640 + i * 50, input_x_pos[0] + 570, 695 + i * 50);
			}

			// Window's in place, next state
			if(input_x_pos[0] < 530)
			{
				input_x_pos[0] = 530;
				state = INPUT;
			}

			// If this is the second time we're doing this, draw the other windows
			if(which_input == 1)
			{
				DrawQuad(operation + OPER_OFFSET, 452, input_y_pos[0], 572, input_y_pos[0] + 270);
				DrawQuad(18, input_x_pos[2], 20, input_x_pos[2] + 500, 350 );
				DrawMat(one, 235 - (one->col - 1) * 30, 155 - (one->row - 1) * 30);
			}
		}
		break;
		// Time to enter our matrix
		case INPUT:
		{
			// If this is the second operand, draw the first operand and the operation
			if(which_input == 1)
			{
				DrawQuad(operation + OPER_OFFSET, 452, input_y_pos[0], 572, input_y_pos[0] + 270);
				DrawQuad(18, input_x_pos[2], 20, input_x_pos[2] + 500, 350 );
				DrawMat(one, 235 - (one->col - 1) * 30, 155 - (one->row - 1) * 30);
			}

			// Draw our input window
			DrawQuad(8, input_x_pos[0], 320, input_x_pos[0] + 500, 650 );

			// Draw the enter and back buttons
			for(int i = 0; i < 2; ++i)
			{
				DrawQuad(10 + i, input_x_pos[0] + 120, 640 + i * 50, input_x_pos[0] + 570, 695 + i * 50);
			}

			// Next entry in the event of TAB being pressed
			if(GetAsyncKeyState(VK_TAB) && !key_press[VK_TAB])
			{
				key_press[VK_TAB] = true;
				// Previous entry in the event of SHIFT-TAB being pressed
				if(GetAsyncKeyState(VK_SHIFT))
				{
					if(chosen_square > 0)
						--chosen_square;
					else
						chosen_square = component[operand[which_input]][0] * component[operand[which_input]][1] - 1;
				}
				// Back to the top
				else
				{
					if(chosen_square < component[operand[which_input]][0] * component[operand[which_input]][1] - 1)
						++chosen_square;
					else
						chosen_square = 0;
				}

				// Reset our input buffer
				if(!pInput[chosen_square])
					input_buffer[0] = '\0';
				else
				{
					// Print the values to the screen
					sprintf(input_buffer, "%.2f", pInput[chosen_square]);

					// Check for eronious zeros...
					char *dump = strstr(input_buffer, ".00");
					// And get rid of them
					if(dump)
					{
						dump[0] = '\0';
					}
					int len = strlen(input_buffer);
					// Check for more eronious zeros, how tedious
					if(len > 3 && input_buffer[len - 1] == '0' && input_buffer[len - 3] == '.')
					{
						input_buffer[len - 1] = '\0';	
					}
				}
			}


			// Check to see if our cursor is on the Enter button
			if(CursorInRect(button_ent, cursor_pos))
			{
				// Highlight the button
				DrawQuad(7, button_ent.left - 50, button_ent.top - 20, button_ent.right + 50, button_ent.bottom + 20);
				
				// Clicked on the button
				if(GetAsyncKeyState(VK_LBUTTON) && !key_press[VK_LBUTTON])
				{
					key_press[VK_LBUTTON] = true;
					// We are moving on
					forward = true;
					state = INPUT_EX;
					// Keep the back button on the screen
					input_x_pos[1] = input_x_pos[0];
					chosen_square = 0;

					// First time
					if(which_input == 0)
					{
						which_input = 1;
						// Store our inputted values
						one = new MatCalc(component[operand[0]][0], component[operand[0]][1],
										  pInput);
					}
					// Second time
					else
					{
						which_input = 2;
						// Store our inputted values
						two = new MatCalc(component[operand[1]][0], component[operand[1]][1],
										  pInput);
					}

					break;
				}
			}
			// If we're hovering over our back button
			else if(CursorInRect(button_back, cursor_pos))
			{
				// Highlight it
				DrawQuad(7, button_back.left - 50, button_back.top - 20, button_back.right + 50, button_back.bottom + 20);
				// If we click...
				if(GetAsyncKeyState(VK_LBUTTON) && !key_press[VK_LBUTTON])
				{
					key_press[VK_LBUTTON] = true;
					// ...time to go back
					forward = false;

					// Reset our input buffer
					input_buffer[0] = '\0';
					chosen_square = 0;
					// Clean up our memory
					delete [] pInput;
					pInput = NULL;

					state = INPUT_EX;

					// If this is the first time, get rid of our back button
					if(which_input == 1)
						input_x_pos[1] = input_x_pos[0];

					break;
				}
				
			}

			bool new_input = false;

			// Handle Backspace being pressed
			if(GetAsyncKeyState(VK_BACK) && !key_press[VK_BACK] && strlen(input_buffer) > 0)
			{
				key_press[VK_BACK] = true;
				input_buffer[strlen(input_buffer) ? strlen(input_buffer) - 1 : 0] = '\0';
				new_input = true;
			}
			// Check for numbers being pressed
			for(char j = '0'; j <= '9'; ++j)
			{
				if(GetAsyncKeyState(j) && !key_press[j])
				{
					key_press[j] = true;

					// Don't accept any 0 inputs if the buffer is empty of other numbers
					if(j == '0' && (input_buffer[0] == '0' || 
									(input_buffer[0] == '-'	&& input_buffer[1] == '\0')))
					{
						continue;
					}

					// Make sure the user isn't entering some ridiculous number
					if((input_buffer[0] == '-' && strlen(input_buffer) < 6) || 
					   (input_buffer[0] != '-' && strlen(input_buffer) < 5))
					{
						// Add the input to out buffer
						input_buffer[strlen(input_buffer) + 1] = '\0';
						input_buffer[strlen(input_buffer)] = j;
						new_input = true;
					}
				}
			}
			// Handle the minus sign being pressed
			if(GetAsyncKeyState(VK_DASH) && !key_press[VK_DASH])
			{
				key_press[VK_DASH] = true;
				// If we aren't already negative, make us so
				if(input_buffer[0] != '-')
				{
					memmove(input_buffer + 1, input_buffer, strlen(input_buffer) + 1);
					input_buffer[0] = '-';
				}
				// Otherwise make us not
				else
				{
					memmove(input_buffer, input_buffer + 1, strlen(input_buffer));
				}
				new_input = true;
			}
			// Handle the period beign pressed
			if(GetAsyncKeyState(VK_PERIOD) && !key_press[VK_PERIOD] && strlen(input_buffer) < 6)
			{
				bool decimal_entered = false;
				// Cehck to see if there's already a decimal entered
				for(int k = 0; k < strlen(input_buffer); ++k)
				{
					if(input_buffer[k] == '.')
					{
						decimal_entered = true;
						break;
					}
				}
				// If there isn't, give us one
				if(!decimal_entered)
				{
					key_press[VK_PERIOD] = true;
					input_buffer[strlen(input_buffer) + 1] = '\0';
					input_buffer[strlen(input_buffer)] = '.';
					new_input = true;
				}
			}
			// If there has been new input, update our floats
			if(new_input)
			{
				pInput[chosen_square] = atof(input_buffer);
			}
			// Drawing position of our matrix's top left corner
			int tX = 725 - (component[operand[which_input]][1] - 1) * 30;
			int tY = 455 - (component[operand[which_input]][0] - 1) * 30;

			int index = 0;

			// For every value in our operand
			for(i = 0; i < component[operand[which_input]][0]; ++i)
			{
				for(int j = 0; j < component[operand[which_input]][1]; ++j)
				{
					RECT square = { tX + (60 * j), tY + (60 * i), tX + (60 * j) + 58, tY + (60 * i) + 58};
					// Check for mouse clicks
					if(GetAsyncKeyState(VK_LBUTTON))
					{
						// Cehck to see if we're clicking on a square
						if(CursorInRect(square, cursor_pos))
						{
							chosen_square = index;
							// Set up our input buffer
							if(!pInput[chosen_square])
								input_buffer[0] = '\0';
							// if there's a value in the square, put it in the buffer
							else
							{
								sprintf(input_buffer, "%.2f", pInput[chosen_square]);

								// check for eronious zeros
								char *dump = strstr(input_buffer, ".00");
								
								if(dump)
								{
									dump[0] = '\0';
								}
								int len = strlen(input_buffer);
								if(len > 3 && input_buffer[len - 1] == '0' && input_buffer[len - 3] == '.')
								{
									input_buffer[len - 1] = '0';	
								}
							}
						}  
					}
					// Draw our squares
					DrawQuad(9, square.left, square.top, square.right, square.bottom,
							 1, 1, 1, (chosen_square == index ? 1 : .3f)); 

					// Draw our text
					glPushMatrix();
						glDisable(GL_TEXTURE_2D);
						glColor4f(0, 1, 0, 1);					// Make the next text green
						char pTemp[100];
						if(pInput[index] == (int)pInput[index])
							sprintf(pTemp, "%.1f", pInput[index]); 
						else
							sprintf(pTemp, "%.2f", pInput[index]);
							 
						// Position The Text On The Screen
						glRasterPos2f(square.left + 30 - strlen(pTemp) * 4, square.top + 35);
 						glPrint(pTemp);	// Print GL Text To The Screen
						glEnable(GL_TEXTURE_2D);
					glPopMatrix();
					++ index; 
				}
			}

		}
		break;

		// Time to make the input window go away
		case INPUT_EX:
		{
			// Move the input window
			input_x_pos[0] += (1040 - input_x_pos[0]) / 10;
			// Draw the input window
			DrawQuad(8, input_x_pos[0], 320, input_x_pos[0] + 500, 650);

			// First time doing this?
			if(which_input == 1)
			{
				if(forward)
					input_x_pos[2] += (0 - input_x_pos[2]) / 10;
				
				// Move our left operand window into place
				DrawQuad(18, input_x_pos[2], 20, input_x_pos[2] + 500, 350 );
				if(!forward)
				{
					DrawQuad(operation + OPER_OFFSET, 452, input_y_pos[0], 572, input_y_pos[0] + 270);
					DrawMat(one, 235 - (one->col - 1) * 30, 155 - (one->row - 1) * 30);	 
				}
			}
			// Second tine doing this?
			if(which_input == 2)
			{
				// Move the right operand window into place
				input_x_pos[3] -= (input_x_pos[3] - 515) / 10;
				// Draw the right operand window
				DrawQuad(8, input_x_pos[3], 20, input_x_pos[3] + 515, 350 );
				
				// Draw the operation window
				DrawQuad(operation + OPER_OFFSET, 452, input_y_pos[0], 572, input_y_pos[0] + 270);
				// Draw the left operand window
				DrawQuad(18, input_x_pos[2], 20, input_x_pos[2] + 500, 350 );
				// Draw the left operand inside the operand window
				DrawMat(one, 235 - (one->col - 1) * 30, 155 - (one->row - 1) * 30);	 

				// Draw the solve button
				DrawQuad(24, input_x_pos[3] + 120, 640, input_x_pos[3] + 570, 695);
			}

			// Draw the enter and back buttons
			for(int i = 0; i < 2; ++i)
			{
				DrawQuad(10 + i, input_x_pos[i * (forward || which_input)] + 120, 640 + i * 50,
						 input_x_pos[i * (forward || which_input)] + 570, 695 + i * 50);
			} 
			// time to move on...or move back
			if(input_x_pos[0] > 1024)
			{
				input_x_pos[0] = 1024;
				// Are we going forward?
				if(!forward)
				{
					if(which_input == 0)
						state = PICK_ONE_ENT;
					else
						state = PICK_TWO_ENT;
				}
				// Are we going backward?
				else
				{
					if(which_input == 1)
						state = OPERATION_ENT;	   
					else				
					{					  
						state = SOLVE;	   
					}
				}
			}

		}
		break;

		// Time to pick our operation
		case OPERATION_ENT:
		{
			// Draw the left operand window and matrix
			DrawQuad(18, input_x_pos[2], 20, input_x_pos[2] + 500, 350 );
			DrawMat(one, 235 - (one->col - 1) * 30, 155 - (one->row - 1) * 30);

			if(which < 0)
				which = 0;
			// Move our buttons
			if(which < 6)
				button_angle[which] -= 15;
			// Next button
			if(button_angle[which] < 10 && which < 6)
			{
				++which;
			}
			for(int i = 0; i < 6; ++i)
			{
				if(i < which && button_angle[i] > 10)
					button_angle[i] -= 15;
					
				if(button_angle[i] < 10)
					button_angle[i] = 0; 
			}
			// Draw all of our buttons
			for(i = 0; i < 6; ++i)
			{
				glPushMatrix();
					glTranslatef(-35, 400 + i * 55, 0);
					glRotatef(button_angle[i], 0, 0, 1);

					// Darken the buttons which aren't valid
					DrawQuad(i + NORMALIZE, 0 - i * 20, -55, 450 - i * 20, 0,
							 (valid_op[operand[0] / 3][i] || (i == 4 && operand[0] == VECTOR3)) ? 1 : .3f, 
							 (valid_op[operand[0] / 3][i] || (i == 4 && operand[0] == VECTOR3)) ? 1 : .3f, 
							 (valid_op[operand[0] / 3][i] || (i == 4 && operand[0] == VECTOR3)) ? 1 : .3f, 1);
				glPopMatrix();
			}
			// Draw the back button
			DrawQuad(11, input_x_pos[1] + 120, 690, input_x_pos[1] + 570, 745);
			
			// Everyone's in place, move on	 
			if(button_angle[5] == 0)
				state = OPERATION;
		}
		break;

		// Which operation? 
		case OPERATION:
		{
			// Draw the left operand window and matrix
			DrawQuad(18, input_x_pos[2], 20, input_x_pos[2] + 500, 350 );
			DrawMat(one, 235 - (one->col - 1) * 30, 155 - (one->row - 1) * 30);


			bool valid_cursor = false;
		
			// cehck to see if we're on a button, and draw all the buttons while we're at it
			for(int i = 0; i < 6; ++i)
			{
				// Check the cursor
				if(CursorInRect(button[i], cursor_pos) && 
				   (valid_op[operand[0] / 3][i] || (i == 4 && operand[0] == VECTOR3)))
				{
					valid_cursor = true;
					selection = i;
				}
				// Draw our buttons
				glPushMatrix();
					glTranslatef(-35, 400 + i * 55, 0);
					glRotatef(button_angle[i], 0, 0, 1);
					// Darken the ones that can't be picked
					DrawQuad(i + NORMALIZE, 0 - i * 20, -55, 450 - i * 20, 0,
							 (valid_op[operand[0] / 3][i] || (i == 4 && operand[0] == VECTOR3)) ? 1 : .3f, 
							 (valid_op[operand[0] / 3][i] || (i == 4 && operand[0] == VECTOR3)) ? 1 : .3f, 
							 (valid_op[operand[0] / 3][i] || (i == 4 && operand[0] == VECTOR3)) ? 1 : .3f, 1);
				glPopMatrix();
			}
			if(valid_cursor)
			{
				// highlight the button we're on
				DrawQuad(7, button[selection].left - 50, button[selection].top - 20,
						 button[selection].right + 50, button[selection].bottom + 20 );
			}
			// If the user clicks
			if(GetAsyncKeyState(VK_LBUTTON))
			{
				// And we're on a button
				if(valid_cursor)
				{
					// Time to move on
					forward = true;
					// Error checking
					input_buffer[0] = '\0';
					// Store the operation we picked
					operation = selection + NORMALIZE;

					// if normalize was picked, time to finish up
					if(operation == NORMALIZE)
					{
						// Calculate our answer
						answer = MatCalc::normalize(one);
					}

					state = OPERATION_EX;
				}
			}
			// Draw the Back button	 
			DrawQuad(11, input_x_pos[1] + 120, 690, input_x_pos[1] + 570, 745);

			// Check to see if our cursor is hovering over the Back button
			if(CursorInRect(button_back, cursor_pos))
			{
				// High-light it
				DrawQuad(7, button_back.left - 50, button_back.top - 20, button_back.right + 50, button_back.bottom + 20);

				// Time to go back
				if(GetAsyncKeyState(VK_LBUTTON) && !key_press[VK_LBUTTON])
				{
					key_press[VK_LBUTTON] = true;
					forward = false;

					input_buffer[0] = '\0';
					chosen_square = 0;

					// Re-make our temo array of floats and pt the values back in it
					pInput = new float[one->row * one->col];
					memcpy(pInput, one->pData, sizeof(float) * one->row * one->col);
					// Get rid of our left operand
					delete one;
					one = NULL;
					state = OPERATION_EX;

					break;
				}
				
			}


		}
		break;

		// Make the buttons go away 
		case OPERATION_EX:
		{
			// Draw our left operand
			DrawQuad(18, input_x_pos[2], 20, input_x_pos[2] + 500, 350 );
			DrawQuad(11, input_x_pos[1] + 120, 690, input_x_pos[1] + 570, 745);

			// Roate our buttons
			if(which > 5)
				which = 5;
			if(which > -1)
				button_angle[which] += 15;
			if(button_angle[which] > 60 && which > -1)
					--which;
			for(int i = 0; i < 6; ++i)
			{
				if(i > which && button_angle[i] < 91)
					button_angle[i] += 15;
					
				if(button_angle[i] > 100)
					button_angle[i] = 100; 
			}
			// Draw our buttons
			for(i = 0; i < 6; ++i)
			{
				glPushMatrix();
					glTranslatef(-35, 400 + i * 55, 0);
					glRotatef(button_angle[i], 0, 0, 1);

					DrawQuad(i + NORMALIZE, 0 - i * 20, -55, 450 - i * 20, 0,
							 (valid_op[operand[0] / 3][i] || (i == 4 && operand[0] == VECTOR3)) ? 1 : .3f, 
							 (valid_op[operand[0] / 3][i] || (i == 4 && operand[0] == VECTOR3)) ? 1 : .3f, 
							 (valid_op[operand[0] / 3][i] || (i == 4 && operand[0] == VECTOR3)) ? 1 : .3f, 1);
				glPopMatrix();
			}		 
			// If we're moving back...
			if(!forward)
			{
				// Move our windows into place
				which_input = 0;
				input_x_pos[2] += (-500 - input_x_pos[2]) / 10;
				input_x_pos[1] += (1040 - input_x_pos[1]) / 10;

				if(button_angle[0] == 100)
				{
					input_x_pos[2] = -500; 
					state = INPUT_ENT;
				}
			}
			// ..otherwise
			else
			{
				// draw the left operand's matrix 
				DrawMat(one, 235 - (one->col - 1) * 30, 155 - (one->row - 1) * 30);

				if(button_angle[0] == 100)
				{
					if(operation == NORMALIZE)
						state = SOLVE_EX;
					else
						state = PICK_TWO_ENT;
				}
			}
		}
		break;

		// Time to pick contestant number two
		case PICK_TWO_ENT:
		{
			// move the operation window into place
			input_y_pos[0] += (0 - input_y_pos[0]) / 10;

			//////////////////////////////////////////////////////////////////////////////////
			// Draw our GUI elements
			//////////////////////////////////////////////////////////////////////////////////
			DrawQuad(operation + OPER_OFFSET, 452, input_y_pos[0], 572, input_y_pos[0] + 270);
			
			DrawQuad(18, input_x_pos[2], 20, input_x_pos[2] + 500, 350 );
			DrawMat(one, 235 - (one->col - 1) * 30, 155 - (one->row - 1) * 30);


			// Draw the Back button
			DrawQuad(11, input_x_pos[1] + 120, 690, input_x_pos[1] + 570, 745);
			//////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////

			if(which < 0)
				which = 0;
			if(which < 7)
				button_angle[which] -= 15;
			if(button_angle[which] < 10 && which < 7)
			{
				++which;
			}
			// Move our buttons into place
			for(int i = 0; i < 7; ++i)
			{
				if(i < which && button_angle[i] > 10)
					button_angle[i] -= 15;
					
				if(button_angle[i] < 10)
					button_angle[i] = 0; 
			}
			bool valid_buttons[7] = { 0, };

			// Adjust our valid buttons for special cases
			if(operand[0] == VECTOR2 ||	operand[0] == VECTOR3 || operand[0] == VECTOR4)
			{
				if(operation == MULTIPLY)
				{
					valid_buttons[SCALAR] = true;
				}
				else
				{
					valid_buttons[operand[0]] = true;
				}
			}
			else if(operand[0] == MATRIX2 ||	operand[0] == MATRIX3 || operand[0] == MATRIX4)
			{
				if(operation == MULTIPLY)
				{
					valid_buttons[SCALAR] = true;
					valid_buttons[operand[0]] = true;
					valid_buttons[operand[0] - 3] = true;
				}
				else
				{
					valid_buttons[operand[0]] = true;
				}
			}
			else
			{
				for(int i = 0; i < 6; ++i)
				{
					valid_buttons[i] = true;
				}
			}
			// Draw our buttons
			for(i = 0; i < 7; ++i)
			{
				glPushMatrix();
					glTranslatef(-35, 400 + i * 55, 0);
					glRotatef(button_angle[i], 0, 0, 1);

					DrawQuad(i, 0 - i * 20, -55, 450 - i * 20, 0,
							 valid_buttons[i] ? 1 : .3f, 
							 valid_buttons[i] ? 1 : .3f, 
							 valid_buttons[i] ? 1 : .3f, 1);
				glPopMatrix();
			}
			// time to move on	 
			if(button_angle[6] == 0)
				state = PICK_TWO;

		}
		break;

		// Let's pick the winner
		case PICK_TWO:
		{
			//////////////////////////////////////////////////////////////////////////////////
			// Draw our GUI elements
			//////////////////////////////////////////////////////////////////////////////////
			DrawQuad(operation + OPER_OFFSET, 452, input_y_pos[0], 572, input_y_pos[0] + 270);
			DrawQuad(18, input_x_pos[2], 20, input_x_pos[2] + 500, 350 );
			DrawMat(one, 235 - (one->col - 1) * 30, 155 - (one->row - 1) * 30);

			// Draw the Back button
			DrawQuad(11, input_x_pos[1] + 120, 690, input_x_pos[1] + 570, 745);
			//////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////

			bool valid_buttons[7] = { 0, };
			// Adjust which buttons can be picked
			if(operand[0] == VECTOR2 ||	operand[0] == VECTOR3 || operand[0] == VECTOR4)
			{
				if(operation == MULTIPLY)
				{
					valid_buttons[SCALAR] = true;
				}
				else
				{
					valid_buttons[operand[0]] = true;
				}
			}
			// In the event of a matrix
			else if(operand[0] == MATRIX2 ||	operand[0] == MATRIX3 || operand[0] == MATRIX4)
			{
				if(operation == MULTIPLY)
				{
					valid_buttons[SCALAR] = true;
					valid_buttons[operand[0]] = true;
					valid_buttons[operand[0] - 3] = true;
				}
				else
				{
					valid_buttons[operand[0]] = true;
				}
			}
			// Anything else
			else
			{
				for(int i = 0; i < 6; ++i)
				{
					valid_buttons[i] = true;
				}
			}

			bool valid_cursor = false;

			for(int i = 0; i < 7; ++i)
			{
				// Where's our cursor?
				if(CursorInRect(button[i], cursor_pos) && valid_buttons[i])
				{
					valid_cursor = true;
					selection = i;
				}
				// Draw our buttons
				glPushMatrix();
					glTranslatef(-35, 400 + i * 55, 0);
					glRotatef(button_angle[i], 0, 0, 1);

					// darken the ones that can't be picked
					DrawQuad(i, 0 - i * 20, -55, 450 - i * 20, 0,
							 valid_buttons[i] ? 1 : .3f, 
							 valid_buttons[i] ? 1 : .3f, 
							 valid_buttons[i] ? 1 : .3f, 1);
				glPopMatrix();
			}
			
			if(valid_cursor)
			{
				// High light the button that we're on
				DrawQuad(7, button[selection].left - 50, button[selection].top - 20,
						 button[selection].right + 50, button[selection].bottom + 20 );
			}
			// time to move on
			if(GetAsyncKeyState(VK_LBUTTON) && valid_cursor)
			{
					forward = true;
					operand[1] = selection;
					state = PICK_TWO_EX;
					// remake our input array
					pInput = new float[component[operand[1]][0] * component[operand[1]][1]];

					for(int j = 0; j < component[operand[1]][0] * component[operand[1]][1]; ++j)
						pInput[j] = 0;
			}	 
			// Are we on the back button?
			if(CursorInRect(button_back, cursor_pos))
			{
				DrawQuad(7, button_back.left - 50, button_back.top - 20, button_back.right + 50, button_back.bottom + 20);

				// let's go back
				if(GetAsyncKeyState(VK_LBUTTON) && !key_press[VK_LBUTTON])
				{
					key_press[VK_LBUTTON] = true;
					forward = false;

					chosen_square = 0;

					state = PICK_TWO_EX;
					break;
				}
				
			}

		}
		break;

		// Make the buttons go bye-bye
		case PICK_TWO_EX:
		{
			//////////////////////////////////////////////////////////////////////////////////
			// Draw our GUI elements
			//////////////////////////////////////////////////////////////////////////////////
			DrawQuad(operation + OPER_OFFSET, 452, input_y_pos[0], 572, input_y_pos[0] + 270);
			DrawQuad(18, input_x_pos[2], 20, input_x_pos[2] + 500, 350 );
			DrawMat(one, 235 - (one->col - 1) * 30, 155 - (one->row - 1) * 30);
				
			if(forward)
				input_x_pos[1] += (1040 - input_x_pos[1]) / 10;
			DrawQuad(11, input_x_pos[1] + 120, 690, input_x_pos[1] + 570, 745);
			//////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////

			if(which > 6)
				which = 6;
			if(which > -1)
				button_angle[which] += 15;
			if(button_angle[which] > 60 && which > -1)
					--which;
			// Bye bye buttons, we love you
			for(int i = 0; i < 7; ++i)
			{
				if(i > which && button_angle[i] < 91)
					button_angle[i] += 15;
					
				if(button_angle[i] > 100)
					button_angle[i] = 100; 
			}
			bool valid_buttons[7] = { 0, };
			// Once again we darken the buttons that can't be picked
			if(operand[0] == VECTOR2 ||	operand[0] == VECTOR3 || operand[0] == VECTOR4)
			{
				if(operation == MULTIPLY)
				{
					valid_buttons[SCALAR] = true;
				}
				else
				{
					valid_buttons[operand[0]] = true;
				}
			}
			else if(operand[0] == MATRIX2 ||	operand[0] == MATRIX3 || operand[0] == MATRIX4)
			{
				if(operation == MULTIPLY)
				{
					valid_buttons[SCALAR] = true;
					valid_buttons[operand[0]] = true;
					valid_buttons[operand[0] - 3] = true;
				}
				else
				{
					valid_buttons[operand[0]] = true;
				}
			}
			else
			{
				for(int i = 0; i < 6; ++i)
				{
					valid_buttons[i] = true;
				}
			}
			// Draw our buttons
			for(i = 0; i < 7; ++i)
			{
				glPushMatrix();
					glTranslatef(-35, 400 + i * 55, 0);
					glRotatef(button_angle[i], 0, 0, 1);

					DrawQuad(i, 0 - i * 20, -55, 450 - i * 20, 0,
							 valid_buttons[i] ? 1 : .3f, 
							 valid_buttons[i] ? 1 : .3f, 
							 valid_buttons[i] ? 1 : .3f, 1);
				glPopMatrix();
			}
				 
			// If we're going back in time...
			if(!forward)
			{
				// move our windwo into place
				input_y_pos[0] += (-270 - input_y_pos[0]) / 10;
				
				if(button_angle[0] == 100)
				{
					// pick our operation again
					operation = 0;
					state = OPERATION_ENT;
				}
			}
			// Otherwise, back to the input state
			else
			{
				if(button_angle[0] == 100)
					state = INPUT_ENT;
			}
		}
		break;

		case SOLVE:
		{
			//////////////////////////////////////////////////////////////////////////////////
			// Draw our GUI elements
			//////////////////////////////////////////////////////////////////////////////////
			// Draw the operation window
			DrawQuad(operation + OPER_OFFSET, 452, input_y_pos[0], 572, input_y_pos[0] + 270);
			// Draw the left operand window
			DrawQuad(18, input_x_pos[2], 20, input_x_pos[2] + 500, 350 );
			// Draw the left operand inside the operand window
			DrawMat(one, 235 - (one->col - 1) * 30, 155 - (one->row - 1) * 30);	 

			// Draw the right operand window
			DrawQuad(8, input_x_pos[3], 20, input_x_pos[3] + 515, 350 );
			// Draw the right operand inside the operand window
			DrawMat(two, 735 - (two->col - 1) * 30, 155 - (two->row - 1) * 30);	 

			// Draw the back button
			DrawQuad(11, input_x_pos[1] + 120, 690, input_x_pos[1] + 570, 745);
			// Draw the solve button
			DrawQuad(24, input_x_pos[3] + 120, 640, input_x_pos[3] + 570, 695);
			//////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////


			// check to see if we're on the back button
			if(CursorInRect(button_back, cursor_pos))
			{
				// high light it
				DrawQuad(7, button_back.left - 50, button_back.top - 20, button_back.right + 50, button_back.bottom + 20);

				if(GetAsyncKeyState(VK_LBUTTON) && !key_press[VK_LBUTTON])
				{
					key_press[VK_LBUTTON] = true;
					forward = false;

					// reset everything back to the way it should be for the beginning of
					// the previous state
					which_input = 1;

					input_buffer[0] = '\0';
					chosen_square = 0;

					pInput = new float[two->row * two->col];
					memcpy(pInput, two->pData, sizeof(float) * two->row * two->col);
					delete two;
					two = NULL;
					// let's go back
					state = SOLVE_EX;
					break;
				}
				
			}
			// Check to see if we're on the solve button
			if(CursorInRect(button_ent, cursor_pos))
			{
				// High light it
				DrawQuad(7, button_ent.left - 50, button_ent.top - 20, button_ent.right + 50, button_ent.bottom + 20);

				if(GetAsyncKeyState(VK_LBUTTON) && !key_press[VK_LBUTTON])
				{
					key_press[VK_LBUTTON] = true;
					forward = true;

					// Calculate our answer
					answer = MatCalc::pf_solve[operation - MULTIPLY](one, two);

					// Time to move on
					state = SOLVE_EX;
					break;
				}
				
			}

		}
		break;

		case SOLVE_EX:
		{
			//////////////////////////////////////////////////////////////////////////////////
			// Draw our GUI elements
			//////////////////////////////////////////////////////////////////////////////////
			// Draw the left operand window
			DrawQuad(18, input_x_pos[2], 20, input_x_pos[2] + 500, 350 );
			// Draw the left operand inside the operand window
			DrawMat(one, 235 - (one->col - 1) * 30, 155 - (one->row - 1) * 30);	 
			
			if(operation != NORMALIZE)
			{
				// Draw the operation window
				DrawQuad(operation + OPER_OFFSET, 452, input_y_pos[0], 572, input_y_pos[0] + 270);

				// Draw the right operand window
				DrawQuad(8, input_x_pos[3], 20, input_x_pos[3] + 515, 350 );

				// Draw the back button
				DrawQuad(11, input_x_pos[1] + 120, 690, input_x_pos[1] + 570, 745);
				// Draw the solve button
				DrawQuad(24, input_x_pos[1] + 120, 640, input_x_pos[1] + 570, 695);
			}

			if(forward)
			{
				input_y_pos[1] -= (input_y_pos[1] - 368) / 10;

				DrawQuad(25, 300, input_y_pos[1], 724, input_y_pos[1] + 400);

				if(operation != NORMALIZE)
				{
					input_x_pos[1] += (1040 - input_x_pos[1]) / 10;
					// Draw the right operand inside the operand window
					DrawMat(two, 735 - (two->col - 1) * 30, 155 - (two->row - 1) * 30);	 

				}
				
				if(input_y_pos[1] < 380)
					state = SOLUTION;
			}
			//////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////
			else
			{
				// move everyone in to place
				input_x_pos[1] += (1040 - input_x_pos[1]) / 10;
				input_x_pos[3] += (1040 - input_x_pos[3]) / 10;
				
				if(input_x_pos[1] > 1024)
					state = INPUT_ENT;
			}
		}
		break;

		case SOLUTION:
		{
			//////////////////////////////////////////////////////////////////////////////////
			// Draw our GUI elements
			//////////////////////////////////////////////////////////////////////////////////
			// Draw the left operand window
			DrawQuad(18, input_x_pos[2], 20, input_x_pos[2] + 500, 350 );
			// Draw the left operand inside the operand window
			DrawMat(one, 235 - (one->col - 1) * 30, 155 - (one->row - 1) * 30);
			
			DrawQuad(25, 300, input_y_pos[1], 724, input_y_pos[1] + 400);
			DrawMat(answer, 482 - (answer->col - 1) * 30, 512 - (answer->row - 1) * 30);

			if(operation != NORMALIZE)
			{	 
				// Draw the operation window
				DrawQuad(operation + OPER_OFFSET, 452, input_y_pos[0], 572, input_y_pos[0] + 270);

				// Draw the right operand window
				DrawQuad(8, input_x_pos[3], 20, input_x_pos[3] + 515, 350 );
				// Draw the right operand inside the operand window
				DrawMat(two, 735 - (two->col - 1) * 30, 155 - (two->row - 1) * 30);	 
			}
			//////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////

			// Check to see if we're on the clear button
			if(CursorInRect(button_clear, cursor_pos))
			{
				// Highlight it
				DrawQuad(7, button_clear.left - 50, button_clear.top - 20, button_clear.right + 50, button_clear.bottom + 20);

				if(GetAsyncKeyState(VK_LBUTTON) && !key_press[VK_LBUTTON])
				{
					key_press[VK_LBUTTON] = true;
					// Clean up our memeory
					delete one;
					delete answer;

					if(operation != NORMALIZE)
					{
						delete two;
					}
					state = SOLUTION_EX;
					break;
				}
			}

		}
		break;

		case SOLUTION_EX:
		{
			//////////////////////////////////////////////////////////////////////////////////
			// Draw our GUI elements
			//////////////////////////////////////////////////////////////////////////////////
			// Draw the left operand window
			DrawQuad(18, input_x_pos[2], 20, input_x_pos[2] + 500, 350 );
			
			DrawQuad(25, 300, input_y_pos[1], 724, input_y_pos[1] + 400);
			
			input_y_pos[1] += (770 - input_y_pos[1]) / 10;
			input_x_pos[2] += (-511 - input_x_pos[2]) / 10;
			
			if(operation != NORMALIZE)
			{
				// Draw the operation window
				DrawQuad(operation + OPER_OFFSET, 452, input_y_pos[0], 572, input_y_pos[0] + 270);

				// Draw the right operand window
				DrawQuad(8, input_x_pos[3], 20, input_x_pos[3] + 515, 350 );


				input_y_pos[0] += (-270 - input_y_pos[0]) / 10;
				input_x_pos[3] += (1040 - input_x_pos[3]) / 10;
			}
			//////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////

			// Make all the windows go away
			if(input_x_pos[2] < -500)
			{
				which_input = 0;
				
				input_x_pos[2] = -500;	
				input_x_pos[3] = 1024;	
				input_y_pos[0] = -270;	
				input_x_pos[1] = 770;
				
				state = PICK_ONE_ENT;	
			}
		}
		break;
	}		   
	PerspectiveMode();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	// Draw the threads
	for(i = 0; i < threadCount; ++i)
	{

		glBegin(GL_LINE_STRIP);
			for(int j = 0; j < threadLength; ++j)
			{
				// generate thread color
				rd = 0.3f * (0.3f + sin(3 * angle / 130 - i / 50.0f)) * (1 - (float)j / threadLength);
				gr = 0.3f * (0.3f + sin(3 * angle / 70 - i / 45.0f)) * (1 - (float)j/ threadLength);
				bl = 0.3f * (0.3f + cos(3 * angle / 100 - i / 60.0f)) * (1- (float)j / threadLength);
				glColor3f(rd, gr, bl);
				glVertex3f(threads[i][j].x, threads[i][j].y, threads[i][j].z);
			}
		glEnd();
	}	  
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	
	OrthoMode(0, 0, 1024, 768);
	
	DrawQuad(28, cursor_pos.x - 20, cursor_pos.y - 20, cursor_pos.x + 20, cursor_pos.y + 20);
	
	PerspectiveMode();		
	
glPopMatrix();


	// Calculate our FPS and set it as the window text
	++frames;
	if(!(frames % 100))
	{
		float fps = float(frames) / timer.getElapsedTime();

		char cBuffer[32];
		sprintf(cBuffer, "%.2f FPS", fps);

		SetWindowText(hWnd, cBuffer);

		frames = 0;
		timer.Reset();
	}
	// OK Lady, buh-bye!!
	if(GetAsyncKeyState(VK_ESCAPE))
		return FALSE;

	// Buffering the key inputs
	for(int m = 0; m < 256; ++m)
	{
		if(!GetAsyncKeyState(m))
			key_press[m] = false;
	}
	
	// Limit to 33 FPS
	while(GetTickCount() - start_time < 30) { } 

	return TRUE;	  

}
// initialize our game
GLvoid OGL_Wrapper::InitGame(GLvoid)
{
	srand((unsigned int)time(0));
	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	// Set up the camera
	camera.RotateLocalY(180.0f);
	camera.SetOrigin(0.0f, 0.0f, 0.0f); 

	// set up the button locations
	for(int i = 0; i < 7; ++i)
	{
		button[i].left = 215 - i * 20;
		button[i].right = button[i].left + 160;
		button[i].top = 355 + i * 55;
		button[i].bottom = button[i].top + 35;
	}
	input_buffer[0] = '\0';

	// Create our tunnel
	for(i = 0; i < 33; ++i)
	{
		for(int j = 0; j < 33; ++j)
		{
			Tunnels[i][j].x = (3.0 - j / 12.0f) * cos((2 * PI / 32) * i);
			Tunnels[i][j].y = (3.0 - j / 12.0f) * sin((2 * PI / 32) * i);
			Tunnels[i][j].z = -j;
		}
	}
	// Initialize our threads' random factors
	for(i = 0; i < maxThreads; ++i)
	{
		rnd[i].x = random(200, 100) / 1000.0f;
		rnd[i].y = random(200, 100) / 1000.0f;
		rnd[i].z = random(200, 100) / 1000.0f;
	}
}
GLvoid OGL_Wrapper::ShutdownGame()
{
	DestroyFont();			// This frees up our font display list									
}

// all our GL initialization goes here
int OGL_Wrapper::InitGL(bool firstLoad)
{
	glShadeModel(GL_SMOOTH);				// enables smooth shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// black background

	// enable depth testing
	glClearDepth(1.0f);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_LINE_SMOOTH);
    glEnable(GL_NORMALIZE);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// perspective calculation

	// Create our font list
	CreateOpenGLFont("Courier New", FONT_HEIGHT);
	// Load all of our textures
	for(int i = 0; i < MAX_TARGA_TEXTURES; ++i)
	{
		CreateTargaTexture(t_Texture, file_name[i], i);
	}

	return TRUE;
}


// Resize and initialize our GL window
GLvoid OGL_Wrapper::ReSizeGLScene(GLsizei width, GLsizei height)
{
	// prevents divide by zero issues
	if(!height)
		height = 1;

	glViewport(0, 0, width, height);		// reset the current viewport

	glMatrixMode(GL_PROJECTION);			// Select The Projection Matrix
	glLoadIdentity();						// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height, 0.1f, 50.0f);

	glMatrixMode(GL_MODELVIEW);				// Select The Modelview Matrix
	glLoadIdentity();						// Reset The Modelview Matrix
}



// release the rendering context, the device context, and finally the window handle
GLvoid OGL_Wrapper::KillGLWindow(HINSTANCE hInstance)
{
	// resolves issues on some graphics cards where the desktop gets corrupted
	if(fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);		// force the computer back to the desktop settings
		ShowCursor(TRUE);
	}

	if(hRC)
	{
		if(!wglMakeCurrent(NULL, NULL))
		{
			MessageBox(NULL, "Release of DC and RC failed", "SHUTDOWN ERROR", 
					   MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(hRC))			// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR",
					   MB_OK | MB_ICONINFORMATION);
		}

		hRC = NULL;						
	}

	if (hDC && !ReleaseDC(hWnd,hDC))		// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.","SHUTDOWN ERROR",
				   MB_OK | MB_ICONINFORMATION);
		hDC = NULL;							
	}

	if (hWnd && !DestroyWindow(hWnd))		// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.","SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;						
	}

	if (!UnregisterClass("OpenGL", hInstance))	// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;					
	}
}
// Create our window
BOOL OGL_Wrapper::CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag,
								 HINSTANCE hInstance, bool firstLoad/*, WNDPROC WndProc*/)
{

	GLuint PixelFormat;						// Holds The Results After Searching For A Match
 	WNDCLASS wc;							// Windows Class Structure

 	DWORD dwExStyle;						// Window Extended Style
	DWORD dwStyle;							// Window Style

	// Grabs Rectangle Upper Left / Lower Right Values
	RECT WindowRect;						
	WindowRect.left = (long)0;				
	WindowRect.right = (long)width;			
	WindowRect.top = (long)0;				
	WindowRect.bottom = (long)height;

	fullscreen = fullscreenflag;							// Set The Global Fullscreen Flag
	
	if(fullscreen)											// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;									// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));		// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);			// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;					// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;					// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;						// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_PELSWIDTH|DM_PELSHEIGHT | DM_BITSPERPEL;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if(ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Run In A Window.
			if(MessageBox(NULL,"Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",
				"OpenGL", MB_YESNO|MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;				// Select Windowed Mode 
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK|MB_ICONSTOP);
				return FALSE;					// Exit And Return FALSE
			}
		}
	}
	// I am using my own cursor to disable the "use cursor shadow" option if it has been selected
	// by the user.  The shadow makes the game look terribly 2 dimensional
//	HCURSOR cursor = (HCURSOR)LoadImage(NULL, "3dwarro.cur", IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);		


	hInstance			= GetModuleHandle(NULL);			// Grab An Instance For Our Window
	wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Move, And Own DC For Window
	wc.lpfnWndProc		= (WNDPROC) WndProc;				// WndProc Handles Messages
	wc.cbClsExtra		= 0;								// No Extra Window Data
	wc.cbWndExtra		= 0;								// No Extra Window Data
	wc.hInstance		= hInstance;						// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);		// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);  	// Load The Arrow Pointer
	wc.hbrBackground	= NULL;								// No Background Required For GL
	wc.lpszMenuName		= NULL;								// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";							// Set The Class Name

	RegisterClass(&wc);										// Register our window
															
	if (fullscreen)								// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;			// Window Extended Style
		dwStyle = WS_POPUP;						// Windows Style
		ShowCursor(FALSE);						// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;					// Windows Style
		ShowCursor(FALSE);						// Hide Mouse Pointer

	}
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	if (!(hWnd = CreateWindowEx(	dwExStyle,			// Extended Style For The Window
					"OpenGL",							// Class Name
					title,								// Window Title
					WS_CLIPSIBLINGS | WS_CLIPCHILDREN |	dwStyle,	// Selected Window Style
					0, 0,								// Window Position
					WindowRect.right-WindowRect.left,	// Calculate Adjusted Window Width
					WindowRect.bottom-WindowRect.top,	// Calculate Adjusted Window Height
					NULL,								// No Parent Window
					NULL,								// No Menu
					hInstance,							// Instance
					NULL)))								// Don't Pass Anything To WM_CREATE

	{
		KillGLWindow(hInstance);									// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =		// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),		// Size Of This Pixel Format Descriptor
		1,									// Version Number
		PFD_DRAW_TO_WINDOW |				// Format Must Support Window
		PFD_SUPPORT_OPENGL |				// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,					// Must Support Double Buffering
		PFD_TYPE_RGBA,						// Request An RGBA Format
		bits,								// Select Our Color Depth
		0, 0, 0, 0, 0, 0,					// Color Bits Ignored
		0,									// No Alpha Buffer
		0,									// Shift Bit Ignored
		0,									// No Accumulation Buffer
		0, 0, 0, 0,							// Accumulation Bits Ignored
		32,									// 32 Bit Z-Buffer (Depth Buffer)
		0,									// No Stencil Buffer
		0,									// No Auxiliary Buffer
		PFD_MAIN_PLANE,						// Main Drawing Layer
		0,									// Reserved
		0, 0, 0								// Layer Masks Ignored
	};

	hDC = GetDC(hWnd);						// get a DC

	// Get a pixel format and set it
	PixelFormat = ChoosePixelFormat(hDC,&pfd);
	SetPixelFormat(hDC,PixelFormat,&pfd);

	// Creates a rendering contet compatible with this DC
	hRC = wglCreateContext(hDC);

	// Binds the the OpenGL rendering context to the window DC
	wglMakeCurrent(hDC, hRC);

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen


	if (!InitGL(firstLoad))								// Initialize Our Newly Created GL Window
	{
		KillGLWindow(hInstance);							// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;							// Return FALSE
	}

	return TRUE;
}


// Our windows procedure function
LRESULT CALLBACK OGL_Wrapper::WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)								// Check For Windows Messages
	{
		case WM_ACTIVATE:						// Watch For Window Activate Message
		{
			// Check Minimization State
//			(!HIWORD(wParam)) ? active = TRUE : active = FALSE;	
			return 0;							// Return To The Message Loop
		}


		case WM_SYSCOMMAND:						// Intercept System Commands
		{
			switch (wParam)						// Check System Calls
			{
				case SC_SCREENSAVE:				// Screensaver Trying To Start?
				case SC_MONITORPOWER:			// Monitor Trying To Enter Powersave?
				return 0;						// Prevent From Happening
			}
			break;								// Exit
		}
		case WM_CLOSE:							// Did We Receive A Close Message?
		{
			PostQuitMessage(0);					// Send A Quit Message
			return 0;							
		}
		case WM_SIZE:							// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));		// LoWord = Width, HiWord = Height
			return 0;						
		}
	}
				   
	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);	
}

void OGL_Wrapper::DrawSphere(float radius)
{
	GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);

	gluSphere(pObj, radius, 26, 52);
	gluDeleteQuadric(pObj);

}


void OGL_Wrapper::CreateTargaTexture(UINT textureArray[], LPSTR strFileName, int textureID)
{
	if(!strFileName)									// Return from the function if no file name was passed in
		return;

	tImageTGA *pImage = LoadTGA(strFileName);			// Load the image and store the data

	if(pImage == NULL)									// If we can't load the file, quit!
		exit(0);

	// Generate a texture with the associative texture ID stored in the array
	glGenTextures(1, &textureArray[textureID]);

	// Bind the texture to the texture arrays index and init the texture
	glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);



	// Assume that the texture is a 24 bit RGB texture (We convert 16-bit ones to 24-bit)
	int textureType = GL_RGB;

	// If the image is 32-bit (4 channels), then we need to specify GL_RGBA for an alpha
	if(pImage->channels == 4)
		textureType = GL_RGBA;
		
	// Build Mipmaps (builds different versions of the picture for distances - looks better)
	gluBuild2DMipmaps(GL_TEXTURE_2D, pImage->channels, pImage->sizeX, 
					  pImage->sizeY, textureType, GL_UNSIGNED_BYTE, pImage->data);



	// Lastly, we need to tell OpenGL the quality of our texture map.
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);	

	// Now we need to free the image data that we loaded since OpenGL stored it as a texture
	if (pImage)										// If we loaded the image
	{
		if (pImage->data)							// If there is texture data
		{
			delete[] pImage->data;					// Free the texture data, we don't need it anymore
		}

		free(pImage);								// Free the image structure
	}	  
}

tImageTGA *LoadTGA(const char *filename)
{
	tImageTGA *pImageData = NULL;		// This stores our important image data
	WORD width = 0, height = 0;			// The dimensions of the image
	byte length = 0;					// The length in bytes to the pixels
	byte imageType = 0;					// The image type (RLE, RGB, Alpha...)
	byte bits = 0;						// The bits per pixel for the image (16, 24, 32)
	FILE *pFile = NULL;					// The file pointer
	int channels = 0;					// The channels of the image (3 = RGA : 4 = RGBA)
	int stride = 0;						// The stride (channels * width)
	int i = 0;							// A counter
		
	// Open a file pointer to the targa file and check if it was found and opened 
	if((pFile = fopen(filename, "rb")) == NULL) 
	{
		// Display an error message saying the file was not found, then return NULL
		MessageBox(NULL, "Unable to load TGA File!", "Error", MB_OK);
		return NULL;
	}
		
	// Allocate the structure that will hold our eventual image data (must free it!)
	pImageData = (tImageTGA*)malloc(sizeof(tImageTGA));

	// Read in the length in bytes from the header to the pixel data
	fread(&length, sizeof(byte), 1, pFile);
	
	// Jump over one byte
	fseek(pFile,1,SEEK_CUR); 

	// Read in the imageType (RLE, RGB, etc...)
	fread(&imageType, sizeof(byte), 1, pFile);
	
	// Skip past general information we don't care about
	fseek(pFile, 9, SEEK_CUR); 

	// Read the width, height and bits per pixel (16, 24 or 32)
	fread(&width,  sizeof(WORD), 1, pFile);
	fread(&height, sizeof(WORD), 1, pFile);
	fread(&bits,   sizeof(byte), 1, pFile);
	
	// Now we move the file pointer to the pixel data
	fseek(pFile, length + 1, SEEK_CUR); 

	// Check if the image is RLE compressed or not
	if(imageType != TGA_RLE)
	{
		// Check if the image is a 24 or 32-bit image
		if(bits == 24 || bits == 32)
		{
			// Calculate the channels (3 or 4) - (use bits >> 3 for more speed).
			// Next, we calculate the stride and allocate enough memory for the pixels.
			channels = bits / 8;
			stride = channels * width;
			pImageData->data = new unsigned char[stride * height];

			// Load in all the pixel data line by line
			for(int y = 0; y < height; y++)
			{
				// Store a pointer to the current line of pixels
				unsigned char *pLine = &(pImageData->data[stride * y]);

				// Read in the current line of pixels
				fread(pLine, stride, 1, pFile);
			
				// Go through all of the pixels and swap the B and R values since TGA
				// files are stored as BGR instead of RGB (or use GL_BGR_EXT verses GL_RGB)
				for(i = 0; i < stride; i += channels)
				{
					int temp     = pLine[i];
					pLine[i]     = pLine[i + 2];
					pLine[i + 2] = temp;
				}
			}
		}
		// Check if the image is a 16 bit image (RGB stored in 1 unsigned short)
		else if(bits == 16)
		{
			unsigned short pixels = 0;
			int r=0, g=0, b=0;

			// Since we convert 16-bit images to 24 bit, we hardcode the channels to 3.
			// We then calculate the stride and allocate memory for the pixels.
			channels = 3;
			stride = channels * width;
			pImageData->data = new unsigned char[stride * height];

			// Load in all the pixel data pixel by pixel
			for(int i = 0; i < width*height; i++)
			{
				// Read in the current pixel
				fread(&pixels, sizeof(unsigned short), 1, pFile);
				
				b = (pixels & 0x1f) << 3;
				g = ((pixels >> 5) & 0x1f) << 3;
				r = ((pixels >> 10) & 0x1f) << 3;
				
				// This essentially assigns the color to our array and swaps the
				// B and R values at the same time.
				pImageData->data[i * 3 + 0] = r;
				pImageData->data[i * 3 + 1] = g;
				pImageData->data[i * 3 + 2] = b;
			}
		}	
		// Else return a NULL for a bad or unsupported pixel format
		else
			return NULL;
	}
	// Else, it must be Run-Length Encoded (RLE)
	else
	{
		// Create some variables to hold the rleID, current colors read, channels, & stride.
		byte rleID = 0;
		int colorsRead = 0;
		channels = bits / 8;
		stride = channels * width;

		// Next we want to allocate the memory for the pixels and create an array,
		// depending on the channel count, to read in for each pixel.
		pImageData->data = new unsigned char[stride * height];
		byte *pColors = new byte [channels];

		// Load in all the pixel data
		while(i < width*height)
		{
			// Read in the current color count + 1
			fread(&rleID, sizeof(byte), 1, pFile);
			
			// Check if we don't have an encoded string of colors
			if(rleID < 128)
			{
				// Increase the count by 1
				rleID++;

				// Go through and read all the unique colors found
				while(rleID)
				{
					// Read in the current color
					fread(pColors, sizeof(byte) * channels, 1, pFile);

					// Store the current pixel in our image array
					pImageData->data[colorsRead + 0] = pColors[2];
					pImageData->data[colorsRead + 1] = pColors[1];
					pImageData->data[colorsRead + 2] = pColors[0];

					// If we have a 4 channel 32-bit image, assign one more for the alpha
					if(bits == 32)
						pImageData->data[colorsRead + 3] = pColors[3];

					// Increase the current pixels read, decrease the amount
					// of pixels left, and increase the starting index for the next pixel.
					i++;
					rleID--;
					colorsRead += channels;
				}
			}
			// Else, let's read in a string of the same character
			else
			{
				// Minus the 128 ID + 1 (127) to get the color count that needs to be read
				rleID -= 127;

				// Read in the current color, which is the same for a while
				fread(pColors, sizeof(byte) * channels, 1, pFile);

				// Go and read as many pixels as are the same
				while(rleID)
				{
					// Assign the current pixel to the current index in our pixel array
					pImageData->data[colorsRead + 0] = pColors[2];
					pImageData->data[colorsRead + 1] = pColors[1];
					pImageData->data[colorsRead + 2] = pColors[0];

					// If we have a 4 channel 32-bit image, assign one more for the alpha
					if(bits == 32)
						pImageData->data[colorsRead + 3] = pColors[3];

					// Increase the current pixels read, decrease the amount
					// of pixels left, and increase the starting index for the next pixel.
					i++;
					rleID--;
					colorsRead += channels;
				}
				
			}
				
		}

		// Free up pColors
		delete[] pColors;
	}

	// Close the file pointer that opened the file
	fclose(pFile);

	// Fill in our tImageTGA structure to pass back
	pImageData->channels = channels;
	pImageData->sizeX    = width;
	pImageData->sizeY    = height;

	// Return the TGA data (remember, you must free this data after you are done)
	return pImageData;
}


void OGL_Wrapper::OrthoMode(int left, int top, int right, int bottom)
{
	// Switch to our projection matrix so that we can change it to ortho mode, not perspective.
	glMatrixMode(GL_PROJECTION);						

	// Push on a new matrix so that we can just pop it off to go back to perspective mode
	glPushMatrix();									
	
	// Reset the current matrix to our identify matrix
	glLoadIdentity();								

	//Pass in our 2D ortho screen coordinates.like so (left, right, bottom, top).  The last
	// 2 parameters are the near and far planes.
	glOrtho( left, right, bottom, top, 0, 1 );	
	
	// Switch to model view so that we can render the scope image
	glMatrixMode(GL_MODELVIEW);								

	// Initialize the current model view matrix with the identity matrix
	glLoadIdentity();										
}

void OGL_Wrapper::PerspectiveMode()										
{
	// Enter into our projection matrix mode
	glMatrixMode( GL_PROJECTION );							

	// Pop off the last matrix pushed on when in projection mode (Get rid of ortho mode)
	glPopMatrix();											

	// Go back to our model view matrix like normal
	glMatrixMode( GL_MODELVIEW );							

	// We should be in the normal 3D perspective mode now
}

bool OGL_Wrapper::CursorInRect(RECT &r, POINT &cur)
{
	return (cur.x < r.right && cur.x > r.left && cur.y > r.top && cur.y < r.bottom);
}


void OGL_Wrapper::CreateOpenGLFont(char *strFontName, int height)	// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	g_FontListID = glGenLists(MAX_CHARS);				// Storage For 96 Characters

	font = CreateFont(	height,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						strFontName);					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 0, MAX_CHARS - 1, g_FontListID);				// Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font
}



GLvoid OGL_Wrapper::glPrint(const char *text)					// Custom GL "Print" Routine
{
	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(g_FontListID);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}


///////////////////////////////// DESTROY FONT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This function frees our display lists
/////
///////////////////////////////// DESTROY FONT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

void OGL_Wrapper::DestroyFont()										
{
	glDeleteLists(g_FontListID, MAX_CHARS);				// Free the display list
}

void OGL_Wrapper::DrawQuad(int tex, int left, int top, int right, int bottom,
						   float r, float g, float b, float a)
{
	if(tex > -1)
		glBindTexture(GL_TEXTURE_2D, t_Texture[tex]);

	glBegin(GL_QUADS);

		glColor4f(r, g, b, a);
		// Display the top left vertex
		glTexCoord2f(0.01f, 1.0f);
		glVertex2f(left, top);

		// Display the bottom left vertex
		glTexCoord2f(0.01f, 0.0f);
		glVertex2f(left, bottom);

		// Display the bottom right vertex
		glTexCoord2f(.99f, 0.0f);
		glVertex2f(right, bottom);

		// Display the top right vertex
		glTexCoord2f(.99f, 1.0f);
		glVertex2f(right, top);

	// Stop drawing QUADS
	glEnd();

}
void OGL_Wrapper::DrawMat(MatCalc *mat, int tX, int tY)
{
	int index = 0;
	for(int i = 0; i < mat->row; ++i)
	{
		for(int j = 0; j < mat->col; ++j)
		{
			RECT square = { tX + (60 * j), tY + (60 * i), tX + (60 * j) + 58, tY + (60 * i) + 58};

			DrawQuad(9, square.left, square.top, square.right, square.bottom,
					 1, 1, 1, .3f); 


			glPushMatrix();
				glDisable(GL_TEXTURE_2D);
				glColor4f(0, 1, 0, 1);					// Make the next text green
				char pTemp[100];
				if(mat->pData[index] == (int)mat->pData[index])
					sprintf(pTemp, "%.1f", mat->pData[index]); 
				else
					sprintf(pTemp, "%.2f", mat->pData[index]);
					 
				// Position The Text On The Screen
				glRasterPos2f(square.left + 30 - strlen(pTemp) * 4, square.top + 35);
 				glPrint(pTemp);			// Print GL Text To The Screen
				glEnable(GL_TEXTURE_2D);
			glPopMatrix();

			++ index; 
			
		}
	}

}

// Returns a random integer between high and low
int random(int high, int low)
{
	// Swap the numbers if they're passed in the wrong order
	if(low > high)
	{
		low ^= high;
		high ^= low;
		low ^= high;
	}
	// Return our random number
	return rand() % (high - low + 1) + low;
}

										

 