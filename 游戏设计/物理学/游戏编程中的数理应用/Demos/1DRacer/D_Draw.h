
#ifndef _D_DRAW_H_
#define _D_DRAW_H_

#include <ddraw.h>

#pragma comment (lib, "ddraw.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")

// 16 bit 5.6.5 RGB color "rrrrrggggggbbbbb"
// 11111000 = 248, 11111100 = 252
// take 5 bits of b ((b&248)>>3) +
// take 6 bits of g ((g&252)>>2) (shifted over 5) +
// take 5 bits of r ((r&248)>>3) (shifted over 11)
#ifndef RGB16_565
#define RGB16_565(r,g,b) (((b&248)>>3)+((g&252)<<3)+((r&248)<<8))
#endif

// 16 bit 5.5.5 RGB color "xrrrrrgggggbbbbb"
// 11111000 = 248
// take 5 bits of b ((b&248)>>3) +
// take 5 bits of g ((g&248)>>3) (shifted up 5) +
// take 5 bits of r ((r&248)>>3) (shifted up 10)
#ifndef RGB16_555
#define RGB16_555(r,g,b) (((b&248)>>3)+((g&248)<<2)+((r&248)<<7))
#endif

// D_Draw : DirectDraw class
class D_Draw
{
	private:

		// State values for the D_Draw system
		enum { NOT_INIT = 0, INIT_FS, INIT_W };

		HWND main_hWnd;						// Window Handle
		bool window_active;                // Active flag for the window

		int state;                         // NOT_INIT -> Not Initialized
										  // INIT_FS -> Fullscreen
										  // INIT_W -> Windowed
		int mode16Bit;                     // stores 16 Bit pixel format
										  // 0=565, 1=555, -1=Unknown
		LPDIRECTDRAW7 dd_object;           // DD object
		DDSURFACEDESC2 dd_description;     // DD surface description
		LPDIRECTDRAWSURFACE7 dd_primary;              // DD primary surface
		LPDIRECTDRAWSURFACE7 dd_back;                 // DD back surface
		DDBLTFX dd_blt_flags;              // Blt Flags for fills
		LPDIRECTDRAWCLIPPER dd_clipper;              // DD clipper for backbuffer
		LPDIRECTDRAWCLIPPER dd_wclipper;             // DD clipper for window (windowed mode)

		RECT client_rect;                  // client area (windowed mode)
	public:
		// D_Draw : Constructor for DirectDraw setup
		D_Draw ();

		// ~D_Draw : Destructor for DirectDraw setup
		virtual ~D_Draw ();

		// init : initialization routine for DirectDraw
		bool init (HWND hwnd, int screen_width, int screen_height, bool fullscreen = true);

		// shutdown : shutdown routine for DirectDraw
		void shutdown (void);

		// getDDObject : accessor to the main DirectDraw object
		LPDIRECTDRAW7 getDDObject () { return dd_object; }

		// getBackBuffer : accessor to backbuffer surface
		LPDIRECTDRAWSURFACE7 getBackBuffer () { return dd_back; }

		// fillBackBuffer : fills the back rect to specified color
		bool fillBackBuffer (int red = 0, int green = 0, int blue = 0);

		// fillRect : draw a rectangle onto the backbuffer
		void fillRect (RECT &r, int red, int green, int blue);

		// notifyActivate : for windowed apps only, must be called
		//on WM_ACTIVATE message
		void notifyActivate (WPARAM wparam);

		// notifyResize : for windowed apps only, must be called
		//  on WM_SIZE and WM_MOVE messages
		void notifyAttributes ();

		// renderNextFrame : renders the backbuffer to the screen
		bool renderNextFrame ();

		// clipSurface : creates a clipper around a surface and attaches it to the surface
		bool clipSurface (LPDIRECTDRAWSURFACE7 surface, LPDIRECTDRAWCLIPPER *clipper);

		// getMode16Bit : returns the type of 16 bit pixel arrangement on the video card
		int getMode16Bit () { return mode16Bit; }
		
		void drawText( HFONT hFont, char* strText, int originX, int originY,
					   COLORREF crBack, COLORREF crFore );
};

#endif
