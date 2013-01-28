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

#ifndef _FORMATTER_H
#define _FORMATTER_H

#include "common.h"
#include "node.h"
#include "exception.h"

/* state enumeration */
enum EState {
    S_NONE,
    S_CONTROL_STRUCTURE,
    S_ELSE,
    S_CURLY_BRACKETS,
    S_BRACKETS
};

/* assignment structure */
struct SAssignment {
    CNode *var,
          *semicolon;
    uint   length;
};

class CFormatter {
    public:
        CFormatter(void);
        ~CFormatter(void);
        
        void Init(void);
        void Run(string &strOut);
        
        void   Write(CNode *);
        string GetIndent(int = 0, bool = false);
        
        void   AddAssignment(CNode *, CNode *semicolon);
        void   FormatAssignments(void);
        
        void   HandleSemicolon(CNode *);
        
        void   FormatOperator(CNode *, CNode *, CNode *, bool);
        void   FormatOpenCurlyBracket(CNode **, bool = false);
        void   FormatCloseCurlyBracket(CNode *);
        void   FormatLongComment(CNode *);
        
        CNode *MoveShortComment(CNode *);
        void   AddStructureComment(CNode *, CNode *);
        
        //FILE *file;
        
        uint indent;
        
        stack<SAssignment> assignments;
        uint maxvarlength;
        
        //vector<EState> states;
        stack<EState> states;
        
        CNode *first_node,
              *last_node;
};

/* writes node to file */
inline void CFormatter::Write(CNode *node) {
    uint length = node->token.length();
    
//     if (fwrite(node->token.c_str(), length, 1, file) != 1) {
//         throw new CException(E_INTERNAL, "Couldn\'t write output file!");
//     }
    
    //cout << "Written: " << length << " bytes.\n";
}

/* handles fake semicolons */
inline void CFormatter::HandleSemicolon(CNode *node) {
    /* check if it is a close tag */
    if (node->token[0] != ';') {
        node->token = ";\n" + node->token; //NOTE: changing!
    }
}

/* formats operators */
inline void CFormatter::FormatOperator(CNode *first, CNode *second, CNode *third, bool surround) {
    /* surround operator with spaces */
    if (surround) {
        second->Surround(' ');
    }
    
    /* join them in first */
    //first->Append(second);
    first->Append(third);
}

#endif
