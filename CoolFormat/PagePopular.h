#pragma once

//////////////////////////////////////////////////////////////////////////
// CPagePopular 对话框

class CPagePopular : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CPagePopular)

public:
	CPagePopular();
	~CPagePopular();

// 对话框数据
	enum { IDD = IDD_OPTIONS_PAGE_POPULAR_PAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void InitLang();

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int m_nColorStyle;
	int m_nTooltipStyle;
	int m_nLanguageStyle;
	virtual void OnOK();
};
