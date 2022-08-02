#include <wx/wx.h>

const int ID_SAY_HELLO = 1000;
const int ID_SAY_GOODBYE = 1001;

/**
   A frame with buttons that add greetings to a 
   text control.
*/
class ButtonFrame : public wxFrame
{
public:
   /**
      Constructs and lays out the text control and buttons.
   */
   ButtonFrame();
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
   An application to demonstrate button layout.
*/
class ButtonApp : public wxApp
{
public:
   /**
      Constructs the frame.
   */
   ButtonApp();
   /**
      Shows the frame.
      @return true
   */
   virtual bool OnInit();
private:
   ButtonFrame* frame;
};

DECLARE_APP(ButtonApp)

IMPLEMENT_APP(ButtonApp)

BEGIN_EVENT_TABLE(ButtonFrame, wxFrame)
   EVT_BUTTON(ID_SAY_HELLO, ButtonFrame::OnSayHello)
   EVT_BUTTON(ID_SAY_GOODBYE, ButtonFrame::OnSayGoodbye) 
END_EVENT_TABLE()

ButtonFrame::ButtonFrame() 
   : wxFrame(NULL, -1, "ButtonFrame")
{
   text = new wxTextCtrl(this, -1, "",
      wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

   wxButton* hello_button = new wxButton(this, 
      ID_SAY_HELLO, "Say Hello");

   wxButton* goodbye_button = new wxButton(this, 
      ID_SAY_GOODBYE, "Say Goodbye");

   wxBoxSizer* button_sizer = new wxBoxSizer(wxHORIZONTAL);
   button_sizer->Add(hello_button);
   button_sizer->Add(goodbye_button);

   wxBoxSizer* frame_sizer = new wxBoxSizer(wxVERTICAL);
   frame_sizer->Add(text, 1, wxGROW);
   frame_sizer->Add(button_sizer, 0, wxALIGN_CENTER);

   SetAutoLayout(true);
   SetSizer(frame_sizer);
}

void ButtonFrame::OnSayHello(wxCommandEvent& event)
{
   text->AppendText("Hello, World!\n");
}

void ButtonFrame::OnSayGoodbye(wxCommandEvent& event)
{
   text->AppendText("Goodbye, World!\n");
}

ButtonApp::ButtonApp()
{
   frame = new ButtonFrame();
}

bool ButtonApp::OnInit()
{
   frame->Show(true);
   return true;
}
