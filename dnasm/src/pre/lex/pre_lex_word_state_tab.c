//===========================================================================
// pre_lex_word_state_tab.c
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
#include	"dnasm_pre_lex_word.h"
#include	<stdio.h>
#include	"dnasm_prototype.h"

PRIVATE	s32	pre_lex_word_state_tab[PRE_LEX_WORD_STATES][LEX_WORD_NR_ACTION];	
//===========================================================================
// init
//===========================================================================
PUBLIC	void	pre_lex_word_statetab_init()
{
	printf("--pre_lex_word_state_tab init---\n");

	s32 i;

	p_pre_lex_word_state_tab = pre_lex_word_state_tab;

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE1 
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][i]= PRE_LEX_WORD_STATE1;
	}	

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][LEX_WORD_SEMICOLON]	= PRE_LEX_WORD_STATE2;	// ;
			
	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE2 (semicolon)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE2][i]	= PRE_LEX_WORD_STATE2;
	}

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE2][LEX_WORD_END]	= PRE_LEX_WORD_STATE1;
	
}
