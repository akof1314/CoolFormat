#include "JsTidy.h"
#include "jsformatString.h"

namespace JsFormatter{
JsTidy::JsTidy(void)
{
}

JsTidy::~JsTidy(void)
{
}

bool JsFormatter::JsTidy::JsTidyMain( const char* pSourceIn, const char *pOptions, string &strOut/*, string &strErr*/ )
{
	string strOptions = pOptions;
	char chIndent = ' ';
	if (string::npos != strOptions.find("-ci1"))
	{
		chIndent = '\t';
	}
	int nChPerInd = 4;
	string::size_type nPos = strOptions.find("-cn");
	if (string::npos != nPos)
	{
		string strIN = "";
		for (string::size_type i = nPos + 3; i < strOptions.size(); ++i)
		{
			if (!isdigit(strOptions[i]))
			{
				break;
			}
			strIN.append(1, strOptions[i]);
		}
		nChPerInd = atoi(strIN.c_str());
	}
	bool bNLBracket = false;
	if (string::npos != strOptions.find("-nb"))
	{
		bNLBracket = true;
	}
	try
	{
		JSFormatString jsformat(pSourceIn, &strOut, chIndent, nChPerInd, true, bNLBracket);
		jsformat.Go();
	}
	catch (std::exception ex)
	{
		return false;
	}
	return true;
}
}