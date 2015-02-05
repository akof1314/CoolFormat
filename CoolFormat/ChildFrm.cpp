// ChildFrm.cpp : implementation of the CChildFrame class
//
#include "stdafx.h"
#include "CoolFormat3.h"
#include "CoolFormat3Doc.h"
#include "CoolFormat3View.h"

#include "ChildFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CBCGPMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CBCGPMDIChildWnd)
	ON_WM_CREATE()
	ON_WM_MDIACTIVATE()
END_MESSAGE_MAP()


// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{	
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CBCGPMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style &= ~WS_SYSMENU;

	return TRUE;
}


// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CBCGPMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CBCGPMDIChildWnd::Dump(dc);
}

#endif //_DEBUG


// CChildFrame message handlers

void CChildFrame::ActivateFrame(int /*nCmdShow*/)
{
	CBCGPMDIChildWnd::ActivateFrame(SW_SHOWMAXIMIZED);
}

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STRING_OUTPUT);
	ASSERT(bNameVaild);
	if (!m_wndOutput.Create(strTemp, this, CRect(0, 0, 200, 100), TRUE, ID_OUTPUT_BAR,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM))
	{
		TRACE(_T("Failed to create output bar\n"));
		return FALSE;
	}
	m_wndOutput.SetIcon(AfxGetApp()->LoadIcon(IDI_OUTPUT_BAR_HC), FALSE);
	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHideBars(CBRS_ALIGN_ANY);
	GetDockManager()->EnableDockBarMenu(TRUE);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndOutput);
	m_wndOutput.ShowControlBar(FALSE, FALSE, FALSE);

	return 0;
}

void CChildFrame::OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd)
{
	CBCGPMDIChildWnd::OnMDIActivate(bActivate, pActivateWnd, pDeactivateWnd);
	if (bActivate && pActivateWnd->GetSafeHwnd() && pDeactivateWnd->GetSafeHwnd())
	{
		CView *pView = ((CChildFrame*)pActivateWnd)->GetActiveView();
		if (pView == NULL)
		{
			return;
		}
		CBCGPTabWnd *pTabctrl = (CBCGPTabWnd *)pView->GetParent();
		if (pTabctrl == NULL)
		{
			return;
		}
		CCoolFormat3View *pTabView = (CCoolFormat3View *)pTabctrl->GetParent();
		CSynBCGPEditView *pSynView = pTabView->GetSynView();
		if (pSynView != NULL)
		{
			pSynView->ReSetLangLabel();
			pSynView->ReSetEncodingLabel();
		}
	}
}
//////////////////////////////////////////////////////////////////////////
void CChildFrame::AddOutputMsg( LPCTSTR lpszMsg )
{
	m_wndOutput.AddMsgToEdit(lpszMsg);
}