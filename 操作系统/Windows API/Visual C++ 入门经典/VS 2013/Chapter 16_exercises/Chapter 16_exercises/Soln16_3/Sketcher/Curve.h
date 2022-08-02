#pragma once
#include "Element.h"
#include <vector>
class CCurve :
  public CElement
{
public:
  virtual ~CCurve();
  virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override;    // Function to display a curve
  // Constructor for a curve object
  CCurve(const CPoint& first, const CPoint& second, COLORREF color, int penWidth);
  virtual void Move(const CSize& aSize) override;                                        // Function to move an element
  void AddSegment(const CPoint& point);                                                  // Add a segment to the curve

protected:
  std::vector<CPoint> m_Points;                                                          // Points defining the curve
  CCurve();                                                                              // Default constructor - should not be used
};

