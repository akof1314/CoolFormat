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

#include "scanner.h"

#include "exception.h"
#include "tokens.h"
#include "settings.h"
#include "formatter.h"

extern CSettings  *settings;
extern CFormatter *formatter;

/* constructor */
CScanner::CScanner(void) {
    //file = NULL;
    
    bottom = token = limit = eof = top = cursor = marker = NULL;
    
    state = SS_HTML;
    
    line = 1;
    
    previous_node = NULL;
    
    in_short_tag = false;
    
    next_token = 0;
    next_node  = NULL;
}

/* destructor */
CScanner::~CScanner(void) {
    /* close file */
   /* if (file != NULL) {
        fclose(file);
    }*/
    
    /* free buffer */
    if (bottom != NULL) {
        free(bottom);
    }
}

/* init scanner */
void CScanner::Init(const char* pSourceIn) {
    /* open input file */
//     file = fopen(settings->input.c_str(), "r");
//     if (file == NULL) {
//         throw new CException(E_INTERNAL, "Couldn\'t open input file!");
//     }
	strInput = pSourceIn;
}

/* get lookahead token */
void CScanner::ScanAhead(void) {
    if (next_node == NULL) {
        next_token = Scan(&next_node);
    }
}

/*
 +---------+---------+---------------------+-------+
 bottom    token     limit                 eof     top
*/

/* fills buffer with data */
void CScanner::FillBuffer(void) {
    /* check if there is data left */
    if (!eof) {
        uint count;
        
        /* copy existing token, if any */
        if ((count = (token - bottom)) != 0) {
            memcpy(bottom, token, limit - token);
            
            token   = bottom;
            marker -= count;
            cursor -= count;
            limit  -= count;
        }
        
        /* enlarge buffer, if needed */
        if ((top - limit) < SCANNER_BUFFER) {
            uchar *buffer;
            
            /* allocate memory for buffer */
            buffer = (uchar *) malloc((limit - bottom) + SCANNER_BUFFER);
            if (buffer == NULL) {
                throw new CException(E_MEMORY);
            }
            
            memcpy(buffer, bottom, limit - bottom);
            
            /* change some pointers */
            marker = buffer + (marker - bottom);
            cursor = buffer + (cursor - bottom);
            limit  = buffer + (limit  - bottom);
            top    = limit  + SCANNER_BUFFER;
            
            /* free old buffer */
            if (bottom != NULL) {
                free(bottom);
            }
            
            /* set new one */
            token = bottom = buffer;
        }
        
        /* read new data, and set eof if EOF is reached */
        //if ((count = fread(limit, 1, SCANNER_BUFFER, file)) != SCANNER_BUFFER) {
        //    //TODO: an error could have been occured: ferror!
        //    
        //    eof    = limit + count;
        //    eof[0] = '\0';
        //}
		if (strInput.size() >= SCANNER_BUFFER - 1)
		{
			//_mbscpy(limit,(unsigned char*)((strInput.substr(0,SCANNER_BUFFER - 1)).c_str()));
			strcpy((char *)limit, (char *)(unsigned char*)((strInput.substr(0,SCANNER_BUFFER - 1)).c_str()));
			count = SCANNER_BUFFER -1;
		}
		else
		{
			//_mbscpy(limit,(unsigned char*)(strInput.c_str()));
			strcpy((char *)limit, (char *)(unsigned char*)(strInput.c_str()));
			count = strInput.size();
		}
		if ( count != SCANNER_BUFFER - 1){    
			eof    = limit + count;
			eof[0] = '\0';
		}else
			strInput = strInput.substr(SCANNER_BUFFER - 1);
        /* update limit */
        limit += count;
    }
}

/* adds newlines in a string to line */
uint CScanner::CountNewlines(string *string) {
    const char *p   = string->c_str(),
               *end = p + string->length();
    uint        newlines = 0;
    
    /* count newlines */
    for (; p < end; p++) {
        if ((*p == '\n') || ((*p == '\r') && ((p + 1) < end) && (*(p + 1) != '\n'))) {
            newlines++;
        }
    }
    
    return newlines;
}

/* adds newlines in a string to line */
inline void CScanner::AddNewlines(string *string) {
    line += CountNewlines(string);
}

/* creates a string from a token */
inline void CScanner::TokenNode(CNode *node) {
    /* append token */
    node->token = "";
    node->token.append((char *) token, cursor - token);
    
    /* set line */
    node->line = line;
}

/* disable var never used warning: re2c never uses yych and yyaccept */
//#pragma warn -8004

/* generates tokens from file */
int CScanner::Scan(CNode **node) {
    uint start_line;
    
    string label;
    
    /* handle lookahead token */
    if (next_node) {
        (*node) = next_node;
        next_node = NULL;
        
        return next_token;
    }
    
again:
    
    /* create new node */
    *node = new CNode();
    if (*node == NULL) {
        throw new CException(E_MEMORY);
    }
    
    /* set previous node its next */
    if (previous_node != NULL) {
        previous_node->next = *node;
    } else {
        formatter->first_node = *node;
    }
    
    /* set new previous node */
    previous_node = *node;
    
    /* return to state */
    switch (state) {
        case SS_PHP:
            goto php;
            
        case SS_OBJECT_PROPERTY:
            goto object_property;
            
        case SS_HALT_COMPILER:
            goto halt_compiler;
        
        //default: SS_HTML
    }
    
    /* loop until a token is found */
    while (true) {
html:
        /* set current token */
        token = cursor;
        

        {
            uchar chr;
            unsigned int accept = 0;
            static const unsigned char bm[] = {
                  0,  64,  64,  64,  64,  64,  64,  64, 
                 64, 192, 192,  64,  64, 192,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                192,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,   0,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
                 64,  64,  64,  64,  64,  64,  64,  64, 
            };

            if((limit - cursor) < 8) FillBuffer();
            chr = *cursor;
            if(bm[0+chr] & 64) {
                goto state_4;
            }
            if(chr <= 0x00) goto state_6;
            goto state_3;
state_2:
            {
                TokenNode(*node);
                AddNewlines(&((*node)->token));
                
                return T_INLINE_HTML;
            }
state_3:
            chr = *++cursor;
            if(chr <= '>') {
                if(chr <= '%') {
                    if(chr <= '$') goto state_5;
                    goto state_14;
                } else {
                    if(chr == '<') goto state_2;
                    goto state_5;
                }
            } else {
                if(chr <= 'S') {
                    if(chr <= '?') goto state_12;
                    if(chr <= 'R') goto state_5;
                    goto state_11;
                } else {
                    if(chr == 's') goto state_10;
                    goto state_5;
                }
            }
state_4:
            accept = 0;
            marker = ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
state_5:
            if(bm[0+chr] & 64) {
                goto state_4;
            }
            if(chr <= 0x00) goto state_2;
            goto state_8;
state_6:
            ++cursor;
            {
                formatter->last_node = *node;
                
                return 0;
            }
state_8:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
            if(chr <= '<') {
                if(chr <= '$') {
                    if(chr >= 0x01) goto state_4;
                } else {
                    if(chr <= '%') goto state_9;
                    if(chr <= ';') goto state_4;
                }
            } else {
                if(chr <= '?') {
                    if(chr <= '>') goto state_4;
                } else {
                    if(chr != 's') goto state_4;
                }
            }
state_9:
            cursor = marker;
            if(accept <= 1) {
                if(accept <= 0) {
                    goto state_2;
                } else {
                    goto state_13;
                }
            } else {
                goto state_47;
            }
state_10:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'C') goto state_54;
            if(chr == 'c') goto state_54;
            goto state_2;
state_11:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'C') goto state_22;
            if(chr == 'c') goto state_22;
            goto state_5;
state_12:
            accept = 1;
            chr = *(marker = ++cursor);
            if(chr <= 'O') {
                if(chr == '=') goto state_16;
            } else {
                if(chr <= 'P') goto state_18;
                if(chr == 'p') goto state_18;
            }
state_13:
            {
                TokenNode(*node);
                
                if (settings->short_tags) {
                    state = SS_PHP;
                    
                    if (settings->rewrite_short_tag) {
                        (*node)->token = "<?php"; //NOTE change!
                    }
                    
                    in_short_tag = false;
                    
                    return T_OPEN_TAG;
                } else {
                    return T_INLINE_HTML;
                }
            }
state_14:
            ++cursor;
            if((chr = *cursor) == '=') goto state_16;
            {
                TokenNode(*node);
                
                if (settings->asp_tags) {
                    state = SS_PHP;
                    
                    if (settings->rewrite_short_tag) {
                        (*node)->token = "<?php"; //NOTE change!
                    }
                    
                    in_short_tag = false;
                    
                    return T_OPEN_TAG;
                } else {
                    return T_INLINE_HTML;
                }
            }
state_16:
            ++cursor;
            {
                TokenNode(*node);
                
                if (((token[1] == '%') && settings->asp_tags) || settings->short_tags) {
                    state = SS_PHP;
                    
                    in_short_tag = true;
                    
                    return T_OPEN_TAG_WITH_ECHO;
                } else {
                    return T_INLINE_HTML;
                }
            }
state_18:
            chr = *++cursor;
            if(chr == 'H') goto state_19;
            if(chr != 'h') goto state_9;
state_19:
            chr = *++cursor;
            if(chr == 'P') goto state_20;
            if(chr != 'p') goto state_9;
state_20:
            ++cursor;
            {
                TokenNode(*node);
                
                state = SS_PHP;
                
                in_short_tag = false;
                
                return T_OPEN_TAG;
            }
state_22:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'R') goto state_23;
            if(chr != 'r') goto state_5;
state_23:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'I') goto state_24;
            if(chr != 'i') goto state_5;
state_24:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'P') goto state_25;
            if(chr != 'p') goto state_5;
state_25:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'T') goto state_26;
            if(chr != 't') goto state_5;
state_26:
            accept = 0;
            chr = *(marker = ++cursor);
            if(bm[0+chr] & 128) {
                goto state_27;
            }
            goto state_5;
state_27:
            accept = 0;
            marker = ++cursor;
            if((limit - cursor) < 8) FillBuffer();
            chr = *cursor;
            if(bm[0+chr] & 128) {
                goto state_27;
            }
            if(chr <= 'K') {
                if(chr <= 0x00) goto state_2;
                if(chr == '<') goto state_8;
                goto state_4;
            } else {
                if(chr <= 'L') goto state_29;
                if(chr != 'l') goto state_4;
            }
state_29:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'A') goto state_30;
            if(chr != 'a') goto state_5;
state_30:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'N') goto state_31;
            if(chr != 'n') goto state_5;
state_31:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'G') goto state_32;
            if(chr != 'g') goto state_5;
state_32:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'U') goto state_33;
            if(chr != 'u') goto state_5;
state_33:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'A') goto state_34;
            if(chr != 'a') goto state_5;
state_34:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'G') goto state_35;
            if(chr != 'g') goto state_5;
state_35:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'E') goto state_36;
            if(chr != 'e') goto state_5;
state_36:
            accept = 0;
            marker = ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
            if(chr <= 0x0D) {
                if(chr <= 0x08) {
                    if(chr <= 0x00) goto state_2;
                    goto state_4;
                } else {
                    if(chr <= 0x0A) goto state_36;
                    if(chr <= 0x0C) goto state_4;
                    goto state_36;
                }
            } else {
                if(chr <= ';') {
                    if(chr == ' ') goto state_36;
                    goto state_4;
                } else {
                    if(chr <= '<') goto state_8;
                    if(chr >= '>') goto state_4;
                }
            }
state_38:
            accept = 0;
            marker = ++cursor;
            if((limit - cursor) < 5) FillBuffer();
            chr = *cursor;
            if(chr <= '"') {
                if(chr <= 0x0C) {
                    if(chr <= 0x00) goto state_2;
                    if(chr <= 0x08) goto state_4;
                    if(chr <= 0x0A) goto state_38;
                    goto state_4;
                } else {
                    if(chr <= 0x1F) {
                        if(chr <= 0x0D) goto state_38;
                        goto state_4;
                    } else {
                        if(chr <= ' ') goto state_38;
                        if(chr <= '!') goto state_4;
                    }
                }
            } else {
                if(chr <= '<') {
                    if(chr == '\'') goto state_41;
                    if(chr <= ';') goto state_4;
                    goto state_8;
                } else {
                    if(chr <= 'P') {
                        if(chr <= 'O') goto state_4;
                        goto state_42;
                    } else {
                        if(chr == 'p') goto state_42;
                        goto state_4;
                    }
                }
            }
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'P') goto state_51;
            if(chr == 'p') goto state_51;
            goto state_5;
state_41:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'P') goto state_48;
            if(chr == 'p') goto state_48;
            goto state_5;
state_42:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'H') goto state_43;
            if(chr != 'h') goto state_5;
state_43:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'P') goto state_44;
            if(chr != 'p') goto state_5;
