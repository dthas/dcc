//===========================================================================
// dnasm_parse.h
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

#ifndef	_DNASM_PARSE_H_
#define	_DNASM_PARSE_H_

//-------------------------------------------------------------------------
// setting  
//-------------------------------------------------------------------------
#define	PARSE_PRODUCTIONS	45		//
#define	PARSE_WORDS		128		// reference to dnasm_lex_word
#define	SETS	2				// FIRST_SET && FOLLOW_SET
#define	FIRST_SET	0
#define	FOLLOW_SET	1

#define	SIZE_OF_TEMP_DATA	100		// 100 * 4 bytes

PUBLIC	s32	parse_production_tab[PARSE_PRODUCTIONS][SETS][PARSE_WORDS];

//-------------------------------------------------------------------------
// productions
//-------------------------------------------------------------------------
#define	PRODUCTION_N		FALSE
#define	PRODUCTION_Y		TRUE

#define	PRODUCTION_1		0		//
#define	PRODUCTION_2		1
#define	PRODUCTION_3		2
#define	PRODUCTION_4		3
#define	PRODUCTION_5		4
#define	PRODUCTION_6		5
#define	PRODUCTION_7		6
#define	PRODUCTION_8		7
#define	PRODUCTION_9		8
#define	PRODUCTION_10		9
#define	PRODUCTION_11		10
#define	PRODUCTION_12		11
#define	PRODUCTION_13		12
#define	PRODUCTION_14		13
#define	PRODUCTION_15		14
#define	PRODUCTION_16		15
#define	PRODUCTION_17		16
#define	PRODUCTION_18		17
#define	PRODUCTION_19		18
#define	PRODUCTION_20		19
#define	PRODUCTION_21		20
#define	PRODUCTION_22		21
#define	PRODUCTION_23		22
#define	PRODUCTION_24		23
#define	PRODUCTION_25		24
#define	PRODUCTION_26		25
#define	PRODUCTION_27		26
#define	PRODUCTION_28		27
#define	PRODUCTION_29		28
#define	PRODUCTION_30		29
#define	PRODUCTION_31		30
#define	PRODUCTION_32		31
#define	PRODUCTION_33		32

#define	PRODUCTION_34		33
#define	PRODUCTION_35		34
#define	PRODUCTION_36		35
#define	PRODUCTION_37		36
#define	PRODUCTION_38		37
#define	PRODUCTION_39		38
#define	PRODUCTION_40		39
#define	PRODUCTION_41		40
#define	PRODUCTION_42		41
#define	PRODUCTION_43		42
#define	PRODUCTION_44		43

#define	PRODUCTION_45		44

PUBLIC s32 * p_parse_production_tab;
PUBLIC s32 parse_production;

struct s_stack
{
	s32	count;
	s32	stack[SIZE_OF_TEMP_DATA];
	struct s_stack	*head;
	struct s_stack	*tail;
};

struct s_queue
{
	s32	count;
	s32	queue[SIZE_OF_TEMP_DATA];
	s32	*head;
	s32	*tail;
};

PUBLIC struct s_stack * p_stack;
PUBLIC struct s_queue * p_queue;

//-------------------------------------------------------------------------
// for dword/word/byte
//-------------------------------------------------------------------------

PUBLIC	s32	postfix_var_len;

s8 flg_abop_g;

s8 flg_cmpcond_g;

s8 flg_extern_g;

s8 flg_global_g;
#endif
