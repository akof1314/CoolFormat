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

	BOOL DoFormatter(UINT nLanguage, const CString &strTextIn, CString &strTextOut, CString &strMsgOut, UINT uCodepage);
};
