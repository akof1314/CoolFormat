// KofBCGPFontComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "KofBCGPFontComboBox.h"
#include "BCGPLocalResource.h"

// CKofBCGPFontComboBox
const int nImageHeight = 16;
const int nImageWidth = 16;

CKofBCGPFontComboBox::CKofBCGPFontComboBox()
{

}

CKofBCGPFontComboBox::~CKofBCGPFontComboBox()
{
}

BEGIN_MESSAGE_MAP(CKofBCGPFontComboBox, CBCGPFontComboBox)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CKofBCGPFontComboBox::OnPaint()
{
	if ((GetStyle () & 0x0003L) == CBS_SIMPLE)
	{
		Default ();
		return;
	}

	if (!m_bVisualManagerStyle && !m_bOnGlass)
	{
		Default ();
		return;
	}

	CPaintDC dc(this); // device context for painting
	BYTE alpha = 0;
	if (m_bOnGlass)
	{
		alpha = 255;
	}
	CBCGPMemDC memDC (dc, this, alpha);
	CDC* pDC = &memDC.GetDC ();

	CRect rectClient;
	GetClientRect (rectClient);

	CBCGPDrawManager dm (*pDC);
	dm.DrawRect (rectClient, globalData.clrWindow, (COLORREF)-1);
//  得注释掉这句话
// 	SendMessage (WM_PRINTCLIENT, (WPARAM) pDC->GetSafeHdc (), (LPARAM) PRF_CLIENT);
	const int cxDropDown = ::GetSystemMetrics (SM_CXVSCROLL) + 4;

	int nCurSel = GetCurSel();
	if (CB_ERR != nCurSel)
	{
		if (m_Images.GetSafeHandle () == NULL)
		{
			CBCGPLocalResource locaRes;
			m_Images.Create (IDB_BCGBARRES_FONT, nImageWidth, 0, RGB (255, 255, 255));
		}

		CFont fontSelected;
		CFont* pOldFont = NULL;
		CRect rc(rectClient);		
		rc.right -= cxDropDown;

		CBCGPFontDesc* pDesc = (CBCGPFontDesc*)GetItemDataPtr(nCurSel);
		if (pDesc != NULL)
		{			
			if (pDesc->m_nType & (DEVICE_FONTTYPE | TRUETYPE_FONTTYPE))
			{
				CPoint ptImage (rc.left + 3, rc.top + (rc.Height () - nImageHeight) / 2);
				m_Images.Draw (pDC, pDesc->GetImageIndex (), ptImage, ILD_NORMAL);
			}

			rc.left += nImageWidth + 9;

			if (m_bDrawUsingFont && pDesc->m_nCharSet != SYMBOL_CHARSET)
			{
				LOGFONT lf;
				globalData.fontRegular.GetLogFont (&lf);

				lstrcpy (lf.lfFaceName, pDesc->m_strName);

				if (pDesc->m_nCharSet != DEFAULT_CHARSET)
				{
					lf.lfCharSet = pDesc->m_nCharSet;
				}

				if (lf.lfHeight < 0)
				{
					lf.lfHeight -= 4;
				}
				else
				{
					lf.lfHeight += 4;
				}

				fontSelected.CreateFontIndirect (&lf);
				pOldFont = pDC->SelectObject (&fontSelected);
			}
		}

		CString strText;
		GetLBText (nCurSel, strText);

		pDC->DrawText (strText, rc, DT_SINGLELINE | DT_VCENTER);

		if (pOldFont != NULL)
		{
			pDC->SelectObject (pOldFont);
		}
	}

	m_rectBtn = rectClient;
	m_rectBtn.left = m_rectBtn.right - cxDropDown;

	m_rectBtn.DeflateRect (2, 2);

	CBCGPDrawOnGlass dog (m_bOnGlass);

	CKofBCGPToolbarComboBoxButton buttonDummy;
#ifndef _BCGSUITE_
	buttonDummy.m_bIsCtrl = TRUE;

	CBCGPVisualManager::GetInstance ()->OnDrawComboDropButton (
		pDC, m_rectBtn, !IsWindowEnabled (), m_bIsDroppedDown,
		m_bIsButtonHighlighted,
		&buttonDummy);
#else
	CMFCVisualManager::GetInstance ()->OnDrawComboDropButton (
		pDC, m_rectBtn, !IsWindowEnabled (), m_bIsDroppedDown,
		m_bIsButtonHighlighted,
		&buttonDummy);
#endif

	dm.DrawRect (rectClient, (COLORREF)-1, globalData.clrBarShadow);
	rectClient.DeflateRect (1, 1);
	dm.DrawRect (rectClient, (COLORREF)-1, globalData.clrWindow);
}
