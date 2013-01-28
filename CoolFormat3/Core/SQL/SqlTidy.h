#pragma once
#include <string>
using namespace std;
#ifdef _DEBUG
#pragma comment(lib, "SqlFormatterLibd.lib")
#else
#pragma comment(lib, "SqlFormatterLib.lib")
#endif // _DEBUG

namespace SqlFormatter{
class SqlTidy
{
public:
	SqlTidy(void);
	~SqlTidy(void);
	bool SqlTidyMain(const char* pSourceIn, const char *pOptions, string &strOut/*, string &strErr*/);
};
}