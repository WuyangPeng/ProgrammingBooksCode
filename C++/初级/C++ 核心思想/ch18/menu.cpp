#include <wx/wx.h>

const int ID_SAY_HELLO = 1000;
const int ID_SAY_GOODBYE = 1001;

/**
   A frame with a simple menu and a text control.
*/
class MenuFrame : public wxFrame
{
public:
   /**
      Constructs the menu and text control.
   */
   MenuFrame();
private:
   wxTextCtrl* text;
};

/**
   An application with a frame that has a menu and text control.
*/
class MenuApp : public wxApp
{
public:
   /**
      Constructs the frame.
   */
   MenuApp();
   /**
      Shows the frame.
      @return true
   */
   virtual bool OnInit();
private:
   MenuFrame* frame;
};

DECLARE_APP(MenuApp)

IMPLEMENT_APP(MenuApp)

MenuFrame::MenuFrame() 
   : wxFrame(NULL, -1, "MenuFrame")
{
   text = new wxTextCtrl(this, -1, "",
      wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

   // initialize menu
   wxMenu* menu = new wxMenu();
   menu->Append(ID_SAY_HELLO, "Hello");
   menu->Append(ID_SAY_GOODBYE, "Goodbye");

   // add menu to menu bar
   wxMenuBar* menu_bar = new wxMenuBar();
   SetMenuBar(menu_bar);
   menu_bar->Append(menu, "Say");   
}

MenuApp::MenuApp()
{
   frame = new MenuFrame();
}

bool MenuApp::OnInit()
{
   frame->Show(true);
   return true;
}
