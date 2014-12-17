
#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "MakeSetConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void CMyMFCPropertyGridCtrl::RemoveAllPropertyNoDelete(bool bAll)
{
	if (m_pSel != NULL)
	{
		m_pSel->OnEndEdit();
	}
	m_lstProps.RemoveAll();

	if (bAll)
	{
		RemoveAll();
		AdjustLayout();
	}
}

void CMyMFCPropertyGridCtrl::OnChangeSelection(CMFCPropertyGridProperty* pNewSel, CMFCPropertyGridProperty* pOldSel)
{
	CPropertiesWnd* pParentWnd = (CPropertiesWnd*)GetParent();
	if (pParentWnd)
	{
		pParentWnd->ChangeSelection(pNewSel, pOldSel);
	}
}

void CMyMFCPropertyGridCtrl::OnPropertyChanged(CMFCPropertyGridProperty* pProp) const
{
	CMFCPropertyGridCtrl::OnPropertyChanged(pProp);
	CPropertiesWnd* pParentWnd = (CPropertiesWnd*)GetParent();
	if (pParentWnd)
	{
		pParentWnd->PropertyChanged(pProp);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROP_RESET, &CPropertiesWnd::OnPropReset)
	ON_COMMAND(ID_PROP_ADDITEM, &CPropertiesWnd::OnPropAdditem)
	ON_COMMAND(ID_PROP_DELITEM, &CPropertiesWnd::OnPropDelitem)
	ON_UPDATE_COMMAND_UI(ID_PROP_ADDITEM, &CPropertiesWnd::OnUpdatePropAdditem)
	ON_UPDATE_COMMAND_UI(ID_PROP_DELITEM, &CPropertiesWnd::OnUpdatePropDelitem)
	ON_COMMAND(ID_PROP_UPITEM, &CPropertiesWnd::OnPropUpitem)
	ON_COMMAND(ID_PROP_DOWNITEM, &CPropertiesWnd::OnPropDownitem)
	ON_UPDATE_COMMAND_UI(ID_PROP_DOWNITEM, &CPropertiesWnd::OnUpdatePropDownitem)
	ON_UPDATE_COMMAND_UI(ID_PROP_UPITEM, &CPropertiesWnd::OnUpdatePropUpitem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar message handlers

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyTlb, rectClient.Width(), rectClient.Height() -(cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// Create combo:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;


	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Failed to create Properties Grid \n");
		return -1;      // fail to create
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* Is locked */);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* Locked */);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: Add your command handler code here
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: Add your command update UI handler code here
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: Add your command handler code here
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: Add your command update UI handler code here
}

void CPropertiesWnd::InitPropList()
{
	//SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea(FALSE);
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	return;

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Appearance"));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("3D Look"), (_variant_t) false, _T("Specifies the window's font will be non-bold and controls will have a 3D border")));

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("Border"), _T("Dialog Frame"), _T("One of: None, Thin, Resizable, or Dialog Frame"));
	pProp->AddOption(_T("None"));
	pProp->AddOption(_T("Thin"));
	pProp->AddOption(_T("Resizable"));
	pProp->AddOption(_T("Dialog Frame"));
	pProp->AllowEdit(FALSE);

	pGroup1->AddSubItem(pProp);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Caption"), (_variant_t) _T("About"), _T("Specifies the text that will be displayed in the window's title bar")));

	m_wndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("Window Size"), 0, TRUE);

	pProp = new CMFCPropertyGridProperty(_T("Height"), (_variant_t) 250l, _T("Specifies the window's height"));
	pProp->EnableSpinControl(TRUE, 50, 300);
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("Width"), (_variant_t) 150l, _T("Specifies the window's width"));
	pProp->EnableSpinControl(TRUE, 50, 200);
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("Font"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);

	lstrcpy(lf.lfFaceName, _T("Arial"));

	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("Font"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("Specifies the default font for the window")));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Use System Font"), (_variant_t) true, _T("Specifies that the window uses MS Shell Dlg font")));

	m_wndPropList.AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("Misc"));
	pProp = new CMFCPropertyGridProperty(_T("(Name)"), _T("Application"));
	pProp->Enable(FALSE);
	pGroup3->AddSubItem(pProp);

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("Window Color"), RGB(210, 192, 254), NULL, _T("Specifies the default window color"));
	pColorProp->EnableOtherButton(_T("Other..."));
	pColorProp->EnableAutomaticButton(_T("Default"), ::GetSysColor(COLOR_3DFACE));
	pGroup3->AddSubItem(pColorProp);

	static const TCHAR szFilter[] = _T("Icon Files(*.ico)|*.ico|All Files(*.*)|*.*||");
	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("Icon"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("Specifies the window icon")));

	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("Folder"), _T("c:\\")));

	m_wndPropList.AddProperty(pGroup3);

	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("Hierarchy"));

	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("First sub-level"));
	pGroup4->AddSubItem(pGroup41);

	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("Second sub-level"));
	pGroup41->AddSubItem(pGroup411);

	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 1"), (_variant_t) _T("Value 1"), _T("This is a description")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 2"), (_variant_t) _T("Value 2"), _T("This is a description")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("Item 3"), (_variant_t) _T("Value 3"), _T("This is a description")));

	pGroup4->Expand(FALSE);
	m_wndPropList.AddProperty(pGroup4);
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	//SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
}

