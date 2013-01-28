#pragma once

//////////////////////////////////////////////////////////////////////////
// CSetPageJson 对话框

class CSetPageJson : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CSetPageJson)
public:
	CSetPageJson();
	virtual ~CSetPageJson();

// 对话框数据
	enum { IDD = IDD_SET_JSON };
	void SetTidyConfig(LPCTSTR lpszTidy);
	void GetTidyConfig(CString &strTidyValue);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void InitLimit();
	void SetViewEdit(LPCTSTR lpszText);
	void SetTidyControl(LPCTSTR lpszTidy, int nPos, int nSize);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnSetfocusEditJsonIndentNumber();
	virtual void OnOK();
};
