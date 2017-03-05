#include "CFJsTidy.h"
#include <cstring>
#include "jsformatString.h"
#include "jsminCharArray.h"
#include "jsformatter.h"

CCFJsTidy::CCFJsTidy(void)
{
}

CCFJsTidy::~CCFJsTidy(void)
{
}

struct STTidyOptions
{
	bool bFormatter;
	bool bKeepTopComt;
	FormatterOption formatterOptions;
};

bool CCFJsTidy::TidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &/*strErr*/)
{
	STTidyOptions tidyOptions;
	TidyOptionsSet(&tidyOptions, pOptions);

	try
	{
		if (tidyOptions.bFormatter)
		{
			JSFormatString jsformat(pSourceIn, &strOut, tidyOptions.formatterOptions);
			jsformat.Go();
		} 
		else
		{
			size_t jsMinLen = strlen(pSourceIn) + 10;
			unsigned char *pJSMin = new unsigned char[jsMinLen];
			for (size_t i = 0; i < jsMinLen; ++i)
				pJSMin[i] = '\0';

			JSMinCharArray jsmin((const unsigned char *)pSourceIn, pJSMin, false, tidyOptions.bKeepTopComt);
			jsmin.go();

			strOut = (char *)pJSMin;
			delete[] pJSMin;

			strOut.erase(0, strOut.find_first_not_of(" \n\r\t"));
		}
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
	formatter->bFormatter = true;
	formatter->bKeepTopComt = false;
	formatter->formatterOptions.chIndent = ' ';
	formatter->formatterOptions.nChPerInd = 4;
	formatter->formatterOptions.eBracNL = NO_NEWLINE_BRAC;
	formatter->formatterOptions.eEmpytIndent = NO_INDENT_IN_EMPTYLINE;
}

void CCFJsTidy::SetTidyProp(const std::string& strParam, int nNumValue, const std::string& /*strNumValue*/, const std::string& /*strTextValue*/)
{
	STTidyOptions* formatter = (STTidyOptions*)tidy;
	if ("ci" == strParam)
	{
		switch (nNumValue)
		{
		case 0:formatter->formatterOptions.chIndent = ' '; break;
		case 1:formatter->formatterOptions.chIndent = '\t'; break;
		}
	}
	else if ("cn" == strParam)
	{
		formatter->formatterOptions.nChPerInd = nNumValue;
	}
	else if ("nb" == strParam)
	{
		formatter->formatterOptions.eBracNL = NEWLINE_BRAC;
	}
	else if ("ei" == strParam)
	{
		formatter->formatterOptions.eEmpytIndent = INDENT_IN_EMPTYLINE;
	}
	else if ("mi" == strParam)
	{
		formatter->bFormatter = false;
	}
	else if ("kc" == strParam)
	{
		formatter->bKeepTopComt = true;
	}
}
