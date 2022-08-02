#include "stdafx.h"
#include "Curve.h"
#include <algorithm>

// Constructor for a curve object
CCurve::CCurve(const CPoint& first, const CPoint& second, COLORREF color) : CElement { first, color }
{
  // Store the second point in the vector
  m_Points.push_back(second);
  m_EnclosingRect = CRect {
    (std::min)(first.x, second.x), (std::min)(first.y, second.y),
    (std::max)(first.x, second.x), (std::max)(first.y, second.y) };
  m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}

CCurve::CCurve()
{
}


CCurve::~CCurve()
{
}

// Draw a curve
void CCurve::Draw(CDC* pDC, std::shared_ptr<CElement> pElement)
{
  // Create a pen for this object and initialize it
  CPen aPen;
  CreatePen(aPen, pElement);

  CPen* pOldPen { pDC->SelectObject(&aPen) };  // Select the pen

  // Now draw the curve
  pDC->MoveTo(m_StartPoint);
  for (const auto& point : m_Points)
    pDC->LineTo(point);

  pDC->SelectObject(pOldPen);                // Restore the old pen
}

// Add a segment to the curve
void CCurve::AddSegment(const CPoint& point)
{
  m_Points.push_back(point);                // Add the point to the end

  // Modify the enclosing rectangle for the new point
  m_EnclosingRect.DeflateRect(m_PenWidth, m_PenWidth);
  m_EnclosingRect = CRect { (std::min)(point.x, m_EnclosingRect.left), (std::min)(point.y, m_EnclosingRect.top),
                            (std::max)(point.x, m_EnclosingRect.right), (std::max)(point.y, m_EnclosingRect.bottom) };
  m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}

void CCurve::Move(const CSize& aSize)
{
  m_EnclosingRect += aSize;            // Move the rectangle
  m_StartPoint += aSize;               // Move the start point
  // Now move all the other points
  for (auto& p : m_Points)
    p += aSize;
}
