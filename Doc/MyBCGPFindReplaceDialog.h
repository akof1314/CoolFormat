#pragma once


#include "BCGCBPro.h"
#include "MyBCGPDlgImpl.h"

class CMyBCGPFindReplaceDialog : public CFindReplaceDialog
{
	DECLARE_DYNAMIC(CMyBCGPFindReplaceDialog)

public:
	CMyBCGPFindReplaceDialog();
	virtual ~CMyBCGPFindReplaceDialog();

protected:
	DECLARE_MESSAGE_MAP()
	CMyBCGPDlgImpl	m_Impl;
public:
	void EnableVisualManagerStyle (BOOL bEnable = TRUE, BOOL bNCArea = FALSE, const CList<UINT,UINT>* plstNonSubclassedItems = NULL);
	BOOL IsVisualManagerStyle () const
	{
		return m_Impl.m_bVisualManagerStyle;
	}

	BOOL IsVisualManagerNCArea () const
	{
		return m_Impl.m_bVisualManagerNCArea;
	}	

	BOOL EnableAero (BCGPMARGINS& margins);
	void GetAeroMargins (BCGPMARGINS& margins) const;

	BOOL HasAeroMargins () const
	{
		return m_Impl.HasAeroMargins ();
	}

	void UpdateCaptionButtons ()
	{
		m_Impl.UpdateCaptionButtons();
	}

	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcPaint();
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSysColorChange();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnChangeVisualManager(WPARAM, LPARAM);
	afx_msg LRESULT OnSetText(WPARAM, LPARAM);
	
};