state_44:
            accept = 0;
            marker = ++cursor;
            if((limit - cursor) < 2) FillBuffer();
            chr = *cursor;
            if(chr <= 0x1F) {
                if(chr <= 0x0A) {
                    if(chr <= 0x00) goto state_2;
                    if(chr <= 0x08) goto state_4;
                    goto state_44;
                } else {
                    if(chr == 0x0D) goto state_44;
                    goto state_4;
                }
            } else {
                if(chr <= '<') {
                    if(chr <= ' ') goto state_44;
                    if(chr <= ';') goto state_4;
                    goto state_8;
                } else {
                    if(chr != '>') goto state_4;
                }
            }
            accept = 2;
            chr = *(marker = ++cursor);
            if(chr >= 0x01) goto state_5;
state_47:
            {
                TokenNode(*node);
                AddNewlines(&((*node)->token));
                
                //change to <?php ?
                
                state = SS_PHP;
                
                in_short_tag = false;
                
                return T_OPEN_TAG;
            }
state_48:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'H') goto state_49;
            if(chr != 'h') goto state_5;
state_49:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'P') goto state_50;
            if(chr != 'p') goto state_5;
state_50:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == '\'') goto state_44;
            goto state_5;
state_51:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'H') goto state_52;
            if(chr != 'h') goto state_5;
state_52:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == 'P') goto state_53;
            if(chr != 'p') goto state_5;
state_53:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr == '"') goto state_44;
            goto state_5;
state_54:
            chr = *++cursor;
            if(chr == 'R') goto state_55;
            if(chr != 'r') goto state_9;
state_55:
            chr = *++cursor;
            if(chr == 'I') goto state_56;
            if(chr != 'i') goto state_9;
state_56:
            chr = *++cursor;
            if(chr == 'P') goto state_57;
            if(chr != 'p') goto state_9;
state_57:
            chr = *++cursor;
            if(chr == 'T') goto state_58;
            if(chr != 't') goto state_9;
state_58:
            chr = *++cursor;
            if(chr == 'L') goto state_9;
            if(chr == 'l') goto state_9;
            goto state_60;
state_59:
            ++cursor;
            if((limit - cursor) < 8) FillBuffer();
            chr = *cursor;
state_60:
            if(chr <= 0x1F) {
                if(chr <= 0x0A) {
                    if(chr <= 0x08) goto state_9;
                    goto state_59;
                } else {
                    if(chr == 0x0D) goto state_59;
                    goto state_9;
                }
            } else {
                if(chr <= 'L') {
                    if(chr <= ' ') goto state_59;
                    if(chr <= 'K') goto state_9;
                } else {
                    if(chr != 'l') goto state_9;
                }
            }
            chr = *++cursor;
            if(chr == 'A') goto state_62;
            if(chr != 'a') goto state_9;
state_62:
            chr = *++cursor;
            if(chr == 'N') goto state_63;
            if(chr != 'n') goto state_9;
state_63:
            chr = *++cursor;
            if(chr == 'G') goto state_64;
            if(chr != 'g') goto state_9;
state_64:
            chr = *++cursor;
            if(chr == 'U') goto state_65;
            if(chr != 'u') goto state_9;
state_65:
            chr = *++cursor;
            if(chr == 'A') goto state_66;
            if(chr != 'a') goto state_9;
state_66:
            chr = *++cursor;
            if(chr == 'G') goto state_67;
            if(chr != 'g') goto state_9;
state_67:
            chr = *++cursor;
            if(chr == 'E') goto state_68;
            if(chr != 'e') goto state_9;
state_68:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
            if(chr <= 0x0D) {
                if(chr <= 0x08) goto state_9;
                if(chr <= 0x0A) goto state_68;
                if(chr <= 0x0C) goto state_9;
                goto state_68;
            } else {
                if(chr <= ' ') {
                    if(chr <= 0x1F) goto state_9;
                    goto state_68;
                } else {
                    if(chr != '=') goto state_9;
                }
            }
state_70:
            ++cursor;
            if((limit - cursor) < 5) FillBuffer();
            chr = *cursor;
            if(chr <= '!') {
                if(chr <= 0x0C) {
                    if(chr <= 0x08) goto state_9;
                    if(chr <= 0x0A) goto state_70;
                    goto state_9;
                } else {
                    if(chr <= 0x0D) goto state_70;
                    if(chr == ' ') goto state_70;
                    goto state_9;
                }
            } else {
                if(chr <= 'O') {
                    if(chr <= '"') goto state_73;
                    if(chr == '\'') goto state_74;
                    goto state_9;
                } else {
                    if(chr <= 'P') goto state_72;
                    if(chr != 'p') goto state_9;
                }
            }
state_72:
            chr = *++cursor;
            if(chr == 'H') goto state_84;
            if(chr == 'h') goto state_84;
            goto state_9;
state_73:
            chr = *++cursor;
            if(chr == 'P') goto state_81;
            if(chr == 'p') goto state_81;
            goto state_9;
state_74:
            chr = *++cursor;
            if(chr == 'P') goto state_75;
            if(chr != 'p') goto state_9;
state_75:
            chr = *++cursor;
            if(chr == 'H') goto state_76;
            if(chr != 'h') goto state_9;
state_76:
            chr = *++cursor;
            if(chr == 'P') goto state_77;
            if(chr != 'p') goto state_9;
state_77:
            chr = *++cursor;
            if(chr != '\'') goto state_9;
state_78:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
            if(chr <= 0x0D) {
                if(chr <= 0x08) goto state_9;
                if(chr <= 0x0A) goto state_78;
                if(chr <= 0x0C) goto state_9;
                goto state_78;
            } else {
                if(chr <= ' ') {
                    if(chr <= 0x1F) goto state_9;
                    goto state_78;
                } else {
                    if(chr != '>') goto state_9;
                }
            }
            chr = *++cursor;
            goto state_47;
state_81:
            chr = *++cursor;
            if(chr == 'H') goto state_82;
            if(chr != 'h') goto state_9;
state_82:
            chr = *++cursor;
            if(chr == 'P') goto state_83;
            if(chr != 'p') goto state_9;
state_83:
            chr = *++cursor;
            if(chr == '"') goto state_78;
            goto state_9;
state_84:
            ++cursor;
            if((chr = *cursor) == 'P') goto state_78;
            if(chr == 'p') goto state_78;
            goto state_9;
        }

php:
        /* set current token */
        token = cursor;
        

        {
            uchar chr;
            unsigned int accept = 0;
            static const unsigned char bm[] = {
                  0,   0,   0,   0,   0,   0,   0,   0, 
                  0,  24,  16,   0,   0,  16,   0,   0, 
                  0,   0,   0,   0,   0,   0,   0,   0, 
                  0,   0,   0,   0,   0,   0,   0,   0, 
                 24,   0,   0,   0,   0,   0,   0,   0, 
                  0,   0,   0,   0,   0,   0,   0,   0, 
                224, 224, 224, 224, 224, 224, 224, 224, 
                224, 224,   0,   0,   0,   0,   0,   0, 
                  0, 160, 160, 160, 160, 160, 160,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,   0,   0,   0,   0,  32, 
                  0, 160, 160, 160, 160, 160, 160,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,   0,   0,   0,   0,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
                 32,  32,  32,  32,  32,  32,  32,  32, 
            };
            if((limit - cursor) < 16) FillBuffer();
            chr = *cursor;
            switch(chr) {
            case 0x00:    goto state_146;
            case 0x01:
            case 0x02:
            case 0x03:
            case 0x04:
            case 0x05:
            case 0x06:
            case 0x07:
            case 0x08:
            case 0x0B:
            case 0x0C:
            case 0x0E:
            case 0x0F:
            case 0x10:
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x14:
            case 0x15:
            case 0x16:
            case 0x17:
            case 0x18:
            case 0x19:
            case 0x1A:
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x1E:
            case 0x1F:
            case '\\':    goto state_145;
            case 0x09:
            case ' ':    goto state_144;
            case 0x0A:    goto state_142;
            case 0x0D:    goto state_140;
            case '!':    goto state_118;
            case '"':    goto state_136;
            case '#':    goto state_138;
            case '$':    goto state_129;
            case '%':    goto state_91;
            case '&':    goto state_123;
            case '\'':    goto state_134;
            case '(':    goto state_113;
            case ')':
            case ',':
            case ';':
            case '@':
            case '[':
            case ']':
            case '{':
            case '}':
            case '~':    goto state_130;
            case '*':    goto state_120;
            case '+':    goto state_117;
            case '-':    goto state_115;
            case '.':    goto state_122;
            case '/':    goto state_121;
            case '0':    goto state_126;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':    goto state_128;
            case ':':    goto state_116;
            case '<':    goto state_90;
            case '=':    goto state_114;
            case '>':    goto state_119;
            case '?':    goto state_88;
            case 'A':
            case 'a':    goto state_101;
            case 'B':
            case 'b':    goto state_103;
            case 'C':
            case 'c':    goto state_96;
            case 'D':
            case 'd':    goto state_94;
            case 'E':
            case 'e':    goto state_92;
            case 'F':
            case 'f':    goto state_95;
            case 'G':
            case 'g':    goto state_108;
            case 'I':
            case 'i':    goto state_99;
            case 'L':
            case 'l':    goto state_110;
            case 'N':
            case 'n':    goto state_105;
            case 'O':
            case 'o':    goto state_111;
            case 'P':
            case 'p':    goto state_104;
            case 'R':
            case 'r':    goto state_97;
            case 'S':
            case 's':    goto state_102;
            case 'T':
            case 't':    goto state_98;
            case 'U':
            case 'u':    goto state_107;
            case 'V':
            case 'v':    goto state_106;
            case 'W':
            case 'w':    goto state_100;
            case 'X':
            case 'x':    goto state_112;
            case '^':    goto state_125;
            case '_':    goto state_109;
            case '`':    goto state_132;
            case '|':    goto state_124;
            default:    goto state_131;
            }
state_87:
            {
                goto php;
            }
state_88:
            ++cursor;
            if((chr = *cursor) == '>') goto state_663;
state_89:
            {
                TokenNode(*node);
                
                return token[0];
            }
state_90:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr <= ';') {
                if(chr == '/') goto state_655;
                goto state_89;
            } else {
                if(chr <= '<') goto state_650;
                if(chr <= '=') goto state_652;
                if(chr <= '>') goto state_654;
                goto state_89;
            }
state_91:
            chr = *++cursor;
            if(chr <= '<') goto state_89;
            if(chr <= '=') goto state_646;
            if(chr <= '>') goto state_648;
            goto state_89;
state_92:
            ++cursor;
            switch((chr = *cursor)) {
            case 'C':
            case 'c':    goto state_581;
            case 'L':
            case 'l':    goto state_582;
            case 'M':
            case 'm':    goto state_583;
            case 'N':
            case 'n':    goto state_584;
            case 'V':
            case 'v':    goto state_585;
            case 'X':
            case 'x':    goto state_586;
            default:    goto state_153;
            }
state_93:
            {
                TokenNode(*node);
                
                return T_STRING;
            }
state_94:
            chr = *++cursor;
            if(chr <= 'O') {
                if(chr <= 'H') {
                    if(chr == 'E') goto state_563;
                    goto state_153;
                } else {
                    if(chr <= 'I') goto state_564;
                    if(chr <= 'N') goto state_153;
                    goto state_565;
                }
            } else {
                if(chr <= 'h') {
                    if(chr == 'e') goto state_563;
                    goto state_153;
                } else {
                    if(chr <= 'i') goto state_564;
                    if(chr == 'o') goto state_565;
                    goto state_153;
                }
            }
state_95:
            chr = *++cursor;
            if(chr <= 'U') {
                if(chr <= 'N') {
                    if(chr == 'I') goto state_542;
                    goto state_153;
                } else {
                    if(chr <= 'O') goto state_543;
                    if(chr <= 'T') goto state_153;
                    goto state_544;
                }
            } else {
                if(chr <= 'n') {
                    if(chr == 'i') goto state_542;
                    goto state_153;
                } else {
                    if(chr <= 'o') goto state_543;
                    if(chr == 'u') goto state_544;
                    goto state_153;
                }
            }
state_96:
            chr = *++cursor;
            if(chr <= 'O') {
                if(chr <= 'K') {
                    if(chr == 'A') goto state_514;
                    goto state_153;
                } else {
                    if(chr <= 'L') goto state_515;
                    if(chr <= 'N') goto state_153;
                    goto state_516;
                }
            } else {
                if(chr <= 'k') {
                    if(chr == 'a') goto state_514;
                    goto state_153;
                } else {
                    if(chr <= 'l') goto state_515;
                    if(chr == 'o') goto state_516;
                    goto state_153;
                }
            }
state_97:
            chr = *++cursor;
            if(chr == 'E') goto state_496;
            if(chr == 'e') goto state_496;
            goto state_153;
state_98:
            chr = *++cursor;
            if(chr <= 'R') {
                if(chr == 'H') goto state_488;
                if(chr <= 'Q') goto state_153;
                goto state_489;
            } else {
                if(chr <= 'h') {
                    if(chr <= 'g') goto state_153;
                    goto state_488;
                } else {
                    if(chr == 'r') goto state_489;
                    goto state_153;
                }
            }
state_99:
            chr = *++cursor;
            if(chr <= 'S') {
                if(chr <= 'L') {
                    if(chr == 'F') goto state_441;
                    goto state_153;
                } else {
                    if(chr <= 'M') goto state_443;
                    if(chr <= 'N') goto state_444;
                    if(chr <= 'R') goto state_153;
                    goto state_445;
                }
            } else {
                if(chr <= 'm') {
                    if(chr == 'f') goto state_441;
                    if(chr <= 'l') goto state_153;
                    goto state_443;
                } else {
                    if(chr <= 'n') goto state_444;
                    if(chr == 's') goto state_445;
                    goto state_153;
                }
            }
