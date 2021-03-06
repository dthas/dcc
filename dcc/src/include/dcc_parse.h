//===========================================================================
// dcc_parse.h
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

#ifndef	_DCC_PARSE_H_
#define	_DCC_PARSE_H_

//-------------------------------------------------------------------------
// setting  
//-------------------------------------------------------------------------
#define	PARSE_PRODUCTIONS	129		//
#define	PARSE_WORDS		128		// reference to dcc_lex_word
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
#define	PRODUCTION_46		45
#define	PRODUCTION_47		46
#define	PRODUCTION_48		47
#define	PRODUCTION_49		48
#define	PRODUCTION_50		49
#define	PRODUCTION_51		50
#define	PRODUCTION_52		51
#define	PRODUCTION_53		52
#define	PRODUCTION_54		53
#define	PRODUCTION_55		54
#define	PRODUCTION_56		55
#define	PRODUCTION_57		56
#define	PRODUCTION_58		57
#define	PRODUCTION_59		58
#define	PRODUCTION_60		59
#define	PRODUCTION_61		60
#define	PRODUCTION_62		61
#define	PRODUCTION_63		62

#define	PRODUCTION_64		63
#define	PRODUCTION_65		64
#define	PRODUCTION_66		65
#define	PRODUCTION_67		66
#define	PRODUCTION_68		67
#define	PRODUCTION_69		68
#define	PRODUCTION_70		69
#define	PRODUCTION_71		70
#define	PRODUCTION_72		71
#define	PRODUCTION_73		72
#define	PRODUCTION_74		73
#define	PRODUCTION_75		74
#define	PRODUCTION_76		75
#define	PRODUCTION_77		76
#define	PRODUCTION_78		77
#define	PRODUCTION_79		78
#define	PRODUCTION_80		79
#define	PRODUCTION_81		80
#define	PRODUCTION_82		81
#define	PRODUCTION_83		82
#define	PRODUCTION_84		83
#define	PRODUCTION_85		84
#define	PRODUCTION_86		85
#define	PRODUCTION_87		86
#define	PRODUCTION_88		87
#define	PRODUCTION_89		88
#define	PRODUCTION_90		89
#define	PRODUCTION_91		90
#define	PRODUCTION_92		91
#define	PRODUCTION_93		92
#define	PRODUCTION_94		93
#define	PRODUCTION_95		94
#define	PRODUCTION_96		95
#define	PRODUCTION_97		96
#define	PRODUCTION_98		97
#define	PRODUCTION_99		98
#define	PRODUCTION_100		99
#define	PRODUCTION_101		100
#define	PRODUCTION_102		101
#define	PRODUCTION_103		102
#define	PRODUCTION_104		103
#define	PRODUCTION_105		104
#define	PRODUCTION_106		105
#define	PRODUCTION_107		106
#define	PRODUCTION_108		107
#define	PRODUCTION_109		108
#define	PRODUCTION_110		109
#define	PRODUCTION_111		110
#define	PRODUCTION_112		111
#define	PRODUCTION_113		112
#define	PRODUCTION_114		113
#define	PRODUCTION_115		114
#define	PRODUCTION_116		115
#define	PRODUCTION_117		116
#define	PRODUCTION_118		117
#define	PRODUCTION_119		118
#define	PRODUCTION_120		119
#define	PRODUCTION_121		120
#define	PRODUCTION_122		121
#define	PRODUCTION_123		122
#define	PRODUCTION_124		123
#define	PRODUCTION_125		124
#define	PRODUCTION_126		125
#define	PRODUCTION_127		126
#define	PRODUCTION_128		127
#define	PRODUCTION_129		128

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
// for declaration
//-------------------------------------------------------------------------

PUBLIC	s8	flg_param;
PUBLIC	s8	flg_struct_union;
PUBLIC	s8 	g_function_inside;			//just for judge a variable whether it's in a function

//-------------------------------------------------------------------------
// for exp
//-------------------------------------------------------------------------
PUBLIC	s8	flg_val_pointer;
PUBLIC	s8	flg_val_array;
PUBLIC	s8	flg_val_func;
PUBLIC	s8	flg_val_struct_union;

//-------------------------------------------------------------------------
// for select
//-------------------------------------------------------------------------
PUBLIC	s8	flg_select;

//-------------------------------------------------------------------------
// for iteration
//-------------------------------------------------------------------------
PUBLIC	s8	flg_iteration;

#endif
