#pragma once
#include "Element.h"
class CLine :
  public CElement
{
public:
  virtual ~CLine();
  virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) override; // Function to display a line
  // Constructor for a line object
  CLine(const CPoint& start, const CPoint& end, COLORREF aColor);
  virtual void Move(const CSize& aSize) override;                                   // Function to move an element
protected:
  CPoint m_EndPoint;                                                                // End point of line

protected:
  CLine();                                                                          // Default constructor should not be used
};

