/** 
 * @file FormatterHelp.h
 * @brief 格式化辅助类
 * @author 无幻 
 * @date 2012-6-17
 * @details 
 */ 
#pragma once

class CFormatterHelp
{
public:
	CFormatterHelp(void);
	~CFormatterHelp(void);

	BOOL DoFormatter(UINT nLanguage, const char *pTextIn, CString &strTextOut, CString &strMsgOut);

protected:
	BOOL FormatterCpp(const char *pTextIn, CString &strTextOut);
	BOOL FormatterCs(const char *pTextIn, CString &strTextOut);
	BOOL FormatterJava(const char *pTextIn, CString &strTextOut);
	BOOL FormatterHtml(const char *pTextIn, CString &strTextOut, CString &strMsgOut);
	BOOL FormatterXml(const char *pTextIn, CString &strTextOut, CString &strMsgOut);
	BOOL FormatterPhp(const char *pTextIn, CString &strTextOut, CString &strMsgOut);
	BOOL FormatterJs(const char *pTextIn, CString &strTextOut);
	BOOL FormatterCss(const char *pTextIn, CString &strTextOut, CString &strMsgOut);
	BOOL FormatterJson(const char *pTextIn, CString &strTextOut, CString &strMsgOut);
	BOOL FormatterSql(const char *pTextIn, CString &strTextOut);

};
