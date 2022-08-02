// OGL_Wrapper.cpp: implementation of the OGL_Wrapper class.
//
//////////////////////////////////////////////////////////////////////
#include <ctime>
#include <cmath>
#include <vector>
using namespace std;

#include "OGL_Wrapper.h"

#include "glframe.h"

#define PI 3.141593f

#define NUM_OBJECTS 19
#define TABLE (NUM_OBJECTS - 1)
#define LEGS (NUM_OBJECTS - 2)
#define STICK (NUM_OBJECTS - 3)

#define CUEBALL 100

// These defines are used to tell us about the type of TARGA file it is
#define TGA_RGB		 2			// This tells us it's a normal RGB (really BGR) file
#define TGA_A		 3			// This tells us it's a ALPHA file
#define TGA_RLE		10			// This tells us that the targa is Run-Length Encoded (RLE)
#define MAX_TARGA_TEXTURES 9	// This is the max number of targa textures being loaded

// This is our image structure for our targa data
struct tImageTGA
{
	int channels;			// The channels in the image (3 = RGB : 4 = RGBA)
	int sizeX;				// The width of the image in pixels
	int sizeY;				// The height of the image in pixels
	unsigned char *data;	// The image pixel data
};

// Our model names
char *file_name[NUM_OBJECTS] = { "ball0.3ds", "ball1.3ds", "ball2.3ds", "ball3.3ds", 
	"ball4.3ds", "ball5.3ds", "ball6.3ds", "ball7.3ds", "ball8.3ds", "ball9.3ds", 
	"ball10.3ds", "ball11.3ds", "ball12.3ds", "ball13.3ds", "ball14.3ds", "ball15.3ds", 
	"stick.3ds", "legs.3ds", "table.3ds"};
///////////////////////////////////////////////////////////////////////////////////////////
UINT g_Texture[NUM_OBJECTS][MAX_TEXTURES] = {0, };		// This holds the texture info, referenced by an ID
UINT t_Texture[MAX_TARGA_TEXTURES] = { 0, };			// This is our texture data array

CLoad3DS g_Load3ds[NUM_OBJECTS];						// This is 3DS class.  This should go in a good model class.
t3DModel g_3DModel[NUM_OBJECTS];						// This holds the 3D Model info that we load in

OrthonormalFrame camera;								// Our camera
int   g_ViewMode	  = GL_TRIANGLES;					// We want the default drawing mode to be normal
bool  g_bLighting     = true;							// Turn lighting on initially
float g_RotateX		  = 0.0f;							// This is the current value at which the model is rotated
float g_RotationSpeed = 0.8f;							// This is the speed that our model rotates.  (-speed rotates left)
//////////////////////////////////////////////////////////////////////////////////////////
bool key_press[256] = { 0, };					// Buffering key input
bool disable_camera = false;					// true if the camera can't be moved
bool draw_normals = false;						// True if we're drawing normals

// Our relational vectors					  
GLT_VECTOR3 world_up = { 0, 0, 1.0f };
GLT_VECTOR3 world_down = { 0, 0, -1.0f };
GLT_VECTOR3 focal_point = { 0, 0, -10.0f };		// The focal point of the camera


///////////////////////////////////////////////////////////////////////////////////////////////////
// Object Selection Code
///////////////////////////////////////////////////////////////////////////////////////////////////
RECT  g_rRect;						// This holds the window dimensions
int objectID = 0;					// Used for object selection
///////////////////////////////////////////////////////////////////////////////////////////////////
// Camera variables
///////////////////////////////////////////////////////////////////////////////////////////////////
float cam_x = 0;					// The camera's x, y and z, respectively
float cam_y = 0;
float cam_z = 0;
float dist_to_center = -10;			// The distance of the camera from its focal point

float angle = 0;					// The angle made between the camera and the xy plane
///////////////////////////////////////////////////////////////////////////////////////////////////
// aiming variables
///////////////////////////////////////////////////////////////////////////////////////////////////
bool aiming = false;				// True if we are in aiming mode
GLT_POINT3 cue_tip = { 0, };		// The world coordinates of the cue's tip
float cue_angle = 180.0f;			// The direction of the shot
float cue_dist = .12f;				// The distance of the tip from the cue ball
unsigned char blah = 1;				// test code
///////////////////////////////////////////////////////////////////////////////////////////////////
// shooting variables
///////////////////////////////////////////////////////////////////////////////////////////////////
bool shooting = false;				// True if the shot is active
int predicted_ball = 0;				// The ball number of the first ball which is giong to be struck
bool invalid_collision[16][16] = { {0, }, };   // Array used to fix minor collision issues
bool first_shot = true;				// whether or not we have broken
bool started = false;				// Bug fix
///////////////////////////////////////////////////////////////////////////////////////////////////
// GUI variables
///////////////////////////////////////////////////////////////////////////////////////////////////
int spot_x = 165;					// X and Y values of the blue dot denoting the english
int spot_y = 55;
///////////////////////////////////////////////////////////////////////////////////////////////////
// english variables
///////////////////////////////////////////////////////////////////////////////////////////////////
float x_spin = 0;					// The X and Y values of the applied english
float y_spin = 0;
bool apply_english = false;			// True if the english is valid
///////////////////////////////////////////////////////////////////////////////////////////////////
// Sound variables
///////////////////////////////////////////////////////////////////////////////////////////////////
short collision = 0;				// Handle to our collision sound
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
// Loads a targa image
tImageTGA *LoadTGA(const char *filename);

