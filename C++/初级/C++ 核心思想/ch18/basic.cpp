#include <wx/wx.h>

/**
   A basic application that shows an empty frame.
*/
class BasicApp : public wxApp
{
public:
   /**
      Constructs the frame.
   */
   BasicApp();
   /**
      Shows the frame.
      @return true
   */
   virtual bool OnInit();
private:
   wxFrame* frame;
};

DECLARE_APP(BasicApp)

IMPLEMENT_APP(BasicApp)

BasicApp::BasicApp()
{
   frame = new wxFrame(NULL, -1, "My First GUI Program");
}

bool BasicApp::OnInit()
{
   frame->Show(true);
   return true;
}

