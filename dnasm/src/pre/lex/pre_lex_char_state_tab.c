//===========================================================================
// pre_pre_lex_char_state_tab.c
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
#include	<stdio.h>
#include	"dnasm_prototype.h"

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
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_SEMICOL]		= PRE_LEX_CHAR_STATE2;	//;

	// ( and )
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_LP]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_RP]		= PRE_LEX_CHAR_STATE3;

	// [ and ]
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_LB]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_RB]		= PRE_LEX_CHAR_STATE3;

	// character
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_A]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_B]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_C]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_D]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_E]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_F]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_G]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_H]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_I]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_J]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_K]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_L]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_M]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_N]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_O]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_P]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_Q]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_R]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_S]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_T]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_U]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_V]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_W]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_X]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_Y]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_Z]		= PRE_LEX_CHAR_STATE3;

	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_a]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_b]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_c]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_d]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_e]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_f]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_g]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_h]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_i]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_j]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_k]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_l]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_m]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_n]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_o]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_p]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_q]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_r]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_s]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_t]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_u]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_v]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_w]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_x]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_y]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_z]		= PRE_LEX_CHAR_STATE3;

	// _ underline
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_UL]		= PRE_LEX_CHAR_STATE3;

	// . dot
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_DOT]		= PRE_LEX_CHAR_STATE3;	

	// ' single quota
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_SQ]		= PRE_LEX_CHAR_STATE3;

	// +
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_ADD]		= PRE_LEX_CHAR_STATE3;

	// digit
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_0]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_1]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_2]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_3]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_4]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_5]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_6]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_7]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_8]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_9]		= PRE_LEX_CHAR_STATE3;

	// tab and space
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_TAB]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_SPACE]		= PRE_LEX_CHAR_STATE3;

	// return and change line
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_LF]		= PRE_LEX_CHAR_STATE3;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_CR]		= PRE_LEX_CHAR_STATE3;

	// $
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_DOLLAR]		= PRE_LEX_CHAR_STATE3;

	// #
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_PROMPT]		= PRE_LEX_CHAR_STATE3;

	// %
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_BF]		= PRE_LEX_CHAR_STATE3;

	// -
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_MINUS]		= PRE_LEX_CHAR_STATE3;

	// *
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_MUL]		= PRE_LEX_CHAR_STATE3;

	// /
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE1][CH_DIV]		= PRE_LEX_CHAR_STATE3;
		
	//------------------------------------------------------------------
	// PRE_LEX_CHAR_STATE2 
	//------------------------------------------------------------------
	for(i=0; i<PRE_LEX_INPUT_CHARS; i++)
	{
		pre_lex_char_state_tab[PRE_LEX_CHAR_STATE2][i]	= PRE_LEX_CHAR_STATE2;
	}

	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE2][CH_LF]	= PRE_LEX_CHAR_STATE4;
	pre_lex_char_state_tab[PRE_LEX_CHAR_STATE2][CH_CR]	= PRE_LEX_CHAR_STATE4;

	//------------------------------------------------------------------
	// PRE_LEX_CHAR_STATE3 
	//------------------------------------------------------------------
	for(i=0; i<PRE_LEX_INPUT_CHARS; i++)
	{
		pre_lex_char_state_tab[PRE_LEX_CHAR_STATE3][i]	= PRE_LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// PRE_LEX_CHAR_STATE4 
	//------------------------------------------------------------------
	for(i=0; i<PRE_LEX_INPUT_CHARS; i++)
	{
		pre_lex_char_state_tab[PRE_LEX_CHAR_STATE4][i]	= PRE_LEX_CHAR_STATE_END;
	}	
}
