#include "stdafx.h"
#include "OutputViewBar.h"

//////////////////////////////////////////////////////////////////////////
// COutputViewBar

COutputViewBar::COutputViewBar()
{

}

COutputViewBar::~COutputViewBar()
{
}

BEGIN_MESSAGE_MAP(COutputViewBar, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

int COutputViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectClient(0, 0, lpCreateStruct->cx, lpCreateStruct->cy);
	const DWORD dwStyle =  ES_MULTILINE | ES_AUTOHSCROLL | ES_WANTRETURN | WS_VSCROLL | WS_HSCROLL | WS_CHILD | WS_VISIBLE;

	if (!m_edtOutput.Create(dwStyle, rectClient, this, 1))
	{
		TRACE0("Failed to create output window\n");
		return -1;
	}
	m_edtOutput.SetFont(&globalData.fontRegular);

	return 0;
}

void COutputViewBar::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	CRect rc;
	GetClientRect(rc);
	m_edtOutput.SetWindowPos(NULL, 1, 1, rc.Width() - 2, rc.Height() - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void COutputViewBar::OnPaint()
{
	CPaintDC dc(this);
	CRect rectEdit;
	m_edtOutput.GetWindowRect(rectEdit);
	ScreenToClient(rectEdit);

	rectEdit.InflateRect(1, 1);
	dc.Draw3dRect(rectEdit, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void COutputViewBar::OnSetFocus(CWnd* pOldWnd)
{
	CBCGPDockingControlBar::OnSetFocus(pOldWnd);
	m_edtOutput.SetFocus();
}

void COutputViewBar::AddMsgToEdit( LPCTSTR lpszMsg )
{
	if (m_edtOutput.GetSafeHwnd())
	{
		CString strMsg(lpszMsg);
		strMsg.TrimRight();
		m_edtOutput.SetWindowText(strMsg);
		int nLen = strMsg.GetLength();
		if (nLen > 0)
		{
			ShowControlBar(TRUE, FALSE, FALSE);
			m_edtOutput.SetSel(nLen, nLen);			
		}
		else
		{
			if (FALSE == IsAutoHideMode())
			{
				ShowControlBar(FALSE, FALSE, FALSE);
			}
		}
	}
}