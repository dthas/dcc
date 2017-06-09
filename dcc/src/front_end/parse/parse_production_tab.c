//===========================================================================
// parse_production_tab.c
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
#include	"dcc_parse.h"
#include	<stdio.h>
#include	"dcc_lex_char.h"
#include	"dcc_lex_word.h"
#include	"dcc_prototype.h"

//===========================================================================
// init
//===========================================================================
PUBLIC	void	parse_productiontab_init()
{
	printf("--parse_productiontab_init(beg)---\n");

	s32 i,j;

	p_parse_production_tab = parse_production_tab;

	//------------------------------------------------------------------
	// PRODUCTION_1 
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_1][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '('}
	parse_production_tab[PRODUCTION_1][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;

	
	//------------------------------------------------------------------
	// PRODUCTION_2
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_2][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '('}
	parse_production_tab[PRODUCTION_2][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_3
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_3][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_3][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][OP_MINUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][OP_NOT]		= PRODUCTION_Y;


	//------------------------------------------------------------------
	// PRODUCTION_4
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_4][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_4][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][OP_MINUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_5
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_5][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{'&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_5][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][OP_MINUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_6
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_6][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_6][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][OP_MINUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_7
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_7][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_7][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][OP_MINUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_8
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_8][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_8][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FIRST_SET][OP_MINUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_9
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_9][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_9][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][OP_MINUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_10
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_10][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_10][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_11
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_11][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_11][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_12
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_12][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_12][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_13
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_13][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_13][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_13][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_13][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_13][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_13][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_13][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_13][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_13][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_13][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_13][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_13][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_13][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_13][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_13][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_13][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_13][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_13][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_14
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_14][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_14][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_15
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_15][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_15][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_15][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_15][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_15][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_15][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_15][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_15][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_15][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_15][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_15][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_15][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_15][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_15][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_15][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_15][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_15][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_15][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_16
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_16][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_16][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_16][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_16][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_16][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_16][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_16][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_16][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_16][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_16][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_16][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_16][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_16][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_16][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_16][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_16][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_16][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_16][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_17
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_17][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_17][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_17][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_17][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_17][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_17][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_17][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_17][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_17][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_17][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_17][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_17][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_17][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_17][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_17][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_17][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_17][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_17][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_18
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_18][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_18][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_18][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_18][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_18][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_18][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_18][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_18][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_18][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_18][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_18][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_18][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_18][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_18][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_18][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_18][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_18][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_18][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_19
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_19][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {'=', MUL_ASSIGN, DIV_ASSIGN, MOD_ASSIGN, ADD_ASSIGN,SUB_ASSIGN, LEFT_ASSIGN, RIGHT_ASSIGN, AND_ASSIGN,XOR_ASSIGN, OR_ASSIGN }

	parse_production_tab[PRODUCTION_19][FIRST_SET][OP_EQU]			= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_19][FIRST_SET][OP_MUL_EQU]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_19][FIRST_SET][OP_DIV_EQU]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_19][FIRST_SET][OP_MOD_EQU]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_19][FIRST_SET][OP_PLUS_EQU]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_19][FIRST_SET][OP_MINUS_EQU]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_19][FIRST_SET][OP_SHIFT_LEFT_EQU]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_19][FIRST_SET][OP_SHIFT_RIGHT_EQU]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_19][FIRST_SET][OP_AND_EQU]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_19][FIRST_SET][OP_XOR_EQU]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_19][FIRST_SET][OP_OR_EQU]		= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_20
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_20][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_20][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_20][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_20][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_20][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_20][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_20][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_20][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_20][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_20][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_20][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_20][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_20][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_20][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_20][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_20][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_20][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_20][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_21
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_21][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_21][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_21][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_21][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_21][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_21][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_21][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_21][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_21][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_21][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_21][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_21][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_21][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_21][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_21][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_21][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_21][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_21][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_22
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_22][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {TYPEDEF, EXTERN, STATIC, AUTO, REGISTER, VOID, CHAR, SHORT,INT, LONG, FLOAT, DOUBLE, SIGNED, UNSIGNED, TYPE_NAME, STRUCT , UNION, ENUM, CONST, VOLATILE}

	parse_production_tab[PRODUCTION_22][FIRST_SET][TYPEDEF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][EXTERN]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][STATIC]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][AUTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][REGISTER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_22][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_23
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_23][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {TYPEDEF, EXTERN, STATIC, AUTO, REGISTER, VOID, CHAR, SHORT,INT, LONG, FLOAT, DOUBLE, SIGNED, UNSIGNED, TYPE_NAME, STRUCT , UNION, ENUM, CONST, VOLATILE}

	parse_production_tab[PRODUCTION_23][FIRST_SET][TYPEDEF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][EXTERN]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][STATIC]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][AUTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][REGISTER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_23][FIRST_SET][VOLATILE]	= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_24
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_24][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{'*', IDENTIFIER, '(', '['}
	parse_production_tab[PRODUCTION_24][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_24][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_24][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_24][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_25
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_25][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{'*', IDENTIFIER, '(', '['}
	parse_production_tab[PRODUCTION_25][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_25][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_25][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_25][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_26
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_26][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{TYPEDEF, EXTERN, STATIC, AUTO, REGISTER}
	parse_production_tab[PRODUCTION_26][FIRST_SET][TYPEDEF]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_26][FIRST_SET][EXTERN]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_26][FIRST_SET][STATIC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_26][FIRST_SET][AUTO]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_26][FIRST_SET][REGISTER]= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_27
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_27][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {VOID, CHAR, SHORT, INT, LONG, FLOAT, DOUBLE, SIGNED,UNSIGNED, TYPE_NAME, STRUCT , UNION, ENUM}
	parse_production_tab[PRODUCTION_27][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_27][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_27][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_27][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_27][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_27][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_27][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_27][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_27][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_27][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_27][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_27][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_27][FIRST_SET][ENUM]		= PRODUCTION_Y;
		
	//------------------------------------------------------------------
	// PRODUCTION_28
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_28][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {STRUCT , UNION}
	parse_production_tab[PRODUCTION_28][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_28][FIRST_SET][UNION]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_29
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_29][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {STRUCT , UNION}
	parse_production_tab[PRODUCTION_29][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_29][FIRST_SET][UNION]		= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_30
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_30][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {VOID, CHAR, SHORT,INT, LONG, FLOAT, DOUBLE, SIGNED, UNSIGNED, TYPE_NAME, STRUCT , UNION, ENUM, CONST, VOLATILE}
	parse_production_tab[PRODUCTION_30][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_30][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_30][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_30][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_30][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_30][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_30][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_30][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_30][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_30][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_30][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_30][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_30][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_30][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_30][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_31
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_31][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {VOID, CHAR, SHORT,INT, LONG, FLOAT, DOUBLE, SIGNED, UNSIGNED, TYPE_NAME, STRUCT , UNION, ENUM, CONST, VOLATILE}
	parse_production_tab[PRODUCTION_31][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_31][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_31][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_31][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_31][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_31][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_31][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_31][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_31][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_31][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_31][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_31][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_31][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_31][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_31][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_32
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_32][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {VOID, CHAR, SHORT,INT, LONG, FLOAT, DOUBLE, SIGNED, UNSIGNED, TYPE_NAME, STRUCT , UNION, ENUM, CONST, VOLATILE}
	parse_production_tab[PRODUCTION_32][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_33
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_33][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {'*', IDENTIFIER, '(', '['}
	parse_production_tab[PRODUCTION_33][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_34
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_34][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {'*', IDENTIFIER, '(', '[', ':'}
	parse_production_tab[PRODUCTION_34][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_34][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_34][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_34][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_34][FIRST_SET][OP_COLON]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_35
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_35][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {ENUM}
	parse_production_tab[PRODUCTION_35][FIRST_SET][ENUM]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_36
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_36][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {ENUM}
	parse_production_tab[PRODUCTION_36][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_37
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_37][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_37][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_38
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_38][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {CONST, VOLATILE}
	parse_production_tab[PRODUCTION_38][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_39
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_39][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {'*', IDENTIFIER, '('}
	parse_production_tab[PRODUCTION_39][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_40
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_40][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {IDENTIFIER, '('}
	parse_production_tab[PRODUCTION_40][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_41
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_41][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {'*'}	
	parse_production_tab[PRODUCTION_41][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_42
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_42][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {CONST, VOLATILE}
	parse_production_tab[PRODUCTION_42][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_43
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_43][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {TYPEDEF, EXTERN, STATIC, AUTO, REGISTER, VOID, CHAR, SHORT,INT, LONG, FLOAT, DOUBLE, SIGNED, UNSIGNED, TYPE_NAME, STRUCT , UNION, ENUM, CONST, VOLATILE}
	parse_production_tab[PRODUCTION_43][FIRST_SET][TYPEDEF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][EXTERN]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][STATIC]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][AUTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][REGISTER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_44
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_44][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {TYPEDEF, EXTERN, STATIC, AUTO, REGISTER, VOID, CHAR, SHORT,INT, LONG, FLOAT, DOUBLE, SIGNED, UNSIGNED, TYPE_NAME, STRUCT , UNION, ENUM, CONST, VOLATILE}
	parse_production_tab[PRODUCTION_44][FIRST_SET][TYPEDEF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][EXTERN]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][STATIC]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][AUTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][REGISTER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_44][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_45
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_45][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {TYPEDEF, EXTERN, STATIC, AUTO, REGISTER, VOID, CHAR, SHORT,INT, LONG, FLOAT, DOUBLE, SIGNED, UNSIGNED, TYPE_NAME, STRUCT , UNION, ENUM, CONST, VOLATILE}
	parse_production_tab[PRODUCTION_45][FIRST_SET][TYPEDEF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][EXTERN]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][STATIC]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][AUTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][REGISTER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_45][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_46
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_46][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {IDENTIFIER}
	parse_production_tab[PRODUCTION_46][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_47
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_47][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {VOID, CHAR, SHORT,INT, LONG, FLOAT, DOUBLE, SIGNED, UNSIGNED, TYPE_NAME, STRUCT , UNION, ENUM, CONST, VOLATILE}
	parse_production_tab[PRODUCTION_47][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_47][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_47][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_47][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_47][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_47][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_47][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_47][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_47][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_47][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_47][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_47][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_47][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_47][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_47][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_48
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_48][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {'*', '(', '['}
	parse_production_tab[PRODUCTION_48][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_48][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_48][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_49
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_49][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {'(', '['}
	parse_production_tab[PRODUCTION_49][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_49][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_50
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_50][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!', '{'}
	parse_production_tab[PRODUCTION_50][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][OP_NOT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_50][FIRST_SET][OP_L_BRACE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_51
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_51][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!', '{'}
	parse_production_tab[PRODUCTION_51][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][OP_NOT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_51][FIRST_SET][OP_L_BRACE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_52
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_52][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// { IDENTIFIER, CASE, DEFAULT, '{' , CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' , ';', IF, SWITCH, WHILE, DO,FOR, GOTO, CONTINUE, BREAK, RETURN}
	parse_production_tab[PRODUCTION_52][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][CASE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][DEFAULT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][OP_L_BRACE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][OP_NOT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][SEMICOLON]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][IF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][SWITCH]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][WHILE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][DO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][FOR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][GOTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][CONTINUE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][BREAK]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_52][FIRST_SET][RETURN]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_53
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_53][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// { IDENTIFIER, CASE, DEFAULT}
	parse_production_tab[PRODUCTION_53][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_53][FIRST_SET][CASE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_53][FIRST_SET][DEFAULT]		= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_54
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_54][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// { '{' }
	parse_production_tab[PRODUCTION_54][FIRST_SET][OP_L_BRACE]	= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_55
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_55][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {'*', IDENTIFIER, '(', '[', ';'}
	parse_production_tab[PRODUCTION_55][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_55][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_55][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_55][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_55][FIRST_SET][SEMICOLON]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_56
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_56][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// { IDENTIFIER, CASE, DEFAULT, '{' , CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' , ';', IF, SWITCH, WHILE, DO,FOR, GOTO, CONTINUE, BREAK, RETURN}
	parse_production_tab[PRODUCTION_56][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][CASE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][DEFAULT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][OP_L_BRACE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][OP_NOT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][SEMICOLON]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][IF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][SWITCH]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][WHILE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][DO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][FOR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][GOTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][CONTINUE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][BREAK]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_56][FIRST_SET][RETURN]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_57
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_57][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!', ';'}
	parse_production_tab[PRODUCTION_57][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][OP_NOT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_57][FIRST_SET][SEMICOLON]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_58
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_58][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// { IF, SWITCH}	
	parse_production_tab[PRODUCTION_58][FIRST_SET][IF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_58][FIRST_SET][SWITCH]		= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_59
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_59][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// { WHILE, DO,FOR}
	parse_production_tab[PRODUCTION_59][FIRST_SET][WHILE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_59][FIRST_SET][DO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_59][FIRST_SET][FOR]		= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_60
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_60][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// { GOTO, CONTINUE, BREAK, RETURN}
	parse_production_tab[PRODUCTION_60][FIRST_SET][GOTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_60][FIRST_SET][CONTINUE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_60][FIRST_SET][BREAK]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_60][FIRST_SET][RETURN]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_61
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_61][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {TYPEDEF, EXTERN, STATIC, AUTO, REGISTER, VOID, CHAR, SHORT,INT, LONG, FLOAT, DOUBLE, SIGNED, UNSIGNED, TYPE_NAME,STRUCT , UNION, ENUM, CONST, VOLATILE, '*', IDENTIFIER,'(', '['}
	parse_production_tab[PRODUCTION_61][FIRST_SET][TYPEDEF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][EXTERN]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][STATIC]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][AUTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][REGISTER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][VOLATILE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_61][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_62
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_62][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {TYPEDEF, EXTERN, STATIC, AUTO, REGISTER, VOID, CHAR, SHORT,INT, LONG, FLOAT, DOUBLE, SIGNED, UNSIGNED, TYPE_NAME,STRUCT , UNION, ENUM, CONST, VOLATILE, '*', IDENTIFIER,'(', '['}
	parse_production_tab[PRODUCTION_62][FIRST_SET][TYPEDEF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][EXTERN]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][STATIC]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][AUTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][REGISTER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][VOLATILE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_62][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_63
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_63][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {TYPEDEF, EXTERN, STATIC, AUTO, REGISTER, VOID, CHAR, SHORT,INT, LONG, FLOAT, DOUBLE, SIGNED, UNSIGNED, TYPE_NAME,STRUCT , UNION, ENUM, CONST, VOLATILE, '*', IDENTIFIER,'(', '['}
	parse_production_tab[PRODUCTION_63][FIRST_SET][TYPEDEF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][EXTERN]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][STATIC]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][AUTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][REGISTER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][VOLATILE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_63][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_64(postfix_expression_1)
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_64][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {++,->,--,[,(,.}
	parse_production_tab[PRODUCTION_64][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_64][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_64][FIRST_SET][OP_POINTOR]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_64][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_64][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_64][FIRST_SET][OP_DOT]		= PRODUCTION_Y;	

	//------------------------------------------------------------------
	// PRODUCTION_65
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_65][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_65][FIRST_SET][OP_COMMA]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_66
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_66][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {*,/,%}
	parse_production_tab[PRODUCTION_66][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_66][FIRST_SET][OP_DIV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_66][FIRST_SET][OP_MOD]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_67
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_67][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {*,/,%}
	parse_production_tab[PRODUCTION_67][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_67][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_68
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_68][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {>>,<<}
	parse_production_tab[PRODUCTION_68][FIRST_SET][OP_SHIFT_LEFT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_68][FIRST_SET][OP_SHIFT_RIGHT]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_69
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_69][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {<,>,<=,>=}
	parse_production_tab[PRODUCTION_69][FIRST_SET][OP_LOW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_69][FIRST_SET][OP_ABOVE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_69][FIRST_SET][OP_LOW_EQU]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_69][FIRST_SET][OP_ABOVE_EQU]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_70
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_70][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {==,!=}
	parse_production_tab[PRODUCTION_70][FIRST_SET][OP_EQU_EQU]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_70][FIRST_SET][OP_NOT_EQU]	= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_71
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_71][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {&}
	parse_production_tab[PRODUCTION_71][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_72
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_72][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {&}
	parse_production_tab[PRODUCTION_72][FIRST_SET][OP_XOR]		= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_73
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_73][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {&}
	parse_production_tab[PRODUCTION_73][FIRST_SET][OP_OR]		= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_74
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_74][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {&}
	parse_production_tab[PRODUCTION_74][FIRST_SET][OP_AND_AND]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_75
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_75][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {&}
	parse_production_tab[PRODUCTION_75][FIRST_SET][OP_OR_OR]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_76
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_76][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {&}
	parse_production_tab[PRODUCTION_76][FIRST_SET][OP_Q_COND]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_77
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_77][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {&}
	parse_production_tab[PRODUCTION_77][FIRST_SET][OP_COMMA]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_78
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_78][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {*, IDENTIFIER, (, [, ;}
	parse_production_tab[PRODUCTION_78][FIRST_SET][SEMICOLON]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_78][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_78][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_78][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_78][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_79
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_79][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {*, IDENTIFIER, (, [, ;}
	parse_production_tab[PRODUCTION_79][FIRST_SET][TYPEDEF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][EXTERN]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][STATIC]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][AUTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][REGISTER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_79][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_80
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_80][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {*, IDENTIFIER, (, [, ;}
	parse_production_tab[PRODUCTION_80][FIRST_SET][TYPEDEF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][EXTERN]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][STATIC]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][AUTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][REGISTER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_80][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_81
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_81][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_81][FIRST_SET][OP_COMMA]	= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_82
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_82][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_82][FIRST_SET][OP_EQU]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_83
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_83][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_83][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_84
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_84][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_84][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;

	// follow set
	// {
	parse_production_tab[PRODUCTION_84][FOLLOW_SET][OP_L_BRACE]	= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_85
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_85][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_85][FIRST_SET][OP_L_BRACE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_86
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_86][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_86][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_86][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_86][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_86][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_86][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_86][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_86][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_86][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_86][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_86][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_86][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_86][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_86][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_86][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_86][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_87
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_87][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_87][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_87][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_87][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_87][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_87][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_87][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_87][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_87][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_87][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_87][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_87][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_87][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_87][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_87][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_87][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_88
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_88][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_88][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_88][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_88][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_88][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_88][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_88][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_88][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_88][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_88][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_88][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_88][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_88][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_88][FIRST_SET][ENUM]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_89
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_89][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_89][FIRST_SET][OP_COMMA]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_90
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_90][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_90][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_90][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_90][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_90][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;

	// follow set
	// :
	parse_production_tab[PRODUCTION_90][FOLLOW_SET][OP_COLON]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_91
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_91][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_91][FIRST_SET][OP_COLON]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_92
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_92][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_92][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;

	// follow set
	// {
	parse_production_tab[PRODUCTION_92][FOLLOW_SET][OP_L_BRACE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_93
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_93][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_93][FIRST_SET][OP_L_BRACE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_94
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_94][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_94][FIRST_SET][OP_COMMA]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_95
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_95][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_95][FIRST_SET][OP_EQU]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_96
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_96][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {'[','('}
	parse_production_tab[PRODUCTION_96][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_96][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
		
	//------------------------------------------------------------------
	// PRODUCTION_100
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_100][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_100][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_100][FIRST_SET][VOLATILE]	= PRODUCTION_Y;
	
	// follow set
	// {*}
	parse_production_tab[PRODUCTION_100][FOLLOW_SET][OP_MUL]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_101
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_101][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_101][FIRST_SET][OP_MUL]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_102
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_102][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_102][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_102][FIRST_SET][VOLATILE]	= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_103
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_103][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_103][FIRST_SET][OP_COMMA]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_104
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_104][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_104][FIRST_SET][OP_COMMA]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_105
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_105][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_105][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_105][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_105][FIRST_SET][OP_L_PARENTHESE]= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_105][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_106
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_106][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_106][FIRST_SET][OP_COMMA]	= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_107
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_107][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_107][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_107][FIRST_SET][OP_L_PARENTHESE]= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_107][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_108
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_108][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_108][FIRST_SET][OP_MUL]		= PRODUCTION_Y;

	// follow set
	// {,}
	parse_production_tab[PRODUCTION_108][FOLLOW_SET][OP_L_PARENTHESE]= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_108][FOLLOW_SET][OP_L_BRACKET]	= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_109
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_109][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_109][FIRST_SET][OP_L_PARENTHESE]= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_109][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_110
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_110][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {,}
	parse_production_tab[PRODUCTION_110][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_110][FIRST_SET][OP_L_PARENTHESE]= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_114
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_114][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!', '{'}
	parse_production_tab[PRODUCTION_114][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][OP_L_PARENTHESE]= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][OP_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][OP_NOT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_114][FIRST_SET][OP_L_BRACE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_115
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_115][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!', '{'}
	parse_production_tab[PRODUCTION_115][FIRST_SET][OP_COMMA]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_115][FIRST_SET][OP_R_BRACE]	= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_116
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_116][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!', '{'}
	parse_production_tab[PRODUCTION_116][FIRST_SET][OP_COMMA]	= PRODUCTION_Y;
		
	//------------------------------------------------------------------
	// PRODUCTION_117
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_117][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	parse_production_tab[PRODUCTION_117][FIRST_SET][TYPEDEF]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][EXTERN]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][STATIC]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][AUTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][REGISTER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FIRST_SET][VOLATILE]	= PRODUCTION_Y;


	// follow set
	// {'*', IDENTIFIER, '(', '[', ';'}
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][CASE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][DEFAULT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][OP_L_BRACE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][OP_L_PARENTHESE]= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][OP_MINUS_MINUS]= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][SIZEOF]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][OP_AND]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][OP_MUL]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][OP_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][OP_NEG]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][OP_NOT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][SEMICOLON]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][IF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][SWITCH]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][WHILE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][DO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][FOR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][GOTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][CONTINUE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][BREAK]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_117][FOLLOW_SET][RETURN]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_118
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_118][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// { IDENTIFIER, CASE, DEFAULT, '{' , CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' , ';', IF, SWITCH, WHILE, DO,FOR, GOTO, CONTINUE, BREAK, RETURN}
	parse_production_tab[PRODUCTION_118][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][CASE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][DEFAULT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][OP_L_BRACE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][OP_L_PARENTHESE]= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][OP_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][OP_NOT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][SEMICOLON]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][IF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][SWITCH]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][WHILE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][DO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][FOR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][GOTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][CONTINUE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][BREAK]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_118][FIRST_SET][RETURN]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_119
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_119][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {TYPEDEF, EXTERN, STATIC, AUTO, REGISTER, VOID, CHAR, SHORT,INT, LONG, FLOAT, DOUBLE, SIGNED, UNSIGNED, TYPE_NAME, STRUCT , UNION, ENUM, CONST, VOLATILE}

	parse_production_tab[PRODUCTION_119][FIRST_SET][TYPEDEF]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][EXTERN]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][STATIC]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][AUTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][REGISTER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_119][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_120
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_120][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// { IDENTIFIER, CASE, DEFAULT, '{' , CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' , ';', IF, SWITCH, WHILE, DO,FOR, GOTO, CONTINUE, BREAK, RETURN}
	parse_production_tab[PRODUCTION_120][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][CASE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][DEFAULT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][OP_L_BRACE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][OP_L_PARENTHESE]= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][OP_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][OP_NOT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][SEMICOLON]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][IF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][SWITCH]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][WHILE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][DO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][FOR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][GOTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][CONTINUE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][BREAK]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_120][FIRST_SET][RETURN]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_121
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_121][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// { IDENTIFIER, CASE, DEFAULT, '{' , CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' , ';', IF, SWITCH, WHILE, DO,FOR, GOTO, CONTINUE, BREAK, RETURN}
	parse_production_tab[PRODUCTION_121][FIRST_SET][IF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_121][FIRST_SET][SWITCH]		= PRODUCTION_Y;
	
	//------------------------------------------------------------------
	// PRODUCTION_122
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_122][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// { IDENTIFIER, CASE, DEFAULT, '{' , CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' , ';', IF, SWITCH, WHILE, DO,FOR, GOTO, CONTINUE, BREAK, RETURN}
	parse_production_tab[PRODUCTION_122][FIRST_SET][ELSE]		= PRODUCTION_Y;	

	//------------------------------------------------------------------
	// PRODUCTION_123
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_123][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_123][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_123][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_123][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_123][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_123][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_123][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_123][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_123][FIRST_SET][OP_L_PARENTHESE]= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_123][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_123][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_123][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_123][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_123][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_123][FIRST_SET][OP_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_123][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_123][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_123][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_123][FIRST_SET][OP_R_PARENTHESE]= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_124
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_124][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', INC_OP, DEC_OP, SIZEOF, '&', '*', '+', '-', '~', '!' }
	parse_production_tab[PRODUCTION_124][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_124][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_124][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_124][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_124][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_124][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_124][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_124][FIRST_SET][OP_L_PARENTHESE]= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_124][FIRST_SET][OP_PLUS_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_124][FIRST_SET][OP_MINUS_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_124][FIRST_SET][SIZEOF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_124][FIRST_SET][OP_AND]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_124][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_124][FIRST_SET][OP_PLUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_124][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_124][FIRST_SET][OP_NEG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_124][FIRST_SET][OP_NOT]		= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_124][FIRST_SET][SEMICOLON]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_125
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_125][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {TYPEDEF, EXTERN, STATIC, AUTO, REGISTER, VOID, CHAR, SHORT,INT, LONG, FLOAT, DOUBLE, SIGNED, UNSIGNED, TYPE_NAME,STRUCT , UNION, ENUM, CONST, VOLATILE, '*', IDENTIFIER,'(', '['}
	parse_production_tab[PRODUCTION_125][FIRST_SET][TYPEDEF]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][EXTERN]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][STATIC]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][AUTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][REGISTER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][VOLATILE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_125][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;

	//follow set
	parse_production_tab[PRODUCTION_125][FOLLOW_SET][PARSE_END]	= PRODUCTION_Y;
	

	//------------------------------------------------------------------
	// PRODUCTION_126
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_126][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {TYPEDEF, EXTERN, STATIC, AUTO, REGISTER, VOID, CHAR, SHORT,INT, LONG, FLOAT, DOUBLE, SIGNED, UNSIGNED, TYPE_NAME, STRUCT , UNION, ENUM, CONST, VOLATILE}

	parse_production_tab[PRODUCTION_126][FIRST_SET][TYPEDEF]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][EXTERN]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][STATIC]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][AUTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][REGISTER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	//follow set
	parse_production_tab[PRODUCTION_126][FOLLOW_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FOLLOW_SET][OP_MUL]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FOLLOW_SET][OP_L_PARENTHESE]= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_126][FOLLOW_SET][OP_L_BRACKET]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_127
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_127][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {'*', IDENTIFIER, '(', '['}
	parse_production_tab[PRODUCTION_127][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_127][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_127][FIRST_SET][OP_L_PARENTHESE]= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_127][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_128
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_128][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {'*', IDENTIFIER, '(', '[', ';'}
	parse_production_tab[PRODUCTION_128][FIRST_SET][TYPEDEF]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][EXTERN]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][STATIC]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][AUTO]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][REGISTER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][VOID]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][CHAR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][SHORT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][INT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][LONG]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][FLOAT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][DOUBLE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][SIGNED]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][UNSIGNED]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][TYPE_NAME]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][STRUCT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][UNION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][ENUM]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][CONST]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_128][FIRST_SET][VOLATILE]	= PRODUCTION_Y;

	// follow set
	parse_production_tab[PRODUCTION_128][FOLLOW_SET][OP_L_BRACE]	= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_129
	//------------------------------------------------------------------

	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_129][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// { '{' }
	parse_production_tab[PRODUCTION_129][FIRST_SET][OP_L_BRACE]	= PRODUCTION_Y;





	printf("--parse_productiontab_init(end)---\n");
}









