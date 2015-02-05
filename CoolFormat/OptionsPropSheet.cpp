// BCGEX\OptionsPropSheet.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "OptionsPropSheet.h"


// COptionsPropSheet

// IMPLEMENT_DYNAMIC(COptionsPropSheet, CPropertySheet)

COptionsPropSheet::COptionsPropSheet (CWnd* pWndParent, UINT nSelectedPage) :
CBCGPPropertySheet (IDS_STRING_OPTIONS, pWndParent, nSelectedPage)
{
	m_Icons.SetImageSize (CSize (32, 32));
	m_Icons.Load (IDB_OPTIONS);

	CBCGPControlRendererParams params((UINT)0, CLR_DEFAULT, 
		CRect (0, 0, 350, 60), CRect (83, 58, 266, 1), 
		CRect (0, 0, 0, 0), CRect (0, 0, 0, 0), FALSE);
}

void COptionsPropSheet::OnDrawPageHeader (CDC* pDC, int nPage, CRect rectHeader)
{
	CSize sizeIcon = m_Icons.GetImageSize ();
	CBCGPDrawManager dm (*pDC);
	COLORREF clrBegin = RGB(0, 0, 0);
	COLORREF clrFinish = RGB(0, 0, 0);
	
	switch (CBCGPVisualManager2010::GetStyle())
	{
	case CBCGPVisualManager2010::VS2010_Blue:
		clrBegin = RGB(207, 221, 238);
		clrFinish = RGB(186, 202, 222);
		break;

	case CBCGPVisualManager2010::VS2010_Black:
		clrBegin = RGB(131, 131, 131);
		clrFinish = RGB(57, 57, 57);
		break;

	case CBCGPVisualManager2010::VS2010_Silver:
		clrBegin = RGB(233, 237, 241);
		clrFinish = RGB(200, 204, 209);
		break;
	}
	dm.FillGradient (rectHeader, clrBegin, clrFinish);

	rectHeader.bottom -= 10;

	CRect rectIcon = rectHeader;

	rectIcon.left += 20;
	rectIcon.right = rectIcon.left + sizeIcon.cx;

	m_Icons.DrawEx (pDC, rectIcon, nPage, CBCGPToolBarImages::ImageAlignHorzLeft, CBCGPToolBarImages::ImageAlignVertCenter);

	CString strText;
	BOOL bNameVaild;
	switch (nPage)
	{
	case 0:
		bNameVaild = strText.LoadString(IDS_STRING_CHANGEOPTIONS);
		ASSERT(bNameVaild);
		break;

	case 1:
		bNameVaild = strText.LoadString(IDS_STRING_CHANGEVISIT);
		ASSERT(bNameVaild);
		break;

	case 2:
		bNameVaild = strText.LoadString(IDS_STRING_LINKEUPDATE);
		ASSERT(bNameVaild);
		break;
	}

	CRect rectText = rectHeader;
	rectText.left = rectIcon.right + 10;
	rectText.right -= 20;

	CFont* pOldFont = pDC->SelectObject (&globalData.fontBold);
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor (globalData.clrBarText);

	UINT uiFlags = DT_SINGLELINE | DT_VCENTER;

	CRect rectTextCalc = rectText;
	pDC->DrawText (strText, rectTextCalc, uiFlags | DT_CALCRECT);

	if (rectTextCalc.right > rectText.right)
	{
		rectText.DeflateRect (0, 10);
		uiFlags = DT_WORDBREAK;
	}

	pDC->DrawText (strText, rectText, uiFlags);

	pDC->SelectObject (pOldFont);
}

BOOL COptionsPropSheet::OnInitDialog()
{
	BOOL bResult = CBCGPPropertySheet::OnInitDialog();
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDOK);
	ASSERT(bNameVaild);
	SetDlgItemText(IDOK, strTemp);

	bNameVaild = strTemp.LoadString(IDCANCEL);
	ASSERT(bNameVaild);
	SetDlgItemText(IDCANCEL, strTemp);

	return bResult;
}
