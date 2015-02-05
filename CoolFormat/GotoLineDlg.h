#pragma once

//////////////////////////////////////////////////////////////////////////
// CGotoLineDlg 对话框

class CGotoLineDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CGotoLineDlg)

public:
	CGotoLineDlg(CWnd* pParent = NULL, int nMaxLine = 1);   // 标准构造函数
	virtual ~CGotoLineDlg();

// 对话框数据
	enum { IDD = IDD_GOTO_LINE };

protected:
	int m_nMaxLine;
	void InitLang();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nLineNumber;
	virtual BOOL OnInitDialog();
};
