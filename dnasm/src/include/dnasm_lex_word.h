//===========================================================================
// dnasm_lex_word.h
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

#ifndef	_DNASM_LEX_WORD_H_
#define	_DNASM_LEX_WORD_H_

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
#define	PRESERVE_NUM	52		//
#define	WORD_NUM	89		//

#define	STATE_TRUE	5000		//

//-------------------------------------------------------------------------
// key word
//-------------------------------------------------------------------------
#define	TIMES		0
#define	DW		1
#define	DD		2
#define	DQ		3
#define	DT		4
#define	DY		5
#define	RESB		6
#define	RESW		7
#define	RESQ		8
#define	RESY		9
#define	INCBIN		10
#define	EQU		11
#define	DB		12
#define	ADD		13
#define	SUB		14
#define	MUL		15
#define	DIV		16
#define	MOV		17
#define	JMP		18
#define	CALL		19
#define	RET		20
#define	JA		21
#define	JB		22
#define	JE		23
#define	JAE		24
#define	JBE		25
#define	JNE		26
#define	GLOBAL		27
#define	EXTERN		28
#define	PUSH		29
#define	POP		30
#define	EAX		31
#define	EBX		32
#define	ECX		33
#define	EDX		34
#define	EBP		35
#define	ESP		36
#define	ESI		37
#define	EDI		38
#define	CS		39
#define	EIP		40
#define	DS		41
#define	ES		42
#define	SECTION		43
#define	BYTE		44
#define	WORD		45
#define	DWORD		46
#define	CMP		47
#define	BITS		48
#define	XOR		49
#define	BX		50
#define	INT		51

//-------------------------------------------------------------------------
// other word
//-------------------------------------------------------------------------
#define	IDENTIFIER	52
#define	SPACE		53		//
#define	SEMICOLON	54		// ;
#define	CONST_DEC	55		// decimal constant
#define	ELLIPSIS	56		// ...

//-------------------------------------------------------------------------
// const
//-------------------------------------------------------------------------

// 1) const int
#define	CONST_INT_8	57
#define	CONST_INT_16	58
#define	CONST_INT_32	59
#define	CONST_INT_64	60
#define	CONST_INT_128	61

// 2) const char
#define	CONST_BACKSLASH	62
#define	CONST_QMARK	63
#define	CONST_S_QUOTE	64		// '
#define	CONST_D_QUOTE	65
#define	CONST_OCT	66
#define	CONST_HEX	67

// 3) string const
#define	CONST_STRING	68

// 4) const float

#define	CONST_FLOAT	69
#define	CONST_DOUBLE	70

#define	CONST_CR	71

#define	CONST_S_INT_8	72
//-------------------------------------------------------------------------
// operator
//-------------------------------------------------------------------------
#define	OP_XOR		77

#define	OP_COLON	78
#define	OP_COMMA	79		// ,

// 1) unary operator
#define	OP_PLUS		80		// +
#define	OP_MINUS	81		// -
#define	OP_MUL		82		// *
#define	OP_DIV		83		// /


//-------------------------------------------------------------------------
// delimiter
//-------------------------------------------------------------------------
#define	OP_L_PARENTHESE	84		// (
#define	OP_R_PARENTHESE	85		// )
#define	OP_L_BRACKET	86		// [
#define	OP_R_BRACKET	87		// ]

#define	PARSE_END	88

#endif
