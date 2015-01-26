#include "CFPhpTidy.h"
#include "common.h"

#include "exception.h"
#include "settings.h"
#include "formatter.h"
#include "scanner.h"
#include "parser.h"

/* globals */
CSettings  *settings  = NULL;
CFormatter *formatter = NULL;
CScanner   *scanner   = NULL;
CParser    *parser    = NULL;

CCFPhpTidy::CCFPhpTidy(void)
{
}

CCFPhpTidy::~CCFPhpTidy(void)
{
}

bool CCFPhpTidy::TidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &strErr)
{
	try {
		/* create settings class */
		settings = new CSettings();
		if (settings == NULL) {
			throw new CException(E_MEMORY);
		}

		/* create formatter class */
		formatter = new CFormatter();
		if (formatter == NULL) {
			throw new CException(E_MEMORY);
		}

		/* create scanner class */
		scanner = new CScanner();
		if (scanner == NULL) {
			throw new CException(E_MEMORY);
		}

		/* create parser class */
		parser = new CParser();
		if (parser == NULL) {
			throw new CException(E_MEMORY);
		}

		/* init settings */
		TidyOptionsSet(settings, pOptions);

		/* init formatter */
		formatter->Init();

		/* init scanner */
		scanner->Init(pSourceIn);

		/* init parser */
		//CParser->Init();

		/* start formatting */
		formatter->Run(strOut);
	}

	/* catch exceptions */
	catch (CException *exception) {

		/* show message */
		if (!settings->quiet)
		{
			strErr = exception->message;
		}

		/* delete classes */
		if (settings != NULL) {
			delete settings;
		}

		if (formatter != NULL) {
			delete formatter;
		}

		if (scanner != NULL) {
			delete scanner;
		}

		if (parser != NULL) {
			delete parser;
		}

		return false;
	}

	/* delete classes */
	delete settings;
	delete formatter;
	delete scanner;
	delete parser;

	return true;
}

void CCFPhpTidy::InitTidyDefault()
{
	CSettings* formatter = (CSettings*)tidy;
	formatter->indent_char = ' ';
	formatter->indent_number = 4;
	formatter->first_indent_number = 0;
}

void CCFPhpTidy::SetTidyProp(const std::string& strParam, int nNumValue, const std::string& strNumValue, const std::string& strTextValue)
{
	CSettings* formatter = (CSettings*)tidy;
	if ("sas" == strParam)
	{
		formatter->space_after_structures = true;
	}
	else if ("icd" == strParam)
	{
		formatter->indent_case_default = true;
	}
	else if ("sibr" == strParam)
	{
		formatter->space_inside_brackets = true;
	}
	else if ("siebr" == strParam)
	{
		formatter->space_inside_empty_brackets = true;
	}
	else if ("sibb" == strParam)
	{
		formatter->space_inside_block_brackets = true;
	}
	else if ("siebb" == strParam)
	{
		formatter->space_inside_empty_block_brackets = true;
	}
	else if ("samt" == strParam)
	{
		formatter->spaces_around_math_operators = true;
	}
	else if ("salo" == strParam)
	{
		formatter->spaces_around_logical_operators = true;
	}
	else if ("saeo" == strParam)
	{
		formatter->spaces_around_equality_operators = true;
	}
	else if ("saro" == strParam)
	{
		formatter->spaces_around_relational_operators = true;
	}
	else if ("sabo" == strParam)
	{
		formatter->spaces_around_bitwise_operators = true;
	}
	else if ("saao" == strParam)
	{
		formatter->spaces_around_assignment_operators = true;
	}
	else if ("samp" == strParam)
	{
		formatter->spaces_around_map_operator = true;
	}
	else if ("rc" == strParam)
	{
		formatter->remove_comments = true;
	}
	else if ("cas" == strParam)
	{
		formatter->comment_after_structures = true;
	}
	else if ("aas" == strParam)
	{
		formatter->align_assignments = true;
	}
	else if ("aak" == strParam)
	{
		formatter->align_array_keys = true;
	}
	else if ("rel" == strParam)
	{
		formatter->remove_empty_lines = true;
	}
	else if ("rsl" == strParam)
	{
		formatter->remove_semicolon_lines = true;
	}
	else if ("iel" == strParam)
	{
		formatter->indent_empty_lines = true;
	}
	else if ("rpc" == strParam)
	{
		formatter->rewrite_perl_comments = true;
	}
	else if ("rst" == strParam)
	{
		formatter->rewrite_short_tag = true;
	}
	else if ("at" == strParam)
	{
		formatter->asp_tags = true;
	}
	else if ("st" == strParam)
	{
		formatter->short_tags = true;
	}
	else if ("q" == strParam)
	{
		formatter->quiet = true;
	}
	else if ("tfn" == strParam)
	{
		if (0 <= nNumValue && 2 >= nNumValue)
		{
			formatter->true_false_null = (EOption)nNumValue;
		}
	}
	else if ("tc" == strParam)
	{
		if (0 <= nNumValue && 2 >= nNumValue)
		{
			formatter->type_convertations = (EOption)nNumValue;
		}
	}
	else if ("ich" == strParam)
	{
		if (0 <= nNumValue && 1 >= nNumValue)
		{
			formatter->indent_char = nNumValue == 0 ? ' ' : '\t';
		}
	}
	else if ("in" == strParam)
	{
		if (0 <= nNumValue)
		{
			formatter->indent_number = nNumValue;
		}
	}
	else if ("fin" == strParam)
	{
		if (0 <= nNumValue)
		{
			formatter->first_indent_number = nNumValue;
		}
	}
	else if ("is" == strParam)
	{
		if (0 <= nNumValue && 4 >= nNumValue)
		{
			formatter->indent_style = (EOption)(nNumValue + 3);
		}
	}
}
