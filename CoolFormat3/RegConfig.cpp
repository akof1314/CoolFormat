#include "StdAfx.h"
#include "CoolFormat3.h"
#include "RegConfig.h"

static const TCHAR g_chSection[][9] = {_T("SynColor"), _T("SynStyle"), _T("SynExt"), _T("SynTidy")};

CRegConfig::CRegConfig(void)
{
}

CRegConfig::~CRegConfig(void)
{
}

BOOL CRegConfig::ImportReg(LPCTSTR pszFileName)
{
	if (pszFileName == NULL)
	{
		return FALSE;
	}
	
	CWaitCursor wait;

	CFileFind find;
	if (!find.FindFile(pszFileName))
	{		
		return FALSE;
	}
	find.Close();

	int nSectionLen = sizeof(g_chSection) / sizeof(g_chSection[0]);
	for (int i = 0; i < nSectionLen; ++i )
	{
		if (!RestoreRegFromConfig(g_chSection[i], pszFileName))
			return FALSE;
	}
	return TRUE;
}

BOOL CRegConfig::ExportReg(LPCTSTR pszFileName)
{
	if (pszFileName == NULL)
	{
		return FALSE;
	}

	CWaitCursor wait;

	CFileFind find;
	if (find.FindFile(pszFileName))
	{
		if (!DeleteFile(pszFileName))
		{
			find.Close();
			return FALSE;
		}
	}
	find.Close();
	
	int nSectionLen = sizeof(g_chSection) / sizeof(g_chSection[0]);
	for (int i = 0; i < nSectionLen; ++i )
	{
		if (!SaveRegToConfig(g_chSection[i], pszFileName))
			return FALSE;
	}
	return TRUE;
}

BOOL CRegConfig::SaveRegToConfig( LPCTSTR pszSection, LPCTSTR pszFileName )
{
	ASSERT (pszSection != NULL);

	HKEY hKey = HKEY_CURRENT_USER;

	CString strPath = theApp.GetRegSectionPath(pszSection);
	int iPathLen = strPath.GetLength ();
	if (iPathLen > 0 && strPath [iPathLen - 1] == _T('\\'))
	{
		strPath = strPath.Left (iPathLen - 1);
	}

	LONG ReturnValue = RegOpenKeyEx (hKey, strPath, 0L,
		 KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_NOTIFY, &hKey);

	if(ReturnValue != ERROR_SUCCESS)
	{
		//不存在此项注册表，则不导出
		if (ReturnValue == 2)
		{
			return TRUE;
		}
		return FALSE;
	}

	DWORD rc = ERROR_SUCCESS;
	BOOL result = FALSE;
	TCHAR szValue[ 1024 ];
	TCHAR szData[ 1024 ];
	DWORD length = sizeof( szValue );
	DWORD lenData = sizeof( szData );
	DWORD dwType = 0;
	int index = 0;

	ASSERT(hKey);

	CString strData;
	rc = RegEnumValue(hKey, index, szValue, &length, NULL, &dwType, (LPBYTE)szData, &lenData);
	if( rc == ERROR_NO_MORE_ITEMS) {
		result = TRUE;
	}
	else while( rc == ERROR_SUCCESS )  {
		result = TRUE;

		switch (dwType)
		{
		case REG_SZ:
			strData.Format(_T("\"\"%s\"\""), szData);
			break;
		case REG_DWORD:
			{
				DWORD dwValueData;
				memcpy(&dwValueData, szData, sizeof(dwValueData));
				strData.Format(_T("%lu"), dwValueData);
			}
			break;
		default:
			strData.Empty();
			break;
		}
		WritePrivateProfileString(pszSection, szValue, strData, pszFileName);

		dwType = 0;
		length = sizeof( szValue );
		lenData = sizeof( szData );
		index++;
		rc = RegEnumValue(hKey, index, szValue, &length, NULL, &dwType, (LPBYTE)szData, &lenData);		
	}
	RegCloseKey(hKey);
	hKey = NULL;
	return( result );
}

BOOL CRegConfig::RestoreRegFromConfig( LPCTSTR pszSection, LPCTSTR pszFileName )
{
	ASSERT (pszSection != NULL);

	HKEY hKey = HKEY_CURRENT_USER;

	CString strPath = theApp.GetRegSectionPath(pszSection);
	int iPathLen = strPath.GetLength ();
	if (iPathLen > 0 && strPath [iPathLen - 1] == _T('\\'))
	{
		strPath = strPath.Left (iPathLen - 1);
	}

	DWORD dw;
	LONG ReturnValue = RegCreateKeyEx (hKey, strPath, 0L, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
		&hKey, &dw);

	if(ReturnValue != ERROR_SUCCESS)
		return FALSE;

	BOOL result = FALSE;
	TCHAR szKeyName[1024];
	DWORD dwReturnSize = GetPrivateProfileString(pszSection, NULL, NULL, szKeyName, 1024, pszFileName);
	if (dwReturnSize > 0)
	{
		result = TRUE;
		UINT uKeyValueLen = 0;
		TCHAR szKeyValue[1024];
		TCHAR szKeyData[1024];
		CString strRegData;
		DWORD dwRegData;
		for (UINT i = 0; i < dwReturnSize; ++i)
		{
			szKeyValue[uKeyValueLen++] = szKeyName[i];
			if (szKeyName[i] == '\0')
			{
				if (GetPrivateProfileString(pszSection, szKeyValue, NULL, szKeyData, 1024, pszFileName) > 0)
				{
					TRACE(_T("%s=%s\r"), szKeyValue, szKeyData);
					if (_tcslen(szKeyData) == 0)
					{
						continue;
					}
					else if (szKeyData[0] == '\"')
					{
						szKeyData[_tcslen(szKeyData) - 1] = '\0';
						ReturnValue = RegSetValueEx (hKey, szKeyValue, 0L, REG_SZ,
							(CONST BYTE*) (szKeyData + 1), (DWORD) (_tcslen(szKeyData)) * (sizeof(TCHAR)));

						if(ReturnValue != ERROR_SUCCESS)
							result = FALSE;
					}
					else
					{
						dwRegData = (unsigned long)_ttol(szKeyData);
						ReturnValue = RegSetValueEx (hKey, szKeyValue, 0L, REG_DWORD,
							(CONST BYTE*) &dwRegData, sizeof(DWORD));

						if(ReturnValue != ERROR_SUCCESS)
							 result = FALSE;
					}					
				}
				uKeyValueLen = 0;
			}
		}
	}
	else
	{
		//没有指定项，也略过
		result = TRUE;
	}
	RegCloseKey(hKey);
	hKey = NULL;
	return result;
}