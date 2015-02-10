/*
 * Formatter class
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

#include "formatter.h"

#include "exception.h"
#include "settings.h"
#include "scanner.h"
#include "parser.h"

extern CSettings *settings;
extern CScanner  *scanner;
extern CParser   *parser;

/* constructor */
CFormatter::CFormatter(void) {
    //file = NULL;
    
    indent = 0;
    
    first_node = NULL;
    last_node  = NULL;
    
    maxvarlength = 0;
}

/* destructor */
CFormatter::~CFormatter(void) {
    CNode *node,
          *temp;
    
    /* close file */
//     if (file != NULL) {
//         fclose(file);
//     }
    
    /* free nodes */
    node = first_node;
    while (node) {
        temp = node->next;
        delete node;
        node = temp;
    }
}

/* inits formatter */
void CFormatter::Init(void) {
    /* open output file */
//     file = fopen(settings->output.c_str(), "w");
//     if (file == NULL) {
//         throw new CException(E_INTERNAL, "Couldn\'t open output file!");
//     }
    
    /* insert none state */
    states.push(S_NONE);
}

/* runs formatter */
void CFormatter::Run(string &strOut) {
    /* run parser */
    parser->Parse();
    
    /* format possible assignments */
    FormatAssignments();
    
    if (first_node != last_node) {
        first_node->Append(last_node, true); //NOTE: must absolutely be true
    	
        //Write(first_node);
		strOut = first_node->token;
    } else {
        //NOTE: empty file
		strOut = "";
    }
}

/* gets indent string */
string CFormatter::GetIndent(int add, bool half) {
    int number = (indent + add) * settings->indent_number +
        settings->first_indent_number;
    if (half) { //NOTE: for tabs this is zero!
        number += settings->indent_number / 2;
    }
    
    if (number <= 0) {
        return "";
    }
    
    return string(number, settings->indent_char);
}

void CFormatter::AddAssignment(CNode *variable, CNode *semicolon) {
    SAssignment assignment = {
        variable,
        semicolon,
        (uint)variable->token.length()
    };
    
    //TODO: add more assignments, eg +=, -= list(..) =
    
    //find out whether this is a new serie
    if (!assignments.empty()) {
        CNode *node = assignments.top().semicolon->next;
        
        do {
            //check for variable
            if (node == variable) {
                goto add;
            } else if (//(node->type != NT_NEWLINES) && //really (?)
                       (node->type != NT_SHORT_COMMENT) && //and not on the same line...
                       (node->type != NT_LONG_COMMENT)
                      ) { //really (?)
                
                //definitely a new serie
                break;
            }
        } while (node = node->next);
        
        //format current serie
        FormatAssignments();
    }
    
add:
    
    //find out whether var is longer
    uint varlength = assignment.length;
    if (varlength > maxvarlength) {
        maxvarlength = varlength;
    }
    
    //add assignment
    assignments.push(assignment);
}

void CFormatter::FormatAssignments(void) {
    SAssignment top;
    
    //this is to undo removal of spaces in appending nodes...
    uint add = settings->spaces_around_assignment_operators;
    
    while (!assignments.empty()) {
        top = assignments.top();
        
        top.var->token.append(add + maxvarlength - top.length, ' ');
        top.var->Append(top.semicolon);
        
        assignments.pop();
    }
    
    maxvarlength = 0;
}

/* formats open curly bracket */
void CFormatter::FormatOpenCurlyBracket(CNode **node, bool function_class) {
    bool half = false;
    bool add  = false;
    
    /* check if next node is newlines */
    if ((*node)->next->type == NT_NEWLINES) {
        CNode *next = (*node)->next;
        
        /* skip node */
        (*node)->next = (*node)->next->next;
        
        /* delete node */
        delete next;
    }
    
    /* check indent style */
    switch (settings->indent_style) {
        case OPT_KR:
            break;
            
        case OPT_WHITESMITHS:
            add = true;
            goto newline;
            
        case OPT_GNU:
            half = true;
            goto newline;
            
        case OPT_PEAR:
            if (!function_class) {
                break;
            }
            
            /* fallthrough */
            
        default:
            goto newline;
    }
    
    /* prepend space */
    (*node)->Prepend();
    
    return;
    
newline:
    
    /* move short comment if any */
    *node = MoveShortComment(*node);
    
    /* prepend newline */
    (*node)->PrependNewline(-1 + add, half);
}

