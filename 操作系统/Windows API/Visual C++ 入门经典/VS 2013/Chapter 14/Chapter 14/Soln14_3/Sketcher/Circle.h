#pragma once
#include "Element.h"
class CCircle :
  public CElement
{
public:
  virtual ~CCircle(void);
  virtual void Draw(CDC* pDC) override;     // Function to display a circle
  // Constructor for a circle object
  CCircle(const CPoint& start, const CPoint& end, COLORREF color);

protected:
  CPoint m_BottomRight;            // Bottom-right point for defining circle
  CCircle(void);                   // Default constructor - should not be used
};

