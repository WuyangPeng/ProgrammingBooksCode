#include "stdafx.h"
#include "Ellipse.h"
#include <algorithm>

// CEllipse constructor
CEllipse:: CEllipse (const CPoint& start, const CPoint& end, COLORREF color) : CElement(start, color)
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

// Draw an ellipse
void CEllipse::Draw(CDC* pDC)
{
   // Create a pen for this object and initialize it
   CPen aPen;
   CreatePen(aPen);

   CPen* pOldPen{ pDC->SelectObject(&aPen) };  // Select the pen
        
   // Now draw the circle
   pDC->Ellipse(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);
        
   pDC->SelectObject(pOldPen);                // Restore the old pen
}