void CPropertiesWnd::ShowItemProp(CMFCPropertyGridProperty *pProp)
{
	m_wndPropList.RemoveAllPropertyNoDelete(TRUE);
	if (pProp)
	{
		m_wndPropList.AddProperty(pProp);
	}
	((CMainFrame*)AfxGetMainWnd())->GetClassView()->SetPreviewProp(NULL);
}

void CPropertiesWnd::OnDestroy()
{
	m_wndPropList.RemoveAllPropertyNoDelete(FALSE);
	CDockablePane::OnDestroy();
}

void CPropertiesWnd::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMyMFCPropertyGridCtrl* pWndPropList = (CMyMFCPropertyGridCtrl*)&m_wndPropList;
	ASSERT_VALID(pWndPropList);

	if (pWnd != pWndPropList)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	pWndPropList->SetFocus();
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_PROPLIST, point.x, point.y, this, TRUE);
}

void CPropertiesWnd::OnPropReset()
{
	m_wndPropList.ResetOriginalValues(TRUE);
}

void CPropertiesWnd::OnPropAdditem()
{
	if (!IsComboType())
	{
		return;
	}

	CMFCPropertyGridProperty *pProp = m_wndPropList.FindItemByData(PROP_DATA_ITEMS);
	if (pProp)
	{
		CMFCPropertyGridProperty* pPropItem = new CMFCPropertyGridProperty(_T("ITEM"), 0, TRUE);
		pProp->AddSubItem(pPropItem);
		pProp->Expand(TRUE);

		CMFCPropertyGridProperty* pPropChild = new CMFCPropertyGridProperty(_T("VALUE"), (COleVariant)_T(""));
		pPropItem->AddSubItem(pPropChild);

		pPropChild = new CMFCPropertyGridProperty(_T("SHORT"), (COleVariant)_T(""));
		pPropItem->AddSubItem(pPropChild);

		pPropChild = new CMFCPropertyGridProperty(_T("PREVIEW"), (COleVariant)_T(""));
		pPropItem->AddSubItem(pPropChild);
		pPropItem->Expand(TRUE);
	}
}

void CPropertiesWnd::OnPropDelitem()
{
	if (!IsComboType())
	{
		return;
	}

	CMFCPropertyGridProperty *pProp = m_wndPropList.GetCurSel();
	if (pProp && pProp->IsGroup())
	{
		CString strName(pProp->GetName());
		if (strName.CompareNoCase(_T("ITEM")) == 0 && AfxMessageBox(_T("Sure to delete it?"), MB_YESNO) == IDYES)
		{
			pProp->GetParent()->RemoveSubItem(pProp);
			m_wndPropList.RedrawWindow();
		}
	}
}

void CPropertiesWnd::OnUpdatePropAdditem(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsComboType());
}

void CPropertiesWnd::OnUpdatePropDelitem(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsSelectComboItem());
}

BOOL CPropertiesWnd::IsComboType()
{
	CMFCPropertyGridProperty *pProp = m_wndPropList.FindItemByData(PROP_DATA_TYPE);
	if (pProp)
	{
		CString strValue(pProp->GetValue());
		return strValue.CompareNoCase(_T("Combo")) == 0;
	}
	return FALSE;
}

