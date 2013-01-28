// kofColorButton.cpp : 实现文件
//

#include "stdafx.h"
#include "kofColorButton.h"


// CkofColorButton

IMPLEMENT_DYNAMIC(CkofColorButton, CButton)

CkofColorButton::CkofColorButton(COLORREF color)
: m_Color(color)
{
}

CkofColorButton::~CkofColorButton()
{
}

BEGIN_MESSAGE_MAP(CkofColorButton, CButton)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CkofColorButton::PreSubclassWindow()
{
	CButton::PreSubclassWindow();
	ModifyStyle(0, BS_OWNERDRAW); 
}

void CkofColorButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	ASSERT(lpDIS->CtlType == ODT_BUTTON);

	CDC* pDCPaint = CDC::FromHandle (lpDIS->hDC);
	ASSERT_VALID (pDCPaint);

	CBCGPMemDC memDC (*pDCPaint, this);
	CDC* pDC = &memDC.GetDC ();
	
	CRect rc = lpDIS->rcItem;

	CBCGPDrawManager dm (*pDC);
	if (lpDIS->itemState & ODS_DISABLED)
	{
		dm.DrawRect (rc, RGB(240, 240, 240), (COLORREF)-1);	
	}
	else
	{
		dm.DrawRect (rc, m_Color, (COLORREF)-1);	
	}
	dm.DrawRect (rc, (COLORREF)-1, globalData.clrBarShadow);
	rc.DeflateRect (1, 1);
	dm.DrawRect (rc, (COLORREF)-1, globalData.clrWindow);
}

void CkofColorButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	CBCGPColorDialog dlg(m_Color);
	if (dlg.DoModal() == IDOK)
	{
		SetColor(dlg.GetColor());
	}
	SetFocus();
}

void CkofColorButton::SetColor( COLORREF color )
{
	m_Color = color;

	if (GetSafeHwnd () != NULL)
	{
		Invalidate ();
		UpdateWindow ();
	}
}