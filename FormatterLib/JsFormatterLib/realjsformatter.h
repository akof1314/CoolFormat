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
#include <map>
#include <set>

#include "jsparser.h"

using namespace std;

class RealJSFormatter: public JSParser
{
public:
	typedef map<string, char> StrCharMap;
	typedef set<string> StrSet;

	/*
	 * CR_READ
	 *   READ_CR 读取 \r
	 *   SKIP_READ_CR 读取时跳过 \r
	 */
	enum CR_READ { SKIP_READ_CR, READ_CR };
	/*
	 * CR_PUT
	 *   PUT_CR 换行使用 \r\n
	 *   NOT_PUT_CR 换行使用 \n
	 */
	enum CR_PUT { NOT_PUT_CR, PUT_CR };
	/*
	 * BRAC_NEWLINE
	 *   NEWLINE_BRAC 括号前换行
	 *   NO_NEWLINE_BRAC 括号前不换行
	 */
	enum BRAC_NEWLINE { NO_NEWLINE_BRAC, NEWLINE_BRAC };
	/*
	 * INDENT_IN_EMPTYLINE
	 *   INDENT_IN_EMPTYLINE 空行输出缩进字符
	 *   NO_INDENT_IN_EMPTYLINE 空行不输出缩进字符
	 */
	enum EMPTYLINE_INDENT { NO_INDENT_IN_EMPTYLINE, INDENT_IN_EMPTYLINE };

	struct FormatterOption 
	{
		char chIndent;
		int nChPerInd;
		CR_READ eCRRead;
		CR_PUT eCRPut;
		BRAC_NEWLINE eBracNL;
		EMPTYLINE_INDENT eEmpytIndent;

		FormatterOption():
			chIndent('\t'),
			nChPerInd(1),
			eCRRead(SKIP_READ_CR),
			eCRPut(NOT_PUT_CR),
			eBracNL(NO_NEWLINE_BRAC),
			eEmpytIndent(NO_INDENT_IN_EMPTYLINE)
		{}

		FormatterOption(char op_chIndent,
						int op_nChPerInd,
						CR_READ op_eCRRead,
						CR_PUT op_eCRPut,
						BRAC_NEWLINE op_eBracNL,
						EMPTYLINE_INDENT op_eEmpytIndent):
			chIndent(op_chIndent),
			nChPerInd(op_nChPerInd),
			eCRRead(op_eCRRead),
			eCRPut(op_eCRPut),
			eBracNL(op_eBracNL),
			eEmpytIndent(op_eEmpytIndent)
		{}
	};

	RealJSFormatter(FormatterOption option);

	virtual ~RealJSFormatter()
	{}

	inline void SetInitIndent(const string& initIndent)
	{ m_initIndent = initIndent; }

	void Go();

	static string Trim(const string& str);
	static string TrimSpace(const string& str);
	static string TrimRightSpace(const string& str);
	void StringReplace(string& strBase, const string& strSrc, const string& strDes);

private:
	void Init();

	virtual void PutChar(int ch) = 0;

	void PopMultiBlock(char previousStackTop);
	void ProcessOper(bool bHaveNewLine, char tokenAFirst, char tokenBFirst);
	void ProcessString(bool bHaveNewLine, char tokenAFirst, char tokenBFirst);

	void PutToken(const string& token,
		const string& leftStyle = string(""),
		const string& rightStyle = string("")); // Put a token out with style
	void PutString(const string& str);
	void PutLineBuffer();

	int m_nLineIndents;
	string m_lineBuffer;

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

	string m_initIndent; // 起始缩进

	// 以下为配置项
	FormatterOption m_struOption;

private:
	// 阻止拷贝
	RealJSFormatter(const RealJSFormatter&);
	RealJSFormatter& operator=(const RealJSFormatter&);
};

#endif