void CPropertiesWnd::OnPropUpitem()
{
	if (!IsComboType())
	{
		return;
	}

	CMFCPropertyGridProperty *pProp = m_wndPropList.GetCurSel();
	if (pProp && pProp->IsGroup())
	{
		CString strName(pProp->GetName());
		if (strName.CompareNoCase(_T("ITEM")) == 0)
		{
			CMFCPropertyGridProperty *pParentProp = pProp->GetParent();
			if (pProp == pParentProp->GetSubItem(0))
			{
				return;
			}

			int nEnd = 0;
			CList<CMFCPropertyGridProperty*, CMFCPropertyGridProperty*> lstSubItems;
			for (int i = pParentProp->GetSubItemsCount() - 1; i >= nEnd; i--)
			{
				CMFCPropertyGridProperty *pChildProp = pParentProp->GetSubItem(i);
				if (pChildProp)
				{
					if (pChildProp == pProp)
					{
						nEnd = i - 1;
					}
					else
					{
						lstSubItems.AddHead(pChildProp);
					}
					pParentProp->RemoveSubItem(pChildProp, FALSE);
				}
			}

			pParentProp->AddSubItem(pProp);
			for (POSITION pos = lstSubItems.GetHeadPosition(); pos != NULL;)
			{
				CMFCPropertyGridProperty* pProp = lstSubItems.GetNext(pos);
				ASSERT_VALID(pProp);

				pParentProp->AddSubItem(pProp);
			}
			m_wndPropList.AdjustLayout();
		}
	}
}

void CPropertiesWnd::OnPropDownitem()
{
	if (!IsComboType())
	{
		return;
	}

	CMFCPropertyGridProperty *pProp = m_wndPropList.GetCurSel();
	if (pProp && pProp->IsGroup())
	{
		CString strName(pProp->GetName());
		if (strName.CompareNoCase(_T("ITEM")) == 0)
		{
			CMFCPropertyGridProperty *pParentProp = pProp->GetParent();
			if (pProp == pParentProp->GetSubItem(pParentProp->GetSubItemsCount() - 1))
			{
				return;
			}

			int nEnd = 0;
			CList<CMFCPropertyGridProperty*, CMFCPropertyGridProperty*> lstSubItems;
			for (int i = pParentProp->GetSubItemsCount() - 1; i >= nEnd; i--)
			{
				CMFCPropertyGridProperty *pChildProp = pParentProp->GetSubItem(i);
				if (pChildProp)
				{
					if (pChildProp == pProp)
					{
						nEnd = i;
						lstSubItems.InsertAfter(lstSubItems.GetHeadPosition(), pChildProp);
					}
					else
					{
						lstSubItems.AddHead(pChildProp);
					}
					pParentProp->RemoveSubItem(pChildProp, FALSE);
				}
			}

			for (POSITION pos = lstSubItems.GetHeadPosition(); pos != NULL;)
			{
				CMFCPropertyGridProperty* pProp = lstSubItems.GetNext(pos);
				ASSERT_VALID(pProp);

				pParentProp->AddSubItem(pProp);
			}
			m_wndPropList.AdjustLayout();
		}
	}
}

void CPropertiesWnd::OnUpdatePropDownitem(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsSelectComboItem());
}

void CPropertiesWnd::OnUpdatePropUpitem(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsSelectComboItem());
}

BOOL CPropertiesWnd::IsSelectComboItem()
{
	if (IsComboType())
	{
		CMFCPropertyGridProperty *pProp = m_wndPropList.GetCurSel();
		if (pProp && pProp->IsGroup())
		{
			CString strName(pProp->GetName());
			return (strName.CompareNoCase(_T("ITEM")) == 0);
		}
	}
	return FALSE;
}

