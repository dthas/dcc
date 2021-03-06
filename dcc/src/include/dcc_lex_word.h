//===========================================================================
// dcc_lex_word.h
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

#ifndef	_DCC_LEX_WORD_H_
#define	_DCC_LEX_WORD_H_

PUBLIC 	s32	token;
PUBLIC 	s32	old_token;

struct s_token_list
{
	s32	id;
	s32	token;
	s32	val_i;
	s8	val_s[IDEN_LEN];

	struct s_token_list	*prev;
	struct s_token_list	*next;
};

struct s_token_list *p_cur_token;
struct s_token_list *p_pre_token;
struct s_token_list *p_tmp_token;

PUBLIC 	s8*	p_word;
//-------------------------------------------------------------------------
// setting  
//-------------------------------------------------------------------------
#define	PRESERVE_NUM	32		//
#define	WORD_NUM	128		//

#define	STATE_TRUE	5000		//

#define	PARSE_END	127		//
//-------------------------------------------------------------------------
// key word
//-------------------------------------------------------------------------
#define	AUTO		0
#define	BREAK		1
#define	CASE		2
#define	CHAR		3
#define	CONST		4
#define	CONTINUE	5
#define	DEFAULT		6
#define	DO		7
#define	DOUBLE		8
#define	ELSE		9
#define	ENUM		10
#define	EXTERN		11
#define	FLOAT		12
#define	FOR		13
#define	GOTO		14
#define	IF		15
#define	INT		16
#define	LONG		17
#define	REGISTER	18
#define	RETURN		19
#define	SHORT		20
#define	SIGNED		21
#define	SIZEOF		22
#define	STATIC		23
#define	STRUCT		24
#define	SWITCH		25
#define	TYPEDEF		26
#define	UNION		27
#define	UNSIGNED	28
#define	VOID		29
#define	VOLATILE	30
#define	WHILE		31

//-------------------------------------------------------------------------
// other word
//-------------------------------------------------------------------------
#define	IDENTIFIER	32

#define	SPACE		33		//
#define	COMMENT_S	34		// //
#define	COMMENT_M_BEGIN	35		// /*
#define	COMMENT_M_END	36		// */
#define	SEMICOLON	37		// ;
#define	CONST_DEC	38		// decimal constant
#define	TYPE_NAME	39		// 
#define	ELLIPSIS	40		// ...

//-------------------------------------------------------------------------
// const
//-------------------------------------------------------------------------

// 1) const int
#define	CONST_S_INT_8	42
#define	CONST_S_INT_16	43
#define	CONST_S_INT_32	44
#define	CONST_S_INT_64	45
#define	CONST_S_INT_128	46
#define	CONST_U_INT_8	47
#define	CONST_U_INT_16	48
#define	CONST_U_INT_32	49
#define	CONST_U_INT_64	50
#define	CONST_U_INT_128	51

// 2) const char
#define	CONST_NL	55
#define	CONST_HT	56
#define	CONST_VT	57
#define	CONST_BS	58
#define	CONST_CR	59
#define	CONST_FF	60
#define	CONST_BEL	61
#define	CONST_BACKSLASH	62
#define	CONST_QMARK	63
#define	CONST_S_QUOTE	64
#define	CONST_D_QUOTE	65
#define	CONST_OCT	66
#define	CONST_HEX	67

// 3) string const
#define	CONST_STRING	69

// 4) const float

#define	CONST_FLOAT	70
#define	CONST_DOUBLE	71
#define	CONST_S_SCIENCE	72
#define	CONST_U_SCIENCE	73

//-------------------------------------------------------------------------
// operator
//-------------------------------------------------------------------------

// 1) unary operator
#define	OP_PLUS		80		// +
#define	OP_MINUS	81		// -
#define	OP_MUL		82		// *
#define	OP_DIV		83		// /
#define	OP_MOD		84		// %

#define	OP_AND		85		// &
#define	OP_NOT		86		// !
#define	OP_NEG		87		// ~
#define	OP_OR		88		// |
#define	OP_XOR		89		// ^

// 2) binary operator
#define	OP_PLUS_PLUS	90		// ++
#define	OP_MINUS_MINUS	91		// --

#define	OP_AND_AND	92		// &&
#define	OP_OR_OR	93		// ||
#define	OP_EQU_EQU	94		// ==
#define	OP_LOW_EQU	95		// <=
#define	OP_ABOVE_EQU	96		// >=
#define	OP_NOT_EQU	97		// !=

#define	OP_PLUS_EQU	98		// +=
#define	OP_MINUS_EQU	99		// -=
#define	OP_MUL_EQU	100		// *=
#define	OP_DIV_EQU	101		// /=
#define	OP_MOD_EQU	102		// %=

// 3) shift operator
#define	OP_SHIFT_LEFT	103		// <<
#define	OP_SHIFT_RIGHT	104		// >>
#define	OP_SHIFT_LEFT_EQU	105	// <<=
#define	OP_SHIFT_RIGHT_EQU	106	// >>=

// 4) other operator
#define	OP_AND_EQU	107		// &=
#define	OP_OR_EQU	108		// |=
#define	OP_XOR_EQU	109		// ^=
#define	OP_EQU		110		// =
#define	OP_Q_COND	111		// ?
#define	OP_LOW		112		// <
#define	OP_ABOVE	113		// >
#define	OP_COMMA	114		// ,
#define	OP_DOT		115		// .
#define	OP_POINTOR	116		// ->
#define	OP_COLON	117		// :

//-------------------------------------------------------------------------
// delimiter
//-------------------------------------------------------------------------
#define	OP_L_PARENTHESE	120		// (
#define	OP_R_PARENTHESE	121		// )
#define	OP_L_BRACKET	122		// [
#define	OP_R_BRACKET	123		// ]
#define	OP_L_BRACE	124		// {
#define	OP_R_BRACE	125		// }

#endif
