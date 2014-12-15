#pragma once
class CMainLogic
{
public:
	CMainLogic();
	~CMainLogic();

	void LoadRCFile(LPCTSTR lpszFileName);

private:
	BOOL ParseRCText(LPCTSTR lpszFileName, const CString& strText);

private:
	CString m_strRCFileName;
	CString m_strConfigPath;
	CString m_strFullConfigPath;
	CStringList m_lstConfigs;
};

