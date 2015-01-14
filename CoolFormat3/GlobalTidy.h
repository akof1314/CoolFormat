/** 
 * @file GlobalTidy.h
 * @brief 全局格式化选项参数
 * @author 无幻 
 * @date 2012-6-19
 * @details 
 */ 
#pragma once

struct TidyDeafult {
	const TCHAR *langName;	//用于写注册表、展现用户的名称
	const TCHAR *tidyName;	//默认格式化参数
	UINT langID;			//语言枚举
};

class GlobalTidy
{
public:
	GlobalTidy(void);
	~GlobalTidy(void);

	
	/**
	 * 初始化全局格式化参数
	 * @return void 
	 */
	void InitGlobalTidy();

	BOOL m_bTidySyn[SYN_XML + 1];

	/** AStyle选项类 LGPL协议 */
	CString m_TidyCpp;
	CString m_TidyJava;
	CString m_TidyCSharp;
	CString m_TidyObjectiveC;

	/** Tidy选项类 MIT协议 */
	CString m_TidyHtml;
	CString m_TidyHtml_at;
	CString m_TidyHtml_cp;
	CString m_TidyHtml_nbt;
	CString m_TidyHtml_net;
	CString m_TidyHtml_nit;
	CString m_TidyHtml_npt;

	/** XML选项类 */
	CString m_TidyXml;

	/** phpformatter选项类 GPL2协议 */
	CString m_TidyPhp;

	/** JSMin选项类 GPL */
	CString m_TidyJs;

	/** CssTidy选项类 */
	CString m_TidyCss;

	/** JsonCpp选项类 */
	CString m_TidyJson;

	/** SqlFormatter选项类 */
	CString m_TidySql;

	/** 默认的语言结构体数组 */
	static TidyDeafult m_TidyNames[MAX_SYN_LANG];
};

extern GlobalTidy g_GlobalTidy;
