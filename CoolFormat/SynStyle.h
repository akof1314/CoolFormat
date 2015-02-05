/** 
 * @file SynFont.h
 * @brief ±à¼­Æ÷×ÖÌå¡¢¸ßÁÁ×ÖÌå
 * @author ÎÞ»Ã 
 * @date 2012-5-27
 * @details 
 */ 
#pragma once

class CSynStyle
{
public:
	CSynStyle(void);
	~CSynStyle(void);

	void InitStyle(void);

	CString m_strEdtFontName;
	UINT m_uEdtFontSize;
	BOOL m_bEdtFontBold;
	BOOL m_bEdtFontItalic;
	
	CString m_strHtmlFontName;
	UINT m_uHtmlFontSize;
	BOOL m_bHtmlFontBold;
	BOOL m_bHtmlFontItalic;

	BOOL m_bHtmlShowBorder;
	int m_iHtmlBorderWidth;
	int m_iHtmlBorderStyle;
	COLORREF m_clrHtmlBorderColor;

	COLORREF m_clrHtmlBackgroundColor;
	BOOL m_bHtmlShowLineNumber;
	//COLORREF m_clrHtmlLineNumberColor;
	//COLORREF m_clrHtmlLineNumberBackColor;

	BOOL m_bHtmlShowSidebar;
	//COLORREF m_clrHtmlSidebar;
	int m_iHtmlLineHeight;

	BOOL m_bHtmlShowLangTitle;
	BOOL m_bHtmlShowAddTitle;
	CString m_strHtmlAddTitle;
	BOOL m_bHtmlAutoCopy;
	BOOL m_bHtmlCopyCode;
};
