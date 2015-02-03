// CoolFormat3.cpp : Defines the class behaviors for the application.

#include "stdafx.h"
#include "CoolFormat3.h"
#include "MainFrm.h"
#include "SetSheet.h"
#include "SetPageBase.h"

#include "ChildFrm.h"
#include "CoolFormat3Doc.h"
#include "CoolFormat3View.h"

#include "GlobalUtils.h"
#include "KofFile.h"
#include "FormatterHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCoolFormat3App

BEGIN_MESSAGE_MAP(CCoolFormat3App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CCoolFormat3App construction

CCoolFormat3App::CCoolFormat3App() :
	CBCGPWorkspace (TRUE /* m_bResourceSmartUpdate */)
{
	m_bOnlyShowSettings = FALSE;
}


// The one and only CCoolFormat3App object

CCoolFormat3App theApp;


// CCoolFormat3App initialization

BOOL CCoolFormat3App::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	//AfxEnableControlContainer();

	//globalData.SetDPIAware ();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("CoolFormat"));
	LoadStdProfileSettings(8);  // Load standard INI file options (including MRU)

	SetRegistryBase (_T("Settings"));	

	//加载注册表配置
	LoadReg();
	if (IsCmdLine())
	{
		return FALSE;
	}
	globalData.SetDPIAware();
	RunLang();

	if (m_bOnlyShowSettings)
	{
		CString strTemp;
		BOOL bNameVaild = strTemp.LoadString(IDS_STRING_SETFORMATTER);
		ASSERT(bNameVaild);
		CSetSheet setSheet(strTemp, NULL, 0);
		setSheet.DoModalAllPage(TRUE);
		return FALSE;
	}

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	InitContextMenuManager();
	InitKeyboardManager();

	// TODO: Remove this if you don't want extended tooltips:
	InitTooltipManager();

	CBCGPToolTipParams params;
	params.m_bVislManagerTheme = TRUE;

	theApp.GetTooltipManager ()->SetTooltipParams (
		BCGP_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS (CBCGPToolTipCtrl),
		&params);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_CoolFormat3TYPE,
		RUNTIME_CLASS(CCoolFormat3Doc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CCoolFormat3View));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	/*if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
	{
		if (!pMainFrame->LoadMDIState (GetRegSectionPath ()))
		{
			if (!ProcessShellCommand(cmdInfo))
				return FALSE;
		}
	}
	else*/
	{
		// Dispatch commands specified on the command line
		if (!ProcessShellCommand(cmdInfo))
			return FALSE;
	}

	m_pMainWnd->DragAcceptFiles(TRUE);

	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

// CCoolFormat3App message handlers

int CCoolFormat3App::ExitInstance() 
{
	WriteInt(_T("ApplicationLook"), m_nAppLook);
	WriteInt(_T("ShowToolTips"), m_bShowToolTips);
	WriteInt(_T("ShowToolTipDescr"), m_bShowToolTipDescr);
	WriteInt(_T("ApplicationLanguage"), m_nAppLanguageID);
	WriteInt(_T("SynLanguage"), m_nSynLanguage);
	WriteInt(_T("BatchLanguage"), m_nBatchSyn);
	WriteInt(_T("LastCheckUpdate"), m_nLastCheckUpdate);
	WriteString(_T("LastNewVersion"), m_strNewVersion);
	BCGCBProCleanUp();

	return CWinApp::ExitInstance();
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CBCGPDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };
	CBCGPURLLinkButton m_btnURL;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CBCGPDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPANY_URL, m_btnURL);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBCGPDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CCoolFormat3App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.EnableVisualManagerStyle(TRUE, TRUE);
	aboutDlg.DoModal();
}


// CCoolFormat3App message handlers


void CCoolFormat3App::PreLoadState ()
{
	GetContextMenuManager()->AddMenu(IDS_STRING_MENU_EDIT, IDR_EDIT_CONTEXT_MENU);
	GetContextMenuManager()->AddMenu(IDS_STRING_MENU_HTML, IDR_HTML_CONTEXT_MENU);
}

void CCoolFormat3App::OnFileOpen()
{
	CString strFilter = _T("All Files(*.*)|*.*|")
		_T("C/C++ Files(*.c;*.cpp;*.h;*.hpp)|*.c;*.cpp;*.h;*.hpp|")
		_T("C# Files(*.cs)|*.cs|")
		_T("Java Files(*.java)|*.java||");
	g_GlobalUtils.m_sLanguageExt.GetAllLanguageFilter(strFilter);
	CFileDialog dlg(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, strFilter, NULL);
	if (IDOK == dlg.DoModal())
	{
		CString strExt;
		strExt.Format(_T(".%s"), dlg.GetFileExt());
		strExt.MakeLower();

		if (!g_GlobalUtils.m_sLanguageExt.IsDocSupport(strExt))
		{
			CString strTemp;
			BOOL bNameVaild = strTemp.LoadString(IDS_DOC_UNSUPPORT);
			ASSERT(bNameVaild);
			CFMessageBox(strTemp, MB_OK | MB_ICONERROR);
			return;
		}
		theApp.OpenDocumentFile(dlg.GetPathName());
	}
}

int CCoolFormat3App::DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT /*nIDPrompt*/)
{
	return CFMessageBox(lpszPrompt, nType);
	//return __super::DoMessageBox(lpszPrompt, nType, nIDPrompt);
}

