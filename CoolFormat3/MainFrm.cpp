// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CoolFormat3.h"

#include "MainFrm.h"
#include "SynBCGPEditView.h"
#include "MyBCGPRibbonLabel.h"
#include "MyBCGPRibbonStatusBarPane.h"
#include "OptionsPropSheet.h"
#include "PagePopular.h"
#include "PageResource.h"

#include "RegConfig.h"
#include "LangExtDlg.h"
#include "SetHtmlDlg.h"
#include "SetEditDlg.h"
#include "TellBug.h"
#include "BatchFormat.h"
#include "SetSheet.h"
#include "UpdateChecker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//宏定义
#define CONFIG_DEFAULT_NAME _T("CoolFormatConfig")
#define CONFIG_EXT_NAME _T(".cfconfig")

//////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CBCGPMDIFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CBCGPMDIFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_WINDOW_MANAGER, OnWindowManager)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_WIN7, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_WIN7, OnUpdateAppLook)
	ON_COMMAND(ID_MDI_MOVE_TO_NEXT_GROUP, OnMdiMoveToNextGroup)
	ON_COMMAND(ID_MDI_MOVE_TO_PREV_GROUP, OnMdiMoveToPrevGroup)
	ON_COMMAND(ID_MDI_NEW_HORZ_TAB_GROUP, OnMdiNewHorzTabGroup)
	ON_COMMAND(ID_MDI_NEW_VERT_GROUP, OnMdiNewVertGroup)
	ON_COMMAND(ID_MDI_CANCEL, OnMdiCancel)
	ON_REGISTERED_MESSAGE(BCGM_ON_RIBBON_CUSTOMIZE, OnRibbonCustomize)
	ON_REGISTERED_MESSAGE(BCGM_ON_GET_TAB_TOOLTIP, OnGetTabToolTip)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_FILE_OTHER_CLOSE, &CMainFrame::OnFileOtherClose)
	ON_COMMAND(ID_FILE_PATH, &CMainFrame::OnFilePath)
	ON_COMMAND(ID_FILEDIR_OPEN, &CMainFrame::OnFiledirOpen)
	ON_COMMAND(ID_STATUSBAR_PANE4, OnAdminUrl)
	ON_COMMAND(ID_NOW_ENCODING, OnAdminUrl)
	ON_COMMAND(ID_NEWVERTIP, &CMainFrame::OnNewvertip)
	ON_REGISTERED_MESSAGE(BCGM_ON_BEFORE_SHOW_RIBBON_ITEM_MENU, OnShowRibbonItemMenu)
	ON_COMMAND(ID_EXPORTREG, &CMainFrame::OnExportreg)
	ON_COMMAND(ID_LANGEXT, &CMainFrame::OnLangext)
	ON_COMMAND(ID_SETHTML, &CMainFrame::OnSethtml)
	ON_COMMAND(ID_SETEDIT, &CMainFrame::OnSetedit)
	ON_COMMAND(ID_IMPORTREG, &CMainFrame::OnImportreg)
	ON_COMMAND(ID_TELLBUG, &CMainFrame::OnTellbug)
	ON_COMMAND(ID_ONLINEHELP, &CMainFrame::OnOnlinehelp)
	ON_COMMAND(ID_SETFORMATTER, &CMainFrame::OnSetformatter)
	ON_COMMAND(ID_BATCHFORMAT, &CMainFrame::OnBatchformat)
	ON_MESSAGE(WM_DOCHECKUPDATEEVENT, &CMainFrame::DoCheckUpdateEvenet)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()

