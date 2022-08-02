// Game.cpp: implementation of the Game class.

#include <cmath>
#include <cstdio>
#include "Game.h"

#pragma warning(disable : 4244)

// find : calculates the number of signifacant digits to the left of the deimal place
int find(float a);

// Buffering our key input
int key_press[256] = { 0, };

//////////////////////////////////////////////////////////////////////////////////////////////////
// The names of our Bitmaps
//////////////////////////////////////////////////////////////////////////////////////////////////
char *form_pic[4] = { {"formula1.bmp" },
					  {"formula2.bmp" }, 
					  {"formula3.bmp" }, 
					  {"formula4.bmp" }
					};
char *un_form_pic[4] = { {"formula1_un.bmp" },
					     {"formula2_un.bmp" }, 
					     {"formula3_un.bmp" }, 
					     {"formula4_un.bmp" }
					   };
char *var_pic[Game::NUM_VAR] = { {"accel.bmp"},
							     {"vi.bmp"},
							     {"vf.bmp"},
							     {"dist.bmp"},
							     {"time.bmp"}
							   };
char *un_var_pic[Game::NUM_VAR] = { {"un_accel.bmp"},
								    {"un_vi.bmp"},
								    {"un_vf.bmp"},
								    {"un_dist.bmp"},
								    {"un_time.bmp"}
								  };
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// global used for scaling the formula bitmaps.
float scale = 1;


//	GameInit : Initializes the Window and Game Components.
void Game::GameInit(HWND hwnd, int window_width, int window_height, bool fullscreen)
{
	// Pass our hwnd to our Game class
	hWnd = hwnd;
	
	// Initialize the Window.
	drawer.init(hWnd, window_width, window_height, fullscreen);

	// Initializes our bitmap loader.
	loader.init(drawer.getDDObject(), hWnd);

	// Loading our bitmaps and initializing our array values
	for(int i = 0; i < 4; ++i)
	{
		form[i] = loader.load(form_pic[i]);
		un_form[i] = loader.load(un_form_pic[i]);
		form_start_loc[i].x = form_curr_loc[i].x = 50 + 190 * i;
		form_start_loc[i].y = form_curr_loc[i].y = 100;
		var_values[i] = 0;

		decimal[i] = false;
		negative[i] = 1;
		decimal_place[i] = .1f;
	}
	// More of the same
	for(i = 0; i < NUM_VAR; ++i)
	{
		curr_variable[i] = loader.load(var_pic[i]);
		variable[i] = loader.load(un_var_pic[i]);
	}
	// Loading yet more bitmaps
	car[0] = loader.loadWithKeyColor("car.bmp", 0x4d, 0x4d, 0x4d);
	car[1] = loader.loadWithKeyColor("car2.bmp", 0x4d, 0x4d, 0x4d);
	road = loader.load("road.bmp");

	// Guess what? Even more initialization
	current_formula = current_var = 0;
	state = CHOOSE_FORMULA;

	// Setting up our 2D array of function pointers.
	// Sadly, there was no way to avoid hard-coding this by hand
	pf_form[0][0] = form1_a;
	pf_form[0][1] = form1_vi;
	pf_form[0][2] = form1_vf;
	pf_form[0][3] = form1_t;

	pf_form[1][0] = form2_vi;
	pf_form[1][1] = form2_vf;
	pf_form[1][2] = form2_x;
	pf_form[1][3] = form2_t;

	pf_form[2][0] = form3_a;
	pf_form[2][1] = form3_vi;
	pf_form[2][2] = form3_x;
	pf_form[2][3] = form3_t;

	pf_form[3][0] = form4_a;
	pf_form[3][1] = form4_vi;
	pf_form[3][2] = form4_vf;
	pf_form[3][3] = form4_x;

	// And.....that's right....more initialization
	alt_answer = -100000;
	paused = false;
	get_real = false;
}


