#pragma once
#include "Element.h"
class CRectangle :
  public CElement
{
public:
  virtual ~CRectangle(void);
  virtual void Draw(CDC* pDC) override; // Function to display a rectangle
  // Constructor for a rectangle object
  CRectangle(const CPoint& start, const CPoint& end, COLORREF color);

protected:
  CPoint m_BottomRight;                // Bottom-right point for the rectangle
  CRectangle(void);                    // Default constructor - should not be used
};

