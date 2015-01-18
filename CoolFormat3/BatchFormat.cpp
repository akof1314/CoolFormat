// BatchFormat.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "BatchFormat.h"
#include  <direct.h> 
#include "KofFile.h"
#include "FormatterHelp.h"
#include <math.h>

#define LIST_DEFAULT_NAME _T("CoolFormatList")
#define LIST_EXT_NAME _T(".cflist")
const TCHAR WIN_EOL[] = _T("\r\n");
const int s_iIdList[] = { IDC_CHECK_BAT_C, IDC_CHECK_BAT_CS, IDC_CHECK_BAT_CSS, IDC_CHECK_BAT_HTML, IDC_CHECK_BAT_JAVA,
IDC_CHECK_BAT_JAVAST, IDC_CHECK_BAT_JSON, IDC_CHECK_BAT_OBJC, IDC_CHECK_BAT_PHP, IDC_CHECK_BAT_SQL, IDC_CHECK_BAT_XML };
const int s_iSynList[] = { SYN_CPP, SYN_CS, SYN_CSS, SYN_HTML, SYN_JAVA, SYN_JAVASCRIPT, SYN_JSON, SYN_OBJECTIVEC, SYN_PHP, SYN_SQL, SYN_XML };

// CBatchFormat 对话框

IMPLEMENT_DYNAMIC(CBatchFormat, CBCGPDialog)

CBatchFormat::CBatchFormat(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CBatchFormat::IDD, pParent)
{

}
//////////////////////////////////////////////////////////////////////////
CBatchFormat::~CBatchFormat()
{
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BATCHFILE, m_listFiles);
	DDX_Control(pDX, IDC_PROGRESS_BATCHPGR, m_pgcProgress);
}
//////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CBatchFormat, CBCGPDialog)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_SAVELIST, &CBatchFormat::OnBnClickedButtonSavelist)
	ON_BN_CLICKED(IDC_BUTTON_BATCHLOADLIST, &CBatchFormat::OnBnClickedButtonBatchloadlist)
	ON_BN_CLICKED(IDC_BUTTON_BARCHADDFILES, &CBatchFormat::OnBnClickedButtonBarchaddfiles)
	ON_BN_CLICKED(IDC_BUTTON_DOBATCH, &CBatchFormat::OnBnClickedButtonDobatch)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_BATCHFILE, &CBatchFormat::OnLvnGetdispinfoListBatchfile)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_BATCHFILE, &CBatchFormat::OnLvnKeydownListBatchfile)
	ON_NOTIFY(NM_CLICK, IDC_LIST_BATCHFILE, &CBatchFormat::OnNMClickListBatchfile)
	ON_MESSAGE(WM_DOFOMATTEREVENT, &CBatchFormat::DoFomatterEvenet)
