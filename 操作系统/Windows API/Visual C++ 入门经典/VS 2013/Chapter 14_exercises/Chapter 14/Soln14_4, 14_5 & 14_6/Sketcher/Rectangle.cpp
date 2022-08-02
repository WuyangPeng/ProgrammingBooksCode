#include "stdafx.h"
#include "Rectangle.h"
#include <algorithm>


CRectangle::CRectangle(void)
{
}

// CRectangle constructor
CRectangle:: CRectangle (const CPoint& start, const CPoint& end, COLORREF color, int penWidth, int lineStyle) :
                                                                       CElement{ start, color, penWidth, lineStyle }
{
  // Normalize the rectangle defining points
  m_StartPoint = CPoint{ (std::min)(start.x, end.x), (std::min)(start.y, end.y) };
  m_BottomRight = CPoint{ (std::max)(start.x, end.x), (std::max)(start.y, end.y) };

  // Ensure width and height between the points is at least 2
  if((m_BottomRight.x - m_StartPoint.x) < 2)
    m_BottomRight.x = m_StartPoint.x + 2;
  if((m_BottomRight.y - m_StartPoint.y) < 2)
    m_BottomRight.y = m_StartPoint.y + 2;

  // Define the enclosing rectangle
  m_EnclosingRect = CRect{ m_StartPoint, m_BottomRight };
  m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}

// Draw a CRectangle object
void CRectangle::Draw(CDC* pDC)
{
  // Create a pen for this object and initialize it
  CPen aPen; 
  CreatePen(aPen);
        
  // Select the pen and the null brush
  CPen* pOldPen{ pDC->SelectObject(&aPen) };
  CBrush* pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };
        
  // Now draw the rectangle
  pDC->Rectangle(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);
        
  pDC->SelectObject(pOldBrush);                                        // Restore the old brush
  pDC->SelectObject(pOldPen);                                          // Restore the old pen
}


CRectangle::~CRectangle(void)
{
}
