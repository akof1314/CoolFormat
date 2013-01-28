/*
 * A Re2c scanner
 *
 * Copyright 2009, Gerben van Veenendaal (http://www.gerbenvv.nl)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License in the COPYING file at the
 * root directory of this project for more details.
 */

#include "settings.h"

#include "exception.h"

/* constructor */
CSettings::CSettings(void) {
    /* STRUCTURES */
    
    /* space after structures */
    space_after_structures = false;
    
    /* indent case and default */
    indent_case_default = false;
    
    /* OPERATORS */
    
    /* space inside brackets ( ) */
    space_inside_brackets       = false;
    space_inside_empty_brackets = false;
    
    /* space inside block brackets ([ ]) */
    space_inside_block_brackets       = false;
    space_inside_empty_block_brackets = false;
    
    /* spaces around math operators (+ - * / %) */
    spaces_around_math_operators = false;
    
    /* spaces around logical operators (&& ||) */
    spaces_around_logical_operators = false;
    
    /* spaces around equality operators (=== !== == !=) */
    spaces_around_equality_operators = false;
    
    /* spaces around relational operators (<> <= >= < >) */
    spaces_around_relational_operators = false;
    
    /* spaces around bitwise operators (| & ^ >> << ~) */
    spaces_around_bitwise_operators = false;
    
    /* spaces around assignment operators (= += -= *= /= %= .= |= &= ^= >>= <<= =&) */
    spaces_around_assignment_operators = false;
    
    /* spaces around map operator (=>) */
    spaces_around_map_operator = false;
    
    /* true, false and null and the type casts */
    true_false_null    = OPT_LOWER; //lower, upper, leave
    type_convertations = OPT_LOWER; //lower, upper, leave
    
    /* INDENTATION */
    
    /* indent char */
    indent_char = ' ';
    
    /* indentation numbers */
    indent_number       = 4;
    first_indent_number = 0;
    
    /* indent style */
    indent_style = OPT_PEAR;
    
    /* FUNCTION LINKING */
    
    /* link functions to the PHP manual */
    link_functions = false;
    
    /* link code (%s is replaced by function) */
    link_code = "<a href=\"http://www.php.net/%s\" title=\"Open the PHP manual for %s\" target=\"_blank\"><b>%s</b></a>";
    
    /* OTHERS */
    
    /* color output */
    html_output = false;
    
    /* remove comment */
    remove_comments = false;
    
    /* show comments after the ending bracket of a structure */
    comment_after_structures = false;
    
    /* align assignments */
    align_assignments = false;
    
    /* align array keys */
    align_array_keys = false;
    
    /* remove empty lines */
    remove_empty_lines = false;
    
    /* remove lines with only a semicolon */
    remove_semicolon_lines = false;
    
    /* indent empty lines */
    indent_empty_lines = false;
    
    /* make C comments from perl comments */
    rewrite_perl_comments = false;
    
    /* make <?php from <? */
    rewrite_short_tag = false;
    
    /* asp tags support */
    asp_tags = false;
    
    /* short tag support */
    short_tags = false;
    
    /* whether formatter should be quiet */
    quiet = false;
    
   
    
    bottom = token = limit = eof = top = cursor = marker = NULL;
    
    line = 1;
}

/* destructor */
CSettings::~CSettings(void) {
   
    
    /* free buffer */
    if (bottom != NULL) {
        free(bottom);
    }
    
    //free input, output, link_code
}


void CSettings::InitFromOptions( const char *pOptions )
{
	if (NULL == pOptions)
	{
		return;
	}
	int lenTidy = strlen(pOptions);
	if (lenTidy <= 0 || pOptions[0] != '-')
	{
		return;
	}

	int nOption = -1;
	for (int i = 0; i < lenTidy; ++i)
	{
		if (pOptions[i] == '-')
		{
			if (-1 != nOption)
			{
				SetTidyOption(pOptions, nOption, i - nOption);
			}
			nOption = i;
		}
	}
	SetTidyOption(pOptions, nOption, lenTidy - nOption);
}

