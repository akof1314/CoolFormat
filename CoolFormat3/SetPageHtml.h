#pragma once
#include "SetPageCpp.h"
#include "SetPageHtmlOne.h"
#include "SetPageHtmlTwo.h"
class CBCGPDlgTabWnd : public CBCGPTabWnd
{
	friend class CSetPageCpp;
	friend class CSetPageHtml;
	CBCGPDlgTabWnd();
};
//////////////////////////////////////////////////////////////////////////
// CSetPageHtml 对话框

class CSetPageHtml : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CSetPageHtml)
public:
	CSetPageHtml();
	CSetPageHtml(UINT nLangID, UINT nIDCaption);
	virtual ~CSetPageHtml();

// 对话框数据
	enum { IDD = IDD_SET_HTML };
protected:
	CStatic m_wndTabsArea;
	CBCGPDlgTabWnd m_wndHtmlTabs;

	CSetPageHtmlOne m_wndOne;
	CSetPageHtmlTwo m_wndTwo;
	UINT m_onlyHtmlXml;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
