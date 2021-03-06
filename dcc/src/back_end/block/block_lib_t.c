//===========================================================================
// pr_block_libt.c
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

#include	"dcc_global.h"
#include	"dcc_type.h"
#include	"dcc_symtbl.h"
#include	<stdio.h>
#include	"dcc_main.h"
#include	"dcc_lex_char.h"
#include	"dcc_lex_word.h"
#include	"dcc_parse.h"
#include	"dcc_seman.h"
#include	"dcc_frame.h"
#include	"dcc_ir.h"
#include	"dcc_pasm.h"
#include	"dcc_block.h"
#include	"dcc_prototype.h"

#define	BLOCK_DEBUG

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_block_main()
{
	printf("==================================================================\n");
	printf("	BLOCK print\n");
	printf("==================================================================\n");

	pr_block_file_process(pcur_file);
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_block_file_process(struct pasm_file *f)
{
//--------------------------
//test
#ifdef	BLOCK_DEBUG
	printf("-- pr_block_file_process -- \n");
#endif
//--------------------------

	for(; f; f=f->tail)
	{
		pr_block_stslist_process(f->stslist);
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_block_stslist_process(struct pasm_stslist *stslist)
{
//--------------------------
//test
#ifdef	BLOCK_DEBUG
	printf("-- pr_block_stslist_process -- \n");
#endif
//--------------------------
	
	for(; stslist; stslist=stslist->tail)
	{
		pr_block_sts_process(stslist->sts);		
	}

	
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_block_sts_process(struct pasm_sts  *sts)
{
//--------------------------
//test
#ifdef	BLOCK_DEBUG
	printf("%5s %10s \n","","-- pr_block_sts_process --");
#endif
//--------------------------

	if(sts)
	{
		switch(sts->k)
		{
			case PASM_LABEL_L:
				pr_block_labellist_process(sts->s.exp_sts.pexplist);
				break;
			case PASM_EXP:
				pr_block_explist_process(sts->s.exp_sts.pexplist);
				break;
		}
	}
}

//===========================================================================
// pr_block_labellist_process
//===========================================================================
PUBLIC	void	pr_block_labellist_process(struct pasm_explist *explist)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%15s %10s\n","","-- pr_block_labellist_process --");
#endif
//--------------------------

	printf("\n=====================================================================================\n");
	printf("	New block:\n");
	printf("=====================================================================================\n");

	for(; explist; explist=explist->tail)
	{
		pr_block_exp_process(explist->exp);		
	}
}
//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_block_explist_process(struct pasm_explist *explist)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%15s %10s\n","","-- pr_block_explist_process --");
#endif
//--------------------------


	for(; explist; explist=explist->tail)
	{
		pr_block_exp_process(explist->exp);		
	}
}


//===========================================================================
// pasm_exp_process
//===========================================================================
PUBLIC	void	pr_block_exp_process(struct pasm_exp *exp)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%20s %10s \n\n","","--pr_block_exp_process --");
#endif
//--------------------------

	if(exp)
	{
		switch(exp->k)
		{
			case PASM_ADD:
				printf("Add(left(%s):%x, left(id):%d, right(%s):%x, right(id):%d)\n",  exp->e.add.src_name, exp->e.add.src_reg, 
					exp->e.add.src_id, exp->e.add.dst_name, exp->e.add.dst_reg, exp->e.add.dst_id);			
				break;

			case PASM_MINUS:
				printf("Minus(left(%s):%x, left(id):%d, right(%s):%x, right(id):%d)\n",  exp->e.minus.src_name, 
					exp->e.minus.src_reg, exp->e.minus.src_id, exp->e.minus.dst_name, exp->e.minus.dst_reg, 
					exp->e.minus.dst_id);
				break;

			case PASM_MUL:
				printf("Mul(left(%s):%x, left(id):%d, right(%s):%x, right(id):%d)\n",  exp->e.mul.src_name, exp->e.mul.src_reg, 
					exp->e.mul.src_id, exp->e.mul.dst_name, exp->e.mul.dst_reg, exp->e.mul.dst_id);
				break;

			case PASM_DIV:
				printf("Div(left(%s):%x, left(id):%d, right(%s):%x, right(id):%d)\n",  exp->e.div.src_name, exp->e.div.src_reg, 
					exp->e.div.src_id, exp->e.div.dst_name, exp->e.div.dst_reg, exp->e.div.dst_id);
				break;

			case PASM_MOD:
				printf("Mod(left(%s):%x, left(id):%d, right(%s):%x, right(id):%d)\n",  exp->e.mod.src_name, exp->e.mod.src_reg, 
					exp->e.mod.src_id, exp->e.mod.dst_name, exp->e.mod.dst_reg, exp->e.mod.dst_id);		
				break;

			case PASM_MEM:
				printf("Mem(addr:%x, type_len:%d, num:%d)\n",exp->e.mem.addr, exp->e.mem.type_len, exp->e.mem.num);
				break;

			case PASM_CMP:
				printf("Cmp(left:%x, left(id):%d, right:%x, right(id):%d, op:%d)\n", exp->e.cmp.left, exp->e.cmp.left_type_len, 
					exp->e.cmp.right, exp->e.cmp.right_type_len, exp->e.cmp.op);
				break;

			case PASM_LOAD_MEM:
				printf("Load(addr:%x, type_len:%d, num:%d)\n",exp->e.load.m->e.mem.addr, exp->e.load.m->e.mem.type_len, 
					exp->e.load.m->e.mem.num);	
				break;
				

			case PASM_SAVE_MEM:
				printf("Save(addr:%x, type_len:%d, num:%d, val:%x)\n",exp->e.save.m->e.mem.addr, exp->e.save.m->e.mem.type_len, 
					exp->e.save.m->e.mem.num, exp->e.save.val);
				break;

			case PASM_JUMP:
				printf("Jump(label_1:%x, label_2:%x, cond:", exp->e.jump.label_1, exp->e.jump.label_2);
				pr_block_exp_process(exp->e.jump.cond);
				break;

			case PASM_CALL:
				printf("Call(label:%s, pvlist:%x)\n",exp->e.call.label_name, exp->e.call.ppv);
				break;

			case PASM_LABEL:
				printf("Label(label:%s, id:%d)\n",exp->e.label.label_name, exp->e.label.label_id);
				break;

			case PASM_MOV:
				printf("Move(res(%s):%x, res_type_len:%d, val(%s):%x, val_type_len:%d)\n",exp->e.move.res_name, exp->e.move.res_reg, 
					exp->e.move.res_type_len, exp->e.move.val_name,exp->e.move.val, exp->e.move.val_type_len);
				break;

			default:
				break;
		}
	}
}