// CMainFrame construction/destruction
//////////////////////////////////////////////////////////////////////////
CMainFrame::CMainFrame()
{

	// TODO: add member initialization code here
}
//////////////////////////////////////////////////////////////////////////
CMainFrame::~CMainFrame()
{
}
//////////////////////////////////////////////////////////////////////////
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	if (!CreateRibbonBar ())
	{
		TRACE0("Failed to create ribbon bar\n");
		return -1;      // fail to create
	}


	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	CString strTemp, strTemp2;
	BOOL bNameValid;
	bNameValid = strTemp.LoadString(IDS_STATUS_LINK);
	ASSERT(bNameValid);
	bNameValid = strTemp2.LoadString(IDS_STATUS_AUTOR);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement (new CBCGPRibbonStatusBarPane (
		ID_STATUSBAR_PANE4, strTemp, FALSE), strTemp2);

	bNameValid = strTemp.LoadString(IDS_STATUS_ROWCOL);
	ASSERT(bNameValid);	
	CString strTemp3;
	strTemp3.Format(strTemp, 7483647, 7483647);
	strTemp.Format(strTemp, 0, 0);
	bNameValid = strTemp2.LoadString(IDS_STATUS_CUR_RC);
	ASSERT(bNameValid);
	m_wndStatusBar.AddExtendedElement(new CBCGPRibbonStatusBarPane(
		ID_STATUSBAR_PANE3, strTemp, TRUE, NULL, strTemp3), strTemp2);	
	
	strTemp = _T("GB2312");
	bNameValid = strTemp2.LoadString(IDS_STATUS_ENCODING);
	ASSERT(bNameValid);
	CBCGPRibbonStatusBarPane* pPaneCodepage = new CMyBCGPRibbonStatusBarPane(
		ID_STATUSBAR_PANE2, strTemp, FALSE);
	pPaneCodepage->SetMenu(IDR_ENCODING_MENU);
	pPaneCodepage->SetID(ID_NOW_ENCODING);
	m_wndStatusBar.AddExtendedElement(pPaneCodepage, strTemp2);


	EnableDocking(CBRS_ALIGN_ANY);

	// Enable windows manager:
	EnableWindowsDialog (ID_WINDOW_MANAGER, IDS_WINDOWS_MANAGER, TRUE);
	OnAppLook (theApp.m_nAppLook);
	m_wndRibbonBar.SetScenicLook();
	m_wndRibbonBar.EnableMinimizeButton();

	CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
	CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D;

	CBCGPMDITabParams mdiTabParams;
	mdiTabParams.m_bTabIcons = FALSE;
	mdiTabParams.m_style = CBCGPTabWnd::STYLE_3D_VS2005;
	mdiTabParams.m_bAutoColor = TRUE;
	mdiTabParams.m_bDocumentMenu = TRUE;
	mdiTabParams.m_bTabCustomTooltips = TRUE;
	EnableMDITabbedGroups (TRUE, mdiTabParams);

	CBCGPToolBar::AddToolBarForImageCollection (IDR_MENU_IMAGES, IDB_MENU_IMAGES_HC);

	CBCGPDockManager* pDockManager = GetDockManager ();
	if (pDockManager != NULL)
	{
		ASSERT_VALID (pDockManager);
		pDockManager->AdjustBarFrames ();
	}

	CBCGPTabbedControlBar::ResetTabs ();

	// VISUAL_MANAGER
	return 0;
}
//////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (cs.lpszClass)
	{
		WNDCLASS wndcls;
		GetClassInfo(AfxGetInstanceHandle(), cs.lpszClass, &wndcls);
		wndcls.lpszClassName = COOLFORMAT_CLASS;
		AfxRegisterClass(&wndcls);
		cs.lpszClass = wndcls.lpszClassName;
	}

	if( !CBCGPMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGPMDIFrameWnd::AssertValid();
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGPMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers




//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnWindowManager() 
{
	ShowWindowsDialog ();
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnAppLook(UINT id)
{
	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_2010_1:
	case ID_VIEW_APPLOOK_2010_2:
	case ID_VIEW_APPLOOK_2010_3:
		// enable Office 2010 look:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_2010_1:
			CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Blue);
			break;

		case ID_VIEW_APPLOOK_2010_2:
			CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Black);
			break;

		case ID_VIEW_APPLOOK_2010_3:
			CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Silver);
			break;
		}
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2010));
		break;
	}

	RecalcLayout ();
	RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt (_T("ApplicationLook"), theApp.m_nAppLook);
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnUpdateAppLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (theApp.m_nAppLook == pCmdUI->m_nID);
}
//////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::OnShowMDITabContextMenu (CPoint point, DWORD dwAllowedItems, BOOL bDrop)
{
	CMenu menu;
	VERIFY(menu.LoadMenu (bDrop ? IDR_POPUP_DROP_MDITABS : IDR_POPUP_MDITABS));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	if ((dwAllowedItems & BCGP_MDI_CREATE_HORZ_GROUP) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_NEW_HORZ_TAB_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CREATE_VERT_GROUP) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_NEW_VERT_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CAN_MOVE_NEXT) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_MOVE_TO_NEXT_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CAN_MOVE_PREV) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_MOVE_TO_PREV_GROUP, MF_BYCOMMAND);
	}

	CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
	pPopupMenu->SetAutoDestroy (FALSE);
	pPopupMenu->Create (this, point.x, point.y, pPopup->GetSafeHmenu ());

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnMdiMoveToNextGroup() 
{
	MDITabMoveToNextGroup ();
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnMdiMoveToPrevGroup() 
{
	MDITabMoveToNextGroup (FALSE);
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnMdiNewHorzTabGroup() 
{
	MDITabNewGroup (FALSE);
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnMdiNewVertGroup() 
{
	MDITabNewGroup ();
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnMdiCancel() 
{
	// TODO: Add your command handler code here
	
}
//////////////////////////////////////////////////////////////////////////
CBCGPMDIChildWnd* CMainFrame::CreateDocumentWindow (LPCTSTR lpcszDocName, CObject* /*pObj*/)
{
	if (lpcszDocName != NULL && lpcszDocName [0] != '\0')
	{
		CDocument* pDoc = AfxGetApp()->OpenDocumentFile (lpcszDocName);

		if (pDoc != NULL)
		{
			POSITION pos = pDoc->GetFirstViewPosition();

			if (pos != NULL)
			{
				CView* pView = pDoc->GetNextView (pos);
				if (pView == NULL)
				{
					return NULL;
				}

				return DYNAMIC_DOWNCAST (CBCGPMDIChildWnd, pView->GetParent ());
			}   
		}
	}

	return NULL;
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnClose() 
{
	SaveMDIState (theApp.GetRegSectionPath ());
	CBCGPMDIFrameWnd::OnClose();
}
//////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::CreateRibbonBar ()
{
	if (!m_wndRibbonBar.Create(this))
	{
		return FALSE;
	}

	// Load panel images:
	m_PanelImages.SetImageSize (CSize (16, 16));
	m_PanelImages.Load (IDB_RIBBON_ICONS);

	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STRING_TITLEFILE);
	ASSERT(bNameVaild);

	// Init main button:
	//m_MainButton.SetImage (IDB_RIBBON_MAIN);
	//m_MainButton.SetToolTipText (_T("    文件"));
	m_MainButton.SetText (_T("\nf"));
	m_MainButton.SetScenicText(strTemp);

	m_wndRibbonBar.SetMainButton (&m_MainButton, CSize (45, 45));

	CBCGPRibbonMainPanel* pMainPanel = m_wndRibbonBar.AddMainCategory (
		strTemp, IDB_RIBBON_FILESMALL, IDB_RIBBON_FILELARGE);

	bNameVaild = strTemp.LoadString(IDS_STRING_TITLENEW);
	ASSERT(bNameVaild);
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_NEW, strTemp, 0, 0));
	bNameVaild = strTemp.LoadString(IDS_STRING57);
	ASSERT(bNameVaild);
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_OPEN, strTemp, 1, 1));
	bNameVaild = strTemp.LoadString(IDS_STRING58);
	ASSERT(bNameVaild);
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SAVE, strTemp, 2, 2));
	bNameVaild = strTemp.LoadString(IDS_STRING59);
	ASSERT(bNameVaild);
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_SAVE_AS, strTemp, 3, 3));
	bNameVaild = strTemp.LoadString(IDS_STRING60);
	ASSERT(bNameVaild);
	CBCGPRibbonButton* pBtnPrint = new CBCGPRibbonButton (ID_FILE_PRINT, strTemp, 4, 4);
	bNameVaild = strTemp.LoadString(IDS_STRING61);
	ASSERT(bNameVaild);
	pBtnPrint->AddSubItem (new CBCGPRibbonLabel (strTemp));
	bNameVaild = strTemp.LoadString(IDS_STRING62);
	ASSERT(bNameVaild);
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT, strTemp, 4, 4, TRUE));
	bNameVaild = strTemp.LoadString(IDS_STRING63);
	ASSERT(bNameVaild);
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT_DIRECT, strTemp, 7, 7, TRUE));
	bNameVaild = strTemp.LoadString(IDS_STRING64);
	ASSERT(bNameVaild);
	pBtnPrint->AddSubItem (new CBCGPRibbonButton (ID_FILE_PRINT_PREVIEW, strTemp, 6, 6, TRUE));

	pBtnPrint->SetKeys (_T("p"), _T("w"));

	pMainPanel->Add (pBtnPrint);

	pMainPanel->Add (new CBCGPRibbonSeparator (TRUE));
	bNameVaild = strTemp.LoadString(IDS_STRING65);
	ASSERT(bNameVaild);
	pMainPanel->Add (new CBCGPRibbonButton (ID_FILE_CLOSE, strTemp, 5, 5));
	bNameVaild = strTemp.LoadString(IDS_STRING66);
	ASSERT(bNameVaild);
	pMainPanel->AddRecentFilesList (strTemp);
	bNameVaild = strTemp.LoadString(IDS_STRING67);
	ASSERT(bNameVaild);
	pMainPanel->AddToBottom (new CBCGPRibbonMainPanelButton (ID_TOOLS_OPTIONS, strTemp, 9));
	bNameVaild = strTemp.LoadString(IDS_STRING68);
	ASSERT(bNameVaild);
	pMainPanel->AddToBottom (new CBCGPRibbonMainPanelButton (ID_APP_EXIT, strTemp, 8));

	// 开始页面
	bNameVaild = strTemp.LoadString(IDS_STRING69);
	ASSERT(bNameVaild);
	CBCGPRibbonCategory* pCategory = m_wndRibbonBar.AddCategory (
		strTemp,
		IDB_RIBBON_HOMESMALL,
		IDB_RIBBON_HOMELARGE);

	// 剪贴板面板
	bNameVaild = strTemp.LoadString(IDS_STRING70);
	ASSERT(bNameVaild);
	CBCGPRibbonPanel* pPanelClipboard = pCategory->AddPanel (
		strTemp, 
		m_PanelImages.ExtractIcon (1));

	bNameVaild = strTemp.LoadString(IDS_STRING71);
	ASSERT(bNameVaild);
	CBCGPRibbonButton* pBtnPaste = new CBCGPRibbonButton (ID_EDIT_PASTE, strTemp, 0, 0);
	//pBtnPaste->SetMenu (IDR_PASTE_MENU, TRUE);
	pPanelClipboard->Add (pBtnPaste);
	bNameVaild = strTemp.LoadString(IDS_STRING72);
	ASSERT(bNameVaild);
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_CUT, strTemp, 1));
	bNameVaild = strTemp.LoadString(IDS_STRING73);
	ASSERT(bNameVaild);
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_COPY, strTemp, 2));
	bNameVaild = strTemp.LoadString(IDS_STRING74);
	ASSERT(bNameVaild);
	pPanelClipboard->Add (new CBCGPRibbonButton (ID_EDIT_SELECT_ALL, strTemp, 6));

	pPanelClipboard->SetKeys (_T("zc"));

	// 功能面板
	bNameVaild = strTemp.LoadString(IDS_STRING75);
	ASSERT(bNameVaild);
	CBCGPRibbonPanel* pPanelFunction = pCategory->AddPanel(strTemp, m_PanelImages.ExtractIcon(3));
	bNameVaild = strTemp.LoadString(IDS_STRING76);
	ASSERT(bNameVaild);
	pPanelFunction->Add(new CBCGPRibbonButton(ID_FASTFORMAT, strTemp, -1, 2));
	bNameVaild = strTemp.LoadString(IDS_STRING77);
	ASSERT(bNameVaild);
	pPanelFunction->Add(new CBCGPRibbonButton(ID_SELFORMAT, strTemp, -1, 3));
	bNameVaild = strTemp.LoadString(IDS_STRING78);
	ASSERT(bNameVaild);
	pPanelFunction->Add(new CBCGPRibbonButton(ID_HTMLTOBLOG, strTemp, -1, 4));
	bNameVaild = strTemp.LoadString(IDS_STRING79);
	ASSERT(bNameVaild);
	pPanelFunction->Add(new CBCGPRibbonButton(ID_BATCHFORMAT, strTemp, -1, 5));
	pPanelFunction->SetKeys(_T("zf"));

	//风格面板
	bNameVaild = strTemp.LoadString(IDS_STRING80);
	ASSERT(bNameVaild);
	CBCGPRibbonPanel* pPanelStyle = pCategory->AddPanel(strTemp, m_PanelImages.ExtractIcon(4));
	pPanelStyle->SetCenterColumnVert(TRUE);
	bNameVaild = strTemp.LoadString(IDS_STRING81);
	ASSERT(bNameVaild);
	CBCGPRibbonButton* pBtnLang = new CBCGPRibbonButton(ID_LANG, strTemp, -1, 6);
	pBtnLang->SetMenu(IDR_LANG_MENU);
	pPanelStyle->Add(pBtnLang);
	CBCGPRibbonButtonsGroup *pButtonsStyle = new CBCGPRibbonButtonsGroup;
	pButtonsStyle->AddButton(new CBCGPRibbonButton(ID_INDENT_ADD, _T("\ni"), 7));
	pButtonsStyle->AddButton(new CBCGPRibbonButton(ID_INDENT_MIN, _T("\nu"), 8));
	pButtonsStyle->AddButton(new CBCGPRibbonButton(ID_COMMENT_DO, _T("\nn"), 9));
	pButtonsStyle->AddButton(new CBCGPRibbonButton(ID_COMMENT_NOT, _T("\nm"), 10));
	pPanelStyle->Add(pButtonsStyle);
	CMyBCGPRibbonLabel *pLabelLang = new CMyBCGPRibbonLabel(_T("   ActionScript   "));
	pLabelLang->SetID(ID_NOW_LANG);
	pPanelStyle->Add(pLabelLang);	

	// 窗口面板
	bNameVaild = strTemp.LoadString(IDS_STRING82);
	ASSERT(bNameVaild);
	CBCGPRibbonPanel* pPanelWindow = pCategory->AddPanel (
		strTemp, 
		m_PanelImages.ExtractIcon (2));

	strTemp.Append(_T("\nw"));
	CBCGPRibbonButton* pBtnWindows = new CBCGPRibbonButton (0, strTemp, -1, 1);
	pBtnWindows->SetMenu (IDR_WINDOWS_MENU, TRUE);
	pPanelWindow->Add (pBtnWindows);

	// Add the launch button at the bottom of the panel:
	pPanelWindow->EnableLaunchButton (ID_WINDOW_MANAGER, -1, _T("l"));
	pPanelWindow->SetKeys (_T("zw"));
	
	// Add some hidden (non-ribbon) elements:
	bNameVaild = strTemp.LoadString(IDS_STRING83);
	ASSERT(bNameVaild);
	CBCGPRibbonUndoButton* pUndo = new CBCGPRibbonUndoButton (ID_EDIT_UNDO, strTemp, 4);
	pCategory->AddHidden (pUndo);
	bNameVaild = strTemp.LoadString(IDS_STRING84);
	ASSERT(bNameVaild);
	pCategory->AddHidden(new CBCGPRibbonButton(ID_EDIT_REDO, strTemp, 5));
	bNameVaild = strTemp.LoadString(IDS_CHANGE_VIEW);
	ASSERT(bNameVaild);
	pCategory->AddHidden(new CBCGPRibbonButton(ID_CHANGE_VIEW, strTemp));

	// 添加高级属性页
	bNameVaild = strTemp.LoadString(IDS_STRING85);
	ASSERT(bNameVaild);
	CBCGPRibbonCategory* pAdvCategory = m_wndRibbonBar.AddCategory (
		strTemp, IDB_RIBBON_HOMESMALL,
		IDB_RIBBON_HOMELARGE); 
		
	//添加“语言设置”面板
	bNameVaild = strTemp.LoadString(IDS_STRING86);
	ASSERT(bNameVaild);
	CBCGPRibbonPanel *pPanleSyn = pAdvCategory->AddPanel(strTemp, m_PanelImages.ExtractIcon (5));
	bNameVaild = strTemp.LoadString(IDS_STRING87);
	ASSERT(bNameVaild);
	pPanleSyn->Add(new CBCGPRibbonButton(ID_SETFORMATTER, strTemp, -1, 7));
	bNameVaild = strTemp.LoadString(IDS_STRING88);
	ASSERT(bNameVaild);
	pPanleSyn->Add(new CBCGPRibbonButton(ID_LANGEXT, strTemp, -1, 8));
	pPanleSyn->SetKeys(_T("zl"));

	//添加“编辑器设置”面板
	bNameVaild = strTemp.LoadString(IDS_STRING89);
	ASSERT(bNameVaild);
	CBCGPRibbonPanel *pPanleEdit = pAdvCategory->AddPanel(strTemp, m_PanelImages.ExtractIcon (6));
	bNameVaild = strTemp.LoadString(IDS_STRING90);
	ASSERT(bNameVaild);
	pPanleEdit->Add(new CBCGPRibbonButton(ID_SETEDIT, strTemp, -1, 9));
	bNameVaild = strTemp.LoadString(IDS_STRING91);
	ASSERT(bNameVaild);
	pPanleEdit->Add(new CBCGPRibbonButton(ID_SETHTML, strTemp, -1, 10));
	pPanleEdit->SetKeys(_T("ze"));

	//添加“导入导出”面板
	bNameVaild = strTemp.LoadString(IDS_STRING92);
	ASSERT(bNameVaild);
	CBCGPRibbonPanel *pPanlePort = pAdvCategory->AddPanel(strTemp, m_PanelImages.ExtractIcon (7));
	bNameVaild = strTemp.LoadString(IDS_STRING93);
	ASSERT(bNameVaild);
	pPanlePort->Add(new CBCGPRibbonButton(ID_EXPORTREG, strTemp, -1, 11));
	bNameVaild = strTemp.LoadString(IDS_STRING94);
	ASSERT(bNameVaild);
	pPanlePort->Add(new CBCGPRibbonButton(ID_IMPORTREG, strTemp, -1, 12));
	pPanlePort->SetKeys(_T("zr"));

	//添加“其他功能”面板
	bNameVaild = strTemp.LoadString(IDS_STRING95);
	ASSERT(bNameVaild);
	CBCGPRibbonPanel *pPanleOther = pAdvCategory->AddPanel(strTemp, m_PanelImages.ExtractIcon (8));
	bNameVaild = strTemp.LoadString(IDS_STRING96);
	ASSERT(bNameVaild);
	pPanleOther->Add(new CBCGPRibbonButton(ID_TELLBUG, strTemp, -1, 13));
	bNameVaild = strTemp.LoadString(IDS_STRING97);
	ASSERT(bNameVaild);
	pPanleOther->Add(new CBCGPRibbonButton(ID_ONLINEHELP, strTemp, -1, 14));
	pPanleOther->SetKeys (_T("zo"));

	// Create "<TODO>" panel:
	//CBCGPRibbonPanel* pPanelTODO = pAdvCategory->AddPanel (
	//	_T("<TODO>"));
	//pPanelTODO->Add (new CBCGPRibbonLabel (_T("TODO: add elements here")));

	//pPanelTODO->SetKeys (_T("zt"));


	// Add quick access toolbar commands:
	CBCGPRibbonQATDefaultState qatState;

	qatState.AddCommand (ID_FILE_NEW);
	qatState.AddCommand (ID_FILE_OPEN);
	qatState.AddCommand (ID_FILE_SAVE);
	qatState.AddCommand (ID_FILE_PRINT_DIRECT, FALSE);
	qatState.AddCommand (ID_FILE_PRINT_PREVIEW, FALSE);
	qatState.AddCommand (ID_EDIT_UNDO);
	qatState.AddCommand (ID_EDIT_REDO);

	m_wndRibbonBar.SetQuickAccessDefaultState (qatState);

	// Add "Style" button to the right of tabs:
	//CBCGPRibbonButton* pStyleButton = new CBCGPRibbonButton (-1, _T("样式\ns"), -1, -1);
	//pStyleButton->SetMenu (IDR_THEME_MENU, TRUE /* Right align */);

	//m_wndRibbonBar.AddToTabs (pStyleButton);

	CUpdateChecker checker;
	if (checker.IsHasNewVersion())
	{
		DoCheckUpdateEvenet(0, 0);
	}
	else
	{
		checker.CheckUpdate();
	}

	// Add "About" button to the right of tabs:
	m_wndRibbonBar.AddToTabs (new CBCGPRibbonButton (ID_APP_ABOUT, _T("\na"), m_PanelImages.ExtractIcon (0)));

	m_wndRibbonBar.EnableToolTips (theApp.m_bShowToolTips, theApp.m_bShowToolTipDescr);

	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
