#pragma once
#include <string>

class CFormatterHelp
{
public:
	CFormatterHelp(void);
	~CFormatterHelp(void);

	bool DoFormatter(unsigned int nLanguage, 
		const std::string &strTextIn, 
		std::string &strTextOut, 
		std::string &strMsgOut);
};
