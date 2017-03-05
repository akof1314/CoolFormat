#ifndef ASTYLE_MAIN_H
#define ASTYLE_MAIN_H

#include <string>
using namespace std;

#ifdef ASTYLE_LIB
bool VerilogTidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &strErr);
#endif	// ASTYLE_LIB

#endif // closes ASTYLE_MAIN_H
