#pragma once

class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFileView : public CDockablePane
{
// Construction
public:
	CFileView();

	void FillConfigView();
	void RefreshPropName(CMFCPropertyGridProperty* pProp);
	void SetFileModifiedFlag(BOOL bFlag);

	void AdjustLayout();
	void OnChangeVisualStyle();

// Attributes
protected:

	CTreeCtrl m_wndFileView;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;
	BOOL m_bModifiedFlag;

protected:
	void FillFileView();
	void DestoryAllItemData();
	void DestoryItemData(HTREEITEM hItem);
	BOOL IsSelectItemOpened();
	BOOL IsSelectItemGroup();
	CMFCPropertyGridProperty* GetSelectItemProp();
	HTREEITEM GetSelectItemGroup();
	BOOL IsOtherNoClosed();

// Implementation
public:
	virtual ~CFileView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	void OnTreeTVNSelchanging(NMHDR *pNMHDR, LRESULT *pResult);
	void OnTreeTVNEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnExplorerSave();
	afx_msg void OnExplorerClose();
	afx_msg void OnExplorerDelete();
	afx_msg void OnGroupAddprop();
	afx_msg void OnGroupDelprop();
	afx_msg void OnGroupUpprop();
	afx_msg void OnGroupDownprop();
	afx_msg void OnUpdateGroupDelprop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGroupUpprop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateGroupDownprop(CCmdUI *pCmdUI);
	afx_msg void OnUpdateOpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExplorerSave(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExplorerClose(CCmdUI *pCmdUI);
	afx_msg void OnUpdateExplorerDelete(CCmdUI *pCmdUI);
	afx_msg void OnGroupAddgroup();
	afx_msg void OnUpdateGroupAddgroup(CCmdUI *pCmdUI);
	afx_msg void OnGroupDelgroup();
	afx_msg void OnUpdateGroupDelgroup(CCmdUI *pCmdUI);
};

