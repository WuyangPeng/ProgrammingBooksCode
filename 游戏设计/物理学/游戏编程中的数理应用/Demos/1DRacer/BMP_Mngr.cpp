
#include "BMP_Mngr.h"
#include <stdio.h>

// BMP_Mngr : constructor for the BmpManager class
BMP_Mngr::BMP_Mngr()
{
   // clear all cache data
   numCache = 0;
   for(int index = 0; index < MAX_BITMAPS; index++) 
   {
      strcpy(cache[ index ].name, "" );
      cache[ index ].surface = NULL;
      cache[ index ].width = cache[ index ].height = 0;
   }
}

// BMP_Mngr : destructor for the BmpManager class
BMP_Mngr::~BMP_Mngr()
{
   // release all bitmaps
   clear();
}

// init : initialization for the BmpManager system
int BMP_Mngr::init( LPDIRECTDRAW7 ddObject, HWND hwnd )
{
   if( !ddObject || !hwnd )
      return 0;

   drawObject = ddObject;
   hWnd = hwnd;
   memset (&bltFX, 0, sizeof (bltFX));
   bltFX.dwSize = sizeof (bltFX);
   return 1;
}

// load : loads a bitmap into our manager
int BMP_Mngr::load (char *filename)
{
   int index;

   // validate reference
   if( !fileExists( filename ) )
   {
      char buf[128];
      sprintf (buf, "'%s' : The filename path could not be located.", filename);
      MessageBox (hWnd, buf,
                  "BMP_Mngr::load error", MB_OK);
      return INVALID_BITMAP;
   }

   int opening = -1; // the first opening (if necessary)
   // check for previous instance of same bitmap
   for( index = 0; index < (int)numCache; index++)
   {
      // if there is an empty space where something has been unloaded
      // we may want to load into this position
      if (stricmp (cache[ index ].name, "") == 0)
         if (opening == -1) opening = index; // store the first opening
      
      // check to see if that image is the same file we are looking for
      if( stricmp(cache[ index ].name, filename ) == 0 )
         // we already have a loaded copy of the file
         return index;
   }

   // if we didn't find it...
   if (index == (int)numCache)
   {
      // if we have an opening, use it
      if (opening != -1) 
         index = opening;
      
      else
      // if we have reached the limit of the max size - post an error message
      if ((int)numCache == (MAX_BITMAPS-1))
      {
         MessageBox (hWnd, "Reached max cache size, increase MAX_BITMAP limit",
                     "ERROR", MB_OK);
         return INVALID_BITMAP;
      }
   }

   // Load the bitmap
   if( !loadBmpToStruct (filename, drawObject, cache[index])) 
   {
      // return a failed attempt (-1)
      return INVALID_BITMAP;
   }

   // copy the filename and use it caching puposes later on
   strcpy(cache[ index ].name, filename );
   // note that there is no key color until one is set
   cache[index].useKeyColor = false;

   // we have to expand our cache
   if( index == (int)numCache )
      numCache++;

   // return the bitmap ID number
   return index;
}

// loadBmpToStruct : loads a .bmp file and puts it in a BmpFile struct
int BMP_Mngr::loadBmpToStruct (const char *filename, LPDIRECTDRAW7 ddObject, BmpFile &bmpFile)
{
   HBITMAP        hbm;
   HDC            imageHDC, surfaceHDC;
   BITMAP         bm;
   DDSURFACEDESC2 ddsd;

   // make sure that we have valid parameters
   if (!filename || !ddObject) return 0;

   // load the file into a HBITMAP
   if (!(hbm = (HBITMAP) LoadImage(NULL, filename, IMAGE_BITMAP, 0, 0,
                             LR_LOADFROMFILE | LR_CREATEDIBSECTION)))
   {
      char buf[128];
      sprintf (buf, "Unable to load %s, file may be corrupt.", filename);
      MessageBox (hWnd, buf, "BMP_Mngr::load error", MB_OK);
      return 0;
   }

   // Create a DirectDrawSurface for this bitmap
   memset (&ddsd, 0, sizeof(ddsd));
   ddsd.dwSize = sizeof(ddsd);

   ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
   ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;

   // Get size of the bitmap
   GetObject(hbm, sizeof(bm), &bm);
   ddsd.dwWidth  = bmpFile.width  = bm.bmWidth;
   ddsd.dwHeight = bmpFile.height = bm.bmHeight;
   
   if(FAILED (ddObject->CreateSurface(&ddsd, &bmpFile.surface, NULL)))
   {
      MessageBox (hWnd, "Unable to create bmp surface, out of memory?", "ERROR", MB_OK);
      return 0;
   }

   // put the HBITMAP into a memory DC for Blt
   imageHDC = CreateCompatibleDC (NULL);
   SelectObject (imageHDC, hbm);

   // get our DDSURFACE hdc and perform Blt
   bmpFile.surface->GetDC (&surfaceHDC);
   BitBlt(surfaceHDC, 0, 0, bmpFile.width, bmpFile.height, imageHDC, 0, 0, SRCCOPY);
   bmpFile.surface->ReleaseDC (surfaceHDC);

   // release temporary resources
   DeleteDC (imageHDC);
   DeleteObject(hbm);

   // all is well.
   return 1;
}

