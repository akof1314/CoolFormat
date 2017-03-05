/* jsparser.h
   2012-3-11
   Version: 0.9.9

Copyright (c) 2012- SUN Junwen

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
#include <stdio.h>
#include <time.h>
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <set>

using namespace std;

#if defined (WIN32)
#define SNPRINTF sprintf_s
#else
#define SNPRINTF snprintf
#endif

template<class T>
bool GetStackTop(const stack<T>& stk, T& ret)
{
	if(stk.size() == 0)
		return false;
	ret = stk.top();
	return true;
}

template<class T>
bool StackTopEq(const stack<T>& stk, T eq)
{
	if(stk.size() == 0)
		return false;
	return (eq == stk.top());
}

#define NOT_TOKEN -1
#define STRING_TYPE 0
#define OPER_TYPE 1
#define REGULAR_TYPE 2
#define COMMENT_TYPE_1 9 // 单行注释
#define COMMENT_TYPE_2 10 // 多行注释

/*
 * if-i, else-e, else if-i,
 * for-f, do-d, while-w,
 * switch-s, case-c, default-c
 * try-r, catch-h
 * {-BLOCK, (-BRACKET
 * 0-empty
 */
#define JS_IF 'i'
#define JS_ELSE 'e'
#define JS_FOR 'f'
#define JS_DO 'd'
#define JS_WHILE 'w'
#define JS_SWITCH 's'
#define JS_CASE 'c'
#define JS_TRY 'r'
#define JS_CATCH 'h'
#define JS_FUNCTION 'n'
#define JS_BLOCK '{'
#define JS_BRACKET '('
#define JS_SQUARE '['
#define JS_ASSIGN '='
#define JS_QUEST_MARK '?'
#define JS_HELPER '\\'
#define JS_STUB ' '
#define JS_EMPTY 0

class JSParser
{
protected:
	struct Token
	{
		string code; // 代码内容
		int type; // Token 类型
		bool inlineComment; // COMMENT_TYPE_2 的 inline 模式
		long line; // 行号
	};

public:
	typedef stack<char> CharStack;
	typedef stack<bool> BoolStack;
	typedef stack<int> IntStack;
	typedef stack<size_t> SizeStack;
	typedef queue<Token> TokenQueue;
	typedef map<string, char> StrCharMap;
	typedef set<string> StrSet;

	explicit JSParser();

	virtual ~JSParser()
	{}

	bool m_debug;
	inline const char *GetDebugOutput()
	{ return m_strDebugOutput.c_str(); }

private:
	Token m_tokenABeforeComment;

protected:
	int m_charA;
	int m_charB;
	Token m_tokenA;
	Token m_tokenB;
	long m_lineCount;
	long m_tokenCount;

	bool inline IsNormalChar(int ch)
	{
		// 一般字符
		return ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') ||
				(ch >= 'A' && ch <= 'Z') || ch == '_' || ch == '$' ||
				ch > 126 || ch < 0);
	}

	bool inline IsNumChar(int ch)
	{
		// 数字和.
		return ((ch >= '0' && ch <= '9') || ch == '.');
	}

	bool inline IsBlankChar(int ch)
	{
		// 空白字符
		return (ch == ' ' || ch == '\t' || ch == '\r');
	}

	bool inline IsSingleOper(int ch)
	{
		// 单字符符号
		return (ch == '.' || ch == '(' || ch == ')' ||
				ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
				ch == ',' || ch == ';' || ch == '~' ||
				ch == '\n');
	}

	bool inline IsQuote(int ch)
	{
		// 引号
		return (ch == '\'' || ch == '\"' || ch == '`');
	}

	bool IsInlineComment(const Token& token);

	bool GetToken(); // 处理过负数, 正则等等的 GetToken 函数

	void inline StartParse()
	{ m_startClock = clock(); }

	void inline EndParse()
	{
		m_endClock = clock();
		m_duration = (double)(m_endClock - m_startClock) / CLOCKS_PER_SEC;
		PrintDebug();
	}

private:
	void Init();

	// Should be implemented in derived class
	virtual int GetChar() = 0; // JUST get next char from input

	bool inline IsComment(); // 要联合判断 charA, charB

	void GetTokenRaw();

	void PrepareRegular(); // 通过词法判断 tokenB 正则
	void PreparePosNeg(); // 通过词法判断 tokenB 正负数
	void PrepareTokenB();

	void PrintDebug();
	virtual void PrintAdditionalDebug(string& strDebugOutput) {}

	string m_strBeforeReg; // 判断正则时，正则前面可以出现的字符

	TokenQueue m_tokenBQueue;

	bool m_bRegular; // tokenB 实际是正则 GetToken 用到的两个成员状态
	int m_iRegBracket; // 正则表达式中出现的 [] 深度

	bool m_bPosNeg; // tokenB 实际是正负数

	bool m_bGetTokenInit; // 是否是第一次执行 GetToken

	clock_t m_startClock;
	clock_t m_endClock;
	double m_duration;
	string m_strDebugOutput;

private:
	// 阻止拷贝
	JSParser(const JSParser&);
	JSParser& operator=(const JSParser&);
};

#endif
