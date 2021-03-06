//===========================================================================
// pasm_libt.c
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

#include	"dnasm_global.h"
#include	"dnasm_type.h"
#include	"dnasm_symtbl.h"
#include	<stdio.h>
#include	"dnasm_main.h"
#include	"dnasm_lex_char.h"
#include	"dnasm_lex_word.h"
#include	"dnasm_parse.h"
#include	"dnasm_seman.h"
#include	"dnasm_frame.h"
#include	"dnasm_ir.h"
#include	"dnasm_pasm.h"
#include	"dnasm_prototype.h"

#define	PASM_DEBUG

PRIVATE	s8 exp_kind_info[19][IR_WORD_LEN] = {
					"PASM_STS_MOV","PASM_STS_ADD","PASM_STS_SUB","PASM_STS_MUL","PASM_STS_DIV","PASM_STS_CALL","PASM_STS_RET",
					"PASM_STS_JMP","PASM_STS_JA","PASM_STS_JB","PASM_STS_JE","PASM_STS_JAE","PASM_STS_JBE","PASM_STS_JNE",
					"PASM_STS_PUSH","PASM_STS_POP","PASM_STS_CMP", "PASM_STS_LABEL", "PASM_STS_XOR"};
//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_pasm_main()
{
	printf("==================================================================\n");
	printf("	PASM print\n");
	printf("==================================================================\n");


//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- print_pasm -- (pcur_file=0x%x)\n",pcur_file);
#endif
//--------------------------

	
	pr_pasm_file_process(pcur_file);

	printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	printf("	end of PASM printf\n");
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_pasm_file_process(struct pasm_file *f)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- pasm_file_process -- \n");
#endif
//--------------------------

	for(; f; f=f->tail)
	{
		pr_pasm_stslist_process(f->stslist);
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_pasm_stslist_process(struct pasm_stslist *stslist)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- pr_pasm_stslist_process -- \n");
#endif
//--------------------------

	
	for(; stslist; stslist=stslist->tail)
	{
		pr_pasm_sts_process(stslist->sts);		
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_pasm_sts_process(struct pasm_sts  *sts)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%5s %10s \n","","-- pr_pasm_sts_process --");
#endif
//--------------------------

	if(sts)
	{
		switch(sts->k)
		{
			case PASM_STS_MOV:
				printf("+++++ mov sts +++++++-\n");
				pr_pasm_explist_process(sts->s.mov_sts.pexplist);
				break;
			case PASM_STS_ADD:
				printf("++++- add sts ++++++++\n");
				pr_pasm_explist_process(sts->s.add_sts.pexplist);
				break;
			case PASM_STS_SUB:
				printf("++++- sub sts ++++++++\n");
				pr_pasm_explist_process(sts->s.sub_sts.pexplist);
				break;
			case PASM_STS_MUL:
				printf("++++- mul sts ++++++++\n");
				pr_pasm_explist_process(sts->s.mul_sts.pexplist);
				break;
			case PASM_STS_DIV:
				printf("++++- div sts ++++++++\n");
				pr_pasm_explist_process(sts->s.div_sts.pexplist);
				break;
			case PASM_STS_CALL:
				printf("++++- call sts ++++++++\n");
				pr_pasm_explist_process(sts->s.call_sts.pexplist);
				break;
			case PASM_STS_RET:
				printf("++++- ret sts ++++++++\n");
				pr_pasm_explist_process(sts->s.ret_sts.pexplist);
				break;
			case PASM_STS_JMP:
				printf("++++- jmp sts ++++++++\n");
				pr_pasm_explist_process(sts->s.jmp_sts.pexplist);
				break;
			case PASM_STS_JA:
				printf("++++- ja sts ++++++++\n");
				pr_pasm_explist_process(sts->s.ja_sts.pexplist);
				break;
			case PASM_STS_JB:
				printf("++++- jb sts ++++++++\n");
				pr_pasm_explist_process(sts->s.jb_sts.pexplist);
				break;
			case PASM_STS_JE:
				printf("++++- je sts ++++++++\n");
				pr_pasm_explist_process(sts->s.je_sts.pexplist);
				break;
			case PASM_STS_JAE:
				printf("++++- jae sts ++++++++\n");
				pr_pasm_explist_process(sts->s.jae_sts.pexplist);
				break;
			case PASM_STS_JBE:
				printf("++++- jbe sts ++++++++\n");
				pr_pasm_explist_process(sts->s.jbe_sts.pexplist);
				break;
			case PASM_STS_JNE:
				printf("++++- jne sts ++++++++\n");
				pr_pasm_explist_process(sts->s.jne_sts.pexplist);
				break;
			case PASM_STS_PUSH:
				printf("++++- push sts ++++++++\n");
				pr_pasm_explist_process(sts->s.push_sts.pexplist);
				break;
			case PASM_STS_POP:
				printf("++++- pop sts ++++++++\n");
				pr_pasm_explist_process(sts->s.pop_sts.pexplist);
				break;
			case PASM_STS_CMP:
				printf("++++- cmp sts ++++++++\n");
				pr_pasm_explist_process(sts->s.cmp_sts.pexplist);
				break;
			case PASM_STS_LABEL:
				printf("++++- label sts ++++++++\n");
				pr_pasm_explist_process(sts->s.label_sts.pexplist);
				break;
			case PASM_STS_XOR:
				printf("++++- xor sts ++++++++\n");
				pr_pasm_explist_process(sts->s.xor_sts.pexplist);
				break;
			case PASM_STS_INT:
				printf("++++- int sts ++++++++\n");
				pr_pasm_explist_process(sts->s.int_sts.pexplist);
				break;			
			default:
				break;
		}
	}
}


//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_pasm_explist_process(struct pasm_explist *explist)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%15s %10s\n","","-- pr_pasm_explist_process --");
#endif
//--------------------------


	for(; explist; explist=explist->tail)
	{
		pr_pasm_exp_process(explist->exp);		
	}
}


//===========================================================================
// pasm_exp_process
//===========================================================================
PUBLIC	void	pr_pasm_exp_process(struct pasm_exp *exp)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%20s %10s \n\n","","--pr_pasm_exp_process --");
#endif
//--------------------------

	if(exp)
	{
		switch(exp->k)
		{
			case PASM_EXP_ADD:
				printf("Add(left(%s):%x, left(id):%d, right(%s):%x, right(id):%d)\n",  exp->e.add.src_name, exp->e.add.src_reg, 
					exp->e.add.src_id, exp->e.add.dst_name, exp->e.add.dst_reg, exp->e.add.dst_id);			
				break;

			case PASM_EXP_SUB:
				printf("Minus(left(%s):%x, left(id):%d, right(%s):%x, right(id):%d)\n",  exp->e.minus.src_name, 
					exp->e.minus.src_reg, exp->e.minus.src_id, exp->e.minus.dst_name, exp->e.minus.dst_reg, 
					exp->e.minus.dst_id);
				break;

			case PASM_EXP_MUL:
				printf("Mul(left(%s):%x, left(id):%d, right(%s):%x, right(id):%d)\n",  exp->e.mul.src_name, exp->e.mul.src_reg, 
					exp->e.mul.src_id, exp->e.mul.dst_name, exp->e.mul.dst_reg, exp->e.mul.dst_id);	
				break;

			case PASM_EXP_DIV:
				printf("Div(left(%s):%x, left(id):%d, right(%s):%x, right(id):%d)\n",  exp->e.div.src_name, exp->e.div.src_reg, 
					exp->e.div.src_id, exp->e.div.dst_name, exp->e.div.dst_reg, exp->e.div.dst_id);
				break;

			case PASM_EXP_VAR:
				printf("var(varname:%s)\n", exp->e.var.var_name);
				break;
			
			case PASM_EXP_LABEL:
				printf("Label(label:%s, id:%d)\n",exp->e.label.label_name, exp->e.label.label_id);
				break;

			default:
				break;
		}
	}
}
