#include "StdAfx.h"
#include "HTidyInterface.h"
#include "buffio.h"

HTidyInterface::HTidyInterface(UINT nLangID)
:m_onlyHtmlXml(nLangID)
{
}

HTidyInterface::~HTidyInterface(void)
{
}

bool HTidyInterface::formatSource( const char* textIn, CString &strTidy, CString &strMsg )
{
	TidyBuffer output;
	TidyBuffer errbuf;	
	int rc = -1;
	Bool ok = yes;

	TidyDoc tdoc = tidyCreate();                     // Initialize "document"
	tidyBufInit(&output);
	tidyBufInit(&errbuf);

	InitTidyDefault(tdoc);
	SetTidyConfig(tdoc);

	if ( ok )
		rc = tidySetErrorBuffer(tdoc, &errbuf);      // Capture diagnostics
	if ( rc >= 0 )
		rc = tidyParseString(tdoc, textIn);           // Parse the input
	if ( rc >= 0 )
		rc = tidyCleanAndRepair(tdoc);               // Tidy it up!
	if ( rc >= 0 )
		rc = tidyRunDiagnostics(tdoc);               // Kvetch
	//if ( rc > 1 )                                    // If error, force output.
	//	rc = ( tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1 );
	if ( rc >= 0 )
		rc = tidySaveBuffer(tdoc, &output);          // Pretty Print

	if ( rc >= 0 )
	{		
		strTidy = reinterpret_cast< char const* >(output.bp);
	}

	strMsg = reinterpret_cast< char const* >(errbuf.bp);
	CString strEmpty = _T("No warnings or errors were found.\r\n\r\n");
	if (0 == strEmpty.Compare(strMsg))
	{
		strMsg.Empty();
	}
	tidyBufFree(&output);
	tidyBufFree(&errbuf);
	tidyRelease(tdoc);
	return true;
}

void HTidyInterface::SetTidyConfig( TidyDoc tdoc )
{
	CString strTidy;
	if (SYN_HTML == m_onlyHtmlXml)
	{
		strTidy = g_GlobalTidy.m_TidyHtml;
	}
	else
	{
		strTidy = g_GlobalTidy.m_TidyXml;
	}

	int lenTidy = strTidy.GetLength();
	if (lenTidy <= 0 || strTidy[0] != '-')
	{
		return;
	}

	int nOption = -1;
	for (int i = 0; i < lenTidy; ++i)
	{
		if (strTidy[i] == '-')
		{
			if (-1 != nOption)
			{
				SetTidyControl(tdoc, strTidy, nOption, i - nOption);
			}
			nOption = i;
		}
	}
	SetTidyControl(tdoc, strTidy, nOption, lenTidy - nOption);
}

