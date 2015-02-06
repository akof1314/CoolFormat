#ifndef GLOBALTIDY_H
#define GLOBALTIDY_H
#include <string>
#include "SynLanguage.h"

struct TidyDeafult {
	const TCHAR *langName;	//用于写注册表、展现用户的名称
	const char *tidyName;	//默认格式化参数
	unsigned int langID;			//语言枚举
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

	bool m_bTidySyn[SYN_XML + 1];

	/** AStyle选项类 LGPL协议 */
	std::string m_TidyCpp;
	std::string m_TidyJava;
	std::string m_TidyCSharp;
	std::string m_TidyObjectiveC;

	/** Tidy选项类 MIT协议 */
	std::string m_TidyHtml;

	/** XML选项类 */
	std::string m_TidyXml;

	/** phpformatter选项类 GPL2协议 */
	std::string m_TidyPhp;

	/** JSMin选项类 GPL */
	std::string m_TidyJs;

	/** CssTidy选项类 */
	std::string m_TidyCss;

	/** JsonCpp选项类 */
	std::string m_TidyJson;

	/** SqlFormatter选项类 */
	std::string m_TidySql;

	/** 默认的语言结构体数组 */
	static TidyDeafult m_TidyNames[MAX_SYN_LANG];
};

extern GlobalTidy g_GlobalTidy;

#endif
