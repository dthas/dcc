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

PRIVATE	s32	word_process(s8 *word, s32 state);
PRIVATE	s32	preserve_word_process(s8* word);

PRIVATE s8	preserve_word[PRESERVE_NUM][10]	= {"times","dw","dd","dq","dt","dy","resb","resw","resq","resy",
							"incbin","equ","db","add","sub","mul","div","mov","jmp","call",
							"ret","ja","jb","je","jae","jbe","jne","global","extern","push",
							"pop","eax","ebx","ecx","edx","ebp","esp","esi","edi","cs",
							"eip","ds","es", "section", "byte", "word", "dword", "cmp", "BITS", "xor",
							"bx","int"};

PRIVATE	s32	word_tab[LEX_CHAR_STATES]	= {
	-1, OP_L_PARENTHESE, OP_R_PARENTHESE, OP_L_BRACKET, OP_R_BRACKET, IDENTIFIER, CONST_S_QUOTE, CONST_STRING, OP_PLUS, CONST_INT_8,
	CONST_HEX, CONST_DEC, SPACE, CONST_CR, -1, -1, -1, OP_MINUS, OP_MUL, OP_DIV, OP_COMMA , OP_COLON
	 };

PRIVATE	s8	word_tab_info[LEX_CHAR_STATES][15]	= {
	"NE", "(", ")", "[", "]", "IDENTIFIER", "SINGLE_QUOTA", "STRING", "ADD", "CONST_INT_8",
	"CONST_HEX", "CONST_DEC", "SPACEB", "CR", "$", "#", "%", "SUB","MUL","DIV", "OP_COMMA", "OP_COLON" };

PRIVATE	s8	words[WORD_NUM][20]={
	"TIMES","DW","DD","DQ","DT","DY","RESB","RESW","RESQ","RESY",
	"INCBIN","EQU","DB","ADD","SUB","MUL","DIV","MOV","JMP","CALL",
	"RET","JA","JB","JE","JAE","JBE","JNE","GLOBAL","EXTERN","PUSH",
	"POP","EAX","EBX","ECX","EDX","EBP","ESP","ESI","EDI","CS",
	"EIP","DS","ES","SECTION","BYTE","WORD","DWORD","CMP","BITS","XOR",
	"BX","INT","IDENTIFIER","SPACE","SEMICOLON","CONST_DEC","ELLIPSIS","CONST_INT_8","CONST_INT_16","CONST_INT_32",
"CONST_INT_64","CONST_INT_128","CONST_BACKSLASH","CONST_QMARK","CONST_S_QUOTE","CONST_D_QUOTE","CONST_OCT","CONST_HEX","CONST_STRING","CONST_FLOAT",
	"CONST_DOUBLE","CONST_CR","","","","","","","OP_COLON","OP_COMMA",
	"OP_PLUS","OP_MINUS","OP_MUL","OP_DIV","OP_L_PARENTHESE","OP_R_PARENTHESE","OP_L_BRACKET","OP_R_BRACKET", ""		
	};

//===========================================================================
// init
//===========================================================================
PUBLIC	void	lex_init()
{
	p_word	= words;

	p_tmp_token	= NULL;

	lex_char_statetab_init();

	lex_char_state	= LEX_CHAR_STATE1;

	tokenlist_init();
}



//===========================================================================
// main
//===========================================================================
PUBLIC	void	lex_main(s8 *src)
{
	s8 word[IDEN_LEN];	//64 bytes

	s8 flg 	= TRUE;	

	FILE *fr	= fopen(src,"r");
	
	if(fr == NULL)
	{
		printf("error::can not open read file %s\n", src);
		exit(1);
	}

	while(flg = add_tok(fr,word))
	{
		if(token != STATE_TRUE)
		{
			tokenlist_add(token, word);
		}
	}

	tokenlist_add(PARSE_END, NULL);

	tokenlist_print();
}

//===========================================================================
// main
//===========================================================================
PUBLIC	s32	add_tok(FILE *fr, s8 *word)
{
	s32 i,j;
	s32 old_lex_char_state;
	s8 ch;

	do{
		empty_buf(word, IDEN_LEN);

		for(i=0, lex_char_state=LEX_CHAR_STATE1; ; )
		{
			if((ch=fgetc(fr)) == EOF)
			{
				return FALSE;
			}
					
			old_lex_char_state	= lex_char_state;
			lex_char_state 	= *(p_lex_char_state_tab + lex_char_state * LEX_INPUT_CHARS + ch); 
			
			if(lex_char_state != LEX_CHAR_STATE_END)
			{
				word[i] = ch;
				i++;							
			}
			else
			{
				ungetc(ch, fr);
				break;				
			}
		}		
	}while((ch != EOF) && (lex_char_state != LEX_CHAR_STATE_END));

	//------------------------------------------------------------------
	// LEX STAGE :: get a word(token) from a file and put it into word[] 
	//------------------------------------------------------------------
	word[i]	= NULL;

	token	= word_process(word,old_lex_char_state);
}

//===========================================================================
// PRIVATE	s32	word_process(s8 *word, s32 state)
//===========================================================================
PRIVATE	s32	word_process(s8 *word, s32 state)
{
	switch(state)
	{
		case LEX_CHAR_STATE1:
		case LEX_CHAR_STATE13:
		case LEX_CHAR_STATE14:
		case LEX_CHAR_STATE15:
		case LEX_CHAR_STATE16:
		case LEX_CHAR_STATE17:
			return STATE_TRUE;
			break;

		case LEX_CHAR_STATE7:		
			printf("error:lex_char_state is :%d\n", (state+1));
			return FALSE;
			break;

		case LEX_CHAR_STATE6:
			return 	preserve_word_process(word);
			break;
		
		case LEX_CHAR_STATE11:
		case LEX_CHAR_STATE12:
			//digit		
			p_cur_token->val_i	= s2i(word);
			break;

		case LEX_CHAR_STATE8:
			//char/string
			p_cur_token->val_i	= c2i(word);
			break;
		
		default:
			break;
	}

	return	word_tab[state];
}

//===========================================================================
// preserve_word_process(s8* word)
//===========================================================================
PRIVATE	s32	preserve_word_process(s8* word)
{
	s32 i;
	s8 flg = FALSE;

	for(i=0; i<PRESERVE_NUM; i++)
	{
		if (strcmp(word, &preserve_word[i][0]) == TRUE)
		{
			flg = TRUE;
			break;
		}
	}

	if(flg)
	{
		return i;
	}
	else
	{
		return	word_tab[LEX_CHAR_STATE6];
	}
}
