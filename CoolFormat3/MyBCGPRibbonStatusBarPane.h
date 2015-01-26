/**
* @file MyBCGPRibbonStatusBarPane.h
* @brief 扩展CMyBCGPRibbonStatusBarPane实现不绘制箭头
* @author 无幻
* @date 2015-01-12
* @details
*/
#pragma once

//////////////////////////////////////////////////////////////////////////
// CMyBCGPRibbonStatusBarPane 命令目标

class CMyBCGPRibbonStatusBarPane : public CBCGPRibbonStatusBarPane
{
	DECLARE_DYNCREATE(CMyBCGPRibbonStatusBarPane)
public:
	CMyBCGPRibbonStatusBarPane();

	CMyBCGPRibbonStatusBarPane(
		UINT		nCmdID,						// Pane command id
		LPCTSTR		lpszText,					// Pane label
		BOOL		bIsStatic = FALSE,			// Pane is static (non-clickable)
		HICON		hIcon = NULL,				// Pane icon
		LPCTSTR		lpszAlmostLargeText = NULL,	// The almost large text in pane
		BOOL		bAlphaBlendIcon = FALSE);	// The icon is 32 bit

	virtual ~CMyBCGPRibbonStatusBarPane();

protected:
	virtual void OnDrawMenuArrow(CDC* pDC, const CRect& rectMenuArrow);
};