// this is where all of our drawing is done
int OGL_Wrapper::DrawGLScene(bool true_render)
{
	DWORD start_time = GetTickCount();

	// reset the screen and the depth buffer, reset the modelview matrix
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glInitNames();
    // Clear the background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_LINE_SMOOTH);

// Please fasten your seat belts and make sure all inflight luggage is secured
glPushMatrix();
	// Put the camera where it needs to be
	camera.ApplyCameraTransform();
	// Set up lighting and materials
    GLfloat diffuse_material[4] = { .8f, .8f, .8f, 0.0f };
    GLfloat ambient_light[4] = { 0.8f, 0.8f, 0.8f, 0.0f };
    GLfloat diffuse_light[4] = { .8f, .8f, .8f, 0.0f };
    GLfloat position_light[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat diffuse_material2[4] = { .0f, .8f, .0f, 0.0f };

	// Oooooooh, shiny
	GLfloat specularColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};

	// To change the material properties of our objects, we use glMaterialfv().
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularColor);

    glEnable(GL_LIGHTING);
    // Light has high diffuse and specular components
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, diffuse_light);
    
	// Set up our light
	glLightfv(GL_LIGHT0, GL_POSITION, position_light);
    glEnable(GL_LIGHT0);

	// Set counter-clockwise winding and cull our backface
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

	// High shininess
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor);
	glMateriali(GL_FRONT, GL_SHININESS, 50);

	glEnable(GL_TEXTURE_2D);


	// Rendering everything but the cue ball	 
	if(true_render)
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// Draw the floor and walls
		///////////////////////////////////////////////////////////////////////////////////////////////////
		glBindTexture(GL_TEXTURE_2D, t_Texture[5]);
		glDisable(GL_LIGHTING);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Display a quad texture to the screen
		glBegin(GL_QUADS);

			glColor4f(1, 1, 1, 1);
			// Display the top left vertex
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-25.0f, 25.0f, -13.62f);

			// Display the bottom left vertex
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-25.0f, -25.0f, -13.62f);

			// Display the bottom right vertex
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(25.0f, -25.0f, -13.62f);

			// Display the top right vertex
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(25.0f, 25.0f, -13.62f);

		// Stop drawing QUADS
		glEnd();

		// Draw a wall
		glBindTexture(GL_TEXTURE_2D, t_Texture[6]);
		glBegin(GL_QUADS);

			glColor4f(1, 1, 1, 1);
			// Display the top left vertex
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-25.0f, 25.0f, -3.0f);

			// Display the bottom left vertex
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-25.0f, 25.0f, -13.62f);

			// Display the bottom right vertex
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(25.0f, 25.0f, -13.62f);

			// Display the top right vertex
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(25.0f, 25.0f, -3.0f);

		// Stop drawing QUADS
		glEnd();

		// Draw another wall
		glBindTexture(GL_TEXTURE_2D, t_Texture[6]);
		glBegin(GL_QUADS);

			glColor4f(1, 1, 1, 1);
			// Display the top left vertex
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(25.0f, -25.0f, -3.0f);

			// Display the bottom left vertex
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(25.0f, -25.0f, -13.62f);

			// Display the bottom right vertex
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-25.0f, -25.0f, -13.62f);

			// Display the top right vertex
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-25.0f, -25.0f, -3.0f);

		// Stop drawing QUADS
		glEnd();

		// Yet another wall
		glBindTexture(GL_TEXTURE_2D, t_Texture[6]);
		glBegin(GL_QUADS);

			glColor4f(1, 1, 1, 1);
			// Display the top left vertex
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(25.0f, 25.0f, -3.0f);

			// Display the bottom left vertex
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(25.0f, 25.0f, -13.62f);

			// Display the bottom right vertex
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(25.0f, -25.0f, -13.62f);

			// Display the top right vertex
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(25.0f, -25.0f, -3.0f);

		// Stop drawing QUADS
		glEnd();

		// Draw our stairs
		glBindTexture(GL_TEXTURE_2D, t_Texture[8]);
		glBegin(GL_QUADS);

			glColor4f(1, 1, 1, 1);
			// Display the top left vertex
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-25.0f, -25.0f, -3.0f);

			// Display the bottom left vertex
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-25.0f, -25.0f, -13.62f);

			// Display the bottom right vertex
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-25.0f, 25.0f, -13.62f);

			// Display the top right vertex
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-25.0f, 25.0f, -3.0f);

		// Stop drawing QUADS
		glEnd();

		glDisable(GL_BLEND);											
		glEnable(GL_LIGHTING);	 

		///////////////////////////////////////////////////////////////////////////////////////////////////
		// Draw the table
		///////////////////////////////////////////////////////////////////////////////////////////////////
		glPushMatrix();
			static int rotX = 0;
			static int rotY = 90;
			static int rotZ = 90;

			// Translate our tabke out to where it needs to be and orient it properly
			glTranslatef(0, 0.05f, -10.0f);
			glRotatef(rotX, 1, 0, 0);
			glRotatef(rotY, 0, 1, 0);
			glRotatef(rotZ, 0, 0, 1);
			// Scale it from MAX units to OGL units
			glScalef(.010f, .010f, .010f);

			// Draw the table
			drawModel(g_3DModel[TABLE], g_Texture[TABLE]);

		glPopMatrix();			 

		////////////////////////////////////////////////////////////////////////////////////////////////
		// Draw the legs
		////////////////////////////////////////////////////////////////////////////////////////////////
		int leg_rot = 0;
		float leg_offset = 2.0f;

		// Draw the legs teice, back to back
		for(int k = 0; k < 2; ++k)
		{
			glPushMatrix();

				// Translate and orient them properly
				glTranslatef(leg_offset, 0.05f, -10.8f);
				glRotatef(rotX, 1, 0, 0);
				glRotatef(rotY, 0, 1, 0);
				glRotatef(rotZ, 0, 0, 1);
				glRotatef(leg_rot, 0, 1, 0);

				// Convert from MAX units to OGL
				glScalef(.010f, .010f, .010f);

				// Draw them
				drawModel(g_3DModel[LEGS], g_Texture[LEGS]);
			glPopMatrix();

			leg_rot = 180;
			leg_offset = -2.0f;
		}			 

		///////////////////////////////////////////////////////////////////////////////////////////////
		// Draw the balls (not including the cueball)
		///////////////////////////////////////////////////////////////////////////////////////////////
		for(k = 1; k < 16; ++k)
		{
			// Only draw it if it's not pocketed
			if(!ball[k].pocketed)
			{
				glPushMatrix();
					// Translate to where they belong
					glTranslatef(ball[k].x, ball[k].y, -9.88f);

					// Bind the shadow texture
					glBindTexture(GL_TEXTURE_2D, t_Texture[0]);
					glDisable(GL_LIGHTING);

					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					glDepthMask(false);

					// Display the shadows
					glBegin(GL_QUADS);

						// Display the top left vertice
						glTexCoord2f(0.0f, 1.0f);
						glVertex3f(-.16f, .16f, -.115f);

						// Display the bottom left vertice
						glTexCoord2f(0.0f, 0.0f);
						glVertex3f(-.16f, -.16f, -.115f);

						// Display the bottom right vertice
						glTexCoord2f(1.0f, 0.0f);
						glVertex3f(.16f, -.16f, -.115f);

						// Display the top right vertice
						glTexCoord2f(1.0f, 1.0f);
						glVertex3f(.16f, .16f, -.115f);

					// Stop drawing QUADS
					glEnd();
					glDisable(GL_BLEND);											
					glEnable(GL_LIGHTING);
					glDepthMask(true);	 
				/////////////////////////////////////////////////////////////////////////////////////////	

					// Calculate the current rotation ofthe ball based on the velocity
					ball[k].rotation += (ball[k].velocity * 500);
					if(ball[k].rotation > 360)
						ball[k].rotation -= 360;

					// roate it for the initial draw
					glRotatef(90, 0, 0, 1);

					// Only apply the movement rotation if it has a valid vector
					if(ball[k].nvec[1] || ball[k].nvec[1])
						glRotatef(ball[k].rotation, ball[k].nvec[1], -ball[k].nvec[0], 0);
					// Convert from MAX units to OGL units
					glScalef(.010f, .010f, .010f);

					// Draw the ball
					drawModel(g_3DModel[k], g_Texture[k]);

				glPopMatrix();
			}
		}			 

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

	}

	// Now that that's over with, let's render our cueball
	// Set it in our object selection queue
	glPushName(CUEBALL);
		glPushMatrix();
			// Send it where it needs to be
			glTranslatef(ball[0].x, ball[0].y, -9.88f);

			// Only render it if it hasn't been pocketed
			if(!ball[0].pocketed)
			{
				// Only render the shadow if this is the actual render, not object selection render
				if(true_render)
				{
					glBindTexture(GL_TEXTURE_2D, t_Texture[0]);
					glDisable(GL_LIGHTING);
					glDepthMask(false);

					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					// Draw the shadow
					glBegin(GL_QUADS);

						// Display the top left vertice
						glTexCoord2f(0.0f, 1.0f);
						glVertex3f(-.16f, .16f, -.115f);

						// Display the bottom left vertice
						glTexCoord2f(0.0f, 0.0f);
						glVertex3f(-.16f, -.16f, -.115f);

						// Display the bottom right vertice
						glTexCoord2f(1.0f, 0.0f);
						glVertex3f(.16f, -.16f, -.115f);

						// Display the top right vertice
						glTexCoord2f(1.0f, 1.0f);
						glVertex3f(.16f, .16f, -.115f);

					// Stop drawing QUADS
					glEnd();
					glDisable(GL_BLEND);											
					glEnable(GL_LIGHTING);	 
					glDepthMask(true);
				}

				// Rotate and scale as necessary
				glRotatef(90, 0, 0, 1);
				glScalef(.010f, .010f, .010f);

				// Draw the cueball
				drawModel(g_3DModel[0], g_Texture[0]);
			}
		glPopMatrix();

	// End our object selection code
	glPopName();

	// If we're not aiming, move the camera, check for object selection
	if(!aiming)
	{
		// Changes the focal point ofthe camera
		if(GetAsyncKeyState('C') && !key_press['C'])
		{
			key_press['C'] = true;
			// focus on the cue ball
			if(focal_point[2] == -10.0f)
			{
				focal_point[0] = ball[0].x;
				focal_point[1] = ball[0].y;
				focal_point[2] = -9.88f;
				GLT_VECTOR3 new_forward = { focal_point[0] - camera.GetX(), 
											focal_point[1] - camera.GetY(), 
											focal_point[2] - camera.GetZ() };

				gltNormalize(new_forward);
				camera.SetForwardDirection(new_forward);
				camera.SetUpDirection(0, 0, 1);
			}
			// focus on the center of the table 
			else
			{
				focal_point[0] = 0;
				focal_point[1] = 0;
				focal_point[2] = -10.0f;
				GLT_VECTOR3 new_forward = { focal_point[0] - camera.GetX(), 
											focal_point[1] - camera.GetY(), 
											focal_point[2] - camera.GetZ() };

				gltNormalize(new_forward);
				camera.SetForwardDirection(new_forward);
				camera.SetUpDirection(0, 0, 1);
			} 
		}
		float fTime = lastframe.getElapsedTime();
		lastframe.Reset();

		float linearVelocity = 3.0f;

		GLT_VECTOR3 forward = { focal_point[0] - camera.GetX(), focal_point[1] - camera.GetY(), 
								focal_point[2] - camera.GetZ() };
		gltNormalize(forward);

/*		if(GetAsyncKeyState(VK_RBUTTON) && !key_press[VK_RBUTTON])
		{
			key_press[VK_RBUTTON] = true;
			draw_normals = !draw_normals;
		}  */

		// Move the camera up
		if(GetAsyncKeyState(VK_UP) && !disable_camera)
		{
			// Look where we need to look
			camera.SetForwardDirection(forward);

			GLT_VECTOR3 temp_right, temp_up;

			// get the camera's right vector
			gltCrossProduct(world_up, forward, temp_right);
			if(!temp_right[0] && !temp_right[1] && !temp_right[2])
				temp_right[0] = -1; 

			gltNormalize(temp_right); 
			// Get the camera's up vector
			gltCrossProduct(forward, temp_right, temp_up);
			gltNormalize(temp_up); 

			// Set the up directio
			camera.SetUpDirection(temp_up);
			// As long as we're not above the table, move us up
			if(gltGetAngleDeg(world_down, forward) > 2)
			{
				camera.MoveUp(linearVelocity * fTime);

  				GLT_VECTOR3 forward2 = { focal_point[0] - camera.GetX(), 
										 focal_point[1] - camera.GetY(), 
										 focal_point[2] - camera.GetZ() };
				gltNormalize(forward2);
				camera.SetForwardDirection(forward2);
			}
		}
		// Move the camera down
		if(GetAsyncKeyState(VK_DOWN) && !disable_camera)
		{
			// Look where we need to look
			camera.SetForwardDirection(forward);

			GLT_VECTOR3 temp_right, temp_up;

			// get the right vector
			gltCrossProduct(world_up, forward, temp_right);
			if(!temp_right[0] && !temp_right[1] && !temp_right[2])
				temp_right[0] = -1; 

			gltNormalize(temp_right); 
			// get the camera's up vector
			gltCrossProduct(forward, temp_right, temp_up);
			gltNormalize(temp_up); 

			// Set the up direction
			camera.SetUpDirection(temp_up);
			// As long as we're not under the ground, move us down
			if(gltGetAngleDeg(world_up, forward) > 70)
			{
				camera.MoveUp(-linearVelocity * fTime);
  				GLT_VECTOR3 forward2 = { focal_point[0] - camera.GetX(), 
										 focal_point[1] - camera.GetY(), 
										 focal_point[2] - camera.GetZ() };
				gltNormalize(forward2);
				camera.SetForwardDirection(forward2);
			}
		}

		// Move the camera left
		if(GetAsyncKeyState(VK_LEFT) && !disable_camera)
		{
			camera.MoveRight(linearVelocity * fTime);

			GLT_VECTOR3 forward2 = { focal_point[0] - camera.GetX(),
									focal_point[1] - camera.GetY(),
									focal_point[2] - camera.GetZ() };
			gltNormalize(forward2);
			camera.SetForwardDirection(forward2);
			camera.SetUpDirection(0, 0, 1);
		}
		// Move the camera right
		if(GetAsyncKeyState(VK_RIGHT) && !disable_camera)
		{
			camera.MoveRight(-linearVelocity * fTime);
			GLT_VECTOR3 forward2 = { focal_point[0] - camera.GetX(),
									focal_point[1] - camera.GetY(),
									focal_point[2] - camera.GetZ() };
			gltNormalize(forward2);
			camera.SetForwardDirection(forward2);
			camera.SetUpDirection(0, 0, 1);
		}

		// Zoom the camera in
		if(GetAsyncKeyState('A') && gltGetDistance(*camera.GetOrigin(), focal_point) > 1)
			camera.MoveForward(linearVelocity * fTime);
		// Zoom it out
		if(GetAsyncKeyState('Z') && gltGetDistance(*camera.GetOrigin(), focal_point) < 100)
			camera.MoveForward(-linearVelocity * fTime);

	}		
	/////////////////////////////////////////////////////////////////////////////////////////////
	// aiming code
	/////////////////////////////////////////////////////////////////////////////////////////////
	else
	{
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// Draw the cue stick
		///////////////////////////////////////////////////////////////////////////////////////////////////
		glPushMatrix();
			glTranslatef(ball[0].x, ball[0].y, -9.88f);
			glRotatef(270 + cue_angle, 0, 0, 1);
			glRotatef(5, 1, 0, 0);
			glTranslatef(0, cue_dist, 0);

			glScalef(.010f, .010f, .010f);
			drawModel(g_3DModel[STICK], g_Texture[STICK]);
		glPopMatrix();


		// Moves the aim left
		if(GetAsyncKeyState(VK_LEFT))
		{
			// Precision movement
			if(GetAsyncKeyState(VK_SHIFT))
				cue_angle += .1f;
			else
				cue_angle += 2;

			// Handle wrap around
			if(cue_angle >= 360)
				cue_angle -= 360;

			// Calculate the offset for the tip of the cue stick
			float y_diff = cue_dist * sinf(cue_angle * GLT_PI_DIV_180);
			float x_diff = cue_dist * cosf(cue_angle * GLT_PI_DIV_180);

			cue_tip[0] = x_diff + ball[0].x;
			cue_tip[1] = y_diff + ball[0].y;
		}
		// Moves the aim right
		if(GetAsyncKeyState(VK_RIGHT))
		{
			// Precision movement
			if(GetAsyncKeyState(VK_SHIFT))
				cue_angle -= .1f;
			else
				cue_angle -= 2;

			// Handle wrap around
			if(cue_angle < 0)
				cue_angle += 360;

			// Calculate the offset for the tip of the cue stick
			float y_diff = cue_dist * sinf(cue_angle * GLT_PI_DIV_180);
			float x_diff = cue_dist * cosf(cue_angle * GLT_PI_DIV_180);

			cue_tip[0] = x_diff + ball[0].x;
			cue_tip[1] = y_diff + ball[0].y;
		}
		// Decrease the power of the shot
		if(GetAsyncKeyState(VK_UP))
		{
			cue_dist > .12f	? cue_dist -= .02f : cue_dist = .12f;

			// Calculate the offset for the tip of the cue stick
			float y_diff = cue_dist * sinf(cue_angle * GLT_PI_DIV_180);
			float x_diff = cue_dist * cosf(cue_angle * GLT_PI_DIV_180);

			cue_tip[0] = x_diff + ball[0].x;
			cue_tip[1] = y_diff + ball[0].y;
		}
		// Increase the power of the shot
		if(GetAsyncKeyState(VK_DOWN))
		{
			cue_dist < 1.20f ? cue_dist += .02f : cue_dist = 1.20f;

			// Calculate the offset for the tip of the cue stick
			float y_diff = cue_dist * sinf(cue_angle * GLT_PI_DIV_180);
			float x_diff = cue_dist * cosf(cue_angle * GLT_PI_DIV_180);

			cue_tip[0] = x_diff + ball[0].x;
			cue_tip[1] = y_diff + ball[0].y;
		}
		// Handle the left mouse click
		if(GetAsyncKeyState(VK_LBUTTON) && !key_press[VK_LBUTTON])
		{
			// The Rect which defines our window
			RECT rClient = { 0, };
			GetClientRect(hWnd, &rClient);

			// Offset for drawing in windowed mode
			float hor_var = float(rClient.right) / 1024;
			float ver_var = float(rClient.bottom) / 768;

			// The position of the cursor
			POINT cursor_pos = { 0, 0 };
			GetCursorPos(&cursor_pos);
			// Converted for windowed mode
			ScreenToClient(hWnd, &cursor_pos);

			// How far from the center of the picture of the ball we clicked
			float temp_dist = pow(cursor_pos.x - (165 * hor_var), 2) + pow(cursor_pos.y - (55 * ver_var), 2);
			
			// If it's less than 45 pixels, change the english
			if(temp_dist < (2025 * pow(hor_var, 2)))
			{
				// If it's within the red circle, just se tthe dot to that spot...
				if(temp_dist < (576 * pow(hor_var, 2)))
				{
					spot_x = cursor_pos.x;
					spot_y = cursor_pos.y;
				}
				// Otherwise interpolate where it would fall within the red circle
				else
				{
					spot_x = (165 * hor_var) + ((cursor_pos.x - (165 * hor_var)) * 24 * hor_var / sqrtf(temp_dist));
					spot_y = (55 * ver_var) + ((cursor_pos.y - (55 * ver_var)) * 24 * ver_var / sqrtf(temp_dist));
				}
				// Set the variables which hold the english based on the position of the blue dot
				x_spin = spot_x - (165 * hor_var);
				y_spin = (55 * ver_var) - spot_y;
			}
			// It's the distance is greater than 45 pixels, fire the shot
			else
			{
				key_press[VK_LBUTTON] = true;
				// End the aiming phase and begin the shooting phase
				aiming = false;
				shooting = true;

				// Set the cueball's velocity based on the distance of the stick's tip
				ball[0].velocity = (cue_dist - .12f) * .2f;

				// Set the cueball's vector of travel based on the stick's tip
				ball[0].vec[0] = ball[0].x - cue_tip[0];
				ball[0].vec[1] = ball[0].y - cue_tip[1];

				gltNormalize(ball[0].vec);

				ball[0].evec[0] = ball[0].vec[0];
				ball[0].evec[1] = ball[0].vec[1];

				ball[0].vec[0] *= ball[0].velocity;
				ball[0].vec[1] *= ball[0].velocity;

				// Appl ythe english to the cueball
				ball[0].spin[0] = x_spin / 150;
				ball[0].spin[1] = (y_spin / 400) * cue_dist / 1.2f;
			}

		}
		// Cancel aiming mode if the right button is clicked
		if(GetAsyncKeyState(VK_RBUTTON) && !key_press[VK_RBUTTON])
		{
			key_press[VK_RBUTTON] = true;
			aiming = false;
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////
		// Prediction code
		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		// Holds our first possible collision
		GLT_POINT2 first_point = { 0, };

		// The angle of our shot
		float cue_angle2 = 0;

		(cue_angle >= 180 && cue_angle <= 360) ? cue_angle2 = cue_angle - 180 : cue_angle2 = cue_angle + 180;

		// Flag which is obviously going to be true if a collision with another ball is found
		bool col_detected = false;
		// Holds the number of the ball with which a collision was detected
		int which_ball = 0;
		// Will hold the distance of the closest collision
		float closest_col = 1000.0f;

		// Check every ball
		for(int i = 1; i < 16; ++i)
		{
			// Only check if it hasn't been pocketed
			if(!ball[i].pocketed)
			{
				// Create a vector from the center of the cueball to the center of the object ball
				GLT_VECTOR3 vec_to_center = { ball[i].x - ball[0].x, ball[i].y - ball[0].y, 0 };
				// The vector we're checking collision on
				GLT_VECTOR3 actual_vec = { cosf(cue_angle2 * GLT_PI_DIV_180), sinf(cue_angle2 * GLT_PI_DIV_180), 0 };

				// Find the length of the first vector we made and the normalize it
				float dist_to_center = sqrtf(powf(vec_to_center[0], 2) + powf(vec_to_center[1], 2));
				gltNormalize(vec_to_center);

				// Calculate the angle between the two vectors
				float var_angle = acosf(gltDotProduct(vec_to_center, actual_vec));

				// Only continue if our angle is such that a collision is possible
				if(var_angle <= 90 * GLT_PI_DIV_180)
				{
					// Find distance between the center of the object and our actual vector 
					float dist_to_vector = dist_to_center * tanf(var_angle);

					// If that distance is less than twice the radius of the ball, then if the 
					// cueball were to travel in that direction, it would eventually collide with 
					// the object ball
					if(dist_to_vector <= radius * 2)
					{
						// Houston, we have a collision. Now we need to find the actual point
						// I've used all new varialbes here to make the algorithm clearer.  This is 
						// a surprisingly complicated procedure involving the quadric formula
						col_detected = true;

						// The vector we're checking against
						GLT_VECTOR3 rKD = { cosf(cue_angle2 * GLT_PI_DIV_180), sinf(cue_angle2 * GLT_PI_DIV_180), 0 };
						
						// The vector defined by the center of the 2 spheres
						GLT_VECTOR3 kDiff = { ball[0].x - ball[i].x, ball[0].y - ball[i].y, 0 };

						// The squared distance between the 2 balls minus the diameter squared
						float fA0 = (kDiff[0] * kDiff[0] + kDiff[1] * kDiff[1]) - powf(radius * 2, 2);
						// the dot product between the 2 vectors
						float fA1 = gltDotProduct(rKD, kDiff);

						// This is in effect the part of the quadratic formula which is written
						// as b^2 - 4ac
						float fDiscr = fA1 * fA1 - fA0;

						// This will hold the distance along rKD at the point of collision
						float afT[2] = { 1000, 1000 };
						
						// Two possible answers, due to the nature of the quadratic formula
						// and due to the fact that there will be 2 points of collision in most
						// instances
						if ( fDiscr > 0.0f )
						{
							fDiscr = sqrtf(fDiscr);
							afT[0] = (-fA1 - fDiscr);
							afT[1] = (-fA1 + fDiscr);
						}
						else if(fDiscr == 0.0f)
						{
							afT[0] = -fA1;
						}

						// Whichever value is smaller is the one we want
						if(afT[1] < afT[0])
							afT[0] = afT[1];

						// If this distance is less than any we've calculated beforehand...
						if(afT[0] < closest_col)
						{
							// ...Set this ball as the predicted collision
							predicted_ball = i;
							// ...Set this distance as the closest collision found...
							closest_col = afT[0];
							// ...and set up our transparent cueball.
							col.x = ball[0].x + afT[0] * cosf(cue_angle2 * GLT_PI_DIV_180);
							col.y = ball[0].y + afT[0] * sinf(cue_angle2 * GLT_PI_DIV_180);

							// If our transparent cueball falls outside the table though,
							// scrap this collision
							if(col.x > 4.38 || col.x < -4.38 || col.y > 2.15 || col.y < -2.05)
								col_detected = false;
							which_ball = i;
						}
					}
				}
			}
		}

		// In the event where no collision was detected between our potential vector of travel
		// and another ball, then calcualte the point of collision on the rail
		if(!col_detected)
		{
			predicted_ball = 0;

			// Vector is facing straight up or down, no calculations needed
			if(int(cue_angle2 * 1000) / 1000.0f == 0.0f || int(cue_angle2 * 1000) / 1000.0f == 180.0f)
			{
				col.y = ball[0].y;
				!(int(cue_angle2 * 1000) / 1000.0f) ? col.x = 4.50f - radius : col.x = -4.50f + radius;
			} 
			// Vector is facing straight left or right, no calculations needed
			else if(int(cue_angle2 * 1000) / 1000.0f == 90.0f || int(cue_angle2 * 1000) / 1000.0f == 270.0f)
			{
				col.x = ball[0].x;
				int(cue_angle2 * 1000) / 1000.0f == 90.0f ? col.y = 2.27f - radius : col.y = -2.17f + radius;
			} 
			// Any other case	
			else
			{
				float x_wall, y_wall;

				// figure out whether we'll be collidiing with the left or right wall
				(cosf(cue_angle2 * GLT_PI_DIV_180) > 0) ? x_wall = 4.50f : x_wall = -4.50f;
				// figure out whether we'll be collidiing with the top or bottom wall
				(sinf(cue_angle2 * GLT_PI_DIV_180) > 0) ? y_wall = 2.27f : y_wall = -2.17f;
				
				// Temp varialbe to figure out the possible point of collision with an
				// arbitrary rail
				first_point[1] = (x_wall - ball[0].x) * tanf(cue_angle2 * GLT_PI_DIV_180);
				
				// Check to see if that collision occurs within the bounds of the table
				if(((y_wall == 2.27f) ? (first_point[1] + ball[0].y <= y_wall) :
										(first_point[1] + ball[0].y >= y_wall)))
				{	
					// This is the initial collision point, center of the ball to the rail
					col.y = first_point[1] + ball[0].y;
					col.x = x_wall;

					// Offset the point so that the edge of the ball collides with the rail
					float x_dist = (float)fabs(col.x - ball[0].x);   
					float y_dist = (float)fabs(col.y - ball[0].y);

					float y_var = radius * y_dist / x_dist;

					col.y > ball[0].y ? col.y -= y_var : col.y += y_var;

					col.x > 0 ? col.x -= radius : col.x += radius;	
				}

				// If that collision was invlaid, it must then collide with the other rail
				else
				{
					// This is the initial collision point, center of the ball to the rail
					col.y = y_wall;
					col.x = (y_wall - ball[0].y) / tanf(GLT_PI_DIV_180 * cue_angle2) + ball[0].x; 

					// Offset the point so that the edge of the ball collides with the rail
					float x_dist = (float)fabs(col.x - ball[0].x);   
					float y_dist = (float)fabs(col.y - ball[0].y);

					float x_var = radius * x_dist / y_dist;

					col.x > ball[0].x ? col.x -= x_var : col.x += x_var;

					col.y > 0 ? col.y -= radius : col.y += radius;	 
				}
			}
		}	

		///////////////////////////////////////////////////////////////////////////////////////////////////
		// Draw our transparent predicted ball
		///////////////////////////////////////////////////////////////////////////////////////////////////
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColor4f(1, 1, 1, .2f);
		glPushMatrix();
			glTranslatef(col.x, col.y, -9.88f);
			DrawSphere(.12f);
		glPopMatrix();


		// If a collision between 2 balls was predicted, calculate the trajectories of the 2 balls
		// after the collision
		if(col_detected)
		{
			// The path of the object ball
			GLT_VECTOR3 obj_path = { ball[which_ball].x - col.x, ball[which_ball].y - col.y, 0 };
			
			gltNormalize(obj_path);
			 
			// will hold the path of the cueball
			GLT_VECTOR3 norm = { 0, };
			GLT_VECTOR3 cue_to_col = { col.x - ball[0].x, col.y - ball[0].y, 0 };
			gltNormalize(cue_to_col);

			// Calcualte the path of the cueball
			gltCrossProduct(world_up, obj_path, norm);

			// Make sure we're not facing the wrong way
			if(acosf(gltDotProduct(cue_to_col, norm)) > 90 * GLT_PI_DIV_180)
			{
				norm[0] *= -1;
				norm[1] *= -1;
			}
			
			///////////////////////////////////////////////////////////////////////////////////////////////////
			// Draw our blue and yellow lines which predict the directions of travel of the balls
			///////////////////////////////////////////////////////////////////////////////////////////////////
			glBegin(GL_LINES);
			glColor4f(1, 1, 0, 1);
				glVertex3f(ball[which_ball].x, ball[which_ball].y, -9.88f);
			glColor4f(1, 1, 0, 0);
				glVertex3f(ball[which_ball].x + 2 * obj_path[0], ball[which_ball].y + 2 * obj_path[1], -9.88f); 

			glColor4f(0, 0, 1, 1);
				glVertex3f(col.x, col.y, -9.88f);
			glColor4f(0, 0, 1, 0);
				glVertex3f(col.x + 2 * norm[0], col.y + 2 * norm[1], -9.88f);
			glEnd();
		}


		///////////////////////////////////////////////////////////////////////////////////////////////////
		// Draw our green line between the cueball and the predicted point of collision
		///////////////////////////////////////////////////////////////////////////////////////////////////
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1, 1000);
		glBegin(GL_LINES);
			glColor4f(0, 1, 0, 1);
			glVertex3f(ball[0].x, ball[0].y, -9.88f);

			glColor4f(0, 1, 0, .2f);
			glVertex3f(col.x, col.y, -9.88f); 
		glEnd();
		glDisable(GL_LINE_STIPPLE);
		glDisable(GL_BLEND);

		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
			 
		
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Shooting code
	/////////////////////////////////////////////////////////////////////////////////////////////////
	if(shooting)
	{
		// Will end up false if there are no more balls moving
		bool done = true;

		// Loop through each ball and move it
		for(int i = 0; i < 16; ++i)
		{
			// Only if the ball hasn't been pocketed
			if(!ball[i].pocketed)
			{
				// SLow down due to friction
				(ball[i].velocity > 0) ? (ball[i].velocity -= .0005f) : (ball[i].velocity = 0);
				gltNormalize(ball[i].vec);


				GLT_VECTOR3 temp_vec;
				memcpy(temp_vec, ball[i].vec, sizeof(float) * 3);
				
				ball[i].vec[0] *= ball[i].velocity;
				ball[i].vec[1] *= ball[i].velocity;
				
				// Do some english
				if(!i)
				{
					if(apply_english)
					{
						// Reduction of english due to friction
						if(ball[0].spin[1] > .003)
							ball[0].spin[1] -= .003f;
						else if(ball[0].spin[1] < -.003)
							ball[0].spin[1] += .003f; 
						else
							ball[0].spin[1] = 0;
					}
					else
					{
						// Reduction of english due to friction
						if(ball[0].spin[1] > .0005)
							ball[0].spin[1] -= .0005f;
						else if(ball[0].spin[1] < -.0005)
							ball[0].spin[1] += .0005f; 
						else
							ball[0].spin[1] = 0;
					}

					// Apply the english
					if(ball[0].spin[1] && apply_english)
					{

						ball[0].vec[0] += (ball[0].evec[0] * ball[0].spin[1] * .24f);
						ball[0].vec[1] += (ball[0].evec[1] * ball[0].spin[1] * .24f);

						ball[0].velocity = sqrtf(powf(ball[0].vec[0], 2) + powf(ball[0].vec[1], 2));

					} 
				}

				// Move the ball
				ball[i].x += ball[i].vec[0];
				ball[i].y += ball[i].vec[1];
				

				////////////////////////////////////////////////////////////////////////////////////
				// Ball to bumper collision
				////////////////////////////////////////////////////////////////////////////////////

				// Collision with short bumpers
				if((ball[i].vec[0] > 0 && ball[i].x > (4.38 - (ball[i].velocity / 2) * abs(temp_vec[0]))) ||
				   (ball[i].vec[0] < 0 && ball[i].x < (-4.38 + (ball[i].velocity / 2) * abs(temp_vec[0]))))
				{

					// If we're looking at the cueball, apply the english
					if(i == 0)
					{
						ball[i].x > 0 ? ball[0].vec[1] -= (ball[0].spin[0] * ball[0].velocity / .216f)
									  : ball[0].vec[1] += (ball[0].spin[0] * ball[0].velocity / .216f);

						ball[0].spin[0] /= 2;
						ball[0].spin[1] = 0;
						apply_english = false;
					}

					// Put the ball in the pocket
					if(ball[i].y > 2 || ball[i].y < -1.9)
					{
						ball[i].pocketed = true;
						ball[i].velocity = 0;
					}
					// Otherwise Bounce it off
					else
					{
						ball[i].vec[0] *= -1;
						ball[i].velocity *= .85f;

						ball[i].nvec[0] = -ball[i].vec[1];
						ball[i].nvec[1] = ball[i].vec[0];
						gltNormalize(ball[i].nvec);
					}
				}	
				// Collision with long bumpers
				if((ball[i].vec[1] > 0 && ball[i].y > (2.15 - (ball[i].velocity / 2) * abs(temp_vec[1]))) ||
				   (ball[i].vec[1] < 0 && ball[i].y < (-2.05 + (ball[i].velocity / 2) * abs(temp_vec[1]))))
				{
					// If we're looking at the cueball, apply the english
					if(i == 0)
					{
						ball[i].y > 0 ? ball[0].vec[0] += (ball[0].spin[0] * ball[0].velocity / .216f)
									  : ball[0].vec[0] -= (ball[0].spin[0] * ball[0].velocity / .216f);

						ball[0].spin[0] /= 2;
						ball[0].spin[1] = 0;
						apply_english = false;
					}
					// Put the ball in the pocket
					if(ball[i].x > 4.2 || ball[i].x < -4.2 || (ball[i].x > -.24 && ball[i].x < .24))
					{
						ball[i].pocketed = true;
						ball[i].velocity = 0;
					}
					// Otherwise Bounce it off
					else
					{
						ball[i].vec[1] *= -1;
						ball[i].velocity *= .85f;

						ball[i].nvec[0] = -ball[i].vec[1];
						ball[i].nvec[1] = ball[i].vec[0];
						gltNormalize(ball[i].nvec);
					}
				}
				////////////////////////////////////////////////////////////////////////////////////
				// Ball to ball collision
				////////////////////////////////////////////////////////////////////////////////////
				for(int j = i + 1; j < 16; ++j)
				{
					if(!ball[j].pocketed)
					{
						if(ball[i].collision(ball[j]) && !invalid_collision[i][j])
						{
							// Allow top or bottom english to affect the cueball
							if(!i)
							{
								apply_english = true;
							}

							invalid_collision[i][j] = invalid_collision[j][i] = 1;

							GLT_VECTOR3 intersect = { 0, };
							// Calculate the Unit length vector defined by the centers of the 2 balls
							// this is a special case where the cueball is colliding with the
							// ball which was predicted before the the shot was taken.  In this
							// we apply pixel perfect collision
							if(i == 0 && j == predicted_ball)
							{
								intersect[0] = ball[j].x - col.x;
								intersect[1] = ball[j].y - col.y;
								predicted_ball = 0;
								ball[0].x = col.x;
								ball[0].y = col.y;
							}
							// Otherwise proceed as normal
							else
							{ 
								intersect[0] = ball[j].x - ball[i].x;
								intersect[1] = ball[j].y - ball[i].y;
							}
							
							gltNormalize(intersect);		  
							
							// Small optimization, no need to calculate vectors and what-not if the
							// ball isn't moving
							bool b1_moving = false;
							bool b2_moving = false;

							if(ball[i].vec[0] || ball[i].vec[1])
								b1_moving = true;
							if(ball[j].vec[0] || ball[j].vec[1])
								b2_moving = true;


							// Unify the forward vectors of the 2 balls in question
							if(b1_moving)
								gltNormalize(ball[i].vec);
							if(b2_moving)
								gltNormalize(ball[j].vec);

							if(ball[i].vec[0] > .95f && fabs(ball[i].vec[1]) < .05f)
								bool what_the_fuck = true;
							// Calculate the angle between the balls and the vector of collision
							float angle1 = 0, angle2 = 0; 
							if(b1_moving)
								angle1 = acosf(gltDotProduct(ball[i].vec, intersect));
							if(b2_moving)
								angle2 = acosf(fabs(gltDotProduct(ball[j].vec, intersect)));

							// This will only occur in the event that this is a collision which
							// is invalid and a result of a previous collision not being completely
							// resolved from the last frame.  This collision will be ignored
//								if(angle1 > (90 * GLT_PI_DIV_180) && angle1 < 270 * GLT_PI_DIV_180)
//									continue;
							
							if(i == 0)
								started = true;
							// These variables hold the components of the respective ball's vector.
							// comp1 will hold the component transferred to the owning ball and
							// comp2 will hold the component transferred to the colliding ball.
							float b1_comp1 = 0, b1_comp2 = 0, b2_comp1 = 0, b2_comp2 =0;

							// Calculate the components of ball1 (defined by [i])
							if(b1_moving)
							{
								b1_comp1 = sinf(angle1) * ball[i].velocity;	
								b1_comp2 = cosf(angle1) * ball[i].velocity;	
							} 
							// Calculate the components of ball2 (defined by [j])
							if(b2_moving)
							{
								b2_comp1 = sinf(angle2) * ball[j].velocity;	
								b2_comp2 = cosf(angle2) * ball[j].velocity;	
							}
							 
							// Calculate the vector which is perpendicular to the vector of collision
							GLT_VECTOR3 norm_intersect = { 0, };
							gltCrossProduct(world_up, intersect, norm_intersect);

							// These are the resulant component vectors of the ball's travel vector
							GLT_VECTOR3 b1_vcomp1 = {0, };
							GLT_VECTOR3 b1_vcomp2 = {0, };
							GLT_VECTOR3 b2_vcomp1 = {0, };
							GLT_VECTOR3 b2_vcomp2 = {0, };
							
							// Calculate the resultant vector of ball1 ([i])
							if(gltGetAngleDeg(ball[i].vec, norm_intersect) < 90)
							{
								b1_vcomp1[0] = norm_intersect[0] * b1_comp1;
								b1_vcomp1[1] = norm_intersect[1] * b1_comp1;
							}
							else
							{
								b1_vcomp1[0] = -norm_intersect[0] * b1_comp1;
								b1_vcomp1[1] = -norm_intersect[1] * b1_comp1;
							}
							b1_vcomp2[0] = -intersect[0] * b2_comp2;
							b1_vcomp2[1] = -intersect[1] * b2_comp2;

							ball[i].vec[0] = b1_vcomp1[0] + b1_vcomp2[0];
							ball[i].vec[1] = b1_vcomp1[1] + b1_vcomp2[1];

							ball[i].velocity = sqrtf(ball[i].vec[0] * ball[i].vec[0] + ball[i].vec[1] * ball[i].vec[1]);

							// Calculate the resultant vector of ball2 ([j])
							if(gltGetAngleDeg(ball[j].vec, norm_intersect) < 90)
							{
								b2_vcomp1[0] = norm_intersect[0] * b2_comp1;
								b2_vcomp1[1] = norm_intersect[1] * b2_comp1;
							}
							else
							{
								b2_vcomp1[0] = -norm_intersect[0] * b2_comp1;
								b2_vcomp1[1] = -norm_intersect[1] * b2_comp1;
							}
							b2_vcomp2[0] = intersect[0] * b1_comp2;
							b2_vcomp2[1] = intersect[1] * b1_comp2;

							// Finally we sum up and each balls respective vector and assign it
							// to the ball
							ball[j].vec[0] = b2_vcomp1[0] + b2_vcomp2[0];
							ball[j].vec[1] = b2_vcomp1[1] + b2_vcomp2[1];
							ball[j].velocity = sqrtf(ball[j].vec[0] * ball[j].vec[0] + ball[j].vec[1] * ball[j].vec[1]);

							// Update the vector perpendicular to our forward vector for
							// purposes of spinning the balls
							ball[i].nvec[0] = -ball[i].vec[1];
							ball[i].nvec[1] = ball[i].vec[0];
							ball[j].nvec[0] = -ball[j].vec[1];
							ball[j].nvec[1] = ball[j].vec[0];
							gltNormalize(ball[i].nvec);
							gltNormalize(ball[j].nvec);

//							soundPlayer.playSample(collision);
						}
						// Small buffer to correct some minor collision glitches
						else
						{
							invalid_collision[i][j] = invalid_collision[j][i] = 0;
						}
					}
				}
			}
		}
		if(started)
		{
			if(first_shot)
			{
				ball[1].velocity = 0;
				ball[1].vec[0] = 0; 
				ball[1].vec[1] = 0;
			}
			first_shot = false;
		}

		// Found out the hard way that this check could not be done inside the preceding for-loop.
		// In an instance where only one ball was moving and it collided with a ball of lower
		// index number in such way that it transferred all velocity to the object ball, the 
		// game would think that the shooting phase was over.
		for(i = 0; i < 16; ++i)
		{	
			if(ball[i].velocity > 0)
				done = false;
		}

		// If the cueball has scratched, reset it's position
		if(done)
		{
			if(ball[0].pocketed)
			{
				ball[0].x = -2.25f;
				ball[0].y = 0;
				ball[0].pocketed = false;
			}
			shooting = false;
			ball[0].spin[0] = 0;
			ball[0].spin[1] = 0;
			apply_english = false;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	// Rendering the GUI
	///////////////////////////////////////////////////////////////////////////////////////////////
	RECT rClient = { 0, };
	GetClientRect(hWnd, &rClient);
	float hor_var = float(rClient.right) / 1024;
	float ver_var = float(rClient.bottom) / 768;

	if(true_render)
	{
		OrthoMode(rClient.left, rClient.top, rClient.right, rClient.bottom);

		glBindTexture(GL_TEXTURE_2D, t_Texture[1]);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Draw the 2D cueball at the top-left of the screen
		glBegin(GL_QUADS);
			glColor4f(1, 1, 1, 1);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(120 * hor_var, 10 * ver_var);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(120 * hor_var, 100 * ver_var);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(210 * hor_var, 100 * ver_var);
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(210 * hor_var, 10 * ver_var);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, t_Texture[3]);
		// Draw the little blue dot
		glBegin(GL_QUADS);
			glColor4f(1, 1, 1, 1);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f((spot_x - 5), (spot_y - 5));
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f((spot_x - 5), (spot_y + 5));
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f((spot_x + 5), (spot_y + 5));
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f((spot_x + 5), (spot_y - 5));
		glEnd();

		glBindTexture(GL_TEXTURE_2D, t_Texture[2]);

		float power = (cue_dist - .12f) / 1.08f;

		// Draw the power meter
		glBegin(GL_QUADS);
			glColor4f(1, 1, 1, 1);

			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(700 * hor_var, 30 * ver_var);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(700 * hor_var, 70 * ver_var);
			glTexCoord2f(power, 0.0f);
			glVertex2f((1000 - (300 * (1- power))) * hor_var, 70 * ver_var);
			glTexCoord2f(power, 1.0f);
			glVertex2f((1000  - (300 * (1- power))) * hor_var, 30 * ver_var);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, t_Texture[4]);
		// Draw the border encasing the power meter
		glBegin(GL_QUADS);
			glColor4f(1, 1, 1, 1);

			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(700 * hor_var, 30 * ver_var);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(700 * hor_var, 70 * ver_var);
			glTexCoord2f(.99f, 0.0f);
			glVertex2f(1000 * hor_var, 70 * ver_var);
			glTexCoord2f(.99f, 1.0f);
			glVertex2f(1000 * hor_var, 30 * ver_var);
		glEnd();
		glDisable(GL_BLEND);											
		glEnable(GL_LIGHTING);	 
		glEnable(GL_DEPTH_TEST);

		PerspectiveMode();
	}


glPopMatrix();

	// Here we pass in the cursor's X and Y coordinates to test for an object under the mouse.
	// This checks to see if we've clicked on the cueball
	if(GetAsyncKeyState(VK_LBUTTON) && !key_press[VK_LBUTTON] && !aiming && !shooting)
	{
		POINT cursor_pos = { 0, 0 };

		GetCursorPos(&cursor_pos);
		ScreenToClient(hWnd, &cursor_pos);
		float temp_dist = pow(cursor_pos.x - (165 * hor_var), 2) + pow(cursor_pos.y - (55 * ver_var), 2);
		if(temp_dist < (2025 * pow(hor_var, 2)))
		{
			if(temp_dist < (576 * pow(hor_var, 2)))
			{
				spot_x = cursor_pos.x;
				spot_y = cursor_pos.y;
			}
			else
			{
				spot_x = (165 * hor_var) + ((cursor_pos.x - (165 * hor_var)) * 24 * hor_var / sqrtf(temp_dist));
				spot_y = (55 * ver_var) + ((cursor_pos.y - (55 * ver_var)) * 24 * ver_var / sqrtf(temp_dist));
			}
			x_spin = spot_x - (165 * hor_var);
			y_spin = (55 * ver_var) - spot_y;
		}
		else
		{
			key_press[VK_LBUTTON] = true;
			
			objectID = RetrieveObjectID(cursor_pos.x, cursor_pos.y);

			// Now we just do a switch on our object ID's to see if we hit one.
			// Check the objectID passed back
			if(objectID == CUEBALL)								
			{
				cue_dist = .12f;
				cue_tip[0] = ball[0].x - cue_dist;
				cue_tip[1] = ball[0].y;
				cue_tip[2] = -9.88f;
				cue_angle = 180;
				aiming = true;
			}
		}
	}


/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

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
	// Fix for a minor camera bug
	if(disable_camera && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_DOWN)
	   && !GetAsyncKeyState(VK_LEFT)&& !GetAsyncKeyState(VK_RIGHT))
	{
		disable_camera = false;
	} 
	
	// Limit to 33 FPS
	while(GetTickCount() - start_time < 30) { } 

	return TRUE;	  

}
GLvoid OGL_Wrapper::InitGame(GLvoid)
{
	srand((unsigned int)time(0));
	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_LINE_SMOOTH);

	soundPlayer.init(hWnd);

	collision = soundPlayer.loadSample("Shoot.wav");

	camera.RotateLocalY(180.0f);
	camera.SetOrigin(0.0f, 0.0f, 0.0f); 

