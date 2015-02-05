#pragma once
#include "bcgpoutlineparser.h"

class CXmlOutlineParser :
	public CBCGPOutlineParser
{
public:
	enum XmlTagBlockType	// defines custom lexemes (used with LT_CustomBlock)
	{
		XmlTag_Start = -3,	// "<"
		XmlTag_End = -4,	// ">"
		XmlTag_Slash = -5,	// "/"
		XmlTag_Word = -6,	// word - sequence of literals separated by delimiters

		XmlTag_StartWord = -7,		// "<" + word
		XmlTag_StartSlash = -8,		// "<" + "/"
		XmlTag_StartSlashWord = -9,	// "<" + "/" + word
		XmlTag_SlashEnd = -10,		// "/" + ">"
	};

	enum BlockDataFlags
	{
		Flags_XmlTagBlock = 1
	};

	// terminal lexemes
	Lexeme StartLexeme (int nStart = 0) const;
	Lexeme EndLexeme (int nStart = 0) const;
	Lexeme SlashLexeme (int nStart = 0) const;
	Lexeme WordLexeme (int nStart = 0, int nEnd = 0) const;

	// non-terminal lexemes
	Lexeme StartWordLexeme (const Lexeme& lexemeStart, const Lexeme& lexemeWord) const;
	Lexeme StartSlashLexeme (const Lexeme& lexemeStart, const Lexeme& lexemeSlash) const;
	Lexeme StartSlashWordLexeme (const Lexeme& lexemeStartSlash, const Lexeme& lexemeWord) const;
	Lexeme SlashEndLexeme (const Lexeme& lexemeSlash, const Lexeme& lexemeEnd) const;

	Lexeme TagLexeme (const Lexeme& lexemeTagStart, const Lexeme& lexemeTagEnd,
		const CString& strTagName, LexemType nLexemType = LT_CompleteBlock);

public:
	CXmlOutlineParser();
	virtual ~CXmlOutlineParser();

	void EnableXmlParser (BOOL bXmlParser)
	{
		m_bEnableXmlParser = bXmlParser;
	}

protected:
	// Text processing:
	virtual Lexeme GetNext (const CString& strIn, int& nOffset, const int nSearchTo);
	virtual void PushResult (Lexeme lexem, CObList& lstResults);
	virtual void DoParse (const CString& strBuffer, const int nStartOffset, const int nEndOffset, CObList& lstResults);

	// helper
	CString GetTextData (const Lexeme& lexeme, 
		const CString& strBuffer, const int nStartBufOffset, const int nEndBufOffset) const;

protected:
	int m_nMaxAutoTagsCount;
	BOOL m_bSearchNextWord;

	BOOL m_bEnableXmlParser;
};
