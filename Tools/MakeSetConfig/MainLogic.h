#pragma once

#define PROP_DATA_TYPE 300
#define PROP_DATA_ITEMS 301

class CMainLogic
{
public:
	CMainLogic();
	~CMainLogic();

	void LoadRCFile(LPCTSTR lpszFileName);
	void OpenConfigFile(CTreeCtrl* pTreeCtrl);
	BOOL SaveConfigFile(CTreeCtrl* pTreeCtrl);
	BOOL SaveConfigToHTMLFile(CTreeCtrl* pTreeCtrl);
	void ModifyRCFile(LPCTSTR lpszAddConfig, LPCTSTR lpszDelConfig);

	const CStringList* GetConfigs() { return &m_lstConfigs; }

private:
	BOOL ParseRCText(LPCTSTR lpszFileName, const CString& strText);
	void EntityToSymbol(CString& value);
	CString SymbolToEntity(const CString& value);
	BOOL OpenFile(LPCTSTR lpszFileName, CString& value);

private:
	CString m_strRCFileName;
	CString m_strConfigPath;
	CString m_strFullConfigPath;
	CStringList m_lstConfigs;
};

