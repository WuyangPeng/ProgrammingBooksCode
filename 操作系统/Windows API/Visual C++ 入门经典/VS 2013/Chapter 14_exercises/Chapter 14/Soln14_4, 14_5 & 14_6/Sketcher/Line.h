#pragma once
#include "element.h"
class CLine :
  public CElement
{
public:
  virtual ~CLine(void);
  virtual void Draw(CDC* pDC) override;          // Function to display a line

  // Constructor for a line object
  CLine(const CPoint& start, const CPoint& end, COLORREF aColor, int penWidth=1, int lineStyle=PS_SOLID);

protected:
  CPoint m_EndPoint;                             // End point of line

protected:
  CLine(void);                                   // Default constructor should not be used
};

