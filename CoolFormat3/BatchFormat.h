#pragma once
#include "KofBCGPListCtrl.h"
#include  <afxtempl.h> 

typedef  CList<CString, CString &> StringList; 
typedef CList<BOOL, BOOL> BoolList;
typedef CMap<CString, LPCTSTR, int, int> MapList;

//////////////////////////////////////////////////////////////////////////
// CBatchFormat 对话框

class CBatchFormat : public CBCGPDialog
{
	DECLARE_DYNAMIC(CBatchFormat)

public:
	CBatchFormat(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBatchFormat();

// 对话框数据
	enum { IDD = IDD_BATCHFORMAT };
public:
	CKofBCGPListCtrl m_listFiles;
	CBCGPProgressCtrl m_pgcProgress;
	StringList m_fileNameList;
	BoolList m_fileCheckList;
	MapList m_fileNameMap;

	void InitList();
	void InitLang();
	void AddFileToList(LPCTSTR pszFileName);
	void LoadListToList(LPCTSTR pszFileName);
	void EnableAllWindow(BOOL bEnable);
	void DoThreadFormatter();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSavelist();
	afx_msg void OnBnClickedButtonBatchloadlist();
	afx_msg void OnBnClickedButtonBarchaddfiles();
	afx_msg void OnBnClickedButtonDobatch();
	void GetAllFiles(CString path, StringList &filenamelist, POSITION headpos);
	void AddDirToList(LPCTSTR pszDirName);
	afx_msg LRESULT DoFomatterEvenet(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLvnGetdispinfoListBatchfile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnKeydownListBatchfile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListBatchfile(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	virtual void OnCancel();
};
