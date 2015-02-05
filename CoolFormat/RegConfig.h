/** 
 * @file RegConfig.h
 * @brief 注册表配置类
 * @author 无幻 
 * @date 2012-6-8
 * @details 主要用作导入导出注册表
 */ 
#pragma once

class CRegConfig
{
public:
	CRegConfig(void);
	~CRegConfig(void);

	BOOL ImportReg(LPCTSTR pszFileName);
	BOOL ExportReg(LPCTSTR pszFileName);

protected:
	BOOL SaveRegToConfig(LPCTSTR pszSection, LPCTSTR pszFileName);
	BOOL RestoreRegFromConfig(LPCTSTR pszSection, LPCTSTR pszFileName);
};
