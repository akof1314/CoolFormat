/* realjsformatter.h
   2010-12-16

Copyright (c) 2010-2013 SUN Junwen

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
#ifndef _REAL_JSFORMATTER_H_
#define _REAL_JSFORMATTER_H_
#include <string>
#include <vector>
#include <map>
#include <set>

#include "jsparser.h"
#include "jsformatter.h"

using namespace std;

class RealJSFormatter: public JSParser
{
public:
	typedef map<string, char> StrCharMap;
	typedef set<string> StrSet;
	typedef vector<int> IntVector;

	RealJSFormatter(const FormatterOption& option);

	virtual ~RealJSFormatter()
	{}

	static string Trim(const string& str);
	static string TrimSpace(const string& str);
	static string TrimRightSpace(const string& str);
	void StringReplace(string& strBase, const string& strSrc, const string& strDes);

	inline void SetInitIndent(const string& initIndent)
	{ m_initIndent = initIndent; }

	virtual void Go();

	int GetFormattedLine(int originalLine);

private:
	void Init();

	virtual void PutChar(int ch) = 0;

	virtual void PrintAdditionalDebug(string& strDebugOutput);

	void PopMultiBlock(char previousStackTop);
	void ProcessOper(bool bHaveNewLine, char tokenAFirst, char tokenBFirst);
	void ProcessString(bool bHaveNewLine, char tokenAFirst, char tokenBFirst);

	void ProcessQuote(Token& token);

	void PutToken(const Token& token,
		const string& leftStyle = string(""),
		const string& rightStyle = string("")); // Put a token out with style
	void PutString(const Token& token);
	void PutString(const string& str);
	void PutLineBuffer();

	int m_nLineIndents;
	int m_bLineTemplate;
	string m_lineBuffer;

	int m_nFormattedLineCount;
	IntVector m_lineFormattedVec;
	IntVector m_lineWaitVec;

	StrSet m_specKeywordSet; // 后面要跟着括号的关键字集合
	StrCharMap m_blockMap;
	CharStack m_blockStack;
	int m_nIndents; // 缩进数量，不用计算 blockStack，效果不好

	// 使用栈是为了解决在判断条件中出现循环的问题
	BoolStack m_brcNeedStack; // if 之类的后面的括号

	bool m_bNewLine; // 准备换行的标志
	bool m_bBlockStmt; // block 真正开始了
	bool m_bAssign;
	bool m_bEmptyBracket; // 空 {}

	bool m_bCommentPut; // 刚刚输出了注释
	bool m_bTemplatePut; // Template String

	int m_nQuestOperCount;
	SizeStack m_QuestOperStackCount;

	string m_initIndent; // 起始缩进

	// 以下为配置项
	FormatterOption m_struOption;

private:
	// 阻止拷贝
	RealJSFormatter(const RealJSFormatter&);
	RealJSFormatter& operator=(const RealJSFormatter&);
};

#endif
