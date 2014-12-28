#include "CFHtmlTidy.h"
#include "buffio.h"
#include "tidy-int.h"

CCFHtmlTidy::CCFHtmlTidy(void)
{
}

CCFHtmlTidy::~CCFHtmlTidy(void)
{
}

bool CCFHtmlTidy::TidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &strErr)
{
	TidyBuffer output;
	TidyBuffer errbuf;
	int rc = -1;
	Bool ok = yes;

	TidyDoc tdoc = tidyCreate();                     // Initialize "document"
	tidyBufInit(&output);
	tidyBufInit(&errbuf);

	TidyOptionsSet(tidyDocToImpl(tdoc), pOptions);

	if (ok)
		rc = tidySetErrorBuffer(tdoc, &errbuf);      // Capture diagnostics
	if (rc >= 0)
		rc = tidyParseString(tdoc, pSourceIn);           // Parse the input
	if (rc >= 0)
		rc = tidyCleanAndRepair(tdoc);               // Tidy it up!
	if (rc >= 0)
		rc = tidyRunDiagnostics(tdoc);               // Kvetch
	//if ( rc > 1 )                                    // If error, force output.
	//	rc = ( tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1 );
	if (rc >= 0)
		rc = tidySaveBuffer(tdoc, &output);          // Pretty Print

	if (rc >= 0)
	{
		strOut = reinterpret_cast<char const*>(output.bp);
	}

	strErr = reinterpret_cast<char const*>(errbuf.bp);
	std::string strEmpty = "No warnings or errors were found.\r\n\r\n";
	if (0 == strEmpty.compare(strErr))
	{
		strErr.clear();
	}
	tidyBufFree(&output);
	tidyBufFree(&errbuf);
	tidyRelease(tdoc);
	return true;
}

void CCFHtmlTidy::InitTidyDefault()
{
	TidyDoc formatter = tidyImplToDoc(tidy);
	tidyOptSetBool(formatter, TidyShowMarkup, no);
	tidyOptSetBool(formatter, TidyShowWarnings, no);
	tidyOptSetBool(formatter, TidyDropEmptyParas, no);
	tidyOptSetBool(formatter, TidyFixComments, no);
	tidyOptSetBool(formatter, TidyQuoteNbsp, no);
	tidyOptSetBool(formatter, TidyQuoteAmpersand, no);
	tidyOptSetBool(formatter, TidyWrapSection, no);
	tidyOptSetBool(formatter, TidyWrapAsp, no);
	tidyOptSetBool(formatter, TidyWrapJste, no);
	tidyOptSetBool(formatter, TidyWrapPhp, no);
	tidyOptSetBool(formatter, TidyFixBackslash, no);
	tidyOptSetBool(formatter, TidyMark, no);
	tidyOptSetBool(formatter, TidyFixUri, no);
	tidyOptSetBool(formatter, TidyLowerLiterals, no);
	tidyOptSetBool(formatter, TidyJoinStyles, no);
	tidyOptSetBool(formatter, TidyNCR, no);
	tidyOptSetBool(formatter, TidyAnchorAsName, no);
}

