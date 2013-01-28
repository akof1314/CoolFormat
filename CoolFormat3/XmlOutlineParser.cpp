#include "StdAfx.h"
#include "XmlOutlineParser.h"

CXmlOutlineParser::CXmlOutlineParser()
{
	m_nMaxAutoTagsCount = 512;
	m_bSearchNextWord = FALSE;

	m_bEnableXmlParser = FALSE;
}

CXmlOutlineParser::~CXmlOutlineParser()
{
}
//************************************************************************************
Lexeme CXmlOutlineParser::StartLexeme (int nStart) const
{
	return Lexeme (XmlTag_Start, LT_CustomBlock, nStart, nStart);
}
//************************************************************************************
Lexeme CXmlOutlineParser::EndLexeme (int nStart) const
{
	return Lexeme (XmlTag_End, LT_CustomBlock, nStart, nStart);
}
//************************************************************************************
Lexeme CXmlOutlineParser::SlashLexeme (int nStart) const
{
	return Lexeme (XmlTag_Slash, LT_CustomBlock, nStart, nStart);
}
//************************************************************************************
Lexeme CXmlOutlineParser::WordLexeme (int nStart, int nEnd) const
{
	return Lexeme (XmlTag_Word, LT_CustomBlock, nStart, nEnd,
		MAKELONG ((WORD)nStart, (WORD)nEnd)); // store word's offsets
}
//************************************************************************************
Lexeme CXmlOutlineParser::StartWordLexeme (const Lexeme& lexemeStart, const Lexeme& lexemeWord) const
{
	return Lexeme (XmlTag_StartWord, LT_CustomBlock, lexemeStart.m_nStart, lexemeWord.m_nEnd,
		lexemeWord.m_dwData); // store word's offsets
}
//************************************************************************************
Lexeme CXmlOutlineParser::StartSlashLexeme (const Lexeme& lexemeStart, const Lexeme& lexemeSlash) const
{
	return Lexeme (XmlTag_StartSlash, LT_CustomBlock, lexemeStart.m_nStart, lexemeSlash.m_nEnd);
}
//************************************************************************************
Lexeme CXmlOutlineParser::StartSlashWordLexeme (const Lexeme& lexemeStartSlash, const Lexeme& lexemeWord) const
{
	return Lexeme (XmlTag_StartSlashWord, LT_CustomBlock, lexemeStartSlash.m_nStart, lexemeWord.m_nEnd, 
		lexemeWord.m_dwData); // store word's offsets
}
//************************************************************************************
Lexeme CXmlOutlineParser::SlashEndLexeme (const Lexeme& lexemeSlash, const Lexeme& lexemeEnd) const
{
	return Lexeme (XmlTag_SlashEnd, LT_CustomBlock, lexemeSlash.m_nStart, lexemeEnd.m_nEnd);
}
//************************************************************************************
CString CXmlOutlineParser::GetTextData (const Lexeme& lexeme, 
										const CString& strBuffer, const int nStartBufOffset, const int nEndBufOffset) const
{
	ASSERT_VALID (this);

	if (lexeme.m_dwData != 0)
	{
		int nStartOffset = LOWORD (lexeme.m_dwData);
		int nEndOffset = HIWORD (lexeme.m_dwData);

		if (nStartOffset <= nEndOffset && nEndOffset < strBuffer.GetLength () &&
			nStartOffset >= nStartBufOffset && nStartOffset <= nEndBufOffset &&
			nEndOffset >= nStartBufOffset && nEndOffset <= nEndBufOffset)
		{
			return strBuffer.Mid (nStartOffset, nEndOffset - nStartOffset + 1);
		}
	}

	CString strEmpty;
	return strEmpty;
}
//************************************************************************************
Lexeme CXmlOutlineParser::TagLexeme (const Lexeme& lexemeTagStart, const Lexeme& lexemeTagEnd,
									 const CString& strTagName, LexemType nLexemType)
{
	int nBlockType = -1;
	CString strTag = _T("<") + strTagName + _T(">");

	for (int i = 0; i <= m_arrBlockTypes.GetUpperBound (); i++)
	{
		BlockType* pBlockType = m_arrBlockTypes [i];
		ASSERT (pBlockType != NULL);

		if (pBlockType->m_strReplace.CompareNoCase (strTag) == 0)
		{
			nBlockType = i;
			break;
		}
	}

	if (nBlockType == -1 && m_arrBlockTypes.GetSize () < m_nMaxAutoTagsCount)
	{
		BlockType* pNewBlockType = new BlockType (strTag, strTag, strTag, TRUE);
		pNewBlockType->m_dwData = Flags_XmlTagBlock;
		m_arrBlockTypes.Add (pNewBlockType);

		nBlockType = (int)m_arrBlockTypes.GetUpperBound ();
	}

	return Lexeme (nBlockType, nLexemType, lexemeTagStart.m_nStart, lexemeTagEnd.m_nEnd,
		lexemeTagStart.m_dwData); // store word's offsets
}
//************************************************************************************
Lexeme CXmlOutlineParser::GetNext (const CString& strIn, int& nOffset, const int nSearchTo)
{
	if (!m_bEnableXmlParser)
	{
		return CBCGPOutlineParser::GetNext (strIn, nOffset, nSearchTo);
	}

	while (nOffset >= 0 && nOffset < strIn.GetLength () && nOffset <= nSearchTo)
	{
		if (IsEscapeSequence (strIn, nOffset))
		{
			continue;
		}
		
		for (int i = 0; i <= m_arrBlockTypes.GetUpperBound (); i++)
		{
			BlockType* pBlockType = m_arrBlockTypes [i];
			ASSERT (pBlockType != NULL);

			if (pBlockType->m_dwData == Flags_XmlTagBlock)
			{
				break;
			}
			
			// Nested blocks:
			if (pBlockType->m_bAllowNestedBlocks)
			{
				int nEndOffset;
				if (Compare (strIn, nOffset, pBlockType->m_strOpen, nEndOffset))
				{
					Lexeme lexem (i, LT_BlockStart, nOffset, nEndOffset);
					nOffset += pBlockType->m_strOpen.GetLength ();
					return lexem;
				}
				else if (Compare (strIn, nOffset, pBlockType->m_strClose, nEndOffset))
				{
					Lexeme lexem (i, LT_BlockEnd, nOffset, nEndOffset);
					nOffset += pBlockType->m_strClose.GetLength ();
					return lexem;
				}
			}
			// NonNested blocks:
			else
			{
				int nEndOffset;
				if (Compare (strIn, nOffset, pBlockType->m_strOpen, nEndOffset))
				{
					Lexeme lexem (i, LT_CompleteBlock, nOffset, nEndOffset);
					nOffset += pBlockType->m_strOpen.GetLength ();
					
					if (!pBlockType->m_strClose.IsEmpty ())
					{
						// find close token skipping escape sequences:
						while  (nOffset >= 0 && 
							nOffset < strIn.GetLength () && 
							nOffset <= nSearchTo)
						{
							if (IsEscapeSequence (strIn, nOffset))
							{
								continue;
							}
							
							if (Compare (strIn, nOffset, pBlockType->m_strClose, nEndOffset))
							{
								nOffset += pBlockType->m_strClose.GetLength ();
								if (pBlockType->m_strClose == _T("\n"))
								{
									nOffset--;
								}
								
								lexem.m_nEnd = nOffset - 1;
								return lexem;
							}
							
							nOffset++;
						}
					}
					
					if (pBlockType->m_bIgnore)
					{
						nOffset = lexem.m_nStart;
					}
					else
					{
						lexem.m_nEnd = strIn.GetLength () - 1;
						return lexem;
					}
				}
			}

		}
		
		// StartLexeme
		int nEndOffset;
		if (Compare (strIn, nOffset, _T("<"), nEndOffset))
		{
			m_bSearchNextWord = TRUE;
			return StartLexeme (nOffset++);
		}

		// EndLexeme
		else if (Compare (strIn, nOffset, _T(">"), nEndOffset))
		{
			m_bSearchNextWord = FALSE;
			return EndLexeme (nOffset++);
		}

		// SlashLexeme
		else if (Compare (strIn, nOffset, _T("/"), nEndOffset))
		{
			return SlashLexeme (nOffset++);
		}

		// WordLexeme
		else if (m_bSearchNextWord)
		{
			int nWordStartOffset = nOffset;
			int	nWordEndOffset = nOffset;
			while (nWordEndOffset < strIn.GetLength () && nWordEndOffset <= nSearchTo)
			{
				// search until the first delimiter
				if (m_strDelimiters.Find (strIn [nWordEndOffset]) >= 0)
				{
					if (nWordEndOffset == nOffset)
					{
						break;
					}

					nOffset = nWordEndOffset;
					m_bSearchNextWord = FALSE;

					return WordLexeme (nWordStartOffset, nWordEndOffset - 1);
				}

				nWordEndOffset++;
			}
		}

		nOffset++;
	}
	
	return Lexeme (0, LT_EndOfText, 0, 0);
}
//************************************************************************************
void CXmlOutlineParser::PushResult (Lexeme lexem, CObList& lstResults)
{
	if (lexem.m_nBlockType >= 0 && lexem.m_nBlockType <= m_arrBlockTypes.GetUpperBound ())
	{
		CBCGPOutlineParser::PushResult (lexem, lstResults);
		return;
	}

#ifdef _DEBUG
	CString str;

	switch (lexem.m_nBlockType)
	{
	case XmlTag_Start:
		DEBUG_ONLY (str.Format (_T("<_%d, "), lexem.m_nStart));
		break;

	case XmlTag_End:
		DEBUG_ONLY (str.Format (_T(">_%d, "), lexem.m_nStart));
		break;
		
	case XmlTag_Slash:
		DEBUG_ONLY (str.Format (_T("/_%d, "), lexem.m_nStart));
		break;
		
	case XmlTag_Word:
		DEBUG_ONLY (str.Format (_T("word_%d_%d, "), lexem.m_nStart, lexem.m_nEnd));
		break;
		
	case XmlTag_StartWord:
		DEBUG_ONLY (str.Format (_T("<word_%d_%d, "), lexem.m_nStart, lexem.m_nEnd));
		break;
		
	case XmlTag_StartSlash:
		DEBUG_ONLY (str.Format (_T("</_%d_%d, "), lexem.m_nStart, lexem.m_nEnd));
		break;
		
	case XmlTag_StartSlashWord:
		DEBUG_ONLY (str.Format (_T("</word_%d_%d, "), lexem.m_nStart, lexem.m_nEnd));
		break;
		
	case XmlTag_SlashEnd:
		DEBUG_ONLY (str.Format (_T("/>_%d_%d, "), lexem.m_nStart, lexem.m_nEnd));
		break;
	}

	DEBUG_ONLY (m_strOut += str);
#endif // _DEBUG
}
//************************************************************************************
void CXmlOutlineParser::DoParse (const CString& strBuffer, const int nStartOffset, const int nEndOffset, CObList& lstResults)
{
	if (!m_bEnableXmlParser)
	{
		CBCGPOutlineParser::DoParse (strBuffer, nStartOffset, nEndOffset, lstResults);
		return;
	}

	ASSERT (nStartOffset >= 0);
	ASSERT (nEndOffset < strBuffer.GetLength ());
	ASSERT (nStartOffset <= nEndOffset);
	
	m_strOut.Empty ();
	
	CList <Lexeme, Lexeme&> lstStack;
	Lexeme lexemStackTop (0, LT_Eps, 0, 0);
	lstStack.AddTail (lexemStackTop);
	
	int nOffset	= nStartOffset;
	
	while (nOffset <= nEndOffset)
	{
		// Get next lexem:
		Lexeme lexemNext = GetNext (strBuffer, nOffset, nEndOffset);
		Lexeme lexemTop = lstStack.GetTail ();
		
		if (lexemNext.m_nType == LT_EndOfText)
		{
			break;
		}
		
		// Parser logic:
		switch (lexemNext.m_nType)
		{
		case LT_BlockStart:
			lstStack.AddTail (lexemNext);
			break;
		case LT_BlockEnd:
			if (lexemTop.m_nType == LT_BlockStart &&
				lexemTop.m_nBlockType == lexemNext.m_nBlockType)
			{
				// Push Block:
				lstStack.RemoveTail ();
				Lexeme lexemRes (lexemTop.m_nBlockType, LT_CompleteBlock, lexemTop.m_nStart, lexemNext.m_nEnd, lexemTop.m_dwData);
				PushResult (lexemRes, lstResults);
			}
			else
			{
				lstStack.AddTail (lexemNext);
			}
			break;
		case LT_CompleteBlock:
			{
				// Push Comment:
				PushResult (lexemNext, lstResults);
			}
			break;
		case LT_CustomBlock:
			if (lexemNext.m_nBlockType == XmlTag_Start)
			{
				lstStack.AddTail (lexemNext);
			}
			else if (lexemNext.m_nBlockType == XmlTag_End)
			{
				// XmlTag_SlashEnd <- XmlTag_Slash XmlTag_End
				if (lexemTop.m_nBlockType == XmlTag_Slash)
				{
					lstStack.RemoveTail ();
					Lexeme lexemTagEnd = SlashEndLexeme (lexemTop, lexemNext);

					lexemNext = lexemTagEnd;
					lexemTop = lstStack.GetTail ();

					// TagLexeme <- XmlTag_StartWord XmlTag_SlashEnd
					if (lexemTop.m_nBlockType == XmlTag_StartWord)
					{
						// Push Block:
						lstStack.RemoveTail ();
						CString strName = GetTextData (lexemTop, strBuffer, nStartOffset, nEndOffset);
						Lexeme lexemTag = TagLexeme (lexemTop, lexemNext, strName, LT_CompleteBlock);
						lstStack.AddTail (lexemTag);
					}
					else
					{
						lstStack.AddTail (lexemNext);
					}
				}

				// TagLexeme <- XmlTag_StartWord XmlTag_End
				else if (lexemTop.m_nBlockType == XmlTag_StartWord)
				{
					lstStack.RemoveTail ();
					CString strName = GetTextData (lexemTop, strBuffer, nStartOffset, nEndOffset);
					Lexeme lexemTag = TagLexeme (lexemTop, lexemNext, strName, LT_BlockStart);
					lstStack.AddTail (lexemTag);
				}
				// TagLexeme <- XmlTag_StartSlashWord XmlTag_End
				else if (lexemTop.m_nBlockType == XmlTag_StartSlashWord)
				{
					lstStack.RemoveTail ();
					CString strName = GetTextData (lexemTop, strBuffer, nStartOffset, nEndOffset);
					Lexeme lexemTagEnd = TagLexeme (lexemTop, lexemNext, strName, LT_BlockEnd);

					lexemNext = lexemTagEnd;
					lexemTop = lstStack.GetTail ();

					// TagLexeme(LT_CompleteBlock) <- TagLexeme(LT_BlockStart) TagLexeme(LT_BlockEnd)
					if (lexemTop.m_nType == LT_BlockStart &&
						lexemTop.m_nBlockType == lexemNext.m_nBlockType)
					{
						// Push Block:
						lstStack.RemoveTail ();
						Lexeme lexemRes = TagLexeme (lexemTop, lexemNext, strName, LT_CompleteBlock);
						PushResult (lexemRes, lstResults);
					}
					else
					{
						lstStack.AddTail (lexemNext);
					}
				}
			}
			else if (lexemNext.m_nBlockType == XmlTag_Slash)
			{
				// XmlTag_StartSlash <- XmlTag_Start XmlTag_Slash
				if (lexemTop.m_nBlockType == XmlTag_Start)
				{
					lstStack.RemoveTail ();
					Lexeme lexemRes = StartSlashLexeme (lexemTop, lexemNext);
					lstStack.AddTail (lexemRes);
				}
				else
				{
					lstStack.AddTail (lexemNext);
				}
			}
			else if (lexemNext.m_nBlockType == XmlTag_Word)
			{
				// XmlTag_StartWord <- XmlTag_Start XmlTag_Word
				if (lexemTop.m_nBlockType == XmlTag_Start)
				{
					lstStack.RemoveTail ();
					Lexeme lexemRes = StartWordLexeme (lexemTop, lexemNext);
					lstStack.AddTail (lexemRes);
				}
				// XmlTag_StartSlashWord <- XmlTag_StartSlash XmlTag_Word
				else if (lexemTop.m_nBlockType == XmlTag_StartSlash)
				{
					lstStack.RemoveTail ();
					Lexeme lexemRes = StartSlashWordLexeme (lexemTop, lexemNext);
					lstStack.AddTail (lexemRes);
				}
				else
				{
					// ignore word
				}
			}
			break;
		}
	}
	
	// Finish parsing:
	while (!lstStack.IsEmpty ())
	{
		Lexeme lexem = lstStack.RemoveTail ();
		PushResult (lexem, lstResults);
	}
}
