// Element.cpp : implementation file
//

#include "stdafx.h"
#include "Sketcher.h"
#include "Element.h"


// CElement

CElement::CElement()
{
}

CElement::CElement(const CPoint& start, COLORREF color, int penWidth, int lineStyle) :
m_StartPoint{ start }, m_PenWidth{ penWidth }, m_Color{ color }, m_LineStyle{ lineStyle } {}

CElement::~CElement()
{
}


// CElement member functions
