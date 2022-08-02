/*
	srgp_input_WIN.c

	input functions specific for MS Windows.

*/

#include "srgplocal.h"
#include <ctype.h>
#include <string.h>

static int currentDevice = NO_DEVICE;
int windowInit = 0;
boolean screenRepaintNeeded = FALSE;

void
SRGP__initInputDrivers()
{
}


/** RAW-LEVEL DEACTIVATION OF A DEVICE
Responsible for erasing echo, and resetting device's measure to the
	hardwired default.
Upon entry, the device's cur_mode is its old value (has not been
	changed yet)!  And this procudure does not change it!
**/


void
SRGP__deactivateDevice (int device)
{

	switch (device) {

		case LOCATOR:
			SRGP__disableLocatorRubberEcho();
			SRGP__disableLocatorCursorEcho();
			srgp__cur_locator_measure.position =
				SRGP_defPoint(srgp__canvasTable[0].max_xcoord>>1,
							  srgp__canvasTable[0].max_ycoord>>1);
			ShowCursor(FALSE);

			break;

		case KEYBOARD:
			SRGP__disableKeyboardEcho();
			srgp__cur_keyboard_measure.buffer[0] = '\0';
			bzero (srgp__cur_keyboard_measure.modifier_chord,
				   sizeof(srgp__cur_keyboard_measure.modifier_chord));

			break;
	}
}

/** RAW-LEVEL ACTIVATION OF A DEVICE
Called whenever:
	a device is placed into EVENT or SAMPLE mode...
	a) when previously inactive
	b) when previously active but in a different mode
Responsible for initiating echo...
Upon entry, the device's echo info and mode has already been set
to their new values.
**/

void
SRGP__activateDevice (int device)
{
	switch (device) {
		case LOCATOR:
			SRGP__disableLocatorCursorEcho();
			SRGP__disableLocatorRubberEcho();
			SRGP__enableLocatorCursorEcho();
			SRGP__enableLocatorRubberEcho();
			ShowCursor (TRUE);
			break;
		case KEYBOARD:
			SRGP__enableKeyboardEcho();
			break;
	}
}


void
SRGP__updateRawCursorPosition()
{
	POINT position;

	position.x = srgp__cur_locator_measure.position.x;
	position.y = SCREENFIXED(srgp__cur_locator_measure.position.y);

	srgp__cur_Xcursor_x = position.x;
	srgp__cur_Xcursor_y = position.y;

	ClientToScreen(srgp__curActiveCanvasSpec.drawable.xid, &position);
	SetCursorPos(position.x, position.y);
	SRGP__updateLocatorRubberEcho();
}

void HandleWinButtonEvent (WORD wParam, LONG lParam)
{
	int i;

	srgpx__cur_time = GetMessageTime();
	srgp__cur_locator_measure.position.x = LOWORD(lParam);
	srgp__cur_locator_measure.position.y =
		SCREENFIXED(HIWORD(lParam));
	if (wParam & MK_LBUTTON)
		srgp__cur_locator_measure.button_chord[LEFT_BUTTON] = DOWN;
	else srgp__cur_locator_measure.button_chord[LEFT_BUTTON] = UP;
	if (wParam & MK_MBUTTON)
		srgp__cur_locator_measure.button_chord[MIDDLE_BUTTON] = DOWN;
	else srgp__cur_locator_measure.button_chord[MIDDLE_BUTTON] = UP;
	if (wParam & MK_RBUTTON)
		srgp__cur_locator_measure.button_chord[RIGHT_BUTTON] = DOWN;
	else srgp__cur_locator_measure.button_chord[RIGHT_BUTTON] = UP;

	for (i = 0; i<3; i++)
		if (srgp__get_locator_measure.button_chord[i]
			!= srgp__cur_locator_measure.button_chord[i])
		  srgp__cur_locator_measure.button_of_last_transition = i;

	if (wParam & MK_SHIFT)
		srgp__cur_locator_measure.modifier_chord[SHIFT] = DOWN;
	else srgp__cur_locator_measure.modifier_chord[SHIFT] = UP;
	if (wParam & MK_CONTROL)
		srgp__cur_locator_measure.modifier_chord[CONTROL] = DOWN;
	else srgp__cur_locator_measure.modifier_chord[CONTROL] = UP;
	if (GetKeyState(VK_MENU) < 0)
		srgp__cur_locator_measure.modifier_chord[META] = DOWN;
	else srgp__cur_locator_measure.modifier_chord[META] = UP;

	if ((srgp__cur_mode[LOCATOR] == EVENT) &&
		((srgp__cur_locator_button_mask
		  >> srgp__cur_locator_measure.button_of_last_transition) & 1)) {
		srgp__get_locator_measure = srgp__cur_locator_measure;
		currentDevice = LOCATOR;
	} else currentDevice = NO_DEVICE;

}