void HTidyInterface::SetTidyControl( TidyDoc tdoc, LPCTSTR lpszTidy, int nPos, int nSize )
{
	if (lpszTidy[nPos] != '-' || nSize < 2)
	{
		return;
	}

	int nNumValue = nSize;
	for (int i = nPos + 1; i < nPos + nSize; ++i)
	{
		if (!_istalpha(lpszTidy[i]))
		{
			nNumValue = i - nPos;
			break;
		}
	}
	CString strParam(lpszTidy + nPos + 1, nNumValue - 1);
	if (nNumValue != nSize)
	{
		CString strNum(lpszTidy + nPos + nNumValue, nSize - nNumValue);
		nNumValue = _ttoi(strNum);
	}
	else
	{
		nNumValue = 0;
	}
	CString strNumValue;
	strNumValue.Format(_T("%d"), nNumValue);

	CString strNothing;
	strNothing.Empty();
	if (_T("axd") == strParam)
	{
		tidyOptSetBool(tdoc, TidyXmlDecl, yes);
	} 
	else if (_T("axs") == strParam)
	{
		tidyOptSetBool(tdoc, TidyXmlSpace, yes);
	}
	else if (_T("aan") == strParam)
	{
		tidyOptSetBool(tdoc, TidyAnchorAsName, yes);
	}
	else if (_T("axp") == strParam)
	{
		tidyOptSetBool(tdoc, TidyXmlPIs, yes);
	}
	else if (_T("b") == strParam)
	{
		tidyOptSetBool(tdoc, TidyMakeBare, yes);
	}
	else if (_T("c") == strParam)
	{
		tidyOptSetBool(tdoc, TidyMakeClean, yes);
	}
	else if (_T("diu") == strParam)
	{
		tidyOptSetBool(tdoc, TidyDecorateInferredUL, yes);
	}
	else if (_T("dep") == strParam)
	{
		tidyOptSetBool(tdoc, TidyDropEmptyParas, yes);
	}
	else if (_T("dft") == strParam)
	{
		tidyOptSetBool(tdoc, TidyDropFontTags, yes);
	}
	else if (_T("dpa") == strParam)
	{
		tidyOptSetBool(tdoc, TidyDropPropAttrs, yes);
	}
	else if (_T("ebt") == strParam)
	{
		tidyOptSetBool(tdoc, TidyEncloseBlockText, yes);
	}
	else if (_T("et") == strParam)
	{
		tidyOptSetBool(tdoc, TidyEncloseBodyText, yes);
	}
	else if (_T("ec") == strParam)
	{
		tidyOptSetBool(tdoc, TidyEscapeCdata, yes);
	}
	else if (_T("fb") == strParam)
	{
		tidyOptSetBool(tdoc, TidyFixBackslash, yes);
	}
	else if (_T("fbc") == strParam)
	{
		tidyOptSetBool(tdoc, TidyFixComments, yes);
	}
	else if (_T("fu") == strParam)
	{
		tidyOptSetBool(tdoc, TidyFixUri, yes);
	}
	else if (_T("hc") == strParam)
	{
		tidyOptSetBool(tdoc, TidyHideComments, yes);
	}
	else if (_T("he") == strParam)
	{
		tidyOptSetBool(tdoc, TidyHideEndTags, yes);
	}
	else if (_T("ic") == strParam)
	{
		tidyOptSetBool(tdoc, TidyIndentCdata, yes);
	}
	else if (_T("ix") == strParam)
	{
		tidyOptSetBool(tdoc, TidyXmlTags, yes);
	}
	else if (_T("jc") == strParam)
	{
		tidyOptSetBool(tdoc, TidyJoinClasses, yes);
	}
	else if (_T("js") == strParam)
	{
		tidyOptSetBool(tdoc, TidyJoinStyles, yes);
	}
	else if (_T("la") == strParam)
	{
		tidyOptSetBool(tdoc, TidyLiteralAttribs, yes);
	}
	else if (_T("le") == strParam)
	{
		tidyOptSetBool(tdoc, TidyLogicalEmphasis, yes);
	}
	else if (_T("ll") == strParam)
	{
		tidyOptSetBool(tdoc, TidyLowerLiterals, yes);
	}
	else if (_T("n") == strParam)
	{
		tidyOptSetBool(tdoc, TidyNCR, yes);
	}
	else if (_T("ne") == strParam)
	{
		tidyOptSetBool(tdoc, TidyNumEntities, yes);
	}
	else if (_T("oh") == strParam)
	{
		tidyOptSetBool(tdoc, TidyHtmlOut, yes);
	}
	else if (_T("ox") == strParam)
	{
		tidyOptSetBool(tdoc, TidyXhtmlOut, yes);
	}
	else if (_T("oxm") == strParam)
	{
		tidyOptSetBool(tdoc, TidyXmlOut, yes);
	}
	else if (_T("pe") == strParam)
	{
		tidyOptSetBool(tdoc, TidyPreserveEntities, yes);
	}
	else if (_T("qa") == strParam)
	{
		tidyOptSetBool(tdoc, TidyQuoteAmpersand, yes);
	}
	else if (_T("qm") == strParam)
	{
		tidyOptSetBool(tdoc, TidyQuoteMarks, yes);
	}
	else if (_T("qn") == strParam)
	{
		tidyOptSetBool(tdoc, TidyQuoteNbsp, yes);
	}
	else if (_T("rc") == strParam)
	{
		tidyOptSetBool(tdoc, TidyReplaceColor, yes);
	}
	else if (_T("ua") == strParam)
	{
		tidyOptSetBool(tdoc, TidyUpperCaseAttrs, yes);
	}
	else if (_T("ut") == strParam)
	{
		tidyOptSetBool(tdoc, TidyUpperCaseTags, yes);
	}
	else if (_T("wo") == strParam)
	{
		tidyOptSetBool(tdoc, TidyWord2000, yes);
	}
	else if (_T("bbb") == strParam)
	{
		tidyOptSetBool(tdoc, TidyBreakBeforeBR, yes);
	} 
	else if (_T("ia") == strParam)
	{
		tidyOptSetBool(tdoc, TidyIndentAttributes, yes);
	}
	else if (_T("m") == strParam)
	{
		tidyOptSetBool(tdoc, TidyShowMarkup, yes);
	}
	else if (_T("pw") == strParam)
	{
		tidyOptSetBool(tdoc, TidyPunctWrap, yes);
	}
	else if (_T("vs") == strParam)
	{
		tidyOptSetBool(tdoc, TidyVertSpace, yes);
	}
	else if (_T("wa") == strParam)
	{
		tidyOptSetBool(tdoc, TidyWrapAsp, yes);
	}
	else if (_T("wat") == strParam)
	{
		tidyOptSetBool(tdoc, TidyWrapAttVals, yes);
	}
	else if (_T("wj") == strParam)
	{
		tidyOptSetBool(tdoc, TidyWrapJste, yes);
	}
	else if (_T("wp") == strParam)
	{
		tidyOptSetBool(tdoc, TidyWrapPhp, yes);
	}
	else if (_T("wsl") == strParam)
	{
		tidyOptSetBool(tdoc, TidyWrapScriptlets, yes);
	}
	else if (_T("ws") == strParam)
	{
		tidyOptSetBool(tdoc, TidyWrapSection, yes);
	}
	else if (_T("ac") == strParam)
	{
		tidyOptSetBool(tdoc, TidyAsciiChars, yes);
	}
	else if (_T("sw") == strParam)
	{
		tidyOptSetBool(tdoc, TidyShowWarnings, yes);
	}
	else if (_T("fo") == strParam)
	{
		tidyOptSetBool(tdoc, TidyForceOutput, yes);
	}
	else if (_T("i") == strParam)
	{
		tidyOptSetInt(tdoc, TidyIndentContent, abs(nNumValue - 2) % 3);
	}
	else if (_T("md") == strParam)
	{
		tidyOptSetInt(tdoc, TidyMergeDivs, abs(nNumValue - 2) % 3);
	}
	else if (_T("ms") == strParam)
	{
		tidyOptSetInt(tdoc, TidyMergeSpans, abs(nNumValue - 2) % 3);
	}
	else if (_T("sbo") == strParam)
	{
		tidyOptSetInt(tdoc, TidyBodyOnly, abs(nNumValue - 2) % 3);
	}
	else if (_T("d") == strParam)
	{
		tidyOptSetInt(tdoc, TidyDoctypeMode, nNumValue % 5);
	}
	else if (_T("ra") == strParam)
	{
		tidyOptSetInt(tdoc, TidyDuplicateAttrs, nNumValue % 2);
	}
	else if (_T("sa") == strParam)
	{
		tidyOptSetInt(tdoc, TidySortAttributes, nNumValue % 2);
	}
	else if (_T("ce") == strParam)
	{		
		tidySetCharEncoding(tdoc, GetEncodeByIndex(nNumValue));
	}
	else if (_T("ie") == strParam)
	{
		tidySetInCharEncoding(tdoc, GetEncodeByIndex(nNumValue));
	}
	else if (_T("oe") == strParam)
	{
		tidySetOutCharEncoding(tdoc, GetEncodeByIndex(nNumValue));
	}
	else if (_T("se") == strParam)
	{
		tidyOptSetInt(tdoc, TidyShowErrors, nNumValue);
	}
	else if (_T("is") == strParam)
	{
		tidyOptSetInt(tdoc, TidyIndentSpaces, nNumValue);
	}
	else if (_T("ts") == strParam)
	{
		tidyOptSetInt(tdoc, TidyTabSize, nNumValue);
	}
	else if (_T("w") == strParam)
	{
		tidyOptSetInt(tdoc, TidyWrapLen, nNumValue);
	}
	else if (_T("at") == strParam)
	{
		tidyOptSetValue(tdoc, TidyAltText, CT2A(m_onlyHtmlXml == SYN_HTML?g_GlobalTidy.m_TidyHtml_at:strNothing));
	}
	else if (_T("cp") == strParam)
	{
		tidyOptSetValue(tdoc, TidyCSSPrefix, CT2A(m_onlyHtmlXml == SYN_HTML?g_GlobalTidy.m_TidyHtml_cp:strNothing));
	}
	else if (_T("nbt") == strParam)
	{
		tidyOptSetValue(tdoc, TidyBlockTags, CT2A(m_onlyHtmlXml == SYN_HTML?g_GlobalTidy.m_TidyHtml_nbt:strNothing));
	}
	else if (_T("net") == strParam)
	{
		tidyOptSetValue(tdoc, TidyEmptyTags, CT2A(m_onlyHtmlXml == SYN_HTML?g_GlobalTidy.m_TidyHtml_net:strNothing));
	}
	else if (_T("nit") == strParam)
	{
		tidyOptSetValue(tdoc, TidyInlineTags, CT2A(m_onlyHtmlXml == SYN_HTML?g_GlobalTidy.m_TidyHtml_nit:strNothing));
	}
	else if (_T("npt") == strParam)
	{
		tidyOptSetValue(tdoc, TidyPreTags, CT2A(m_onlyHtmlXml == SYN_HTML?g_GlobalTidy.m_TidyHtml_npt:strNothing));
	}
}

