#pragma once

//////////////////////////////////////////////////////////////////////////
// COutputViewBar

class COutputViewBar : public CBCGPDockingControlBar
{
public:
	COutputViewBar();
	virtual ~COutputViewBar();
	
	void AddMsgToEdit(LPCTSTR lpszMsg);

protected:
	CBCGPEdit m_edtOutput;
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};