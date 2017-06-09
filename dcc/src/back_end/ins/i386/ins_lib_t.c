//===========================================================================
// ins_lib_t.c
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
#include	"dcc_ins.h"
#include	"dcc_prototype.h"

#define	INS_DEBUG

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_ins_main()
{
	printf("==================================================================\n");
	printf("	ins print\n");
	printf("==================================================================\n");

	pr_ins_file_process(icur_file);
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_ins_file_process(struct ins_file *f)
{
	for(; f; f=f->tail)
	{
		pr_ins_stslist_process(f->stslist);
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_ins_stslist_process(struct ins_stslist *stslist)
{
	for(; stslist; stslist=stslist->tail)
	{
		pr_ins_sts_process(stslist->sts);		
	}	
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_ins_sts_process(struct ins_sts  *sts)
{
	if(sts)
	{
		switch(sts->k)
		{
			case INS_LABEL_L:
				pr_ins_label_l_list_process(sts->s.exp_sts.pexplist);
				break;
			case INS_LABEL_J:
				pr_ins_label_j_list_process(sts->s.exp_sts.pexplist);
				break;
			case INS_EXP:
				pr_ins_explist_process(sts->s.exp_sts.pexplist);
				break;
			case INS_SELECT:
				pr_ins_explist_process(sts->s.select_sts.pexplist);
				pr_ins_sts_process(sts->s.select_sts.then_sts);
				pr_ins_sts_process(sts->s.select_sts.else_sts);
				break;
		}
	}
}


//===========================================================================
// pr_ins_labellist_process
//===========================================================================
PUBLIC	void	pr_ins_label_l_list_process(struct ins_explist *explist)
{
	printf("\n=====================================================================================\n");
	printf("	New block:\n");
	printf("=====================================================================================\n");

	for(; explist; explist=explist->tail)
	{
		pr_ins_label_process(explist->exp);		
	}
}

//===========================================================================
// pr_ins_labellist_process
//===========================================================================
PUBLIC	void	pr_ins_label_j_list_process(struct ins_explist *explist)
{
	for(; explist; explist=explist->tail)
	{
		pr_ins_label_process(explist->exp);		
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_ins_explist_process(struct ins_explist *explist)
{
	for(; explist; explist=explist->tail)
	{
		if(explist->exp)
		{		
			pr_ins_exp_process(explist->exp);			
		}			
	}
}


//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_exp_process(struct ins_exp *exp)
{
	for(; exp; exp=exp->tail)
	{
		if(exp->str)
		{
			printf("%s\n", exp->str);
		}
	}
}

//===========================================================================
// ins_label_process
//===========================================================================
PUBLIC	void	pr_ins_label_process(struct ins_exp *exp)
{
	for(; exp; exp=exp->tail)
	{
		if(exp->str)
		{
			printf("%s:\n", exp->str);
		}
	}
}
