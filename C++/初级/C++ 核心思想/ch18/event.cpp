#include <wx/wx.h>

const int ID_SAY_HELLO = 1000;
const int ID_SAY_GOODBYE = 1001;

/**
   A frame with a simple menu that adds greetings to a 
   text control.
*/
class EventFrame : public wxFrame
{
public:
   /**
      Constructs the menu and text control.
   */
   EventFrame();
   /**
      Adds a "Hello, World!" message to the text control.
      @param event the event descriptor
   */
   void OnSayHello(wxCommandEvent& event);
   /**
      Adds a "Goodbye, World!" message to the text control.
      @param event the event descriptor
   */
   void OnSayGoodbye(wxCommandEvent& event);
private:
   wxTextCtrl* text;
   DECLARE_EVENT_TABLE()
};

/**
   An application to demonstrate the handling of menu events.
*/
class EventApp : public wxApp
{
public:
   /**
      Constructs the frame.
   */
   EventApp();
   /**
      Shows the frame.
      @return true
   */
   virtual bool OnInit();
private:
   EventFrame* frame;
};

DECLARE_APP(EventApp)

IMPLEMENT_APP(EventApp)

BEGIN_EVENT_TABLE(EventFrame, wxFrame)
   EVT_MENU(ID_SAY_HELLO, EventFrame::OnSayHello)
   EVT_MENU(ID_SAY_GOODBYE, EventFrame::OnSayGoodbye) 
END_EVENT_TABLE()

EventFrame::EventFrame() 
   : wxFrame(NULL, -1, "EventFrame")
{
   text = new wxTextCtrl(this, -1, "",
      wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

   // initialize menu
   wxMenu* menu = new wxMenu();
   menu->Append(ID_SAY_HELLO, "Hello");
   menu->Append(ID_SAY_GOODBYE, "Goodbye");

   // add menu to menu bar
   wxMenuBar* menuBar = new wxMenuBar();
   SetMenuBar(menuBar);
   menuBar->Append(menu, "Say");   
}

void EventFrame::OnSayHello(wxCommandEvent& event)
{
   text->AppendText("Hello, World!\n");
}

void EventFrame::OnSayGoodbye(wxCommandEvent& event)
{
   text->AppendText("Goodbye, World!\n");
}

EventApp::EventApp()
{
   frame = new EventFrame();
}

bool EventApp::OnInit()
{
   frame->Show(true);
   return true;
}


