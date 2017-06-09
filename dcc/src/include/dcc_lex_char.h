//===========================================================================
// dcc_lex.h
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

#ifndef	_DCC_LEX_CHAR_H_
#define	_DCC_LEX_CHAR_H_

PUBLIC s32 * p_lex_char_state_tab;
PUBLIC s32 lex_char_state;

#define	IDEN_LEN	64

//-------------------------------------------------------------------------
// state table param  
//-------------------------------------------------------------------------
#define	LEX_CHAR_STATES		87	//
#define	LEX_INPUT_CHARS		128		//

//-------------------------------------------------------------------------
// define states
//-------------------------------------------------------------------------
#define	LEX_CHAR_STATE_END		-1		// end state 
#define	LEX_CHAR_STATE1			0		// start state 
#define	LEX_CHAR_STATE2			1		// 
#define	LEX_CHAR_STATE3			2		//
#define	LEX_CHAR_STATE4			3		//
#define	LEX_CHAR_STATE5			4		// 
#define	LEX_CHAR_STATE6			5		//
#define	LEX_CHAR_STATE7			6		//
#define	LEX_CHAR_STATE8			7		// 
#define	LEX_CHAR_STATE9			8		//
#define	LEX_CHAR_STATE10		9		//
#define	LEX_CHAR_STATE11		10		// 
#define	LEX_CHAR_STATE12		11		//
#define	LEX_CHAR_STATE13		12		//
#define	LEX_CHAR_STATE14		13		// 
#define	LEX_CHAR_STATE15		14		//
#define	LEX_CHAR_STATE16		15		//
#define	LEX_CHAR_STATE17		16		// 
#define	LEX_CHAR_STATE18		17		//
#define	LEX_CHAR_STATE19		18		//
#define	LEX_CHAR_STATE20		19		// 
#define	LEX_CHAR_STATE21		20		//
#define	LEX_CHAR_STATE22		21		//
#define	LEX_CHAR_STATE23		22		// 
#define	LEX_CHAR_STATE24		23		//
#define	LEX_CHAR_STATE25		24		//
#define	LEX_CHAR_STATE26		25		// 
#define	LEX_CHAR_STATE27		26		//
#define	LEX_CHAR_STATE28		27		//
#define	LEX_CHAR_STATE29		28		// 
#define	LEX_CHAR_STATE30		29		//
#define	LEX_CHAR_STATE31		30		//
#define	LEX_CHAR_STATE32		31		// 
#define	LEX_CHAR_STATE33		32		//
#define	LEX_CHAR_STATE34		33		//
#define	LEX_CHAR_STATE35		34		// 
#define	LEX_CHAR_STATE36		35		//
#define	LEX_CHAR_STATE37		36		//
#define	LEX_CHAR_STATE38		37		// 
#define	LEX_CHAR_STATE39		38		//
#define	LEX_CHAR_STATE40		39		//
#define	LEX_CHAR_STATE41		40		// 
#define	LEX_CHAR_STATE42		41		//
#define	LEX_CHAR_STATE43		42		//
#define	LEX_CHAR_STATE44		43		// 
#define	LEX_CHAR_STATE45		44		//
#define	LEX_CHAR_STATE46		45		//
#define	LEX_CHAR_STATE47		46		// 
#define	LEX_CHAR_STATE48		47		//
#define	LEX_CHAR_STATE49		48		//
#define	LEX_CHAR_STATE50		49		// 
#define	LEX_CHAR_STATE51		50		//
#define	LEX_CHAR_STATE52		51		//
#define	LEX_CHAR_STATE53		52		// 
#define	LEX_CHAR_STATE54		53		//
#define	LEX_CHAR_STATE55		54		//
#define	LEX_CHAR_STATE56		55		// 
#define	LEX_CHAR_STATE57		56		//
#define	LEX_CHAR_STATE58		57		//
#define	LEX_CHAR_STATE59		58		// 
#define	LEX_CHAR_STATE60		59		//
#define	LEX_CHAR_STATE61		60		//
#define	LEX_CHAR_STATE62		61		// 
#define	LEX_CHAR_STATE63		62		//
#define	LEX_CHAR_STATE64		63		//
#define	LEX_CHAR_STATE65		64		// 
#define	LEX_CHAR_STATE66		65		//
#define	LEX_CHAR_STATE67		66		//
#define	LEX_CHAR_STATE68		67		// 
#define	LEX_CHAR_STATE69		68		//
#define	LEX_CHAR_STATE70		69		//
#define	LEX_CHAR_STATE71		70		// 
#define	LEX_CHAR_STATE72		71		//
#define	LEX_CHAR_STATE73		72		//
#define	LEX_CHAR_STATE74		73		// 
#define	LEX_CHAR_STATE75		74		//
#define	LEX_CHAR_STATE76		75		//
#define	LEX_CHAR_STATE77		76		// 
#define	LEX_CHAR_STATE78		77		//
#define	LEX_CHAR_STATE79		78		//
#define	LEX_CHAR_STATE80		79		// 
#define	LEX_CHAR_STATE81		80		//
#define	LEX_CHAR_STATE82		81		//
#define	LEX_CHAR_STATE83		82		//
#define	LEX_CHAR_STATE84		83		//
#define	LEX_CHAR_STATE85		84		//
#define	LEX_CHAR_STATE86		85		//
#define	LEX_CHAR_STATE87		86		//

