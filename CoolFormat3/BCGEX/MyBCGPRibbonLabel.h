/** 
 * @file MyBCGPRibbonLabel.h
 * @brief 扩展CBCGPRibbonLabel实现文本显示时，不去掉空格
 * @author 无幻 
 * @date 2012-4-3
 * @details 
 */ 
#pragma once

//////////////////////////////////////////////////////////////////////////
// CMyBCGPRibbonLabel 命令目标

class CMyBCGPRibbonLabel : public CBCGPRibbonLabel
{
	DECLARE_DYNCREATE(CMyBCGPRibbonLabel)
public:
	CMyBCGPRibbonLabel (LPCTSTR lpszText, BOOL bIsMultiLine = FALSE);
	virtual ~CMyBCGPRibbonLabel();

	void SetTextEx(LPCTSTR lpszText);

protected:
	CMyBCGPRibbonLabel();
};