/* formats close curly bracket */
void CFormatter::FormatCloseCurlyBracket(CNode *node) {
    /* prepend newline */
    if (settings->indent_style == OPT_GNU) {
        node->PrependNewline(-1, true);
    } else if (settings->indent_style == OPT_WHITESMITHS) {
        node->PrependNewline();
    } else {
        node->PrependNewline(-1);
    }
}

/* moves short comments */
CNode *CFormatter::MoveShortComment(CNode *node) { //NOTE: changing!
    /* check if next is a comment and on the same line */
    if ((node->next->type == NT_SHORT_COMMENT) && (node->line == node->next->line)) {
        string token = node->token;
        
        /* convert token to comment */
        node->type  = NT_SHORT_COMMENT;
        node->token = node->next->token;
        
        /* and comment to token */
        node->next->type  = NT_TOKEN;
        node->next->token = token;
        
        return node->next;
    }
    
    return node;
}

/* definitions for formatting long comment */
#define CHAR_IS_NEWLINE(p)    (((*p == '\r') && (*(p + 1) != '\n')) || (*p == '\n'))
#define CHAR_IS_TABSSPACES(p) ((*p == '\t') || (*p == ' '))

/* formats long comments */
void CFormatter::FormatLongComment(CNode *node) {
    const char  *p   = node->token.c_str() + 2,
                *end = p + node->token.length() - 4;
    
    /* check whether comment is multiline and whether an extra space is needed */
    for (; p < end; p++) {
        if (CHAR_IS_NEWLINE(p)) {
            /* skip tabs and spaces */
            do { p++; } while (CHAR_IS_TABSSPACES(p));
            
            goto multiline;
        }
    }
    
    return;
    
multiline:
    
    string comment,
           newline = "\n" + GetIndent() + ((*p == '*') ? " " : "");
    
    for (p = node->token.c_str() + 2; p < end; p++) {
        if (CHAR_IS_NEWLINE(p)) {
            /* add newline */
            comment += newline;
            
            /* skip tabs and spaces */
            do { p++; } while (CHAR_IS_TABSSPACES(p));
            p--;
        } else if (*p != '\r') {
            comment += *p;
        }
    }
    
    node->token = "/*" + comment + "*/";
}

/* cleans structure expression for comment */
void CFormatter::AddStructureComment(CNode *expr, CNode *node) { //NOTE: changing!
    string comment  = "//";
    const char *p   = expr->token.c_str(),
               *end = p + expr->token.length();
    char        str = 0;
    
    //make sure there is next token
    scanner->ScanAhead();
    
    //TODO: 'old' structures -> no }, ; could be ?> (!)
    
    //return if there is already a comment, and it's on the same line,
    //or the node does not end with a curly bracket
    if (((node->next->type == NT_SHORT_COMMENT) && (node->next->line == node->line)) ||
        (node->token[node->token.length() - 1] != '}')) {
        
        return;
    }
    
    //skip starting spaces
    while (isspace(*p)) p++;
    
    //remove ending spaces
    while (isspace(*(end - 1))) end--;
    
    //walk through expression
    for (; p < end; p++) {
        //handle strings
        if (str) {
            //check for escaped characters
            if (*p == '\\') {
                comment += *p;
                p++;
            }
            
            //handle ?>, %> and </script \s* >
            else if (
                ((*(p - 1) == '?') || (*(p - 1) == '%')) && (*p == '>') ||
                !strncmp(p - 1, "</script", 8)
            ) {
                comment += " ";
            }
            
            //handle end of string
            else if (*p == str) {
                str = 0;
            }
        } else if ((*p == '\'') || (*p == '"')) {
            str = *p;
        }
        
        //skip short comments
        else if (((*p == '/') && (*(p + 1) == '/')) || (*p == '#')) {
            while (*p != '\n') p++;
            
            continue;
        }
        
        //skip long comments
        else if ((*p == '/') && (*(p + 1) == '*')) {
            while ((*p != '*') || (*(p + 1) != '/')) p++;
            p++;
            
            continue;
        }
        
        //skip double spaces
        if (isspace(*p)) {
            if (comment[comment.length() - 1] != ' ') {
                comment += ' ';
            }
            
            continue;
        }
        
        //add character
        comment += *p;
        
        // 'string', "string" //comment #comment and /* comment */
    }
    
    //create new node
    CNode *newnode = new CNode;
    if (newnode == NULL) {
        throw new CException(E_MEMORY);
    }
    
    //set type, token, line and next
    newnode->type  = NT_SHORT_COMMENT;
    newnode->token = comment;
    newnode->line  = node->line;
    newnode->next  = node->next;
    
    //set newnode as node its next
    node->next = newnode;
}