//-------------------------------------------------------------------------
// define characters(0 ~ 127)  
//-------------------------------------------------------------------------
//0~31: invisible characters
#define	CH_TAB		9		//
#define	CH_LF		10		//
#define	CH_CR		13		//

#define	CH_SPACE	32		//
#define	CH_GT		33		// !
#define	CH_DQ		34		// "
#define	CH_PROMPT	35		// #
#define	CH_DOLLAR	36		// $
#define	CH_BF		37		// %
#define	CH_AND		38		// &
#define	CH_SQ		39		// '
#define	CH_LP		40		// (
#define	CH_RP		41		// )
#define	CH_MUL		42		// *
#define	CH_ADD		43		// +
#define	CH_COMMA	44		// ,
#define	CH_MINUS	45		// -
#define	CH_DOT		46		// .
#define	CH_DIV		47		// /
#define	CH_0		48		//
#define	CH_1		49		//
#define	CH_2		50		//
#define	CH_3		51		//
#define	CH_4		52		//
#define	CH_5		53		//
#define	CH_6		54		//
#define	CH_7		55		//
#define	CH_8		56		//
#define	CH_9		57		//
#define	CH_COL		58		// :
#define	CH_SEMICOL	59		// ;
#define	CH_LOW		60		// <
#define	CH_EQU		61		// =
#define	CH_ABOVE	62		// >
#define	CH_QUEST	63		// ?
#define	CH_AT		64		// @
#define	CH_A		65		//
#define	CH_B		66		//
#define	CH_C		67		//
#define	CH_D		68		//
#define	CH_E		69		//
#define	CH_F		70		//
#define	CH_G		71		//
#define	CH_H		72		//
#define	CH_I		73		//
#define	CH_J		74		//
#define	CH_K		75		//
#define	CH_L		76		//
#define	CH_M		77		//
#define	CH_N		78		//
#define	CH_O		79		//
#define	CH_P		80		//
#define	CH_Q		81		//
#define	CH_R		82		//
#define	CH_S		83		//
#define	CH_T		84		//
#define	CH_U		85		//
#define	CH_V		86		//
#define	CH_W		87		//
#define	CH_X		88		//
#define	CH_Y		89		//
#define	CH_Z		90		//
#define	CH_LB		91		// [
#define	CH_BS		92		// BACK SLASH "\"
#define	CH_RB		93		// ]
#define	CH_AF		94		// ^
#define	CH_UL		95		// _
#define	CH_BCOMMA	96		// `
#define	CH_a		97		//
#define	CH_b		98		//
#define	CH_c		99		//
#define	CH_d		100		//
#define	CH_e		101		//
#define	CH_f		102		//
#define	CH_g		103		//
#define	CH_h		104		//
#define	CH_i		105		//
#define	CH_j		106		//
#define	CH_k		107		//
#define	CH_l		108		//
#define	CH_m		109		//
#define	CH_n		110		//
#define	CH_o		111		//
#define	CH_p		112		//
#define	CH_q		113		//
#define	CH_r		114		//
#define	CH_s		115		//
#define	CH_t		116		//
#define	CH_u		117		//
#define	CH_v		118		//
#define	CH_w		119		//
#define	CH_x		120		//
#define	CH_y		121		//
#define	CH_z		122		//
#define	CH_LBB		123		// {
#define	CH_VL		124		// |
#define	CH_RBB		125		// }
#define	CH_REV		126		// ~

//127 is DEL

#endif
