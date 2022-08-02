
#include "D_Draw.h"
#include <stdio.h>

// D_Draw : Constructor for DirectDraw setup
D_Draw::D_Draw () 
{
	// Set initial values of private members
	main_hWnd = NULL;
	window_active = false;
	state = NOT_INIT;
	mode16Bit = -1;
	dd_object = NULL;
	dd_primary = NULL;
	dd_back = NULL;
	dd_clipper = NULL;
	dd_wclipper = NULL;
}

// ~D_Draw : Destructor for DirectDraw setup
D_Draw::~D_Draw () 
{
	shutdown();
}

// shutdown : shutdown routine for DirectDraw
//
void D_Draw::shutdown( void )
{
	// release exclusive mode if we have it
	if (dd_object && (state == INIT_FS))
		dd_object->SetCooperativeLevel (main_hWnd, DDSCL_NORMAL);

	// release any clippers
	if(dd_clipper)
	{
		dd_clipper ->Release();
		dd_clipper = NULL;
	}

	if(dd_wclipper)
	{
		dd_wclipper ->Release();
		dd_wclipper = NULL;
	}

	// release the back_buffer
	if (dd_back)
	{
		dd_back->Release();
		dd_back = NULL;
	}

	// release the primary surface
	if (dd_primary)
	{
		dd_primary->Release();
		dd_primary = NULL;
	}

	// release the DD Object
	if (dd_object)
	{
		dd_object->Release ();
		dd_object = NULL;
	}

	// NULL the pointers not to be messed with
	main_hWnd = NULL;
	window_active = false;
	state = NOT_INIT;
	mode16Bit = -1;
}


// init : initialization routine for DirectDraw
bool D_Draw::init (HWND hwnd, int screen_width, int screen_height, bool fullscreen)
{
	// create main DirectDraw Object
	if (FAILED (DirectDrawCreateEx (NULL, (void**)&dd_object, IID_IDirectDraw7, NULL)))
	{
		MessageBox (hwnd, 
		"Failed to Create DirectDraw Object.",
		"D_Draw::init error", MB_OK);
		return false;
	}

	// pick type of cooperation level based on fullscreen status
	unsigned long cooperationFlags;
	cooperationFlags = (fullscreen) 
	? DDSCL_ALLOWMODEX | DDSCL_FULLSCREEN | DDSCL_EXCLUSIVE | DDSCL_ALLOWREBOOT
	: DDSCL_NORMAL;

	// attempt to set a cooperative level
	if (FAILED (dd_object->SetCooperativeLevel (hwnd, cooperationFlags)))
	{
		MessageBox (hwnd, 
		"Failed to Set DirectDraw Cooperation Level.\nMake sure you are passing a valid HWND to init.",
		"ERROR", MB_OK);
		if (dd_object) dd_object->Release ();
		return false;
	}

	// store the window handle - at this point we know it is valid
	main_hWnd = hwnd;

	// if we are trying to set fullscreen, we need to set
	// the monitor to a fullscreen mode and to 16 bpp
	if (fullscreen)
		if (FAILED (dd_object->SetDisplayMode (screen_width, screen_height, 16, 0, 0)))
		{
			char buf[128];
			sprintf (buf,
			"Failed to Set DirectDraw Display Mode.\nVideo mode %dx%dx16 not valid on this display.");
			MessageBox (hwnd, buf, "ERROR", MB_OK);
			shutdown ();
			return false;
		}

	// clear the description struct
	memset (&dd_description, 0, sizeof (dd_description));
	dd_description.dwSize = sizeof (dd_description);
	// set the desired primary surface flags for either fullscreen or windowed
	if (fullscreen)
	{
		dd_description.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		dd_description.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		dd_description.dwBackBufferCount = 1;
	}
	else
	{
		dd_description.dwFlags = DDSD_CAPS;
		dd_description.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	}

	// create the primary surface
	if (FAILED (dd_object->CreateSurface (&dd_description, &dd_primary, NULL)))
	{
		MessageBox (hwnd, "Failed to Create DirectDraw Primary Surface.\n", "ERROR", MB_OK);
		shutdown ();
		return false;
	}

	// if in windowed mode, we check to see if the primary surface (desktop)
	// is 16-bit.  If not we can't continue.
	memset (&dd_description, 0, sizeof (dd_description));
	dd_description.dwSize = sizeof (dd_description);
	dd_primary->GetSurfaceDesc (&dd_description);

	if (!(dd_description.ddpfPixelFormat.dwRGBBitCount == 16))
	{
		MessageBox (hwnd, "Windowed Mode requires desktop at 16-bit color.\n", "ERROR", MB_OK);
		shutdown ();
		return false;
	}
	else
	{
		// store the kind of 16 bit format of the video card
		if ((dd_description.ddpfPixelFormat.dwGBitMask >> 5) == 63)
			mode16Bit = 0; // 5.6.5 RGB
		else
			mode16Bit = 1; // 5.5.5 RGB
	}

	// now create the backbuffer.  It should already be attached in
	// fullscreen, we have to make it seperately for windowed
	if (fullscreen)
	{							 
		DDSCAPS2 ddscaps;
		memset( &ddscaps, 0, sizeof( ddscaps ));
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		if (FAILED (dd_primary->GetAttachedSurface (&ddscaps,&dd_back)))
		{
			MessageBox (hwnd, "Failed to Create DirectDraw BackBuffer Surface.\n", "ERROR", MB_OK);
			shutdown ();
			return false;
		}
	}
	else
	{
		memset (&dd_description, 0, sizeof (dd_description));
		dd_description.dwSize = sizeof (dd_description);
		// we need fields for caps, width, and height
		dd_description.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
		// set the size of our backbuffer to our window area
		dd_description.dwHeight = screen_height;
		dd_description.dwWidth = screen_width;
		// offscreen plain surface
		dd_description.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		// create the backbuffer
		if (FAILED (dd_object->CreateSurface (&dd_description, &dd_back,
										NULL)))
		{
			MessageBox (hwnd, "Failed to Create DirectDraw BackBuffer Surface.\n", "ERROR", MB_OK);
			shutdown ();
			return false;
		}
	}

	// clip the backbuffer surface - store our clipper in dd_clipper
	if (!clipSurface (dd_back, &dd_clipper))
		return false;

	// add a window clipper if we are in windowed mode
	if (!fullscreen)
	{
		if (FAILED ((dd_object->CreateClipper(0,&dd_wclipper,NULL))))
		{
			MessageBox (hwnd, "Failed to Create DirectDraw Window Clipper.\n", "ERROR", MB_OK);
			shutdown ();
			return false;
		}
		if (FAILED (dd_wclipper->SetHWnd (0, main_hWnd)))
		{
			MessageBox (hwnd, "Failed to Set DirectDraw Window Clipper HWnd.\n","ERROR", MB_OK);
			shutdown ();
			return false;
		}
		if (FAILED ((dd_primary->SetClipper (dd_wclipper))))
		{
			MessageBox (hwnd, "Failed to Set DirectDraw Window Clipper to Primary Surface.\n",
				"ERROR", MB_OK);
			shutdown ();
			return false;
		}
	}


	// successfully initialized DirectDraw.
	// set state and return true
	state = (fullscreen) ? INIT_FS : INIT_W;

	// activate the window
	ShowWindow (main_hWnd, SW_SHOWNORMAL);
	UpdateWindow (main_hWnd);
	window_active = true;

	// update location of the window locally if need be
	if (!fullscreen) 
		notifyAttributes ();

	return true;
}

