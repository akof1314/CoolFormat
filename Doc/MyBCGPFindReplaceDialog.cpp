// MyBCGPFindReplaceDialog.cpp : 实现文件
//

#include "stdafx.h"

#include "MyBCGPFindReplaceDialog.h"


// CMyBCGPFindReplaceDialog

IMPLEMENT_DYNAMIC(CMyBCGPFindReplaceDialog, CFindReplaceDialog)

CMyBCGPFindReplaceDialog::CMyBCGPFindReplaceDialog()
	:m_Impl(*this)
{

}

CMyBCGPFindReplaceDialog::~CMyBCGPFindReplaceDialog()
{
}


BEGIN_MESSAGE_MAP(CMyBCGPFindReplaceDialog, CFindReplaceDialog)
	ON_WM_ACTIVATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_GETMINMAXINFO()
	ON_WM_MOUSEMOVE()
	ON_WM_NCACTIVATE()
	ON_WM_NCCALCSIZE()
	ON_WM_NCHITTEST()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCPAINT()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(BCGM_CHANGEVISUALMANAGER, OnChangeVisualManager)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_WM_SYSCOLORCHANGE()
END_MESSAGE_MAP()



// CMyBCGPFindReplaceDialog 消息处理程序



void CMyBCGPFindReplaceDialog::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	m_Impl.OnActivate (nState, pWndOther);
}



void CMyBCGPFindReplaceDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_Impl.OnLButtonDown (point);
	CFindReplaceDialog::OnLButtonDown(nFlags, point);
}

void CMyBCGPFindReplaceDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_Impl.OnLButtonUp (point);
	CFindReplaceDialog::OnLButtonUp(nFlags, point);
}

void CMyBCGPFindReplaceDialog::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	m_Impl.OnGetMinMaxInfo (lpMMI);
	CFindReplaceDialog::OnGetMinMaxInfo(lpMMI);
}

void CMyBCGPFindReplaceDialog::OnMouseMove(UINT nFlags, CPoint point)
{
	m_Impl.OnMouseMove (point);
	CFindReplaceDialog::OnMouseMove(nFlags, point);
}

BOOL CMyBCGPFindReplaceDialog::OnNcActivate(BOOL bActive)
{
	BOOL bRes = (BOOL)DefWindowProc (WM_NCACTIVATE, bActive, 0L);

	if (bRes)
	{
		m_Impl.OnNcActivate (bActive);
	}

	return bRes;
}

void CMyBCGPFindReplaceDialog::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	if (!m_Impl.OnNcCalcSize (bCalcValidRects, lpncsp))
	{
		CFindReplaceDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
	}
}

LRESULT CMyBCGPFindReplaceDialog::OnNcHitTest(CPoint point)
{
	BCGNcHitTestType nHit = m_Impl.OnNcHitTest (point);
	if (nHit != HTNOWHERE)
	{
		return nHit;
	}
	return CFindReplaceDialog::OnNcHitTest(point);
}

void CMyBCGPFindReplaceDialog::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	m_Impl.OnNcMouseMove (nHitTest, point);
	CFindReplaceDialog::OnNcMouseMove(nHitTest, point);
}

void CMyBCGPFindReplaceDialog::OnNcPaint()
{
	if (!m_Impl.OnNcPaint ())
	{
		Default ();
	}
}

void CMyBCGPFindReplaceDialog::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	if ((lpwndpos->flags & SWP_FRAMECHANGED) == SWP_FRAMECHANGED)
	{
		m_Impl.OnWindowPosChanged (lpwndpos);
	}
	CFindReplaceDialog::OnWindowPosChanged(lpwndpos);
}

BOOL CMyBCGPFindReplaceDialog::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (m_Impl.OnCommand (wParam, lParam))
	{
		return TRUE;
	}

	return CFindReplaceDialog::OnCommand(wParam, lParam);
}

BOOL CMyBCGPFindReplaceDialog::PreTranslateMessage(MSG* pMsg)
{
	if (m_Impl.PreTranslateMessage (pMsg))
	{
		return TRUE;
	}

	return CFindReplaceDialog::PreTranslateMessage(pMsg);
}

int CMyBCGPFindReplaceDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFindReplaceDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	return m_Impl.OnCreate();	
}