// fileExists : searches for a filename path.
bool BMP_Mngr::fileExists (char *filename)
{
   // validate string
   if( !filename || !strlen(filename) )
      return FALSE;

   // try to open the file
   FILE *fp = fopen(filename, "rb");
   if( fp == NULL ) return FALSE;

   // clean up and return OK status
   fclose( fp );
   return TRUE;
}

// setKeyColor : sets the key color for a given int
bool BMP_Mngr::setKeyColor(int graphicID, int tR, int tG, int tB)
{
   DDSURFACEDESC2 ddsd;

   // return if the desired int is not loaded/valid
   // make sure we are in array bounds
   if( graphicID < 0 || graphicID >= (int)numCache )
      return false;

   // only if that imageID has a surface
   if (cache[graphicID].surface)
   {
      // now we need to know the bit depth of the surface (5.5.5 or 5.6.5 or other)
      // loading fails if not either 5.5.5 or 5.6.5
      memset (&ddsd, 0, sizeof (ddsd));
      ddsd.dwSize = sizeof (ddsd);
      cache[graphicID].surface ->GetSurfaceDesc (&ddsd);
      // test the description
      if (ddsd.ddpfPixelFormat.dwRGBBitCount == 16)
      {
         // 5.5.5 bit arrangement
         if ((ddsd.ddpfPixelFormat.dwGBitMask >> 5) != 63)
         {
            // set User-Defined transparency to specified color
            DDCOLORKEY color_key;
            color_key.dwColorSpaceLowValue = RGB16_555 (tR, tG, tB);
            color_key.dwColorSpaceHighValue = color_key.dwColorSpaceLowValue;
            cache[graphicID].surface->SetColorKey (DDCKEY_SRCBLT, &color_key);
         }

         // 5.6.5 bit arrangement
         else
         {
            // set User-Defined transparency to specified color
            DDCOLORKEY color_key;
            color_key.dwColorSpaceLowValue = RGB16_565 (tR, tG, tB);
            color_key.dwColorSpaceHighValue = color_key.dwColorSpaceLowValue;
            cache[graphicID].surface->SetColorKey (DDCKEY_SRCBLT, &color_key);
         }

         // successful
         cache[graphicID].useKeyColor = true;
         return true;
      }
   }

   // unable to set key color
   return false;
}

// loadWithKeyColor : combines load and setKeyColor for convenience
int BMP_Mngr::loadWithKeyColor (char *filename, int tR, int tG, int tB)
{
   int handle;
   if ((handle = load (filename)) == INVALID_BITMAP) return handle;
   setKeyColor (handle, tR, tG, tB);
   return handle;
}

// draw : perform a standard surface blit of this graphic to the specified destination buffer
void BMP_Mngr::draw (LPDIRECTDRAWSURFACE7 destBuffer, int graphicID, int dx, int dy)
{
   // make sure we are in array bounds
   if( graphicID < 0 || graphicID >= (int)numCache || !destBuffer)
      return;

   // draw if that imageID has a surface
   if (cache[graphicID].surface)
   {
      // build the dwFlags for type of blt
      dwFlags = DDBLT_WAIT;
      if (cache[graphicID].useKeyColor) dwFlags |= DDBLT_KEYSRC;
         
	  bltParam = NULL;

      // fill in the source RECT
      sourceRect.left = 0;
      sourceRect.top = 0;
      sourceRect.right = cache[graphicID].width;
      sourceRect.bottom = cache[graphicID].height;

      // fill in the destination RECT
      destRect.left = dx;
      destRect.top = dy;
      destRect.right = dx + cache[graphicID].width;
      destRect.bottom = dy + cache[graphicID].height;

      // let the hardware take care of the rest
      destBuffer->Blt (&destRect, cache[graphicID].surface,
                       &sourceRect, dwFlags, bltParam);
   }
}

