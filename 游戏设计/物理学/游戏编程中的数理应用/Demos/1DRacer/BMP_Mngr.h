
#ifndef _BMP_MNGR_H_
#define _BMP_MNGR_H_

#include "D_Draw.h"

// BMP_Mngr : Bmp File Loader and Renderer class
class BMP_Mngr
{
public:

   // MAX_BITMAPS could be altered accordingly to your game
   enum { INVALID_BITMAP = -1, MAX_BITMAPS = 256 };

private:

   // store the DirectDraw object and HWND
   LPDIRECTDRAW7 drawObject;
   HWND hWnd;

   // structures used in the draw
   RECT sourceRect, destRect;
   DDBLTFX bltFX, *bltParam;
   DWORD dwFlags;

   // information about the bitmap file
   struct BmpFile
   {
      char name[64]; // name of the file
      LPDIRECTDRAWSURFACE7 surface; // memory surface of the bitmap
      int width, height;			// width and height of the bitmap
      bool useKeyColor;				// false if no key color specified, true if specified
   };

   // our BmpFile array
   BmpFile        cache[MAX_BITMAPS];
   unsigned int   numCache;

   // fileExists : searches for a filename path.
   bool fileExists (char *filename);

   // loadBmpToStruct : loads a .bmp file and puts it in a BmpFile struct
   int loadBmpToStruct (const char *filename, LPDIRECTDRAW7 ddObject,
                        BmpFile &bmpFile);

public:

   // BMP_Mngr : constructor for the BmpManager class
   BMP_Mngr ();

   // BMP_Mngr : destructor for the BmpManager class
   ~BMP_Mngr ();

   // init : initialization for the BmpManager system
   int               init (LPDIRECTDRAW7 ddObject, HWND hwnd);

   // load : loads a bitmap into our manager
   int load (char *filename);

   // setKeyColor : sets the key color for a given int
   bool setKeyColor (int graphicID, int tR = 0, int tG = 0, int tB = 0);

   // loadWithKeyColor : combines load and setKeyColor for convenience
   int loadWithKeyColor (char *filename, int tR = 0, int tG = 0, int tB = 0);

   // draw : perform a standard surface blit of this graphic to the specified destination buffer
   void draw (LPDIRECTDRAWSURFACE7 destBuffer, int graphicID, int dx, int dy);

   // drawScaled : perform a scaled surface blit of this graphic
   //              to the specified destination buffer
   void drawScaled (LPDIRECTDRAWSURFACE7 destBuffer, int graphicID, int dx, int dy, int dw, int dh);

   // drawSection : blit a section of this graphic to the specified destination buffer
   void drawSection (LPDIRECTDRAWSURFACE7 destBuffer, int graphicID,
                     int sx, int sy, int sw, int sh, int dx, int dy);

   // drawSectionScaled : blit a scaled section of this graphic to the specified destination buffer
   void drawSectionScaled (LPDIRECTDRAWSURFACE7 destBuffer, int graphicID,
                           int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh);

   // getWidth : return the width (in pixels) of a cached bmp
   int getWidth (int graphicID)
   {
      if( graphicID < 0 || graphicID >= (int)numCache) return 0;
      return cache[graphicID].width;
   }

   // getHeight : return the height (in pixels) of a cached bmp
   int getHeight (int graphicID)
   {
      if( graphicID < 0 || graphicID >= (int)numCache) return 0;
      return cache[graphicID].height;
   }

   // unload : removes graphic from memory and the cache
   void unload (int graphicID);

   // clear : flushes all data and releases all memory.  Called by destructor.
   void clear (void);
};

#endif