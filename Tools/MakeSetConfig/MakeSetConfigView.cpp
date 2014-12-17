
// MakeSetConfigView.cpp : implementation of the CMakeSetConfigView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MakeSetConfig.h"
#endif

#include "MakeSetConfigDoc.h"
#include "MakeSetConfigView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMakeSetConfigView

IMPLEMENT_DYNCREATE(CMakeSetConfigView, CEditView)

BEGIN_MESSAGE_MAP(CMakeSetConfigView, CEditView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CMakeSetConfigView construction/destruction

CMakeSetConfigView::CMakeSetConfigView()
{
	// TODO: add construction code here

}

CMakeSetConfigView::~CMakeSetConfigView()
{
}

BOOL CMakeSetConfigView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

void CMakeSetConfigView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMakeSetConfigView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMakeSetConfigView diagnostics

#ifdef _DEBUG
void CMakeSetConfigView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMakeSetConfigView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMakeSetConfigDoc* CMakeSetConfigView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMakeSetConfigDoc)));
	return (CMakeSetConfigDoc*)m_pDocument;
}
#endif //_DEBUG


// CMakeSetConfigView message handlers


void CMakeSetConfigView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();

	SetFont(&afxGlobalData.fontRegular);

	//GetEditCtrl().SetReadOnly(TRUE);
}

void CMakeSetConfigView::SetConfigText(const CString& strText)
{
	GetEditCtrl().SetWindowText(strText);
}


void CMakeSetConfigView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	//CEditView::OnChar(nChar, nRepCnt, nFlags);
}
