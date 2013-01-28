#pragma once

//////////////////////////////////////////////////////////////////////////
// CSetPageCppFast 对话框

class CSetPageCppFast : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetPageCppFast)
public:
	CSetPageCppFast(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetPageCppFast();

// 对话框数据
	enum { IDD = IDD_SET_CPP_FAST };
	void SetViewEditWnd(CWnd *pWnd){m_pEditWnd = pWnd;};
	void SetTidyConfig(LPCTSTR lpszTidy);
	void GetTidyConfig(CString &strTidyValue);

protected:
	CWnd *m_pEditWnd; //保存预览框句柄
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedStyleRadio();
	virtual BOOL OnInitDialog();
};
