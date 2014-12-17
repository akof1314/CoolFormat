
#include "stdafx.h"
#include "mainfrm.h"
#include "FileView.h"
#include "Resource.h"
#include "MakeSetConfig.h"
#include "MainLogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

#define TREE_VIEW_ID 4

CFileView::CFileView()
{
}

CFileView::~CFileView()
{
}

BEGIN_MESSAGE_MAP(CFileView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
	ON_NOTIFY(TVN_SELCHANGING, TREE_VIEW_ID, OnTreeTVNSelchanging)
	ON_COMMAND(ID_EXPLORER_SAVE, &CFileView::OnExplorerSave)
	ON_COMMAND(ID_EXPLORER_CLOSE, &CFileView::OnExplorerClose)
	ON_COMMAND(ID_EXPLORER_DELETE, &CFileView::OnExplorerDelete)
	ON_COMMAND(ID_GROUP_ADDPROP, &CFileView::OnGroupAddprop)
	ON_COMMAND(ID_GROUP_DELPROP, &CFileView::OnGroupDelprop)
	ON_COMMAND(ID_GROUP_UPPROP, &CFileView::OnGroupUpprop)
	ON_COMMAND(ID_GROUP_DOWNPROP, &CFileView::OnGroupDownprop)
	ON_UPDATE_COMMAND_UI(ID_GROUP_DELPROP, &CFileView::OnUpdateGroupDelprop)
	ON_UPDATE_COMMAND_UI(ID_GROUP_UPPROP, &CFileView::OnUpdateGroupUpprop)
	ON_UPDATE_COMMAND_UI(ID_GROUP_DOWNPROP, &CFileView::OnUpdateGroupDownprop)
	ON_UPDATE_COMMAND_UI(ID_OPEN, &CFileView::OnUpdateOpen)
	ON_UPDATE_COMMAND_UI(ID_EXPLORER_SAVE, &CFileView::OnUpdateExplorerSave)
	ON_UPDATE_COMMAND_UI(ID_EXPLORER_CLOSE, &CFileView::OnUpdateExplorerClose)
	ON_UPDATE_COMMAND_UI(ID_EXPLORER_DELETE, &CFileView::OnUpdateExplorerDelete)
	ON_COMMAND(ID_GROUP_ADDGROUP, &CFileView::OnGroupAddgroup)
	ON_UPDATE_COMMAND_UI(ID_GROUP_ADDGROUP, &CFileView::OnUpdateGroupAddgroup)
	ON_COMMAND(ID_GROUP_DELGROUP, &CFileView::OnGroupDelgroup)
	ON_UPDATE_COMMAND_UI(ID_GROUP_DELGROUP, &CFileView::OnUpdateGroupDelgroup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers

int CFileView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create view:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndFileView.Create(dwViewStyle, rectDummy, this, TREE_VIEW_ID))
	{
		TRACE0("Failed to create file view\n");
		return -1;      // fail to create
	}

	// Load view images:
	m_FileViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* Is locked */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// Fill in some static tree view data (dummy code, nothing magic here)
	AdjustLayout();

	return 0;
}

void CFileView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CFileView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndFileView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	UINT uID = IDR_POPUP_EXPLORER;
	if (point != CPoint(-1, -1))
	{
		// Select clicked item:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
			if (pWndTree->GetItemData(hTreeItem))
			{
				uID = IDR_MENU_GROUP;
			}
		}
	}

	pWndTree->SetFocus();
	theApp.GetContextMenuManager()->ShowPopupMenu(uID, point.x, point.y, this, TRUE);
}

void CFileView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndFileView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CFileView::OnProperties()
{
	AfxMessageBox(_T("Properties...."));
}

void CFileView::OnFileOpen()
{
	HTREEITEM hTreeItem = m_wndFileView.GetSelectedItem();
	if (hTreeItem == NULL)
	{
		return;
	}
	if (m_wndFileView.ItemHasChildren(hTreeItem) || m_wndFileView.GetParentItem(hTreeItem) != NULL)
	{
		return;
	}

	CWaitCursor wait;
	m_wndFileView.SetRedraw(FALSE);
	theApp.m_MainLogic.OpenConfigFile(m_wndFileView.GetItemText(hTreeItem), &m_wndFileView);
	m_wndFileView.Expand(hTreeItem, TVE_EXPAND);
	m_wndFileView.SetRedraw(TRUE);
}

void CFileView::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectTree;
	m_wndFileView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CFileView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndFileView.SetFocus();
}

void CFileView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* Locked */);

	m_FileViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("Can't load bitmap: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_FileViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_FileViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndFileView.SetImageList(&m_FileViewImages, TVSIL_NORMAL);
}

void CFileView::FillConfigView()
{
	DestoryAllItemData();
	m_wndFileView.DeleteAllItems();

	const CStringList* listConfigs = theApp.m_MainLogic.GetConfigs();
	for (POSITION pos = listConfigs->GetHeadPosition(); pos != NULL;)
	{
		HTREEITEM hRoot = m_wndFileView.InsertItem(listConfigs->GetNext(pos), 0, 0);
		m_wndFileView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);
	}
}

