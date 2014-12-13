
// MakeSetConfig.h : main header file for the MakeSetConfig application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMakeSetConfigApp:
// See MakeSetConfig.cpp for the implementation of this class
//

class CMakeSetConfigApp : public CWinAppEx
{
public:
	CMakeSetConfigApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMakeSetConfigApp theApp;
