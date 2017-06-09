//===========================================================================
// pre_main.c
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
#include	"dnasm_pre_lex_char.h"
#include	"dnasm_pre_lex_word.h"
#include	<stdio.h>
#include	"dnasm_prototype.h"

PRIVATE	s32	pre_word_process(s8 *word, s32 state);
PRIVATE	void	pre_start();
PRIVATE	void	pre_end();
PRIVATE	void	pre_set_inputfile(s8 *src, s8 *dst);
PRIVATE	s32	pre_add_tok(FILE *fr, s8 *word);

PRIVATE	s32	word_tab[PRE_LEX_CHAR_STATES]	= {-1, OP_COMMENT, OP_LF, OP_CONTENT};

//===========================================================================
// main
//===========================================================================
PUBLIC	void	pre_main(s8 *filename)
{
	s8 output_file[]	= "src/temp/pre_output.asm";

	//------------------------------------------------------------------
	// init message 
	//------------------------------------------------------------------
	pre_start();

	//------------------------------------------------------------------
	// read src file into pre_output.c 
	//------------------------------------------------------------------
	pre_set_inputfile(filename, output_file);

	//------------------------------------------------------------------
	// end 
	//------------------------------------------------------------------
	pre_end();
}

//===========================================================================
// init
//===========================================================================
PRIVATE	void	pre_start()
{
	printf("--pre start---\n");

	pre_lex_statetab_init();

	pre_lex_char_state	= PRE_LEX_CHAR_STATE1;

}

//===========================================================================
// init
//===========================================================================
PRIVATE	void	pre_end()
{
	printf("--pre end---\n");
}


//===========================================================================
// pre_set_inputfile
//===========================================================================
PRIVATE	void	pre_set_inputfile(s8 *src, s8 *dst)
{
	s32 i;
	s32 len;

	s8 word[PRE_IDEN_LEN];	//128 bytes

	s8 flg 	= TRUE;

	FILE *frp	= fopen(src,"r");
	FILE *fwp	= fopen(dst,"w");

	if(frp == NULL)
	{
		printf("error::can not open read file %s\n", src);
		exit(1);
	}

	if(fwp == NULL)
	{
		printf("error::can not open write file %s\n", dst);
		exit(1);
	}


	while(flg = pre_add_tok(frp,word))
	{
		if(pre_lex_token != PRE_STATE_TRUE)
		{
			len = strlen(word);
			for(i=0; i<len; i++)
			{
				fputc(*(word+i), fwp);
			}
		}
	}
	
	fclose(frp);
	fclose(fwp);
}

//===========================================================================
// main
//===========================================================================
PRIVATE	s32	pre_add_tok(FILE *fr, s8 *word)
{
	s32 i,j;
	s32 old_pre_lex_char_state;
	s8 ch;

	do{
		empty_buf(word, PRE_LEX_WORD_LEN);

		for(i=0, pre_lex_char_state=PRE_LEX_CHAR_STATE1; ; )
		{
			if((ch=fgetc(fr)) == EOF)
			{
				return FALSE;
			}
					
			old_pre_lex_char_state	= pre_lex_char_state;
			pre_lex_char_state 	= *(p_pre_lex_char_state_tab + pre_lex_char_state * PRE_LEX_INPUT_CHARS + ch); 
			
			if(pre_lex_char_state == PRE_LEX_CHAR_STATE2)
			{
				continue;
			}
			else if(pre_lex_char_state != PRE_LEX_CHAR_STATE_END)
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
	}while((ch != EOF) && (pre_lex_char_state != PRE_LEX_CHAR_STATE_END));

	//------------------------------------------------------------------
	// LEX STAGE :: get a word(token) from a file and put it into word[] 
	//------------------------------------------------------------------
	word[i]	= NULL;

	pre_lex_token	= pre_word_process(word,old_pre_lex_char_state);
}

//===========================================================================
// PRIVATE	s32	word_process(s8 *word, s32 state)
//===========================================================================
PRIVATE	s32	pre_word_process(s8 *word, s32 state)
{
	switch(state)
	{
		case PRE_LEX_CHAR_STATE1:
			break;

		case PRE_LEX_CHAR_STATE2:
			return PRE_STATE_TRUE;			
			break;

		case PRE_LEX_CHAR_STATE3:
			return TRUE;
			break;		
		
		default:
			break;
	}

	return	word_tab[state];
}