///////////////////////////////////////////////////////////////////////////////////////////////
// Intro screen
///////////////////////////////////////////////////////////////////////////////////////////////
		CreateTargaTexture(t_Texture, "intro.tga", 7);
		RECT rW = { 0, };
		GetClientRect(hWnd, &rW);
		OrthoMode(rW.left, rW.top, rW.right, rW.bottom);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, t_Texture[7]);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Draw the ...Loading splash screen
		glBegin(GL_QUADS);
			glColor4f(1, 1, 1, 1);
			glTexCoord2f(0.0f, 1.0f);
			glVertex2f(rW.left, rW.top);
			glTexCoord2f(0.0f, 0.0f);
			glVertex2f(rW.left, rW.bottom);
			glTexCoord2f(1.0f, 0.0f);
			glVertex2f(rW.right, rW.bottom);
			glTexCoord2f(1.0f, 1.0f);
			glVertex2f(rW.right, rW.top);
		glEnd();
		PerspectiveMode();
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);

		SwapBuffers(hDC);		// Swap Buffers
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
	for(int j = 0; j < NUM_OBJECTS; ++j)
	{
		g_Load3ds[j].Import3DS(&(g_3DModel[j]), file_name[j]);			// Load our .3DS file into our model structure
		// Go through all the materials
		for(int i = 0; i < g_3DModel[j].numOfMaterials; i++)
		{
			// Check to see if there is a file name to load in this material
			if(strlen(g_3DModel[j].pMaterials[i].strFile) > 0)
			{
				// Use the name of the texture file to load the bitmap, with a texture ID (i).
				// We pass in our global texture array, the name of the texture, and an ID to reference it.	
				CreateTexture(g_Texture[j], g_3DModel[j].pMaterials[i].strFile, i);			
			}

			// Set the texture ID for this material
			g_3DModel[j].pMaterials[i].texureId = i;
		}
	}

	// Loading all of our targa textures
	CreateTargaTexture(t_Texture, "shadow.tga", 0);
	CreateTargaTexture(t_Texture, "cue_ball.tga", 1);
	CreateTargaTexture(t_Texture, "power.tga", 2);
	CreateTargaTexture(t_Texture, "spot.tga", 3);
	CreateTargaTexture(t_Texture, "border.tga", 4);
	CreateTargaTexture(t_Texture, "floor5.tga", 5);
	CreateTargaTexture(t_Texture, "wall4.tga", 6);
	CreateTargaTexture(t_Texture, "intro.tga", 7);
	CreateTargaTexture(t_Texture, "wall5.tga", 8);
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

	radius = .12f;
