#pragma once

class CElement : public CObject
{
protected:
  CPoint m_StartPoint;            // Element position      
  int m_PenWidth;                 // Pen width
  COLORREF m_Color;               // Color of an element
  CRect m_EnclosingRect;          // Rectangle enclosing an element

public:
  virtual ~CElement();
  virtual void Draw(CDC* pDC) {}  // Virtual draw operation
  // Get the element enclosing rectangle
  const CRect& GetEnclosingRect() const { return m_EnclosingRect; }

protected:
  // Create a pen
  void CreatePen(CPen& aPen)
  {
    if (!aPen.CreatePen(PS_SOLID, m_PenWidth, m_Color))
    {
      // Pen creation failed
      AfxMessageBox(_T("Pen creation failed."), MB_OK);
      AfxAbort();
    }
  }

  // Constructors protected so they cannot be called outside the class
  CElement();
  CElement(const CPoint& start, COLORREF color, int penWidth = 1);
};