state_100:
            chr = *++cursor;
            if(chr == 'H') goto state_436;
            if(chr == 'h') goto state_436;
            goto state_153;
state_101:
            chr = *++cursor;
            if(chr <= 'S') {
                if(chr <= 'M') {
                    if(chr == 'B') goto state_418;
                    goto state_153;
                } else {
                    if(chr <= 'N') goto state_419;
                    if(chr <= 'Q') goto state_153;
                    if(chr <= 'R') goto state_420;
                    goto state_421;
                }
            } else {
                if(chr <= 'n') {
                    if(chr == 'b') goto state_418;
                    if(chr <= 'm') goto state_153;
                    goto state_419;
                } else {
                    if(chr <= 'q') goto state_153;
                    if(chr <= 'r') goto state_420;
                    if(chr <= 's') goto state_421;
                    goto state_153;
                }
            }
state_102:
            chr = *++cursor;
            if(chr <= 'W') {
                if(chr == 'T') goto state_406;
                if(chr <= 'V') goto state_153;
                goto state_407;
            } else {
                if(chr <= 't') {
                    if(chr <= 's') goto state_153;
                    goto state_406;
                } else {
                    if(chr == 'w') goto state_407;
                    goto state_153;
                }
            }
state_103:
            chr = *++cursor;
            if(chr == 'R') goto state_401;
            if(chr == 'r') goto state_401;
            goto state_153;
state_104:
            chr = *++cursor;
            if(chr <= 'U') {
                if(chr == 'R') goto state_377;
                if(chr <= 'T') goto state_153;
                goto state_378;
            } else {
                if(chr <= 'r') {
                    if(chr <= 'q') goto state_153;
                    goto state_377;
                } else {
                    if(chr == 'u') goto state_378;
                    goto state_153;
                }
            }
state_105:
            chr = *++cursor;
            if(chr == 'E') goto state_374;
            if(chr == 'e') goto state_374;
            goto state_153;
state_106:
            chr = *++cursor;
            if(chr == 'A') goto state_371;
            if(chr == 'a') goto state_371;
            goto state_153;
state_107:
            chr = *++cursor;
            if(chr <= 'S') {
                if(chr == 'N') goto state_363;
                if(chr <= 'R') goto state_153;
                goto state_364;
            } else {
                if(chr <= 'n') {
                    if(chr <= 'm') goto state_153;
                    goto state_363;
                } else {
                    if(chr == 's') goto state_364;
                    goto state_153;
                }
            }
state_108:
            chr = *++cursor;
            if(chr == 'L') goto state_357;
            if(chr == 'l') goto state_357;
            goto state_153;
state_109:
            chr = *++cursor;
            if(chr == '_') goto state_301;
            goto state_153;
state_110:
            chr = *++cursor;
            if(chr == 'I') goto state_297;
            if(chr == 'i') goto state_297;
            goto state_153;
state_111:
            chr = *++cursor;
            if(chr == 'R') goto state_295;
            if(chr == 'r') goto state_295;
            goto state_153;
state_112:
            chr = *++cursor;
            if(chr == 'O') goto state_292;
            if(chr == 'o') goto state_292;
            goto state_153;
state_113:
            accept = 0;
            chr = *(marker = ++cursor);
            if(chr <= 'S') {
                if(chr <= 'D') {
                    if(chr <= ' ') {
                        if(chr == 0x09) goto state_221;
                        if(chr <= 0x1F) goto state_89;
                        goto state_221;
                    } else {
                        if(chr <= '@') goto state_89;
                        if(chr == 'C') goto state_89;
                        goto state_221;
                    }
                } else {
                    if(chr <= 'I') {
                        if(chr == 'F') goto state_221;
                        if(chr <= 'H') goto state_89;
                        goto state_221;
                    } else {
                        if(chr == 'O') goto state_221;
                        if(chr <= 'Q') goto state_89;
                        goto state_221;
                    }
                }
            } else {
                if(chr <= 'f') {
                    if(chr <= 'b') {
                        if(chr == 'U') goto state_221;
                        if(chr <= '`') goto state_89;
                        goto state_221;
                    } else {
                        if(chr == 'd') goto state_221;
                        if(chr <= 'e') goto state_89;
                        goto state_221;
                    }
                } else {
                    if(chr <= 'o') {
                        if(chr == 'i') goto state_221;
                        if(chr <= 'n') goto state_89;
                        goto state_221;
                    } else {
                        if(chr <= 's') {
                            if(chr <= 'q') goto state_89;
                            goto state_221;
                        } else {
                            if(chr == 'u') goto state_221;
                            goto state_89;
                        }
                    }
                }
            }
state_114:
            chr = *++cursor;
            if(chr <= '<') goto state_89;
            if(chr <= '=') goto state_214;
            if(chr <= '>') goto state_216;
            goto state_89;
state_115:
            chr = *++cursor;
            if(chr <= '<') {
                if(chr == '-') goto state_210;
                goto state_89;
            } else {
                if(chr <= '=') goto state_208;
                if(chr <= '>') goto state_212;
                goto state_89;
            }
state_116:
            chr = *++cursor;
            if(chr == ':') goto state_206;
            goto state_89;
state_117:
            chr = *++cursor;
            if(chr == '+') goto state_204;
            if(chr == '=') goto state_202;
            goto state_89;
state_118:
            chr = *++cursor;
            if(chr == '=') goto state_198;
            goto state_89;
state_119:
            chr = *++cursor;
            if(chr <= '<') goto state_89;
            if(chr <= '=') goto state_194;
            if(chr <= '>') goto state_192;
            goto state_89;
state_120:
            chr = *++cursor;
            if(chr == '=') goto state_190;
            goto state_89;
state_121:
            chr = *++cursor;
            if(chr <= '.') {
                if(chr == '*') goto state_186;
                goto state_89;
            } else {
                if(chr <= '/') goto state_185;
                if(chr == '=') goto state_188;
                goto state_89;
            }
state_122:
            chr = *++cursor;
            if(chr <= '/') goto state_89;
            if(chr <= '9') goto state_181;
            if(chr == '=') goto state_183;
            goto state_89;
state_123:
            chr = *++cursor;
            if(chr == '&') goto state_177;
            if(chr == '=') goto state_179;
            goto state_89;
state_124:
            chr = *++cursor;
            if(chr == '=') goto state_175;
            if(chr == '|') goto state_173;
            goto state_89;
state_125:
            chr = *++cursor;
            if(chr == '=') goto state_171;
            goto state_89;
state_126:
            accept = 1;
            chr = *(marker = ++cursor);
            if(chr <= 'E') {
                if(chr <= '/') {
                    if(chr == '.') goto state_157;
                } else {
                    if(chr <= '9') goto state_160;
                    if(chr >= 'E') goto state_162;
                }
            } else {
                if(chr <= 'd') {
                    if(chr == 'X') goto state_167;
                } else {
                    if(chr <= 'e') goto state_162;
                    if(chr == 'x') goto state_167;
                }
            }
state_127:
            {
                TokenNode(*node);
                
                return T_LNUMBER;
            }
state_128:
            accept = 1;
            chr = *(marker = ++cursor);
            if(chr <= '9') {
                if(chr == '.') goto state_157;
                if(chr <= '/') goto state_127;
                goto state_160;
            } else {
                if(chr <= 'E') {
                    if(chr <= 'D') goto state_127;
                    goto state_162;
                } else {
                    if(chr == 'e') goto state_162;
                    goto state_127;
                }
            }
state_129:
            chr = *++cursor;
            if(chr <= '_') {
                if(chr <= '@') goto state_89;
                if(chr <= 'Z') goto state_154;
                if(chr <= '^') goto state_89;
                goto state_154;
            } else {
                if(chr <= '`') goto state_89;
                if(chr <= 'z') goto state_154;
                if(chr <= '~') goto state_89;
                goto state_154;
            }
state_130:
            chr = *++cursor;
            goto state_89;
state_131:
            chr = *++cursor;
            goto state_153;
state_132:
            ++cursor;
            {
                start_line = line;
                
                goto back_quote_string;
            }
state_134:
            ++cursor;
            {
                start_line = line;
                
                goto single_quote_string;
            }
state_136:
            ++cursor;
            {
                start_line = line;
                
                goto double_quote_string;
            }
state_138:
            ++cursor;
state_139:
            {
                goto short_comment;
            }
state_140:
            ++cursor;
            if((chr = *cursor) == 0x0A) goto state_150;
state_141:
            {
                //TODO: free node? nope
                
                string msg = "Unexpected character in input: '";
                msg += (char) token[0];
                msg += "' (ASCII=";
                msg += int_to_string(token[0]);
                msg += ")!";
                
                throw new CException(E_SOURCE, msg);
            }
state_142:
            ++cursor;
            chr = *cursor;
            goto state_151;
state_143:
            {
                TokenNode(*node);
                
                //make function of node
                line += (*node)->newlines = CountNewlines(&((*node)->token));
                
                if (!(--((*node)->newlines)) || settings->remove_empty_lines) {
                    goto php;
                }
                
                (*node)->type = NT_NEWLINES;
                
                previous_node = *node;
                
                goto again;
            }
state_144:
            chr = *++cursor;
            goto state_149;
state_145:
            chr = *++cursor;
            goto state_141;
state_146:
            ++cursor;
            {
                formatter->last_node = *node;
                
                return 0;
            }
state_148:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
state_149:
            if(bm[0+chr] & 8) {
                goto state_148;
            }
            goto state_87;
state_150:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
state_151:
            if(bm[0+chr] & 16) {
                goto state_150;
            }
            goto state_143;
state_152:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
state_153:
            if(bm[0+chr] & 32) {
                goto state_152;
            }
            goto state_93;
state_154:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
            if(chr <= '^') {
                if(chr <= '9') {
                    if(chr >= '0') goto state_154;
                } else {
                    if(chr <= '@') goto state_156;
                    if(chr <= 'Z') goto state_154;
                }
            } else {
                if(chr <= '`') {
                    if(chr <= '_') goto state_154;
                } else {
                    if(chr <= 'z') goto state_154;
                    if(chr >= 0x7F) goto state_154;
                }
            }
state_156:
            {
                TokenNode(*node);
                
                return T_VARIABLE;
            }
state_157:
            accept = 2;
            marker = ++cursor;
            if((limit - cursor) < 3) FillBuffer();
            chr = *cursor;
            if(bm[0+chr] & 64) {
                goto state_157;
            }
            if(chr == 'E') goto state_162;
            if(chr == 'e') goto state_162;
state_159:
            {
                TokenNode(*node);
                
                return T_DNUMBER;
            }
state_160:
            accept = 1;
            marker = ++cursor;
            if((limit - cursor) < 3) FillBuffer();
            chr = *cursor;
            if(chr <= '9') {
                if(chr == '.') goto state_157;
                if(chr <= '/') goto state_127;
                goto state_160;
            } else {
                if(chr <= 'E') {
                    if(chr <= 'D') goto state_127;
                } else {
                    if(chr != 'e') goto state_127;
                }
            }
state_162:
            chr = *++cursor;
            if(chr <= ',') {
                if(chr == '+') goto state_164;
            } else {
                if(chr <= '-') goto state_164;
                if(chr <= '/') goto state_163;
                if(chr <= '9') goto state_165;
            }
state_163:
            cursor = marker;
            if(accept <= 1) {
                if(accept <= 0) {
                    goto state_89;
                } else {
                    goto state_127;
                }
            } else {
                if(accept <= 2) {
                    goto state_159;
                } else {
                    goto state_651;
                }
            }
state_164:
            chr = *++cursor;
            if(chr <= '/') goto state_163;
            if(chr >= ':') goto state_163;
state_165:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
            if(chr <= '/') goto state_159;
            if(chr <= '9') goto state_165;
            goto state_159;
state_167:
            chr = *++cursor;
            if(bm[0+chr] & 128) {
                goto state_168;
            }
            goto state_163;
state_168:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
            if(bm[0+chr] & 128) {
                goto state_168;
            }
            {
                TokenNode(*node);
                
                return T_LNUMBER;
            }
state_171:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_XOR_EQUAL;
            }
state_173:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_BOOLEAN_OR;
            }
state_175:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_OR_EQUAL;
            }
state_177:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_BOOLEAN_AND;
            }
state_179:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_AND_EQUAL;
            }
state_181:
            accept = 2;
            marker = ++cursor;
            if((limit - cursor) < 3) FillBuffer();
            chr = *cursor;
            if(chr <= 'D') {
                if(chr <= '/') goto state_159;
                if(chr <= '9') goto state_181;
                goto state_159;
            } else {
                if(chr <= 'E') goto state_162;
                if(chr == 'e') goto state_162;
                goto state_159;
            }
state_183:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_CONCAT_EQUAL;
            }
state_185:
            chr = *++cursor;
            goto state_139;
state_186:
            ++cursor;
            {
                start_line = line;
                
                goto long_comment;
            }
state_188:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_DIV_EQUAL;
            }