// drawScaled : perform a scaled surface blit of this graphic to the specified destination buffer
void BMP_Mngr::drawScaled (LPDIRECTDRAWSURFACE7 destBuffer, int graphicID, int dx, int dy, int dw, int dh)
{
   // make sure we are in array bounds
   if( graphicID < 0 || graphicID >= (int)numCache || !destBuffer)
      return;

   // draw if that imageID has a surface
   if (cache[graphicID].surface)
   {
      // build the dwFlags for type of blt
      dwFlags = DDBLT_WAIT;
      if (cache[graphicID].useKeyColor) dwFlags |= DDBLT_KEYSRC;
         
      bltParam = NULL;

      // fill in the source RECT
      sourceRect.left = 0;
      sourceRect.top = 0;
      sourceRect.right = cache[graphicID].width;
      sourceRect.bottom = cache[graphicID].height;

      // fill in the destination RECT
      destRect.left = dx;
      destRect.top = dy;
      destRect.right = dx + dw;
      destRect.bottom = dy + dh;

      // let the hardware take care of the rest
      destBuffer->Blt (&destRect, cache[graphicID].surface,
                       &sourceRect, dwFlags, bltParam);
   }
}

// drawSection : blit a section of this graphic
void BMP_Mngr::drawSection (LPDIRECTDRAWSURFACE7 destBuffer, int graphicID,
                            int sx, int sy, int sw, int sh, int dx, int dy)
{
   // make sure we are in array bounds
   if( graphicID < 0 || graphicID >= (int)numCache || !destBuffer)
      return;

   // draw if that imageID has a surface
   if (cache[graphicID].surface)
   {
      // build the dwFlags for type of blt
      dwFlags = DDBLT_WAIT;
      if (cache[graphicID].useKeyColor) dwFlags |= DDBLT_KEYSRC;
         
	  bltParam = NULL;

      // fill in the source RECT
      sourceRect.left = sx;
      sourceRect.top = sy;
      sourceRect.right = sx + sw;
      sourceRect.bottom = sy + sh;

      // fill in the destination RECT
      destRect.left = dx;
      destRect.top = dy;
      destRect.right = dx + sw;
      destRect.bottom = dy + sh;

      // let the hardware take care of the rest
      destBuffer->Blt (&destRect, cache[graphicID].surface,
                       &sourceRect, dwFlags, bltParam);
   }
}

// drawSectionScaled : blit a scaled section of this graphic
void BMP_Mngr::drawSectionScaled (LPDIRECTDRAWSURFACE7 destBuffer, int graphicID,
                                  int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh)
{
   // make sure we are in array bounds
   if( graphicID < 0 || graphicID >= (int)numCache || !destBuffer)
      return;

   // draw if that imageID has a surface
   if (cache[graphicID].surface)
   {
      // build the dwFlags for type of blt
      dwFlags = DDBLT_WAIT;
      if (cache[graphicID].useKeyColor) dwFlags |= DDBLT_KEYSRC;

      bltParam = NULL;

      // bound parameters to valid values
      if (sx < 0) sx = 0;  if (sw < 0) sw = 0;
      if (sx > cache[graphicID].width) sx = cache[graphicID].width;
      if ((sx + sw) > cache[graphicID].width) sw = cache[graphicID].width - sx;
      if (sy < 0) sy = 0;  if (sh < 0) sh = 0;
      if (sy > cache[graphicID].height) sy = cache[graphicID].height;
      if ((sy + sh) > cache[graphicID].height) sw = cache[graphicID].height - sy;
      if (dw < 0) dw = 0;  if (dh < 0) dh = 0;
      // fill in the source RECT
      sourceRect.left = sx;
      sourceRect.top = sy;
      sourceRect.right = sx + sw;
      sourceRect.bottom = sy + sh;

      // fill in the destination RECT
      destRect.left = dx;
      destRect.top = dy;
      destRect.right = dx + dw;
      destRect.bottom = dy + dh;

      // let the hardware take care of the rest
      destBuffer->Blt (&destRect, cache[graphicID].surface,
                       &sourceRect, dwFlags, bltParam);
   }
}

// unload : removes graphic from memory and the cache
void BMP_Mngr::unload (int graphicID)
{
   // make sure we are in array bounds
   if( graphicID < 0 || graphicID >= (int)numCache )
      return;

   // clear the filename associated to this ID number
   strcpy(cache[ graphicID ].name, "" );
   // clear the width and height information
   cache[ graphicID ].width = cache[ graphicID ].height = 0;

   // check to see if valid information has been loaded
   if(cache[ graphicID ].surface)
   {
      // unload the image data
      cache[graphicID].surface->Release ();
      cache[graphicID].surface = NULL;
   }

   // bitmap was at the end of the list so we can
   // optimize the list a little by cutting it down.
   if( graphicID == (int)(numCache-1) )
      numCache--;
}

// clear : flushes all data and releases all memory.  Called by destructor.
void BMP_Mngr::clear( void )
{
   for(int index = 0; index < (int)numCache; index++)
   {
      BmpFile *c = &cache[ index ];

      // check to see if valid information has been loaded
      if( c ->surface != NULL )
      {
         // unload the image data
         c ->surface->Release ();
         // NULL our surface pointer
         c ->surface = NULL;
      }

      // clear our bmp info
      strcpy(c->name, "" );
      c->useKeyColor = false;
      c->width = c->height = 0;
   }
}