LRESULT CMainFrame::OnRibbonCustomize (WPARAM wp, LPARAM lp)
{
	ShowOptions (0);
	return 1;
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnToolsOptions()
{
	ShowOptions (0);
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::ShowOptions (int nPage)
{
	// Create "Customize" page:
	CBCGPRibbonCustomizePage pageCustomize (&m_wndRibbonBar);

	// Add "popular" items:
	CList<UINT, UINT> lstPopular;

	lstPopular.AddTail (ID_FILE_NEW);
	lstPopular.AddTail (ID_FILE_OPEN);
	lstPopular.AddTail (ID_FILE_SAVE);
	lstPopular.AddTail (ID_FILE_PRINT_PREVIEW);
	lstPopular.AddTail (ID_FILE_PRINT_DIRECT);
	lstPopular.AddTail (ID_EDIT_UNDO);
	lstPopular.AddTail(ID_EDIT_REDO);
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STRING_COMMPOPULAR);
	ASSERT(bNameVaild);
	pageCustomize.AddCustomCategory (strTemp, lstPopular);

	// Add hidden commands:
	CList<UINT,UINT> lstHidden;
	m_wndRibbonBar.GetItemIDsList (lstHidden, TRUE);
	bNameVaild = strTemp.LoadString(IDS_STRING_COMMHIDDEN);
	ASSERT(bNameVaild);
	pageCustomize.AddCustomCategory (strTemp, lstHidden);

	// Add all commands:
	CList<UINT,UINT> lstAll;
	m_wndRibbonBar.GetItemIDsList (lstAll);
	bNameVaild = strTemp.LoadString(IDS_STRING_COMMALL);
	ASSERT(bNameVaild);
	pageCustomize.AddCustomCategory (strTemp, lstAll);

	// Create property sheet:
	COptionsPropSheet propSheet (this, nPage);
	propSheet.EnablePageHeader(60);
	propSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;

	propSheet.SetLook (CBCGPPropertySheet::PropSheetLook_List, 124 /* List width */);

	CPagePopular pagePopular;
	CPageResource pageResource;
	propSheet.AddPage(&pagePopular);
	propSheet.AddPage(&pageCustomize);
	propSheet.AddPage(&pageResource);
	propSheet.EnableVisualManagerStyle(TRUE, TRUE);
	// TODO: add your option pages here:
	// COptionsPage1 pageOptions1;
	// propSheet.AddPage (&pageOptions1);
	//
	// COptionsPage1 pageOptions2;
	// propSheet.AddPage (&pageOptions2);

	if (propSheet.DoModal() != IDOK)
	{
		return;
	}

	OnAppLook (theApp.m_nAppLook);
	m_wndRibbonBar.EnableToolTips (theApp.m_bShowToolTips, theApp.m_bShowToolTipDescr);
}
//////////////////////////////////////////////////////////////////////////
LRESULT CMainFrame::OnGetTabToolTip( WPARAM wp, LPARAM lp )
{
	CBCGPTabToolTipInfo* pInfo = (CBCGPTabToolTipInfo*)lp;
	ASSERT (pInfo != NULL);
	ASSERT_VALID (pInfo->m_pTabWnd);

	if (!pInfo->m_pTabWnd->IsMDITab())
	{
		return 0;
	}

	CFrameWnd* pFrame = DYNAMIC_DOWNCAST (CFrameWnd,
		pInfo->m_pTabWnd->GetTabWnd(pInfo->m_nTabIndex));
	if (pFrame == NULL)
	{
		return 0;
	}

	CDocument* pDoc = pFrame->GetActiveDocument();
	if (pDoc == NULL)
	{
		return 0;
	}

	if (pDoc->GetPathName().IsEmpty())
	{
		pInfo->m_strText = pDoc->GetTitle();
		if (pInfo->m_strText[pInfo->m_strText.GetLength() - 1] == '*')
		{
			pInfo->m_strText = pInfo->m_strText.Left(pInfo->m_strText.GetLength() - 2);
		}
	}
	else
	{
		pInfo->m_strText = pDoc->GetPathName();
	}
	
	return 0;
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnDropFiles(HDROP hDropInfo)
{
	SetActiveWindow();      // activate us first !
	UINT nFiles = ::DragQueryFile(hDropInfo, (UINT)-1, NULL, 0);

	CWinApp* pApp = AfxGetApp();
	ASSERT(pApp != NULL);
	CString strTemp;
	BOOL bNameVaild;
	for (UINT iFile = 0; iFile < nFiles; iFile++)
	{
		TCHAR szFileName[_MAX_PATH];
		::DragQueryFile(hDropInfo, iFile, szFileName, _MAX_PATH);
		LPTSTR pszExtension = PathFindExtension(szFileName);
		if (pszExtension != NULL && *pszExtension == _T('.'))
		{
			_tcslwr_s(pszExtension, _tcslen(pszExtension) + 1);
			if (!g_GlobalUtils.m_sLanguageExt.IsDocSupport(pszExtension))
			{				
				bNameVaild = strTemp.LoadString(IDS_DOC_UNSUPPORT);
				ASSERT(bNameVaild);
				CFMessageBox(strTemp, MB_OK | MB_ICONERROR);
			}
			else
				pApp->OpenDocumentFile(szFileName);
		}
		else
			pApp->OpenDocumentFile(szFileName);
	}
	::DragFinish(hDropInfo);
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnFileOtherClose()
{
	CMDIChildWnd *pChild = (CMDIChildWnd *)GetActiveFrame();
	CMDIChildWnd *pChild2;
	CDocument *pDoc;

	MDINext();
	pChild2 = MDIGetActive();
	while ( pChild2 != pChild)
	{
		pDoc = (pChild2->GetActiveView())->GetDocument();
		if (!pDoc->SaveModified())
			return;
		pDoc->OnCloseDocument();
		pChild2 = MDIGetActive();
	}

	MDIPrev();
	pChild2 = MDIGetActive();
	while ( pChild2 != pChild)
	{
		pDoc = (pChild2->GetActiveView())->GetDocument();
		if (!pDoc->SaveModified())
			return;
		pDoc->OnCloseDocument();
		MDIPrev();
		pChild2 = MDIGetActive();
	}
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnFilePath()
{
	CString strFilePath;
	CDocument *pDoc = GetActiveFrame()->GetActiveView()->GetDocument();
	if (pDoc->GetPathName().IsEmpty())
	{
		strFilePath = pDoc->GetTitle();
		if (strFilePath[strFilePath.GetLength() - 1] == '*')
		{
			strFilePath = strFilePath.Left(strFilePath.GetLength() - 2);
		}
	}
	else
	{
		strFilePath = pDoc->GetPathName();
	}
	
	//----------------------------------剪贴板操作-----------------------------------    
	if (!OpenClipboard ())
	{
		TRACE0("Can't open clipboard\n");
		return ;
	}

	if (!::EmptyClipboard ())
	{
		TRACE0("Can't empty clipboard\n");
		::CloseClipboard ();
		return ;
	}

	HGLOBAL hClipbuffer = ::GlobalAlloc (GMEM_DDESHARE, (strFilePath.GetLength() + 1) * sizeof(TCHAR));
	if (hClipbuffer == NULL)
	{
		TRACE0("GlobalAlloc: out of memory\n");
		::CloseClipboard ();
		return ;
	}

	LPTSTR lpExpBuffer = (LPTSTR) GlobalLock (hClipbuffer);
	if (lpExpBuffer == NULL)
	{
		TRACE0("GlobalLock: out of memory\n");
		GlobalFree (hClipbuffer);
		::CloseClipboard ();
		return ;
	}
	
	memcpy (lpExpBuffer, strFilePath, strFilePath.GetLength() * sizeof(TCHAR));
	lpExpBuffer [strFilePath.GetLength()] = _T ('\0');

	GlobalUnlock (hClipbuffer);
	SetClipboardData (CF_UNICODETEXT, hClipbuffer);

	::CloseClipboard ();
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnFiledirOpen()
{
	CString strFilePath;
	CDocument *pDoc = GetActiveFrame()->GetActiveView()->GetDocument();
	if (pDoc->GetPathName().IsEmpty())
	{
		
	}
	else
	{
		strFilePath = pDoc->GetPathName();
		ShellExecute(0, 0, _T("explorer"), _T("/select, ") + strFilePath, 0, SW_SHOWNORMAL);
	}
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnAdminUrl()
{
	ShellExecute(this->m_hWnd, _T("open"), _T("http://blog.csdn.net/akof1314"), _T(""), _T(""), SW_SHOW );
}
//////////////////////////////////////////////////////////////////////////
LRESULT CMainFrame::OnShowRibbonItemMenu( WPARAM, LPARAM lp)
{
	CBCGPBaseRibbonElement* pElem = (CBCGPBaseRibbonElement*) lp;
	ASSERT_VALID (pElem);

	switch (pElem->GetID ())
	{
	case ID_EDIT_UNDO:
		// Fill Undo items list:
		{
			CBCGPRibbonUndoButton *m_pUndoButton = DYNAMIC_DOWNCAST (CBCGPRibbonUndoButton, pElem);
			ASSERT_VALID (m_pUndoButton);

			m_pUndoButton->CleanUpUndoList ();

			CSynBCGPEditView *pSynView = (CSynBCGPEditView*)MDIGetActive()->GetActiveView();
			if (pSynView && pSynView->IsKindOf(RUNTIME_CLASS(CSynBCGPEditView)))
			{
				CStringList lstActions;
				pSynView->GetUndoActions(lstActions);

				for (POSITION pos = lstActions.GetHeadPosition (); pos != NULL;)
				{
					m_pUndoButton->AddUndoAction(lstActions.GetNext(pos));
				}				
			}
		}
		break;
	}

	return 0;
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnExportreg()
{
	CString strName, strFilter;
	strName.Append(CONFIG_DEFAULT_NAME);
	strName.Append(CONFIG_EXT_NAME);
	strFilter.Format(_T("CoolFormatConfig Files(*%s)|*%s|All Files(*.*)|*.*||"), CONFIG_EXT_NAME, CONFIG_EXT_NAME);
	CFileDialog dlg(FALSE, NULL, strName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_EXTENSIONDIFFERENT,
		strFilter, NULL);
	if (dlg.DoModal() == IDOK)
	{
		CRegConfig reg;
		if (reg.ExportReg(dlg.GetPathName()))
		{
			CString strTemp;
			BOOL bNameVaild = strTemp.LoadString(IDS_STRING_CONFIGOUTOK);
			ASSERT(bNameVaild);
			strTemp.Append(dlg.GetPathName());
			CFMessageBox(strTemp, MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			CString strTemp;
			BOOL bNameVaild = strTemp.LoadString(IDS_STRING_CONFIGOUTFAIL);
			ASSERT(bNameVaild);
			CFMessageBox(strTemp, MB_OK | MB_ICONERROR);
		}
	}
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnLangext()
{
	CLangExtDlg dlg;
	dlg.DoModal();
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnSethtml()
{
	CSetHtmlDlg dlg;
	dlg.DoModal();
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnSetedit()
{
	CSetEditDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		CWaitCursor wait;
		CWinApp *pApp = AfxGetApp();
		POSITION pos = pApp->GetFirstDocTemplatePosition();
		while (pos != NULL)
		{
			CDocTemplate *pDocTemplate = pApp->GetNextDocTemplate(pos);
			POSITION posDoc = pDocTemplate->GetFirstDocPosition();
			while (posDoc != NULL)
			{
				CDocument *pDoc = pDocTemplate->GetNextDoc(posDoc);
				POSITION posView = pDoc->GetFirstViewPosition();
				while (posView != NULL)
				{
					CView *pView = pDoc->GetNextView(posView);
					if (pView->IsKindOf(RUNTIME_CLASS(CSynBCGPEditView)))
					{
						((CSynBCGPEditView *)pView)->LoadFont();
						((CSynBCGPEditView *)pView)->GetEditCtrl()->LoadColor(TRUE);
					}
				}
			}
		}
	}	
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnImportreg()
{
	CString strFilter;
	strFilter.Format(_T("CoolFormatConfig Files(*%s)|*%s|All Files(*.*)|*.*||"), CONFIG_EXT_NAME, CONFIG_EXT_NAME);
	CFileDialog dlg(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, strFilter, NULL);
	if (dlg.DoModal() == IDOK)
	{
		CRegConfig reg;
		if (reg.ImportReg(dlg.GetPathName()))
		{
			CString strTemp;
			BOOL bNameVaild = strTemp.LoadString(IDS_STRING_CONFIGOK);
			ASSERT(bNameVaild);
			CFMessageBox(strTemp, MB_OK | MB_ICONINFORMATION);
		}
		else
		{
			CString strTemp;
			BOOL bNameVaild = strTemp.LoadString(IDS_STRING_CONFIGFAIL);
			ASSERT(bNameVaild);
			CFMessageBox(strTemp, MB_OK | MB_ICONERROR);
		}
	}
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnTellbug()
{
	CTellBug dlg;
	dlg.DoModal();
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnOnlinehelp()
{
	ShellExecute(NULL, _T("open"), _T("http://blog.csdn.net/akof1314/archive/2010/03/08/5355948.aspx"), NULL, NULL, SW_SHOW);
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnSetformatter()
{
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STRING_SETFORMATTER);
	ASSERT(bNameVaild);
	CSetSheet setSheet(strTemp, this, 0);
	setSheet.DoModalAllPage();	
}
//////////////////////////////////////////////////////////////////////////
void CMainFrame::OnBatchformat()
{
	CBatchFormat dlg;
	dlg.DoModal();
}
//////////////////////////////////////////////////////////////////////////
BOOL CMainFrame::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	CString strName((LPCTSTR)pCopyDataStruct->lpData);
	strName = strName.Left(pCopyDataStruct->cbData / 2);
	LPTSTR pszExtension = PathFindExtension(strName);
	if (pszExtension != NULL && *pszExtension == _T('.'))
	{
		_tcslwr_s(pszExtension, _tcslen(pszExtension) + 1);
		if (!g_GlobalUtils.m_sLanguageExt.IsDocSupport(pszExtension))
		{
			CString strTemp;
			BOOL bNameVaild = strTemp.LoadString(IDS_DOC_UNSUPPORT);
			ASSERT(bNameVaild);
			CFMessageBox(strTemp, MB_OK | MB_ICONERROR);
		}
		else
		{
			theApp.OpenDocumentFile(strName);
		}
	}
	else
	{
		theApp.OpenDocumentFile(strName);
	}
	return CBCGPMDIFrameWnd::OnCopyData(pWnd, pCopyDataStruct);
}

void CMainFrame::OnNewvertip()
{
	ShellExecute(this->m_hWnd, _T("open"), _T("https://github.com/akof1314/CoolFormat"), _T(""), _T(""), SW_SHOW);
}

LRESULT CMainFrame::DoCheckUpdateEvenet(WPARAM wParam, LPARAM lParam)
{
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_NEWVERSION);
	ASSERT(bNameVaild);
	CBCGPRibbonHyperlink *pLink = new CBCGPRibbonHyperlink(ID_NEWVERTIP, strTemp, _T(""));
	bNameVaild = strTemp.LoadString(IDS_NEWVERSION_DESC);
	ASSERT(bNameVaild);
	pLink->SetLink(strTemp);
	m_wndRibbonBar.AddToTabs(pLink);

	if (wParam == 1)
	{
		m_wndRibbonBar.RecalcLayout();
	}
	return 0;
}
