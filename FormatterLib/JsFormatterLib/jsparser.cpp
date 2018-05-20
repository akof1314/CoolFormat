/* jsparser.cpp
   2012-3-11
   Version: 0.9.8

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
#include "jsparser.h"
#include <cstring>

using namespace std;

JSParser::JSParser()
{
	Init();
}

void JSParser::Init()
{
	m_debug = false;

	m_lineCount = 1; // 行号从 1 开始
	m_tokenCount = 0;

	m_strBeforeReg = "(,=:[!&|?+{};\n";

	m_bRegular = false;
	m_iRegBracket = 0;

	m_bPosNeg = false;

	m_bGetTokenInit = false;
}

void JSParser::PrintDebug()
{
	if (m_debug)
	{
		m_strDebugOutput = "";
		char buf[1024] = {0};
		SNPRINTF(buf, 1000, "Processed tokens: %ld\n", m_tokenCount);
		m_strDebugOutput.append(buf);
		SNPRINTF(buf, 1000, "Time used: %.3fs\n", m_duration);
		m_strDebugOutput.append(buf);
		SNPRINTF(buf, 1000, "%.3f tokens/second\n", m_tokenCount / m_duration);
		m_strDebugOutput.append(buf);

		PrintAdditionalDebug(m_strDebugOutput);

		printf("%s", m_strDebugOutput.c_str());
	}
}

bool JSParser::IsComment()
{
	// 注释
	return (m_charA == '/' && (m_charB == '/' || m_charB == '*'));
}

bool JSParser::IsInlineComment(const Token& token)
{
	if(token.type != COMMENT_TYPE_2)
		return false;

	return token.inlineComment;
}

void JSParser::GetTokenRaw()
{
	if(!m_bGetTokenInit)
	{
		m_charB = GetChar();
	}

	// normal procedure
	if(!m_bRegular && !m_bPosNeg)
	{
		m_tokenB.code = "";
		m_tokenB.type = STRING_TYPE;
		m_tokenB.line = m_lineCount;
	}
	else if(m_bRegular)
	{
		//m_tokenB.push_back('/');
		m_tokenB.type = REGULAR_TYPE; // 正则
	}
	else
	{
		m_tokenB.type = STRING_TYPE; // 正负数
	}

	bool bQuote = false;
	bool bComment = false;
	bool bRegularFlags = false;
	bool bFirst = true;
	bool bNum = false; // 是不是数字
	bool bLineBegin = false;
	char chQuote = 0; // 记录引号类型 ' 或 "
	char chComment = 0; // 注释类型 / 或 *

	while(1)
	{
		m_charA = m_charB;
		if(m_charA == 0)
		{
			m_bRegular = false; // js content error
			return;
		}

		m_charB = GetChar();
		// \r\n -> \n(next char)
		if(m_charA == '\r' && m_charB == '\n')
		{
			m_charA = '\n';
			m_charB = GetChar();
		}
		// \r -> \n
		if(m_charA == '\r' && m_charB != '\n')
		{
			m_charA = '\n';
		}
	
		if(m_charA == '\n')
			++m_lineCount;

		/*
		 * 参考 m_charB 来处理 m_charA
		 * 输出或不输出 m_charA
		 * 下一次循环时自动会用 m_charB 覆盖 m_charA
		 */

		// 正则需要在 token 级别判断
		if(m_bRegular)
		{
			// 正则状态全部输出，直到 /
			m_tokenB.code.push_back(m_charA);

			if(m_charA == '\\' && 
				(m_charB == '/' || m_charB == '\\' ||
				m_charB == '[' || m_charB == ']')) // 转义字符
			{
				m_tokenB.code.push_back(m_charB);
				m_charB = GetChar();
			}

			if(m_charA == '[' && m_iRegBracket == 0)
			{
				++m_iRegBracket;
			}

			if(m_charA == ']' && m_iRegBracket > 0)
			{
				--m_iRegBracket;
				if(bRegularFlags)
					bRegularFlags = false;
			}

			if(m_charA == '/' && 
				(m_charB != '*' && m_charB != '|' && m_charB != '?')) // 正则可能结束
			{
				if(!bRegularFlags && 
					(IsNormalChar(m_charB) || m_iRegBracket > 0))
				{
					if(m_iRegBracket == 0)
					{
						// 正则的 flags 部分
						// /g /i /ig...
						// 否则 [] 中 / 不需要转移
						bRegularFlags = true;
					}
					continue;
				}
				else
				{
					// 正则结束
					m_bRegular = false;
					return;
				}
			}

			if(bRegularFlags && !IsNormalChar(m_charB))
			{
				// 正则结束
				bRegularFlags = false;
				m_bRegular = false;
				return;
			}

			continue;
		}

		if(bQuote)
		{
			// 引号状态，全部输出，直到引号结束
			m_tokenB.code.push_back(m_charA);

			if(m_charA == '\\' && (m_charB == chQuote || m_charB == '\\')) // 转义字符
			{
				m_tokenB.code.push_back(m_charB);
				m_charB = GetChar();
			}

			if(m_charA == chQuote) // 引号结束
				return;

			continue;
		}

		if(bComment)
		{
			// 注释状态，全部输出
			if(m_tokenB.type == COMMENT_TYPE_2)
			{
				// /*...*/每行前面的\t, ' '都要删掉
				if(bLineBegin && (m_charA == '\t' || m_charA == ' '))
					continue;
				else if(bLineBegin && m_charA == '*')
					m_tokenB.code.push_back(' ');

				bLineBegin = false;

				if(m_charA == '\n')
					bLineBegin = true;
			}
			m_tokenB.code.push_back(m_charA);

			if(chComment == '*')
			{
				// 直到 */
				m_tokenB.type = COMMENT_TYPE_2;
				m_tokenB.inlineComment = false;
				if(m_charA == '*' && m_charB == '/')
				{
					m_tokenB.code.push_back(m_charB);
					m_charB = GetChar();

					m_tokenABeforeComment = m_tokenA;

					return;
				}
			}
			else
			{
				// 直到换行
				m_tokenB.type = COMMENT_TYPE_1;
				m_tokenB.inlineComment = false;
				if(m_charA == '\n')
					return;
			}

			continue;
		}

		if(IsNormalChar(m_charA))
		{
			m_tokenB.type = STRING_TYPE;
			m_tokenB.code.push_back(m_charA);

			// 解决类似 82e-2, 442e+6, 555E-6 的问题
			// 因为这是立即数，所以只能符合以下的表达形式
			bool bNumOld = bNum;
			if(bFirst || bNumOld) // 只有之前是数字才改变状态
			{
				bNum = IsNumChar(m_charA);
				bFirst = false;
			}
			if(bNumOld && !bNum && (m_charA == 'e' || m_charA == 'E') &&
				(m_charB == '-' || m_charB == '+' || IsNumChar(m_charB)))
			{
				bNum = true;
				if(m_charB == '-' || m_charB == '+')
				{
					m_tokenB.code.push_back(m_charB);
					m_charB = GetChar();
				}
			}

			if(!IsNormalChar(m_charB)) // loop until m_charB is not normal char
			{
				m_bPosNeg = false;
				return;
			}
		}
		else
		{
			if(IsBlankChar(m_charA))
				continue; // 忽略空白字符

			if(IsQuote(m_charA))
			{
				// 引号
				bQuote = true;
				chQuote = m_charA;

				m_tokenB.type = STRING_TYPE;
				m_tokenB.code.push_back(m_charA);
				continue;
			}

			if(IsComment())
			{
				// 注释
				bComment = true;
				chComment = m_charB;

				//m_tokenBType = COMMENT_TYPE;
				m_tokenB.code.push_back(m_charA);
				continue;
			}

			if( IsSingleOper(m_charA) ||
				IsNormalChar(m_charB) || IsBlankChar(m_charB) || IsQuote(m_charB))
			{
				m_tokenB.type = OPER_TYPE;
				m_tokenB.code = m_charA; // 单字符符号
				return;
			}

			// 多字符符号
			if((m_charB == '=' || m_charB == m_charA) || 
				((m_charA == '-' || m_charA == '=') && m_charB == '>'))
			{
				// 的确是多字符符号
				m_tokenB.type = OPER_TYPE;
				m_tokenB.code.push_back(m_charA);
				m_tokenB.code.push_back(m_charB);
				m_charB = GetChar();
				if((m_tokenB.code == "==" || m_tokenB.code == "!=" ||
					m_tokenB.code == "<<" || m_tokenB.code == ">>") && m_charB == '=')
				{
					// 三字符 ===, !==, <<=, >>=
					m_tokenB.code.push_back(m_charB);
					m_charB = GetChar();
				}
				else if(m_tokenB.code == ">>" && m_charB == '>')
				{
					// >>>, >>>=
					m_tokenB.code.push_back(m_charB);
					m_charB = GetChar();
					if(m_charB == '=') // >>>=
					{
						m_tokenB.code.push_back(m_charB);
						m_charB = GetChar();
					}
				}
				return;
			}
			else
			{
				// 还是单字符的
				m_tokenB.type = OPER_TYPE;
				m_tokenB.code = m_charA; // 单字符符号
				return;
			}

			// What? How could we come here?
			m_charA = 0;
			return;
		}
	}
}

