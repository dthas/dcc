//===========================================================================
// state_tab.c
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
#include	"dnasm_lex_char.h"
#include	<stdio.h>
#include	"dnasm_prototype.h"

PRIVATE	s32	lex_char_state_tab[LEX_CHAR_STATES][LEX_INPUT_CHARS];	
//===========================================================================
// init
//===========================================================================
PUBLIC	void	lex_char_statetab_init()
{
	printf("--lex_char_state_tab init(beg)---\n");

	s32 i;

	p_lex_char_state_tab = lex_char_state_tab;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE1 
	//------------------------------------------------------------------
	// ( and )
	lex_char_state_tab[LEX_CHAR_STATE1][CH_LP]		= LEX_CHAR_STATE2;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_RP]		= LEX_CHAR_STATE3;

	// [ and ]
	lex_char_state_tab[LEX_CHAR_STATE1][CH_LB]		= LEX_CHAR_STATE4;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_RB]		= LEX_CHAR_STATE5;

	// character
	lex_char_state_tab[LEX_CHAR_STATE1][CH_A]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_B]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_C]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_D]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_E]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_F]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_G]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_H]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_I]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_J]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_K]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_L]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_M]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_N]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_O]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_P]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_Q]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_R]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_S]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_T]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_U]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_V]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_W]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_X]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_Y]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_Z]		= LEX_CHAR_STATE6;

	lex_char_state_tab[LEX_CHAR_STATE1][CH_a]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_b]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_c]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_d]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_e]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_f]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_g]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_h]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_i]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_j]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_k]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_l]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_m]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_n]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_o]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_p]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_q]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_r]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_s]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_t]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_u]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_v]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_w]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_x]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_y]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_z]		= LEX_CHAR_STATE6;

	// _ underline
	lex_char_state_tab[LEX_CHAR_STATE1][CH_UL]		= LEX_CHAR_STATE6;

	// . dot
	lex_char_state_tab[LEX_CHAR_STATE1][CH_DOT]		= LEX_CHAR_STATE6;	

	// ' single quota
	lex_char_state_tab[LEX_CHAR_STATE1][CH_SQ]		= LEX_CHAR_STATE7;

	// +
	lex_char_state_tab[LEX_CHAR_STATE1][CH_ADD]		= LEX_CHAR_STATE9;

	// digit
	lex_char_state_tab[LEX_CHAR_STATE1][CH_0]		= LEX_CHAR_STATE10;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_1]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_2]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_3]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_4]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_5]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_6]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_7]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_8]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_9]		= LEX_CHAR_STATE12;

	// tab and space
	lex_char_state_tab[LEX_CHAR_STATE1][CH_TAB]		= LEX_CHAR_STATE13;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_SPACE]		= LEX_CHAR_STATE13;

	// return and change line
	lex_char_state_tab[LEX_CHAR_STATE1][CH_LF]		= LEX_CHAR_STATE14;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_CR]		= LEX_CHAR_STATE14;

	// $
	lex_char_state_tab[LEX_CHAR_STATE1][CH_DOLLAR]		= LEX_CHAR_STATE15;

	// #
	lex_char_state_tab[LEX_CHAR_STATE1][CH_PROMPT]		= LEX_CHAR_STATE16;

	// %
	lex_char_state_tab[LEX_CHAR_STATE1][CH_BF]		= LEX_CHAR_STATE17;

	// -
	lex_char_state_tab[LEX_CHAR_STATE1][CH_MINUS]		= LEX_CHAR_STATE18;

	// *
	lex_char_state_tab[LEX_CHAR_STATE1][CH_MUL]		= LEX_CHAR_STATE19;

	// /
	lex_char_state_tab[LEX_CHAR_STATE1][CH_DIV]		= LEX_CHAR_STATE20;

	// ,
	lex_char_state_tab[LEX_CHAR_STATE1][CH_COMMA]		= LEX_CHAR_STATE21;

	// :
	lex_char_state_tab[LEX_CHAR_STATE1][CH_COL]		= LEX_CHAR_STATE22;
	
	

	//------------------------------------------------------------------
	// LEX_CHAR_STATE2 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE2][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE3 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE3][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE4 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE4][i]	= LEX_CHAR_STATE_END;
	}
	
	//------------------------------------------------------------------
	// LEX_CHAR_STATE5 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE5][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE6 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE6][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE6][CH_A]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_B]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_C]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_D]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_E]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_F]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_G]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_H]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_I]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_J]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_K]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_L]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_M]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_N]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_O]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_P]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_Q]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_R]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_S]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_T]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_U]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_V]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_W]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_X]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_Y]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_Z]		= LEX_CHAR_STATE6;

	lex_char_state_tab[LEX_CHAR_STATE6][CH_a]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_b]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_c]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_d]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_e]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_f]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_g]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_h]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_i]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_j]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_k]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_l]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_m]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_n]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_o]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_p]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_q]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_r]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_s]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_t]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_u]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_v]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_w]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_x]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_y]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_z]		= LEX_CHAR_STATE6;

	// _ underline
	lex_char_state_tab[LEX_CHAR_STATE6][CH_UL]		= LEX_CHAR_STATE6;

	// . dot
	lex_char_state_tab[LEX_CHAR_STATE6][CH_DOT]		= LEX_CHAR_STATE6;

	// digit
	lex_char_state_tab[LEX_CHAR_STATE6][CH_0]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_1]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_2]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_3]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_4]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_5]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_6]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_7]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_8]		= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE6][CH_9]		= LEX_CHAR_STATE6;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE7 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE7][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE7][CH_A]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_B]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_C]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_D]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_E]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_F]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_G]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_H]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_I]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_J]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_K]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_L]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_M]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_N]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_O]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_P]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_Q]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_R]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_S]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_T]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_U]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_V]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_W]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_X]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_Y]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_Z]		= LEX_CHAR_STATE7;

	lex_char_state_tab[LEX_CHAR_STATE7][CH_a]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_b]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_c]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_d]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_e]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_f]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_g]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_h]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_i]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_j]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_k]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_l]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_m]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_n]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_o]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_p]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_q]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_r]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_s]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_t]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_u]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_v]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_w]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_x]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_y]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_z]		= LEX_CHAR_STATE7;

	// digit
	lex_char_state_tab[LEX_CHAR_STATE7][CH_0]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_1]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_2]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_3]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_4]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_5]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_6]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_7]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_8]		= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE7][CH_9]		= LEX_CHAR_STATE7;

	lex_char_state_tab[LEX_CHAR_STATE7][CH_SQ]		= LEX_CHAR_STATE8;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE8 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE8][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE9 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE9][i]	= LEX_CHAR_STATE_END;
	}
	
	//------------------------------------------------------------------
	// LEX_CHAR_STATE10 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE10][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE10][CH_x]	= LEX_CHAR_STATE11;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE11 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE11][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE11][CH_0]		= LEX_CHAR_STATE11;
	lex_char_state_tab[LEX_CHAR_STATE11][CH_1]		= LEX_CHAR_STATE11;
	lex_char_state_tab[LEX_CHAR_STATE11][CH_2]		= LEX_CHAR_STATE11;
	lex_char_state_tab[LEX_CHAR_STATE11][CH_3]		= LEX_CHAR_STATE11;
	lex_char_state_tab[LEX_CHAR_STATE11][CH_4]		= LEX_CHAR_STATE11;
	lex_char_state_tab[LEX_CHAR_STATE11][CH_5]		= LEX_CHAR_STATE11;
	lex_char_state_tab[LEX_CHAR_STATE11][CH_6]		= LEX_CHAR_STATE11;
	lex_char_state_tab[LEX_CHAR_STATE11][CH_7]		= LEX_CHAR_STATE11;
	lex_char_state_tab[LEX_CHAR_STATE11][CH_8]		= LEX_CHAR_STATE11;
	lex_char_state_tab[LEX_CHAR_STATE11][CH_9]		= LEX_CHAR_STATE11;
	lex_char_state_tab[LEX_CHAR_STATE11][CH_a]		= LEX_CHAR_STATE11;
	lex_char_state_tab[LEX_CHAR_STATE11][CH_b]		= LEX_CHAR_STATE11;
	lex_char_state_tab[LEX_CHAR_STATE11][CH_c]		= LEX_CHAR_STATE11;
	lex_char_state_tab[LEX_CHAR_STATE11][CH_d]		= LEX_CHAR_STATE11;
	lex_char_state_tab[LEX_CHAR_STATE11][CH_e]		= LEX_CHAR_STATE11;
	lex_char_state_tab[LEX_CHAR_STATE11][CH_f]		= LEX_CHAR_STATE11;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE12 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE12][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE12][CH_1]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE12][CH_2]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE12][CH_3]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE12][CH_4]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE12][CH_5]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE12][CH_6]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE12][CH_7]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE12][CH_8]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE12][CH_9]		= LEX_CHAR_STATE12;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE13 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE13][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE14 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE14][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE15 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE15][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE16 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE16][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE16][CH_EQU]	= LEX_CHAR_STATE17;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE17 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE17][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE18 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE18][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE19 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE19][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE20 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE20][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE21 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE21][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE22
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE22][i]	= LEX_CHAR_STATE_END;
	}

	

	printf("--lex_char_state_tab init(end)---\n");
}
