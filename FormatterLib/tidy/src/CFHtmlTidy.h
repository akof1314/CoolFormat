#pragma once
#include "CFBaseTidy.h"

class CCFHtmlTidy : public CCFBaseTidy
{
public:
	CCFHtmlTidy();
	~CCFHtmlTidy();

	bool TidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &strErr);

protected:

	void InitTidyDefault();

	void SetTidyProp(const std::string& strParam, int nNumValue, const std::string& strNumValue, const std::string& strTextValue);

};
