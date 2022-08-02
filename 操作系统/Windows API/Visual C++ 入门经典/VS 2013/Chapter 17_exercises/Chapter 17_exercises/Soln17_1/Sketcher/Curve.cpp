#include "stdafx.h"
#include "Curve.h"
#include <algorithm>

IMPLEMENT_SERIAL(CCurve, CElement, VERSION_NUMBER)

// Constructor for a curve object
CCurve::CCurve(const CPoint& first, const CPoint& second, COLORREF color, int penWidth) :
CElement { first, color, penWidth }
{
  // Store the second point in the vector
  m_Points.push_back(second);
  m_EnclosingRect = CRect {
    (std::min)(first.x, second.x), (std::min)(first.y, second.y),
    (std::max)(first.x, second.x), (std::max)(first.y, second.y) };
  int width { penWidth == 0 ? 1 : penWidth }; // Inflate rect by at least 1
  m_EnclosingRect.InflateRect(width, width);
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
  int width(m_PenWidth == 0 ? 1 : m_PenWidth); // Deflate rect by at least 1
  m_EnclosingRect.DeflateRect(width, width);
  m_EnclosingRect = CRect { (std::min)(point.x, m_EnclosingRect.left), (std::min)(point.y, m_EnclosingRect.top),
                            (std::max)(point.x, m_EnclosingRect.right), (std::max)(point.y, m_EnclosingRect.bottom) };
  m_EnclosingRect.InflateRect(width, width);
}

void CCurve::Move(const CSize& aSize)
{
  m_EnclosingRect += aSize;            // Move the rectangle
  m_StartPoint += aSize;               // Move the start point
  // Now move all the other points
  for (auto& p : m_Points)
    p += aSize;
}

void CCurve::Serialize(CArchive& ar)
{
  CElement::Serialize(ar);             // Call the base class function
  // Serialize the vector of points
  if (ar.IsStoring())
  {
    ar << m_Points.size();             // Store the point count
    // Now store the points
    for (const auto& point : m_Points)
      ar << point;
  }
  else
  {
    size_t nPoints{};                  // Stores number of points
    ar >> nPoints;                     // Retrieve the number of points
    // Now retrieve the points
    CPoint point;
    for (size_t i{}; i < nPoints; ++i)
    {
      ar >> point;
      m_Points.push_back(point);
    }
  }
}
