// $Id: astyle.h, v 1.4 2004/02/06 08:37:56 devsolar Exp $
// --------------------------------------------------------------------------
//
// Copyright (c) 1998, 1999, 2000, 2001, 2002 Tal Davidson. All rights reserved.
//
// compiler_defines.h
// by Tal Davidson (davidsont@bigfoot.com)
//
// This file is a part of "Artistic Style" - an indentater and reformatter
// of C, C++, C# and Java source files.
//
// --------------------------------------------------------------------------
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// --------------------------------------------------------------------------

#ifndef ASTYLE_H
#define ASTYLE_H

#include "compiler_defines.h"

#include <string>
#include <vector>

/* The enums below ave been moved up from inside the namespace astyle, since they
   for some strange reason are not recognized by 'vectors' in Microsoft Visual C++ 5
   when they are part of a namespace!!! There was no such problem with GNU's g++ compiler.
*/
enum BracketMode   { NONE_MODE, ATTACH_MODE, BREAK_MODE};
enum BracketType   { NULL_TYPE = 0,
                     COMMAND_TYPE = 2,

                     SINGLE_LINE_TYPE = 8};

void error(const char *why, const char* what);

#ifdef USES_NAMESPACE
using namespace std;

namespace istyle
{
#endif

class ASStreamIterator
{
    public:
        ASStreamIterator(std::istream *in);
        virtual ~ASStreamIterator();
        bool hasMoreLines() const;

        // Read the next line from the input stream. Returns the line read,
        // stripped of '\r' if any.
        std::string nextLine();

    private:
        std::istream * inStream;
        int linecount;
};

class ASResource
{
    public:
        static const string AS_IF, AS_ELSE;
        static const string AS_WHILE;
        static const string AS_FOR;
        static const string AS_SWITCH, AS_DEFAULT;

        static const string AS_OPEN_BRACKET, AS_CLOSE_BRACKET;
        static const string AS_OPEN_LINE_COMMENT, AS_OPEN_COMMENT, AS_CLOSE_COMMENT;
        //  process

        static const string PRO_CELLDEFINE, PRO_DEFAULT_NETTYPE, PRO_DEFINE, PRO_ELSE;

        static const string PRO_ENDCELLDEFINE, PRO_ENDIF, PRO_IFDEF, PRO_INCLUDE;

        static const string PRO_NOUNCONNECTED_DRIVE, PRO_RESETALL, PRO_TIMESCALE;

        static const string PRO_UNCONNECTED_DRIVE, PRO_UNDEF;

        static const string AS_ASSIGN;
        static const string AS_LS_ASSIGN, AS_EQUAL_EQUAL, AS_NOT_EQUAL_EQUAL;
        static const string AS_BITNOT_AND, AS_BITNOT_OR, AS_BITNOT_XNOR, AS_NOT_XNOR;

        static const string AS_EQUAL, AS_NOT_EQUAL, AS_GR_EQUAL, AS_GR_GR;
        static const string AS_LS_EQUAL, AS_LS_LS, AS_AND, AS_OR;
        static const string AS_PAREN_PAREN, AS_BLPAREN_BLPAREN;
        static const string AS_PLUS, AS_MINUS, AS_MULT, AS_EXP, AS_DIV, AS_MOD, AS_GR, AS_LS;
        static const string AS_NOT, AS_BIT_XOR, AS_BIT_OR, AS_BIT_AND, AS_BIT_NOT;
        static const string AS_QUESTION, AS_COLON, AS_SEMICOLON, AS_COMMA;

        static const string AS_BEGIN, AS_GENERATE, AS_CASE, AS_CASEX, AS_CASEZ, AS_FUNCTION, AS_FORK, AS_TABLE, AS_TASK, AS_SPECIFY, AS_PRIMITIVE; // add verilog

        static const string AS_END, AS_ENDGENERATE, AS_ENDCASE, AS_ENDFUNCTION, AS_JOIN, AS_ENDTASK, AS_ENDTABLE, AS_ENDSPECIFY, AS_ENDPRIMITIVE;

