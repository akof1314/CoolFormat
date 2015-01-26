#include "stdafx.h"
#include <afxinet.h>
#include "UpdateChecker.h"
#include "CoolFormat3.h"

const LPCTSTR s_szURL = _T("https://sourceforge.net/projects/coolformat/rss?path=/Release&limit=1");
const LPCTSTR s_szNowVersion = _T("3.3");

CUpdateChecker::CUpdateChecker()
{
}

CUpdateChecker::~CUpdateChecker()
{
}

UINT DoCheckUpdateThread(LPVOID pParam)
{
	CUpdateChecker *pThis = (CUpdateChecker *)pParam;
	if (pThis)
	{
		pThis->DoThreadCheckUpdate();
	}
	return 0;
}

void CUpdateChecker::CheckUpdate()
{
	if (!theApp.m_strNewVersion.IsEmpty())
	{
		return;
	}

	CString strTime(CTime::GetCurrentTime().Format(_T("%Y%m%d")));
	int nTime = _ttoi(strTime);
	if (theApp.m_nLastCheckUpdate != 0)
	{
		if (nTime - theApp.m_nLastCheckUpdate < 7)
		{
			return;
		}
	}

	AfxBeginThread(DoCheckUpdateThread, this);
}

int CUpdateChecker::CompareVersion(const CString &strVersion1, const CString &strVersion2)
{
	CStringList lstVersion1, lstVersion2;
	CString strToken;
	int nTokenPos = 0;

	while (!(strToken = strVersion1.Tokenize(_T("."), nTokenPos)).IsEmpty())
	{
		lstVersion1.AddTail(strToken);
	}
	nTokenPos = 0;
	while (!(strToken = strVersion2.Tokenize(_T("."), nTokenPos)).IsEmpty())
	{
		lstVersion2.AddTail(strToken);
	}

	int nMax = max(lstVersion1.GetCount(), lstVersion2.GetCount());
	for (int i = 0; i < nMax; ++i)
	{
		int nVer1 = (i < lstVersion1.GetCount()) ? _ttoi(lstVersion1.GetAt(lstVersion1.FindIndex(i))) : 0;
		int nVer2 = (i < lstVersion2.GetCount()) ? _ttoi(lstVersion2.GetAt(lstVersion2.FindIndex(i))) : 0;
		if (nVer1 != nVer2)
		{
			return nVer1 - nVer2;
		}
	}
	return 0;
}

void CUpdateChecker::DoThreadCheckUpdate()
{
	CInternetSession session;
	CHttpFile *pFile = NULL;

	try
	{
		pFile = (CHttpFile *)session.OpenURL(s_szURL);
	}
	catch (CInternetException* e)
	{
		e->Delete();
	}
	catch (CException* e)
	{
		e->Delete();
	}

	if (pFile)
	{
		DWORD dwStatusCode;
		pFile->QueryInfoStatusCode(dwStatusCode);
		if (dwStatusCode == HTTP_STATUS_OK)
		{
			char szBuf[1024] = { 0 };
			CString strHtml;

			while ((pFile->Read((void*)szBuf, 1024)) > 0)
			{
				strHtml += szBuf;
			}

			CString strFind = _T("[CDATA[/Release/CoolFormat");
			int nPosRel = strHtml.Find(strFind);
			if (nPosRel != -1)
			{
				int nPosBegin = nPosRel + strFind.GetLength();
				int nPosEnd = strHtml.Find(_T(".rar"), nPosBegin);
				if (nPosEnd != -1)
				{
					CString strVer = strHtml.Mid(nPosBegin, nPosEnd - nPosBegin);
					if (CompareVersion(strVer, s_szNowVersion) > 0)
					{
						theApp.m_strNewVersion = strVer;

						if (theApp.m_pMainWnd)
						{
							PostMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_DOCHECKUPDATEEVENT, 1, 0);
						}
					}

					CString strTime(CTime::GetCurrentTime().Format(_T("%Y%m%d")));
					int nTime = _ttoi(strTime);
					theApp.m_nLastCheckUpdate = nTime;
				}
			}
		}

		pFile->Close();
		delete pFile;
	}
	session.Close();
}

bool CUpdateChecker::IsHasNewVersion()
{
	if (theApp.m_strNewVersion.IsEmpty())
	{
		return false;
	}

	if (theApp.m_strNewVersion.Compare(s_szNowVersion) == 0)
	{
		theApp.m_strNewVersion.Empty();
		return false;
	}
	else if (CompareVersion(theApp.m_strNewVersion, s_szNowVersion) <= 0)
	{
		theApp.m_strNewVersion.Empty();
		return false;
	}

	return true;
}