void CCoolFormat3App::LoadReg()
{
	m_nAppLook = GetInt (_T("ApplicationLook"), ID_VIEW_APPLOOK_2010_3);
	m_bShowToolTips = GetInt (_T("ShowToolTips"), TRUE);
	m_bShowToolTipDescr = GetInt (_T("ShowToolTipDescr"), TRUE);
	m_nAppLanguageID = GetInt(_T("ApplicationLanguage"), 0);
	m_nSynLanguage = GetInt(_T("SynLanguage"), SYN_NORMALTEXT);
	m_nBatchSyn = GetInt(_T("BatchLanguage"), 0);
	m_nLastCheckUpdate = GetInt(_T("LastCheckUpdate"), 0);
	m_strNewVersion = GetString(_T("LastNewVersion"));
	g_GlobalUtils.InitGlobalUtilsFrist();
}

void CCoolFormat3App::RunLang()
{
	g_GlobalUtils.InitGlobalUtils();
	//0表示第一次启动程序，判断操作系统语言
	//1表示中文，2表示英文
	LANGID langNowID = GetUserDefaultLangID();
	LANGID langCHS = MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED);
	LANGID langENG = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
	if (0 == m_nAppLanguageID)
	{
		if (langNowID == langCHS)
		{
			m_nAppLanguageID = 1;
			return;
		}
		else if (langNowID == langENG)
		{
			m_nAppLanguageID = 2;
			return;
		}
		else
		{
			m_nAppLanguageID = 2;			
		}
	}	
	if (globalData.bIsWindowsVista)
	{
		if (1 == m_nAppLanguageID)
		{
			if (langNowID != langCHS)
			{
				SetThreadUILanguage(langCHS);
			}
		} 
		else
		{
			if (langNowID != langENG)
			{
				SetThreadUILanguage(langENG);
			}
		}
	}
	else
	{
		if (1 == m_nAppLanguageID)
		{
			if (langNowID != langCHS)
			{
				SetThreadLocale(MAKELCID(langCHS, SORT_DEFAULT));
			}
		} 
		else
		{
			if (langNowID != langENG)
			{
				SetThreadLocale(MAKELCID(langENG, SORT_DEFAULT));
			}
		}
	}
}

BOOL CCoolFormat3App::IsCmdLine()
{
	CString strCmd(theApp.m_lpCmdLine);
	CString strArgs(strCmd.Left(3));
	CString strName(strCmd);
	BOOL bFormatter = FALSE;
	if (0 == strArgs.CompareNoCase(_T("-f ")))
	{
		strName = strCmd.Mid(3);
		bFormatter = TRUE;
	}
	else if (0 == strArgs.CompareNoCase(_T("-s")))
	{
		m_bOnlyShowSettings = TRUE;
		return FALSE;
	}

	BOOL bFindFile = FALSE;
	if (strName.GetLength() > 0)
	{
		strName = strName.Trim('"');
		CFileFind fileFind;
		if (fileFind.FindFile(strName))
		{
			bFindFile = TRUE;
		}		
		fileFind.Close();
	}

	if (!bFindFile)
	{
		return bFormatter;
	}

	if (bFormatter)
	{
		CString strExt, strText;
		CString strTextOut, strMsgOut;
		int nSynIndex;
		CFormatterHelp formatterSP;		
		strExt = strName.Right(strName.GetLength() - strName.ReverseFind('.') - 1);
		nSynIndex = g_GlobalUtils.m_sLanguageExt.GetLanguageByExt(strExt);
		if (FALSE == g_GlobalTidy.m_bTidySyn[nSynIndex])
		{
			return TRUE;
		}

		CKofFile m_File;
		if (!m_File.OpenFile(strName, strText))
		{
			return TRUE;
		}
		if (strText.IsEmpty())
		{
			return TRUE;
		}

		strTextOut.Empty();
		if (formatterSP.DoFormatter(nSynIndex, strText, strTextOut, strMsgOut, m_File.GetCodepage()))
		{
			m_File.SaveFile(strName, strTextOut);
		}
		return TRUE;
	} 
	else
	{
		HWND hCoolFormat = FindWindow(COOLFORMAT_CLASS, NULL);
		if (!hCoolFormat)
		{
			return FALSE;
		}

		int nCmdShow = SW_SHOW;
		if (IsZoomed(hCoolFormat))
		{
			nCmdShow = SW_MAXIMIZE;
		} 
		else if (IsIconic(hCoolFormat))
		{
			nCmdShow = SW_RESTORE;
		}
		ShowWindow(hCoolFormat, nCmdShow);
		SetForegroundWindow(hCoolFormat);

		COPYDATASTRUCT fileNamesData;
		fileNamesData.dwData = 0;
		fileNamesData.cbData = strName.GetLength() * sizeof(TCHAR);
		fileNamesData.lpData = (void *)strName.GetBuffer(fileNamesData.cbData);
		SendMessage(hCoolFormat, WM_COPYDATA, NULL, (LPARAM)&fileNamesData);
		strName.ReleaseBuffer();
		return TRUE;
	}
	
	return FALSE;
}

BOOL CAboutDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STRING_ABOUTDESC);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_ABOUT, strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_WUHUAN);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_WUHUAN, strTemp);

	bNameVaild = strTemp.LoadString(IDOK);
	ASSERT(bNameVaild);
	SetDlgItemText(IDOK, strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_VERSION);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_VERSION, strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_RES_ABOUTLB);
	ASSERT(bNameVaild);
	SetWindowText(strTemp);

	m_btnURL.SizeToContent();
	bNameVaild = strTemp.LoadString(IDS_STRING_GOWUHUAN);
	ASSERT(bNameVaild);
	m_btnURL.SetTooltip(strTemp);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

