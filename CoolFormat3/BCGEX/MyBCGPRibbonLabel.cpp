// BCGEX\MyBCGPRibbonLabel.cpp : 实现文件
//

#include "stdafx.h"
#include "MyBCGPRibbonLabel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMyBCGPRibbonLabel, CBCGPRibbonLabel)

// CMyBCGPRibbonLabel

CMyBCGPRibbonLabel::CMyBCGPRibbonLabel(LPCTSTR lpszText, BOOL bIsMultiLine)
:CBCGPRibbonLabel(lpszText, bIsMultiLine)
{
}

CMyBCGPRibbonLabel::CMyBCGPRibbonLabel()
{

}
CMyBCGPRibbonLabel::~CMyBCGPRibbonLabel()
{
}

void CMyBCGPRibbonLabel::SetTextEx( LPCTSTR lpszText )
{
	ASSERT_VALID (this);
	m_strText = lpszText == NULL ? _T("") : lpszText;

	int nIndex = m_strText.Find (_T('\n'));
	if (nIndex >= 0)
	{
		m_strKeys = m_strText.Mid (nIndex + 1);
		m_strText = m_strText.Left (nIndex);
	}

	m_arWordIndexes.RemoveAll ();
}

// CMyBCGPRibbonLabel 成员函数
