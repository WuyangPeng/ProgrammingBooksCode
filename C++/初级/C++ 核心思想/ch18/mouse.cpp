#include <wx/wx.h>

/**
   A window on which the program user can draw
   a triangle by clicking on the three corners.
*/
class TriangleWindow : public wxWindow
{
public:
   /**
      Initializes the base class.
      @param parent the parent window
   */   
   TriangleWindow(wxWindow* parent);
   /**
      Paints the corners and lines that have already been
      entered.
      @param event the event descriptor
   */      
   void OnPaint(wxPaintEvent& event);
   /**
      Adds another corner to the triangle.
      @param event the event descriptor
   */
   void OnMouseEvent(wxMouseEvent& event);
private:
   int x[3];
   int y[3];
   int corners;
   DECLARE_EVENT_TABLE()
};

/**
   A frame with a window that shows a triangle.
*/
class MouseFrame : public wxFrame
{
public:
   /**
      Constructs the window.
   */
   MouseFrame();
private:
   TriangleWindow* window;
};

/**
   An application to demonstrate mouse event handling.
*/
class MouseApp : public wxApp
{
public:
   /**
      Constructs the frame.
   */
   MouseApp();
   /**
      Shows the frame.
      @return true
   */
   virtual bool OnInit();
private:
   MouseFrame* frame;
};

DECLARE_APP(MouseApp)

IMPLEMENT_APP(MouseApp)

BEGIN_EVENT_TABLE(TriangleWindow, wxWindow)
   EVT_MOUSE_EVENTS(TriangleWindow::OnMouseEvent)
   EVT_PAINT(TriangleWindow::OnPaint)
END_EVENT_TABLE()

TriangleWindow::TriangleWindow(wxWindow* parent)
   : wxWindow(parent, -1)
{
   corners = 0;
}

void TriangleWindow::OnMouseEvent(wxMouseEvent& event)
{
   if (event.ButtonDown() && corners < 3)
   {
      x[corners] = event.GetX();
      y[corners] = event.GetY();
      corners++;
      Refresh();
   }
}

void TriangleWindow::OnPaint(wxPaintEvent& event)
{
   const int RADIUS = 2;
   wxPaintDC dc(this);
   dc.SetBrush(*wxTRANSPARENT_BRUSH);
   if (corners == 1)
      dc.DrawEllipse(x[0] - RADIUS, y[0] - RADIUS, 
         2 * RADIUS, 2 * RADIUS);
   if (corners >= 2)
      dc.DrawLine(x[0], y[0], x[1], y[1]);
   if (corners >= 3)
   {
      dc.DrawLine(x[1], y[1], x[2], y[2]);
      dc.DrawLine(x[2], y[2], x[0], y[0]);
   }
}

MouseFrame::MouseFrame() 
   : wxFrame(NULL, -1, "MouseFrame")
{
   window = new TriangleWindow(this);
}

MouseApp::MouseApp()
{
   frame = new MouseFrame();
}

bool MouseApp::OnInit()
{
   frame->Show(true);
   return true;
}
