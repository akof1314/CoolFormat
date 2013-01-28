/*
 * Settings class
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

#ifndef _SETTINGS_H
#define _SETTINGS_H

#include "common.h"

/* options enumeration */
enum EOption {
    OPT_LOWER,
    OPT_UPPER,
    OPT_LEAVE,
    
    OPT_KR,
    OPT_ALLMAN,
    OPT_WHITESMITHS,
    OPT_GNU,
    OPT_PEAR
};

/* config tokens */
enum EConfigToken {
    CT_EOF,
    
    CT_STRING,
    CT_BOOLEAN,
    CT_INTEGER,
    CT_CHAR,
    
    CT_SPACE_AFTER_STRUCTURES,
    CT_INDENT_CASE_DEFAULT,
    CT_SPACE_INSIDE_BRACKETS,
    CT_SPACE_INSIDE_EMPTY_BRACKETS,
    CT_SPACE_INSIDE_BLOCK_BRACKETS,
    CT_SPACE_INSIDE_EMPTY_BLOCK_BRACKETS,
    CT_SPACES_AROUND_MATH_OPERATORS,
    CT_SPACES_AROUND_LOGICAL_OPERATORS,
    CT_SPACES_AROUND_EQUALITY_OPERATORS,
    CT_SPACES_AROUND_RELATIONAL_OPERATORS,
    CT_SPACES_AROUND_BITWISE_OPERATORS,
    CT_SPACES_AROUND_ASSIGNMENT_OPERATORS,
    CT_SPACES_AROUND_MAP_OPERATOR,
    CT_TRUE_FALSE_NULL, //string
    CT_TYPE_CONVERTATIONS, //string
    CT_INDENT_CHAR, //char
    CT_INDENT_NUMBER, //int
    CT_FIRST_INDENT_NUMBER, //int
    CT_INDENT_STYLE, //string
    CT_LINK_FUNCTIONS,
    CT_LINK_CODE, //string
    CT_HTML_OUTPUT,
    CT_REMOVE_COMMENTS,
    CT_COMMENT_AFTER_STRUCTURES,
    CT_ALIGN_ASSIGNMENTS,
    CT_ALIGN_ARRAY_KEYS,
    CT_REMOVE_EMPTY_LINES,
    CT_REMOVE_SEMICOLON_LINES,
    CT_INDENT_EMPTY_LINES,
    CT_REWRITE_PERL_COMMENTS,
    CT_REWRITE_SHORT_TAG,
    CT_ASP_TAGS,
    CT_SHORT_TAGS
};

class CSettings {
    public:
        CSettings(void);
        ~CSettings(void);

        void InitFromOptions(const char *pOptions);
        void SetTidyOption(const char *pOption, int nPos, int nSize);
        
        /* STRUCTURES */
        
        /* space after structures */
        bool space_after_structures;
        
        /* indent case and default */
        bool indent_case_default;
        
        /* OPERATORS */
        
        /* space inside brackets ( ) */
        bool space_inside_brackets,
             space_inside_empty_brackets;
        
        /* space inside block brackets ([ ]) */
        bool space_inside_block_brackets,
             space_inside_empty_block_brackets;
        
        /* spaces around math operators (+ - * / %) */
        bool spaces_around_math_operators;
        
        /* spaces around logical operators (&& ||) */
        bool spaces_around_logical_operators;
        
        /* spaces around equality operators (=== !== == !=) */
        bool spaces_around_equality_operators;
        
        /* spaces around relational operators (<> <= >= < > */
        bool spaces_around_relational_operators;
        
        /* spaces around bitwise operators (| & ^ >> << ~) */
        bool spaces_around_bitwise_operators;
        
        /* spaces around assignment operators (= += -= *= /= %= .= |= &= ^= >>= <<= =&) */
        bool spaces_around_assignment_operators;
        
        /* spaces around map operator (=>) */
        bool spaces_around_map_operator;
        
        /* true, false and null and the type convertations */
        EOption true_false_null,
                type_convertations;
        
        /* INDENTATION */
        
        /* indent char */
        char indent_char;
        
        /* indentation numbers */
        uint indent_number,
             first_indent_number;
        
        /* indent style */
        EOption indent_style;
        
        /* FUNCTION LINKING */
        
        /* link functions to the PHP manual */
        bool link_functions;
        
        /* link code (%s is replaced by function) */
        string link_code;
        
        /* OTHERS */
        
        /* color output */
        bool html_output;
        
        /* remove comment */
        bool remove_comments;
        
        /* show comments after the ending bracket of a structure */
        bool comment_after_structures;
        
        /* align assignments */
        bool align_assignments;

        /* align array keys */
        bool align_array_keys;
        
        /* remove empty lines */
        bool remove_empty_lines;
        
        /* remove lines with only a semicolon */
        bool remove_semicolon_lines;
        
        /* indent empty lines */
        bool indent_empty_lines;
        
        /* make C comments from perl comments */
        bool rewrite_perl_comments;
        
        /* make <?php from <? */
        bool rewrite_short_tag;
        
        /* asp tags support */
        bool asp_tags;
        
        /* short tags support */
        bool short_tags;
        
        /* whether formatter should be quiet */
        bool quiet;
        
       
        
        uchar *bottom,
              *token,
              *limit,
              *eof,
              *top,
              *cursor,
              *marker;
        
        uint line;
        
        char   chr;
        string str;
        uint   num;
        bool   boolean;
};

#endif