state_190:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_MUL_EQUAL;
            }
state_192:
            ++cursor;
            if((chr = *cursor) == '=') goto state_196;
            {
                TokenNode(*node);
                
                return T_SR;
            }
state_194:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_IS_GREATER_OR_EQUAL;
            }
state_196:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_SR_EQUAL;
            }
state_198:
            ++cursor;
            if((chr = *cursor) == '=') goto state_200;
state_199:
            {
                TokenNode(*node);
                
                return T_IS_NOT_EQUAL;
            }
state_200:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_IS_NOT_IDENTICAL;
            }
state_202:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_PLUS_EQUAL;
            }
state_204:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_INC;
            }
state_206:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_PAAMAYIM_NEKUDOTAYIM;
            }
state_208:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_MINUS_EQUAL;
            }
state_210:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_DEC;
            }
state_212:
            ++cursor;
            {
                TokenNode(*node);
                
                state = SS_OBJECT_PROPERTY;
                
                return T_OBJECT_OPERATOR;
            }
state_214:
            ++cursor;
            if((chr = *cursor) == '=') goto state_218;
            {
                TokenNode(*node);
                
                return T_IS_EQUAL;
            }
state_216:
            ++cursor;
            {
                TokenNode(*node);
                
                if (settings->spaces_around_map_operator) {
                    (*node)->token = " => ";
                }
                
                return T_DOUBLE_ARROW;
            }
state_218:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_IS_IDENTICAL;
            }
state_220:
            ++cursor;
            if((limit - cursor) < 7) FillBuffer();
            chr = *cursor;
state_221:
            if(chr <= 'S') {
                if(chr <= 'D') {
                    if(chr <= ' ') {
                        if(chr == 0x09) goto state_220;
                        if(chr <= 0x1F) goto state_163;
                        goto state_220;
                    } else {
                        if(chr <= 'A') {
                            if(chr <= '@') goto state_163;
                            goto state_225;
                        } else {
                            if(chr <= 'B') goto state_223;
                            if(chr <= 'C') goto state_163;
                            goto state_228;
                        }
                    }
                } else {
                    if(chr <= 'I') {
                        if(chr == 'F') goto state_229;
                        if(chr <= 'H') goto state_163;
                        goto state_230;
                    } else {
                        if(chr <= 'O') {
                            if(chr <= 'N') goto state_163;
                            goto state_224;
                        } else {
                            if(chr <= 'Q') goto state_163;
                            if(chr <= 'R') goto state_227;
                            goto state_226;
                        }
                    }
                }
            } else {
                if(chr <= 'f') {
                    if(chr <= 'a') {
                        if(chr == 'U') goto state_222;
                        if(chr <= '`') goto state_163;
                        goto state_225;
                    } else {
                        if(chr <= 'c') {
                            if(chr <= 'b') goto state_223;
                            goto state_163;
                        } else {
                            if(chr <= 'd') goto state_228;
                            if(chr <= 'e') goto state_163;
                            goto state_229;
                        }
                    }
                } else {
                    if(chr <= 'q') {
                        if(chr <= 'i') {
                            if(chr <= 'h') goto state_163;
                            goto state_230;
                        } else {
                            if(chr == 'o') goto state_224;
                            goto state_163;
                        }
                    } else {
                        if(chr <= 's') {
                            if(chr <= 'r') goto state_227;
                            goto state_226;
                        } else {
                            if(chr != 'u') goto state_163;
                        }
                    }
                }
            }
state_222:
            chr = *++cursor;
            if(chr == 'N') goto state_285;
            if(chr == 'n') goto state_285;
            goto state_163;
state_223:
            chr = *++cursor;
            if(chr == 'O') goto state_276;
            if(chr == 'o') goto state_276;
            goto state_163;
state_224:
            chr = *++cursor;
            if(chr == 'B') goto state_268;
            if(chr == 'b') goto state_268;
            goto state_163;
state_225:
            chr = *++cursor;
            if(chr == 'R') goto state_261;
            if(chr == 'r') goto state_261;
            goto state_163;
state_226:
            chr = *++cursor;
            if(chr == 'T') goto state_253;
            if(chr == 't') goto state_253;
            goto state_163;
state_227:
            chr = *++cursor;
            if(chr == 'E') goto state_251;
            if(chr == 'e') goto state_251;
            goto state_163;
state_228:
            chr = *++cursor;
            if(chr == 'O') goto state_247;
            if(chr == 'o') goto state_247;
            goto state_163;
state_229:
            chr = *++cursor;
            if(chr == 'L') goto state_240;
            if(chr == 'l') goto state_240;
            goto state_163;
state_230:
            chr = *++cursor;
            if(chr == 'N') goto state_231;
            if(chr != 'n') goto state_163;
state_231:
            chr = *++cursor;
            if(chr == 'T') goto state_232;
            if(chr != 't') goto state_163;
state_232:
            chr = *++cursor;
            if(chr == 'E') goto state_237;
            if(chr == 'e') goto state_237;
            goto state_234;
state_233:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
state_234:
            if(chr <= 0x1F) {
                if(chr == 0x09) goto state_233;
                goto state_163;
            } else {
                if(chr <= ' ') goto state_233;
                if(chr != ')') goto state_163;
            }
            ++cursor;
            {
                TokenNode(*node);
                
                return T_INT_CAST;
            }
state_237:
            chr = *++cursor;
            if(chr == 'G') goto state_238;
            if(chr != 'g') goto state_163;
state_238:
            chr = *++cursor;
            if(chr == 'E') goto state_239;
            if(chr != 'e') goto state_163;
state_239:
            chr = *++cursor;
            if(chr == 'R') goto state_233;
            if(chr == 'r') goto state_233;
            goto state_163;
state_240:
            chr = *++cursor;
            if(chr == 'O') goto state_241;
            if(chr != 'o') goto state_163;
state_241:
            chr = *++cursor;
            if(chr == 'A') goto state_242;
            if(chr != 'a') goto state_163;
state_242:
            chr = *++cursor;
            if(chr == 'T') goto state_243;
            if(chr != 't') goto state_163;
state_243:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
            if(chr <= 0x1F) {
                if(chr == 0x09) goto state_243;
                goto state_163;
            } else {
                if(chr <= ' ') goto state_243;
                if(chr != ')') goto state_163;
            }
            ++cursor;
            {
                TokenNode(*node);
                
                return T_DOUBLE_CAST;
            }
state_247:
            chr = *++cursor;
            if(chr == 'U') goto state_248;
            if(chr != 'u') goto state_163;
state_248:
            chr = *++cursor;
            if(chr == 'B') goto state_249;
            if(chr != 'b') goto state_163;
state_249:
            chr = *++cursor;
            if(chr == 'L') goto state_250;
            if(chr != 'l') goto state_163;
state_250:
            chr = *++cursor;
            if(chr == 'E') goto state_243;
            if(chr == 'e') goto state_243;
            goto state_163;
state_251:
            chr = *++cursor;
            if(chr == 'A') goto state_252;
            if(chr != 'a') goto state_163;
state_252:
            chr = *++cursor;
            if(chr == 'L') goto state_243;
            if(chr == 'l') goto state_243;
            goto state_163;
state_253:
            chr = *++cursor;
            if(chr == 'R') goto state_254;
            if(chr != 'r') goto state_163;
state_254:
            chr = *++cursor;
            if(chr == 'I') goto state_255;
            if(chr != 'i') goto state_163;
state_255:
            chr = *++cursor;
            if(chr == 'N') goto state_256;
            if(chr != 'n') goto state_163;
state_256:
            chr = *++cursor;
            if(chr == 'G') goto state_257;
            if(chr != 'g') goto state_163;
state_257:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
            if(chr <= 0x1F) {
                if(chr == 0x09) goto state_257;
                goto state_163;
            } else {
                if(chr <= ' ') goto state_257;
                if(chr != ')') goto state_163;
            }
            ++cursor;
            {
                TokenNode(*node);
                
                return T_STRING_CAST;
            }
state_261:
            chr = *++cursor;
            if(chr == 'R') goto state_262;
            if(chr != 'r') goto state_163;
state_262:
            chr = *++cursor;
            if(chr == 'A') goto state_263;
            if(chr != 'a') goto state_163;
state_263:
            chr = *++cursor;
            if(chr == 'Y') goto state_264;
            if(chr != 'y') goto state_163;
state_264:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
            if(chr <= 0x1F) {
                if(chr == 0x09) goto state_264;
                goto state_163;
            } else {
                if(chr <= ' ') goto state_264;
                if(chr != ')') goto state_163;
            }
            ++cursor;
            {
                TokenNode(*node);
                
                return T_ARRAY_CAST;
            }
state_268:
            chr = *++cursor;
            if(chr == 'J') goto state_269;
            if(chr != 'j') goto state_163;
state_269:
            chr = *++cursor;
            if(chr == 'E') goto state_270;
            if(chr != 'e') goto state_163;
state_270:
            chr = *++cursor;
            if(chr == 'C') goto state_271;
            if(chr != 'c') goto state_163;
state_271:
            chr = *++cursor;
            if(chr == 'T') goto state_272;
            if(chr != 't') goto state_163;
state_272:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
            if(chr <= 0x1F) {
                if(chr == 0x09) goto state_272;
                goto state_163;
            } else {
                if(chr <= ' ') goto state_272;
                if(chr != ')') goto state_163;
            }
            ++cursor;
            {
                TokenNode(*node);
                
                return T_OBJECT_CAST;
            }
state_276:
            chr = *++cursor;
            if(chr == 'O') goto state_277;
            if(chr != 'o') goto state_163;
state_277:
            chr = *++cursor;
            if(chr == 'L') goto state_278;
            if(chr != 'l') goto state_163;
state_278:
            chr = *++cursor;
            if(chr == 'E') goto state_279;
            if(chr != 'e') goto state_281;
state_279:
            chr = *++cursor;
            if(chr == 'A') goto state_284;
            if(chr == 'a') goto state_284;
            goto state_163;
state_280:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
state_281:
            if(chr <= 0x1F) {
                if(chr == 0x09) goto state_280;
                goto state_163;
            } else {
                if(chr <= ' ') goto state_280;
                if(chr != ')') goto state_163;
            }
            ++cursor;
            {
                TokenNode(*node);
                
                return T_BOOL_CAST;
            }
state_284:
            chr = *++cursor;
            if(chr == 'N') goto state_280;
            if(chr == 'n') goto state_280;
            goto state_163;
state_285:
            chr = *++cursor;
            if(chr == 'S') goto state_286;
            if(chr != 's') goto state_163;
state_286:
            chr = *++cursor;
            if(chr == 'E') goto state_287;
            if(chr != 'e') goto state_163;
state_287:
            chr = *++cursor;
            if(chr == 'T') goto state_288;
            if(chr != 't') goto state_163;
state_288:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
            if(chr <= 0x1F) {
                if(chr == 0x09) goto state_288;
                goto state_163;
            } else {
                if(chr <= ' ') goto state_288;
                if(chr != ')') goto state_163;
            }
            ++cursor;
            {
                TokenNode(*node);
                
                return T_UNSET_CAST;
            }
state_292:
            chr = *++cursor;
            if(chr == 'R') goto state_293;
            if(chr != 'r') goto state_153;
state_293:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_LOGICAL_XOR;
            }
state_295:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_LOGICAL_OR;
            }
state_297:
            chr = *++cursor;
            if(chr == 'S') goto state_298;
            if(chr != 's') goto state_153;
state_298:
            chr = *++cursor;
            if(chr == 'T') goto state_299;
            if(chr != 't') goto state_153;
state_299:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_LIST;
            }
state_301:
            chr = *++cursor;
            switch(chr) {
            case 'C':
            case 'c':    goto state_303;
            case 'F':
            case 'f':    goto state_304;
            case 'H':
            case 'h':    goto state_302;
            case 'L':
            case 'l':    goto state_306;
            case 'M':
            case 'm':    goto state_305;
            default:    goto state_153;
            }
state_302:
            chr = *++cursor;
            if(chr == 'A') goto state_344;
            if(chr == 'a') goto state_344;
            goto state_153;
state_303:
            chr = *++cursor;
            if(chr == 'L') goto state_337;
            if(chr == 'l') goto state_337;
            goto state_153;
state_304:
            chr = *++cursor;
            if(chr <= 'U') {
                if(chr == 'I') goto state_321;
                if(chr <= 'T') goto state_153;
                goto state_322;
            } else {
                if(chr <= 'i') {
                    if(chr <= 'h') goto state_153;
                    goto state_321;
                } else {
                    if(chr == 'u') goto state_322;
                    goto state_153;
                }
            }
state_305:
            chr = *++cursor;
            if(chr == 'E') goto state_313;
            if(chr == 'e') goto state_313;
            goto state_153;
state_306:
            chr = *++cursor;
            if(chr == 'I') goto state_307;
            if(chr != 'i') goto state_153;
state_307:
            chr = *++cursor;
            if(chr == 'N') goto state_308;
            if(chr != 'n') goto state_153;
state_308:
            chr = *++cursor;
            if(chr == 'E') goto state_309;
            if(chr != 'e') goto state_153;
state_309:
            chr = *++cursor;
            if(chr != '_') goto state_153;
            chr = *++cursor;
            if(chr != '_') goto state_153;
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_LINE;
            }
