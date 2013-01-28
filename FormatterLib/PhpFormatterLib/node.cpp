/*
 * Node class
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

#include "node.h"

#include "exception.h"
#include "formatter.h"
#include "scanner.h"
#include "settings.h"

extern CFormatter *formatter;
extern CScanner   *scanner;
extern CSettings  *settings;

/* constructor */
CNode::CNode(void) {
    next = NULL;
    
    type = NT_TOKEN;
}

/* destructor */
CNode::~CNode(void) {
    ;
}

/* appends a node */
void CNode::Append(CNode *last, bool newlines) {
    CNode *node,
          *temp;
    
    /* append nodes */
    if (next && last) { //NOTE: last / next never NULL? yup!
        string newline = "\n" + formatter->GetIndent();
        
        node = next;
        while (node) {
            switch (node->type) {
                case NT_SHORT_COMMENT:
                    if ((node->token[0] == '#') && settings->rewrite_perl_comments) { //NOTE change!
                        node->token.erase(0, 1);
                        node->token = "//" + node->token;
                    }
                    
                    if (line == node->line) {
                        if (token[token.length() - 1] != ' ') { //NOTE: when?? $a == comment $b
                            token += ' ';
                        }
                        
                        token += node->token;
                    } else {
                        token += newline + node->token;
                    }
                    
                    //what can follow this?
                    //a token
                    //a eof
                    //a long comment
                    //a short comment
                    //newlines
                    
                    //skip newlines if in no newlines mode
                    if (!newlines && (node->next->type == NT_NEWLINES)) {
                        node = node->next;
                    }
                    
                    //this is the real deal
                    
                    //token && !\n
                    //token && !eof
                    
                    //add indent to token, if not EOF
                    if ((node->next->type == NT_TOKEN) &&
                         node->next->token.length() && //NOTE: no EOF
                        (node->next->token[0] != '\n')) { //control structure, preceded by a comment
                        
                        //add extra indent to next line
                        token += "\n" + formatter->GetIndent(1); //NOTE: make option how much
                        
                        //shouldn't we do this in token mode?
                        //if (node->next->token[0] == ' ') {
                        //    node->next->token.erase(0, 1);
                        //}
                    } else if (node->next->type == NT_LONG_COMMENT) {
                        token += newline;
                    }
                    
                    //else if (node->next->type == NT_SHORT_COMMENT) {
                    //    token += "\n" + formatter->GetIndent(1);
                    //}
                    
                    break;
                    
                case NT_LONG_COMMENT: //TODO: indent each line; provide right spacing
                    //format long comment
                    formatter->FormatLongComment(node);
                    
                    //add newline if in newline mode
                    if (newlines) {
                        token += newline + node->token;
                    } else {
                        //add space if this there isn't one
                        if (!isspace(token[token.length() - 1])) {
                            token += ' ';
                        }
                        
                        //add long comment
                        token += node->token + ' ';
                        
                        //shouldn't we do this in token mode?
                        //if (node->next->token[0] != ' ') {
                        //    token += ' ';
                        //}
                    }
                    
                    break;
                    
                case NT_NEWLINES:
                    //add newlines if in newline mode
                    if (newlines) {
                        if (settings->indent_empty_lines) {
                            while (node->newlines--) {
                                token += newline;
                            }
                        } else {
                            while (node->newlines--) {
                                token += '\n';
                            }
                        }
                    }
                    
                    break;
                    
                default: //NT_TOKEN
                    //remove space if this token is indented by previous token
                    if ((node->token[0] == ' ') && isspace(token[token.length() - 1])) {
                        node->token.erase(0, 1);
                    }
                    
                    //add token
                    token += node->token;
                    
                    break;
            }
            
            line = node->line;
            
            if (node == last) {
                break;
            } else {
                temp = node;
                node = node->next;
                delete temp;
            }
        }
        
        next = last->next;
        delete last;
        
        if (next == NULL) {
            scanner->previous_node = this;
        }
    } else {
        if (!next) {
        	throw new CException(E_INTERNAL, string("Next = NULL! ") + token);
        } else {
        	throw new CException(E_INTERNAL, string("Last = NULL! ") + token);
        }
    }
}

/* prepends a newlines */
void CNode::PrependNewline(int add, bool half) {
    token = "\n" + formatter->GetIndent(add, half) + token;
}
