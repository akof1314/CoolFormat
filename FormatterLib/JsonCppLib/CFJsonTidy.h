#ifndef CFJSONTIDY_H
#define CFJSONTIDY_H
#include "CFBaseTidy.h"

class CCFJsonTidy : public CCFBaseTidy
{
public:
	CCFJsonTidy();
	~CCFJsonTidy();

	bool TidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &strErr);

protected:

	void InitTidyDefault();

	void SetTidyProp(const std::string& strParam, int nNumValue, const std::string& strNumValue, const std::string& strTextValue);

};
#endif
