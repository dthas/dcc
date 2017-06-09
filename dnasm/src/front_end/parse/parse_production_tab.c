//===========================================================================
// parse_production_tab.c
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
#include	"dnasm_parse.h"
#include	<stdio.h>
#include	"dnasm_lex_char.h"
#include	"dnasm_lex_word.h"
#include	"dnasm_prototype.h"

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
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '(', EAX, EBX, ECX, EDX, EBP, ESP, ESI, EDI, EIP, CS, DS, ES}
	parse_production_tab[PRODUCTION_1][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_1][FIRST_SET][EAX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][EBX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][ECX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][EDX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][EBP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][ESP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][ESI]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][EDI]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][EIP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][CS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][DS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][ES]		= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_1][FIRST_SET][DWORD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][WORD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][BYTE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_1][FIRST_SET][BX]		= PRODUCTION_Y;

	
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

	parse_production_tab[PRODUCTION_2][FIRST_SET][EAX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][EBX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][ECX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][EDX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][EBP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][ESP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][ESI]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][EDI]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][EIP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][CS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][DS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][ES]		= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_2][FIRST_SET][DWORD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][WORD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_2][FIRST_SET][BYTE]		= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_2][FIRST_SET][BX]		= PRODUCTION_Y;

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
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '('}
	parse_production_tab[PRODUCTION_3][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_3][FIRST_SET][EAX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][EBX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][ECX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][EDX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][EBP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][ESP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][ESI]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][EDI]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][EIP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][CS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][DS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][ES]		= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_3][FIRST_SET][DWORD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][WORD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_3][FIRST_SET][BYTE]		= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_3][FIRST_SET][BX]		= PRODUCTION_Y;

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
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '('}
	parse_production_tab[PRODUCTION_4][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_4][FIRST_SET][EAX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][EBX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][ECX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][EDX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][EBP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][ESP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][ESI]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][EDI]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][EIP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][CS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][DS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][ES]		= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_4][FIRST_SET][DWORD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][WORD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_4][FIRST_SET][BYTE]		= PRODUCTION_Y;

	//add on 2013-8-29
	parse_production_tab[PRODUCTION_4][FIRST_SET][BX]		= PRODUCTION_Y;

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
	//{IDENTIFIER, CONSTANT, STRING_LITERAL, '('}
	parse_production_tab[PRODUCTION_5][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][OP_L_PARENTHESE]	= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_5][FIRST_SET][EAX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][EBX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][ECX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][EDX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][EBP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][ESP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][ESI]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][EDI]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][EIP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][CS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][DS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][ES]		= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_5][FIRST_SET][DWORD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][WORD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_5][FIRST_SET][BYTE]		= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_5][FIRST_SET][BX]		= PRODUCTION_Y;

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
	//{GLOBAL, EXTERN, DB, DW, DD, DQ, DT, DY, RESB, RESW, RESQ, RESY, IDENTIFIER }
	parse_production_tab[PRODUCTION_6][FIRST_SET][GLOBAL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][EXTERN]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_6][FIRST_SET][DB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][DW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][DD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][DQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][DT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][DY]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][RESB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][RESW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][RESQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_6][FIRST_SET][RESY]		= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_6][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;

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
	//{GLOBAL, EXTERN, DB, DW, DD, DQ, DT, DY, RESB, RESW, RESQ, RESY ,IDENTIFIER }
	parse_production_tab[PRODUCTION_7][FIRST_SET][GLOBAL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][EXTERN]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_7][FIRST_SET][DB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][DW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][DD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][DQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][DT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][DY]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][RESB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][RESW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][RESQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_7][FIRST_SET][RESY]		= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_7][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;

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
	//{IDENTIFIER}
	parse_production_tab[PRODUCTION_8][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;

	// follow set
	//{DB, DW, DD, DQ, DT, DY, RESB, RESW, RESQ, RESY }
	parse_production_tab[PRODUCTION_8][FOLLOW_SET][DB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FOLLOW_SET][DW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FOLLOW_SET][DD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FOLLOW_SET][DQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FOLLOW_SET][DT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FOLLOW_SET][DY]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FOLLOW_SET][RESB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FOLLOW_SET][RESW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FOLLOW_SET][RESQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_8][FOLLOW_SET][RESY]		= PRODUCTION_Y;

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
	//{GLOBAL, EXTERN}
	parse_production_tab[PRODUCTION_9][FIRST_SET][GLOBAL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_9][FIRST_SET][EXTERN]		= PRODUCTION_Y;	

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
	//{DB, DW, DD, DQ, DT, DY, RESB, RESW, RESQ, RESY }
	parse_production_tab[PRODUCTION_10][FIRST_SET][DB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][DW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][DD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][DQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][DT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][DY]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][RESB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][RESW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][RESQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_10][FIRST_SET][RESY]		= PRODUCTION_Y;

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
	//{IDENTIFIER, CONSTANT,STRING_LITERAL, '(', '''
	parse_production_tab[PRODUCTION_11][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][CONST_DEC]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][CONST_S_INT_8]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][CONST_OCT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][CONST_HEX]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][CONST_FLOAT]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][CONST_STRING]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][OP_L_PARENTHESE] = PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][CONST_S_QUOTE]	= PRODUCTION_Y;
	
	parse_production_tab[PRODUCTION_11][FIRST_SET][EAX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][EBX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][ECX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][EDX]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][EBP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][ESP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][ESI]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][EDI]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][EIP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][CS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][DS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][ES]		= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_11][FIRST_SET][DWORD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][WORD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_11][FIRST_SET][BYTE]		= PRODUCTION_Y;

	parse_production_tab[PRODUCTION_11][FIRST_SET][BX]		= PRODUCTION_Y;

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
	// {IDENTIFIER, MOV,ADD,SUB,MUL,DIV,CALL,RET,JMP,JA,JB,JE,JAE,MBE,JNE,PUSH,POP,CMP}
	parse_production_tab[PRODUCTION_12][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_12][FIRST_SET][MOV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][ADD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][SUB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][DIV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][CALL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][RET]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][JMP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][JA]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][JB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][JE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][JAE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][JBE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][JNE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][PUSH]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][POP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][CMP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][XOR]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_12][FIRST_SET][INT]		= PRODUCTION_Y;
	
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
	// {IDENTIFIER}
	parse_production_tab[PRODUCTION_13][FIRST_SET][XOR]	= PRODUCTION_Y;	

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
	//{MOV,ADD,SUB,MUL,DIV,CALL,RET,JMP,JA,JB,JE,JAE,MBE,JNE,PUSH,POP,CMP}
	parse_production_tab[PRODUCTION_14][FIRST_SET][MOV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][ADD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][SUB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][DIV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][CALL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][RET]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][JMP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][JA]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][JB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][JE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][JAE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][JBE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][JNE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][PUSH]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][POP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][CMP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_14][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_14][FIRST_SET][XOR]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_14][FIRST_SET][INT]		= PRODUCTION_Y;

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
	//{MOV}
	parse_production_tab[PRODUCTION_15][FIRST_SET][MOV]		= PRODUCTION_Y;
	
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
	//{ADD}
	parse_production_tab[PRODUCTION_16][FIRST_SET][ADD]		= PRODUCTION_Y;
	
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
	//{SUB}
	parse_production_tab[PRODUCTION_17][FIRST_SET][SUB]		= PRODUCTION_Y;
	
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
	//{MUL}
	parse_production_tab[PRODUCTION_18][FIRST_SET][MUL]	= PRODUCTION_Y;
	
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
	// {DIV}
	parse_production_tab[PRODUCTION_19][FIRST_SET][DIV]			= PRODUCTION_Y;
		
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
	//{CALL}
	parse_production_tab[PRODUCTION_20][FIRST_SET][CALL]		= PRODUCTION_Y;
	
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
	//{RET}
	parse_production_tab[PRODUCTION_21][FIRST_SET][RET]		= PRODUCTION_Y;
	
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
	// {JMP}
	parse_production_tab[PRODUCTION_22][FIRST_SET][JMP]		= PRODUCTION_Y;
	
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
	// {JA}
	parse_production_tab[PRODUCTION_23][FIRST_SET][JA]		= PRODUCTION_Y;
		
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
	//{JB}
	parse_production_tab[PRODUCTION_24][FIRST_SET][JB]		= PRODUCTION_Y;
	
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
	//{JE}
	parse_production_tab[PRODUCTION_25][FIRST_SET][JE]		= PRODUCTION_Y;
	
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
	//{JAE}
	parse_production_tab[PRODUCTION_26][FIRST_SET][JAE]	= PRODUCTION_Y;
	
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
	// {JBE}
	parse_production_tab[PRODUCTION_27][FIRST_SET][JBE]		= PRODUCTION_Y;
			
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
	// {JNE}
	parse_production_tab[PRODUCTION_28][FIRST_SET][JNE]		= PRODUCTION_Y;
	
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
	// {PUSH}
	parse_production_tab[PRODUCTION_29][FIRST_SET][PUSH]		= PRODUCTION_Y;
		
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
	// {POP}
	parse_production_tab[PRODUCTION_30][FIRST_SET][POP]		= PRODUCTION_Y;
	
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
	// {CMP}
	parse_production_tab[PRODUCTION_31][FIRST_SET][CMP]		= PRODUCTION_Y;
	
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
	//{MOV,ADD,SUB,MUL,DIV,CALL,RET,JMP,JA,JB,JE,JAE,MBE,JNE,PUSH,POP,CMP,GLOBAL, EXTERN, DB, DW, DD, DQ, DT, DY, RESB, RESW, RESQ, RESY}
	parse_production_tab[PRODUCTION_32][FIRST_SET][MOV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][ADD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][SUB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][DIV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][CALL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][RET]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][JMP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][JA]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][JB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][JE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][JAE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][JBE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][JNE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][PUSH]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][POP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][CMP]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_32][FIRST_SET][GLOBAL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][EXTERN]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_32][FIRST_SET][DB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][DW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][DD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][DQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][DT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][DY]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][RESB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][RESW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][RESQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_32][FIRST_SET][RESY]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_32][FIRST_SET][XOR]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_32][FIRST_SET][INT]		= PRODUCTION_Y;

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
	//{MOV,ADD,SUB,MUL,DIV,CALL,RET,JMP,JA,JB,JE,JAE,MBE,JNE,PUSH,POP,CMP,GLOBAL, EXTERN, DB, DW, DD, DQ, DT, DY, RESB, RESW, RESQ, RESY, '['}
	parse_production_tab[PRODUCTION_33][FIRST_SET][MOV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][ADD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][SUB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][DIV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][CALL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][RET]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][JMP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][JA]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][JB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][JE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][JAE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][JBE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][JNE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][PUSH]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][POP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][CMP]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_33][FIRST_SET][GLOBAL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][EXTERN]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_33][FIRST_SET][DB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][DW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][DD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][DQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][DT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][DY]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][RESB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][RESW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][RESQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][RESY]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_33][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_33][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_33][FIRST_SET][XOR]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_33][FIRST_SET][INT]		= PRODUCTION_Y;

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
	//{SECTION, BITS}
	parse_production_tab[PRODUCTION_34][FIRST_SET][SECTION]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_34][FIRST_SET][BITS]		= PRODUCTION_Y;

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
	// {OP_MUL, OP_DIV}
	parse_production_tab[PRODUCTION_35][FIRST_SET][OP_MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_35][FIRST_SET][OP_DIV]		= PRODUCTION_Y;

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
	// {OP_PLUS, OP_MINUS}
	parse_production_tab[PRODUCTION_36][FIRST_SET][OP_PLUS]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_36][FIRST_SET][OP_MINUS]	= PRODUCTION_Y;
	
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
	//{GLOBAL, EXTERN, DB, DW, DD, DQ, DT, DY, RESB, RESW, RESQ, RESY }
	parse_production_tab[PRODUCTION_37][FIRST_SET][GLOBAL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][EXTERN]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_37][FIRST_SET][DB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][DW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][DD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][DQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][DT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][DY]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][RESB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][RESW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][RESQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_37][FIRST_SET][RESY]		= PRODUCTION_Y;


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
	//{MOV,ADD,SUB,MUL,DIV,CALL,RET,JMP,JA,JB,JE,JAE,MBE,JNE,PUSH,POP,CMP}
	parse_production_tab[PRODUCTION_38][FIRST_SET][MOV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][ADD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][SUB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][DIV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][CALL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][RET]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][JMP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][JA]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][JB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][JE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][JAE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][JBE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][JNE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][PUSH]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][POP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_38][FIRST_SET][CMP]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_38][FIRST_SET][XOR]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_38][FIRST_SET][INT]		= PRODUCTION_Y;

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
	// {IDENTIFIER}
	parse_production_tab[PRODUCTION_39][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;

	// follow set
	//{MOV,ADD,SUB,MUL,DIV,CALL,RET,JMP,JA,JB,JE,JAE,MBE,JNE,PUSH,POP,CMP}
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][MOV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][ADD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][SUB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][DIV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][CALL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][RET]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][JMP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][JA]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][JB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][JE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][JAE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][JBE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][JNE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][PUSH]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][POP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][CMP]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][XOR]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_39][FOLLOW_SET][INT]		= PRODUCTION_Y;
	
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
	//{MOV,ADD,SUB,MUL,DIV,CALL,RET,JMP,JA,JB,JE,JAE,MBE,JNE,PUSH,POP,CMP}
	parse_production_tab[PRODUCTION_40][FIRST_SET][MOV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][ADD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][SUB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][DIV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][CALL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][RET]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][JMP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][JA]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][JB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][JE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][JAE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][JBE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][JNE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][PUSH]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][POP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_40][FIRST_SET][CMP]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_40][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_40][FIRST_SET][XOR]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_40][FIRST_SET][INT]		= PRODUCTION_Y;

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
	//{MOV,ADD,SUB,MUL,DIV,CALL,RET,JMP,JA,JB,JE,JAE,MBE,JNE,PUSH,POP,CMP,GLOBAL, EXTERN, DB, DW, DD, DQ, DT, DY, RESB, RESW, RESQ, RESY, '['}
	parse_production_tab[PRODUCTION_41][FIRST_SET][MOV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][ADD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][SUB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][DIV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][CALL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][RET]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][JMP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][JA]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][JB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][JE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][JAE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][JBE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][JNE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][PUSH]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][POP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][CMP]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_41][FIRST_SET][GLOBAL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][EXTERN]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_41][FIRST_SET][DB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][DW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][DD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][DQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][DT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][DY]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][RESB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][RESW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][RESQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][RESY]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_41][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_41][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_41][FIRST_SET][XOR]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_41][FIRST_SET][INT]		= PRODUCTION_Y;

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
	//{'['}	
	parse_production_tab[PRODUCTION_42][FIRST_SET][OP_L_BRACKET]	= PRODUCTION_Y;
	
	// follow set
	//{MOV,ADD,SUB,MUL,DIV,CALL,RET,JMP,JA,JB,JE,JAE,MBE,JNE,PUSH,POP,CMP,GLOBAL, EXTERN, DB, DW, DD, DQ, DT, DY, RESB, RESW, RESQ, RESY}
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][MOV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][ADD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][SUB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][DIV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][CALL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][RET]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][JMP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][JA]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][JB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][JE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][JAE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][JBE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][JNE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][PUSH]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][POP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][CMP]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][GLOBAL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][EXTERN]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][DB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][DW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][DD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][DQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][DT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][DY]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][RESB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][RESW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][RESQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][RESY]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][IDENTIFIER]	= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][XOR]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_42][FOLLOW_SET][INT]		= PRODUCTION_Y;

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
	//{MOV,ADD,SUB,MUL,DIV,CALL,RET,JMP,JA,JB,JE,JAE,MBE,JNE,PUSH,POP,CMP,GLOBAL, EXTERN, DB, DW, DD, DQ, DT, DY, RESB, RESW, RESQ, RESY}
	parse_production_tab[PRODUCTION_43][FIRST_SET][MOV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][ADD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][SUB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][MUL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][DIV]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][CALL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][RET]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][JMP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][JA]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][JB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][JE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][JAE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][JBE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][JNE]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][PUSH]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][POP]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][CMP]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_43][FIRST_SET][GLOBAL]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][EXTERN]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_43][FIRST_SET][DB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][DW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][DD]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][DQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][DT]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][DY]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][RESB]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][RESW]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][RESQ]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][RESY]		= PRODUCTION_Y;
	parse_production_tab[PRODUCTION_43][FIRST_SET][IDENTIFIER]	= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_43][FIRST_SET][XOR]		= PRODUCTION_Y;	
	parse_production_tab[PRODUCTION_43][FIRST_SET][INT]		= PRODUCTION_Y;

	//------------------------------------------------------------------
	// PRODUCTION_44
	//------------------------------------------------------------------
/*
	for(i=0; i<SETS; i++)
	{
		for(j=0; j<PARSE_WORDS; j++)
		{
			parse_production_tab[PRODUCTION_44][i][j]	= PRODUCTION_N;
		}
	}

	// first set
	// {OP_XOR}
	parse_production_tab[PRODUCTION_44][FIRST_SET][OP_XOR]		= PRODUCTION_Y;
*/
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
	// {INT}
	parse_production_tab[PRODUCTION_45][FIRST_SET][INT]		= PRODUCTION_Y;
	
	
	


	printf("--parse_productiontab_init(end)---\n");
}









