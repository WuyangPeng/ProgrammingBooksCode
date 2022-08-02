
// TextEditorView.h : interface of the CTextEditorView class
//

#pragma once


class CTextEditorView : public CEditView
{
protected: // create from serialization only
	CTextEditorView();
	DECLARE_DYNCREATE(CTextEditorView)

// Attributes
public:
	CTextEditorDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTextEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TextEditorView.cpp
inline CTextEditorDoc* CTextEditorView::GetDocument() const
   { return reinterpret_cast<CTextEditorDoc*>(m_pDocument); }
#endif