void CMyBCGPFindReplaceDialog::OnDestroy()
{
	m_Impl.OnDestroy();
	CFindReplaceDialog::OnDestroy();
}

HBRUSH CMyBCGPFindReplaceDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (IsVisualManagerStyle ())
	{
		HBRUSH hbr = m_Impl.OnCtlColor (pDC, pWnd, nCtlColor);
		if (hbr != NULL)
		{
			return hbr;
		}
	}
	return CFindReplaceDialog::OnCtlColor(pDC, pWnd, nCtlColor);	
}

BOOL CMyBCGPFindReplaceDialog::OnEraseBkgnd(CDC* pDC)
{
	BOOL bRes = TRUE;

	if (!IsVisualManagerStyle ())
	{
		bRes = CFindReplaceDialog::OnEraseBkgnd (pDC);
	}
	else
	{
		ASSERT_VALID (pDC);

		CRect rectClient;
		GetClientRect (rectClient);
		if (IsVisualManagerStyle ())
		{
			if (!CBCGPVisualManager::GetInstance ()->OnFillDialog (pDC, this, rectClient))
			{
				CFindReplaceDialog::OnEraseBkgnd (pDC);
			}
		}				
	}
	m_Impl.DrawResizeBox(pDC);
	m_Impl.ClearAeroAreas (pDC);
	return bRes;
}

void CMyBCGPFindReplaceDialog::OnSize(UINT nType, int cx, int cy)
{
	BOOL bIsMinimized = (nType == SIZE_MINIMIZED);

	if (m_Impl.IsOwnerDrawCaption ())
	{
		CRect rectWindow;
		GetWindowRect (rectWindow);

		WINDOWPOS wndpos;
		wndpos.flags = SWP_FRAMECHANGED;
		wndpos.x     = rectWindow.left;
		wndpos.y     = rectWindow.top;
		wndpos.cx    = rectWindow.Width ();
		wndpos.cy    = rectWindow.Height ();

		m_Impl.OnWindowPosChanged (&wndpos);
	}

	m_Impl.UpdateCaption ();
	CFindReplaceDialog::OnSize(nType, cx, cy);	
}

BOOL CMyBCGPFindReplaceDialog::OnInitDialog()
{
	CFindReplaceDialog::OnInitDialog();

	m_Impl.m_bHasBorder = (GetStyle () & WS_BORDER) != 0;

	if (IsVisualManagerStyle ())
	{
		m_Impl.EnableVisualManagerStyle (TRUE, IsVisualManagerNCArea ());
	}

	if (m_Impl.HasAeroMargins ())
	{
		m_Impl.EnableAero (m_Impl.m_AeroMargins);
	}		

	return TRUE; 
}

void CMyBCGPFindReplaceDialog::EnableVisualManagerStyle( BOOL bEnable /*= TRUE*/, BOOL bNCArea /*= FALSE*/, const CList<UINT,UINT>* plstNonSubclassedItems /*= NULL*/ )
{
	ASSERT_VALID (this);

	m_Impl.EnableVisualManagerStyle (bEnable, bEnable && bNCArea, plstNonSubclassedItems);

	if (bEnable && bNCArea)
	{
		m_Impl.OnChangeVisualManager ();
	}
}

BOOL CMyBCGPFindReplaceDialog::EnableAero( BCGPMARGINS& margins )
{
	return m_Impl.EnableAero (margins);
}

void CMyBCGPFindReplaceDialog::GetAeroMargins( BCGPMARGINS& margins ) const
{
	m_Impl.GetAeroMargins (margins);
}

LRESULT CMyBCGPFindReplaceDialog::OnChangeVisualManager (WPARAM, LPARAM)
{
	m_Impl.OnChangeVisualManager ();
	return 0;
}

LRESULT CMyBCGPFindReplaceDialog::OnSetText(WPARAM, LPARAM) 
{
	LRESULT	lRes = Default();

	if (lRes && IsVisualManagerStyle () && IsVisualManagerNCArea ())
	{
		RedrawWindow (NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
	}

	return lRes;
}
void CMyBCGPFindReplaceDialog::OnSysColorChange()
{
	CFindReplaceDialog::OnSysColorChange();	

	if (AfxGetMainWnd () == this)
	{
		globalData.UpdateSysColors ();
	}
}