void CFileView::DestoryAllItemData()
{
	DestoryItemData(m_wndFileView.GetRootItem());
}

void CFileView::DestoryItemData(HTREEITEM hItem)
{
	if (hItem == NULL)
	{
		return;
	}

	DWORD_PTR pData = m_wndFileView.GetItemData(hItem);
	if (pData)
	{
		CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)pData;
		if (pProp)
		{
			delete pProp;
		}
	}

	if (m_wndFileView.ItemHasChildren(hItem))
	{
		HTREEITEM hChildItem = m_wndFileView.GetChildItem(hItem);
		while (hChildItem != NULL)
		{
			DestoryItemData(hChildItem);
			hChildItem = m_wndFileView.GetNextItem(hChildItem, TVGN_NEXT);
		}
	}
}

void CFileView::OnDestroy()
{
	DestoryAllItemData();
	CDockablePane::OnDestroy();
}

void CFileView::OnTreeTVNSelchanging(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pnmtv = (LPNMTREEVIEW)pNMHDR;

	DWORD_PTR pData = m_wndFileView.GetItemData(pnmtv->itemNew.hItem);
	if (pData)
	{
		CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)pData;
		if (pProp)
		{
			((CMainFrame*)AfxGetMainWnd())->GetPropertiesWnd()->ShowItemProp(pProp);
		}
	}
	else
	{
		((CMainFrame*)AfxGetMainWnd())->GetPropertiesWnd()->ShowItemProp(NULL);
	}

	*pResult = 0;
}


void CFileView::OnExplorerSave()
{
	// TODO:  在此添加命令处理程序代码
}


void CFileView::OnExplorerClose()
{
	HTREEITEM hItem = m_wndFileView.GetSelectedItem();
	DestoryItemData(hItem);
	while (m_wndFileView.ItemHasChildren(hItem))
	{
		HTREEITEM hChildItem = m_wndFileView.GetChildItem(hItem);
		m_wndFileView.DeleteItem(hChildItem);
	}
}


void CFileView::OnExplorerDelete()
{
	HTREEITEM hItem = m_wndFileView.GetSelectedItem();
	if (hItem == NULL)
	{
		return;
	}

	if (AfxMessageBox(_T("Sure to delete it?"), MB_YESNO) == IDYES)
	{
		DestoryItemData(hItem);
		m_wndFileView.DeleteItem(hItem);
	}
}


void CFileView::OnGroupAddprop()
{
	HTREEITEM hGroupItem = GetSelectItemGroup();
	ASSERT(hGroupItem != NULL);

	CMFCPropertyGridProperty* pPropGroup = new CMFCPropertyGridProperty(_T("PROPERTY"));
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("NAME"), (COleVariant)_T("New"));
	pPropGroup->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("TYPE"), (COleVariant)_T("Combo"), _T(""), PROP_DATA_TYPE);
	pProp->AddOption(_T("Combo"));
	pProp->AddOption(_T("Number"));
	pProp->AddOption(_T("Text"));
	pProp->AllowEdit(FALSE);
	pPropGroup->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("VALUE"), (COleVariant)_T(""));
	pPropGroup->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("ITEMS"), PROP_DATA_ITEMS, TRUE);
	pPropGroup->AddSubItem(pProp);

	HTREEITEM hItem = m_wndFileView.InsertItem(_T("New"), 2, 2, hGroupItem);
	m_wndFileView.SetItemData(hItem, (DWORD_PTR)pPropGroup);

	if (hGroupItem)
	{
		m_wndFileView.Expand(hGroupItem, TVE_EXPAND);
		m_wndFileView.SelectItem(hItem);
	}
}


void CFileView::OnGroupDelprop()
{
	HTREEITEM hItem = m_wndFileView.GetSelectedItem();
	if (hItem == NULL || IsSelectItemGroup())
	{
		return;
	}

	if (AfxMessageBox(_T("Sure to delete it?"), MB_YESNO) == IDYES)
	{
		DestoryItemData(hItem);
		m_wndFileView.DeleteItem(hItem);
	}
}


void CFileView::OnGroupUpprop()
{
	HTREEITEM hItem = m_wndFileView.GetSelectedItem();
	if (hItem == NULL || IsSelectItemGroup())
	{
		return;
	}

	HTREEITEM hPrevItem = m_wndFileView.GetNextItem(hItem, TVGN_PREVIOUS);
	if (hPrevItem == NULL)
	{
		return;
	}

	CString strName = m_wndFileView.GetItemText(hItem);
	DWORD_PTR dwData = m_wndFileView.GetItemData(hItem);

	m_wndFileView.SetItemText(hItem, m_wndFileView.GetItemText(hPrevItem));
	m_wndFileView.SetItemData(hItem, m_wndFileView.GetItemData(hPrevItem));
	m_wndFileView.SetItemText(hPrevItem, strName);
	m_wndFileView.SetItemData(hPrevItem, dwData);
	m_wndFileView.SelectItem(hPrevItem);
}