/* <not finished> */
void HandleRawModeKeyEvent (WORD wParam, LONG lParam)
{
	srgpx__cur_time = GetMessageTime();
	srgp__cur_keyboard_measure.buffer[0] = wParam;
	srgp__cur_keyboard_measure.buffer[1] = '\0';
	if (GetKeyState(VK_SHIFT) < 0)
		srgp__cur_keyboard_measure.modifier_chord[SHIFT] = DOWN;
	else srgp__cur_keyboard_measure.modifier_chord[SHIFT] = UP;
	if (GetKeyState(VK_CONTROL) < 0)
		srgp__cur_keyboard_measure.modifier_chord[CONTROL] = DOWN;
	else srgp__cur_keyboard_measure.modifier_chord[CONTROL] = UP;
	if (GetKeyState(VK_MENU) < 0)
		srgp__cur_keyboard_measure.modifier_chord[META] = DOWN;
	else srgp__cur_keyboard_measure.modifier_chord[META] = UP;
	strcpy (srgp__get_keyboard_measure.buffer,
			 srgp__cur_keyboard_measure.buffer);
	bcopy (srgp__cur_keyboard_measure.modifier_chord,
		   srgp__get_keyboard_measure.modifier_chord,
		   sizeof(srgp__get_keyboard_measure.modifier_chord));
	srgp__get_keyboard_measure.position =
    	srgp__cur_keyboard_measure.position;
}

/* <not finished> */
void HandleProcModeKeyEvent (WORD wParam, LONG lParam)
{

	switch (wParam) {
		case VK_RETURN:
			if (srgp__cur_mode[KEYBOARD] != EVENT) {
				srgp__cur_keyboard_measure.buffer[0] = '\0';
				srgp__cur_keyboard_measure_length = 0;
				SRGP__updateKeyboardEcho();
			}
			break;

		case VK_BACK:
			if (srgp__cur_keyboard_measure_length > 0) {
				srgp__cur_keyboard_measure_length -= 1;
				srgp__cur_keyboard_measure.buffer
					[srgp__cur_keyboard_measure_length] = '\0';
				SRGP__updateKeyboardEcho();
			}
			break;

		default:
			if ((isprint(wParam)) &&
				(srgp__cur_keyboard_measure_length < MAX_STRING_SIZE)) {

				srgp__cur_keyboard_measure.buffer
					[srgp__cur_keyboard_measure_length] = wParam;
				srgp__cur_keyboard_measure_length++;
				srgp__cur_keyboard_measure.buffer
					[srgp__cur_keyboard_measure_length] = '\0';
				SRGP__updateKeyboardEcho();
			}
			break;
	}
}


void CleanUpResources(void)
{
	int i;
	HDC hdc;

	hdc = GetDC (srgp__canvasTable[0].drawable.win);
	SelectObject(hdc, GetStockObject(SYSTEM_FONT));
	for (i=0; i <= MAX_FONT_INDEX; i++)
	  DeleteObject(srgp__fontTable[i]);

	ReleaseDC(srgp__canvasTable[0].drawable.win, hdc);
	SRGP__memFree();

}
 
