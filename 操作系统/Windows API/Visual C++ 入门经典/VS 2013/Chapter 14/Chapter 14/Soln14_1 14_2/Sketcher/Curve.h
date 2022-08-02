#pragma once
#include "Element.h"
#include <vector>
class CCurve :
  public CElement
{
public:
  virtual ~CCurve(void);
  virtual void Draw(CDC* pDC) override;   // Function to display a curve
  // Constructor for a curve object
  CCurve(const CPoint& first, const CPoint& second, COLORREF color);

  void AddSegment(const CPoint& point);   // Add a segment to the curve

protected:
  std::vector<CPoint> m_Points;           // Points defining the curve
  CCurve(void);                           // Default constructor - should not be used
};

