#pragma once
#include "SetPageCppFast.h"
#include "SetPageCppHigh.h"

//////////////////////////////////////////////////////////////////////////
// 
class CBCGPDlgTabWnd : public CBCGPTabWnd
{
	friend class CSetPageCpp;
	friend class CSetPageHtml;
	CBCGPDlgTabWnd();
};

//////////////////////////////////////////////////////////////////////////
// CSetPageCpp 对话框

class CSetPageCpp : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CSetPageCpp)

public:
	CSetPageCpp();
	CSetPageCpp(UINT nLangID, UINT nIDCaption);
	virtual ~CSetPageCpp();

// 对话框数据
	enum { IDD = IDD_SET_CPP };
protected:
	CStatic m_wndTabsArea;
	CBCGPDlgTabWnd m_wndCppTabs;

	CSetPageCppFast m_wndFast;
	CSetPageCppHigh m_wndHigh;
	UINT m_onlyCppJavaCS;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