/////////////////////////////////////////////////////////////////////////////////
	ball[0].setXY(-2.25f, 0);

	int index = 1;
	int y_offset = 0;
	float x_offset = 2.0f * radius * cosf(PI * 30.0f / 180.0f);
	
	// Sets our balls up in the rack
	for(int i = 0; i < 5; ++i)
	{
		y_offset = i;
		for(int j = 0; j < i + 1; ++j)
		{
			ball[index].y = y_offset * radius;
			y_offset -= 2;
			ball[index].x = i * x_offset + 2.25f;
			ball[index].rad = radius;
			ball[index].number = index;
			++index;
		}
	}
	// Put the 8 ball in the center
	ball[5].Swap(ball[8]);

	// Shuffle all the balls but the 1 and the 8 balls
	for(i = 1; i < 16; ++i)
	{
		int random = rand() % (15 - i + 1) + i;
		if(ball[i].getNumber() != 1 && ball[i].getNumber() != 8 && 
		   ball[random].getNumber() != 1 && ball[random].getNumber() != 8)
		{
			ball[i].Swap(ball[random]);
		}
	} 

/////////////////////////////////////////////////////////////////////////////////

}
GLvoid OGL_Wrapper::ShutdownGame()
{
	// When we are done, we need to free all the model data
	// We do this by walking through all the objects and freeing their information
	for(int i = 0; i < NUM_OBJECTS; ++i)
	{
		for(int j = 0; j < g_3DModel[i].numOfObjects; j++)
		{
			// Free the faces, normals, vertices, and texture coordinates.
			delete [] g_3DModel[i].pObject[j].pFaces;
			delete [] g_3DModel[i].pObject[j].pNormals;
			delete [] g_3DModel[i].pObject[j].pVerts;
			delete [] g_3DModel[i].pObject[j].pTexVerts;
		}
	}
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

//	InitGame();


	if(!firstLoad)
	{
		for(int k = 0; k < NUM_OBJECTS; ++k)
		{
			for(int i = 0; i < g_3DModel[k].numOfMaterials; i++)
			{
				// Check to see if there is a file name to load in this material
				if(strlen(g_3DModel[k].pMaterials[i].strFile) > 0)
				{
					// Use the name of the texture file to load the bitmap, with a texture ID (i).
					// We pass in our global texture array, the name of the texture, and an ID to reference it.	
					CreateTexture(g_Texture[k], g_3DModel[k].pMaterials[i].strFile, i);			
				}

				// Set the texture ID for this material
				g_3DModel[k].pMaterials[i].texureId = i;
			}
		}	
		CreateTargaTexture(t_Texture, "shadow.tga", 0);
		CreateTargaTexture(t_Texture, "cue_ball.tga", 1);
		CreateTargaTexture(t_Texture, "power.tga", 2);
		CreateTargaTexture(t_Texture, "spot.tga", 3);
		CreateTargaTexture(t_Texture, "border.tga", 4);
		CreateTargaTexture(t_Texture, "floor5.tga", 5);
		CreateTargaTexture(t_Texture, "wall4.tga", 6);
		CreateTargaTexture(t_Texture, "intro.tga", 7);
		CreateTargaTexture(t_Texture, "wall5.tga", 8);
	}

	return TRUE;
}


