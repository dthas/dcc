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

PRIVATE	s32	word_process(s8 *word, s32 state);
PRIVATE	s32	preserve_word_process(s8* word);

PRIVATE s8	preserve_word[PRESERVE_NUM][10]	= {"auto","break","case","char","const","continue","default","do","double","else",
							"enum","extern","float","for","goto","if","int","long","register","return",
							"short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void",
							"volatile","while"};

PRIVATE	s32	word_tab[LEX_CHAR_STATES]	= {
	-1, OP_PLUS, OP_PLUS_PLUS, OP_PLUS_EQU, OP_MINUS, OP_MINUS_MINUS, OP_MINUS_EQU, OP_POINTOR, OP_MUL,
	OP_MUL_EQU, COMMENT_M_END, OP_DIV, OP_DIV_EQU, COMMENT_S, COMMENT_M_BEGIN, OP_MOD, OP_MOD_EQU, OP_AND, OP_AND_AND,
	OP_AND_EQU, OP_OR, OP_OR_OR, OP_OR_EQU, OP_NEG, OP_XOR, OP_XOR_EQU, OP_EQU, OP_EQU_EQU, OP_LOW, 
	OP_LOW_EQU, OP_SHIFT_LEFT, OP_SHIFT_LEFT_EQU, OP_ABOVE, OP_ABOVE_EQU, OP_SHIFT_RIGHT, OP_SHIFT_RIGHT_EQU, OP_Q_COND, OP_COLON, OP_COMMA,
	OP_R_PARENTHESE, OP_L_PARENTHESE, OP_L_BRACKET, OP_R_BRACKET, OP_L_BRACE, OP_R_BRACE, IDENTIFIER, SEMICOLON, -1, CONST_DEC,
	CONST_S_INT_8, -1, -1, CONST_S_INT_8, -1, -1, CONST_S_INT_8, -1, CONST_S_INT_8, -1,
	-1, -1, CONST_STRING, -1, CONST_OCT, CONST_HEX, CONST_DEC, OP_DOT, -1, -1,
	-1, -1, -1, OP_NOT, -1, -1, CONST_FLOAT, -1, -1, CONST_FLOAT,
	CONST_FLOAT, CONST_FLOAT, CONST_FLOAT, -1, CONST_S_INT_8, OP_NOT_EQU, -1, ELLIPSIS };

PRIVATE	s8	word_tab_info[LEX_CHAR_STATES][15]	= {
	"NE", "+", "++", "+=", "-", "--", "-=", "->", "*",
	"*=", "*/", "/", "/=", "//", "/*", "%", "%=", "&", "&&",
	"&=", "|", "||", "|=", "~", "^", "^=", "=", "==", "<", 
	"<=", "<<", "<<=", ">", ">=", ">>", ">>=", "?", ":", ",",
	")", "(", "[", "]", "{", "}", "IDENTIFIER", ";", "NE", "CONST_DEC",
	"CHAR", "NE", "NE", "CHAR", "NE", "NE", "CHAR", "NE", "CHAR", "NE",
	"NE", "NE", "CONST_STRING", "NE", "CONST_OCT", "CONST_HEX", "CONST_DEC", ".", "NE", "NE",
	"NE", "NE", "NE", "!", "NE", "NE", "CONST_FLOAT", "NE", "NE", "CONST_FLOAT",
	"CONST_FLOAT", "CONST_FLOAT", "CONST_FLOAT", "NE", "CHAR", "!=" };

