 /* '04 Main.h' */

 /* Mirus window framework header */
#include "mrWindow.h"

 /* Custom derived class */
class CustomWindow : public mrWindow
{
public:
  /* Constructor / Destructor */
 CustomWindow (void) {};
 ~CustomWindow (void) {};

  /* Window manipulation functions */
 mrBool32 Frame (void) {return mrTrue;} ;
};

 /* "WinMain Vs. main" */
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst, 
                    LPSTR lpCmdLine, int nShowCmd)
{
  /* Our window */
 CustomWindow		kWindow;

  /* Create window */
 kWindow.Create (hInstance, "04 Mirus Example");
	/* Enter message loop */
 kWindow.Run ();

	return 0;
}