//===========================================================================
// pre_pre_lex_char_state_tab.c
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
#include	"dcc_pre_lex_char.h"
#include	<stdio.h>
#include	"dcc_prototype.h"

PRIVATE	s32	pre_lex_char_state_tab[PRE_LEX_CHAR_STATES][PRE_LEX_INPUT_CHARS];	
//===========================================================================
// init
//===========================================================================
PUBLIC	void	pre_lex_statetab_init()
{
	printf("--pre_lex_char_state_tab init---\n");

	s32 i;

	p_pre_lex_char_state_tab = pre_lex_char_state_tab;

	//------------------------------------------------------------------
	// PRE_LEX_CHAR_STATE1 
	//------------------------------------------------------------------
	for(i=0; i<PRE_LEX_INPUT_CHARS; i++)
	{
		pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][i]	= PRE_LEX_CHAR_STATE1;
	}	

	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_PROMPT]	= PRE_LEX_CHAR_STATE3;	//#
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_DQ]	= PRE_LEX_CHAR_STATE4;	//"
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_LOW]	= PRE_LEX_CHAR_STATE6;	//<
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_DIV]	= PRE_LEX_CHAR_STATE9;	// /

	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_SPACE]	= PRE_LEX_CHAR_STATE2;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_TAB]	= PRE_LEX_CHAR_STATE2;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_LF]	= PRE_LEX_CHAR_STATE2;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_CR]	= PRE_LEX_CHAR_STATE2;	
	
	//------------------------------------------------------------------
	// PRE_LEX_CHAR_STATE2 
	//------------------------------------------------------------------
	for(i=0; i<PRE_LEX_INPUT_CHARS; i++)
	{
		pre_lex_char_state_tab[PRE_LEX_CHAR_STATE2][i]	= PRE_LEX_CHAR_STATE_END;
	}	

	//------------------------------------------------------------------
	// PRE_LEX_CHAR_STATE3 
	//------------------------------------------------------------------
	for(i=0; i<PRE_LEX_INPUT_CHARS; i++)
	{
		pre_lex_char_state_tab[PRE_LEX_CHAR_STATE3][i]	= PRE_LEX_CHAR_STATE8;
	}

	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE3][CH_SPACE]	= PRE_LEX_CHAR_STATE3;

	//------------------------------------------------------------------
	// STATE4
	//------------------------------------------------------------------
	for(i=0; i<PRE_LEX_INPUT_CHARS; i++)
	{
		pre_lex_char_state_tab[PRE_LEX_CHAR_STATE4][i]	= PRE_LEX_CHAR_STATE4;
	}

	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE4][CH_DQ]	= PRE_LEX_CHAR_STATE5;

	//------------------------------------------------------------------
	// STATE5
	//------------------------------------------------------------------
	for(i=0; i<PRE_LEX_INPUT_CHARS; i++)
	{
		pre_lex_char_state_tab[PRE_LEX_CHAR_STATE5][i]	= PRE_LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// STATE6
	//------------------------------------------------------------------
	for(i=0; i<PRE_LEX_INPUT_CHARS; i++)
	{
		pre_lex_char_state_tab[PRE_LEX_CHAR_STATE6][i]	= PRE_LEX_CHAR_STATE6;
	}

	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE6][CH_ABOVE]	= PRE_LEX_CHAR_STATE7;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE6][CH_SPACE]	= PRE_LEX_CHAR_STATE_END;

	//------------------------------------------------------------------
	// STATE7
	//------------------------------------------------------------------
	for(i=0; i<PRE_LEX_INPUT_CHARS; i++)
	{
		pre_lex_char_state_tab[PRE_LEX_CHAR_STATE7][i]	= PRE_LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// PRE_LEX_CHAR_STATE8
	//------------------------------------------------------------------
	for(i=0; i<PRE_LEX_INPUT_CHARS; i++)
	{
		pre_lex_char_state_tab[PRE_LEX_CHAR_STATE8][i]	= PRE_LEX_CHAR_STATE8;
	}

	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE8][CH_LF]	= PRE_LEX_CHAR_STATE_END;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE8][CH_CR]	= PRE_LEX_CHAR_STATE_END;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE8][CH_SPACE]	= PRE_LEX_CHAR_STATE_END;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE8][CH_TAB]	= PRE_LEX_CHAR_STATE_END;

	//------------------------------------------------------------------
	// PRE_LEX_CHAR_STATE9
	//------------------------------------------------------------------
	for(i=0; i<PRE_LEX_INPUT_CHARS; i++)
	{
		pre_lex_char_state_tab[PRE_LEX_CHAR_STATE9][i]	= PRE_LEX_CHAR_STATE_END;
	}

	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE9][CH_MUL]	= PRE_LEX_CHAR_STATE11;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE9][CH_DIV]	= PRE_LEX_CHAR_STATE10;

	//------------------------------------------------------------------
	// PRE_LEX_CHAR_STATE10
	//------------------------------------------------------------------
	for(i=0; i<PRE_LEX_INPUT_CHARS; i++)
	{
		pre_lex_char_state_tab[PRE_LEX_CHAR_STATE10][i]	= PRE_LEX_CHAR_STATE10;
	}

	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE10][CH_LF]	= PRE_LEX_CHAR_STATE_END;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE10][CH_CR]	= PRE_LEX_CHAR_STATE_END;

	//------------------------------------------------------------------
	// PRE_LEX_CHAR_STATE11
	//------------------------------------------------------------------
	for(i=0; i<PRE_LEX_INPUT_CHARS; i++)
	{
		pre_lex_char_state_tab[PRE_LEX_CHAR_STATE11][i]	= PRE_LEX_CHAR_STATE11;
	}

	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE11][CH_MUL]	= PRE_LEX_CHAR_STATE12;

	//------------------------------------------------------------------
	// PRE_LEX_CHAR_STATE12
	//------------------------------------------------------------------
	for(i=0; i<PRE_LEX_INPUT_CHARS; i++)
	{
		pre_lex_char_state_tab[PRE_LEX_CHAR_STATE12][i]	= PRE_LEX_CHAR_STATE11;
	}

	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE12][CH_DIV]	= PRE_LEX_CHAR_STATE_END;
}