LPCSTR HTidyInterface::GetEncodeByIndex( int nIndex )
{
	switch (nIndex)
	{
	case 0:return "raw";
	case 1:return "ascii";
	case 2:return "latin0";
	case 3:return "latin1";
	case 4:return "utf8";
	case 5:return "iso2022";
	case 6:return "mac";
	case 7:return "win1252";
	case 8:return "ibm858";
	case 9:return "utf16le";
	case 10:return "utf16be";
	case 11:return "utf16";
	case 12:return "big5";
	case 13:return "shiftjis";
	}
	return "raw";
}

void HTidyInterface::InitTidyDefault( TidyDoc tdoc )
{
	tidyOptSetBool(tdoc, TidyShowMarkup, no);
	tidyOptSetBool(tdoc, TidyShowWarnings, no);
	tidyOptSetBool(tdoc, TidyDropEmptyParas, no);
	tidyOptSetBool(tdoc, TidyFixComments, no);
	tidyOptSetBool(tdoc, TidyQuoteNbsp, no);
	tidyOptSetBool(tdoc, TidyQuoteAmpersand, no);
	tidyOptSetBool(tdoc, TidyWrapSection, no);
	tidyOptSetBool(tdoc, TidyWrapAsp, no);
	tidyOptSetBool(tdoc, TidyWrapJste, no);
	tidyOptSetBool(tdoc, TidyWrapPhp, no);
	tidyOptSetBool(tdoc, TidyFixBackslash, no);
	tidyOptSetBool(tdoc, TidyMark, no);
	tidyOptSetBool(tdoc, TidyFixUri, no);
	tidyOptSetBool(tdoc, TidyLowerLiterals, no);
	tidyOptSetBool(tdoc, TidyJoinStyles, no);
	tidyOptSetBool(tdoc, TidyNCR, no);
	tidyOptSetBool(tdoc, TidyAnchorAsName, no);
}