// resize and initialize our GL window
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
	HCURSOR cursor = (HCURSOR)LoadImage(NULL, "3dwarro.cur", IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);		


	hInstance			= GetModuleHandle(NULL);			// Grab An Instance For Our Window
	wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Move, And Own DC For Window
	wc.lpfnWndProc		= (WNDPROC) WndProc;				// WndProc Handles Messages
	wc.cbClsExtra		= 0;								// No Extra Window Data
	wc.cbWndExtra		= 0;								// No Extra Window Data
	wc.hInstance		= hInstance;						// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);		// Load The Default Icon
	wc.hCursor			= cursor;  	// Load The Arrow Pointer
	wc.hbrBackground	= NULL;								// No Background Required For GL
	wc.lpszMenuName		= NULL;								// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";							// Set The Class Name

	RegisterClass(&wc);										// Register our window
															
	if (fullscreen)								// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;			// Window Extended Style
		dwStyle = WS_POPUP;						// Windows Style
//		ShowCursor(FALSE);						// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;					// Windows Style
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


int OGL_Wrapper::RetrieveObjectID(int x, int y)
{
	int objectsFound = 0;							// This will hold the amount of objects clicked
	int	viewportCoords[4] = {0};					// We need an array to hold our view port coordinates
	GetClientRect(hWnd, &g_rRect);					// Get the window rectangle

	// The ID's of the objects we click on.
	unsigned int selectBuffer[32] = {0};				
														
	// Register our selection buffer
	glSelectBuffer(32, selectBuffer);					// Setup our selection buffer to accept object ID's

	// This function returns information about many things in OpenGL.  We pass in GL_VIEWPORT
	// to get the view port coordinates.  It saves it like a RECT with {top, left, bottom, right}
	glGetIntegerv(GL_VIEWPORT, viewportCoords);			

	// Now we want to get out of our GL_MODELVIEW matrix and start effecting our
	// GL_PROJECTION matrix.  This allows us to check our X and Y coords against 3D space.

	glMatrixMode(GL_PROJECTION);						// We want to now effect our projection matrix
	
	glPushMatrix();										// We push on a new matrix so we don't effect our 3D projection

		glRenderMode(GL_SELECT);						// Allows us to render the objects, but not change the frame buffer

		glLoadIdentity();								// Reset our projection matrix

		// Create a projection matrix that is around our cursor.
		gluPickMatrix(x, viewportCoords[3] - y, 2, 2, viewportCoords);

		// Next, we just call our normal gluPerspective() function, exactly as we did on startup.
		// This is to multiply the perspective matrix by the pick matrix we created up above. 
		gluPerspective(45.0f,(float)g_rRect.right/(float)g_rRect.bottom, 0.1f, 100.0f);
		
		glMatrixMode(GL_MODELVIEW);						// Go back into our model view matrix
	
		DrawGLScene(false);

		objectsFound = glRenderMode(GL_RENDER);			// Return to render mode and get the number of objects found

		glMatrixMode(GL_PROJECTION);					// Put our projection matrix back to normal.
	glPopMatrix();										// Stop effecting our projection matrix

	glMatrixMode(GL_MODELVIEW);							// Go back to our normal model view matrix

	if (objectsFound > 0)
	{		
		// Set the lowest depth to the first object to start it off.
		// 1 is the first object's minimum Z value.
		// We use an unsigned int so we don't get a warning with selectBuffer below.
		unsigned int lowestDepth = selectBuffer[1];

		// Set the selected object to the first object to start it off.
		// 3 is the first object's object ID we passed into glLoadName().
		int selectedObject = selectBuffer[3];

		// Go through all of the objects found, but start at the second one
		for(int i = 1; i < objectsFound; i++)
		{
			// Check if the current objects depth is lower than the current lowest
			// Notice we times i by 4 (4 values for each object) and add 1 for the depth.
			if(selectBuffer[(i * 4) + 1] < lowestDepth)
			{
				// Set the current lowest depth
				lowestDepth = selectBuffer[(i * 4) + 1];

				// Set the current object ID
				selectedObject = selectBuffer[(i * 4) + 3];
			}
		}
		
		// Return the selected object
		return selectedObject;
	}

	// We didn't click on any objects so return 0
	return 0;											
}