state_313:
            chr = *++cursor;
            if(chr == 'T') goto state_314;
            if(chr != 't') goto state_153;
state_314:
            chr = *++cursor;
            if(chr == 'H') goto state_315;
            if(chr != 'h') goto state_153;
state_315:
            chr = *++cursor;
            if(chr == 'O') goto state_316;
            if(chr != 'o') goto state_153;
state_316:
            chr = *++cursor;
            if(chr == 'D') goto state_317;
            if(chr != 'd') goto state_153;
state_317:
            chr = *++cursor;
            if(chr != '_') goto state_153;
            chr = *++cursor;
            if(chr != '_') goto state_153;
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_METHOD_C;
            }
state_321:
            chr = *++cursor;
            if(chr == 'L') goto state_332;
            if(chr == 'l') goto state_332;
            goto state_153;
state_322:
            chr = *++cursor;
            if(chr == 'N') goto state_323;
            if(chr != 'n') goto state_153;
state_323:
            chr = *++cursor;
            if(chr == 'C') goto state_324;
            if(chr != 'c') goto state_153;
state_324:
            chr = *++cursor;
            if(chr == 'T') goto state_325;
            if(chr != 't') goto state_153;
state_325:
            chr = *++cursor;
            if(chr == 'I') goto state_326;
            if(chr != 'i') goto state_153;
state_326:
            chr = *++cursor;
            if(chr == 'O') goto state_327;
            if(chr != 'o') goto state_153;
state_327:
            chr = *++cursor;
            if(chr == 'N') goto state_328;
            if(chr != 'n') goto state_153;
state_328:
            chr = *++cursor;
            if(chr != '_') goto state_153;
            chr = *++cursor;
            if(chr != '_') goto state_153;
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_FUNC_C;
            }
state_332:
            chr = *++cursor;
            if(chr == 'E') goto state_333;
            if(chr != 'e') goto state_153;
state_333:
            chr = *++cursor;
            if(chr != '_') goto state_153;
            chr = *++cursor;
            if(chr != '_') goto state_153;
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_FILE;
            }
state_337:
            chr = *++cursor;
            if(chr == 'A') goto state_338;
            if(chr != 'a') goto state_153;
state_338:
            chr = *++cursor;
            if(chr == 'S') goto state_339;
            if(chr != 's') goto state_153;
state_339:
            chr = *++cursor;
            if(chr == 'S') goto state_340;
            if(chr != 's') goto state_153;
state_340:
            chr = *++cursor;
            if(chr != '_') goto state_153;
            chr = *++cursor;
            if(chr != '_') goto state_153;
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_CLASS_C;
            }
state_344:
            chr = *++cursor;
            if(chr == 'L') goto state_345;
            if(chr != 'l') goto state_153;
state_345:
            chr = *++cursor;
            if(chr == 'T') goto state_346;
            if(chr != 't') goto state_153;
state_346:
            chr = *++cursor;
            if(chr != '_') goto state_153;
            chr = *++cursor;
            if(chr == 'C') goto state_348;
            if(chr != 'c') goto state_153;
state_348:
            chr = *++cursor;
            if(chr == 'O') goto state_349;
            if(chr != 'o') goto state_153;
state_349:
            chr = *++cursor;
            if(chr == 'M') goto state_350;
            if(chr != 'm') goto state_153;
state_350:
            chr = *++cursor;
            if(chr == 'P') goto state_351;
            if(chr != 'p') goto state_153;
state_351:
            chr = *++cursor;
            if(chr == 'I') goto state_352;
            if(chr != 'i') goto state_153;
state_352:
            chr = *++cursor;
            if(chr == 'L') goto state_353;
            if(chr != 'l') goto state_153;
state_353:
            chr = *++cursor;
            if(chr == 'E') goto state_354;
            if(chr != 'e') goto state_153;
state_354:
            chr = *++cursor;
            if(chr == 'R') goto state_355;
            if(chr != 'r') goto state_153;
state_355:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_HALT_COMPILER;
            }
state_357:
            chr = *++cursor;
            if(chr == 'O') goto state_358;
            if(chr != 'o') goto state_153;
state_358:
            chr = *++cursor;
            if(chr == 'B') goto state_359;
            if(chr != 'b') goto state_153;
state_359:
            chr = *++cursor;
            if(chr == 'A') goto state_360;
            if(chr != 'a') goto state_153;
state_360:
            chr = *++cursor;
            if(chr == 'L') goto state_361;
            if(chr != 'l') goto state_153;
state_361:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_GLOBAL;
            }
state_363:
            chr = *++cursor;
            if(chr == 'S') goto state_367;
            if(chr == 's') goto state_367;
            goto state_153;
state_364:
            chr = *++cursor;
            if(chr == 'E') goto state_365;
            if(chr != 'e') goto state_153;
state_365:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_USE;
            }
state_367:
            chr = *++cursor;
            if(chr == 'E') goto state_368;
            if(chr != 'e') goto state_153;
state_368:
            chr = *++cursor;
            if(chr == 'T') goto state_369;
            if(chr != 't') goto state_153;
state_369:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_UNSET;
            }
state_371:
            chr = *++cursor;
            if(chr == 'R') goto state_372;
            if(chr != 'r') goto state_153;
state_372:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_VAR;
            }
state_374:
            chr = *++cursor;
            if(chr == 'W') goto state_375;
            if(chr != 'w') goto state_153;
state_375:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_NEW;
            }
state_377:
            chr = *++cursor;
            if(chr <= 'O') {
                if(chr == 'I') goto state_384;
                if(chr <= 'N') goto state_153;
                goto state_385;
            } else {
                if(chr <= 'i') {
                    if(chr <= 'h') goto state_153;
                    goto state_384;
                } else {
                    if(chr == 'o') goto state_385;
                    goto state_153;
                }
            }
state_378:
            chr = *++cursor;
            if(chr == 'B') goto state_379;
            if(chr != 'b') goto state_153;
state_379:
            chr = *++cursor;
            if(chr == 'L') goto state_380;
            if(chr != 'l') goto state_153;
state_380:
            chr = *++cursor;
            if(chr == 'I') goto state_381;
            if(chr != 'i') goto state_153;
state_381:
            chr = *++cursor;
            if(chr == 'C') goto state_382;
            if(chr != 'c') goto state_153;
state_382:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_PUBLIC;
            }
state_384:
            chr = *++cursor;
            if(chr <= 'V') {
                if(chr == 'N') goto state_393;
                if(chr <= 'U') goto state_153;
                goto state_394;
            } else {
                if(chr <= 'n') {
                    if(chr <= 'm') goto state_153;
                    goto state_393;
                } else {
                    if(chr == 'v') goto state_394;
                    goto state_153;
                }
            }
state_385:
            chr = *++cursor;
            if(chr == 'T') goto state_386;
            if(chr != 't') goto state_153;
state_386:
            chr = *++cursor;
            if(chr == 'E') goto state_387;
            if(chr != 'e') goto state_153;
state_387:
            chr = *++cursor;
            if(chr == 'C') goto state_388;
            if(chr != 'c') goto state_153;
state_388:
            chr = *++cursor;
            if(chr == 'T') goto state_389;
            if(chr != 't') goto state_153;
state_389:
            chr = *++cursor;
            if(chr == 'E') goto state_390;
            if(chr != 'e') goto state_153;
state_390:
            chr = *++cursor;
            if(chr == 'D') goto state_391;
            if(chr != 'd') goto state_153;
state_391:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_PROTECTED;
            }
state_393:
            chr = *++cursor;
            if(chr == 'T') goto state_399;
            if(chr == 't') goto state_399;
            goto state_153;
state_394:
            chr = *++cursor;
            if(chr == 'A') goto state_395;
            if(chr != 'a') goto state_153;
state_395:
            chr = *++cursor;
            if(chr == 'T') goto state_396;
            if(chr != 't') goto state_153;
state_396:
            chr = *++cursor;
            if(chr == 'E') goto state_397;
            if(chr != 'e') goto state_153;
state_397:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_PRIVATE;
            }
state_399:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_PRINT;
            }
state_401:
            chr = *++cursor;
            if(chr == 'E') goto state_402;
            if(chr != 'e') goto state_153;
state_402:
            chr = *++cursor;
            if(chr == 'A') goto state_403;
            if(chr != 'a') goto state_153;
state_403:
            chr = *++cursor;
            if(chr == 'K') goto state_404;
            if(chr != 'k') goto state_153;
state_404:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_BREAK;
            }
state_406:
            chr = *++cursor;
            if(chr == 'A') goto state_413;
            if(chr == 'a') goto state_413;
            goto state_153;
state_407:
            chr = *++cursor;
            if(chr == 'I') goto state_408;
            if(chr != 'i') goto state_153;
state_408:
            chr = *++cursor;
            if(chr == 'T') goto state_409;
            if(chr != 't') goto state_153;
state_409:
            chr = *++cursor;
            if(chr == 'C') goto state_410;
            if(chr != 'c') goto state_153;
state_410:
            chr = *++cursor;
            if(chr == 'H') goto state_411;
            if(chr != 'h') goto state_153;
state_411:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_SWITCH;
            }
state_413:
            chr = *++cursor;
            if(chr == 'T') goto state_414;
            if(chr != 't') goto state_153;
state_414:
            chr = *++cursor;
            if(chr == 'I') goto state_415;
            if(chr != 'i') goto state_153;
state_415:
            chr = *++cursor;
            if(chr == 'C') goto state_416;
            if(chr != 'c') goto state_153;
state_416:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_STATIC;
            }
state_418:
            chr = *++cursor;
            if(chr == 'S') goto state_429;
            if(chr == 's') goto state_429;
            goto state_153;
state_419:
            chr = *++cursor;
            if(chr == 'D') goto state_427;
            if(chr == 'd') goto state_427;
            goto state_153;
state_420:
            chr = *++cursor;
            if(chr == 'R') goto state_423;
            if(chr == 'r') goto state_423;
            goto state_153;
state_421:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_AS;
            }
state_423:
            chr = *++cursor;
            if(chr == 'A') goto state_424;
            if(chr != 'a') goto state_153;
state_424:
            chr = *++cursor;
            if(chr == 'Y') goto state_425;
            if(chr != 'y') goto state_153;
state_425:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_ARRAY;
            }
state_427:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_LOGICAL_AND;
            }
state_429:
            chr = *++cursor;
            if(chr == 'T') goto state_430;
            if(chr != 't') goto state_153;
state_430:
            chr = *++cursor;
            if(chr == 'R') goto state_431;
            if(chr != 'r') goto state_153;
state_431:
            chr = *++cursor;
            if(chr == 'A') goto state_432;
            if(chr != 'a') goto state_153;
state_432:
            chr = *++cursor;
            if(chr == 'C') goto state_433;
            if(chr != 'c') goto state_153;
state_433:
            chr = *++cursor;
            if(chr == 'T') goto state_434;
            if(chr != 't') goto state_153;
state_434:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_ABSTRACT;
            }
state_436:
            chr = *++cursor;
            if(chr == 'I') goto state_437;
            if(chr != 'i') goto state_153;
state_437:
            chr = *++cursor;
            if(chr == 'L') goto state_438;
            if(chr != 'l') goto state_153;
state_438:
            chr = *++cursor;
            if(chr == 'E') goto state_439;
            if(chr != 'e') goto state_153;
state_439:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_WHILE;
            }
state_441:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_IF;
            }
state_443:
            chr = *++cursor;
            if(chr == 'P') goto state_479;
            if(chr == 'p') goto state_479;
            goto state_153;
state_444:
            chr = *++cursor;
            if(chr <= 'T') {
                if(chr <= 'C') {
                    if(chr <= 'B') goto state_153;
                    goto state_452;
                } else {
                    if(chr <= 'R') goto state_153;
                    if(chr <= 'S') goto state_450;
                    goto state_451;
                }
            } else {
                if(chr <= 'r') {
                    if(chr == 'c') goto state_452;
                    goto state_153;
                } else {
                    if(chr <= 's') goto state_450;
                    if(chr <= 't') goto state_451;
                    goto state_153;
                }
            }
state_445:
            chr = *++cursor;
            if(chr == 'S') goto state_446;
            if(chr != 's') goto state_153;
state_446:
            chr = *++cursor;
            if(chr == 'E') goto state_447;
            if(chr != 'e') goto state_153;
state_447:
            chr = *++cursor;
            if(chr == 'T') goto state_448;
            if(chr != 't') goto state_153;
state_448:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_ISSET;
            }
state_450:
            chr = *++cursor;
            if(chr == 'T') goto state_471;
            if(chr == 't') goto state_471;
            goto state_153;
state_451:
            chr = *++cursor;
            if(chr == 'E') goto state_464;
            if(chr == 'e') goto state_464;
            goto state_153;
state_452:
            chr = *++cursor;
            if(chr == 'L') goto state_453;
            if(chr != 'l') goto state_153;
state_453:
            chr = *++cursor;
            if(chr == 'U') goto state_454;
            if(chr != 'u') goto state_153;
state_454:
            chr = *++cursor;
            if(chr == 'D') goto state_455;
            if(chr != 'd') goto state_153;
