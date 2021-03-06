//===========================================================================
// dcc_pasm.h
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

#ifndef	_DCC_PASM_H_
#define	_DCC_PASM_H_

#define	PASM_NAME_LEN		64

#define	PASM_ADDRESS_FLG	1000
//-------------------------------------------------------------------------
// type list
//-------------------------------------------------------------------------
enum pasm_exp_kind
{
	PASM_ADD, PASM_MINUS,
	PASM_MUL, PASM_DIV,
	PASM_MOD, PASM_MOV, 
	PASM_CMP, PASM_MEM,
	PASM_LOAD_MEM, PASM_SAVE_MEM ,
	PASM_JUMP,PASM_CALL,
	PASM_LABEL, PASM_PUSH,
	PASM_POP, PASM_ABOVE,
	PASM_LOW, PASM_EQUAL,
	PASM_NOT_EQUAL, PASM_ABOVE_EQUAL,
	PASM_LOW_EQUAL		
};

enum pasm_sts_kind
{
	PASM_LABEL_L, PASM_LABEL_J, PASM_EXP, PASM_JUMP_RETURN, PASM_SELECT , PASM_ITERATION_FOR, PASM_ITERATION_WHILE, PASM_ITERATION_DOWHILE
};

//-------------------------------------------------------------------------
// pasm_exp
//-------------------------------------------------------------------------
struct pasm_exp
{
	enum pasm_exp_kind k;

	struct live_list *livelist;
	
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
		struct {u32 src_reg, src_id, dst_reg, dst_id, src_len, dst_len; s8 src_name[PASM_NAME_LEN]; s8 dst_name[PASM_NAME_LEN];} mod;
		//6)
		struct {struct pasm_exp *cond; u32 label_1; u32 label_2;} jump;
		//7)
		struct {s32 id; u32 addr; u32 type_len; u32 num; s8 src_name[PASM_NAME_LEN];} mem;
		//8)
		struct {struct pasm_exp *m; s8 src_name[PASM_NAME_LEN];} load;
		//9)
		struct {struct pasm_exp *m; u32 val; s8 src_name[PASM_NAME_LEN];} save;	
		//10)
		struct {s8* label_name; struct pasm_explist *ppv; u32 ret_addr; u32 ret_len;} call;
		//11)	
		struct {u32 res_reg; u32 res_id; u32 res_type_len; u32 val; u32 val_type_len; s8 res_name[PASM_NAME_LEN]; 
			s8 val_name[PASM_NAME_LEN];} move;
		//12)
		struct {u32 op; u32 left, left_id, left_type_len, right, right_id, right_type_len; s8 src_name[PASM_NAME_LEN]; 
			s8 dst_name[PASM_NAME_LEN];} cmp;
		//13)	
		struct {s8* label_name; u32 label_id} label;
		//14)
		struct {u32 var_addr; u32 var_len; s8 name[PASM_NAME_LEN];} push;
		//15)
		struct {u32 var_addr; u32 var_len; s8 name[PASM_NAME_LEN];} pop;
		//16)
		struct {u32 src_reg, src_id, dst_reg, dst_id, src_len, dst_len; s8 src_name[PASM_NAME_LEN]; s8 dst_name[PASM_NAME_LEN];
			s8 t_label[PASM_NAME_LEN]; s8 f_label[PASM_NAME_LEN]; s8 e_label[PASM_NAME_LEN];} above;
		//17)
		struct {u32 src_reg, src_id, dst_reg, dst_id, src_len, dst_len; s8 src_name[PASM_NAME_LEN]; s8 dst_name[PASM_NAME_LEN];
			s8 t_label[PASM_NAME_LEN]; s8 f_label[PASM_NAME_LEN]; s8 e_label[PASM_NAME_LEN];} low;
		//18)
		struct {u32 src_reg, src_id, dst_reg, dst_id, src_len, dst_len; s8 src_name[PASM_NAME_LEN]; s8 dst_name[PASM_NAME_LEN];
			s8 t_label[PASM_NAME_LEN]; s8 f_label[PASM_NAME_LEN]; s8 e_label[PASM_NAME_LEN];} equal;
		//19)
		struct {u32 src_reg, src_id, dst_reg, dst_id, src_len, dst_len; s8 src_name[PASM_NAME_LEN]; s8 dst_name[PASM_NAME_LEN];
			s8 t_label[PASM_NAME_LEN]; s8 f_label[PASM_NAME_LEN]; s8 e_label[PASM_NAME_LEN];} not_equal;
		//20)
		struct {u32 src_reg, src_id, dst_reg, dst_id, src_len, dst_len; s8 src_name[PASM_NAME_LEN]; s8 dst_name[PASM_NAME_LEN];
			s8 t_label[PASM_NAME_LEN]; s8 f_label[PASM_NAME_LEN]; s8 e_label[PASM_NAME_LEN];} above_equal;
		//21)
		struct {u32 src_reg, src_id, dst_reg, dst_id, src_len, dst_len; s8 src_name[PASM_NAME_LEN]; s8 dst_name[PASM_NAME_LEN];
			s8 t_label[PASM_NAME_LEN]; s8 f_label[PASM_NAME_LEN]; s8 e_label[PASM_NAME_LEN];} low_equal;
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
		struct{struct pasm_explist *pexplist;} exp_sts;
		//2) label_sts
		struct{struct pasm_explist *pexplist;} label_sts;
		//3) select_sts
		struct{struct pasm_explist *pexplist; struct pasm_sts *then_sts; struct pasm_sts *else_sts;} select_sts;
		//4) iteration for sts
		//struct{struct pasm_explist *init_pexplist; struct pasm_explist *cond_pexplist; struct pasm_explist *next_pexplist; 
		//	struct pasm_sts *sts; s8 l_label[PASM_NAME_LEN]; } for_sts;
		struct{struct pasm_sts *init_sts; struct pasm_sts *cond_sts; struct pasm_explist *next_pexplist; 
			struct pasm_sts *sts; s8 l_label[PASM_NAME_LEN]; } for_sts;
		//5) iteration while sts
		struct{struct pasm_explist *cond_pexplist; struct pasm_sts *sts; s8 l_label[PASM_NAME_LEN]; } while_sts;
		//6) iteration dowhile sts
		struct{struct pasm_explist *cond_pexplist; struct pasm_sts *sts; s8 l_label[PASM_NAME_LEN]; } dowhile_sts;
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
