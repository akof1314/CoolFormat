/* jsformatter.h
   2015-9-14

Copyright (c) 2010- SUN Junwen

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
#ifndef _JSFORMATTER_H_
#define _JSFORMATTER_H_
// This is JSFormatter library include file.

/*
 * CR_READ
 *   READ_CR, Read \r.
 *   SKIP_READ_CR, Skip \r when read.
 */
enum CR_READ { SKIP_READ_CR, READ_CR };
/*
 * CR_PUT
 *   PUT_CR, Use \r\n as new line.
 *   NOT_PUT_CR, Use \n as new line.
 */
enum CR_PUT { NOT_PUT_CR, PUT_CR };
/*
 * BRAC_NEWLINE
 *   NEWLINE_BRAC, New line before bracket.
 *   NO_NEWLINE_BRAC, No bracket before new line.
 */
enum BRAC_NEWLINE { NO_NEWLINE_BRAC, NEWLINE_BRAC };
/*
 * INDENT_IN_EMPTYLINE
 *   INDENT_IN_EMPTYLINE, Output indent chars in empty line.
 *   NO_INDENT_IN_EMPTYLINE, No indent chars in empty line.
 */
enum EMPTYLINE_INDENT { NO_INDENT_IN_EMPTYLINE, INDENT_IN_EMPTYLINE };

struct _FormatterOption
{
	char chIndent;
	int nChPerInd;
	CR_READ eCRRead;
	CR_PUT eCRPut;
	BRAC_NEWLINE eBracNL;
	EMPTYLINE_INDENT eEmpytIndent;

	_FormatterOption():
        chIndent('\t'),
        nChPerInd(1),
        eCRRead(SKIP_READ_CR),
        eCRPut(NOT_PUT_CR),
        eBracNL(NO_NEWLINE_BRAC),
        eEmpytIndent(NO_INDENT_IN_EMPTYLINE)
	{}

	_FormatterOption(char op_chIndent,
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

typedef struct _FormatterOption FormatterOption;

#endif
