/* JSParser.h
   2012-3-11
   Version: 0.9.5

Copyright (c) 2012 SUN Junwen

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#ifndef _JS_PARSER_H_
#define _JS_PARSER_H_
#include <ctime>
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <set>

using namespace std;

#define STRING_TYPE 0
#define OPER_TYPE 1
#define REGULAR_TYPE 2
#define COMMENT_TYPE_1 9 // 单行注释
#define COMMENT_TYPE_2 10 // 多行注释

class JSParser
{
protected:
	struct TokenAndType
	{
		string token;
		int type;
	};

public:
	typedef stack<char> CharStack;
	typedef stack<bool> BoolStack;
	typedef queue<TokenAndType> TokenQueue;
	typedef map<string, char> StrCharMap;
	typedef set<string> StrSet;

	explicit JSParser();

	virtual ~JSParser()
	{}

protected:
	int m_charA;
	int m_charB;
	int m_tokenAType;
	int m_tokenBType;
	string m_tokenA;
	string m_tokenB;
	int m_tokenCount;

	bool inline IsNormalChar(int ch);
	bool inline IsNumChar(int ch);
	bool inline IsBlankChar(int ch);
	bool inline IsSingleOper(int ch);
	bool inline IsQuote(int ch);

	bool GetToken(); // 处理过负数, 正则等等的 GetToken 函数

private:
	void Init();

	// Should be implemented in derived class
	virtual int GetChar() = 0; // JUST get next char from input

	bool inline IsComment(); // 要联合判断 charA, charB

	void GetTokenRaw();

	void PrepareRegular(); // 通过词法判断 tokenB 正则
	void PreparePosNeg(); // 通过词法判断 tokenB 正负数
	void PrepareTokenB();

	string m_strBeforeReg; // 判断正则时，正则前面可以出现的字符

	bool m_bRegular; // tokenB 实际是正则 GetToken 用到的两个成员状态
	bool m_bPosNeg; // tokenB 实际是正负数
	TokenQueue m_tokenBQueue;

	bool m_bGetTokenInit; // 是否是第一次执行 GetToken

private:
	// 阻止拷贝
	JSParser(const JSParser&);
	JSParser& operator=(const JSParser&);
};

#endif