END_MESSAGE_MAP()
//////////////////////////////////////////////////////////////////////////
BOOL CBatchFormat::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	m_fileNameList.RemoveAll();
	m_fileCheckList.RemoveAll();
	m_fileNameMap.RemoveAll();
	InitLang();
	InitList();

	int nBatchSyn = theApp.m_nBatchSyn;
	int nSizeList = sizeof(s_iIdList) / sizeof(int);
	for (int i = 0; i < nSizeList; ++i)
	{
		int nBitPow = (int)pow(2.0, i);
		((CButton *)(GetDlgItem(s_iIdList[i])))->SetCheck((nBatchSyn & nBitPow) == nBitPow);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::InitLang()
{
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STRING_BATCHFORMAT);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_BUTTON_DOBATCH, strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_BATCHEXIT);
	ASSERT(bNameVaild);
	SetDlgItemText(IDCANCEL, strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_BATCHFORMAT);
	ASSERT(bNameVaild);
	SetWindowText(strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_BATCHSELLANG);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_BATCHSELLAN, strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_BATCHSELFILE);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_BATCHSELFILES, strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_BATCHLOADLIST);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_BUTTON_BATCHLOADLIST, strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_BATCHSAVELIST);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_BUTTON_SAVELIST, strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_BATCHDROPTIP);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_DROPTIP, strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_BATCHADD);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_BUTTON_BARCHADDFILES, strTemp);
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::OnDropFiles(HDROP hDropInfo)
{
	UINT nFiles = ::DragQueryFile(hDropInfo, (UINT)-1, NULL, 0); 

	CFileFind fileDir;
	for (UINT iFile = 0; iFile < nFiles; iFile++) 
	{ 
		TCHAR szFileName[_MAX_PATH]; 
		::DragQueryFile(hDropInfo, iFile, szFileName, _MAX_PATH); 
		LPTSTR pszExtension = PathFindExtension(szFileName); 
		if (pszExtension != NULL && *pszExtension == _T('.')) 
		{ 
			_tcslwr_s(pszExtension, _tcslen(pszExtension) + 1); 
			if (0 == _tcscmp(pszExtension, _T(".cflist"))) 
			{ 
				LoadListToList(szFileName);
				continue;
			}			
		}

		if (fileDir.FindFile(szFileName))
		{
			fileDir.FindNextFile();
			if (fileDir.IsDots())
			{
			}
			else if (fileDir.IsDirectory())
			{
				AddDirToList(szFileName);
			}
			else
			{
				AddFileToList(szFileName);
			}
		}
		fileDir.Close();
	} 
	::DragFinish(hDropInfo);
	m_listFiles.SetItemCount(m_fileNameList.GetCount());

	CBCGPDialog::OnDropFiles(hDropInfo);
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::InitList()
{
	m_listFiles.SetExtendedStyle(m_listFiles.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);

	//插入列头
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STRING_FILENAMES);
	ASSERT(bNameVaild);
	m_listFiles.InsertColumn(0, strTemp, LVCFMT_LEFT, 590);
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::OnBnClickedButtonSavelist()
{
	CString strName, strFilter;
	strName.Append(LIST_DEFAULT_NAME);
	strName.Append(LIST_EXT_NAME);
	strFilter.Format(_T("CoolFormatList Files(*%s)|*%s|All Files(*.*)|*.*||"), LIST_EXT_NAME, LIST_EXT_NAME);
	CFileDialog dlg(FALSE, NULL, strName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_EXTENSIONDIFFERENT,
		strFilter, NULL);
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	CWaitCursor wait;

	CString strFileName = dlg.GetPathName();
	CFileFind find;
	if (find.FindFile(strFileName))
	{
		if (!DeleteFile(strFileName))
		{
			//find.Close();
			//return;
		}
	}
	find.Close();

	CString strList;
	strList.Empty();
	int nMaxItem = m_fileNameList.GetCount();
	for (int i = 0; i < nMaxItem; ++i)
	{
		if (m_fileCheckList.GetAt(m_fileCheckList.FindIndex(i)))
		{
			strList.Append(m_fileNameList.GetAt(m_fileNameList.FindIndex(i)));
			strList.Append(_T("\r\n"));
		}
	}

	CFile listFile;
	CFileException fileException;
	if (!listFile.Open(strFileName, CFile::modeWrite | CFile::modeCreate, &fileException))
	{
		TCHAR szErrorMsg[1024];
		fileException.GetErrorMessage(szErrorMsg, 1024, NULL);
		CFMessageBox(szErrorMsg, MB_OK | MB_ICONERROR);
		return ;
	}
	CStringA strListA(strList);
	listFile.Write(strListA, strListA.GetLength());
	listFile.Close();

	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STRING_LISTOUTOK);
	ASSERT(bNameVaild);
	strTemp.Append(strFileName);
	CFMessageBox(strTemp, MB_OK | MB_ICONINFORMATION);
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::OnBnClickedButtonBatchloadlist()
{
	CString strFilter;
	strFilter.Format(_T("CoolFormatList Files(*%s)|*%s|All Files(*.*)|*.*||"), LIST_EXT_NAME, LIST_EXT_NAME);
	CFileDialog dlg(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT, strFilter, NULL);
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	LoadListToList(dlg.GetPathName());
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::AddFileToList( LPCTSTR pszFileName )
{
	int nValue;
	if (m_fileNameMap.Lookup(pszFileName, nValue))
	{
		return;
	}
	else
	{
		m_fileNameMap.SetAt(pszFileName, 1);
	}
	CString strItem;
	strItem = pszFileName;
	m_fileNameList.AddTail(strItem);
	m_fileCheckList.AddTail(TRUE);
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::LoadListToList( LPCTSTR pszFileName )
{
	CFile listFile;
	CFileException fileException;
	if (!listFile.Open(pszFileName, CFile::modeRead, &fileException))
	{
		TCHAR szErrorMsg[1024];
		fileException.GetErrorMessage(szErrorMsg, 1024, NULL);
		CFMessageBox(szErrorMsg, MB_OK | MB_ICONERROR);
		return ;
	}
	try
	{
		CWaitCursor wait;
		const DWORD dwFileSize = (const DWORD)listFile.GetLength();
		if (dwFileSize == 0)
		{			
			return;
		}

		LPSTR pszFileBuffer = new char[dwFileSize + 2];
		ZeroMemory(pszFileBuffer, dwFileSize + 2);

#if _MSC_VER >= 1300
		listFile.Read(pszFileBuffer, dwFileSize);
#else
		listFile.ReadHuge(pszFileBuffer, dwFileSize);
#endif
		listFile.Close();

		CString strList(pszFileBuffer);
		delete[] pszFileBuffer;

		strList = strList.Trim();
		strList.Append(WIN_EOL);
		CString strMid;
		int nStart = 0;
		int nPos = strList.Find(WIN_EOL, 0);
		while (-1 != nPos)
		{
			strMid = strList.Mid(nStart, nPos - nStart);
			if (!strMid.IsEmpty())
			{
				AddFileToList(strMid);
			}
			nStart = nPos + 2;
			nPos = strList.Find(WIN_EOL, nStart);
		}
		m_listFiles.SetItemCount(m_fileNameList.GetCount());

	}
	catch (CException* e)
	{
		TCHAR szErrorMsg[1024];
		e->GetErrorMessage(szErrorMsg, 1024, NULL);
		e->Delete();
		CFMessageBox(szErrorMsg, MB_OK | MB_ICONERROR);
		return ;
	}
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::OnBnClickedButtonBarchaddfiles()
{
	CString strDir;
	BROWSEINFO bi;
	ZeroMemory(&bi, sizeof(BROWSEINFO));
	bi.hwndOwner = GetSafeHwnd();
	bi.pidlRoot = NULL;
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STRING_BATCHFINDFILES);
	ASSERT(bNameVaild);
	bi.lpszTitle = strTemp;
	bi.ulFlags = BIF_NONEWFOLDERBUTTON | BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	ITEMIDLIST *pidl = SHBrowseForFolder(&bi);
	if(pidl == NULL) 
		return;

	TCHAR szDir[MAX_PATH];
	if(!SHGetPathFromIDList(pidl, szDir)) 
		return;
	else  
		strDir = szDir;
	LPMALLOC pMalloc;
	if (SUCCEEDED(SHGetMalloc(&pMalloc)))
	{
		pMalloc->Free(pidl);
		pMalloc->Release();
	}

	AddDirToList(strDir);	
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::GetAllFiles(CString path, StringList &filenamelist, POSITION headpos)
{
	WIN32_FIND_DATA fdata = {0};
	_tchdir(path.GetBuffer(0));
	path.ReleaseBuffer();
	HANDLE hSearch = FindFirstFile(_T("*"), &fdata);
	if(hSearch == INVALID_HANDLE_VALUE)
		return;
	CString FileName;

	if((fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(fdata.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
	{
		if(fdata.cFileName[0] != '.')
		{
			CString childpath;
			childpath.Format(_T("%s\\%s"), path, fdata.cFileName);
			SetCurrentDirectory(childpath.GetBuffer(0));
			childpath.ReleaseBuffer();
			GetAllFiles(childpath, filenamelist, headpos);
			SetCurrentDirectory(_T(".."));
		}
	}
	else if (!(fdata.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
	{
		FileName.Format(_T("%s\\%s"), path, fdata.cFileName);
		filenamelist.InsertAfter(headpos, FileName);
	}

	while(FindNextFile(hSearch, &fdata))
	{
		if((fdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !(fdata.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
		{
			if(fdata.cFileName[0] != '.')
			{

				CString childpath;
				childpath.Format(_T("%s\\%s"), path, fdata.cFileName);
				SetCurrentDirectory(childpath.GetBuffer(0));
				childpath.ReleaseBuffer();
				GetAllFiles(childpath, filenamelist, headpos);
				SetCurrentDirectory(_T(".."));
			}
		}
		else if (!(fdata.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM))
		{
			FileName.Format(_T("%s\\%s"), path, fdata.cFileName);
			filenamelist.InsertAfter(headpos, FileName);
		}
	}

	FindClose(hSearch);
}
//////////////////////////////////////////////////////////////////////////
UINT DoBatchFormatterThread(LPVOID pParam)
{
	CBatchFormat *pThis = (CBatchFormat *)pParam;
	if (pThis)
	{
		pThis->DoThreadFormatter();
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::OnBnClickedButtonDobatch()
{
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STRING_BATCH_EMPTY);
	ASSERT(bNameVaild);
	int nCount = m_fileNameList.GetCount();
	if (0 == nCount)
	{
		CFMessageBox(strTemp, MB_OK | MB_ICONERROR);
		return;
	}
	
	bNameVaild = strTemp.LoadString(IDS_STRING_BATCH_QUEREN);
	ASSERT(bNameVaild);
	if (CFMessageBox(strTemp, MB_OKCANCEL | MB_ICONINFORMATION) != IDOK)
	{
		return;
	}

	m_pgcProgress.SetRange(0, nCount);
	m_pgcProgress.SetPos(0);
	m_pgcProgress.SetStep(1);
	EnableAllWindow(FALSE);	
	m_pgcProgress.ShowWindow(SW_SHOW);
	AfxBeginThread(DoBatchFormatterThread, this);
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::EnableAllWindow( BOOL bEnable )
{
	GetDlgItem(IDC_CHECK_BAT_C)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_BAT_CS)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_BAT_CSS)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_BAT_HTML)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_BAT_JAVA)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_BAT_JAVAST)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_BAT_JSON)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_BAT_PHP)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_BAT_OBJC)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_BAT_SQL)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHECK_BAT_XML)->EnableWindow(bEnable);

	GetDlgItem(IDC_LIST_BATCHFILE)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_BARCHADDFILES)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_BATCHLOADLIST)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_SAVELIST)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_DOBATCH)->EnableWindow(bEnable);
	GetDlgItem(IDCANLE)->EnableWindow(bEnable);
	if (bEnable)
	{
		GetSystemMenu(FALSE)->EnableMenuItem(SC_CLOSE, MF_ENABLED | MF_BYCOMMAND);
	} 
	else
	{
		GetSystemMenu(FALSE)->EnableMenuItem(SC_CLOSE, MF_DISABLED | MF_BYCOMMAND | MF_GRAYED);
	}
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::OnLvnGetdispinfoListBatchfile(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	LV_ITEM* pItem = &(pDispInfo)->item;

	int iItem = pItem->iItem;

	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		switch(pItem->iSubItem)
		{
		case 0: //fill in main text
			_tcscpy_s(pItem->pszText, pItem->cchTextMax,
				m_fileNameList.GetAt(m_fileNameList.FindIndex(iItem)));
			break;
		}
	}
	pItem->mask |= LVIF_STATE;
	pItem->stateMask = LVIS_STATEIMAGEMASK;
	if (m_fileCheckList.GetAt(m_fileCheckList.FindIndex(iItem)))
	{
		pItem->state = INDEXTOSTATEIMAGEMASK(2);
	}
	else
	{
		pItem->state = INDEXTOSTATEIMAGEMASK(1);
	}
	
	*pResult = 0;
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::OnLvnKeydownListBatchfile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDown = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	if( pLVKeyDown->wVKey == VK_SPACE )
	{
		int item = m_listFiles.GetSelectionMark();
		if(item != -1)
		{
			m_fileCheckList.GetAt(m_fileCheckList.FindIndex(item)) = !m_fileCheckList.GetAt(m_fileCheckList.FindIndex(item));
			m_listFiles.RedrawItems(item, item);
		}
	}
	*pResult = 0;
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::OnNMClickListBatchfile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	LVHITTESTINFO hitinfo;
	hitinfo.pt = pNMItemActivate->ptAction;
	int item = m_listFiles.HitTest(&hitinfo);
	if(item != -1)
	{
		if( (hitinfo.flags & LVHT_ONITEMSTATEICON) != 0)
		{
			m_fileCheckList.GetAt(m_fileCheckList.FindIndex(item)) = !m_fileCheckList.GetAt(m_fileCheckList.FindIndex(item));
			m_listFiles.RedrawItems(item, item);
		}
	}
	*pResult = 0;
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::AddDirToList( LPCTSTR pszDirName )
{
	CString strFileExt, strSynExt;
	int nSizeList = sizeof(s_iIdList) / sizeof(int);
	for (int i = 0; i < nSizeList; ++i)
	{
		if (((CButton *)(GetDlgItem(s_iIdList[i])))->GetCheck())
		{
			g_GlobalUtils.m_sLanguageExt.GetLanguageFilter(s_iSynList[i], strSynExt);
			strFileExt.Append(strSynExt);
		}
	}

	StringList allFileNameList;
	CWaitCursor wait;
	CString Head = _T(".");
	POSITION pos = allFileNameList.AddHead(Head);
	GetAllFiles(pszDirName, allFileNameList, pos);

	CString FileName, NameExt;
	int extPos = -1;
	int nCount = allFileNameList.GetCount();
	for (int i = 1; i < nCount; i++)
	{
		POSITION pos = allFileNameList.FindIndex(i);
		FileName = allFileNameList.GetAt(pos);
		if (strFileExt.IsEmpty())
		{
			AddFileToList(FileName);
		}
		else
		{
			if (FileName.ReverseFind('.') != -1)
			{
				NameExt = FileName.Right(FileName.GetLength() - FileName.ReverseFind('.') - 1);
				NameExt.Insert(0, '.');
				NameExt.Append(_T(";"));
				extPos = strFileExt.Find(NameExt);
				if (-1 != extPos)
				{
					AddFileToList(FileName);
				}
			}
		}		
	}
	m_listFiles.SetItemCount(m_fileNameList.GetCount());
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::DoThreadFormatter()
{
	// 多线程处理格式化，不要在这里操作界面
	int nCount = m_fileNameList.GetCount();
	CString strName, strExt, strText;
	int nSynIndex;
	CString strTextOut, strMsgOut;
	CFormatterHelp formatterSP;	
	for (int i = 0; i < nCount; ++i)
	{
		do 
		{
			if (FALSE == m_fileCheckList.GetAt(m_fileCheckList.FindIndex(i)))
			{
				break;
			}
	
			strText.Empty();
			strName = m_fileNameList.GetAt(m_fileNameList.FindIndex(i));
			strExt = strName.Right(strName.GetLength() - strName.ReverseFind('.') - 1);
			nSynIndex = g_GlobalUtils.m_sLanguageExt.GetLanguageByExt(strExt);
			if (FALSE == g_GlobalTidy.m_bTidySyn[nSynIndex])
			{
				break;
			}
	
			CKofFile m_File;
			if (!m_File.OpenFile(strName, strText))
			{
				break;
			}
			if (strText.IsEmpty())
			{
				break;
			}
	
			strTextOut.Empty();
			if (formatterSP.DoFormatter(nSynIndex, strText, strTextOut, strMsgOut, m_File.GetCodepage()))
			{
				m_File.SaveFile(strName, strTextOut);
			}
			//Sleep(1000);
		} while (0);
		PostMessage(WM_DOFOMATTEREVENT);
	}
	PostMessage(WM_DOFOMATTEREVENT);
}
//////////////////////////////////////////////////////////////////////////
LRESULT CBatchFormat::DoFomatterEvenet( WPARAM wParam, LPARAM lParam )
{
	if (FALSE == m_pgcProgress.IsWindowVisible())
	{
		return 0;
	}
	m_pgcProgress.StepIt();
	if (m_pgcProgress.GetPos() >=  m_fileNameList.GetCount())
	{
		m_pgcProgress.ShowWindow(SW_HIDE);
		EnableAllWindow(TRUE);
		CString strTemp;
		BOOL bNameVaild = strTemp.LoadString(IDS_STRING_BATCH_OVER);
		ASSERT(bNameVaild);
		CFMessageBox(strTemp, MB_OK | MB_ICONINFORMATION);
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////
void CBatchFormat::OnCancel()
{
	int nSizeList = sizeof(s_iIdList) / sizeof(int);
	int nBatchSyn = 0;
	int nCheck;
	for (int i = 0; i < nSizeList; ++i)
	{
		nCheck = (BOOL)((CButton *)(GetDlgItem(s_iIdList[i])))->GetCheck();
		if (1 == nCheck)
		{
			nBatchSyn |= (int)pow(2.0, i);
		}
		else
		{
			nBatchSyn &= (int)pow(2.0, i) - 1;
		}		
	}
	theApp.m_nBatchSyn = nBatchSyn;

	CBCGPDialog::OnCancel();
}
