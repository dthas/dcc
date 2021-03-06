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

#define	ASM_DEBUG

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_asm_main(FILE *foutput)
{
	printf(";==================================================================\n");
	printf("	asm var\n");
	printf(";==================================================================\n");

	fprintf(foutput, "\n[section .text]\n");

	pr_asm_file_process(icur_file, foutput);
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_asm_file_process(struct ins_file *f, FILE *foutput)
{
	for(; f; f=f->tail)
	{
		pr_asm_stslist_process(f->stslist, foutput);
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_asm_stslist_process(struct ins_stslist *stslist, FILE *foutput)
{
	for(; stslist; stslist=stslist->tail)
	{
		pr_asm_sts_process(stslist->sts, foutput);		
	}	
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_asm_sts_process(struct ins_sts  *sts, FILE *foutput)
{
	if(sts)
	{
		switch(sts->k)
		{
			case INS_JMP:
				pr_asm_jmplist_process(sts->s.exp_sts.pexplist, foutput);
				break;
			case INS_LABEL_L:
				pr_asm_label_l_list_process(sts->s.exp_sts.pexplist, foutput);
				break;
			case INS_LABEL_J:
				pr_asm_label_j_list_process(sts->s.exp_sts.pexplist, foutput);
				break;
			case INS_JUMP_RETURN:
				pr_asm_jumplist_process(sts->s.exp_sts.pexplist, foutput);
				break;
			case INS_EXP:
				pr_asm_explist_process(sts->s.exp_sts.pexplist, foutput);
				break;
			case INS_SELECT:
				pr_asm_explist_process(sts->s.select_sts.pexplist, foutput);
				pr_asm_sts_process(sts->s.select_sts.then_sts, foutput);

				if(sts->s.select_sts.else_sts)
				{
					pr_asm_sts_process(sts->s.select_sts.else_sts, foutput);
				}
				break;
		}
	}
}


//===========================================================================
// pr_asm_labellist_process
//===========================================================================
PUBLIC	void	pr_asm_jmplist_process(struct ins_explist *explist, FILE *foutput)
{
	for(; explist; explist=explist->tail)
	{
		pr_asm_jmp_process(explist->exp, foutput);		
	}
}

//===========================================================================
// pr_asm_labellist_process
//===========================================================================
PUBLIC	void	pr_asm_label_l_list_process(struct ins_explist *explist, FILE *foutput)
{
	for(; explist; explist=explist->tail)
	{
		pr_asm_label_l_process(explist->exp, foutput);		
	}
}

//===========================================================================
// pr_asm_labellist_process
//===========================================================================
PUBLIC	void	pr_asm_label_j_list_process(struct ins_explist *explist, FILE *foutput)
{
	for(; explist; explist=explist->tail)
	{
		pr_asm_label_j_process(explist->exp, foutput);		
	}
}

//===========================================================================
// pr_asm_labellist_process
//===========================================================================
PUBLIC	void	pr_asm_jumplist_process(struct ins_explist *explist, FILE *foutput)
{
	for(; explist; explist=explist->tail)
	{
		pr_asm_jump_return_process(explist->exp, foutput);		
	}
}
//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_asm_explist_process(struct ins_explist *explist, FILE *foutput)
{
	for(; explist; explist=explist->tail)
	{
		if(explist->exp)
		{		
			pr_asm_exp_process(explist->exp, foutput);			
		}			
	}

	fprintf(foutput, "\n");
}


//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_asm_exp_process(struct ins_exp *exp, FILE *foutput)
{
	for(; exp; exp=exp->tail)
	{
		if(exp->str)
		{
			fprintf(foutput, "%s\n", exp->str);			
		}
	}	
}

//===========================================================================
// ins_label_process
//===========================================================================
PUBLIC	void	pr_asm_jmp_process(struct ins_exp *exp, FILE *foutput)
{

	for(; exp; exp=exp->tail)
	{
		if(exp->str)
		{
			fprintf(foutput, "%s\n", exp->str);				
		}
	}
}

//===========================================================================
// ins_label_process
//===========================================================================
PUBLIC	void	pr_asm_label_l_process(struct ins_exp *exp, FILE *foutput)
{

	for(; exp; exp=exp->tail)
	{
		if(exp->str)
		{
			fprintf(foutput, "\n;--------------------------------------------------------------\n");
			fprintf(foutput, "%s\n", exp->str);	
			fprintf(foutput, ";--------------------------------------------------------------\n");
		}
	}
}

//===========================================================================
// ins_label_process
//===========================================================================
PUBLIC	void	pr_asm_label_j_process(struct ins_exp *exp, FILE *foutput)
{

	for(; exp; exp=exp->tail)
	{
		if(exp->str)
		{
			fprintf(foutput, "%s\n", exp->str);				
		}
	}
}

//===========================================================================
// ins_label_process
//===========================================================================
PUBLIC	void	pr_asm_jump_return_process(struct ins_exp *exp, FILE *foutput)
{
	if(exp->str)
	{
		fprintf(foutput, "%s\n", exp->str);
	}	
}
