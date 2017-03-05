// $Id: ASResource.cpp,v 1.2 2004/02/04 07:35:10 devsolar Exp $
// --------------------------------------------------------------------------
//
// Copyright (c) 1998,1999,2000,2001,2002 Tal Davidson. All rights reserved.
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

#include "compiler_defines.h"
#include "astyle.h"

#include <string>

#ifdef USES_NAMESPACE
using namespace std;

namespace istyle
{
#endif

const string ASResource::AS_IF = string("if");
const string ASResource::AS_ELSE = string ("else");
const string ASResource::AS_FOR = string("for");

const string ASResource::AS_WHILE = string("while");
const string ASResource::AS_SWITCH = string ("switch");

const string ASResource::AS_DEFAULT = string("default");

const string ASResource::PRO_CELLDEFINE            = string("`celldefine");

const string ASResource::PRO_DEFAULT_NETTYPE       = string("`default_nettype");

const string ASResource::PRO_DEFINE                = string("`define");

const string ASResource::PRO_ELSE                  = string("`else");

const string ASResource::PRO_ENDCELLDEFINE         = string("`endcelldefine");

const string ASResource::PRO_ENDIF                 = string("`endif");

const string ASResource::PRO_IFDEF                 = string("`ifdef");

const string ASResource::PRO_INCLUDE               = string("`include");

const string ASResource::PRO_NOUNCONNECTED_DRIVE   = string("`nounconnected_drive");

const string ASResource::PRO_RESETALL              = string("`resetall");

const string ASResource::PRO_TIMESCALE             = string("`timescale");

const string ASResource::PRO_UNCONNECTED_DRIVE     = string("`unconnected_drive");

const string ASResource::PRO_UNDEF                 = string("`undef");

const string ASResource::AS_OPEN_BRACKET = string("{");
const string ASResource::AS_CLOSE_BRACKET = string("}");
const string ASResource::AS_OPEN_LINE_COMMENT = string("//");
const string ASResource::AS_OPEN_COMMENT = string("/*");
const string ASResource::AS_CLOSE_COMMENT = string("*/");

const string ASResource::AS_ASSIGN = string("=");
const string ASResource::AS_LS_ASSIGN = string("<=");

const string ASResource::AS_EQUAL = string("==");
const string ASResource::AS_NOT_EQUAL = string("!=");
const string ASResource::AS_EQUAL_EQUAL = string("===");
const string ASResource::AS_NOT_EQUAL_EQUAL = string("!==");

const string ASResource::AS_BITNOT_AND  = string("~&");
const string ASResource::AS_BITNOT_OR   = string("~|");
const string ASResource::AS_BITNOT_XNOR = string("~^");
const string ASResource::AS_NOT_XNOR    = string("^~");

const string ASResource::AS_GR_EQUAL = string(">=");
const string ASResource::AS_GR_GR = string(">>");
const string ASResource::AS_LS_EQUAL = string("<=");
const string ASResource::AS_LS_LS = string("<<");

const string ASResource::AS_AND = string("&&");
const string ASResource::AS_OR = string("||");

const string ASResource::AS_PAREN_PAREN = string("()");
const string ASResource::AS_BLPAREN_BLPAREN = string("[]");

const string ASResource::AS_PLUS = string("+");
const string ASResource::AS_MINUS = string("-");
const string ASResource::AS_MULT = string("*");
const string ASResource::AS_DIV = string("/");
const string ASResource::AS_MOD = string("%");
const string ASResource::AS_EXP = string("**");

const string ASResource::AS_GR = string(">");
const string ASResource::AS_LS = string("<");
const string ASResource::AS_NOT = string("!");
const string ASResource::AS_BIT_OR = string("|");
const string ASResource::AS_BIT_AND = string("&");
const string ASResource::AS_BIT_NOT = string("~");
const string ASResource::AS_BIT_XOR = string("^");
const string ASResource::AS_QUESTION = string("?");
const string ASResource::AS_COLON = string(":");
const string ASResource::AS_COMMA = string(",");
const string ASResource::AS_SEMICOLON = string(";");

const string ASResource::AS_INITIAL      = string("initial");

const string ASResource::AS_FOREVER      = string("forever");

const string ASResource::AS_ALWAYS       = string("always");
const string ASResource::AS_REPEAT       = string("repeat");

const string ASResource::AS_CASE         = string("case"     );
const string ASResource::AS_CASEX        = string("casex"    );
const string ASResource::AS_CASEZ        = string("casez"    );
const string ASResource::AS_GENERATE     = string("generate" );
const string ASResource::AS_FUNCTION     = string("function" );
const string ASResource::AS_FORK         = string("fork"     );
const string ASResource::AS_TABLE        = string("table"    );
const string ASResource::AS_TASK         = string("task"     );
const string ASResource::AS_SPECIFY      = string("specify"  );
const string ASResource::AS_PRIMITIVE    = string("primitive");
//const string ASResource::AS_MODULE       = string("module"   );
const string ASResource::AS_BEGIN        = string("begin"    );

const string ASResource::AS_ENDCASE      = string("endcase"       );
const string ASResource::AS_ENDGENERATE  = string("endgenerate"   );
const string ASResource::AS_ENDFUNCTION  = string("endfunction"   );
const string ASResource::AS_JOIN         = string("join"          );
const string ASResource::AS_ENDTASK      = string("endtask"       );
const string ASResource::AS_ENDTABLE     = string("endtable"      );
const string ASResource::AS_ENDSPECIFY   = string("endspecify"    );
const string ASResource::AS_ENDPRIMITIVE = string("endprimitive"  );
//const string ASResource::AS_ENDMODULE    = string("endmodule"     );
const string ASResource::AS_END          = string("end"           );

const char   ASResource::PREPROCESSOR_CHAR ='`';

#ifdef USES_NAMESPACE
}
#endif

