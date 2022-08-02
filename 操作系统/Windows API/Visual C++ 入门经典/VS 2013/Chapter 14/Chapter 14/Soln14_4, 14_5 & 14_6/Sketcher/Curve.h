#pragma once
#include "element.h"
#include <vector>

class CCurve :
  public CElement
{
public:
  virtual ~CCurve(void);
  virtual void Draw(CDC* pDC) override;                                // Function to display a curve
  CCurve(const CPoint& first, const CPoint& second, COLORREF color, int penWidth=1, int lineStyle=PS_SOLID);   // Constructor for a curve object
  void AddSegment(const CPoint& point);                                // Add a segment to the curve

protected:
  std::vector<CPoint> m_Points;                                        // Points defining the curve
  CCurve(void);                                                        // Default constructor - should not be used
};

