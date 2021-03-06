//===========================================================================
// block_main.c
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
PUBLIC	void	block_main()
{
	printf("==================================================================\n");
	printf("	BLOCK print\n");
	printf("==================================================================\n");


//--------------------------
//test
#ifdef	BLOCK_DEBUG
	printf("-- print_block -- (pcur_file=0x%x)\n",pcur_file);
#endif
//--------------------------

	block_file_process(pcur_file);
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	block_file_process(struct pasm_file *f)
{
//--------------------------
//test
#ifdef	BLOCK_DEBUG
	printf("-- block_file_process -- \n");
#endif
//--------------------------

	for(; f; f=f->tail)
	{
		block_stslist_process(f->stslist);
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	s8	block_stslist_process(struct pasm_stslist *stslist)
{
//--------------------------
//test
#ifdef	BLOCK_DEBUG
	printf("-- block_stslist_process -- \n");
#endif
//--------------------------
	s8 flg = FALSE;
	
	for(; stslist; stslist=stslist->tail)
	{
		struct block *src_block 	= block_build(stslist);
		
		if(block_sts_process(stslist->sts))
		{	
			cur_block	= block_build(NULL);
			add2block(src_block, cur_block);
	
			struct blocklist *src_blocklist	= blocklist_build(cur_block);
			add2blocklist(src_blocklist, cur_blocklist);									
		}	
		else
		{
			add2block(src_block, cur_block);
		}
	}	
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	s8	block_sts_process(struct pasm_sts  *sts)
{
//--------------------------
//test
#ifdef	BLOCK_DEBUG
	printf("%5s %10s \n","","-- block_sts_process --");
#endif
//--------------------------

	if(sts)
	{
		switch(sts->k)
		{
			case PASM_LABEL_L:
				return TRUE;
				break;
			case PASM_EXP:
				return FALSE;
				break;
			case PASM_SELECT:
				return FALSE;
				break;
			case PASM_ITERATION_FOR:
				return FALSE;
				break;
		}
	}
}
