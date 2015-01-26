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
