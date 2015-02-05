#pragma once
#include <string>

class CCFBaseTidy
{
public:
	CCFBaseTidy();
	virtual ~CCFBaseTidy();

	/**
	* 格式化
	* @param const char * pSourceIn
	* @param const char * pOptions
	* @param string & strOut
	* @param string & strErr
	* @return bool
	*/
	virtual bool TidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &strErr);

protected:

	/**
	* 设置格式化参数
	* @param void * pTidy 格式化指针
	* @param const char * pOptions 参数缓存区
	*/
	void TidyOptionsSet(void* pTidy, const char* pOptions);

	/**
	* 初始化默认的格式化参数
	*/
	virtual void InitTidyDefault();

	/**
	* 设置格式化参数
	* @param const char * pOptions 参数缓存区
	*/
	void SetTidyFromOptions(const char* pOptions);

	/**
	* 设置每一项的参数
	* @param const char * pOption 参数缓存区
	* @param int nPos 起始位置
	* @param int nSize 大小
	*/
	void SetTidyOption(const char* pOption, int nPos, int nSize);

	/**
	* 设置具体的属性
	* @param const std::string & strParam 参数缩写词
	* @param int nNumValue 数值
	* @param const std::string & strNumValue 数值
	* @param const std::string & strTextValue 文本值
	*/
	virtual void SetTidyProp(const std::string& strParam, int nNumValue, const std::string& strNumValue, const std::string& strTextValue);

	/**
	* 具体的格式化类指针
	*/
	void* tidy;
};

