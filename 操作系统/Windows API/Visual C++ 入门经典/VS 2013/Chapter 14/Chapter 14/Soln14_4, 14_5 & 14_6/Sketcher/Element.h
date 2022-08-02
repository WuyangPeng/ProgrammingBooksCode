#pragma once

// CElement command target

class CElement : public CObject
{
protected:
  CPoint m_StartPoint;            // Element position      
  int m_PenWidth;                 // Pen width
  COLORREF m_Color;               // Color of an element
  int m_LineStyle;                // Line style for drawing
  CRect m_EnclosingRect;          // Rectangle enclosing an element

public:
	virtual ~CElement();
  virtual void Draw(CDC* pDC) {}  // Virtual draw operation

  // Get the element enclosing rectangle 
  const CRect& GetEnclosingRect() const  { return m_EnclosingRect; }

protected:
  // Constructors protected so they cannot be called outside the class
  CElement();              
  CElement(const CPoint& start, COLORREF color, int penWidth = 1, int m_LineStyle=PS_SOLID);

 // Create a pen
 void CreatePen(CPen& aPen)
 {
   if(!aPen.CreatePen(m_LineStyle, m_PenWidth, m_Color))
   {
     // Pen creation failed
     AfxMessageBox(_T("Pen creation failed."), MB_OK);
     AfxAbort();
   }
 }
};


