#include <wx/wx.h>

/**
   A window onto which an ellipse is painted.
*/
class EllipseWindow : public wxWindow
{
public:
   /**
      Initializes the base class.
      @param parent the parent window
   */
   EllipseWindow(wxWindow* parent);
   /**
      Draws an ellipse on the window.
      @param event the event descriptor
   */
   void OnPaint(wxPaintEvent& event);
private:
   DECLARE_EVENT_TABLE()
};

/**
   A frame with a window that shows an ellipse.
*/
class PaintFrame : public wxFrame
{
public:
   /**
      Constructs the window.
   */
   PaintFrame();
private:
   EllipseWindow* window;
};

/**
   An application to demonstrate painting.
*/
class PaintApp : public wxApp
{
public:
   /**
      Constructs the frame.
   */
   PaintApp();
   /**
      Shows the frame.
      @return true
   */
   virtual bool OnInit();
private:
   PaintFrame* frame;
};

DECLARE_APP(PaintApp)

IMPLEMENT_APP(PaintApp)

BEGIN_EVENT_TABLE(EllipseWindow, wxWindow)
   EVT_PAINT(EllipseWindow::OnPaint)
END_EVENT_TABLE()

EllipseWindow::EllipseWindow(wxWindow* parent)
   : wxWindow(parent, -1)
{
}

void EllipseWindow::OnPaint(wxPaintEvent& event)
{
   wxPaintDC dc(this);
   dc.SetBrush(*wxTRANSPARENT_BRUSH);
   wxSize size = GetSize();
   int x = 0;
   int y = 0;
   int width = size.GetWidth();
   int height = size.GetHeight();
   dc.DrawEllipse(x, y, width, height);
}

PaintFrame::PaintFrame() 
   : wxFrame(NULL, -1, "PaintFrame")
{
   window = new EllipseWindow(this);
}

PaintApp::PaintApp()
{
   frame = new PaintFrame();
}

bool PaintApp::OnInit()
{
   frame->Show(true);
   return true;
}

