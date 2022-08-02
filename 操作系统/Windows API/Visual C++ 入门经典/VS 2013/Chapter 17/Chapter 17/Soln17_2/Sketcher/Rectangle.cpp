#include "stdafx.h"
#include "Rectangle.h"
#include <algorithm>

IMPLEMENT_SERIAL(CRectangle, CElement, VERSION_NUMBER)

// CRectangle constructor
CRectangle::CRectangle(
  const CPoint& start, const CPoint& end, COLORREF color, int penWidth) :
  CElement { start, color, penWidth }
{
  // Normalize the rectangle defining points
  m_StartPoint = CPoint { (std::min)(start.x, end.x), (std::min)(start.y, end.y) };
  m_BottomRight = CPoint { (std::max)(start.x, end.x), (std::max)(start.y, end.y) };
  // Ensure width and height between the points is at least 2
  if ((m_BottomRight.x - m_StartPoint.x) < 2)
    m_BottomRight.x = m_StartPoint.x + 2;
  if ((m_BottomRight.y - m_StartPoint.y) < 2)
    m_BottomRight.y = m_StartPoint.y + 2;
  // Define the enclosing rectangle
  m_EnclosingRect = CRect { m_StartPoint, m_BottomRight };
  int width { penWidth == 0 ? 1 : penWidth }; // Inflate rect by at least 1
  m_EnclosingRect.InflateRect(width, width);
}

CRectangle::CRectangle()
{
}


CRectangle::~CRectangle()
{
}

// Draw a CRectangle object
void CRectangle::Draw(CDC* pDC, std::shared_ptr<CElement> pElement)
{
  // Create a pen for this object and initialize it
  CPen aPen;
  CreatePen(aPen, pElement);

  // Select the pen and the null brush
  CPen* pOldPen { pDC->SelectObject(&aPen) };
  CBrush* pOldBrush { dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };

  // Now draw the rectangle
  pDC->Rectangle(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);

  pDC->SelectObject(pOldBrush);       // Restore the old brush
  pDC->SelectObject(pOldPen);         // Restore the old pen
}

void CRectangle::Move(const CSize& aSize)
{
  m_StartPoint += aSize;               // Move the start point
  m_BottomRight += aSize;              // Move the bottom right point
  m_EnclosingRect += aSize;            // Move the enclosing rectangle
}

void CRectangle::Serialize(CArchive& ar)
{
  CElement::Serialize(ar);             // Call the base class function
  if (ar.IsStoring())
  { // Writing to the file
    ar << m_BottomRight;               // Bottom-right point for the rectangle
  }
  else
  { // Reading from the file
    ar >> m_BottomRight;
  }
}
