#pragma once
#include "element.h"
class CRectangle :
  public CElement
{
public:
  virtual ~CRectangle(void);
 virtual void Draw(CDC* pDC) override;                                 // Function to display a rectangle

 
 CRectangle(const CPoint& start, const CPoint& end, COLORREF color, int penWidth=1, int lineStyle=PS_SOLID);   // Constructor for a rectangle object

protected:
  CPoint m_BottomRight;                                                // Bottom-right point for the rectangle
  CRectangle(void);                                                    // Default constructor - should not be used
};

