//===========================================================================
// lex_main.c
//   Copyright (C) 2013 Free Software Foundation, Inc.
//   Originally by ZhaoFeng Liang <zhf.liang@outlook.com>
//
//This file is part of DTAHS_DCC.
//
//DTAHS_DCC is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or 
//(at your option) any later version.
//
//DTAHS_DCC is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with DTHAS; If not, see <http://www.gnu.org/licenses/>.  
//===========================================================================

#include	"dcc_global.h"
#include	"dcc_type.h"
#include	<stdio.h>
#include	"dcc_prototype.h"
#include	"dcc_main.h"
#include	"dcc_lex_char.h"
#include	"dcc_lex_word.h"
#include	"dcc_parse.h"

PRIVATE	s8 word_info[WORD_NUM][20] = {"AUTO","BREAK","CASE","CHAR","CONST","CONTINUE","DEFAULT","DO","DOUBLE","ELSE",
					"ENUM","EXTERN","FLOAT","FOR","GOTO","IF","INT","LONG",	"REGISTER","RETURN",
					"SHORT","SIGNED","SIZEOF","STATIC","STRUCT","SWITCH","TYPEDEF","UNION",	"UNSIGNED","VOID",
					"VOLATILE","WHILE","IDENTIFIER","SPACE","COMMENT_S","COMMENT_M_BEGIN","COMMENT_M_END","SEMICOLON","CONST_DEC","TYPE_NAME",
					"ELLIPSIS","","CONST_S_INT_8","CONST_S_INT_16","CONST_S_INT_32","CONST_S_INT_64","CONST_S_INT_128","CONST_U_INT_8","CONST_U_INT_16","CONST_U_INT_32",
					"CONST_U_INT_64","CONST_U_INT_128","","","","CONST_NL","CONST_HT","CONST_VT","CONST_BS","CONST_CR",
					"CONST_FF","CONST_BEL","CONST_BACKSLASH","CONST_QMARK","CONST_S_QUOTE","CONST_D_QUOTE","CONST_OCT","CONST_HEX","","CONST_STRING",
					"CONST_FLOAT","CONST_DOUBLE","CONST_S_SCIENCE","CONST_U_SCIENCE","","","","","","",
					"OP_PLUS","OP_MINUS","OP_MUL","OP_DIV","OP_MOD","OP_AND","OP_NOT","OP_NEG","OP_OR","OP_XOR",
					"OP_PLUS_PLUS","OP_MINUS_MINUS","OP_AND_AND","OP_OR_OR","OP_EQU_EQU","OP_LOW_EQU","OP_ABOVE_EQU","OP_NOT_EQU","OP_PLUS_EQU","OP_MINUS_EQU",
					"OP_MUL_EQU","OP_DIV_EQU","OP_MOD_EQU","OP_SHIFT_LEFT","OP_SHIFT_RIGHT","OP_SHIFT_LEFT_EQU","OP_SHIFT_RIGHT_EQU","OP_AND_EQU","OP_OR_EQU","OP_XOR_EQU",
					"OP_EQU","OP_Q_COND","OP_LOW","OP_ABOVE","OP_COMMA","OP_DOT","OP_POINTOR","OP_COLON","","",
					"OP_L_PARENTHESE","OP_R_PARENTHESE","OP_L_BRACKET","OP_R_BRACKET","OP_L_BRACE","OP_R_BRACE","","PARSE_END"
				};

struct s_token_list	tokenlist;

#define	LEX_DEBUG
//===========================================================================
// tokenlist_init()
//===========================================================================
PUBLIC	void	tokenlist_init()
{
	p_pre_token	= &tokenlist;

	p_cur_token	= &tokenlist;

	tokenlist.id	= 0;
	tokenlist.token	= 10000;
	tokenlist.prev	= NULL;
	tokenlist.next	= NULL;
}

//===========================================================================
// tokenlist_init()
//===========================================================================
PUBLIC	void	tokenlist_add(s32 token, s8 *val_s)
{
	struct s_token_list *t	= malloc(sizeof(struct s_token_list));

	if(!t)
	{
		printf("err::tokenlist_add::no enough memory!\n");
		exit(1);
	}

	struct s_token_list * p = &tokenlist;
	for(;p->next!=NULL;p=p->next)
	{}

	t->id		= p->id + 1;
	t->token	= token;
	t->prev		= p;
	t->next		= NULL;
	
	if(val_s)
	{
		strcopy(t->val_s, val_s);
		t->val_s[strlen(val_s)]	= NULL;		
	}
	else
	{
		t->val_s[0]	= NULL;
	}

	p->next		= t;
}

//===========================================================================
// tokenlist_init()
//===========================================================================
PUBLIC	void	tokenlist_print()
{
	struct s_token_list *t	= &tokenlist;

	for(; t != NULL; t=t->next)
	{
		printf("%d::%d::%s\n",t->id, t->token, &word_info[t->token][0]);
	}	
}


//===========================================================================
// main
//===========================================================================
PUBLIC	void	get_tok()
{
	if(p_cur_token)
	{
		p_pre_token = p_cur_token;
		p_cur_token = p_cur_token->next;
	}

	token	= p_cur_token->token;
}

//===========================================================================
// main
//===========================================================================
PUBLIC	void	uget_tok(s32 num)
{
	s32 i;
	for(i=0; i<num; i++)
	{
		if(p_cur_token->prev)
		{
			p_cur_token = p_cur_token->prev;
		}
	}

	token	= p_cur_token->token;
}