        static const string AS_INITIAL, AS_FOREVER, AS_ALWAYS, AS_REPEAT;

    public:

        static const char PREPROCESSOR_CHAR;

};

class ASBeautifier : protected ASResource
{
    public:
        ASBeautifier();
        virtual ~ASBeautifier();
        virtual void init(ASStreamIterator* iter); // pointer to dynamically created iterator.
        virtual void init();
        virtual bool hasMoreLines() const;
        virtual string nextLine();
        virtual string beautify(const string &line);
        void setTabIndentation(int length = 4, bool forceTabs = false);
        
        void setSpaceIndentation(int length = 4);
        void setMaxInStatementIndentLength(int max);
        void setMinConditionalIndentLength(int min);

        void setSwitchIndent(bool state);
        void setCaseIndent(bool state);
        void setBracketIndent(bool state);
        void setBlockIndent(bool state);
        void setLabelIndent(bool state);
        void setEmptyLineFill(bool state);
        void setPreprocessorIndent(bool state);

    protected:
        int getNextProgramCharDistance(const string &line, int i);
        bool isLegalNameChar(char ch) const;

        bool isInVerilogNum(const string &line, int i) const;
        bool isWhiteSpace(char ch) const;
        const string *findHeader(const string &line, int i,
                                 const vector<const string*> &possibleHeaders,
                                 bool checkBoundry = true);
        string trim(const string &str);
        int indexOf(vector<const string*> &container, const string *element);

    private:
        ASBeautifier(const ASBeautifier &copy);
        void operator=(ASBeautifier&); // not to be implemented

        void initStatic();
        void registerInStatementIndent(const string &line, int i, int spaceTabCount,
                                       int minIndent, bool updateParenStack);
        string preLineWS(int spaceTabCount, int tabCount);
        void deleteBeautifierContainer(vector<ASBeautifier*>* &container);
        void deleteTempStacksContainer(vector<vector<const string*>*>* &container);
        static vector<const string*> headers;
        static vector<const string*> nonParenHeaders;
        static vector<const string*> preprocessorHeaders;

        static vector<const string*> verilogBlockBegin;

        static vector<const string*> verilogBlockEnd;
        static bool calledInitStatic;

        ASStreamIterator *sourceIterator;
        vector<ASBeautifier*> *waitingBeautifierStack;
        vector<ASBeautifier*> *activeBeautifierStack;
        vector<int> *waitingBeautifierStackLengthStack;
        vector<int> *activeBeautifierStackLengthStack;
        vector<const string*> *headerStack;
        vector< vector<const string*>* > *tempStacks;
        vector<int> *blockParenDepthStack;

        vector<int> *inStatementIndentStack;
        vector<int> *inStatementIndentStackSizeStack;
        vector<int> *parenIndentStack;

        string indentString;
        const string *currentHeader;
        const string *previousLastLineHeader;

        bool isInQuote;
        bool isInComment;
        int  isInCase;
        bool isInQuestion;
        bool isInStatement;
        bool isInHeader;
        bool isInDefine;
        bool isInDefineDefinition;

        bool caseIndent;
        bool namespaceIndent;
        bool bracketIndent;
        bool blockIndent;
        bool labelIndent;
        bool preprocessorIndent;
        bool isInConditional;
        bool isMinimalConditinalIndentSet;

        bool shouldForceTabIndentation;
        int minConditionalIndent;
        int parenDepth;
        int indentLength;
        int leadingWhiteSpaces;
        int maxInStatementIndent;
        char quoteChar;
        char prevNonSpaceCh;
        char currentNonSpaceCh;
        char currentNonLegalCh;
        char prevNonLegalCh;
        int prevFinalLineSpaceTabCount;
        int prevFinalLineTabCount;
        bool emptyLineFill;
        bool backslashEndsPrevLine;
        int defineTabCount;

};

class ASFormatter : public ASBeautifier
{
    public:
        ASFormatter();
        virtual ~ASFormatter();
        virtual void init(ASStreamIterator* iter);
        virtual bool hasMoreLines() const;
        virtual string nextLine();
        bool getIsLineReady() const;
        void setBracketFormatMode(BracketMode mode);
        void setOperatorPaddingMode(bool mode);
        void setParenthesisPaddingMode(bool mode);