void CCFHtmlTidy::SetTidyProp(const std::string& strParam, int nNumValue, const std::string& /*strNumValue*/, const std::string& strTextValue)
{
	TidyDoc formatter = tidyImplToDoc(tidy);
	if ("axd" == strParam)
	{
		tidyOptSetBool(formatter, TidyXmlDecl, yes);
	}
	else if ("axs" == strParam)
	{
		tidyOptSetBool(formatter, TidyXmlSpace, yes);
	}
	else if ("aan" == strParam)
	{
		tidyOptSetBool(formatter, TidyAnchorAsName, yes);
	}
	else if ("axp" == strParam)
	{
		tidyOptSetBool(formatter, TidyXmlPIs, yes);
	}
	else if ("b" == strParam)
	{
		tidyOptSetBool(formatter, TidyMakeBare, yes);
	}
	else if ("c" == strParam)
	{
		tidyOptSetBool(formatter, TidyMakeClean, yes);
	}
	else if ("diu" == strParam)
	{
		tidyOptSetBool(formatter, TidyDecorateInferredUL, yes);
	}
	else if ("dep" == strParam)
	{
		tidyOptSetBool(formatter, TidyDropEmptyParas, yes);
	}
	else if ("dft" == strParam)
	{
		tidyOptSetBool(formatter, TidyDropFontTags, yes);
	}
	else if ("dpa" == strParam)
	{
		tidyOptSetBool(formatter, TidyDropPropAttrs, yes);
	}
	else if ("ebt" == strParam)
	{
		tidyOptSetBool(formatter, TidyEncloseBlockText, yes);
	}
	else if ("et" == strParam)
	{
		tidyOptSetBool(formatter, TidyEncloseBodyText, yes);
	}
	else if ("ec" == strParam)
	{
		tidyOptSetBool(formatter, TidyEscapeCdata, yes);
	}
	else if ("fb" == strParam)
	{
		tidyOptSetBool(formatter, TidyFixBackslash, yes);
	}
	else if ("fbc" == strParam)
	{
		tidyOptSetBool(formatter, TidyFixComments, yes);
	}
	else if ("fu" == strParam)
	{
		tidyOptSetBool(formatter, TidyFixUri, yes);
	}
	else if ("hc" == strParam)
	{
		tidyOptSetBool(formatter, TidyHideComments, yes);
	}
	else if ("he" == strParam)
	{
		tidyOptSetBool(formatter, TidyHideEndTags, yes);
	}
	else if ("ic" == strParam)
	{
		tidyOptSetBool(formatter, TidyIndentCdata, yes);
	}
	else if ("ix" == strParam)
	{
		tidyOptSetBool(formatter, TidyXmlTags, yes);
	}
	else if ("jc" == strParam)
	{
		tidyOptSetBool(formatter, TidyJoinClasses, yes);
	}
	else if ("js" == strParam)
	{
		tidyOptSetBool(formatter, TidyJoinStyles, yes);
	}
	else if ("la" == strParam)
	{
		tidyOptSetBool(formatter, TidyLiteralAttribs, yes);
	}
	else if ("le" == strParam)
	{
		tidyOptSetBool(formatter, TidyLogicalEmphasis, yes);
	}
	else if ("ll" == strParam)
	{
		tidyOptSetBool(formatter, TidyLowerLiterals, yes);
	}
	else if ("n" == strParam)
	{
		tidyOptSetBool(formatter, TidyNCR, yes);
	}
	else if ("ne" == strParam)
	{
		tidyOptSetBool(formatter, TidyNumEntities, yes);
	}
	else if ("oh" == strParam)
	{
		tidyOptSetBool(formatter, TidyHtmlOut, yes);
	}
	else if ("ox" == strParam)
	{
		tidyOptSetBool(formatter, TidyXhtmlOut, yes);
	}
	else if ("oxm" == strParam)
	{
		tidyOptSetBool(formatter, TidyXmlOut, yes);
	}
	else if ("pe" == strParam)
	{
		tidyOptSetBool(formatter, TidyPreserveEntities, yes);
	}
	else if ("qa" == strParam)
	{
		tidyOptSetBool(formatter, TidyQuoteAmpersand, yes);
	}
	else if ("qm" == strParam)
	{
		tidyOptSetBool(formatter, TidyQuoteMarks, yes);
	}
	else if ("qn" == strParam)
	{
		tidyOptSetBool(formatter, TidyQuoteNbsp, yes);
	}
	else if ("rc" == strParam)
	{
		tidyOptSetBool(formatter, TidyReplaceColor, yes);
	}
	else if ("ua" == strParam)
	{
		tidyOptSetBool(formatter, TidyUpperCaseAttrs, yes);
	}
	else if ("ut" == strParam)
	{
		tidyOptSetBool(formatter, TidyUpperCaseTags, yes);
	}
	else if ("wo" == strParam)
	{
		tidyOptSetBool(formatter, TidyWord2000, yes);
	}
	else if ("bbb" == strParam)
	{
		tidyOptSetBool(formatter, TidyBreakBeforeBR, yes);
	}
	else if ("ia" == strParam)
	{
		tidyOptSetBool(formatter, TidyIndentAttributes, yes);
	}
	else if ("m" == strParam)
	{
		tidyOptSetBool(formatter, TidyShowMarkup, yes);
	}
	else if ("pw" == strParam)
	{
		tidyOptSetBool(formatter, TidyPunctWrap, yes);
	}
	else if ("vs" == strParam)
	{
		tidyOptSetBool(formatter, TidyVertSpace, yes);
	}
	else if ("wa" == strParam)
	{
		tidyOptSetBool(formatter, TidyWrapAsp, yes);
	}
	else if ("wat" == strParam)
	{
		tidyOptSetBool(formatter, TidyWrapAttVals, yes);
	}
	else if ("wj" == strParam)
	{
		tidyOptSetBool(formatter, TidyWrapJste, yes);
	}
	else if ("wp" == strParam)
	{
		tidyOptSetBool(formatter, TidyWrapPhp, yes);
	}
	else if ("wsl" == strParam)
	{
		tidyOptSetBool(formatter, TidyWrapScriptlets, yes);
	}
	else if ("ws" == strParam)
	{
		tidyOptSetBool(formatter, TidyWrapSection, yes);
	}
	else if ("ac" == strParam)
	{
		tidyOptSetBool(formatter, TidyAsciiChars, yes);
	}
	else if ("sw" == strParam)
	{
		tidyOptSetBool(formatter, TidyShowWarnings, yes);
	}
	else if ("fo" == strParam)
	{
		tidyOptSetBool(formatter, TidyForceOutput, yes);
	}
	else if ("i" == strParam)
	{
		tidyOptSetInt(formatter, TidyIndentContent, abs(nNumValue - 2) % 3);
	}
	else if ("md" == strParam)
	{
		tidyOptSetInt(formatter, TidyMergeDivs, abs(nNumValue - 2) % 3);
	}
	else if ("ms" == strParam)
	{
		tidyOptSetInt(formatter, TidyMergeSpans, abs(nNumValue - 2) % 3);
	}
	else if ("sbo" == strParam)
	{
		tidyOptSetInt(formatter, TidyBodyOnly, abs(nNumValue - 2) % 3);
	}
	else if ("d" == strParam)
	{
		tidyOptSetInt(formatter, TidyDoctypeMode, nNumValue % 5);
	}
	else if ("ra" == strParam)
	{
		tidyOptSetInt(formatter, TidyDuplicateAttrs, nNumValue % 2);
	}
	else if ("sa" == strParam)
	{
		tidyOptSetInt(formatter, TidySortAttributes, nNumValue % 2);
	}
	else if ("ce" == strParam)
	{
		tidySetCharEncoding(formatter, TY_(GetEncodingOptNameFromTidyId)(nNumValue));
	}
	else if ("ie" == strParam)
	{
		tidySetInCharEncoding(formatter, TY_(GetEncodingOptNameFromTidyId)(nNumValue));
	}
	else if ("oe" == strParam)
	{
		tidySetOutCharEncoding(formatter, TY_(GetEncodingOptNameFromTidyId)(nNumValue));
	}
	else if ("se" == strParam)
	{
		tidyOptSetInt(formatter, TidyShowErrors, nNumValue);
	}
	else if ("is" == strParam)
	{
		tidyOptSetInt(formatter, TidyIndentSpaces, nNumValue);
	}
	else if ("ts" == strParam)
	{
		tidyOptSetInt(formatter, TidyTabSize, nNumValue);
	}
	else if ("w" == strParam)
	{
		tidyOptSetInt(formatter, TidyWrapLen, nNumValue);
	}
	else if ("at" == strParam)
	{
		tidyOptSetValue(formatter, TidyAltText, strTextValue.c_str());
	}
	else if ("cp" == strParam)
	{
		tidyOptSetValue(formatter, TidyCSSPrefix, strTextValue.c_str());
	}
	else if ("nbt" == strParam)
	{
		tidyOptSetValue(formatter, TidyBlockTags, strTextValue.c_str());
	}
	else if ("net" == strParam)
	{
		tidyOptSetValue(formatter, TidyEmptyTags, strTextValue.c_str());
	}
	else if ("nit" == strParam)
	{
		tidyOptSetValue(formatter, TidyInlineTags, strTextValue.c_str());
	}
	else if ("npt" == strParam)
	{
		tidyOptSetValue(formatter, TidyPreTags, strTextValue.c_str());
	}
}
