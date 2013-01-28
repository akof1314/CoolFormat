#pragma once

//////////////////////////////////////////////////////////////////////////
// CTellBug 对话框

class CTellBug : public CBCGPDialog
{
	DECLARE_DYNAMIC(CTellBug)

public:
	CTellBug(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTellBug();

// 对话框数据
	enum { IDD = IDD_TELL_BUG };

protected:
	CBCGPURLLinkButton m_btnLinkEmail;
	CBCGPURLLinkButton m_btnLinkCsdn;
	CBCGPURLLinkButton m_btnLinkQQ;

	void InitLang();
	void SetLinkBtn();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