// clipSurface : creates a clipper around a surface and attaches it to the surface
bool D_Draw::clipSurface (LPDIRECTDRAWSURFACE7 surface, LPDIRECTDRAWCLIPPER *clipper)
{
   // make sure the surface is valid
   if (!surface)
   {
      MessageBox (main_hWnd,
         "NULL Surface, cannot attach clipper.\n",
         "D_Draw::clipSurface error", MB_OK);
      return false;
   }

   // create clipper object
   if (FAILED ((dd_object->CreateClipper(0, clipper, NULL))))
   {
      MessageBox (main_hWnd,
         "Failed to Create Clipper.\n",
         "D_Draw::clipSurface error", MB_OK);
      return false;
   }

   // create a region data struct to hold clip info
   LPRGNDATA clipinfo;
   clipinfo = (LPRGNDATA) malloc (sizeof(RGNDATAHEADER) + sizeof (RECT));

   // create clip list rectangle
   RECT clipregion;
   clipregion.left = clipregion.top = 0;
   DDSURFACEDESC2 surface_desc;
   memset (&surface_desc, 0, sizeof (surface_desc));
   surface_desc.dwSize = sizeof (surface_desc);
   if (FAILED (surface->GetSurfaceDesc (&surface_desc)))
   {
      MessageBox (main_hWnd,
         "Failed to Get Surface Description.\n",
         "D_Draw::clipSurface error", MB_OK);
      free (clipinfo);
      return false;
   }
   clipregion.right = surface_desc.dwWidth;
   clipregion.bottom = surface_desc.dwHeight;

   // fill in its fields
   memcpy(clipinfo->Buffer, &clipregion, sizeof(RECT));
   clipinfo->rdh.dwSize = sizeof (RGNDATAHEADER);
   clipinfo->rdh.iType = RDH_RECTANGLES;
   clipinfo->rdh.nCount = 1;
   clipinfo->rdh.nRgnSize = sizeof (RECT);
   clipinfo->rdh.rcBound = clipregion;

   // set the clipping information
   if (FAILED((*clipper)->SetClipList(clipinfo, 0)))
   {
      MessageBox (main_hWnd,
         "Failed to Set the Clip List.\n",
         "D_Draw::clipSurface error", MB_OK);
      free (clipinfo);
      return false;
   }

   // attach the clipper to the surface
   if (FAILED(surface->SetClipper(*clipper)))
   {
      MessageBox (main_hWnd, 
         "Failed to Set the Surface Clipper.\n",
         "D_Draw::clipSurface error", MB_OK);
      free (clipinfo);
      return false;
   }

   // clipping successful
   free (clipinfo);
   return true;
}