long FAR PASCAL WndProc (HWND hWnd, unsigned Message,
						 WORD wParam, LONG lParam)
{
	RECT 	clientRect;
	int     width, height;
	unsigned int dataSeg;
	LPCREATESTRUCT newWin;
	HDC		hdc, hdcMem, hdcMem2;
	PAINTSTRUCT ps;
	HBITMAP hBitmap;
	char   msg[80];
	HBRUSH hBrush;
	HPEN   hPen;
	HRGN   hRgn;
	POINT  locPos;

	switch(Message)
	{
/*
		case WM_CREATE:
			GetClientRect(hWnd, &clientRect);
			newWin = (LPCREATESTRUCT) lParam;
			width = newWin->cx + (newWin->cx - (clientRect.right - clientRect.left));
			height = newWin->cy + (newWin->cy - (clientRect.bottom - clientRect.top));
			SetWindowPos(hWnd, NULL, 0, 0, width, height,
						 (SWP_DRAWFRAME | SWP_NOMOVE | SWP_SHOWWINDOW));


			hdc = GetDC (hwnd);

			Release (hwnd, hdc);
			break;

		case WM_PAINT:
			sprintf((char *)msg,"WndProc message #%d\n",Message);
			SRGP_trace(SRGP_logStream,msg);
			hdc = BeginPaint(hWnd, &ps);
			EndPaint (hWnd, &ps);
			srgp__canvasTable[0].drawable.win = hWnd;
			break;

*/
		case WM_PAINT:
			screenRepaintNeeded = TRUE;
			return DefWindowProc(hWnd, Message, wParam, lParam);
		case WM_MOUSEMOVE:
			SetCursor(srgp__cursorTable[srgp__cur_cursor]);
			srgp__canvasTable[0].drawable.win = hWnd;
			if (srgp__cur_mode[LOCATOR] == INACTIVE)
				break;
			srgpx__cur_time = GetMessageTime();
			srgp__cur_Xcursor_x = LOWORD(lParam);
			srgp__cur_Xcursor_y = HIWORD(lParam);
			srgp__cur_locator_measure.position.x = srgp__cur_Xcursor_x;
			srgp__cur_locator_measure.position.y =
										SCREENFIXED(srgp__cur_Xcursor_y);
			SRGP__updateLocatorRubberEcho();
			currentDevice = NO_DEVICE;
			break;

		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
			sprintf((char *)msg,"WndProc message #%d\n",Message);
			SRGP_trace(SRGP_logStream,msg);
			srgp__canvasTable[0].drawable.win = hWnd;
			if (srgp__cur_mode[LOCATOR] == INACTIVE)
				break;
			HandleWinButtonEvent (wParam, lParam);
			break;

		case WM_CHAR:
			sprintf((char *)msg,"Key pressed: %d ,WndProc message #%d\n",wParam, Message);
			SRGP_trace(SRGP_logStream,msg);
			if (srgp__cur_mode[KEYBOARD] == INACTIVE)
				break;
			GetCursorPos(&srgp__cur_keyboard_measure.position);
			ScreenToClient(hWnd, &srgp__cur_keyboard_measure.position);
			srgp__cur_keyboard_measure.position.y =
				SCREENFIXED(srgp__cur_keyboard_measure.position.y);
			if (srgp__cur_keyboard_processing_mode == RAW) {
				HandleRawModeKeyEvent (wParam, lParam);
			}
			else HandleProcModeKeyEvent (wParam, lParam);
			currentDevice = KEYBOARD;
			break;

		case WM_SIZE:
			SRGP_trace(SRGP_logStream,msg);

			if (wParam != SIZE_MINIMIZED) {
				width = LOWORD(lParam);
				height = HIWORD(lParam);
				if (windowInit>1) {
					srgp__canvasTable[0].drawable.win = hWnd;
					hdc = GetDC (srgp__canvasTable[0].drawable.win);
					hRgn = CreateRectRgn(0, 0, width+1, height+1);
					SelectClipRgn(hdc, hRgn);
					hBrush = SelectObject (hdc, GetStockObject (WHITE_BRUSH));
					hPen = SelectObject (hdc, GetStockObject (WHITE_PEN));
					Rectangle(hdc, 0, 0, width+1, height+1);
					DeleteObject(SelectObject(hdc, hBrush));
					DeleteObject(SelectObject(hdc, hPen));
					ReleaseDC(srgp__canvasTable[0].drawable.win, hdc);
				}
				else {
					windowInit++;
					srgp__canvasTable[0].max_xcoord = width-1;
					srgp__canvasTable[0].max_ycoord = height-1;
					if (srgp__curActiveCanvasId == 0) {
						srgp__curActiveCanvasSpec.max_xcoord = width-1;
						srgp__curActiveCanvasSpec.max_ycoord = height-1;
					}
				}
			}
			currentDevice = NO_DEVICE;
			return DefWindowProc(hWnd, Message, wParam, lParam);
		case WM_DESTROY:
        	CleanUpResources();
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);
	}
	return 0;
}


int
SRGP__handleRawEvents (boolean inwaitevent, boolean forever)
{
	MSG		msg;
	RECT 	clientRect;
	int 	width, height;

	SRGP_trace(SRGP_logStream, "SRGP__handleRawEvents\n");
	currentDevice = NO_DEVICE;
	if (forever && inwaitevent) {
		do {
			if (GetMessage(&msg, NULL, 0, 0)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				if (screenRepaintNeeded) {
					GetClientRect(srgp__canvasTable[0].drawable.win,
								  &clientRect);
					SRGP__reactToScreenResize (clientRect.right - clientRect.left,
											   clientRect.bottom - clientRect.top);
					screenRepaintNeeded = FALSE;
				}
			} else exit(0);
		} while (currentDevice == NO_DEVICE);
	}
	else {
		do {
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				if (msg.message != WM_QUIT) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
					if (screenRepaintNeeded) {
						GetClientRect(srgp__canvasTable[0].drawable.win,
									  &clientRect);
						SRGP__reactToScreenResize
							(clientRect.right - clientRect.left,
							 clientRect.bottom - clientRect.top);
						screenRepaintNeeded = FALSE;
					}
				} else exit(0);
			}
			else break;
		} while (currentDevice == NO_DEVICE);
	}
	return currentDevice;
}

