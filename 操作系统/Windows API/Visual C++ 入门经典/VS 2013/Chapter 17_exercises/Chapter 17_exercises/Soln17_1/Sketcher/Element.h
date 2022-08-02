#pragma once
#include <memory>

static const COLORREF SELECT_COLOR{ RGB(255, 0, 180) };                       // Highlight color
static const UINT VERSION_NUMBER{ 1001 };                                     // Version number for serialization

class CElement : public CObject
{
  DECLARE_SERIAL(CElement)
protected:
  CPoint m_StartPoint;                                                         // Element position      
  int m_PenWidth;                                                              // Pen width
  COLORREF m_Color;                                                            // Color of an element
  CRect m_EnclosingRect;                                                       // Rectangle enclosing an element

public:
  virtual ~CElement();
  virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) {}   // Virtual draw operation
  virtual void Move(const CSize& aSize){}                                      // Move an element 
  virtual void Serialize(CArchive& ar) override;                               // Serialize object
  const CRect& GetEnclosingRect() const { return m_EnclosingRect; }            // Get the element enclosing rectangle

protected:
  // Create a pen
  void CreatePen(CPen& aPen, std::shared_ptr<CElement> pElement)
  {
    if (!aPen.CreatePen(PS_SOLID, m_PenWidth, this == pElement.get() ? SELECT_COLOR : m_Color))
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