// fillBackBuffer : fills the back rect to specified color
bool D_Draw::fillBackBuffer (int red, int green, int blue)
{
   if (dd_back == NULL)
      return false;

   // clear out the blt flags
   memset (&dd_blt_flags, 0, sizeof (dd_blt_flags));
   dd_blt_flags.dwSize = sizeof (dd_blt_flags);

   // create the proper color, using the mode16Bit
   int color;
   if (mode16Bit == 0)
      // 5.6.5
      color = RGB16_565 (red, green, blue);
   else if (mode16Bit == 1)
      // 5.5.5
      color = RGB16_555 (red, green, blue);
   else
      return false; // 16 bit mode not determined

   // set the color and Blt it
   dd_blt_flags.dwFillColor = color;
   dd_back->Blt (NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT,
                 &dd_blt_flags);

   // we ok
   return true;
}

// fillRect : draw a rectangle onto the backbuffer
void D_Draw::fillRect (RECT &r, int red, int green, int blue)
{
   if (dd_back == NULL)
      return;

   // clear out the blt flags
   memset (&dd_blt_flags, 0, sizeof (dd_blt_flags));
   dd_blt_flags.dwSize = sizeof (dd_blt_flags);

   // create the proper color, using the mode16Bit
   int color;
   if (mode16Bit == 0)
      // 5.6.5
      color = RGB16_565 (red, green, blue);
   else if (mode16Bit == 1)
      // 5.5.5
      color = RGB16_555 (red, green, blue);
   else
      return; // 16 bit mode not determined

   // set the color and Blt it
   dd_blt_flags.dwFillColor = color;
   dd_back->Blt (&r, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT,
                 &dd_blt_flags);
}

// notifyActivate : for windowed apps only, must be called
//					on WM_ACTIVATE message
void D_Draw::notifyActivate (WPARAM wparam)
{
   // only once window is initialized do we worry about this
   if (state == NOT_INIT) return;
   // our windowed app is becoming active or inactive
   int cond = LOWORD (wparam);
   // test to see what's happening
   if ((cond == WA_ACTIVE) || (cond == WA_CLICKACTIVE))
      // active
      window_active = true;
   else
      // inactive
      window_active = false;
}

// notifyAttributes : for windowed apps only, must be called
//					  on WM_SIZE and WM_MOVE messages
void D_Draw::notifyAttributes ()
{
   // only once window is initialized do we worry about this
   if (state == NOT_INIT) return;
   // get the location of the window
   // and store it locally
   GetClientRect (main_hWnd, &client_rect);
   POINT topleft, bottomright;
   topleft.x = client_rect.left;
   topleft.y = client_rect.top;
   bottomright.x = client_rect.right;
   bottomright.y = client_rect.bottom;
   ClientToScreen (main_hWnd, &topleft);
   ClientToScreen (main_hWnd, &bottomright);
   client_rect.left = topleft.x;
   client_rect.top = topleft.y;
   client_rect.right = bottomright.x;
   client_rect.bottom = bottomright.y;
}


// renderNextFrame : renders the backbuffer to the screen
bool D_Draw::renderNextFrame () 
{
   if (window_active)
   {
      switch (state)
      {
         case INIT_W:
         {
         // let the hardware take care of the rest
         dd_primary->Blt (&client_rect, dd_back, NULL,
                          DDBLT_WAIT, NULL);
         return true;
         } break;

         case INIT_FS:
         {
         // page flip for double buffering
         while (dd_primary->Flip (NULL, DDFLIP_WAIT) != DD_OK);

         return true;
         } break;

         case NOT_INIT:
         default:
         {
         // sorry, not initialized
         return false;
         } break;
      }
   }
   // return false, window was not active
   return false;
}
void D_Draw::drawText( HFONT hFont, char* strText, int originX, int originY,
                       COLORREF crBack, COLORREF crFore )
{
    HDC hDC = NULL;

    // Make sure this surface is restored.
//    getBackBuffer()->Restore();

    getBackBuffer()->GetDC(&hDC);

    // Set the background and foreground color
	if(crBack)
	    SetBkColor(hDC, crBack);
	else
		SetBkMode(hDC, TRANSPARENT);

    SetTextColor(hDC, crFore);

    if(hFont)
        SelectObject(hDC, hFont);

    // Use GDI to draw the text on the surface
    TextOut(hDC, originX, originY, strText, strlen(strText));

    getBackBuffer()->ReleaseDC(hDC);

}
