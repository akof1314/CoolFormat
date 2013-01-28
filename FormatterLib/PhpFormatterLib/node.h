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

#ifndef _NODE_H
#define _NODE_H

#include "common.h"

/* node types enumeration */
enum ENodeType {
    NT_TOKEN,
    NT_SHORT_COMMENT,
    NT_LONG_COMMENT,
    NT_NEWLINES
};

class CNode {
    public:
        CNode(void);
        ~CNode(void);
        
        void Append(CNode *, bool = false);
        void Append(string);
        void Append(char = ' ');
        
        void PrependNewline(int = 0, bool = false);
        
        void Prepend(string);
        void Prepend(char = ' ');
        
        void Surround(string);
        void Surround(char = ' ');
        
        void FormatLongComment(void);
        
        ENodeType type;
        
        CNode *next;
        uint   line,
               newlines;
        string token;
};

/* appends a string */
inline void CNode::Append(string str) {
    /* append string */
    token += str;
}

/* appends a char */
inline void CNode::Append(char chr) {
    /* append char */
    token += chr;
}

/* prepends a string */
inline void CNode::Prepend(string str) {
    /* prepend string */
    token = str + token;
}

/* prepends a char */
inline void CNode::Prepend(char chr) {
    /* prepend char */
    token = chr + token;
}

/* surrounds node with string */
inline void CNode::Surround(string str) {
    /* surround with string */
    token = str + token + str;
}

/* surrounds node with a char */
inline void CNode::Surround(char chr) {
    /* surround with char */
    token = chr + token + chr;
}

#endif
