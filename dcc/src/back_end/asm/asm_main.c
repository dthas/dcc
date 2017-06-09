//===========================================================================
// asm_main.c
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

s8 *varlen[4][3]	= {"db", "dw", "", "dd"};
//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	asm_main()
{
	printf("==================================================================\n");
	printf("	asm main\n");
	printf("==================================================================\n");

	s8 output_file[]	= "src/temp/test.asm";

	FILE *fp	= fopen(output_file,"w");

	if(fp == NULL)
	{
		printf("error::can not open write file %s\n", output_file);
		exit(1);
	}

	pr_asm_title(fp);

	pr_asm_var(fp);

	pr_asm_main(fp);

	fclose(fp);
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_asm_title(FILE *foutput)
{
	printf("==================================================================\n");
	printf("	asm title\n");
	printf("==================================================================\n");

	fprintf(foutput, "\n[BITS	32]\n");

	struct symbol *p;
	s8 i,j;
	for(i=0; i<SYMTBL_SIZE; i++)
	{
		for(p=(*(p_symtbl+i)).tail; p!=NULL; p=p->tail)
		{
			if((p->scope_1 == SCOPE_GLOBAL) && (p->type_scs != EXTERN))
			{
				if(p->flg_func)
				{
					fprintf(foutput, "global	%s\n", p->label);
				}
				else
				{
					fprintf(foutput, "global	%s\n", p->name);
				}
			}	
		}
	}
	
	for(i=0; i<SYMTBL_SIZE; i++)
	{
		for(p=(*(p_symtbl+i)).tail; p!=NULL; p=p->tail)
		{
			if(p->type_scs == EXTERN)
			{
				fprintf(foutput, "extern	%s\n", p->name);				
			}	
		}
	}
}

//===========================================================================
// pr_asm_var(FILE *foutput)
//===========================================================================
PUBLIC	void	pr_asm_var(FILE *foutput)
{
	printf("==================================================================\n");
	printf("	asm var\n");
	printf("==================================================================\n");

	fprintf(foutput, "\n[section .data]\n");
	fprintf(foutput, ";==================================================================\n");
	fprintf(foutput, ";global\n");
	fprintf(foutput, ";==================================================================\n");

	struct symbol *p;
	s8 i,j;
	for(i=0; i<SYMTBL_SIZE; i++)
	{
		for(p=(*(p_symtbl+i)).tail; p!=NULL; p=p->tail)
		{
			if(p->scope_1 == SCOPE_GLOBAL)
			{
				if(!p->flg_func)
				{
					fprintf(foutput, "%s		resb	0x%d\n", p->name, p->len);
				}
			}	
		}
	}
	
	fprintf(foutput, "\ntemp_val	resb	0x4\n");
}
