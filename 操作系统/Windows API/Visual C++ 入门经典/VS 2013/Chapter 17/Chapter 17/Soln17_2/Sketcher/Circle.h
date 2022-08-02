#pragma once
#include "Element.h"
class CCircle :
  public CElement
{
DECLARE_SERIAL(CCircle)
public:
  virtual ~CCircle();
  virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override;    // Function to display a circle
  // Constructor for a circle object
  CCircle(const CPoint& start, const CPoint& end, COLORREF color, int penWidth);
  virtual void Move(const CSize& aSize) override;                                        // Function to move an element
  virtual void Serialize(CArchive& ar) override;                                         // Serialize object

protected:
  CPoint m_BottomRight;                                                                  // Bottom-right point for defining circle
  CCircle();                                                                             // Default constructor - should not be used
};

