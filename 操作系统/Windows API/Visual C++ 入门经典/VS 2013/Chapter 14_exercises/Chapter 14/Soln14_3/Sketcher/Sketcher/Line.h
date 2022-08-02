#pragma once
#include "Element.h"
class CLine :
  public CElement
{
public:
  virtual ~CLine(void);
  virtual void Draw(CDC* pDC) override; // Function to display a line
  // Constructor for a line object
  CLine(const CPoint& start, const CPoint& end, COLORREF aColor);

protected:
  CPoint m_EndPoint;                    // End point of line

protected:
  CLine(void);                          // Default constructor should not be used
};

