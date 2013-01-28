// CoolFormat3Doc.cpp : implementation of the CCoolFormat3Doc class
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "MainFrm.h"

#include "CoolFormat3Doc.h"
#include "CoolFormat3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCoolFormat3Doc

IMPLEMENT_DYNCREATE(CCoolFormat3Doc, CDocument)

BEGIN_MESSAGE_MAP(CCoolFormat3Doc, CDocument)
END_MESSAGE_MAP()


// CCoolFormat3Doc construction/destruction

CCoolFormat3Doc::CCoolFormat3Doc()
{
	m_bTitleMark = FALSE;

}

CCoolFormat3Doc::~CCoolFormat3Doc()
{
}

BOOL CCoolFormat3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CCoolFormat3Doc serialization

void CCoolFormat3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CCoolFormat3Doc diagnostics

#ifdef _DEBUG
void CCoolFormat3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCoolFormat3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCoolFormat3Doc commands

void CCoolFormat3Doc::SetTitle(LPCTSTR lpszTitle)
{
	CString strTitle(lpszTitle);

	if (IsModified())
	{
		if (!m_bTitleMark)
		{
			m_bTitleMark = TRUE;
			strTitle += _T(" *");
		}
	} 
	else
	{
		if (m_bTitleMark)
		{
			strTitle.ReleaseBuffer(strTitle.GetLength() - 2);
			m_bTitleMark = FALSE;
		}
	}
	CDocument::SetTitle(strTitle.GetBuffer(0));
}

void CCoolFormat3Doc::CheckTitle()
{
	if (IsModified() ^ m_bTitleMark)
	{
		SetTitle(GetTitle());
	}
}

BOOL CCoolFormat3Doc::SaveModified()
{
	if (!IsModified())
		return TRUE;        // ok to continue

	// get name/title of document
	CString name;
	if (m_strPathName.IsEmpty())
	{
		// get name based on caption
		name = GetTitle();
		if (name.IsEmpty())
			ENSURE(name.LoadString(AFX_IDS_UNTITLED));
		if (m_bTitleMark)
		{
			name = name.Left(name.GetLength() - 2);
		}
	}
	else
	{
		// get name based on file title of path name
		name = m_strPathName;
		GetFileTitle(m_strPathName, name.GetBuffer(_MAX_PATH), _MAX_PATH);
		name.ReleaseBuffer();
	}	

	CString prompt;
	BOOL bNameVaild = prompt.LoadString(IDS_IS_WANTSAVE);
	ASSERT(bNameVaild);
	CString strMsg;
	strMsg.Format(prompt, name);	
	
	switch (CFMessageBox(strMsg, MB_YESNOCANCEL| MB_ICONINFORMATION))
	{
	case IDCANCEL:
		return FALSE;       // don't continue

	case IDYES:
		// If so, either Save or Update, as appropriate
		if (!DoFileSave())
			return FALSE;       // don't continue
		break;

	case IDNO:
		// If not saving changes, revert the document
		break;

	default:
		ASSERT(FALSE);
		break;
	}
	return TRUE;    // keep going
}

BOOL CCoolFormat3Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	POSITION pos = GetFirstViewPosition();
	CCoolFormat3View *pView = (CCoolFormat3View *)GetNextView(pos);	
	pView->SaveEditFile(lpszPathName);	
	m_bTitleMark = FALSE;
	return TRUE;

	//return CDocument::OnSaveDocument(lpszPathName);
}

void CCoolFormat3Doc::OnCloseDocument()
{
	CBCGPRibbonStatusBar* pStatusBar = ((CMainFrame*) AfxGetMainWnd())->GetRibbonStatusBar ();
	CBCGPRibbonStatusBarPane* pCursorPos = DYNAMIC_DOWNCAST (
		CBCGPRibbonStatusBarPane,
		pStatusBar->FindElement (ID_STATUSBAR_PANE3));
	ASSERT_VALID (pCursorPos);

	CString strCursorPos, strTemp;
	BOOL bNameValid = strTemp.LoadString(IDS_STATUS_ROWCOL);
	ASSERT(bNameValid);
	strCursorPos.Format (strTemp, 0, 0);

	pCursorPos->SetText (strCursorPos);
	pCursorPos->Redraw ();

	CDocument::OnCloseDocument();
}

BOOL CCoolFormat3Doc::DoSave( LPCTSTR lpszPathName, BOOL bReplace /*= TRUE*/ )
{
	if ( lpszPathName == NULL )  
	{ 
		TCHAR szPath[MAX_PATH]; 
		CString strDefault = GetTitle();
		strDefault.Remove('*');
		strDefault = strDefault.Trim();

		CString strFilter = _T("All Files(*.*)|*.*|")
			_T("C/C++ Files(*.c;*.cpp;*.h;*.hpp)|*.c;*.cpp;*.h;*.hpp|")
			_T("C# Files(*.cs)|*.cs|")
			_T("Java Files(*.java)|*.java||");
		g_GlobalUtils.m_sLanguageExt.GetAllLanguageFilter(strFilter);
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_EXTENSIONDIFFERENT;     
		CFileDialog dlg(FALSE, NULL, strDefault, dwFlags, strFilter, NULL);         
		if ( dlg.DoModal() == IDOK ) 
		{ 
			CString strTemp = dlg.GetPathName();
			if (dlg.m_ofn.nFilterIndex < MAX_SYN_LANG + 1 && dlg.m_ofn.nFilterIndex > 1)
			{
				CString strExt;
				g_GlobalUtils.m_sLanguageExt.GetLanguageOneFilter(dlg.m_ofn.nFilterIndex - 2, strExt);
				strTemp.Append(strExt);
			}		                                    
			lstrcpy(szPath, strTemp.GetBuffer(0)); 
			lpszPathName = szPath;                 
		} 
		else  
			return FALSE; 
	} 
	return  CDocument::DoSave(lpszPathName, bReplace); 
}
