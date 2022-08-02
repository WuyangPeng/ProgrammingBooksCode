/*--------------------------------------------------------
   KEYVIEW1.C -- Displays Keyboard and Character Messages
                 (c) Charles Petzold, 1998
  --------------------------------------------------------*/

#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("KeyView1") ;
     HWND         hwnd ;
     MSG          msg ;
     WNDCLASS     wndclass ;
     
     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;

     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("This program requires Windows NT!"), 
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }
     
     hwnd = CreateWindow (szAppName, TEXT ("Keyboard Message Viewer #1"),
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL, NULL, hInstance, NULL) ;
     
     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;
     
     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static int   cxClientMax, cyClientMax, cxClient, cyClient, cxChar, cyChar ;
     static int   cLinesMax, cLines ;
     static PMSG  pmsg ;//MSG结构的阵列
     static RECT  rectScroll ;
     static TCHAR szTop[] = TEXT ("Message        Key       Char     ")
                            TEXT ("Repeat Scan Ext ALT Prev Tran") ;
     static TCHAR szUnd[] = TEXT ("_______        ___       ____     ")
                            TEXT ("______ ____ ___ ___ ____ ____") ;

     static TCHAR * szFormat[2] = { 
          
               TEXT ("%-13s %3d %-15s%c%6u %4d %3s %3s %4s %4s"),
               TEXT ("%-13s            0x%04X%1s%c %6u %4d %3s %3s %4s %4s") } ;

     static TCHAR * szYes  = TEXT ("Yes") ;
     static TCHAR * szNo   = TEXT ("No") ;
     static TCHAR * szDown = TEXT ("Down") ;
     static TCHAR * szUp   = TEXT ("Up") ;

     static TCHAR * szMessage [] = { 
                         TEXT ("WM_KEYDOWN"),    TEXT ("WM_KEYUP"), 
                         TEXT ("WM_CHAR"),       TEXT ("WM_DEADCHAR"), 
                         TEXT ("WM_SYSKEYDOWN"), TEXT ("WM_SYSKEYUP"), 
                         TEXT ("WM_SYSCHAR"),    TEXT ("WM_SYSDEADCHAR") } ;
     HDC          hdc ;
     int          i, iType ;
     PAINTSTRUCT  ps ;
     TCHAR        szBuffer[128], szKeyName [32] ;
     TEXTMETRIC   tm ;
     
     switch (message)
     {
     case WM_CREATE:
     case WM_DISPLAYCHANGE:
		 //如果使用者在程式执行时调整了视讯显示的大小
		 //在这种情况下KEYVIEW1接收WM_DISPLAYCHANGE讯息，将重新分配此阵列。
     
               // Get maximum size of client area

          cxClientMax = GetSystemMetrics (SM_CXMAXIMIZED) ;//得到窗口客户区最大的宽度,即最大化后客户区的宽度
          cyClientMax = GetSystemMetrics (SM_CYMAXIMIZED) ;//得到窗口客户区最大的高度,即最大化后客户区的高度

              // Get character size for fixed-pitch font

          hdc = GetDC (hwnd) ;

          SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT)) ;//便於以分行的方式显示此资讯,使用了等宽字体
          GetTextMetrics (hdc, &tm) ;
          cxChar = tm.tmAveCharWidth ;
          cyChar = tm.tmHeight ;

          ReleaseDC (hwnd, hdc) ;

          // Allocate memory for display lines

          if (pmsg)
               free (pmsg) ;

          cLinesMax = cyClientMax / cyChar ;
          pmsg = malloc (cLinesMax * sizeof (MSG)) ;//使用标准C的malloc函式为阵列按字节配置记忆体。
		  //分配最大的可能需要的内存块,该阵列的大小依据最大化视窗的大小和等宽的系统字体。
          cLines = 0 ;
                                   // fall through
     case WM_SIZE:
          if (message == WM_SIZE)
          {
               cxClient = LOWORD (lParam) ;//窗口尺寸变化后得到客户区的尺寸
               cyClient = HIWORD (lParam) ;
          }
               // Calculate scrolling rectangle
          //计算滚动矩形框范围,此范围比客户区要小一行.
          rectScroll.left   = 0 ;
          rectScroll.right  = cxClient ;
          rectScroll.top    = cyChar ;
          rectScroll.bottom = cyChar * (cyClient / cyChar) ;

          InvalidateRect (hwnd, NULL, TRUE) ;//使重画
          return 0 ;

          //8种不同键盘讯息的全部资讯
     case WM_KEYDOWN:
     case WM_KEYUP:
     case WM_CHAR:
     case WM_DEADCHAR:
     case WM_SYSKEYDOWN:
     case WM_SYSKEYUP:
     case WM_SYSCHAR:
     case WM_SYSDEADCHAR: 

               // Rearrange storage array

          for (i = cLinesMax - 1 ; i > 0 ; i--)
          {
               pmsg[i] = pmsg[i - 1] ;
          }
               // Store new message

          pmsg[0].hwnd = hwnd ;
          pmsg[0].message = message ;
          pmsg[0].wParam = wParam ;
          pmsg[0].lParam = lParam ;

          cLines = min (cLines + 1, cLinesMax) ;

               // Scroll up the display

          ScrollWindow (hwnd, 0, -cyChar, &rectScroll, &rectScroll) ;

          break ;        // ie, call DefWindowProc so Sys messages work
          
     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;

          SelectObject (hdc, GetStockObject (SYSTEM_FIXED_FONT)) ;
          SetBkMode (hdc, TRANSPARENT) ;
		  //通常，Windows以一种「不透明」的方式显示文字，也就是说显示字元时Windows将擦除字元背景区。
		  //这将导致第二个字串（szUnd）擦除掉前一个（szTop）。
          TextOut (hdc, 0, 0, szTop, lstrlen (szTop)) ;
          TextOut (hdc, 0, 0, szUnd, lstrlen (szUnd)) ;

          for (i = 0 ; i < min (cLines, cyClient / cyChar - 1) ; i++)
          {
			  //四类字元讯息
               iType = pmsg[i].message == WM_CHAR ||
                       pmsg[i].message == WM_SYSCHAR ||
                       pmsg[i].message == WM_DEADCHAR ||
                       pmsg[i].message == WM_SYSDEADCHAR ;

               GetKeyNameText (pmsg[i].lParam, szKeyName, 
                               sizeof (szKeyName) / sizeof (TCHAR)) ;

			   /*
			   szFormat的定义如下:
       static TCHAR * szFormat[2] = { TEXT ("%-13s %3d %-15s%c%6u %4d %3s %3s %4s %4s"),
               TEXT ("%-13s            0x%04X%1s%c %6u %4d %3s %3s %4s %4s") } ;

                szMessage的定义如下:
       static TCHAR * szMessage [] = { 
                         TEXT ("WM_KEYDOWN"),    TEXT ("WM_KEYUP"), 
                         TEXT ("WM_CHAR"),       TEXT ("WM_DEADCHAR"), 
                         TEXT ("WM_SYSKEYDOWN"), TEXT ("WM_SYSKEYUP"), 
                         TEXT ("WM_SYSCHAR"),    TEXT ("WM_SYSDEADCHAR") } ;
			   */
               TextOut (hdc, 0, (cyClient / cyChar - 1 - i) * cyChar, szBuffer,
                        wsprintf (szBuffer, szFormat [iType],//是否为字元讯息
                             szMessage [pmsg[i].message - WM_KEYFIRST],                   
                             pmsg[i].wParam,
                             (PTSTR) (iType ? TEXT (" ") : szKeyName),//按键讯息的虚拟键代码,此代码是经由GetKeyNameText函式取得的
                             (TCHAR) (iType ? pmsg[i].wParam : ' '),//如果是字元信息,则打出pmsg[i].wParam

                             LOWORD (pmsg[i].lParam),//以下是lParam变数的6个按键讯息栏位 
                             HIWORD (pmsg[i].lParam) & 0xFF,
                             0x01000000 & pmsg[i].lParam ? szYes  : szNo,
                             0x20000000 & pmsg[i].lParam ? szYes  : szNo,
                             0x40000000 & pmsg[i].lParam ? szDown : szUp,
                             0x80000000 & pmsg[i].lParam ? szUp   : szDown)) ;
          }
          EndPaint (hwnd, &ps) ;
          return 0 ;

     case WM_DESTROY:
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}
