#pragma once
#include <memory>

static const COLORREF SELECT_COLOR { RGB(255, 0, 180) };                       // Highlight color

class CElement : public CObject
{
protected:
  CPoint m_StartPoint;                                                         // Element position      
  int m_PenWidth;                                                              // Pen width
  COLORREF m_Color;                                                            // Color of an element
  CRect m_EnclosingRect;                                                       // Rectangle enclosing an element

public:
  virtual ~CElement();
  virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) {}   // Virtual draw operation
  virtual void Move(const CSize& aSize){}                                      // Move an element  
  const CRect& GetEnclosingRect() const { return m_EnclosingRect; }            // Get the element enclosing rectangle

protected:
  // Create a pen
  void CreatePen(CPen& aPen, std::shared_ptr<CElement> pElement)
  {
    if (!aPen.CreatePen(this == pElement.get() ? PS_DASH : PS_SOLID, m_PenWidth,
      this == pElement.get() ? SELECT_COLOR : m_Color))
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