bool JSParser::GetToken()
{
	if(!m_bGetTokenInit)
	{
		// 第一次多调用一次 GetTokenRaw
		GetTokenRaw();
		m_bGetTokenInit = true;
	}

	PrepareRegular(); // 判断正则
	PreparePosNeg(); // 判断正负数

	++m_tokenCount;
	m_tokenPreA = m_tokenA;
	m_tokenA = m_tokenB;

	if(m_tokenBQueue.size() == 0)
	{
		GetTokenRaw();
		PrepareTokenB(); // 看看是不是要跳过换行
	}
	else
	{
		// 有排队的换行
		m_tokenB = m_tokenBQueue.front();
		m_tokenBQueue.pop();
	}

	return (m_charA != 0 || m_tokenA.code != "");
}

void JSParser::PrepareRegular()
{
	/*
	 * 先处理一下正则
	 * m_tokenB[0] == /，且 m_tokenB 不是注释
	 * m_tokenA 不是 STRING (除了 m_tokenA == return)
	 * 而且 m_tokenA 的最后一个字符是下面这些
	*/
	//size_t last = m_tokenA.size() > 0 ? m_tokenA.size() - 1 : 0;
	char tokenALast = m_tokenA.code.size() > 0 ? m_tokenA.code[m_tokenA.code.size() - 1] : 0;
	char tokenBFirst = m_tokenB.code[0];
	if(tokenBFirst == '/' && m_tokenB.type != COMMENT_TYPE_1 &&
		m_tokenB.type != COMMENT_TYPE_2 &&
		((m_tokenA.type != STRING_TYPE && m_strBeforeReg.find(tokenALast) != string::npos) ||
			m_tokenA.code == "return"))
	{
		m_bRegular = true;
		GetTokenRaw(); // 把正则内容加到 m_tokenB
	}
}

