#include "stdafx.h"
#include "MyBCGPRibbonStatusBarPane.h"

IMPLEMENT_DYNCREATE(CMyBCGPRibbonStatusBarPane, CBCGPRibbonStatusBarPane)

// CMyBCGPRibbonStatusBarPane

CMyBCGPRibbonStatusBarPane::CMyBCGPRibbonStatusBarPane()
	:CBCGPRibbonStatusBarPane()
{
}

CMyBCGPRibbonStatusBarPane::CMyBCGPRibbonStatusBarPane(UINT nCmdID, /* Pane command id */ LPCTSTR lpszText, /* Pane label */ BOOL bIsStatic /*= FALSE*/, /* Pane is static (non-clickable) */ HICON hIcon /*= NULL*/, /* Pane icon */ LPCTSTR lpszAlmostLargeText /*= NULL*/, /* The almost large text in pane */ BOOL bAlphaBlendIcon /*= FALSE*/)
	:CBCGPRibbonStatusBarPane(nCmdID, lpszText, bIsStatic, hIcon, lpszAlmostLargeText, bAlphaBlendIcon)
{
}

CMyBCGPRibbonStatusBarPane::~CMyBCGPRibbonStatusBarPane()
{
}

void CMyBCGPRibbonStatusBarPane::OnDrawMenuArrow(CDC* /*pDC*/, const CRect& /*rectMenuArrow*/)
{
}
