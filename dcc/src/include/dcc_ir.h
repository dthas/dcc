//===========================================================================
// dcc_ir.h
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

#ifndef	_DCC_IR_H_
#define	_DCC_IR_H_

#define	IR_NAME_LEN		64
#define	IR_OP_NULL		1000

#define	IR_OP_LEN		10

#define	IR_ABOP_NUM		15
#define	IR_ASSIGNOP_NUM		11
#define	IR_RELATEOP_NUM		7
#define	IR_POSTFIXOP_NUM	6

#define	IR_WORD_NUM		128		//
#define	IR_WORD_LEN		20

#define	IR_EXPKIND_BASE		10
//-------------------------------------------------------------------------
// IR operator
//-------------------------------------------------------------------------

// 1) unary operator
#define	IR_PLUS		80		// +
#define	IR_MINUS	81		// -
#define	IR_MUL		82		// *
#define	IR_DIV		83		// /
#define	IR_MOD		84		// %

#define	IR_AND		85		// &
#define	IR_NOT		86		// !
#define	IR_NEG		87		// ~
#define	IR_OR		88		// |
#define	IR_XOR		89		// ^

// 2) binary operator
#define	IR_INC		90		// ++
#define	IR_DEC		91		// --

#define	IR_AND_AND	92		// &&
#define	IR_OR_OR	93		// ||
#define	IR_EQU_EQU	94		// ==
#define	IR_LOW_EQU	95		// <=
#define	IR_ABOVE_EQU	96		// >=
#define	IR_NOT_EQU	97		// !=

#define	IR_PLUS_EQU	98		// +=
#define	IR_MINUS_EQU	99		// -=
#define	IR_MUL_EQU	100		// *=
#define	IR_DIV_EQU	101		// /=
#define	IR_MOD_EQU	102		// %=

// 3) shift operator
#define	IR_SHIFT_LEFT	103		// <<
#define	IR_SHIFT_RIGHT	104		// >>
#define	IR_SHIFT_LEFT_EQU	105	// <<=
#define	IR_SHIFT_RIGHT_EQU	106	// >>=

// 4) other operator
#define	IR_AND_EQU	107		// &=
#define	IR_OR_EQU	108		// |=
#define	IR_XOR_EQU	109		// ^=
#define	IR_EQU		110		// =
#define	IR_Q_COND	111		// ?
#define	IR_LOW		112		// <
#define	IR_ABOVE	113		// >
#define	IR_COMMA	114		// ,
#define	IR_DOT		115		// .
#define	IR_POINTER	116		// ->
#define	IR_COLON	117		// :
#define	IR_PARAMLIST	118

#define	IR_L_PARENTHESE	120		// (
#define	IR_R_PARENTHESE	121		// )
#define	IR_L_BRACKET	122		// [
#define	IR_R_BRACKET	123		// ]
#define	IR_L_BRACE	124		// {
#define	IR_R_BRACE	125		// }

#define	IR_STRUCT	126		// .
#define	IR_ARRAY	127		// .
//-------------------------------------------------------------------------
// type list
//-------------------------------------------------------------------------
enum sts_kind
{
	IR_LABELS, IR_EXP, IR_JUMP_RETURN, IR_SELECT, IR_ITERATION_FOR, IR_ITERATION_WHILE, IR_ITERATION_DOWHILE
};


enum exp_kind
{
	IR_ABOP=IR_EXPKIND_BASE, IR_CALL, IR_VARADDR, IR_ASSIGN, IR_COND, IR_RELATE, IR_POSTFIX, IR_UNARY, IR_LABEL, IR_NULL
};


//-------------------------------------------------------------------------
// pvlist
//-------------------------------------------------------------------------

struct ir_pvlist
{
	struct ir_exp *exp;

	struct ir_pvlist *head;
	struct ir_pvlist *tail;
};

//-------------------------------------------------------------------------
// expression
//-------------------------------------------------------------------------
struct ir_explist
{
	struct ir_exp *exp;
	
	struct ir_explist *head;
	struct ir_explist *tail;
};

struct ir_exp
{
	enum exp_kind k;
	
	union
	{
		//1)
		struct{s32 op; struct ir_exp *left, *right;}abop;
		//2)
		struct{s8 * label_name; u32 align_1; u32 align_2; struct ir_explist *ppv; s32 ret_type; u32 ret_len; u32 ret_addr;} call;	
		//3)
		struct{s32 var_type; u32 align_1; u32 align_2; u32 var_len; u32 var_addr; s8 name[IR_NAME_LEN]; s8 label[IR_NAME_LEN]; s32 var_id; struct s_var *pvar; } var;
		//4)
		struct{s32 op; struct ir_exp *res, *val;} assign;
		//5)
		struct{struct ir_exp *cond, *op_1, *op_2;} cond;
		//6)		
		struct{s32 op; struct ir_exp *left, *right; }relate;
		//7)
		struct{s32 op; struct ir_exp *left, *right;}postfix;
		//8)
		struct{s32 op; struct ir_exp *left, *right;}unary;
		//9)
		struct{s8 *label_name; u32 label_id; u32 align_1;}label;
		//10)
		struct{u32 align_1; u32 align_2; u32 align_3;}null;
	}e;
};

//-------------------------------------------------------------------------
// sentence
//-------------------------------------------------------------------------
struct ir_sts
{
	enum sts_kind k;

	union
	{
		//1) exp_sts
		struct{struct ir_explist *explist} exp_sts;
		//2) jump_sts		
		struct{struct ir_explist *explist} label_sts;
		//3)
		struct{struct ir_explist *explist} jump_sts;
		//4)select_sts
		struct{struct ir_explist *explist; struct ir_sts *then_sts; struct ir_sts *else_sts;} select_sts;
		//4)iteration for sts		
		struct{struct ir_sts *init_sts; struct ir_sts *cond_sts; struct ir_explist *next_explist; struct ir_sts *sts;}for_sts;
		//5)iteration while sts
		struct{struct ir_explist *cond_explist; struct ir_sts *sts;}while_sts;
		//5)iteration do while sts
		struct{struct ir_explist *cond_explist; struct ir_sts *sts;}dowhile_sts;
	}s;
};

struct ir_stslist
{
	struct ir_sts *sts;
	struct ir_stslist *head;
	struct ir_stslist *tail;
};

//-------------------------------------------------------------------------
// whole file
//-------------------------------------------------------------------------
struct ir_file
{
	struct ir_stslist *stslist;
	struct ir_file *head;
	struct ir_file *tail;
};

struct ir_explist *cur_explist;
struct ir_stslist *cur_stslist;
struct ir_sts *cur_sts;
struct ir_file	*cur_file;
struct ir_explist *cur_parm_explist;
#endif