//	GameMain : Does all Main Game Processing.
bool Game::GameMain(void)
{
	// start our frame limiter
	DWORD start_time = GetTickCount();

	//	Clear the screen and set transparency.
	drawer.fillBackBuffer(0);

	// our beginning game state.  Which formula?
	if(state == CHOOSE_FORMULA)
	{
		drawer.drawText(NULL, "Left and Right selects, Enter to continue",
						265, 20, 0, 0x00FF7777); 

		drawer.drawText(NULL, "Please choose the formula you wish to use: ",
						250, 50, 0, 0x00FF0000); 
		
		// Line 'em up at the top of the screen.
		for(int i = 0; i < 4; ++i)
		{
			// Draw the unselected ones
			if(i != current_formula)
				loader.draw(drawer.getBackBuffer(), un_form[i], form_start_loc[i].x, form_start_loc[i].y);  
			// Draw our lucky winner
			else
				loader.draw(drawer.getBackBuffer(), form[i], form_start_loc[i].x, form_start_loc[i].y);  
		} 

		// Move right
		if(GetAsyncKeyState(VK_RIGHT) && (key_press[VK_RIGHT] < 1 || 
			(key_press[VK_RIGHT] > 30 && !(key_press[VK_RIGHT] % 7))))
		{
			++key_press[VK_RIGHT];
			if(current_formula < 3)
			{
				++current_formula;
			}
			else
			{
				current_formula = 0;
			}
		}
		// Move left
		if(GetAsyncKeyState(VK_LEFT) && (key_press[VK_LEFT] < 1 || 
			(key_press[VK_LEFT] > 30 &&! (key_press[VK_LEFT] % 7))))
		{
			++key_press[VK_LEFT];
			if(current_formula > 0)
			{
				--current_formula;
			}
			else
			{
				current_formula = 3;
			}
		}
		// Move on
		if(GetAsyncKeyState(VK_RETURN) && !key_press[VK_RETURN])
		{
			++key_press[VK_RETURN];
			state = FORMULA_CHOOSING;
		}
	}
	// Our second state, isn't this part pretty?
	if(state == FORMULA_CHOOSING)
	{
		// A temp variable for the sake of simplicity. Who wants to do all that typing?
		int a = current_formula;

		// Decrease the size of the picture until it's gone
		if(scale > 0)
		{
			scale /= 1.1f;
		}
		
		drawer.drawText(NULL, "Left and Right selects, Enter to continue, Backspace to go back",
						185, 20, 0, 0x00FF7777); 

		// Handles the movement of our 2 left bitmaps.
		if(a < 2)
		{
			// Are we there yet papa smurf?
			if(form_curr_loc[a].x < 335)
				form_curr_loc[a].x += int(float(355 - form_curr_loc[a].x) / 20);
			// Yes we are.
			else
				state = FORMULA_CHOSEN;
		}
		// Handles the movement of our 2 right bitmaps.
		else
		{
			// Are we there yet papa smurf?
			if(form_curr_loc[a].x > 335)
				form_curr_loc[a].x += int(float(315 - form_curr_loc[a].x) / 20);
			// Yes we are.
			else
				state = FORMULA_CHOSEN;

		}
		// Make the unlucky 3 go bye-bye
		for(int i = 0; i < 4; ++i)
		{
			if(a != i)
			{
				// going, going, gone.
				loader.drawScaled(drawer.getBackBuffer(), un_form[i], 
								  int(form_curr_loc[i].x + (130 * (1 - scale) / 2)), 
								  int(form_curr_loc[i].y + (70 * (1 - scale) / 2)),
								  int(130 * scale), int(70 * scale));  
			}
		}
		// Draw our lucky contestant
		loader.draw(drawer.getBackBuffer(), form[a], form_curr_loc[a].x, form_curr_loc[a].y);  

		// Only 4 variables in the formula, but we have 5.  Somebody's gotta go
		switch(a)
		{
			case 0:
				var_to_ignore = DIST;
				break;
			case 1:
				var_to_ignore =	ACCEL;
				break; 
			case 2:
				var_to_ignore = FINAL_VEL;
				break;
			case 3:
				var_to_ignore = TIME;
				break;
		}

		int x_loc = 310;
		// Let's bring the variables into the picture
		for(i = 0; i < NUM_VAR; ++i)
		{
			if(i != var_to_ignore)
			{
				loader.drawScaled(drawer.getBackBuffer(), variable[i], 
								  int(x_loc + (30 * (scale) / 2)), 
								  int(200 + (30 * (scale) / 2)),
								  int(30 * (1 - scale) - 4), int(30 * (1 - scale) - 4));  
				x_loc += 50;
			}
		}
	}
	// Time to pick our variable.
	if(state == FORMULA_CHOSEN)
	{
		// A temp variable for the sake of simplicity. Who wants to do all that typing?
		int a = current_formula;

		// Print the instructions to the screem
		drawer.drawText(NULL, "Left and Right selects, Enter to continue, Backspace to go back",
						185, 20, 0, 0x00FF7777); 
		drawer.drawText(NULL, "Please choose the variable you wish to solve for: ",
						230, 50, 0, 0x00FF0000); 
		// Draw our formula
		loader.draw(drawer.getBackBuffer(), form[a], form_curr_loc[a].x, form_curr_loc[a].y);  

		// Let's move to the right, shall we?
		if(GetAsyncKeyState(VK_RIGHT) && (key_press[VK_RIGHT] < 1 || 
			(key_press[VK_RIGHT] > 30 && !(key_press[VK_RIGHT] % 7))))
		{
			++key_press[VK_RIGHT];
			if(current_var < 4)
			{
				++current_var;
				if(current_var == var_to_ignore)
					++current_var;
			}
			// Wrap around
			else
			{
				current_var = 0;
				if(current_var == var_to_ignore)
					++current_var;
			}
			// An extra check which solves a minor issue of no default variable being selected
			if(current_var > 4)
				current_var = 0; 
		}

		// Let's move to the left
		if(GetAsyncKeyState(VK_LEFT) && (key_press[VK_LEFT] < 1 || 
			(key_press[VK_LEFT] > 30 && !(key_press[VK_LEFT] % 7))))
		{
			++key_press[VK_LEFT];
			if(current_var > 0)
			{
				--current_var;
				if(current_var == var_to_ignore)
					--current_var;
			}
			// Wrap around
			else
			{
				current_var = 4;
				if(current_var == var_to_ignore)
					--current_var;
			}
			// An extra check which solves a minor issue of no default variable being selected
			if(current_var < 0)
				current_var = 4; 
		}

		// Fix an issue on formula 2 where no default variable is initially selected
		if(current_var == var_to_ignore)
			++current_var;

		int x_loc = 310;
		int index = 0;
		// Draw our variables.
		for(int i = 0; i < NUM_VAR; ++i)
		{
			// Make sure we don't draw the one not being used
			if(i != var_to_ignore)
			{
				// Set up our array for future use
				valid_var[index] = curr_variable[i];
				un_valid_var[index] = variable[i];
				
				var_start_loc[index].x = var_curr_loc[index].x = x_loc;
				var_start_loc[index++].y = var_curr_loc[index].y = 200;

				// Draw the selected one
				if(i == current_var)
					loader.draw(drawer.getBackBuffer(), curr_variable[i], x_loc , 200);
				// Draw the other 3
				else
					loader.draw(drawer.getBackBuffer(), variable[i], x_loc , 200);
				x_loc += 50;
			}
		}
		// I don't think I like this formula, let's go back
		if(GetAsyncKeyState(VK_BACK) && !key_press[VK_BACK])
		{
			++key_press[VK_BACK];
			state = FORMULA_UNCHOOSING;
			current_var = 0;
		}
		// Wow, this formula is the shiznit!  Let's move on
		if(GetAsyncKeyState(VK_RETURN) && !key_press[VK_RETURN])
		{
			++key_press[VK_RETURN];
			state = VAR_CHOOSING;

			// Make sure nothing funny is happening
			if(current_var < var_to_ignore)
				new_curr_var = current_var;
			else
				new_curr_var = current_var - 1;

			// Set up the final locations
			int temp_x = 135 - 45;
			for(int i = 0; i < 4; ++i)
			{
				// Where to move the one we selected
				if(i == new_curr_var)
				{
					var_end_loc[i].x = 385 - 45;
					var_end_loc[i].y = 200;
				}
				// Where to move the other three
				else
				{
					var_end_loc[i].x = temp_x;
					var_end_loc[i].y = 300;
					temp_x += 250;
				}
			}
		}
	}
	// Moves our variables into the appropriate position
	if(state == VAR_CHOOSING)
	{
		int a = current_formula;
		drawer.drawText(NULL, "Left and Right selects, Enter to continue, Backspace to go back",
						185, 20, 0, 0x00FF7777); 

		// Draws our selected formula
		loader.draw(drawer.getBackBuffer(), form[a], form_curr_loc[a].x, form_curr_loc[a].y);

		// Draws all the variables.
		for(int i = 0; i < 4; ++i)
		{
			// Moves our selected variable
			if(i == new_curr_var)
			{
				float mx = float(var_end_loc[i].x - var_start_loc[i].x);
				// Move it left
				if(var_curr_loc[i].x > var_end_loc[i].x)
					var_curr_loc[i].x -= abs((int)mx / 20);
				// Or move it right
				else
					var_curr_loc[i].x += abs((int)mx / 20);
			}
			// Moves all the other variables
			else
			{
				// X and Y components of the slope of the line between where they are and where
				// they need to be
				float mx = float(var_end_loc[i].x - var_start_loc[i].x);
				float my = float(var_end_loc[i].y - var_start_loc[i].y);

				// Move it right along the X axis
				if(var_curr_loc[i].x < var_end_loc[i].x && var_curr_loc[i].y < var_end_loc[i].y)
				{
					var_curr_loc[i].x += abs((int)mx / 20);
				}
				// Move it left along the X axis
				else if(var_curr_loc[i].x > var_end_loc[i].x && var_curr_loc[i].y < var_end_loc[i].y)
				{
					var_curr_loc[i].x -= abs((int)mx / 20);
				}
				// Move it down along the Y axis
				if(var_curr_loc[i].y < var_end_loc[i].y)
					var_curr_loc[i].y += ((int)my / 20);
			}
			// Do the actual drawing
			loader.draw(drawer.getBackBuffer(), valid_var[i], var_curr_loc[i].x , var_curr_loc[i].y);
		}

		// If everything is where it needs to be, move to the next state
		if((new_curr_var == 0 && var_curr_loc[new_curr_var].x >= var_end_loc[new_curr_var].x) ||
		   (new_curr_var > 0 && var_curr_loc[new_curr_var].x <= var_end_loc[new_curr_var].x))
			state = VAR_CHOSEN;

		// Reset back to the first variable
		var_being_changed = 0;
		if(var_being_changed == new_curr_var)
			var_being_changed++;
		if(var_being_changed > 3)
			var_being_changed = 0;  

	}
	// Entering in the values for the known parameters
	if(state == VAR_CHOSEN)
	{
		// Temp values to cut down on the typing
		int a = current_formula;
		int b = new_curr_var;						   
		// Print the instruction manual
		drawer.drawText(NULL, "Left and Right selects.   Enter the known values, use Delete to make corrections",
						135, 240, 0, 0x00FF7777);
		drawer.drawText(NULL, "Enter to solve the equation, Backspace to return",
						240, 260, 0, 0x00FF7777);

		// Prints out the error message in the case of a value which could cause errors
		if(get_real)
			drawer.drawText(NULL, "That value would be unrealistically high",
							275, 350, 0, 0x000000FF);
		// Draw the formula's bitmap
		loader.draw(drawer.getBackBuffer(), form[a], form_curr_loc[a].x, form_curr_loc[a].y);

		// Draw the variable names and the corresponding values
		for(int i = 0; i < 4; ++i)
		{
			char temp[60];
			// Convert the values into a string, significant figures dependant upon the input
			if(decimal[i])
				sprintf(temp, "%.2f", var_values[i]);
			else
				sprintf(temp, "%.0f", var_values[i]);

			// Draw the variable being changed and the one being solved for
			if(i == b || i == var_being_changed)
			{
				loader.draw(drawer.getBackBuffer(), valid_var[i], var_curr_loc[i].x , var_curr_loc[i].y);

				drawer.drawText(NULL, "=", var_curr_loc[i].x + 25, var_curr_loc[i].y + 4, 0, 0x0000FFFF);
				drawer.drawText(NULL, temp, var_curr_loc[i].x + 75, var_curr_loc[i].y + 4, 0, 0x0000FFFF); 
			}
			// Draw the other two
			else
			{
				loader.draw(drawer.getBackBuffer(), un_valid_var[i], var_curr_loc[i].x , var_curr_loc[i].y);
				drawer.drawText(NULL, "=", var_curr_loc[i].x + 25, var_curr_loc[i].y + 4, 0, 0x00004444); 
				drawer.drawText(NULL, temp, var_curr_loc[i].x + 75, var_curr_loc[i].y + 4, 0, 0x00004444); 
			}
		}
		// Go back to choosing the variable		
		if(GetAsyncKeyState(VK_BACK) &&	!key_press[VK_BACK])
		{
			++key_press[VK_BACK];
			state = VAR_UNCHOOSING;
			for(int i = 0; i < 4; ++i)
			{
				// Make sure that all of our values are reset to the initialized state
				var_values[i] = 0;
				decimal[i] = false;
				negative[i] = 1;
				decimal_place[i] = .1f;
			}
			// Really no need to do this here as well, I'm just paranoid
			alt_answer = -100000;
			paused = false;
		}
		// Let's get ready to rumble
		if(GetAsyncKeyState(VK_RETURN) && !key_press[VK_RETURN])
		{
			++key_press[VK_RETURN];
			state = SOLVE;
		}

		// Check for numerical input
		for(char j = '0'; j <= '9'; ++j)
		{
			if(GetAsyncKeyState(j) && !key_press[j])
			{
				// A number has been pressed
				++key_press[j];

				// If the current value has no decimal places.....
				if(!decimal[var_being_changed])
				{
					// .....Move all the other numbers over 1 space, and add the entered value
					var_values[var_being_changed] = var_values[var_being_changed] * 10 
													+ (atoi(&j) * negative[var_being_changed]);
				}
				// If there	are decimal values and they aren't further than 2 places right of the dot
				else if(decimal_place[var_being_changed] > .005f)
				{
					// then turn the input in to the appropriate value and add it in
					var_values[var_being_changed] += 
						(atoi(&j) * decimal_place[var_being_changed] * negative[var_being_changed]);
					decimal_place[var_being_changed] /= 10;
				}
				get_real = false;
			}
		}
		// Check the number of significant digits to the left of the decimal point
		if(find(var_values[var_being_changed]) > 6)
		{
			// If there are more than 6 digits, remove one and make sure the error meassage
			// gets printed
			get_real = true;
			var_values[var_being_changed] /= 10;
			var_values[var_being_changed] = int(var_values[var_being_changed]);
		}
		// Implementation of decimal values
		if(GetAsyncKeyState(VK_PERIOD) && !key_press[VK_PERIOD] && !decimal[var_being_changed])
		{
			++key_press[VK_PERIOD];
			decimal[var_being_changed] = true;
			// Initialize the deicmal place holder to the left most space
			decimal_place[var_being_changed] = .1f;
			// Unlock the input if it was previously locked
			get_real = false;
		}
		// Toggle the postive or negative value of the veriable being changed 
		if(GetAsyncKeyState(VK_DASH) && !key_press[VK_DASH])
		{
			++key_press[VK_DASH];
			negative[var_being_changed] *= -1;
			var_values[var_being_changed] *= -1;
			get_real = false;
		}
		// Make corrections to the input
		if(GetAsyncKeyState(VK_DELETE) && !key_press[VK_DELETE])
		{
			++key_press[VK_DELETE];
			// In the case of no decimal values.....
			if(!decimal[var_being_changed])
			{
				// ...just divide the number by 10.....
				var_values[var_being_changed] /= 10;
				var_values[var_being_changed] = int(var_values[var_being_changed]);
			}
			// ...but if there are decimal vlues.....
			else
			{
				// Depending on which digit, we must do differennt things
				// Second digit from the decimal point
				if(decimal_place[var_being_changed] < .01f)
				{
					// multiply by 10 and type-cast as an int, then divide by 10 again
					var_values[var_being_changed] = int(var_values[var_being_changed] * 10) / 10.0f;
					decimal_place[var_being_changed] = .01f;
				}
				// This case only happens in the case of 2 consecutive deletes
				else if(decimal_place[var_being_changed] == .01f)
				{
					var_values[var_being_changed] = int(var_values[var_being_changed]);
					decimal_place[var_being_changed] = .1f;
				}
				// Remove all decimal values
				else
				{
					var_values[var_being_changed] /= 10;
					var_values[var_being_changed] = int(var_values[var_being_changed]);
					decimal_place[var_being_changed] = .1f;
					decimal[var_being_changed] = false;
				}
			}
			// Reset the "stop being stupid" state
			get_real = false; 
		}
		// Move to the next variable 
		if(GetAsyncKeyState(VK_RIGHT) && (key_press[VK_RIGHT] < 1 || 
			(key_press[VK_RIGHT] > 30 && !(key_press[VK_RIGHT] % 7))))
		{
			++key_press[VK_RIGHT];
			// Skip the value we're solving for
			if(var_being_changed + 1 == b)
				var_being_changed += 2;
			else
				++var_being_changed;

			if(var_being_changed > 3)
				var_being_changed = 0;

			// extra check which fixes a minor issue with skipping a selection
			if(var_being_changed == b)
				++var_being_changed;
			// Reset the safety check	
			get_real = false;
		}
		// Move to the previous variable
		if(GetAsyncKeyState(VK_LEFT) && (key_press[VK_LEFT] < 1 || 
			(key_press[VK_LEFT] > 30 && !(key_press[VK_LEFT] % 7))))
		{
			++key_press[VK_LEFT];
			// Skip the value we're solving for
			if(var_being_changed - 1 == b)
				var_being_changed -= 2;
			else
				--var_being_changed;

			if(var_being_changed < 0)
				var_being_changed = 3;
			
			// Extra check which fixes a minor issue with skipping a selection
			if(var_being_changed == b)
				--var_being_changed;
			// Reset the safety check
			get_real = false;
		}
	}
	// Solve the equation
	if(state == SOLVE)
	{
		// Temp values
		int a = current_formula;
		int b = new_curr_var;

		// Do the actual solving using our previously set up function pointers
		// Don't hate me because I'm beautiful
		var_values[b] = pf_form[a][b](var_values[(b == 0 ? 1 : 0)], 
									  var_values[((b == 0 || b == 1) ? 2 : 1)], 
									  var_values[(b == 3 ? 2 : 3)], alt_answer);
		// Print the directions to the screen
		drawer.drawText(NULL, "Left and Right selects.   Enter the known values, use Delete to make corrections",
						135, 240, 0, 0x00FF7777);
		drawer.drawText(NULL, "Enter to solve the equation, Backspace to return",
						240, 260, 0, 0x00990000);
		// Draw our equation 
		loader.draw(drawer.getBackBuffer(), form[a], form_curr_loc[a].x, form_curr_loc[a].y);

		// Draw all the values
		for(int i = 0; i < 4; ++i)
		{
			char temp[60];
			sprintf(temp, "%.2f", var_values[i]);
			loader.draw(drawer.getBackBuffer(), valid_var[i], var_curr_loc[i].x , var_curr_loc[i].y);
			drawer.drawText(NULL, "=", var_curr_loc[i].x + 25, var_curr_loc[i].y + 4, 0, 0x0000FFFF);
			drawer.drawText(NULL, temp, var_curr_loc[i].x + 75, var_curr_loc[i].y + 4, 0, 0x0000FFFF); 
		}
		// Set all the convenience variables.  It was not a neccesity to create and use these
		// but it made the work alot simpler
		switch(a)
		{
			case 0:
			{
				race_values[ACCEL] = var_values[0];
				race_values[INIT_VEL] = var_values[1];
				race_values[FINAL_VEL] = var_values[2];
				race_values[TIME] = var_values[3];
				float dump = 0;
				// Calculate the missing parameter
				race_values[DIST] = form2_x(race_values[INIT_VEL], race_values[FINAL_VEL],
											 race_values[TIME], dump);
			}
				break;
			case 1:
			{
				race_values[INIT_VEL] = var_values[0];
				race_values[FINAL_VEL] = var_values[1];
				race_values[DIST] = var_values[2];
				race_values[TIME] = var_values[3];
				float dump = 0;
				// Calculate the missing parameter
				race_values[ACCEL] = form1_a(race_values[INIT_VEL],	race_values[FINAL_VEL],
											 race_values[TIME], dump);
			}
				break;
			case 2:
			{
				race_values[ACCEL] = var_values[0];
				race_values[INIT_VEL] = var_values[1];
				race_values[DIST] = var_values[2];
				// In the event of 2 possible times, go with the larger one
				if(alt_answer > 0)
					race_values[TIME] = alt_answer;
				else
					race_values[TIME] = var_values[3];
				float dump = 0;
				// Calculate the missing parameter
				race_values[FINAL_VEL] = form2_vf(race_values[INIT_VEL], race_values[DIST],
												  race_values[TIME], dump);
			}
				break;
			case 3:
				race_values[ACCEL] = var_values[0];
				race_values[INIT_VEL] = var_values[1];
				race_values[FINAL_VEL] = var_values[2];
				race_values[DIST] = var_values[3];
				float dump = 0;
				// Calculate the missing parameter
				race_values[TIME] = form1_t(race_values[ACCEL], race_values[INIT_VEL],
											race_values[FINAL_VEL], dump);
				break;

		}
		// Initialize the counter variables
		curr_vel = race_values[INIT_VEL];
		time_elapsed = disp = 0;

		screen_disp = -40;
		start = GetTickCount();
		// Time to make the car go zoom
		state = SOLVED;

	}
	// Let's race
	if(state == SOLVED)
	{
		// Arthritis prevention
		int a = current_formula;
		int b = new_curr_var;

		// Print out the instructions
		drawer.drawText(NULL, "Press P to pause,  Backspace to return",
						275, 250, 0, 0x00FF7777);
		// Draw our formula
		loader.draw(drawer.getBackBuffer(), form[a], form_curr_loc[a].x, form_curr_loc[a].y);

		// Print out the error message in the event of unsolvable parameters
		if(var_values[b] == -100000)
		{
			drawer.drawText(NULL, "INVALID PARAMETERS, EQUATION IS UNSOLVABLE", 220, 300, 0, 0x000000FF);
		}
		// Otherwise print out everything else
		else
		{
			sprintf(print[0], "Elapsed time: %.2f sec", time_elapsed);
			sprintf(print[1], "Displacement: %.2f units", disp);
			sprintf(print[2], "Current velocity: %.2f units/sec", curr_vel);

			float dump = 0;
			// Update the values every frame if we're not paused
			if(!paused)
			{
				time_elapsed = (GetTickCount() - start) / 1000.0f;

				curr_vel = form1_vf(race_values[ACCEL], race_values[INIT_VEL], time_elapsed, dump);

				disp = form3_x(race_values[ACCEL], race_values[INIT_VEL], time_elapsed, dump);
			}
			// If we are paused, change the starting time so that no time elapses
			else
			{
				start = GetTickCount() - unsigned long(time_elapsed * 1000);
			}

			// Set the numbers on the mile markers
			screen_disp = ((int)disp / 10) * 10  - 50;

			// Set the screen offset for where they are drawn
			int offset = int(disp * 10) % 100;

			// Draw the road and the mile markers
			for(int i = -1; i < 9; ++i)
			{
				char t[50];
				sprintf(t, "%d" ,screen_disp);
				if(!(screen_disp % 20))
					drawer.drawText(NULL, t, i * 100 - offset, 400, 0, 0x00FF0000);
				
				loader.draw(drawer.getBackBuffer(), road, i * 100 - offset, 450);
				screen_disp += 10;
			}

			// Copy the values into strings for displaying
			sprintf(print[0], "Elapsed time: %.2f sec", time_elapsed);
			sprintf(print[1], "Displacement: %.2f units", disp);
			sprintf(print[2], "Current velocity: %.2f units/sec", curr_vel);

			// Print the variables and their values
			for(i = 0; i < 4; ++i)
			{
				char temp[60];
				sprintf(temp, "%.2f", var_values[i]);

				loader.draw(drawer.getBackBuffer(), valid_var[i], var_curr_loc[i].x , var_curr_loc[i].y);

				drawer.drawText(NULL, "=", var_curr_loc[i].x + 25, var_curr_loc[i].y + 4, 0, 0x0000FFFF);
				drawer.drawText(NULL, temp, var_curr_loc[i].x + 75, var_curr_loc[i].y + 4, 0, 0x0000FFFF); 
				
				// Print the alterante answer, if there is one
				if(alt_answer > 0)
				{
					char temp2[60];
					sprintf(temp2, "and         %.2f", alt_answer);
					drawer.drawText(NULL, temp2, 470, 205, 0, 0x0000FFFF); 	
				}
				// Print the current race values
				if(i < 3)
				{
					drawer.drawText(NULL, print[i], 110 + i * 215, 350, 0, 0x0000FF00);
				}
			}
			// Stop when the elapsed time equals the time calculated and/or inputted
			if(time_elapsed >= race_values[TIME])
			{
				state = LE_FIN;
			}
			// Pause if they hit 'P'
			if(GetAsyncKeyState('P') && !key_press['P'])
			{
				++key_press['P'];
				paused = !paused;
			}
			// Draw the car
			static index = 0;
			++index;
			loader.draw(drawer.getBackBuffer(), car[abs(((int)disp / 4) % 2)], 400 - 174 / 2, 450);
		}
		// "Wow, this is boring, I wanna start over"
		if(GetAsyncKeyState(VK_BACK) &&	!key_press[VK_BACK])
		{
			++key_press[VK_BACK];
			state = VAR_UNCHOOSING;
			// Reset all our values back to the initialized state
			for(int i = 0; i < 4; ++i)
			{
				var_values[i] = 0;
				decimal[i] = false;
				negative[i] = 1;
				decimal_place[i] = .1f;
			}
			// Reset the alternate answer if there is one
			alt_answer = -100000;
			// Make sure the race doesn't start on pause the next time around
			paused = false;
		}

	}
	// Free at last.....Free at last......THANK GOD ALMIGHTY!! We're free at last!
	if(state == LE_FIN)
	{
		// If being lazy is wrong, then I don't wanna be right.
		int a = current_formula;
		int b = new_curr_var;

		// Print the instructions
		drawer.drawText(NULL, "Race finished,  Press Backspace to return",
						265, 250, 0, 0x00FF7777);
		// Draw the formula
		loader.draw(drawer.getBackBuffer(), form[a], form_curr_loc[a].x, form_curr_loc[a].y);
		// Print out the variables, their values, and the end race values
		for(int i = 0; i < 4; ++i)
		{
			char temp[60];
			sprintf(temp, "%.2f", var_values[i]);

			loader.draw(drawer.getBackBuffer(), valid_var[i], var_curr_loc[i].x , var_curr_loc[i].y);

			drawer.drawText(NULL, "=", var_curr_loc[i].x + 25, var_curr_loc[i].y + 4, 0, 0x0000FFFF);
			drawer.drawText(NULL, temp, var_curr_loc[i].x + 75, var_curr_loc[i].y + 4, 0, 0x0000FFFF); 
			
			// Print out the alternate answer, if there is one
			if(alt_answer > 0)
			{
				char temp2[60];
				sprintf(temp2, "and         %.2f", alt_answer);
				drawer.drawText(NULL, temp2, 470, 205, 0, 0x0000FFFF); 	
			}

			if(i < 3)
			{
				drawer.drawText(NULL, print[i], 110 + i * 215, 350, 0, 0x0000FF00);
			}
		}
		// Calculate the mile marker start value
		screen_disp = ((int)disp / 10) * 10  - 50;
		// Calculate the screen offset for the mile markers
		int offset = int(disp * 10) % 100;
		// Draw the markers and the road
		for(i = -1; i < 9; ++i)
		{
			char t[50];
			sprintf(t, "%d" ,screen_disp);
			if(!(screen_disp % 20))
				drawer.drawText(NULL, t, i * 100 - offset, 400, 0, 0x00FF0000);
			loader.draw(drawer.getBackBuffer(), road, i * 100 - offset, 450);
			// Next in line please
			screen_disp += 10;
		}
		// Draw the car
		loader.draw(drawer.getBackBuffer(), car[0], 400 - 174 / 2, 450);

		// Wanna play again?
		if(GetAsyncKeyState(VK_BACK) &&	!key_press[VK_BACK])
		{
			++key_press[VK_BACK];
			state = VAR_UNCHOOSING;
			// Reset values
			for(int i = 0; i < 4; ++i)
			{
				var_values[i] = 0;
				decimal[i] = false;
				negative[i] = 1;
				decimal_place[i] = .1f;
			}
			alt_answer = -100000;
			paused = false;
		}

	}
	// This state is called at various parts on the code to move the variables back to the
	// "Choose which variable" state
	if(state == VAR_UNCHOOSING)
	{
		int a = current_formula;
		// Print the directions
		drawer.drawText(NULL, "Left and Right selects, Enter to continue, Backspace to go back",
						185, 20, 0, 0x00990000); 
		// Draw the formula
		loader.draw(drawer.getBackBuffer(), form[a], form_curr_loc[a].x, form_curr_loc[a].y);

		// Move the variables
		for(int i = 0; i < 4; ++i)
		{
			// Update the position of the previously selected one
			if(i == new_curr_var)
			{
				float mx = float(var_start_loc[i].x - var_end_loc[i].x);
				if(var_curr_loc[i].x > var_start_loc[i].x)
					var_curr_loc[i].x -= abs((int)mx / 20);
				else
					var_curr_loc[i].x += abs((int)mx / 20);
			}
			// Update the rest of them
			else
			{
				// Variables which hold the slope of the line along which they are moving
				float mx = float(var_start_loc[i].x - var_end_loc[i].x);
				float my = float(var_start_loc[i].y - var_end_loc[i].y);
				// Update the X
				if(var_curr_loc[i].x < var_start_loc[i].x && var_curr_loc[i].y > var_start_loc[i].y)
				{
					var_curr_loc[i].x += abs((int)mx / 20);
				}
				else if(var_curr_loc[i].x > var_start_loc[i].x && var_curr_loc[i].y > var_start_loc[i].y)
				{
					var_curr_loc[i].x -= abs((int)mx / 20);
				}
				// Update the Y
				if(var_curr_loc[i].y > var_start_loc[i].y)
					var_curr_loc[i].y += ((int)my / 20);
			}
		// Do the actual drawing now that the values are updated 
		loader.draw(drawer.getBackBuffer(), valid_var[i], var_curr_loc[i].x , var_curr_loc[i].y);
		}
		// If everybody is where they need to be, let them pick which variable again
		if(var_curr_loc[new_curr_var].x == var_start_loc[new_curr_var].x)
			state = FORMULA_CHOSEN;
	}

	// This state is called at various parts on the code to move the variables back to the
	// "Choose which formula" state
	if(state == FORMULA_UNCHOOSING)
	{
		int a = current_formula;
		// Update the scale each frame.  This value begins at almost, 
		// but not quite, the exact opposite of infiniy
		if(scale < 1)
		{
			scale *= 1.1f;
		}
		// Print the instructions
		drawer.drawText(NULL, "Left and Right selects, Enter to continue, Backspace to go back",
						185, 20, 0, 0x00990000); 

		// In the instance where the formula should move left
		if(a < 2)
		{
			if(form_curr_loc[a].x > form_start_loc[a].x)
				form_curr_loc[a].x += int(float(form_start_loc[a].x - 20 - form_curr_loc[a].x) / 20);
			else
				state = CHOOSE_FORMULA;
		}
		// In the instance where the formula should move right
		else
		{
			if(form_curr_loc[a].x < form_start_loc[a].x)
				form_curr_loc[a].x += int(float(form_start_loc[a].x + 20 - form_curr_loc[a].x) / 20);
			else
				state = CHOOSE_FORMULA;

		}
		// Draw the rest of the formulas
		for(int i = 0; i < 4; ++i)
		{
			if(a != i)
			{
				// Scale them back in
				loader.drawScaled(drawer.getBackBuffer(), un_form[i], 
								  int(form_curr_loc[i].x + (130 * (1 - scale) / 2) + 1), 
								  int(form_curr_loc[i].y + (70 * (1 - scale) / 2) + 1),
								  int(130 * scale), int(70 * scale));  
			}
		}
		// Draw the previoulsy selected formula
		loader.draw(drawer.getBackBuffer(), form[a], form_curr_loc[a].x, form_curr_loc[a].y);  

		int x_loc = 310;
		// Scale away, scale away, scale away
		for(i = 0; i < NUM_VAR; ++i)
		{
			if(i != var_to_ignore)
			{
				// Draw the variables
				loader.drawScaled(drawer.getBackBuffer(), variable[i], 
								  int(x_loc + (30 * (scale) / 2)), 
								  int(200 + (30 * (scale) / 2)),
								  int(30 * (1 - scale) - 4), int(30 * (1 - scale) - 4));  
				x_loc += 50;
			}
		}


	}

	// Input buffering
	for(int i = 0; i < 256; ++i)
	{
		// Reset the counter to zero if the key isn't being pressed
		if(!GetAsyncKeyState(i))
		{
			key_press[i] = 0;
		}
		else
			++key_press[i];
	}															

	// Buh-bye lady, I love ya! (Am I the only 28 year old who still watches Animaniacs?)
	if(GetAsyncKeyState(VK_ESCAPE))
	{
		return false;
	}
	
	// If it hasn't been 20 ms, wait.
	while((GetTickCount() - start_time) < 20) { } 
	
	//	Moves the backbuffer to the front.
	drawer.renderNextFrame();
	return true;
}

//	GameShutdown : Shutdown all Game Components.
void Game::GameShutdown(void)
{
}


// A function for finding the number of significant digits to the left of the decimal point
int find(float a)
{
	int i = 0;
	while(true)
	{
		if(!int(a / pow(10, i)))
		{
			return i;	
		}
		++i;
	}
}




