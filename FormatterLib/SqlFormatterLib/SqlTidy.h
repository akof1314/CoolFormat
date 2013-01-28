#pragma once
#include <string>
using namespace std;

namespace SqlFormatter{
class SqlTidy
{
public:
	SqlTidy(void);
	~SqlTidy(void);
	bool SqlTidyMain(const char* pSourceIn, const char *pOptions, string &strOut/*, string &strErr*/);
};
}