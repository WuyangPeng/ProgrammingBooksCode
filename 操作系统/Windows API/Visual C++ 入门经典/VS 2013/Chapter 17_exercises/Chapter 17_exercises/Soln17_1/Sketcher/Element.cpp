// Element.cpp : implementation file
//

#include "stdafx.h"
#include "Sketcher.h"
#include "Element.h"


// CElement
IMPLEMENT_SERIAL(CElement, CObject, VERSION_NUMBER)
CElement::CElement()
{
}

CElement::CElement(const CPoint& start, COLORREF color, int penWidth) :
m_StartPoint { start }, m_PenWidth { penWidth }, m_Color { color } {}

CElement::~CElement()
{
}

void CElement::Serialize(CArchive& ar)
{
  CObject::Serialize(ar);              // Call the base class function

  if (ar.IsStoring())
  { // Writing to the file
    ar << m_StartPoint                // Element position 
      << m_PenWidth                  // The pen width
      << m_Color                     // The element color
      << m_EnclosingRect;            // The enclosing rectangle
  }
  else
  {  // Reading from the file
    ar >> m_StartPoint                // Element position 
      >> m_PenWidth                  // The pen width
      >> m_Color                     // The element color
      >> m_EnclosingRect;            // The enclosing rectangle
  }
}

// CElement member functions