        void setBlockPaddingMode(bool mode);
        void setBreakOneLineBlocksMode(bool state);
        void setSingleStatementsMode(bool state);
        void setTabSpaceConversionMode(bool state);
        void setBreakBlocksMode(bool state);
        void setBreakClosingHeaderBlocksMode(bool state);
        void setBreakElseIfsMode(bool state);

    private:
        void ASformatter(ASFormatter &copy); // not to be imlpemented
        void operator=(ASFormatter&); // not to be implemented
        void staticInit();
        bool isFormattingEnabled() const;
        void goForward(int i);
        bool getNextChar();
        char peekNextChar() const;
        bool isBeforeComment() const;
        void trimNewLine();
        BracketType getBracketType() const;
        bool isUrinaryMinus() const;
        bool isInExponent() const;
        bool isOneLineBlockReached() const;
        void appendChar(char ch, bool canBreakLine = true);
        void appendCurrentChar(bool canBreakLine = true);

        void appendBlock(bool canBreakLine = true);
        void appendSequence(const string &sequence, bool canBreakLine = true);
        void appendSpacePad();
        void breakLine();
        inline bool isSequenceReached(const string &sequence) const;
        const string *findHeader(const vector<const string*> &headers, bool checkBoundry = true);

        static vector<const string*> headers;
        static vector<const string*> nonParenHeaders;

        //used for verilog
        static vector<const string*> preprocessorHeaders;

        static vector<const string*> preCommandHeaders;
        static vector<const string*> operators;
        static vector<const string*> verilogBlockBegin;

        static vector<const string*> verilogBlockEnd;

        static bool calledInitStatic;

        ASStreamIterator *sourceIterator;
        vector<const string*> *preBracketHeaderStack;
        vector<int> *parenStack;
        string readyFormattedLine;
        string currentLine;
        string formattedLine;
        const string *currentHeader;
        const string *previousOperator;
        char currentChar;
        char previousChar;
        char previousNonWSChar;
        char previousCommandChar;
        char quoteChar;
        int charNum;
        BracketMode bracketFormatMode;

        bool isVirgin;
        bool shouldPadOperators;

        bool shouldPadBlocks;
        bool shouldPadParenthesies;
        bool shouldConvertTabs;
        bool isInLineComment;
        bool isInComment;
        bool isInPreprocessor;
        bool doesLineStartComment;
        bool isInQuote;
        bool isSpecialChar;
        bool isNonParenHeader;
        bool foundQuestionMark;

        bool isInLineBreak;
        bool isInClosingBracketLineBreak;
        bool endOfCodeReached;
        bool isLineReady;
        bool shouldBreakOneLineBlocks;
        bool shouldReparseCurrentChar;
        bool shouldBreakOneLineStatements;
        bool shouldBreakLineAfterComments;
        bool shouldBreakElseIfs;

        bool passedSemicolon;
        bool passedColon;
        bool isImmediatelyPostComment;

        bool isImmediatelyPostLineComment;

//      bool isImmediatelyPostEmptyBlock;

        bool shouldBreakBlocks;
        bool shouldBreakClosingHeaderBlocks;
        bool isPrependPostBlockEmptyLineRequested;
        bool isAppendPostBlockEmptyLineRequested;

        bool prependEmptyLine;
        int previousReadyFormattedLineLength;

        bool isInHeader;

        bool isImmediatelyPostHeader;

        bool isRealBraceCh;

        bool isInsert;
        const string *vBlockBegin;

        const string *vBlockEnd;

};

#ifdef USES_NAMESPACE
}
#endif

#endif // closes ASTYLE_H

