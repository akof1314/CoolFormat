#include "stdafx.h"
#include "MakeSetConfig.h"
#include "MainFrm.h"
#include "MainLogic.h"
#include "afxtagmanager.h"

#define STR_XML_NAME_BEGIN _T("IDR_SETCONFIG_XML_")

CMainLogic::CMainLogic()
{
}


CMainLogic::~CMainLogic()
{
}

void CMainLogic::LoadRCFile(LPCTSTR lpszFileName)
{
	CFile listFile;
	CFileException fileException;
	if (!listFile.Open(lpszFileName, CFile::modeRead, &fileException))
	{
		TCHAR szErrorMsg[1024];
		fileException.GetErrorMessage(szErrorMsg, 1024, NULL);
		AfxMessageBox(szErrorMsg, MB_OK | MB_ICONERROR);
		return;
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

		CString strText(pszFileBuffer);
		delete[] pszFileBuffer;

		ParseRCText(lpszFileName, strText);
	}
	catch (CException* e)
	{
		TCHAR szErrorMsg[1024];
		e->GetErrorMessage(szErrorMsg, 1024, NULL);
		e->Delete();
		AfxMessageBox(szErrorMsg, MB_OK | MB_ICONERROR);
	}
}

BOOL CMainLogic::ParseRCText(LPCTSTR lpszFileName, const CString& strText)
{
	int nPosXml = strText.Find(_T("// XML\r\n//\r\n\r\n"));
	if (nPosXml == -1)
	{
		AfxMessageBox(_T("Could not find the xml"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	m_strRCFileName = lpszFileName;
	m_strConfigPath.Empty();
	m_lstConfigs.RemoveAll();

	int nPosConfigBegin = strText.Find(STR_XML_NAME_BEGIN, nPosXml);
	while (nPosConfigBegin != -1)
	{
		int nPosNameBegin = strText.Find(_T("\""), nPosConfigBegin);
		if (nPosNameBegin != -1)
		{
			int nPosNameEnd = strText.Find(_T("\""), nPosNameBegin + 1);
			if (nPosNameEnd != -1)
			{
				CString strFullName = strText.Mid(nPosNameBegin + 1, nPosNameEnd - nPosNameBegin - 1);
				nPosNameBegin = strFullName.ReverseFind(_T('\\'));
				m_lstConfigs.AddTail(strFullName.Mid(nPosNameBegin + 1));

				if (m_strConfigPath.IsEmpty())
				{
					m_strConfigPath = strFullName.Left(nPosNameBegin);

					m_strFullConfigPath = m_strConfigPath;
					m_strFullConfigPath.Replace(_T("\\\\"), _T("\\"));

					nPosNameBegin = m_strRCFileName.ReverseFind(_T('\\'));
					m_strFullConfigPath.Insert(0, m_strRCFileName.Left(nPosNameBegin + 1));
				}

				nPosConfigBegin = strText.Find(STR_XML_NAME_BEGIN, nPosNameEnd);
				continue;
			}
		}

		break;
	}

	((CMainFrame*)AfxGetMainWnd())->RefreshConfigView();
	return TRUE;
}
