//===========================================================================
// dcc_ins.h
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

#ifndef	_DCC_INS_H_
#define	_DCC_INS_H_

#define	INS_LEN		128

#define	REG_NUM		6

#define	REG_EAX		0
#define	REG_EBX		1
#define	REG_ECX		2
#define	REG_EDX		3
#define	REG_ESI		4
#define	REG_EDI		5

enum ins_sts_kind
{
	INS_LABEL_L, INS_LABEL_J, INS_EXP, INS_JUMP_RETURN, INS_JMP, INS_SELECT
};

struct ins_exp
{
	s8 str[INS_LEN];

	struct ins_str *head;
	struct ins_str *tail;
};


struct ins_explist
{
	struct ins_exp *exp;
	
	struct ins_explist *head;
	struct ins_explist *tail;
};

//-------------------------------------------------------------------------
// ins_sts
//-------------------------------------------------------------------------
struct ins_sts
{
	enum ins_sts_kind k;

	union
	{
		//1) exp_sts
		struct{struct ins_explist *pexplist;} exp_sts;
		//2) label_sts
		struct{struct ins_explist *pexplist;} label_sts;
		//3) jump_sts
		struct{struct ins_explist *pexplist;} jump_sts;
		//4) select_sts
		struct{struct ins_explist *pexplist; struct ins_sts *then_sts; struct ins_sts *else_sts;} select_sts;
	}s;
};

struct ins_stslist
{
	struct ins_sts *sts;
	struct ins_stslist *head;
	struct ins_stslist *tail;
};

//-------------------------------------------------------------------------
// whole file
//-------------------------------------------------------------------------
struct ins_file
{
	struct ins_stslist *stslist;
	struct ins_file *head;
	struct ins_file *tail;
};

struct ins_file	*icur_file;

s32 sts_kind;

#endif
