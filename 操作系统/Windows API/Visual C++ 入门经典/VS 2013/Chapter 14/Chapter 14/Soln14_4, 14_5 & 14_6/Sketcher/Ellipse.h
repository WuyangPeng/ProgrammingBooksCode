#pragma once
#include "element.h"
class CEllipse :
  public CElement
{
public:
  virtual ~CEllipse(void){}
 virtual void Draw(CDC* pDC) override;                                 // Function to display an ellipse

 
 CEllipse(const CPoint& center, const CPoint& end, COLORREF color, int penWidth=1, int lineStyle=PS_SOLID);     // Constructor for an ellipse object

protected:
  CPoint m_BottomRight;                                                // Bottom-right point for the rectangle defining the ellipse
  CEllipse(void) {}                                                    // Default constructor - should not be used
};

