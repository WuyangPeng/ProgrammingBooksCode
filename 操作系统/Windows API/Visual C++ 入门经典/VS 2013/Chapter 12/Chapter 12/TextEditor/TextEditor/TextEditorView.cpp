
// TextEditorView.cpp : implementation of the CTextEditorView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TextEditor.h"
#endif

#include "TextEditorDoc.h"
#include "TextEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTextEditorView

IMPLEMENT_DYNCREATE(CTextEditorView, CEditView)

BEGIN_MESSAGE_MAP(CTextEditorView, CEditView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTextEditorView construction/destruction

CTextEditorView::CTextEditorView()
{
	// TODO: add construction code here

}

CTextEditorView::~CTextEditorView()
{
}

BOOL CTextEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}


// CTextEditorView printing

BOOL CTextEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CTextEditorView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CTextEditorView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CTextEditorView diagnostics

#ifdef _DEBUG
void CTextEditorView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTextEditorView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CTextEditorDoc* CTextEditorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTextEditorDoc)));
	return (CTextEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CTextEditorView message handlers
