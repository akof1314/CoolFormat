#ifndef CFJSTIDY_H
#define CFJSTIDY_H
#include "CFBaseTidy.h"

class CCFVerilogTidy : public CCFBaseTidy
{
public:
    CCFVerilogTidy(void);
    ~CCFVerilogTidy(void);

	bool TidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &strErr);

protected:

	void InitTidyDefault();

	void SetTidyProp(const std::string& strParam, int nNumValue, const std::string& strNumValue, const std::string& strTextValue);

};
#endif