void JSParser::PreparePosNeg()
{
	/*
	 * 如果 m_tokenB 是 -,+ 号
	 * 而且 m_tokenA 不是字符串型也不是正则表达式
	 * 而且 m_tokenA 不是 ++, --, ], )
	 * 而且 m_charB 是一个 NormalChar
	 * 那么 m_tokenB 实际上是一个正负数
	 */
	Token tokenRealPre = m_tokenA;
	if(m_tokenA.type == COMMENT_TYPE_2)
		tokenRealPre = m_tokenABeforeComment;

	if(m_tokenB.type == OPER_TYPE && (m_tokenB.code == "-" || m_tokenB.code == "+") &&
		(tokenRealPre.type != STRING_TYPE || 
		tokenRealPre.code == "return" || tokenRealPre.code == "case" ||
		tokenRealPre.code == "delete" || tokenRealPre.code == "throw") && 
		tokenRealPre.type != REGULAR_TYPE &&
		tokenRealPre.code != "++" && tokenRealPre.code != "--" &&
		tokenRealPre.code != "]" && tokenRealPre.code != ")" &&
		IsNormalChar(m_charB))
	{
		// m_tokenB 实际上是正负数
		m_bPosNeg = true;
		GetTokenRaw();
	}
}

void JSParser::PrepareTokenB()
{
	//char stackTop = m_blockStack.top();

	/*
	 * 跳过 else, while, catch, ',', ';', ')', { 之前的换行
	 * 如果最后读到的不是上面那几个，再把去掉的换行补上
	 */
	int c = 0;
	while(m_tokenB.code == "\n" || m_tokenB.code == "\r\n")
	{
		++c;
		GetTokenRaw();
	}

	if(c == 0 && 
		m_tokenA.type != COMMENT_TYPE_1 &&
		m_tokenB.type == COMMENT_TYPE_2 && 
		m_tokenB.code.find("\r") == string::npos &&
		m_tokenB.code.find("\n") == string::npos)
	{
		// COMMENT_TYPE_2 之前没有换行, 自己也没有换行
		m_tokenB.inlineComment = true;
	}

	if(m_tokenB.code != "else" && m_tokenB.code != "while" && m_tokenB.code != "catch" &&
		m_tokenB.code != "," && m_tokenB.code != ";" && m_tokenB.code != ")")
	{
		// 将去掉的换行压入队列，先处理
		if(m_tokenA.code == "{" && m_tokenB.code == "}")
			return; // 空 {}

		Token temp;
		c = c > 2 ? 2 : c;
		for(; c > 0; --c)
		{
			temp.code = string("\n");
			temp.type = OPER_TYPE;
			m_tokenBQueue.push(temp);
		}
		temp = m_tokenB;
		m_tokenBQueue.push(temp);
		temp = m_tokenBQueue.front();
		m_tokenBQueue.pop();
		m_tokenB = temp;
	}
}
