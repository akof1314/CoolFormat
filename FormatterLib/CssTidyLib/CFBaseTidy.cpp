#include "CFBaseTidy.h"
#include <algorithm>
using namespace std;

CCFBaseTidy::CCFBaseTidy()
{
}

CCFBaseTidy::~CCFBaseTidy()
{
}

bool CCFBaseTidy::TidyMain(const char* /*pSourceIn*/, const char* /*pOptions*/, std::string &/*strOut*/, std::string &/*strErr*/)
{
	return false;
}

void CCFBaseTidy::TidyOptionsSet(void* pTidy, const char* pOptions)
{
	tidy = pTidy;
	InitTidyDefault();
	SetTidyFromOptions(pOptions);
}

void CCFBaseTidy::InitTidyDefault()
{
}

void CCFBaseTidy::SetTidyFromOptions(const char* pOptions)
{
	if (NULL == pOptions)
	{
		return;
	}

	int lenTidy = strlen(pOptions);
	if (lenTidy <= 0 || pOptions[0] != '-')
	{
		return;
	}

	int nOption = -1;
	for (int i = 0; i < lenTidy; ++i)
	{
		if (pOptions[i] == '-')
		{
			if (-1 != nOption)
			{
				SetTidyOption(pOptions, nOption, i - nOption);
			}
			nOption = i;
		}
	}
	SetTidyOption(pOptions, nOption, lenTidy - nOption);
}

void CCFBaseTidy::SetTidyOption(const char* pOption, int nPos, int nSize)
{
	if (pOption[nPos] != '-' || nSize < 2)
	{
		return;
	}

	#define STR_SHORT_TEXT_FALG "#"

	string strParam;
	string strNumValue;
	string strBstrValue;

	string strTextParam(pOption + nPos + 1, nSize - 1);
	string::size_type nPosFlag = strTextParam.find(STR_SHORT_TEXT_FALG);
	if (nPosFlag != string::npos)
	{
		strBstrValue = strTextParam.substr(nPosFlag + 1);
		strParam = strTextParam.substr(0, nPosFlag);
	}
	else
	{
		auto it = std::find_if(strTextParam.begin(), strTextParam.end(), isdigit);
		if (it != strTextParam.end())
		{
			strParam.assign(strTextParam.begin(), it);
			strNumValue.assign(it, strTextParam.end());
		}
		else
		{
			strParam.assign(strTextParam);
		}
	}

	int nNumValue = strNumValue.empty() ? 0 : std::stoi(strNumValue);
	SetTidyProp(strParam, nNumValue, strNumValue, strBstrValue);
}

void CCFBaseTidy::SetTidyProp(const std::string& /*strParam*/, int /*nNumValue*/, const std::string& /*strNumValue*/, const std::string& /*strTextValue*/)
{
}
