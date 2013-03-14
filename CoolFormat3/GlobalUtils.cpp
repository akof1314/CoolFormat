#include "StdAfx.h"
#include "CoolFormat3.h"
#include "GlobalUtils.h"
GlobalUtils g_GlobalUtils;

GlobalUtils::GlobalUtils(void)
{
}

GlobalUtils::~GlobalUtils(void)
{
	if (NULL != m_fontWidth.GetSafeHandle())
	{
		m_fontWidth.DeleteObject();
	}
}

void GlobalUtils::InitGlobalUtils()
{
	//开启对话框内建控件的主题（如：颜色对话框）
	globalData.m_bUseVisualManagerInBuiltInDialogs = TRUE;	
	m_sColorScheme.InitColorScheme();
	m_sStyleScheme.InitStyle();
	//m_fontWidth.CreatePointFont(85, _T("Courier New"), NULL);

	LOGFONT lf;
	memset (&lf, 0, sizeof (LOGFONT));
	//lf.lfCharSet = (BYTE) GetTextCharsetInfo (dc.GetSafeHdc (), NULL, 0);
	lf.lfWeight = FW_NORMAL;
	lf.lfHeight = -12;
	lstrcpy (lf.lfFaceName, _T("Courier New"));
	lf.lfOutPrecision =	3;
	lf.lfClipPrecision = 2;
	lf.lfQuality = 1;
	lf.lfPitchAndFamily = 49;
	m_fontWidth.CreateFontIndirect (&lf);
}

void GlobalUtils::InitGlobalUtilsFrist()
{
	g_GlobalTidy.InitGlobalTidy();
	m_sLanguageExt.InitLanguageExt();
}

int CFMessageBox( LPCTSTR lpText, UINT uType )
{
	int nResult = IDOK;	
	nResult = BCGPMessageBox(::GetActiveWindow(), lpText, COOLFORMAT_CLASS, uType);
	return nResult;
}