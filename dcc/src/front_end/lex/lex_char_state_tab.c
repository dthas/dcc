//===========================================================================
// state_tab.c
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
#include	"dcc_lex_char.h"
#include	<stdio.h>
#include	"dcc_prototype.h"

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
	lex_char_state_tab[LEX_CHAR_STATE1][CH_TAB]		= LEX_CHAR_STATE69;

	lex_char_state_tab[LEX_CHAR_STATE1][CH_SPACE]		= LEX_CHAR_STATE69;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_GT]		= LEX_CHAR_STATE73;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_DQ]		= LEX_CHAR_STATE60;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_PROMPT]		= LEX_CHAR_STATE70;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_LF]		= LEX_CHAR_STATE75;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_CR]		= LEX_CHAR_STATE75;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_DOLLAR]		= LEX_CHAR_STATE71;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_BF]		= LEX_CHAR_STATE16;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_AND]		= LEX_CHAR_STATE18;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_SQ]		= LEX_CHAR_STATE51;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_LP]		= LEX_CHAR_STATE41;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_RP]		= LEX_CHAR_STATE40;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_MUL]		= LEX_CHAR_STATE9;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_ADD]		= LEX_CHAR_STATE2;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_COMMA]		= LEX_CHAR_STATE39;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_MINUS]		= LEX_CHAR_STATE5;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_DOT]		= LEX_CHAR_STATE67;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_DIV]		= LEX_CHAR_STATE12;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_0]		= LEX_CHAR_STATE63;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_1]		= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_2]		= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_3]		= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_4]		= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_5]		= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_6]		= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_7]		= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_8]		= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_9]		= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_COL]		= LEX_CHAR_STATE38;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_SEMICOL]		= LEX_CHAR_STATE47;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_LOW]		= LEX_CHAR_STATE29;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_EQU]		= LEX_CHAR_STATE27;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_ABOVE]		= LEX_CHAR_STATE33;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_QUEST]		= LEX_CHAR_STATE37;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_AT]		= LEX_CHAR_STATE74;

	lex_char_state_tab[LEX_CHAR_STATE1][CH_A]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_B]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_C]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_D]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_E]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_F]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_G]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_H]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_I]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_J]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_K]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_L]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_M]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_N]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_O]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_P]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_Q]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_R]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_S]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_T]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_U]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_V]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_W]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_X]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_Y]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_Z]		= LEX_CHAR_STATE46;

	lex_char_state_tab[LEX_CHAR_STATE1][CH_LB]		= LEX_CHAR_STATE42;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_BS]		= LEX_CHAR_STATE68;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_RB]		= LEX_CHAR_STATE43;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_AF]		= LEX_CHAR_STATE25;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_UL]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_BCOMMA]	= LEX_CHAR_STATE72;

	lex_char_state_tab[LEX_CHAR_STATE1][CH_a]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_b]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_c]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_d]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_e]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_f]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_g]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_h]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_i]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_j]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_k]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_l]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_m]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_n]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_o]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_p]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_q]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_r]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_s]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_t]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_u]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_v]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_w]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_x]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_y]		= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_z]		= LEX_CHAR_STATE46;
	
	lex_char_state_tab[LEX_CHAR_STATE1][CH_LBB]		= LEX_CHAR_STATE44;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_VL]		= LEX_CHAR_STATE21;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_RBB]		= LEX_CHAR_STATE45;
	lex_char_state_tab[LEX_CHAR_STATE1][CH_REV]		= LEX_CHAR_STATE24;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE2 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE2][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE2][CH_ADD]	= LEX_CHAR_STATE3;
	lex_char_state_tab[LEX_CHAR_STATE2][CH_EQU]	= LEX_CHAR_STATE4;
	
	lex_char_state_tab[LEX_CHAR_STATE2][CH_0]	= LEX_CHAR_STATE63;
	lex_char_state_tab[LEX_CHAR_STATE2][CH_1]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE2][CH_2]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE2][CH_3]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE2][CH_4]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE2][CH_5]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE2][CH_6]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE2][CH_7]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE2][CH_8]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE2][CH_9]	= LEX_CHAR_STATE66;

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

	lex_char_state_tab[LEX_CHAR_STATE5][CH_MINUS]	= LEX_CHAR_STATE6;
	lex_char_state_tab[LEX_CHAR_STATE5][CH_EQU]	= LEX_CHAR_STATE7;
	lex_char_state_tab[LEX_CHAR_STATE5][CH_ABOVE]	= LEX_CHAR_STATE8;

	lex_char_state_tab[LEX_CHAR_STATE5][CH_0]	= LEX_CHAR_STATE63;
	lex_char_state_tab[LEX_CHAR_STATE5][CH_1]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE5][CH_2]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE5][CH_3]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE5][CH_4]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE5][CH_5]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE5][CH_6]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE5][CH_7]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE5][CH_8]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE5][CH_9]	= LEX_CHAR_STATE66;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE6 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE6][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE7 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE7][i]	= LEX_CHAR_STATE_END;
	}

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

	lex_char_state_tab[LEX_CHAR_STATE9][CH_DIV]	= LEX_CHAR_STATE11;
	lex_char_state_tab[LEX_CHAR_STATE9][CH_EQU]	= LEX_CHAR_STATE10;
	
	//------------------------------------------------------------------
	// LEX_CHAR_STATE10 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE10][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE11 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE11][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE12 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE12][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE12][CH_DIV]	= LEX_CHAR_STATE14;
	lex_char_state_tab[LEX_CHAR_STATE12][CH_EQU]	= LEX_CHAR_STATE13;
	lex_char_state_tab[LEX_CHAR_STATE12][CH_MUL]	= LEX_CHAR_STATE15;

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

	lex_char_state_tab[LEX_CHAR_STATE18][CH_EQU]	= LEX_CHAR_STATE20;
	lex_char_state_tab[LEX_CHAR_STATE18][CH_AND]	= LEX_CHAR_STATE19;
	
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

	lex_char_state_tab[LEX_CHAR_STATE21][CH_EQU]	= LEX_CHAR_STATE23;
	lex_char_state_tab[LEX_CHAR_STATE21][CH_VL]	= LEX_CHAR_STATE22;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE22
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE22][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE23
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE23][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE24
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE24][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE25
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE25][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE25][CH_EQU]	= LEX_CHAR_STATE26;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE26
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE26][i]	= LEX_CHAR_STATE_END;
	}
	
	//------------------------------------------------------------------
	// LEX_CHAR_STATE27
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE27][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE27][CH_EQU]	= LEX_CHAR_STATE28;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE28
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE28][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE29
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE29][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE29][CH_EQU]	= LEX_CHAR_STATE30;
	lex_char_state_tab[LEX_CHAR_STATE29][CH_LOW]	= LEX_CHAR_STATE31;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE30
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE30][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE31
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE31][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE31][CH_EQU]	= LEX_CHAR_STATE32;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE32 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE32][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE33 
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE33][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE33][CH_EQU]	= LEX_CHAR_STATE34;
	lex_char_state_tab[LEX_CHAR_STATE33][CH_ABOVE]= LEX_CHAR_STATE35;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE34
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE34][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE35
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE35][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE35][CH_EQU]	= LEX_CHAR_STATE36;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE36
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE36][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE37
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE37][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE38
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE38][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE39
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE39][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE40
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE40][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE41
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE41][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE42
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE42][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE43
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE43][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE44
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE44][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE45
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE45][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE46
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE46][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE46][CH_A]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_B]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_C]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_D]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_E]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_F]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_G]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_H]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_I]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_J]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_K]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_L]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_M]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_N]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_O]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_P]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_Q]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_R]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_S]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_T]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_U]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_V]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_W]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_X]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_Y]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_Z]	= LEX_CHAR_STATE46;

	lex_char_state_tab[LEX_CHAR_STATE46][CH_UL]	= LEX_CHAR_STATE46;
	
	lex_char_state_tab[LEX_CHAR_STATE46][CH_a]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_b]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_c]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_d]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_e]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_f]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_g]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_h]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_i]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_j]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_k]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_l]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_m]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_n]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_o]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_p]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_q]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_r]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_s]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_t]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_u]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_v]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_w]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_x]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_y]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_z]	= LEX_CHAR_STATE46;

	lex_char_state_tab[LEX_CHAR_STATE46][CH_0]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_1]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_2]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_3]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_4]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_5]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_6]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_7]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_8]	= LEX_CHAR_STATE46;
	lex_char_state_tab[LEX_CHAR_STATE46][CH_9]	= LEX_CHAR_STATE46;	

	//------------------------------------------------------------------
	// LEX_CHAR_STATE47
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE47][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE48
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE48][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE48][CH_0]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE48][CH_1]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE48][CH_2]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE48][CH_3]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE48][CH_4]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE48][CH_5]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE48][CH_6]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE48][CH_7]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE48][CH_8]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE48][CH_9]	= LEX_CHAR_STATE49;


	//------------------------------------------------------------------
	// LEX_CHAR_STATE49
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE49][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE49][CH_0]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE49][CH_1]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE49][CH_2]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE49][CH_3]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE49][CH_4]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE49][CH_5]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE49][CH_6]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE49][CH_7]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE49][CH_8]	= LEX_CHAR_STATE49;
	lex_char_state_tab[LEX_CHAR_STATE49][CH_9]	= LEX_CHAR_STATE49;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE50
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE50][i]	= LEX_CHAR_STATE_END;
	}	

	//------------------------------------------------------------------
	// LEX_CHAR_STATE51
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE51][i]	= LEX_CHAR_STATE52;
	}

	lex_char_state_tab[LEX_CHAR_STATE51][CH_BS]	= LEX_CHAR_STATE54;
	lex_char_state_tab[LEX_CHAR_STATE51][CH_LF]	= LEX_CHAR_STATE_END;
	lex_char_state_tab[LEX_CHAR_STATE51][CH_CR]	= LEX_CHAR_STATE_END;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE52
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE52][i]	= LEX_CHAR_STATE61;
	}

	lex_char_state_tab[LEX_CHAR_STATE52][CH_SQ]	= LEX_CHAR_STATE53;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE53
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE53][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE54
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE54][i]	= LEX_CHAR_STATE83;
	}

	lex_char_state_tab[LEX_CHAR_STATE54][CH_n]	= LEX_CHAR_STATE55;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_t]	= LEX_CHAR_STATE55;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_v]	= LEX_CHAR_STATE55;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_b]	= LEX_CHAR_STATE55;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_r]	= LEX_CHAR_STATE55;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_f]	= LEX_CHAR_STATE55;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_a]	= LEX_CHAR_STATE55;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_BS]	= LEX_CHAR_STATE55;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_QUEST]= LEX_CHAR_STATE55;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_SQ]	= LEX_CHAR_STATE55;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_DQ]	= LEX_CHAR_STATE55;

	lex_char_state_tab[LEX_CHAR_STATE54][CH_0]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_1]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_2]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_3]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_4]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_5]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_6]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_7]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_8]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_9]	= LEX_CHAR_STATE57;

	lex_char_state_tab[LEX_CHAR_STATE54][CH_x]	= LEX_CHAR_STATE59;
	lex_char_state_tab[LEX_CHAR_STATE54][CH_X]	= LEX_CHAR_STATE59;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE55
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE55][i]	= LEX_CHAR_STATE61;
	}

	lex_char_state_tab[LEX_CHAR_STATE55][CH_SQ]	= LEX_CHAR_STATE56;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE56
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE56][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE57
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE57][i]	= LEX_CHAR_STATE61;
	}

	lex_char_state_tab[LEX_CHAR_STATE57][CH_0]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE57][CH_1]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE57][CH_2]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE57][CH_3]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE57][CH_4]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE57][CH_5]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE57][CH_6]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE57][CH_7]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE57][CH_8]	= LEX_CHAR_STATE57;
	lex_char_state_tab[LEX_CHAR_STATE57][CH_9]	= LEX_CHAR_STATE57;

	lex_char_state_tab[LEX_CHAR_STATE57][CH_SQ]	= LEX_CHAR_STATE58;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE58
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE58][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE59
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE59][i]	= LEX_CHAR_STATE61;
	}

	lex_char_state_tab[LEX_CHAR_STATE59][CH_0]	= LEX_CHAR_STATE59;
	lex_char_state_tab[LEX_CHAR_STATE59][CH_1]	= LEX_CHAR_STATE59;
	lex_char_state_tab[LEX_CHAR_STATE59][CH_2]	= LEX_CHAR_STATE59;
	lex_char_state_tab[LEX_CHAR_STATE59][CH_3]	= LEX_CHAR_STATE59;
	lex_char_state_tab[LEX_CHAR_STATE59][CH_4]	= LEX_CHAR_STATE59;
	lex_char_state_tab[LEX_CHAR_STATE59][CH_5]	= LEX_CHAR_STATE59;
	lex_char_state_tab[LEX_CHAR_STATE59][CH_6]	= LEX_CHAR_STATE59;
	lex_char_state_tab[LEX_CHAR_STATE59][CH_7]	= LEX_CHAR_STATE59;
	lex_char_state_tab[LEX_CHAR_STATE59][CH_8]	= LEX_CHAR_STATE59;
	lex_char_state_tab[LEX_CHAR_STATE59][CH_9]	= LEX_CHAR_STATE59;

	lex_char_state_tab[LEX_CHAR_STATE59][CH_a]	= LEX_CHAR_STATE59;
	lex_char_state_tab[LEX_CHAR_STATE59][CH_b]	= LEX_CHAR_STATE59;
	lex_char_state_tab[LEX_CHAR_STATE59][CH_c]	= LEX_CHAR_STATE59;
	lex_char_state_tab[LEX_CHAR_STATE59][CH_d]	= LEX_CHAR_STATE59;
	lex_char_state_tab[LEX_CHAR_STATE59][CH_e]	= LEX_CHAR_STATE59;
	lex_char_state_tab[LEX_CHAR_STATE59][CH_f]	= LEX_CHAR_STATE59;

	lex_char_state_tab[LEX_CHAR_STATE59][CH_SQ]	= LEX_CHAR_STATE50;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE60
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE60][i]	= LEX_CHAR_STATE51;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE61
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE61][i]	= LEX_CHAR_STATE51;
	}

	lex_char_state_tab[LEX_CHAR_STATE61][CH_DQ]	= LEX_CHAR_STATE62;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE62
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE62][i]	= LEX_CHAR_STATE_END;
	}
	
	//------------------------------------------------------------------
	// LEX_CHAR_STATE63
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE63][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE63][CH_0]	= LEX_CHAR_STATE64;
	lex_char_state_tab[LEX_CHAR_STATE63][CH_1]	= LEX_CHAR_STATE64;
	lex_char_state_tab[LEX_CHAR_STATE63][CH_2]	= LEX_CHAR_STATE64;
	lex_char_state_tab[LEX_CHAR_STATE63][CH_3]	= LEX_CHAR_STATE64;
	lex_char_state_tab[LEX_CHAR_STATE63][CH_4]	= LEX_CHAR_STATE64;
	lex_char_state_tab[LEX_CHAR_STATE63][CH_5]	= LEX_CHAR_STATE64;
	lex_char_state_tab[LEX_CHAR_STATE63][CH_6]	= LEX_CHAR_STATE64;
	lex_char_state_tab[LEX_CHAR_STATE63][CH_7]	= LEX_CHAR_STATE64;

	lex_char_state_tab[LEX_CHAR_STATE63][CH_x]	= LEX_CHAR_STATE65;
	lex_char_state_tab[LEX_CHAR_STATE63][CH_X]	= LEX_CHAR_STATE65;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE64
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE64][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE64][CH_0]	= LEX_CHAR_STATE64;
	lex_char_state_tab[LEX_CHAR_STATE64][CH_1]	= LEX_CHAR_STATE64;
	lex_char_state_tab[LEX_CHAR_STATE64][CH_2]	= LEX_CHAR_STATE64;
	lex_char_state_tab[LEX_CHAR_STATE64][CH_3]	= LEX_CHAR_STATE64;
	lex_char_state_tab[LEX_CHAR_STATE64][CH_4]	= LEX_CHAR_STATE64;
	lex_char_state_tab[LEX_CHAR_STATE64][CH_5]	= LEX_CHAR_STATE64;
	lex_char_state_tab[LEX_CHAR_STATE64][CH_6]	= LEX_CHAR_STATE64;
	lex_char_state_tab[LEX_CHAR_STATE64][CH_7]	= LEX_CHAR_STATE64;

	lex_char_state_tab[LEX_CHAR_STATE64][CH_DOT]	= LEX_CHAR_STATE76;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE65
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE65][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE65][CH_0]	= LEX_CHAR_STATE65;
	lex_char_state_tab[LEX_CHAR_STATE65][CH_1]	= LEX_CHAR_STATE65;
	lex_char_state_tab[LEX_CHAR_STATE65][CH_2]	= LEX_CHAR_STATE65;
	lex_char_state_tab[LEX_CHAR_STATE65][CH_3]	= LEX_CHAR_STATE65;
	lex_char_state_tab[LEX_CHAR_STATE65][CH_4]	= LEX_CHAR_STATE65;
	lex_char_state_tab[LEX_CHAR_STATE65][CH_5]	= LEX_CHAR_STATE65;
	lex_char_state_tab[LEX_CHAR_STATE65][CH_6]	= LEX_CHAR_STATE65;
	lex_char_state_tab[LEX_CHAR_STATE65][CH_7]	= LEX_CHAR_STATE65;
	lex_char_state_tab[LEX_CHAR_STATE65][CH_8]	= LEX_CHAR_STATE65;
	lex_char_state_tab[LEX_CHAR_STATE65][CH_9]	= LEX_CHAR_STATE65;

	lex_char_state_tab[LEX_CHAR_STATE65][CH_a]	= LEX_CHAR_STATE65;
	lex_char_state_tab[LEX_CHAR_STATE65][CH_b]	= LEX_CHAR_STATE65;
	lex_char_state_tab[LEX_CHAR_STATE65][CH_c]	= LEX_CHAR_STATE65;
	lex_char_state_tab[LEX_CHAR_STATE65][CH_d]	= LEX_CHAR_STATE65;
	lex_char_state_tab[LEX_CHAR_STATE65][CH_e]	= LEX_CHAR_STATE65;
	lex_char_state_tab[LEX_CHAR_STATE65][CH_f]	= LEX_CHAR_STATE65;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE66
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE66][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE66][CH_0]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE66][CH_1]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE66][CH_2]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE66][CH_3]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE66][CH_4]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE66][CH_5]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE66][CH_6]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE66][CH_7]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE66][CH_8]	= LEX_CHAR_STATE66;
	lex_char_state_tab[LEX_CHAR_STATE66][CH_9]	= LEX_CHAR_STATE66;

	lex_char_state_tab[LEX_CHAR_STATE66][CH_e]	= LEX_CHAR_STATE48;
	lex_char_state_tab[LEX_CHAR_STATE66][CH_E]	= LEX_CHAR_STATE48;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE67
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE67][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE67][CH_DOT]		= LEX_CHAR_STATE86;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE68
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE68][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE69
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE69][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE70
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE70][i]	= LEX_CHAR_STATE46;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE71
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE71][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE72
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE72][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE73
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE73][i]	= LEX_CHAR_STATE_END;
	}
	
	lex_char_state_tab[LEX_CHAR_STATE73][CH_EQU]	= LEX_CHAR_STATE85;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE74
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE74][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE75
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE75][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE76
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE76][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE76][CH_0]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE76][CH_1]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE76][CH_2]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE76][CH_3]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE76][CH_4]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE76][CH_5]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE76][CH_6]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE76][CH_7]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE76][CH_8]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE76][CH_9]	= LEX_CHAR_STATE77;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE77
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE77][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE77][CH_0]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE77][CH_1]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE77][CH_2]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE77][CH_3]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE77][CH_4]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE77][CH_5]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE77][CH_6]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE77][CH_7]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE77][CH_8]	= LEX_CHAR_STATE77;
	lex_char_state_tab[LEX_CHAR_STATE77][CH_9]	= LEX_CHAR_STATE77;

	lex_char_state_tab[LEX_CHAR_STATE77][CH_e]	= LEX_CHAR_STATE78;
	lex_char_state_tab[LEX_CHAR_STATE77][CH_E]	= LEX_CHAR_STATE78;
	lex_char_state_tab[LEX_CHAR_STATE77][CH_f]	= LEX_CHAR_STATE81;
	lex_char_state_tab[LEX_CHAR_STATE77][CH_F]	= LEX_CHAR_STATE81;
	lex_char_state_tab[LEX_CHAR_STATE77][CH_l]	= LEX_CHAR_STATE81;
	lex_char_state_tab[LEX_CHAR_STATE77][CH_L]	= LEX_CHAR_STATE81;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE78
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE78][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE78][CH_0]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE78][CH_1]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE78][CH_2]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE78][CH_3]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE78][CH_4]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE78][CH_5]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE78][CH_6]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE78][CH_7]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE78][CH_8]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE78][CH_9]	= LEX_CHAR_STATE79;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE79
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE79][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE79][CH_0]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE79][CH_1]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE79][CH_2]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE79][CH_3]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE79][CH_4]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE79][CH_5]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE79][CH_6]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE79][CH_7]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE79][CH_8]	= LEX_CHAR_STATE79;
	lex_char_state_tab[LEX_CHAR_STATE79][CH_9]	= LEX_CHAR_STATE79;

	lex_char_state_tab[LEX_CHAR_STATE79][CH_f]	= LEX_CHAR_STATE80;
	lex_char_state_tab[LEX_CHAR_STATE79][CH_F]	= LEX_CHAR_STATE80;
	lex_char_state_tab[LEX_CHAR_STATE79][CH_l]	= LEX_CHAR_STATE80;
	lex_char_state_tab[LEX_CHAR_STATE79][CH_L]	= LEX_CHAR_STATE80;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE80
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE80][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE81
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE81][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE82
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE82][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE83
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE83][i]	= LEX_CHAR_STATE61;
	}

	lex_char_state_tab[LEX_CHAR_STATE83][CH_SQ]	= LEX_CHAR_STATE84;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE84
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE84][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE85
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE85][i]	= LEX_CHAR_STATE_END;
	}

	//------------------------------------------------------------------
	// LEX_CHAR_STATE86
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE86][i]	= LEX_CHAR_STATE_END;
	}

	lex_char_state_tab[LEX_CHAR_STATE86][CH_DOT]		= LEX_CHAR_STATE87;

	//------------------------------------------------------------------
	// LEX_CHAR_STATE87
	//------------------------------------------------------------------
	for(i=0; i<LEX_INPUT_CHARS; i++)
	{
		lex_char_state_tab[LEX_CHAR_STATE87][i]	= LEX_CHAR_STATE_END;
	}


	

	printf("--lex_char_state_tab init(end)---\n");
}









