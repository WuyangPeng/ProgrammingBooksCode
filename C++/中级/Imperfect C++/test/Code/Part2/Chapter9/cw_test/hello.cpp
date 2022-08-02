/*
 *  Copyright © 1997-2002 Metrowerks Corporation.  All Rights Reserved.
 *
 *  Please see the stationery release note "Win32 Shared Runtime Notes.txt" 
 *  for information about using this stationery.
 *
 *  Questions and comments to:
 *       <mailto:support@metrowerks.com>
 *       <http://www.metrowerks.com/>
 */

/* Win32 GUI app skeleton */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

LRESULT CALLBACK WndProc( HWND hWnd, UINT messg,
                                WPARAM wParam, LPARAM lParam );


char szProgName[] = "Hello Win32"; /* name of application */
char message[] = "Hello from Win32"; /* message to be printed in client area */

                                
int WINAPI WinMain( HINSTANCE hInst,    /*Win32 entry-point routine */
                    HINSTANCE hPreInst, 
                    LPSTR lpszCmdLine, 
                    int nCmdShow )
{
    #pragma unused(lpszCmdLine)
    HWND hWnd;
    MSG lpMsg;
    WNDCLASS wc;

    if( !hPreInst )         /*set up window class and register it */
    {
        wc.lpszClassName    = szProgName;
        wc.hInstance        = hInst;
        wc.lpfnWndProc      = WndProc;
        wc.hCursor          = LoadCursor( NULL, IDC_ARROW );
        wc.hIcon            = LoadIcon( NULL, IDI_APPLICATION );
        wc.lpszMenuName     = NULL;
        wc.hbrBackground    = (HBRUSH)GetStockObject( WHITE_BRUSH );
        wc.style            = 0;
        wc.cbClsExtra       = 0;
        wc.cbWndExtra       = 0;

        if( !RegisterClass( &wc ) )
            return FALSE;
    }


    hWnd = CreateWindow(    szProgName,                         /* now create the window */
                            "CodeWarrior Win32 stationery",
                            WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            (HWND)NULL,
                            (HMENU)NULL,
                            hInst,
                            (LPSTR)NULL     );

    ShowWindow(hWnd, nCmdShow );
    UpdateWindow( hWnd );
    


    while( GetMessage( &lpMsg, NULL, 0, 0 ) )                   /* begin the message loop */
    {
        TranslateMessage( &lpMsg );
        DispatchMessage( &lpMsg );
    }
    return( lpMsg.wParam);
}



LRESULT CALLBACK WndProc( HWND hWnd, UINT messg,                /*callback procedure */
                                WPARAM wParam, LPARAM lParam )
{
    HDC hdc;                /* handle to the device context */
    PAINTSTRUCT pstruct;    /*struct for the call to BeginPaint */
    
    switch(messg)
    {
        case WM_PAINT:
        hdc = BeginPaint(hWnd, &pstruct ); /* prepare window for painting*/
        
        TextOut( hdc, 0, 0, message, ( sizeof(message) - 1 ) ); /*print hello at upper left corner */
        
        EndPaint(hWnd, &pstruct );  /* stop painting */
        break;
        
        case WM_DESTROY:
        PostQuitMessage( 0 );
        break;
    
        default:
        return( DefWindowProc( hWnd, messg, wParam, lParam ) );
    }

    return( 0L );
}

