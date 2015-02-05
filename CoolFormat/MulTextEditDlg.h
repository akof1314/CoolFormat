#pragma once

// CMulTextEditDlg 对话框

class CMulTextEditDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CMulTextEditDlg)

public:
	CMulTextEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMulTextEditDlg();

	void SetText(LPCTSTR lpszText);
	LPCTSTR GetText();

// 对话框数据
	enum { IDD = IDD_MULTEXT_EDIT_DLG };

	virtual BOOL OnInitDialog();

protected:
	CString m_strValue;
	void InitLang();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