void CSettings::SetTidyOption( const char *pOption, int nPos, int nSize )
{
	if (pOption[nPos] != '-' || nSize < 2)
	{
		return;
	}
	
	int nNumValue = -1;
	for (int i = nPos + 1; i < nPos + nSize; ++i)
	{
		if (isdigit(pOption[i]))
		{
			nNumValue = i - nPos;
			break;
		}
	}
	if (-1 != nNumValue)
	{
		char *szNum = new char[nSize - nNumValue + 1];
		memcpy(szNum, pOption + nPos + nNumValue, nSize - nNumValue);
		szNum[nSize - nNumValue] = '\0';
		nNumValue = atoi(szNum);
		delete[] szNum;
	}

	const char *pTidy = pOption + nPos + 1;
	if (nSize > 3 && 0 == memcmp(pTidy, "sas", 3))
	{
		space_after_structures = true;
	}
	else if (nSize > 3 && 0 == memcmp(pTidy, "icd", 3))
	{
		indent_case_default = true;
	}
	else if (nSize > 4 && 0 == memcmp(pTidy, "sibr", 4))
	{
		space_inside_brackets = true;
	}
	else if (nSize > 5 && 0 == memcmp(pTidy, "siebr", 5))
	{
		space_inside_empty_brackets = true;
	}
	else if (nSize > 4 && 0 == memcmp(pTidy, "sibb", 4))
	{
		space_inside_block_brackets = true;
	}
	else if (nSize > 5 && 0 == memcmp(pTidy, "siebb", 5))
	{
		space_inside_empty_block_brackets = true;
	}
	else if (nSize > 4 && 0 == memcmp(pTidy, "samt", 4))
	{
		spaces_around_math_operators = true;
	}
	else if (nSize > 4 && 0 == memcmp(pTidy, "salo", 4))
	{
		spaces_around_logical_operators = true;
	}
	else if (nSize > 4 && 0 == memcmp(pTidy, "saeo", 4))
	{
		spaces_around_equality_operators = true;
	}
	else if (nSize > 4 && 0 == memcmp(pTidy, "saro", 4))
	{
		spaces_around_relational_operators = true;
	}
	else if (nSize > 4 && 0 == memcmp(pTidy, "sabo", 4))
	{
		spaces_around_bitwise_operators = true;
	}
	else if (nSize > 4 && 0 == memcmp(pTidy, "saao", 4))
	{
		spaces_around_assignment_operators = true;
	}
	else if (nSize > 4 && 0 == memcmp(pTidy, "samp", 4))
	{
		spaces_around_map_operator = true;
	}
	else if (nSize > 2 && 0 == memcmp(pTidy, "rc", 2))
	{
		remove_comments = true;
	}
	else if (nSize > 3 && 0 == memcmp(pTidy, "cas", 3))
	{
		comment_after_structures = true;
	}
	else if (nSize > 3 && 0 == memcmp(pTidy, "aas", 3))
	{
		align_assignments = true;
	}
	else if (nSize > 3 && 0 == memcmp(pTidy, "aak", 3))
	{
		align_array_keys = true;
	}
	else if (nSize > 3 && 0 == memcmp(pTidy, "rel", 3))
	{
		remove_empty_lines = true;
	}
	else if (nSize > 3 && 0 == memcmp(pTidy, "rsl", 3))
	{
		remove_semicolon_lines = true;
	}
	else if (nSize > 3 && 0 == memcmp(pTidy, "iel", 3))
	{
		indent_empty_lines = true;
	}
	else if (nSize > 3 && 0 == memcmp(pTidy, "rpc", 3))
	{
		rewrite_perl_comments = true;
	}
	else if (nSize > 3 && 0 == memcmp(pTidy, "rst", 3))
	{
		rewrite_short_tag = true;
	}
	else if (nSize > 2 && 0 == memcmp(pTidy, "at", 2))
	{
		asp_tags = true;
	}
	else if (nSize > 2 && 0 == memcmp(pTidy, "st", 2))
	{
		short_tags = true;
	}
	else if (nSize > 1 && 0 == memcmp(pTidy, "q", 1))
	{
		quiet = true;
	}
	else if (nSize > 3 && 0 == memcmp(pTidy, "tfn", 3))
	{
		if (0 <= nNumValue && 2 >= nNumValue)
		{
			true_false_null = (EOption)nNumValue;
		}
	}
	else if (nSize > 2 && 0 == memcmp(pTidy, "tc", 2))
	{
		if (0 <= nNumValue && 2 >= nNumValue)
		{
			type_convertations = (EOption)nNumValue;
		}
	}
	else if (nSize > 3 && 0 == memcmp(pTidy, "ich", 3))
	{
		if (0 <= nNumValue && 1 >= nNumValue)
		{
			indent_char = nNumValue == 0?' ':'\t';
		}
	}
	else if (nSize > 2 && 0 == memcmp(pTidy, "in", 2))
	{
		if (0 <= nNumValue)
		{
			indent_number = nNumValue;
		}
	}
	else if (nSize > 3 && 0 == memcmp(pTidy, "fin", 3))
	{
		if (0 <= nNumValue)
		{
			first_indent_number = nNumValue;
		}
	}
	else if (nSize > 2 && 0 == memcmp(pTidy, "is", 2))
	{
		if (0 <= nNumValue && 4 >= nNumValue)
		{
			indent_style = (EOption)(nNumValue + 3);
		}
	}
}
