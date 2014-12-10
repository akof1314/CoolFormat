#pragma once

//////////////////////////////////////////////////////////////////////////
// CSetPageBase 对话框

class CSetPageBase : public CBCGPPropertyPage
{
	DECLARE_DYNAMIC(CSetPageBase)

public:
	CSetPageBase();
	virtual ~CSetPageBase();

// 对话框数据
	enum { IDD = IDD_SET_BASE };

protected:
	CBCGPPropList m_wndPropList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void SetViewEdit(LPCTSTR lpszText);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
