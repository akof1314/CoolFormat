#pragma once


// CLangExtEditDlg 对话框

class CLangExtEditDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CLangExtEditDlg)

public:
	CLangExtEditDlg(const CString &strLang, const CString &strExt, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLangExtEditDlg();
	LPCTSTR GetStrExt(){return m_strExt.Trim();}
// 对话框数据
	enum { IDD = IDD_LANG_EXT_EDIT };

protected:
	CString m_strLang;
	CString m_strExt;
	void InitLang();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
};