state_455:
            chr = *++cursor;
            if(chr == 'E') goto state_456;
            if(chr != 'e') goto state_153;
state_456:
            ++cursor;
            if((chr = *cursor) <= '^') {
                if(chr <= '9') {
                    if(chr >= '0') goto state_152;
                } else {
                    if(chr <= '@') goto state_457;
                    if(chr <= 'Z') goto state_152;
                }
            } else {
                if(chr <= '`') {
                    if(chr <= '_') goto state_458;
                } else {
                    if(chr <= 'z') goto state_152;
                    if(chr >= 0x7F) goto state_152;
                }
            }
state_457:
            {
                TokenNode(*node);
                
                return T_INCLUDE;
            }
state_458:
            chr = *++cursor;
            if(chr == 'O') goto state_459;
            if(chr != 'o') goto state_153;
state_459:
            chr = *++cursor;
            if(chr == 'N') goto state_460;
            if(chr != 'n') goto state_153;
state_460:
            chr = *++cursor;
            if(chr == 'C') goto state_461;
            if(chr != 'c') goto state_153;
state_461:
            chr = *++cursor;
            if(chr == 'E') goto state_462;
            if(chr != 'e') goto state_153;
state_462:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_INCLUDE_ONCE;
            }
state_464:
            chr = *++cursor;
            if(chr == 'R') goto state_465;
            if(chr != 'r') goto state_153;
state_465:
            chr = *++cursor;
            if(chr == 'F') goto state_466;
            if(chr != 'f') goto state_153;
state_466:
            chr = *++cursor;
            if(chr == 'A') goto state_467;
            if(chr != 'a') goto state_153;
state_467:
            chr = *++cursor;
            if(chr == 'C') goto state_468;
            if(chr != 'c') goto state_153;
state_468:
            chr = *++cursor;
            if(chr == 'E') goto state_469;
            if(chr != 'e') goto state_153;
state_469:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_INTERFACE;
            }
state_471:
            chr = *++cursor;
            if(chr == 'A') goto state_472;
            if(chr != 'a') goto state_153;
state_472:
            chr = *++cursor;
            if(chr == 'N') goto state_473;
            if(chr != 'n') goto state_153;
state_473:
            chr = *++cursor;
            if(chr == 'C') goto state_474;
            if(chr != 'c') goto state_153;
state_474:
            chr = *++cursor;
            if(chr == 'E') goto state_475;
            if(chr != 'e') goto state_153;
state_475:
            chr = *++cursor;
            if(chr == 'O') goto state_476;
            if(chr != 'o') goto state_153;
state_476:
            chr = *++cursor;
            if(chr == 'F') goto state_477;
            if(chr != 'f') goto state_153;
state_477:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_INSTANCEOF;
            }
state_479:
            chr = *++cursor;
            if(chr == 'L') goto state_480;
            if(chr != 'l') goto state_153;
state_480:
            chr = *++cursor;
            if(chr == 'E') goto state_481;
            if(chr != 'e') goto state_153;
state_481:
            chr = *++cursor;
            if(chr == 'M') goto state_482;
            if(chr != 'm') goto state_153;
state_482:
            chr = *++cursor;
            if(chr == 'E') goto state_483;
            if(chr != 'e') goto state_153;
state_483:
            chr = *++cursor;
            if(chr == 'N') goto state_484;
            if(chr != 'n') goto state_153;
state_484:
            chr = *++cursor;
            if(chr == 'T') goto state_485;
            if(chr != 't') goto state_153;
state_485:
            chr = *++cursor;
            if(chr == 'S') goto state_486;
            if(chr != 's') goto state_153;
state_486:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_IMPLEMENTS;
            }
state_488:
            chr = *++cursor;
            if(chr == 'R') goto state_492;
            if(chr == 'r') goto state_492;
            goto state_153;
state_489:
            chr = *++cursor;
            if(chr == 'Y') goto state_490;
            if(chr != 'y') goto state_153;
state_490:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_TRY;
            }
state_492:
            chr = *++cursor;
            if(chr == 'O') goto state_493;
            if(chr != 'o') goto state_153;
state_493:
            chr = *++cursor;
            if(chr == 'W') goto state_494;
            if(chr != 'w') goto state_153;
state_494:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_THROW;
            }
state_496:
            chr = *++cursor;
            if(chr <= 'T') {
                if(chr == 'Q') goto state_498;
                if(chr <= 'S') goto state_153;
            } else {
                if(chr <= 'q') {
                    if(chr <= 'p') goto state_153;
                    goto state_498;
                } else {
                    if(chr != 't') goto state_153;
                }
            }
            chr = *++cursor;
            if(chr == 'U') goto state_510;
            if(chr == 'u') goto state_510;
            goto state_153;
state_498:
            chr = *++cursor;
            if(chr == 'U') goto state_499;
            if(chr != 'u') goto state_153;
state_499:
            chr = *++cursor;
            if(chr == 'I') goto state_500;
            if(chr != 'i') goto state_153;
state_500:
            chr = *++cursor;
            if(chr == 'R') goto state_501;
            if(chr != 'r') goto state_153;
state_501:
            chr = *++cursor;
            if(chr == 'E') goto state_502;
            if(chr != 'e') goto state_153;
state_502:
            ++cursor;
            if((chr = *cursor) <= '^') {
                if(chr <= '9') {
                    if(chr >= '0') goto state_152;
                } else {
                    if(chr <= '@') goto state_503;
                    if(chr <= 'Z') goto state_152;
                }
            } else {
                if(chr <= '`') {
                    if(chr <= '_') goto state_504;
                } else {
                    if(chr <= 'z') goto state_152;
                    if(chr >= 0x7F) goto state_152;
                }
            }
state_503:
            {
                TokenNode(*node);
                
                return T_REQUIRE;
            }
state_504:
            chr = *++cursor;
            if(chr == 'O') goto state_505;
            if(chr != 'o') goto state_153;
state_505:
            chr = *++cursor;
            if(chr == 'N') goto state_506;
            if(chr != 'n') goto state_153;
state_506:
            chr = *++cursor;
            if(chr == 'C') goto state_507;
            if(chr != 'c') goto state_153;
state_507:
            chr = *++cursor;
            if(chr == 'E') goto state_508;
            if(chr != 'e') goto state_153;
state_508:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_REQUIRE_ONCE;
            }
state_510:
            chr = *++cursor;
            if(chr == 'R') goto state_511;
            if(chr != 'r') goto state_153;
state_511:
            chr = *++cursor;
            if(chr == 'N') goto state_512;
            if(chr != 'n') goto state_153;
state_512:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_RETURN;
            }
state_514:
            chr = *++cursor;
            if(chr <= 'T') {
                if(chr <= 'R') goto state_153;
                if(chr <= 'S') goto state_536;
                goto state_535;
            } else {
                if(chr <= 'r') goto state_153;
                if(chr <= 's') goto state_536;
                if(chr <= 't') goto state_535;
                goto state_153;
            }
state_515:
            chr = *++cursor;
            if(chr <= 'O') {
                if(chr == 'A') goto state_527;
                if(chr <= 'N') goto state_153;
                goto state_528;
            } else {
                if(chr <= 'a') {
                    if(chr <= '`') goto state_153;
                    goto state_527;
                } else {
                    if(chr == 'o') goto state_528;
                    goto state_153;
                }
            }
state_516:
            chr = *++cursor;
            if(chr == 'N') goto state_517;
            if(chr != 'n') goto state_153;
state_517:
            chr = *++cursor;
            if(chr <= 'T') {
                if(chr <= 'R') goto state_153;
                if(chr >= 'T') goto state_519;
            } else {
                if(chr <= 'r') goto state_153;
                if(chr <= 's') goto state_518;
                if(chr <= 't') goto state_519;
                goto state_153;
            }
state_518:
            chr = *++cursor;
            if(chr == 'T') goto state_525;
            if(chr == 't') goto state_525;
            goto state_153;
state_519:
            chr = *++cursor;
            if(chr == 'I') goto state_520;
            if(chr != 'i') goto state_153;
state_520:
            chr = *++cursor;
            if(chr == 'N') goto state_521;
            if(chr != 'n') goto state_153;
state_521:
            chr = *++cursor;
            if(chr == 'U') goto state_522;
            if(chr != 'u') goto state_153;
state_522:
            chr = *++cursor;
            if(chr == 'E') goto state_523;
            if(chr != 'e') goto state_153;
state_523:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_CONTINUE;
            }
state_525:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_CONST;
            }
state_527:
            chr = *++cursor;
            if(chr == 'S') goto state_532;
            if(chr == 's') goto state_532;
            goto state_153;
state_528:
            chr = *++cursor;
            if(chr == 'N') goto state_529;
            if(chr != 'n') goto state_153;
state_529:
            chr = *++cursor;
            if(chr == 'E') goto state_530;
            if(chr != 'e') goto state_153;
state_530:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_CLONE;
            }
state_532:
            chr = *++cursor;
            if(chr == 'S') goto state_533;
            if(chr != 's') goto state_153;
state_533:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_CLASS;
            }
state_535:
            chr = *++cursor;
            if(chr == 'C') goto state_539;
            if(chr == 'c') goto state_539;
            goto state_153;
state_536:
            chr = *++cursor;
            if(chr == 'E') goto state_537;
            if(chr != 'e') goto state_153;
state_537:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_CASE;
            }
state_539:
            chr = *++cursor;
            if(chr == 'H') goto state_540;
            if(chr != 'h') goto state_153;
state_540:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_CATCH;
            }
state_542:
            chr = *++cursor;
            if(chr == 'N') goto state_559;
            if(chr == 'n') goto state_559;
            goto state_153;
state_543:
            chr = *++cursor;
            if(chr == 'R') goto state_552;
            if(chr == 'r') goto state_552;
            goto state_153;
state_544:
            chr = *++cursor;
            if(chr == 'N') goto state_545;
            if(chr != 'n') goto state_153;
state_545:
            chr = *++cursor;
            if(chr == 'C') goto state_546;
            if(chr != 'c') goto state_153;
state_546:
            chr = *++cursor;
            if(chr == 'T') goto state_547;
            if(chr != 't') goto state_153;
state_547:
            chr = *++cursor;
            if(chr == 'I') goto state_548;
            if(chr != 'i') goto state_153;
state_548:
            chr = *++cursor;
            if(chr == 'O') goto state_549;
            if(chr != 'o') goto state_153;
state_549:
            chr = *++cursor;
            if(chr == 'N') goto state_550;
            if(chr != 'n') goto state_153;
state_550:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_FUNCTION;
            }
state_552:
            ++cursor;
            if((chr = *cursor) <= '^') {
                if(chr <= '@') {
                    if(chr <= '/') goto state_553;
                    if(chr <= '9') goto state_152;
                } else {
                    if(chr == 'E') goto state_554;
                    if(chr <= 'Z') goto state_152;
                }
            } else {
                if(chr <= 'd') {
                    if(chr != '`') goto state_152;
                } else {
                    if(chr <= 'e') goto state_554;
                    if(chr <= 'z') goto state_152;
                    if(chr >= 0x7F) goto state_152;
                }
            }
state_553:
            {
                TokenNode(*node);
                
                return T_FOR;
            }
state_554:
            chr = *++cursor;
            if(chr == 'A') goto state_555;
            if(chr != 'a') goto state_153;
state_555:
            chr = *++cursor;
            if(chr == 'C') goto state_556;
            if(chr != 'c') goto state_153;
state_556:
            chr = *++cursor;
            if(chr == 'H') goto state_557;
            if(chr != 'h') goto state_153;
state_557:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_FOREACH;
            }
state_559:
            chr = *++cursor;
            if(chr == 'A') goto state_560;
            if(chr != 'a') goto state_153;
state_560:
            chr = *++cursor;
            if(chr == 'L') goto state_561;
            if(chr != 'l') goto state_153;
state_561:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_FINAL;
            }
state_563:
            chr = *++cursor;
            if(chr <= 'F') {
                if(chr == 'C') goto state_569;
                if(chr <= 'E') goto state_153;
                goto state_570;
            } else {
                if(chr <= 'c') {
                    if(chr <= 'b') goto state_153;
                    goto state_569;
                } else {
                    if(chr == 'f') goto state_570;
                    goto state_153;
                }
            }
state_564:
            chr = *++cursor;
            if(chr == 'E') goto state_567;
            if(chr == 'e') goto state_567;
            goto state_153;
state_565:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_DO;
            }
state_567:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_EXIT;
            }
state_569:
            chr = *++cursor;
            if(chr == 'L') goto state_576;
            if(chr == 'l') goto state_576;
            goto state_153;
state_570:
            chr = *++cursor;
            if(chr == 'A') goto state_571;
            if(chr != 'a') goto state_153;
state_571:
            chr = *++cursor;
            if(chr == 'U') goto state_572;
            if(chr != 'u') goto state_153;
state_572:
            chr = *++cursor;
            if(chr == 'L') goto state_573;
            if(chr != 'l') goto state_153;
state_573:
            chr = *++cursor;
            if(chr == 'T') goto state_574;
            if(chr != 't') goto state_153;
state_574:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_DEFAULT;
            }
state_576:
            chr = *++cursor;
            if(chr == 'A') goto state_577;
            if(chr != 'a') goto state_153;
