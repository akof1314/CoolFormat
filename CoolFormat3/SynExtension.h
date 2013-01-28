/** 
 * @file SynExtension.h
 * @brief 语言扩展名
 * @author 无幻 
 * @date 2012-5-20
 * @details 
 */ 
#pragma once

#include "SynLanguage.h"

struct LanguageName {
	const TCHAR *langName;	//用于写注册表、展现用户的名称
	const TCHAR *extName;	//默认后缀名
	UINT langID;			//语言枚举
};

class CSynExtension
{
public:
	CSynExtension(void);
	~CSynExtension(void);	
	
	/**
	 * 初始化扩展名，从注册表读取
	 * @return void 
	 */
	void InitLanguageExt();
	
	/**
	 * 根据扩展名返回语言
	 * @param CString strExt 扩展名
	 * @return UINT 语言编号
	 */
	UINT GetLanguageByExt(CString strExt);
	
	/**
	 * 根据语言返回语言标识名
	 * @param UINT nLanguage 语言编号
	 * @return LPCTSTR 语言标识名
	 */
	LPCTSTR GetLanguageString(UINT nLanguage);
	
	/**
	 * 根据语言获取语言的第一个扩展名，用于保存时使用
	 * @param UINT nLanguage 语言编号
	 * @param CString & strFilter 语言扩展名
	 * @return void 
	 */
	void GetLanguageOneFilter(UINT nLanguage, CString &strFilter);
	
	/**
	 * 根据语言获取语言的扩展名
	 * @param UINT nLanguage 语言编号
	 * @param CString & strFilter 语言扩展名
	 * @return void 
	 */
	void GetLanguageFilter(UINT nLanguage, CString &strFilter);
	
	/**
	 * 设置语言的扩展名
	 * @param UINT nLanguage 语言编号
	 * @param const CString & strFilter 语言扩展名 
	 * @return void 
	 */
	void SetLanguageFilter(UINT nLanguage, CString &strFilter);

	/**
	 * 获取所有语言的扩展名，组成打开/保存对话框格式
	 * @param CString & strFilter 所有语言扩展名
	 * @return void 
	 */
	void GetAllLanguageFilter(CString &strFilter);
	
	/**
	 * 判断后缀名是否是支持
	 * @param LPCTSTR strExt 后缀名
	 * @return bool 支持返回真
	 */
	bool IsDocSupport(LPCTSTR strExt);

	/** 默认的语言结构体数组 */
	static LanguageName m_LangNames[MAX_SYN_LANG];

private:
	/** 语言扩展名表 */
	CMap<int, int, CString, CString&> m_mapLangExt;	
};
