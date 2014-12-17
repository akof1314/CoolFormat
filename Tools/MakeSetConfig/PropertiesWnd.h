
#pragma once

class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CMyMFCPropertyGridCtrl : public CMFCPropertyGridCtrl
{
public:
	void RemoveAllPropertyNoDelete(bool bAll);
	void OnChangeSelection(CMFCPropertyGridProperty* /*pNewSel*/, CMFCPropertyGridProperty* /*pOldSel*/);
	void OnPropertyChanged(CMFCPropertyGridProperty* pProp) const;
};

class CPropertiesWnd : public CDockablePane
{
// Construction
public:
	CPropertiesWnd();

	void ShowItemProp(CMFCPropertyGridProperty *pProp);
	void PropertyChanged(CMFCPropertyGridProperty* pProp);
	void ChangeSelection(CMFCPropertyGridProperty* pNewSel, CMFCPropertyGridProperty* /*pOldSel*/);

	void AdjustLayout();

// Attributes
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}

protected:
	CFont m_fntPropList;
	CPropertiesToolBar m_wndToolBar;
	CMyMFCPropertyGridCtrl m_wndPropList;

	void InitPropList();
	void SetPropListFont();
	BOOL IsComboType();
	BOOL IsSelectComboItem();

// Implementation
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnPropReset();
	afx_msg void OnPropAdditem();
	afx_msg void OnPropDelitem();
	afx_msg void OnUpdatePropAdditem(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePropDelitem(CCmdUI *pCmdUI);
	afx_msg void OnPropUpitem();
	afx_msg void OnPropDownitem();
	afx_msg void OnUpdatePropDownitem(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePropUpitem(CCmdUI *pCmdUI);
};