state_577:
            chr = *++cursor;
            if(chr == 'R') goto state_578;
            if(chr != 'r') goto state_153;
state_578:
            chr = *++cursor;
            if(chr == 'E') goto state_579;
            if(chr != 'e') goto state_153;
state_579:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_DECLARE;
            }
state_581:
            chr = *++cursor;
            if(chr == 'H') goto state_643;
            if(chr == 'h') goto state_643;
            goto state_153;
state_582:
            chr = *++cursor;
            if(chr == 'S') goto state_637;
            if(chr == 's') goto state_637;
            goto state_153;
state_583:
            chr = *++cursor;
            if(chr == 'P') goto state_633;
            if(chr == 'p') goto state_633;
            goto state_153;
state_584:
            chr = *++cursor;
            if(chr == 'D') goto state_599;
            if(chr == 'd') goto state_599;
            goto state_153;
state_585:
            chr = *++cursor;
            if(chr == 'A') goto state_596;
            if(chr == 'a') goto state_596;
            goto state_153;
state_586:
            chr = *++cursor;
            if(chr <= 'T') {
                if(chr == 'I') goto state_587;
                if(chr <= 'S') goto state_153;
                goto state_588;
            } else {
                if(chr <= 'i') {
                    if(chr <= 'h') goto state_153;
                } else {
                    if(chr == 't') goto state_588;
                    goto state_153;
                }
            }
state_587:
            chr = *++cursor;
            if(chr == 'T') goto state_594;
            if(chr == 't') goto state_594;
            goto state_153;
state_588:
            chr = *++cursor;
            if(chr == 'E') goto state_589;
            if(chr != 'e') goto state_153;
state_589:
            chr = *++cursor;
            if(chr == 'N') goto state_590;
            if(chr != 'n') goto state_153;
state_590:
            chr = *++cursor;
            if(chr == 'D') goto state_591;
            if(chr != 'd') goto state_153;
state_591:
            chr = *++cursor;
            if(chr == 'S') goto state_592;
            if(chr != 's') goto state_153;
state_592:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_EXTENDS;
            }
state_594:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_EXIT;
            }
state_596:
            chr = *++cursor;
            if(chr == 'L') goto state_597;
            if(chr != 'l') goto state_153;
state_597:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_EVAL;
            }
state_599:
            chr = *++cursor;
            switch(chr) {
            case 'D':
            case 'd':    goto state_600;
            case 'F':
            case 'f':    goto state_601;
            case 'I':
            case 'i':    goto state_602;
            case 'S':
            case 's':    goto state_603;
            case 'W':
            case 'w':    goto state_604;
            default:    goto state_153;
            }
state_600:
            chr = *++cursor;
            if(chr == 'E') goto state_626;
            if(chr == 'e') goto state_626;
            goto state_153;
state_601:
            chr = *++cursor;
            if(chr == 'O') goto state_618;
            if(chr == 'o') goto state_618;
            goto state_153;
state_602:
            chr = *++cursor;
            if(chr == 'F') goto state_616;
            if(chr == 'f') goto state_616;
            goto state_153;
state_603:
            chr = *++cursor;
            if(chr == 'W') goto state_610;
            if(chr == 'w') goto state_610;
            goto state_153;
state_604:
            chr = *++cursor;
            if(chr == 'H') goto state_605;
            if(chr != 'h') goto state_153;
state_605:
            chr = *++cursor;
            if(chr == 'I') goto state_606;
            if(chr != 'i') goto state_153;
state_606:
            chr = *++cursor;
            if(chr == 'L') goto state_607;
            if(chr != 'l') goto state_153;
state_607:
            chr = *++cursor;
            if(chr == 'E') goto state_608;
            if(chr != 'e') goto state_153;
state_608:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_ENDWHILE;
            }
state_610:
            chr = *++cursor;
            if(chr == 'I') goto state_611;
            if(chr != 'i') goto state_153;
state_611:
            chr = *++cursor;
            if(chr == 'T') goto state_612;
            if(chr != 't') goto state_153;
state_612:
            chr = *++cursor;
            if(chr == 'C') goto state_613;
            if(chr != 'c') goto state_153;
state_613:
            chr = *++cursor;
            if(chr == 'H') goto state_614;
            if(chr != 'h') goto state_153;
state_614:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_ENDSWITCH;
            }
state_616:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_ENDIF;
            }
state_618:
            chr = *++cursor;
            if(chr == 'R') goto state_619;
            if(chr != 'r') goto state_153;
state_619:
            ++cursor;
            if((chr = *cursor) <= '^') {
                if(chr <= '@') {
                    if(chr <= '/') goto state_620;
                    if(chr <= '9') goto state_152;
                } else {
                    if(chr == 'E') goto state_621;
                    if(chr <= 'Z') goto state_152;
                }
            } else {
                if(chr <= 'd') {
                    if(chr != '`') goto state_152;
                } else {
                    if(chr <= 'e') goto state_621;
                    if(chr <= 'z') goto state_152;
                    if(chr >= 0x7F) goto state_152;
                }
            }
state_620:
            {
                TokenNode(*node);
                
                return T_ENDFOR;
            }
state_621:
            chr = *++cursor;
            if(chr == 'A') goto state_622;
            if(chr != 'a') goto state_153;
state_622:
            chr = *++cursor;
            if(chr == 'C') goto state_623;
            if(chr != 'c') goto state_153;
state_623:
            chr = *++cursor;
            if(chr == 'H') goto state_624;
            if(chr != 'h') goto state_153;
state_624:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_ENDFOREACH;
            }
state_626:
            chr = *++cursor;
            if(chr == 'C') goto state_627;
            if(chr != 'c') goto state_153;
state_627:
            chr = *++cursor;
            if(chr == 'L') goto state_628;
            if(chr != 'l') goto state_153;
state_628:
            chr = *++cursor;
            if(chr == 'A') goto state_629;
            if(chr != 'a') goto state_153;
state_629:
            chr = *++cursor;
            if(chr == 'R') goto state_630;
            if(chr != 'r') goto state_153;
state_630:
            chr = *++cursor;
            if(chr == 'E') goto state_631;
            if(chr != 'e') goto state_153;
state_631:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_ENDDECLARE;
            }
state_633:
            chr = *++cursor;
            if(chr == 'T') goto state_634;
            if(chr != 't') goto state_153;
state_634:
            chr = *++cursor;
            if(chr == 'Y') goto state_635;
            if(chr != 'y') goto state_153;
state_635:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_EMPTY;
            }
state_637:
            chr = *++cursor;
            if(chr == 'E') goto state_638;
            if(chr != 'e') goto state_153;
state_638:
            ++cursor;
            if((chr = *cursor) <= '^') {
                if(chr <= '@') {
                    if(chr <= '/') goto state_639;
                    if(chr <= '9') goto state_152;
                } else {
                    if(chr == 'I') goto state_640;
                    if(chr <= 'Z') goto state_152;
                }
            } else {
                if(chr <= 'h') {
                    if(chr != '`') goto state_152;
                } else {
                    if(chr <= 'i') goto state_640;
                    if(chr <= 'z') goto state_152;
                    if(chr >= 0x7F) goto state_152;
                }
            }
state_639:
            {
                TokenNode(*node);
                
                return T_ELSE;
            }
state_640:
            chr = *++cursor;
            if(chr == 'F') goto state_641;
            if(chr != 'f') goto state_153;
state_641:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_ELSEIF;
            }
state_643:
            chr = *++cursor;
            if(chr == 'O') goto state_644;
            if(chr != 'o') goto state_153;
state_644:
            ++cursor;
            if(bm[0+(chr = *cursor)] & 32) {
                goto state_152;
            }
            {
                TokenNode(*node);
                
                return T_ECHO;
            }
state_646:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_MOD_EQUAL;
            }
state_648:
            ++cursor;
            {
                if (settings->asp_tags) {
                    TokenNode(*node);
                    
                    state = SS_HTML;
                    
                    return ';';
                } else {
                    cursor--;
                    
                    return '%';
                }
            }
state_650:
            accept = 3;
            chr = *(marker = ++cursor);
            if(chr <= ';') goto state_651;
            if(chr <= '<') goto state_667;
            if(chr <= '=') goto state_665;
state_651:
            {
                TokenNode(*node);
                
                return T_SL;
            }
state_652:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_IS_SMALLER_OR_EQUAL;
            }
state_654:
            chr = *++cursor;
            goto state_199;
state_655:
            chr = *++cursor;
            if(chr != 's') goto state_163;
            chr = *++cursor;
            if(chr != 'c') goto state_163;
            chr = *++cursor;
            if(chr != 'r') goto state_163;
            chr = *++cursor;
            if(chr != 'i') goto state_163;
            chr = *++cursor;
            if(chr != 'p') goto state_163;
            chr = *++cursor;
            if(chr != 't') goto state_163;
state_661:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
            if(chr <= 0x0D) {
                if(chr <= 0x08) goto state_163;
                if(chr <= 0x0A) goto state_661;
                if(chr <= 0x0C) goto state_163;
                goto state_661;
            } else {
                if(chr <= ' ') {
                    if(chr <= 0x1F) goto state_163;
                    goto state_661;
                } else {
                    if(chr != '>') goto state_163;
                }
            }
state_663:
            ++cursor;
            {
                TokenNode(*node);
                AddNewlines(&((*node)->token));
                
                state = SS_HTML;
                
                return ';';
            }
state_665:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_SL_EQUAL;
            }
state_667:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
            if(chr <= 'Z') {
                if(chr <= 0x1F) {
                    if(chr == 0x09) goto state_667;
                    goto state_163;
                } else {
                    if(chr <= ' ') goto state_667;
                    if(chr <= '@') goto state_163;
                }
            } else {
                if(chr <= '`') {
                    if(chr != '_') goto state_163;
                } else {
                    if(chr <= 'z') goto state_669;
                    if(chr <= '~') goto state_163;
                }
            }
state_669:
            ++cursor;
            if((limit - cursor) < 2) FillBuffer();
            chr = *cursor;
            if(chr <= '@') {
                if(chr <= 0x0C) {
                    if(chr == 0x0A) goto state_672;
                    goto state_163;
                } else {
                    if(chr <= 0x0D) goto state_671;
                    if(chr <= '/') goto state_163;
                    if(chr <= '9') goto state_669;
                    goto state_163;
                }
            } else {
                if(chr <= '_') {
                    if(chr <= 'Z') goto state_669;
                    if(chr <= '^') goto state_163;
                    goto state_669;
                } else {
                    if(chr <= '`') goto state_163;
                    if(chr <= 'z') goto state_669;
                    if(chr <= '~') goto state_163;
                    goto state_669;
                }
            }
state_671:
            chr = *++cursor;
            if(chr != 0x0A) goto state_163;
state_672:
            ++cursor;
            {
                //TODO: make \n of \r\n
                
                uchar *offset = token + 3;
                
                while ((*offset == '\t') || (*offset == ' ')) {
                    offset++;
                }
                
                label = "\n";
                label.append((char *) offset, (cursor - offset) - (*(cursor - 2) == '\r') - 1);
                
                cursor--;
                
                start_line = line;
                
                goto heredoc_string;
            }
        }

            
short_comment:

        {
            uchar chr;
            if((limit - cursor) < 2) FillBuffer();
            chr = *cursor;
            if(chr <= 0x0D) {
                if(chr <= 0x09) {
                    if(chr <= 0x00) goto state_683;
                    goto state_682;
                } else {
                    if(chr <= 0x0A) goto state_678;
                    if(chr <= 0x0C) goto state_682;
                }
            } else {
                if(chr <= '%') {
                    if(chr <= '$') goto state_682;
                    goto state_681;
                } else {
                    if(chr == '?') goto state_680;
                    goto state_682;
                }
            }
            ++cursor;
            if((chr = *cursor) == 0x0A) goto state_687;
state_677:
            {
                goto short_comment;
            }
state_678:
            ++cursor;
state_679:
            {
                //remove newline
                cursor--;
                if (*(cursor - 1) == '\r') {
                    cursor--;
                }
                
                if (settings->remove_comments) {
                    goto php;
                }
                
                TokenNode(*node);
                
                (*node)->type = NT_SHORT_COMMENT;
                
                previous_node = *node;
                
                goto again;
            }
state_680:
            chr = *++cursor;
            if(chr == '>') goto state_685;
            goto state_677;
state_681:
            chr = *++cursor;
            if(chr == '>') goto state_685;
            goto state_677;
state_682:
            chr = *++cursor;
            goto state_677;
state_683:
            ++cursor;
            {
                formatter->last_node = *node;
                
                if (settings->remove_comments) {
                    return 0;
                }
                
                //remove \0 from comment
                cursor--;
                
                TokenNode(*node);
                
                (*node)->type = NT_SHORT_COMMENT;
                
                previous_node = *node;
                
                goto again;
            }
state_685:
            ++cursor;
            {
                if ((token[0] != '%') || settings->asp_tags) {
                    cursor -= 2;
                    
                    if (settings->remove_comments) {
                        goto php; 
                    }
                    
                    TokenNode(*node);
                    
                    (*node)->type = NT_SHORT_COMMENT;
                    
                    previous_node = *node;
                    
                    goto again;
                }
                
                goto short_comment;
            }
state_687:
            ++cursor;
            chr = *cursor;
            goto state_679;
        }