void CPropertiesWnd::PropertyChanged(CMFCPropertyGridProperty* pProp)
{
	CString strName(pProp->GetName());
	if (strName.CompareNoCase(_T("TYPE")) == 0)
	{
		CMFCPropertyGridProperty* pPropGroup = pProp->GetParent();
		for (int i = pPropGroup->GetSubItemsCount() - 1; i >= 0; i--)
		{
			CMFCPropertyGridProperty* pChildProp = pPropGroup->GetSubItem(i);
			if (pChildProp == pProp)
			{
				break;
			}
			pPropGroup->RemoveSubItem(pChildProp);
		}

		CString strType(pProp->GetValue());
		if (strType.CompareNoCase(_T("Combo")) == 0)
		{
			CMFCPropertyGridProperty* pNewProp = new CMFCPropertyGridProperty(_T("VALUE"), (COleVariant)_T(""));
			pPropGroup->AddSubItem(pNewProp);

			pNewProp = new CMFCPropertyGridProperty(_T("ITEMS"), PROP_DATA_ITEMS, TRUE);
			pPropGroup->AddSubItem(pNewProp);
		}
		else if (strType.CompareNoCase(_T("Number")) == 0)
		{ 
			CMFCPropertyGridProperty* pNewProp = new CMFCPropertyGridProperty(_T("VALUE"), (_variant_t)0, _T(""));
			pPropGroup->AddSubItem(pNewProp);

			pNewProp = new CMFCPropertyGridProperty(_T("RANGE MIN"), (_variant_t)0, _T(""));
			pNewProp->EnableSpinControl(TRUE, -9999, 9999);
			pPropGroup->AddSubItem(pNewProp);
			pNewProp = new CMFCPropertyGridProperty(_T("RANGE MAX"), (_variant_t)100, _T(""));
			pNewProp->EnableSpinControl(TRUE, -9999, 9999);
			pPropGroup->AddSubItem(pNewProp);

			BOOL bBuddy = FALSE;
			pNewProp = new CMFCPropertyGridProperty(_T("BUDDY"), (_variant_t)(bBuddy == TRUE), _T(""));
			pPropGroup->AddSubItem(pNewProp);

			pNewProp = new CMFCPropertyGridProperty(_T("SHORT"), (_variant_t)_T(""), _T(""));
			pPropGroup->AddSubItem(pNewProp);

			pNewProp = new CMFCPropertyGridProperty(_T("PREVIEW"), (_variant_t)_T(""), _T(""));
			pPropGroup->AddSubItem(pNewProp);
		}
		else if (strType.CompareNoCase(_T("Text")) == 0)
		{
			CMFCPropertyGridProperty* pNewProp = new CMFCPropertyGridProperty(_T("VALUE"), (COleVariant)_T(""));
			pPropGroup->AddSubItem(pNewProp);

			pNewProp = new CMFCPropertyGridProperty(_T("SHORT"), (COleVariant)_T(""));
			pPropGroup->AddSubItem(pNewProp);

			pNewProp = new CMFCPropertyGridProperty(_T("PREVIEW"), (COleVariant)_T(""));
			pPropGroup->AddSubItem(pNewProp);
		}

		m_wndPropList.AdjustLayout();
	}
	else if (strName.CompareNoCase(_T("PREVIEW")) == 0)
	{
		((CMainFrame*)AfxGetMainWnd())->GetClassView()->RefreshPreview();
	}
}

void CPropertiesWnd::ChangeSelection(CMFCPropertyGridProperty* pNewSel, CMFCPropertyGridProperty* /*pOldSel*/)
{
	if (pNewSel == NULL)
	{
		((CMainFrame*)AfxGetMainWnd())->GetClassView()->SetPreviewProp(NULL);
		return;
	}

	CString strPreview;
	if (IsComboType())
	{
		if (pNewSel->IsGroup())
		{
			CString strName(pNewSel->GetName());
			if (strName.CompareNoCase(_T("ITEM")) == 0)
			{
				CMFCPropertyGridProperty* pPreviewProp = pNewSel->GetSubItem(pNewSel->GetSubItemsCount() - 1);
				((CMainFrame*)AfxGetMainWnd())->GetClassView()->SetPreviewProp(pPreviewProp);
				return;
			}
		}
		else
		{
			CMFCPropertyGridProperty* pGroupProp = pNewSel->GetParent();
			CString strName(pGroupProp->GetName());
			if (strName.CompareNoCase(_T("ITEM")) == 0)
			{
				CMFCPropertyGridProperty* pPreviewProp = pGroupProp->GetSubItem(pGroupProp->GetSubItemsCount() - 1);
				((CMainFrame*)AfxGetMainWnd())->GetClassView()->SetPreviewProp(pPreviewProp);
				return;
			}
		}
		((CMainFrame*)AfxGetMainWnd())->GetClassView()->SetPreviewProp(NULL);
	}
	else
	{
		// the last is preview
		CMFCPropertyGridProperty* pGroupProp = pNewSel;
		if (!pNewSel->IsGroup())
		{
			pGroupProp = pNewSel->GetParent();
		}

		CMFCPropertyGridProperty* pPreviewProp = pGroupProp->GetSubItem(pGroupProp->GetSubItemsCount() - 1);
		((CMainFrame*)AfxGetMainWnd())->GetClassView()->SetPreviewProp(pPreviewProp);		
	}
}

void CPropertiesWnd::SetPropModifiedFlag(CMFCPropertyGridProperty* pProp)
{
	if (pProp)
	{
		m_wndPropList.OnPropertyChanged(pProp);
	}
}
