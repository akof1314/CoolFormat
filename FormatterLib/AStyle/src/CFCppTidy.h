#pragma once
#include "CFBaseTidy.h"

class CCFCppTidy : public CCFBaseTidy
{
public:
	CCFCppTidy();
	~CCFCppTidy();
	
	bool TidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &strErr);

protected:

	void InitTidyDefault();

	void SetTidyProp(const std::string& strParam, int nNumValue, const std::string& strNumValue, const std::string& strTextValue);
};