void CFileView::OnGroupDownprop()
{
	HTREEITEM hItem = m_wndFileView.GetSelectedItem();
	if (hItem == NULL || IsSelectItemGroup())
	{
		return;
	}

	HTREEITEM hNextItem = m_wndFileView.GetNextItem(hItem, TVGN_NEXT);
	if (hNextItem == NULL)
	{
		return;
	}

	CString strName = m_wndFileView.GetItemText(hItem);
	DWORD_PTR dwData = m_wndFileView.GetItemData(hItem);

	m_wndFileView.SetItemText(hItem, m_wndFileView.GetItemText(hNextItem));
	m_wndFileView.SetItemData(hItem, m_wndFileView.GetItemData(hNextItem));
	m_wndFileView.SetItemText(hNextItem, strName);
	m_wndFileView.SetItemData(hNextItem, dwData);
	m_wndFileView.SelectItem(hNextItem);
}


void CFileView::OnUpdateGroupDelprop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!IsSelectItemGroup());
}


void CFileView::OnUpdateGroupUpprop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!IsSelectItemGroup());
}


void CFileView::OnUpdateGroupDownprop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!IsSelectItemGroup());
}


void CFileView::OnUpdateOpen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!IsSelectItemOpened());
}


void CFileView::OnUpdateExplorerSave(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsSelectItemOpened());
}


void CFileView::OnUpdateExplorerClose(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsSelectItemOpened());
}


void CFileView::OnUpdateExplorerDelete(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
}

BOOL CFileView::IsSelectItemOpened()
{
	HTREEITEM hItem = m_wndFileView.GetSelectedItem();
	return hItem && m_wndFileView.ItemHasChildren(hItem);
}


void CFileView::OnGroupAddgroup()
{
	HTREEITEM hItem = m_wndFileView.GetSelectedItem();
	HTREEITEM hParentItem = m_wndFileView.GetParentItem(hItem);
	while (m_wndFileView.GetParentItem(hParentItem))
	{
		hParentItem = m_wndFileView.GetParentItem(hParentItem);
	}

	CMFCPropertyGridProperty* pPropGroup = new CMFCPropertyGridProperty(_T("PROPERTY"));
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("NAME"), (COleVariant)_T("New Group"));
	pPropGroup->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty(_T("GROUP"), (_variant_t)true, _T(""));
	pPropGroup->AddSubItem(pProp);

	HTREEITEM hGroupItem = m_wndFileView.InsertItem(_T("New Group"), 1, 1, hParentItem);
	m_wndFileView.SetItemData(hGroupItem, (DWORD_PTR)pPropGroup);
}


void CFileView::OnUpdateGroupAddgroup(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
}

BOOL CFileView::IsSelectItemGroup()
{
	HTREEITEM hItem = m_wndFileView.GetSelectedItem();
	if (hItem)
	{
		int nImage, nSelectImage;
		m_wndFileView.GetItemImage(hItem, nImage, nSelectImage);
		if (nImage == 1)
		{
			return TRUE;
		}
	}
	return FALSE;
}


void CFileView::OnGroupDelgroup()
{
	HTREEITEM hItem = m_wndFileView.GetSelectedItem();
	if (hItem == NULL || !IsSelectItemGroup())
	{
		return;
	}

	if (AfxMessageBox(_T("Sure to delete it?"), MB_YESNO) == IDYES)
	{
		HTREEITEM hParentItem = m_wndFileView.GetParentItem(hItem);
		DestoryItemData(hItem);
		m_wndFileView.DeleteItem(hItem);

		if (!m_wndFileView.ItemHasChildren(hParentItem))
		{
			CMFCPropertyGridProperty* pPropGroup = new CMFCPropertyGridProperty(_T("PROPERTY"));
			CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("NAME"), (COleVariant)_T("New Group"));
			pPropGroup->AddSubItem(pProp);

			pProp = new CMFCPropertyGridProperty(_T("GROUP"), (_variant_t)true, _T(""));
			pPropGroup->AddSubItem(pProp);

			HTREEITEM hGroupItem = m_wndFileView.InsertItem(_T("New Group"), 1, 1, hParentItem);
			m_wndFileView.SetItemData(hGroupItem, (DWORD_PTR)pPropGroup);
		}
	}
}


void CFileView::OnUpdateGroupDelgroup(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsSelectItemGroup());
}

CMFCPropertyGridProperty* CFileView::GetSelectItemProp()
{
	HTREEITEM hItem = m_wndFileView.GetSelectedItem();
	if (hItem)
	{
		DWORD_PTR pData = m_wndFileView.GetItemData(hItem);
		if (pData)
		{
			CMFCPropertyGridProperty *pProp = (CMFCPropertyGridProperty*)pData;
			if (pProp)
			{
				return pProp;
			}
		}
	}
	return NULL;
}

HTREEITEM CFileView::GetSelectItemGroup()
{
	HTREEITEM hItem = m_wndFileView.GetSelectedItem();
	if (hItem)
	{
		int nImage, nSelectImage;
		m_wndFileView.GetItemImage(hItem, nImage, nSelectImage);
		if (nImage == 2)
		{
			return m_wndFileView.GetParentItem(hItem);
		}
	}
	return hItem;
}
