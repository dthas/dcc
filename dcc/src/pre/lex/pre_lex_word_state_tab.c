//===========================================================================
// pre_lex_word_state_tab.c
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
#include	"dcc_pre_lex_word.h"
#include	<stdio.h>
#include	"dcc_prototype.h"

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

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][LEX_WORD_INCLUDE]	= PRE_LEX_WORD_STATE2;	//
	pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][LEX_WORD_DEFINE]	= PRE_LEX_WORD_STATE3;	//
	pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][LEX_WORD_UNDEF]	= PRE_LEX_WORD_STATE4;	//
	pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][LEX_WORD_LINE]	= PRE_LEX_WORD_STATE5;	//
	pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][LEX_WORD_ERROR]	= PRE_LEX_WORD_STATE6;	//
	pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][LEX_WORD_PRAGMA]	= PRE_LEX_WORD_STATE7;	//
	pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][LEX_WORD_IF]	= PRE_LEX_WORD_STATE8;	//
	pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][LEX_WORD_IFDEF]	= PRE_LEX_WORD_STATE9;	//
	pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][LEX_WORD_IFNDEF]	= PRE_LEX_WORD_STATE10;	//
	pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][LEX_WORD_ELIF]	= PRE_LEX_WORD_STATE11;	//
	pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][LEX_WORD_ELSE]	= PRE_LEX_WORD_STATE12;	//
	pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][LEX_WORD_ENDIF]	= PRE_LEX_WORD_STATE13;	//

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][LEX_WORD_DIVDIV]	= PRE_LEX_WORD_STATE16;	// //
	pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][LEX_WORD_DIVMUL]	= PRE_LEX_WORD_STATE17;	// /*
	pre_lex_word_state_tab[PRE_LEX_WORD_STATE1][LEX_WORD_MULDIV]	= PRE_LEX_WORD_STATE18;	// */
		
	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE2 (include)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE2][i]	= PRE_LEX_WORD_STATE2;
	}

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE2][LEX_WORD_PARAM1]	= PRE_LEX_WORD_STATE1;

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE3 (define)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE3][i]	= PRE_LEX_WORD_STATE3;
	}

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE3][LEX_WORD_PARAM1]	= PRE_LEX_WORD_STATE14;

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE4 (undef)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE4][i]	= PRE_LEX_WORD_STATE4;
	}

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE4][LEX_WORD_PARAM1]	= PRE_LEX_WORD_STATE1;

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE5 (line)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE5][i]	= PRE_LEX_WORD_STATE5;
	}

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE5][LEX_WORD_PARAM1]	= PRE_LEX_WORD_STATE15;

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE6 (error)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE6][i]	= PRE_LEX_WORD_STATE6;
	}

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE6][LEX_WORD_PARAM1]	= PRE_LEX_WORD_STATE1;

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE7 (pragma)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE7][i]	= PRE_LEX_WORD_STATE7;
	}

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE7][LEX_WORD_PARAM1]	= PRE_LEX_WORD_STATE1;

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE8 (if)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE8][i]	= PRE_LEX_WORD_STATE8;
	}

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE8][LEX_WORD_PARAM1]	= PRE_LEX_WORD_STATE1;

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE9 (ifdef)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE9][i]	= PRE_LEX_WORD_STATE9;
	}

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE9][LEX_WORD_PARAM1]	= PRE_LEX_WORD_STATE1;

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE10 (ifndef)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE10][i]	= PRE_LEX_WORD_STATE10;
	}

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE10][LEX_WORD_PARAM1]	= PRE_LEX_WORD_STATE1;

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE11 (elif)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE11][i]	= PRE_LEX_WORD_STATE11;
	}

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE11][LEX_WORD_PARAM1]	= PRE_LEX_WORD_STATE1;

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE12 (else)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE12][i]	= PRE_LEX_WORD_STATE1;
	}

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE13 (endif)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE13][i]	= PRE_LEX_WORD_STATE1;
	}

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE14 (define--param2)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE14][i]	= PRE_LEX_WORD_STATE14;
	}

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE14][LEX_WORD_PARAM2]	= PRE_LEX_WORD_STATE1;

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE15 (line--param2)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE15][i]	= PRE_LEX_WORD_STATE15;
	}

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE15][LEX_WORD_END]	= PRE_LEX_WORD_STATE1;
	pre_lex_word_state_tab[PRE_LEX_WORD_STATE15][LEX_WORD_PARAM2]	= PRE_LEX_WORD_STATE1;

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE16 (//)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE16][i]	= PRE_LEX_WORD_STATE16;
	}

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE16][LEX_WORD_END]	= PRE_LEX_WORD_STATE1;

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE17 (/*)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE17][i]	= PRE_LEX_WORD_STATE17;
	}

	pre_lex_word_state_tab[PRE_LEX_WORD_STATE17][LEX_WORD_MULDIV]	= PRE_LEX_WORD_STATE18;

	//------------------------------------------------------------------
	// PRE_LEX_WORD_STATE18 (*/)
	//------------------------------------------------------------------
	for(i=0; i<LEX_WORD_NR_ACTION; i++)
	{
		pre_lex_word_state_tab[PRE_LEX_WORD_STATE18][i]	= PRE_LEX_WORD_STATE1;
	}

	
}
