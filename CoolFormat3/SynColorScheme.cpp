#include "StdAfx.h"
#include "CoolFormat3.h"
#include "SynColorScheme.h"

CSynColorScheme::CSynColorScheme(void)
{
}

CSynColorScheme::~CSynColorScheme(void)
{
}

void CSynColorScheme::InitColorScheme( void )
{
	COLORREF colorReg;
	LPCTSTR lpszSubSection = _T("SynColor");
	CString strSection = theApp.GetRegSectionPath(lpszSubSection);

	CBCGPRegistrySP regSP;
	CBCGPRegistry& reg = regSP.Create (FALSE, TRUE);

	//增加默认的选定颜色
	m_DefclrBackSelActive = globalData.clrHilite;
	m_DefclrBackSelInActive = globalData.clrHilite;
	if (globalData.m_nBitsPerPixel > 8 && !globalData.IsHighContastMode ())
	{
		double H;
		double S;
		double L;

		CBCGPDrawManager::RGBtoHSL (m_DefclrBackSelInActive, &H, &S, &L);				
		m_DefclrBackSelInActive = CBCGPDrawManager::HLStoRGB_ONE (
			H,
			min (1., L * 1.1),
			min (1., S * 1.1));				
	}
	m_DefclrTextSelActive = globalData.clrTextHilite;
	m_DefclrTextSelInActive = globalData.clrTextHilite;
	if (globalData.m_nBitsPerPixel > 8 && !globalData.IsHighContastMode ())
	{
		m_DefclrTextSelInActive = CBCGPDrawManager::PixelAlpha (m_DefclrTextSelInActive, 110);
	}


	if (reg.Open (strSection))
	{
		if (!reg.Read(_T("clrBack"), colorReg))
		{
			colorReg = GetSysColor (COLOR_WINDOW);
		}
		m_clrBack = colorReg;

		if (!reg.Read(_T("clrText"), colorReg))
		{
			colorReg = GetSysColor (COLOR_WINDOWTEXT);
		}
		m_clrText = colorReg;

		if (!reg.Read(_T("clrBackSelActive"), colorReg))
		{
			colorReg = m_DefclrBackSelActive;
		}
		m_clrBackSelActive = colorReg;

		if (!reg.Read(_T("clrBackSelInActive"), colorReg))
		{
			colorReg = m_DefclrBackSelInActive;
		}
		m_clrBackSelInActive = colorReg;

		if (!reg.Read(_T("clrTextSelActive"), colorReg))
		{
			colorReg = m_DefclrTextSelActive;
		}
		m_clrTextSelActive = colorReg;

		if (!reg.Read(_T("clrTextSelInActive"), colorReg))
		{
			colorReg = m_DefclrTextSelInActive;
		}
		m_clrTextSelInActive = colorReg;

		if (!reg.Read(_T("clrBackOutline"), colorReg))
		{
			colorReg =  RGB (255, 255, 255);
		}
		m_clrBackOutline = colorReg;

		if (!reg.Read(_T("clrLineOutline"), colorReg))
		{
			colorReg = RGB (128, 128, 128);
		}
		m_clrLineOutline = colorReg;

		if (!reg.Read(_T("clrBackLineNumber"), colorReg))
		{
			colorReg = RGB (227, 227, 227);
		}
		m_clrBackLineNumber = colorReg;

		if (!reg.Read(_T("clrTextLineNumber"), colorReg))
		{
			colorReg = RGB (0, 130, 132);
		}
		m_clrTextLineNumber = colorReg;

		if (!reg.Read(_T("clrBackSidebar"), colorReg))
		{
			colorReg = RGB (0, 130, 132);
		}
		m_clrBackSidebar = colorReg;

		if (!reg.Read(_T("clrHyperlink"), colorReg))
		{
			colorReg = RGB(0, 102, 204);
		}
		m_clrHyperlink = colorReg;

		if (!reg.Read(_T("clrSyn"), colorReg))
		{
			colorReg = RGB (0, 0, 255);
		}
		m_clrSyn = colorReg;

		if (!reg.Read(_T("clrType"), colorReg))
		{
			colorReg = RGB (128, 0, 255);
		}
		m_clrType = colorReg;

		if (!reg.Read(_T("clrNumber"), colorReg))
		{
			colorReg = RGB(255, 0, 0);
		}
		m_clrNumber = colorReg;

		if (!reg.Read(_T("clrString"), colorReg))
		{
			colorReg = RGB(128, 0, 0);
		}
		m_clrString = colorReg;

		if (!reg.Read(_T("clrChar"), colorReg))
		{
			colorReg = RGB(128, 0, 0);
		}
		m_clrChar = colorReg;

		if (!reg.Read(_T("clrComment"), colorReg))
		{
			colorReg = RGB(0, 128, 0);
		}
		m_clrComment = colorReg;
	}
	else
	{
		m_clrBack = GetSysColor (COLOR_WINDOW);
		m_clrText = GetSysColor (COLOR_WINDOWTEXT);	

		m_clrBackSelActive = m_DefclrBackSelActive;	
		m_clrBackSelInActive = m_DefclrBackSelInActive;	
		m_clrTextSelActive = m_DefclrTextSelActive;	
		m_clrTextSelInActive = m_DefclrTextSelInActive;

		m_clrBackOutline = RGB (255, 255, 255);
		m_clrLineOutline = RGB (128, 128, 128);
		m_clrBackLineNumber = RGB (227, 227, 227);
		m_clrTextLineNumber = RGB (0, 130, 132);
		m_clrBackSidebar = RGB (0, 130, 132);	
		m_clrHyperlink = RGB(0, 102, 204);		

		m_clrSyn = RGB (0, 0, 255);
		m_clrType = RGB (128, 0, 255);
		m_clrNumber =  RGB(255, 0, 0);
		m_clrString = RGB(128, 0, 0);
		m_clrChar = RGB(128, 0, 0);
		m_clrComment = RGB(0, 128, 0);	
	}
}