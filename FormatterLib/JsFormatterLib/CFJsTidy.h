#ifndef CFJSTIDY_H
#define CFJSTIDY_H
#include "CFBaseTidy.h"

class CCFJsTidy : public CCFBaseTidy
{
public:
	CCFJsTidy(void);
	~CCFJsTidy(void);

	bool TidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &strErr);

protected:

	void InitTidyDefault();

	void SetTidyProp(const std::string& strParam, int nNumValue, const std::string& strNumValue, const std::string& strTextValue);

};
#endif
