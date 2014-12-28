#pragma once
#include "CFBaseTidy.h"

class CCFSqlTidy : public CCFBaseTidy
{
public:
	CCFSqlTidy(void);
	~CCFSqlTidy(void);

	bool TidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &strErr);

protected:

	void InitTidyDefault();

	void SetTidyProp(const std::string& strParam, int nNumValue, const std::string& strNumValue, const std::string& strTextValue);
};