PRIVATE	s8	words[WORD_NUM][20]={
	"AUTO","BREAK","CASE","CHAR","CONST","CONTINUE","DEFAULT","DO","DOUBLE","ELSE",
	"ENUM","EXTERN","FLOAT","FOR","GOTO","IF","INT","LONG","REGISTER","RETURN",
	"SHORT","SIGNED","SIZEOF","STATIC","STRUCT","SWITCH","TYPEDEF","UNION","UNSIGNED","VOID",
	"VOLATILE","WHILE","IDENTIFIER","SPACE","COMMENT_S","COMMENT_M_BEGIN","COMMENT_M_END","SEMICOLON","CONST_DEC","TYPE_NAME",		
	"ELLIPSIS","","CONST_S_INT_8","CONST_S_INT_16","CONST_S_INT_32","CONST_S_INT_64","CONST_S_INT_128","CONST_U_INT_8","CONST_U_INT_16","CONST_U_INT_32",
	"CONST_U_INT_64","CONST_U_INT_128","","","","CONST_NL","CONST_HT","CONST_VT","CONST_BS","CONST_CR",
	"CONST_FF","CONST_BEL","CONST_BACKSLASH","CONST_QMARK","CONST_S_QUOTE","CONST_D_QUOTE","CONST_OCT","CONST_HEX","","CONST_STRING",	
	"CONST_FLOAT","CONST_DOUBLE","CONST_S_SCIENCE","CONST_U_SCIENCE","","","","","","",	
	"OP_PLUS","OP_MINUS","OP_MUL",	"OP_DIV","OP_MOD","OP_AND","OP_NOT","OP_NEG","OP_OR","OP_XOR",		
	"OP_PLUS_PLUS","OP_MINUS_MINUS","OP_AND_AND","OP_OR_OR","OP_EQU_EQU","OP_LOW_EQU","OP_ABOVE_EQU","OP_NOT_EQU","OP_PLUS_EQU","OP_MINUS_EQU",			
	"OP_MUL_EQU","OP_DIV_EQU","OP_MOD_EQU",	"OP_SHIFT_LEFT","OP_SHIFT_RIGHT","OP_SHIFT_LEFT_EQU","OP_SHIFT_RIGHT_EQU","OP_AND_EQU",	"OP_OR_EQU","OP_XOR_EQU",		
	"OP_EQU","OP_Q_COND","OP_LOW","OP_ABOVE","OP_COMMA","OP_DOT","OP_POINTOR","OP_COLON","","",
	"OP_L_PARENTHESE","OP_R_PARENTHESE","OP_L_BRACKET","OP_R_BRACKET","OP_L_BRACE","OP_R_BRACE",		
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
PUBLIC	void	lex_main()
{
	s8 word[IDEN_LEN];	//64 bytes

	s8 flg 	= TRUE;

	s8 src[]	= "src/temp/pre_output.c";

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
		case LEX_CHAR_STATE11:
		case LEX_CHAR_STATE15:
		case LEX_CHAR_STATE68:
		case LEX_CHAR_STATE69:
		case LEX_CHAR_STATE70:
		case LEX_CHAR_STATE71:
		case LEX_CHAR_STATE72:
		case LEX_CHAR_STATE74:
		case LEX_CHAR_STATE75:
			return STATE_TRUE;
			break;

		case LEX_CHAR_STATE48:
		case LEX_CHAR_STATE51:
		case LEX_CHAR_STATE52:
		case LEX_CHAR_STATE54:
		case LEX_CHAR_STATE55:
		case LEX_CHAR_STATE57:
		case LEX_CHAR_STATE59:
		case LEX_CHAR_STATE60:
		case LEX_CHAR_STATE61:
		case LEX_CHAR_STATE63:
		case LEX_CHAR_STATE77:
		case LEX_CHAR_STATE78:
		case LEX_CHAR_STATE83:
			printf("error:lex_char_state is :%d\n", (state+1));
			return FALSE;
			break;

		case LEX_CHAR_STATE46:
			return 	preserve_word_process(word);
			break;

		
		case LEX_CHAR_STATE64:
		case LEX_CHAR_STATE65:
		case LEX_CHAR_STATE66:

			p_cur_token->val_i	= s2i(word);
			break;

		case LEX_CHAR_STATE50:
		case LEX_CHAR_STATE53:
		case LEX_CHAR_STATE56:
		case LEX_CHAR_STATE58:
		case LEX_CHAR_STATE84:
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
		return	word_tab[LEX_CHAR_STATE46];
	}
}







