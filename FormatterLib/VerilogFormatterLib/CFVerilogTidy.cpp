#include "CFVerilogTidy.h"
#include <cstring>
#include "astyle_main.h"

CCFVerilogTidy::CCFVerilogTidy(void)
{
}

CCFVerilogTidy::~CCFVerilogTidy(void)
{
}


bool CCFVerilogTidy::TidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &strErr)
{
    return VerilogTidyMain(pSourceIn, pOptions, strOut, strErr);
}

void CCFVerilogTidy::InitTidyDefault()
{
}

void CCFVerilogTidy::SetTidyProp(const std::string& /*strParam*/, int /*nNumValue*/, const std::string& /*strNumValue*/, const std::string& /*strTextValue*/)
{
	
}
