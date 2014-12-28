#include "CFJsonTidy.h"
#include "json.h"
using namespace Json;

CCFJsonTidy::CCFJsonTidy()
{
}

CCFJsonTidy::~CCFJsonTidy()
{
}

struct STTidyOptions
{
	int nChPerInd;
};

bool CCFJsonTidy::TidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &strErr)
{
	STTidyOptions tidyOptions;
	TidyOptionsSet(&tidyOptions, pOptions);

	Reader jReader;
	Value jValue;

	bool parsingSuccessful = jReader.parse(pSourceIn, jValue);
	if (!parsingSuccessful)
	{
		strErr = jReader.getFormattedErrorMessages();
		return false;
	}

	strOut = jValue.toMyStyledString(tidyOptions.nChPerInd);
	return true;
}

void CCFJsonTidy::InitTidyDefault()
{
	STTidyOptions* formatter = (STTidyOptions*)tidy;
	formatter->nChPerInd = 3;
}

void CCFJsonTidy::SetTidyProp(const std::string& strParam, int nNumValue, const std::string& /*strNumValue*/, const std::string& /*strTextValue*/)
{
	STTidyOptions* formatter = (STTidyOptions*)tidy;
	if ("cn" == strParam)
	{
		formatter->nChPerInd = nNumValue;
	}
}
