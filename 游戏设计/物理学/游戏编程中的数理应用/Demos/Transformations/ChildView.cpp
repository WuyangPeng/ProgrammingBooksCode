// ChildView.cpp : implementation of the CChildView class
//
// ©New Riders, 2003. All rights reserved.
// Created By: Mike Fawcett & Mike Wigand

#include "stdafx.h"
#include "TransformationsApp.h"
#include "ChildView.h"
#include "OpenGL.h"
#include "EntityManager.h"

RECT rect;
OpenGL* view = OpenGL::getInstance();

// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()													// Responds when the user presses the LButton
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	static int init = 0;

	if (init == 0)
	{
		view->InitializeGL(GetDC());

		GetClientRect(&rect);

		view->Reshape(rect.right, rect.bottom);
	}


	CPaintDC dc(this); // device context for painting

	
	// TODO: Add your message handler code here
	view->Render();
	// Do not call CWnd::OnPaint() for painting messages
}

afx_msg void CChildView::OnLButtonDown(UINT flags, CPoint pos)
{
	OpenGL* view = OpenGL::getInstance();

	pos.x -= viewWidth/2;
	pos.y -= viewHeight/2;
	pos.y *= -1;

	pos.x /= 15;
	pos.y /= 15;

	EntityManager* EMan = EntityManager::getInstance();
	EMan->Picking(pos);
	RECT rect;
	GetClientRect(&rect);
	InvalidateRect(&rect, true);
}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	//DialogBox("Test", "Test", NULL);
	GetClientRect(&rect);

	viewWidth = rect.right;
	viewHeight = rect.bottom;

	view->Reshape(rect.right, rect.bottom);
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{

	return 0;
}