long_comment:

        {
            uchar chr;
            if((limit - cursor) < 2) FillBuffer();
            chr = *cursor;
            if(chr <= 0x0C) {
                if(chr <= 0x00) goto state_696;
                if(chr == 0x0A) goto state_693;
                goto state_695;
            } else {
                if(chr <= 0x0D) goto state_692;
                if(chr != '*') goto state_695;
            }
            ++cursor;
            if((chr = *cursor) == '/') goto state_699;
state_691:
            {
                goto long_comment;
            }
state_692:
            chr = *++cursor;
            if(chr == 0x0A) goto state_698;
            goto state_691;
state_693:
            ++cursor;
state_694:
            {
                //TODO: make \n of \r\n
                
                line++;
                
                //NOTE: and before? NOPE, don't change comment, but indentation
                
                goto long_comment;
            }
state_695:
            chr = *++cursor;
            goto state_691;
state_696:
            ++cursor;
            {
                //NOTE: free node? nope it is pointed to with next
                
                throw new CException(E_SOURCE,
                    string("Unterminated comment starting line ") + int_to_string(start_line) +
                    "!");
            }
state_698:
            chr = *++cursor;
            goto state_694;
state_699:
            ++cursor;
            {
                if (settings->remove_comments) {
                    goto php;
                }
                
                TokenNode(*node);
                
                (*node)->type = NT_LONG_COMMENT;
                
                previous_node = *node;
                
                goto again;
            }
        }

back_quote_string:

        {
            uchar chr;
            if((limit - cursor) < 2) FillBuffer();
            chr = *cursor;
            if(chr <= 0x0D) {
                if(chr <= 0x09) {
                    if(chr <= 0x00) goto state_711;
                    goto state_710;
                } else {
                    if(chr <= 0x0A) goto state_705;
                    if(chr <= 0x0C) goto state_710;
                }
            } else {
                if(chr <= '\\') {
                    if(chr <= '[') goto state_710;
                    goto state_707;
                } else {
                    if(chr == '`') goto state_708;
                    goto state_710;
                }
            }
            ++cursor;
            if((chr = *cursor) == 0x0A) goto state_717;
state_704:
            {
                goto back_quote_string;
            }
state_705:
            ++cursor;
state_706:
            {
                //TODO: make \n of \r\n
                
                line++;
                
                goto back_quote_string;
            }
state_707:
            chr = *++cursor;
            if(chr == '\\') goto state_715;
            if(chr == '`') goto state_713;
            goto state_704;
state_708:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_CONSTANT_ENCAPSED_STRING;
            }
state_710:
            chr = *++cursor;
            goto state_704;
state_711:
            ++cursor;
            {
                //NOTE: free node? nope it is pointed to
                
                throw new CException(E_SOURCE,
                    string("Unterminated string starting line ") + int_to_string(start_line) +
                    "!");
            }
state_713:
            ++cursor;
            {
                goto back_quote_string;
            }
state_715:
            ++cursor;
            {
                goto back_quote_string;
            }
state_717:
            ++cursor;
            chr = *cursor;
            goto state_706;
        }

single_quote_string:

        {
            uchar chr;
            if((limit - cursor) < 2) FillBuffer();
            chr = *cursor;
            if(chr <= 0x0D) {
                if(chr <= 0x09) {
                    if(chr <= 0x00) goto state_728;
                    goto state_727;
                } else {
                    if(chr <= 0x0A) goto state_722;
                    if(chr <= 0x0C) goto state_727;
                }
            } else {
                if(chr <= '\'') {
                    if(chr <= '&') goto state_727;
                    goto state_725;
                } else {
                    if(chr == '\\') goto state_724;
                    goto state_727;
                }
            }
            ++cursor;
            if((chr = *cursor) == 0x0A) goto state_734;
state_721:
            {
                goto single_quote_string;
            }
state_722:
            ++cursor;
state_723:
            {
                //TODO: make \n of \r\n
                
                line++;
                
                goto single_quote_string;
            }
state_724:
            chr = *++cursor;
            if(chr == '\'') goto state_730;
            if(chr == '\\') goto state_732;
            goto state_721;
state_725:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_CONSTANT_ENCAPSED_STRING;
            }
state_727:
            chr = *++cursor;
            goto state_721;
state_728:
            ++cursor;
            {
                //NOTE: free node? nope it is pointed to
                
                throw new CException(E_SOURCE,
                    string("Unterminated string starting line ") + int_to_string(start_line) +
                    "!");
            }
state_730:
            ++cursor;
            {
                goto single_quote_string;
            }
state_732:
            ++cursor;
            {
                goto single_quote_string;
            }
state_734:
            ++cursor;
            chr = *cursor;
            goto state_723;
        }

double_quote_string:

        {
            uchar chr;
            if((limit - cursor) < 2) FillBuffer();
            chr = *cursor;
            if(chr <= 0x0D) {
                if(chr <= 0x09) {
                    if(chr <= 0x00) goto state_744;
                    goto state_746;
                } else {
                    if(chr <= 0x0A) goto state_739;
                    if(chr <= 0x0C) goto state_746;
                }
            } else {
                if(chr <= '"') {
                    if(chr <= '!') goto state_746;
                    goto state_742;
                } else {
                    if(chr == '\\') goto state_741;
                    goto state_746;
                }
            }
            ++cursor;
            if((chr = *cursor) == 0x0A) goto state_751;
state_738:
            {
                goto double_quote_string;
            }
state_739:
            ++cursor;
state_740:
            {
                //TODO: make \n of \r\n
                
                line++;
                
                goto double_quote_string;
            }
state_741:
            chr = *++cursor;
            if(chr == '"') goto state_747;
            if(chr == '\\') goto state_749;
            goto state_738;
state_742:
            ++cursor;
            {
                TokenNode(*node);
                
                return T_CONSTANT_ENCAPSED_STRING;
            }
state_744:
            ++cursor;
            {
                //NOTE: free node? nope it is pointed to
                
                throw new CException(E_SOURCE,
                    string("Unterminated string starting line ") + int_to_string(start_line) +
                    "!");
            }
state_746:
            chr = *++cursor;
            goto state_738;
state_747:
            ++cursor;
            {
                goto double_quote_string;
            }
state_749:
            ++cursor;
            {
                goto double_quote_string;
            }
state_751:
            ++cursor;
            chr = *cursor;
            goto state_740;
        }

heredoc_string: //TODO: implement HEREDOC

        {
            uchar chr;
            static const unsigned char bm[] = {
                  0,   0,   0,   0,   0,   0,   0,   0, 
                  0,   0,   0,   0,   0,   0,   0,   0, 
                  0,   0,   0,   0,   0,   0,   0,   0, 
                  0,   0,   0,   0,   0,   0,   0,   0, 
                  0,   0,   0,   0,   0,   0,   0,   0, 
                  0,   0,   0,   0,   0,   0,   0,   0, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128,   0,   0,   0,   0,   0,   0, 
                  0, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128,   0,   0,   0,   0, 128, 
                  0, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128,   0,   0,   0,   0, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
            };
            if((limit - cursor) < 3) FillBuffer();
            chr = *cursor;
            if(chr <= 0x0A) {
                if(chr <= 0x00) goto state_759;
                if(chr <= 0x09) goto state_758;
                goto state_756;
            } else {
                if(chr != 0x0D) goto state_758;
            }
            ++cursor;
            if((chr = *cursor) == 0x0A) goto state_768;
state_755:
            {
                goto heredoc_string;
            }
state_756:
            chr = *(marker = ++cursor);
            if(chr <= '_') {
                if(chr <= '@') goto state_757;
                if(chr <= 'Z') goto state_761;
                if(chr >= '_') goto state_761;
            } else {
                if(chr <= '`') goto state_757;
                if(chr <= 'z') goto state_761;
                if(chr >= 0x7F) goto state_761;
            }
state_757:
            {
                //TODO: make \n of \r\n? Nope, don't change string! It isn't changed!
                // php newline -> \n
                
                line++;
                
                goto heredoc_string;
            }
state_758:
            chr = *++cursor;
            goto state_755;
state_759:
            ++cursor;
            {
                //NOTE: free node? nope it is pointed to
                
                throw new CException(E_SOURCE,
                    string("Unterminated string starting line ") + int_to_string(start_line) +
                    "!");
            }
state_761:
            ++cursor;
            if((limit - cursor) < 3) FillBuffer();
            chr = *cursor;
            if(bm[0+chr] & 128) {
                goto state_761;
            }
            if(chr <= 0x0C) {
                if(chr == 0x0A) goto state_766;
            } else {
                if(chr <= 0x0D) goto state_765;
                if(chr == ';') goto state_764;
            }
state_763:
            cursor = marker;
            goto state_757;
state_764:
            chr = *++cursor;
            if(chr == 0x0A) goto state_766;
            if(chr != 0x0D) goto state_763;
state_765:
            chr = *++cursor;
            if(chr != 0x0A) goto state_763;
state_766:
            ++cursor;
            {
                uint length = label.length();
                
                //NOTE: we should indent after a heredoc
                //NOTE: we should always put a ; after the label -> nope, could be an expr!
                //TODO: make \n of \r\n
                
                //NOTE: after a semicolon, there's always a newline!
                
                line++;
                
                cursor--;
                if (*(cursor - 2) == '\r') {
                    cursor--;
                }
                
                if (*(cursor - 1) == ';') {
                    cursor--;
                }
                
                if (!strncmp(label.c_str(), (char *) (cursor - length), length)) {
                    TokenNode(*node);
                    
                    if (*cursor != ';') {
                        (*node)->token += "\n" + formatter->GetIndent(1);
                        //TODO: make an option how much
                        line--;
                    }
                    
                    return T_CONSTANT_ENCAPSED_STRING;
                }
                
                goto heredoc_string;
            }
state_768:
            chr = *(marker = ++cursor);
            if(chr <= '_') {
                if(chr <= '@') goto state_757;
                if(chr <= 'Z') goto state_761;
                if(chr <= '^') goto state_757;
                goto state_761;
            } else {
                if(chr <= '`') goto state_757;
                if(chr <= 'z') goto state_761;
                if(chr <= '~') goto state_757;
                goto state_761;
            }
        }

object_property:
        /* set current token */
        token = cursor;
        

        {
            uchar chr;
            static const unsigned char bm[] = {
                  0,   0,   0,   0,   0,   0,   0,   0, 
                  0,   0,   0,   0,   0,   0,   0,   0, 
                  0,   0,   0,   0,   0,   0,   0,   0, 
                  0,   0,   0,   0,   0,   0,   0,   0, 
                  0,   0,   0,   0,   0,   0,   0,   0, 
                  0,   0,   0,   0,   0,   0,   0,   0, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128,   0,   0,   0,   0,   0,   0, 
                  0, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128,   0,   0,   0,   0, 128, 
                  0, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128,   0,   0,   0,   0, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
            };
            if((limit - cursor) < 2) FillBuffer();
            chr = *cursor;
            if(chr <= '^') {
                if(chr <= 0x00) goto state_775;
                if(chr <= '@') goto state_773;
                if(chr >= '[') goto state_773;
            } else {
                if(chr <= '`') {
                    if(chr >= '`') goto state_773;
                } else {
                    if(chr <= 'z') goto state_771;
                    if(chr <= '~') goto state_773;
                }
            }
state_771:
            ++cursor;
            chr = *cursor;
            goto state_778;
state_772:
            {
                TokenNode(*node);
                
                state = SS_PHP;
                
                return T_STRING;
            }
state_773:
            ++cursor;
            {
                cursor--;
                
                state = SS_PHP;
                
                goto php;
            }
state_775:
            ++cursor;
            {
                formatter->last_node = *node;
                
                return 0;
            }
state_777:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
state_778:
            if(bm[0+chr] & 128) {
                goto state_777;
            }
            goto state_772;
        }

halt_compiler: //TODO: flush everyting, and die
        /* set current token */
        token = cursor;
        

        {
            uchar chr;
            static const unsigned char bm[] = {
                  0, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
                128, 128, 128, 128, 128, 128, 128, 128, 
            };
            if(limit == cursor) FillBuffer();
            chr = *cursor;
            if(bm[0+chr] & 128) {
                goto state_781;
            }
            goto state_784;
state_781:
            ++cursor;
            if(limit == cursor) FillBuffer();
            chr = *cursor;
            if(bm[0+chr] & 128) {
                goto state_781;
            }
            {
                //TODO: make \n of \r\n and \n of \r
                
                //we gotta make this different
                //write everything to file, until \000
                //return 0; parser will get EOF
                //we don't need to count lines, there can be no error anymore
                
                //1: output buffer
                //2: fread 1 Mb at a time -> output this, if fread returns less, die
                //3: return 0, parser will get EOF
                
                TokenNode(*node);
                AddNewlines(&((*node)->token)); //NOTE: needed? only costs time...
                
                formatter->last_node = *node;
                
                return 0;
                
                //return T_INLINE_HTML;
            }
state_784:
            ++cursor;
            { //x
                formatter->last_node = *node;
                
                return 0;
            }
        }

    }
}

/* enable var never used warning */
//#pragma warn +8004