void OGL_Wrapper::CreateTexture(UINT textureArray[], LPSTR strFileName, int textureID)
{
	if(!strFileName)									// Return from the function if no file name was passed in
		return;

	int w, h;

	unsigned char *temp = gltReadBMPBits(strFileName, &w, &h);

	// Generate a texture with the associative texture ID stored in the array
	glGenTextures(1, &textureArray[textureID]);

	// This sets the alignment requirements for the start of each pixel row in memory.
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	// Bind the texture to the texture arrays index and init the texture
	glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);

	// Build Mipmaps (builds different versions of the picture for distances - looks better)
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_BGR_EXT/*GL_RGB*/, GL_UNSIGNED_BYTE, temp);

	// Lastly, we need to tell OpenGL the quality of our texture map.  
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);

	// Now we need to free the bitmap data that we loaded since openGL stored it as a texture
	free(temp);   
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

void OGL_Wrapper::drawModel(t3DModel &model, UINT *text)
{
	for(int i = 0; i < model.numOfObjects; i++)
	{
		// Make sure we have valid objects just in case. (size() is in the vector class)
		if(model.pObject.size() <= 0) break;

		// Get the current object that we are displaying
		t3DObject *pObject = &model.pObject[i];
			
		// Check to see if this object has a texture map, if so bind the texture to it.
		if(pObject->bHasTexture) {

			// Turn on texture mapping and turn off color
			glEnable(GL_TEXTURE_2D);

			// Reset the color to normal again
			glColor3ub(255, 255, 255);

			// Bind the texture map to the object by it's materialID
			glBindTexture(GL_TEXTURE_2D, text[pObject->materialID]);
		} else {

			// Turn off texture mapping and turn on color
			glDisable(GL_TEXTURE_2D);

			// Reset the color to normal again
			glColor3ub(255, 255, 0);
		}

		// This determines if we are in wireframe or normal mode
		glBegin(g_ViewMode);					// Begin drawing with our selected mode (triangles or lines)

			// Go through all of the faces (polygons) of the object and draw them
			for(int j = 0; j < pObject->numOfFaces; j++)
			{
				// Go through each corner of the triangle and draw it.
				for(int whichVertex = 0; whichVertex < 3; whichVertex++)
				{
					// Get the index for each point of the face
					int index = pObject->pFaces[j].vertIndex[whichVertex];
			
					// Give OpenGL the normal for this vertex.
					glNormal3f(pObject->pNormals[ index ].x, pObject->pNormals[ index ].y, pObject->pNormals[ index ].z);
				
					// If the object has a texture associated with it, give it a texture coordinate.
					if(pObject->bHasTexture) {

						// Make sure there was a UVW map applied to the object or else it won't have tex coords.
						if(pObject->pTexVerts) {
							glTexCoord2f(pObject->pTexVerts[ index ].x, pObject->pTexVerts[ index ].y);
						}
					} else {

						if(model.pMaterials.size() && pObject->materialID >= 0) 
						{
							// Get and set the color that the object is, since it must not have a texture
							BYTE *pColor = model.pMaterials[pObject->materialID].color;

							// Assign the current color to this model
							glColor3ub(pColor[0], pColor[1], pColor[2]);
						}
					}

					// Pass in the current vertex of the object (Corner of current face)
					glVertex3f(pObject->pVerts[ index ].x, pObject->pVerts[ index ].y, pObject->pVerts[ index ].z);
				}
			}

		glEnd();								// End the drawing
	}
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

 