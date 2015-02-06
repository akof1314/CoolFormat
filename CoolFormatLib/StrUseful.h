#ifndef STRUSEFUL_H
#define STRUSEFUL_H

#include <string>
#ifdef _MSC_VER
#include <codecvt>
#include "Windows.h"
#endif

inline std::wstring s2ws(const std::string& str)
{
#ifdef _MSC_VER
	try
	{
		typedef std::codecvt_utf8<wchar_t> convert_typeX;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.from_bytes(str);
	}
	catch (std::exception ex)
	{
		UINT codePage = CP_ACP;
		size_t wstrLen = MultiByteToWideChar(codePage, 0, str.c_str(), -1, NULL, 0);
		std::wstring wstrTo;
		wchar_t *wszTo = new wchar_t[wstrLen + 1];
		wszTo[wstrLen] = L'\0';
		MultiByteToWideChar(codePage, 0, str.c_str(), -1, wszTo, (int)wstrLen);
		wstrTo = wszTo;
		delete[] wszTo;
		return wstrTo;
	}
#else
	setlocale(LC_ALL, "zh_CN.UTF-8");
	size_t num_chars = mbstowcs(NULL, str.c_str(), 0);
	wchar_t* wct_buf = new wchar_t[num_chars + 1];
	mbstowcs(wct_buf, str.c_str(), num_chars);
	std::wstring wstr(wct_buf, num_chars);
	delete[] wct_buf;
	setlocale(LC_ALL, "C");

	return wstr;
#endif
}

inline std::string ws2s(const std::wstring& wstr)
{
#ifdef _MSC_VER
	try
	{
		typedef std::codecvt_utf8<wchar_t> convert_typeX;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(wstr);
	}
	catch (std::exception ex)
	{
		UINT codePage = CP_ACP;
		size_t strLen = WideCharToMultiByte(codePage, 0, wstr.c_str(), (int)wstr.length(), NULL, 0, NULL, NULL);
		std::string strTo;
		char *szTo = new char[strLen + 1];
		szTo[strLen] = '\0';
		WideCharToMultiByte(codePage, 0, wstr.c_str(), -1, szTo, (int)strLen, NULL, NULL);
		strTo = szTo;
		delete[] szTo;
		return strTo;
	}
#else
	setlocale(LC_ALL, "zh_CN.UTF-8");
	size_t num_chars = wcstombs(NULL, wstr.c_str(), 0);
	char* char_buf = new char[num_chars + 1];
	wcstombs(char_buf, wstr.c_str(), num_chars);
	std::string str(char_buf);
	delete[] char_buf;
	setlocale(LC_ALL, "C");

	return str;
#endif
}

inline std::string strreplace_all(std::string str, const std::string& from, const std::string& to)
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); 
	}
	return str;
}

inline std::string strtrim_right(std::string str)
{
	return str.erase(str.find_last_not_of(" \n\r\t") + 1);;
}
#endif
