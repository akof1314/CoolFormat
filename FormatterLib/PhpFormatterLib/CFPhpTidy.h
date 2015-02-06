#ifndef CFPHPTIDY_H
#define CFPHPTIDY_H
#include "CFBaseTidy.h"

class CCFPhpTidy : public CCFBaseTidy
{
public:
	CCFPhpTidy(void);
	~CCFPhpTidy(void);

	bool TidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &strErr);

protected:

	void InitTidyDefault();

	void SetTidyProp(const std::string& strParam, int nNumValue, const std::string& strNumValue, const std::string& strTextValue);

};
#endif
