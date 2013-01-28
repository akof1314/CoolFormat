#include "SqlTidy.h"
#include "SQLFormatter2.h"

SqlFormatter::SqlTidy::SqlTidy( void )
{

}

SqlFormatter::SqlTidy::~SqlTidy( void )
{

}

bool SqlFormatter::SqlTidy::SqlTidyMain( const char* pSourceIn, const char *pOptions, string &strOut/*, string &strErr*/ )
{
	string strOptions = pOptions;
	char chIndent = ' ';
	if (string::npos != strOptions.find("-ci1"))
	{
		chIndent = '\t';
	}
	int nChPerInd = 2;
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
	bool bendLineOnSubQuery = false;
	if (string::npos != strOptions.find("-el"))
	{
		bendLineOnSubQuery = true;
	}
	int nminSubqueryLength = 100;
	nPos = strOptions.find("-ml");
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
		nminSubqueryLength = atoi(strIN.c_str());
	}

	int nLen = strlen(pSourceIn);
	char *strOutput = new char[nLen + 99999];	
	char *strInput = new char[nLen + 99999];
	SQLFormatter2 *sqlformatter = NULL;
	try
	{		
		sqlformatter = new SQLFormatter2(2, nChPerInd, bendLineOnSubQuery, nminSubqueryLength, chIndent);
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