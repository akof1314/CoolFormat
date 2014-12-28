#include "CFSqlTidy.h"
#include "SQLFormatter2.h"

CCFSqlTidy::CCFSqlTidy(void)
{

}

CCFSqlTidy::~CCFSqlTidy(void)
{

}

bool CCFSqlTidy::TidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &/*strErr*/)
{
	int nLen = strlen(pSourceIn);
	char *strOutput = new char[nLen + 99999];
	char *strInput = new char[nLen + 99999];
	SQLFormatter2 *sqlformatter = NULL;
	try
	{
		sqlformatter = new SQLFormatter2();
		TidyOptionsSet(sqlformatter, pOptions);

		sqlformatter->flattenSql(const_cast<char*>(pSourceIn), strInput);
		sqlformatter->formatSql(strInput, strOutput);
		strOut = strOutput;
		if (strOut.size() > 0)
		{
			if (strOut.at(0) == 10)
			{
				strOut.erase(0, 1);
			}
		}
	}
	catch (...)
	{
	}
	delete strInput;
	delete strOutput;
	if (sqlformatter)
	{
		delete sqlformatter;
	}
	return true;
}

void CCFSqlTidy::InitTidyDefault()
{
	SQLFormatter2* formatter = (SQLFormatter2*)tidy;
	formatter->_endLineOnSubQuery = false;
}

void CCFSqlTidy::SetTidyProp(const std::string& strParam, int nNumValue, const std::string& /*strNumValue*/, const std::string& /*strTextValue*/)
{
	SQLFormatter2* formatter = (SQLFormatter2*)tidy;
	if ("ci" == strParam)
	{
		switch (nNumValue)
		{
		case 0:formatter->_indentationChar = ' '; break;
		case 1:formatter->_indentationChar = '\t'; break;
		}
	}
	else if ("cn" == strParam)
	{
		formatter->_indent = nNumValue;
	}
	else if ("el" == strParam)
	{
		formatter->_endLineOnSubQuery = true;
	}
	else if ("ml" == strParam)
	{
		formatter->_minSubqueryLength = nNumValue;
	}
}
