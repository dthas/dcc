//===========================================================================
// lex_main.c
//   Copyright (C) 2013 Free Software Foundation, Inc.
//   Originally by ZhaoFeng Liang <zhf.liang@outlook.com>
//
//This file is part of DTHAS_DNASM.
//
//DTHAS_DNASM is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or 
//(at your option) any later version.
//
//DTHAS_DNASM is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with DTHAS; If not, see <http://www.gnu.org/licenses/>.  
//===========================================================================

#include	"dnasm_global.h"
#include	"dnasm_type.h"
#include	<stdio.h>
#include	"dnasm_prototype.h"
#include	"dnasm_main.h"
#include	"dnasm_lex_char.h"
#include	"dnasm_lex_word.h"
#include	"dnasm_parse.h"

PRIVATE	s8	word_info[WORD_NUM][20]={
	"TIMES","DW","DD","DQ","DT","DY","RESB","RESW","RESQ","RESY",
	"INCBIN","EQU","DB","ADD","SUB","MUL","DIV","MOV","JMP","CALL",
	"RET","JA","JB","JE","JAE","JBE","JNE","GLOBAL","EXTERN","PUSH",
	"POP","EAX","EBX","ECX","EDX","EBP","ESP","ESI","EDI","CS",
	"EIP","DS","ES","SECTION","BYTE","WORD","DWORD","CMP","BITS","XOR",
	"BX","INT","IDENTIFIER","SPACE","SEMICOLON","CONST_DEC","ELLIPSIS","CONST_INT_8","CONST_INT_16","CONST_INT_32",
"CONST_INT_64","CONST_INT_128","CONST_BACKSLASH","CONST_QMARK","CONST_S_QUOTE","CONST_D_QUOTE","CONST_OCT","CONST_HEX","CONST_STRING","CONST_FLOAT",
	"CONST_DOUBLE","CONST_CR","","","","","","","OP_COLON","OP_COMMA",
	"OP_PLUS","OP_MINUS","OP_MUL","OP_DIV","OP_L_PARENTHESE","OP_R_PARENTHESE","OP_L_BRACKET","OP_R_BRACKET","PARSE_END"		
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
		if(t->token != 10000)
		{
			printf("%d::%d::%s\n",t->id, t->token, &word_info[t->token][0]);
		}
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
