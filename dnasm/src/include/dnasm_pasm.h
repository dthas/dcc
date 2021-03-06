//===========================================================================
// dnasm_pasm.h
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

#ifndef	_DNASM_PASM_H_
#define	_DNASM_PASM_H_

#define	PASM_NAME_LEN		64

#define	PASM_ADDRESS_FLG	1000
//-------------------------------------------------------------------------
// type list
//-------------------------------------------------------------------------
enum pasm_exp_kind
{
	PASM_EXP_MOV, PASM_EXP_ADD, PASM_EXP_SUB, PASM_EXP_MUL, PASM_EXP_DIV, PASM_EXP_VAR, PASM_EXP_LABEL
};

enum pasm_sts_kind
{
	PASM_STS_MOV, PASM_STS_ADD, PASM_STS_SUB, PASM_STS_MUL, PASM_STS_DIV, PASM_STS_CALL, PASM_STS_RET, PASM_STS_JMP, PASM_STS_JA, 
	PASM_STS_JB,  PASM_STS_JE,	PASM_STS_JAE, PASM_STS_JBE, PASM_STS_JNE, PASM_STS_PUSH, PASM_STS_POP, PASM_STS_CMP, PASM_STS_LABEL,
	PASM_STS_XOR, PASM_STS_INT
};

enum pasm_store_class
{
	PASM_MEM, PASM_REG, PASM_IMM
};

//-------------------------------------------------------------------------
// pasm_exp
//-------------------------------------------------------------------------
struct pasm_exp
{
	enum pasm_exp_kind k;

	enum pasm_store_class s;

	union
	{
		//1)
		struct {u32 src_reg, src_id, dst_reg, dst_id, src_len, dst_len; s8 src_name[PASM_NAME_LEN]; s8 dst_name[PASM_NAME_LEN];} add;
		//2)
		struct {u32 src_reg, src_id, dst_reg, dst_id, src_len, dst_len; s8 src_name[PASM_NAME_LEN]; s8 dst_name[PASM_NAME_LEN];} minus;
		//3)
		struct {u32 src_reg, src_id, dst_reg, dst_id, src_len, dst_len; s8 src_name[PASM_NAME_LEN]; s8 dst_name[PASM_NAME_LEN];} mul;
		//4)
		struct {u32 src_reg, src_id, dst_reg, dst_id, src_len, dst_len; s8 src_name[PASM_NAME_LEN]; s8 dst_name[PASM_NAME_LEN];} div;
		//5)
		struct {u8 *var_name; } var;
		//18) 
		struct {s8* label_name; u32 label_id} label;
	}e;
};


struct pasm_explist
{
	struct pasm_exp *exp;
	
	struct pasm_explist *head;
	struct pasm_explist *tail;
};

//-------------------------------------------------------------------------
// pasm_sts
//-------------------------------------------------------------------------
struct pasm_sts
{
	enum pasm_sts_kind k;

	union
	{
		//1) exp_sts
		struct{struct pasm_explist *pexplist;} mov_sts;
		//2) add_sts
		struct{struct pasm_explist *pexplist;} add_sts;
		//3) sub_sts
		struct{struct pasm_explist *pexplist;} sub_sts;
		//4) mul_sts
		struct{struct pasm_explist *pexplist;} mul_sts;
		//5) div_sts
		struct{struct pasm_explist *pexplist;} div_sts;
		//6) call_sts
		struct{struct pasm_explist *pexplist;} call_sts;
		//7) ret_sts
		struct{struct pasm_explist *pexplist;} ret_sts;
		//8) jmp_sts
		struct{struct pasm_explist *pexplist;} jmp_sts;
		//9) ja_sts
		struct{struct pasm_explist *pexplist;} ja_sts;
		//10) jb_sts
		struct{struct pasm_explist *pexplist;} jb_sts;
		//11) je_sts
		struct{struct pasm_explist *pexplist;} je_sts;
		//12) jne_sts
		struct{struct pasm_explist *pexplist;} jne_sts;
		//13) jbe_sts
		struct{struct pasm_explist *pexplist;} jbe_sts;
		//14) jae_sts
		struct{struct pasm_explist *pexplist;} jae_sts;
		//15) push_sts
		struct{struct pasm_explist *pexplist;} push_sts;
		//16) pop_sts
		struct{struct pasm_explist *pexplist;} pop_sts;
		//17) cmp_sts
		struct{struct pasm_explist *pexplist;} cmp_sts;
		//18) label sts
		struct{struct pasm_explist *pexplist;} label_sts;
		//19) xor sts
		struct{struct pasm_explist *pexplist;} xor_sts;
		//20) int sts
		struct{struct pasm_explist *pexplist;} int_sts;
	}s;
};

struct pasm_stslist
{
	struct pasm_sts *sts;
	struct pasm_stslist *head;
	struct pasm_stslist *tail;
};

//-------------------------------------------------------------------------
// whole file
//-------------------------------------------------------------------------
struct pasm_file
{
	struct pasm_stslist *stslist;
	struct pasm_file *head;
	struct pasm_file *tail;
};

struct pasm_file	*pcur_file;

#endif
