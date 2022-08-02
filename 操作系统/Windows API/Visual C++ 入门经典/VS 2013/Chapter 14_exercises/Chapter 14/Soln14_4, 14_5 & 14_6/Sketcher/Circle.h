#pragma once
#include "element.h"

class CCircle :
  public CElement
{
public:
  virtual ~CCircle(void);
  virtual void Draw(CDC* pDC) override;                                // Function to display a circle

  
  CCircle(const CPoint& start, const CPoint& end, COLORREF color, int penWidth=1, int lineStyle=PS_SOLID);     // Constructor for a circle object

protected:
  CPoint m_BottomRight;                                                // Bottom-right point for defining rectangle
  CCircle(void);                                                       // Default constructor - should not be used
};

