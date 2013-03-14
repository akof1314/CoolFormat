// CoolFormat3.h : main header file for the CoolFormat3 application
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#define COOLFORMAT_CLASS _T("CoolFormat")
// CCoolFormat3App:
// See CoolFormat3.cpp for the implementation of this class
//

class CCoolFormat3App : public CWinApp,
							public CBCGPWorkspace
{
public:
	CCoolFormat3App();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	void LoadReg();
	void RunLang();
	
	/**
	 * 是否有命令行参数
	 * @return BOOL TRUE表示有参数，退出程序
	 */
	BOOL IsCmdLine();

	UINT m_nAppLook;
	BOOL m_bShowToolTips;
	BOOL m_bShowToolTipDescr;
	UINT m_nAppLanguageID;
	UINT m_nSynLanguage;
	UINT m_nBatchSyn;	//批量格式化语言选择
	BOOL m_bChangedLang;//XP下更改了线程

// Implementation
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	DECLARE_MESSAGE_MAP()
	virtual int DoMessageBox(LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt);
};

extern CCoolFormat3App theApp;