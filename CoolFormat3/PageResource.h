#pragma once

//////////////////////////////////////////////////////////////////////////
// CPageResource 对话框

class CPageResource : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CPageResource)

public:
	CPageResource();
	~CPageResource();

// 对话框数据
	enum { IDD = IDD_OPTIONS_PAGE_RESOURCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void InitLang();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCheckupdate();
	afx_msg void OnBnClickedButtonLinkme();
	afx_msg void OnBnClickedButtonAbout();
	virtual BOOL OnInitDialog();
};
