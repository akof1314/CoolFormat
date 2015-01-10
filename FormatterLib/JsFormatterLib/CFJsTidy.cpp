#include "CFJsTidy.h"
#include "jsformatString.h"

CCFJsTidy::CCFJsTidy(void)
{
}

CCFJsTidy::~CCFJsTidy(void)
{
}

struct STTidyOptions
{
	char chIndent;
	int nChPerInd;
	bool bNLBracket;
};

bool CCFJsTidy::TidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &/*strErr*/)
{
	STTidyOptions tidyOptions;
	TidyOptionsSet(&tidyOptions, pOptions);

	try
	{
		JSFormatString jsformat(pSourceIn, &strOut, tidyOptions.chIndent, tidyOptions.nChPerInd, false, tidyOptions.bNLBracket);
		jsformat.Go();
	}
	catch (std::exception ex)
	{
		return false;
	}
	return true;
}

void CCFJsTidy::InitTidyDefault()
{
	STTidyOptions* formatter = (STTidyOptions*)tidy;
	formatter->chIndent = ' ';
	formatter->nChPerInd = 4;
	formatter->bNLBracket = false;
}

void CCFJsTidy::SetTidyProp(const std::string& strParam, int nNumValue, const std::string& /*strNumValue*/, const std::string& /*strTextValue*/)
{
	STTidyOptions* formatter = (STTidyOptions*)tidy;
	if ("ci" == strParam)
	{
		switch (nNumValue)
		{
		case 0:formatter->chIndent = ' '; break;
		case 1:formatter->chIndent = '\t'; break;
		}
	}
	else if ("cn" == strParam)
	{
		formatter->nChPerInd = nNumValue;
	}
	else if ("nb" == strParam)
	{
		formatter->bNLBracket = true;
	}
}
