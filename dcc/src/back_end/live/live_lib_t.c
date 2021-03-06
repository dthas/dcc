//===========================================================================
// live_lib_t.c
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
#include	"dcc_live.h"
#include	"dcc_prototype.h"

#define	LIVE_DEBUG

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_live_main()
{
	printf("==================================================================\n");
	printf("	LIVE print\n");
	printf("==================================================================\n");


//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("-- print_live -- (lcur_file=0x%x)\n",lcur_file);
#endif
//--------------------------

	
	pr_live_file_process(lcur_file);
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_live_file_process(struct live_file *f)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("-- live_file_process -- \n");
#endif
//--------------------------

	for(; f; f=f->tail)
	{
		if(f->liveblock)
		{
			pr_live_stslist_process(f->liveblock);
		}
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_live_stslist_process(struct live_block *liveblock)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("-- pr_live_stslist_process -- \n");
#endif
//--------------------------

	
	printf("\n=====================================================================================\n");
	printf("	live block:\n");
	printf("=====================================================================================\n");

	s32 i;
	for(i=0; liveblock; liveblock=liveblock->tail, i++)
	{
		if(liveblock->livelist)
		{
			printf("%d)\n",i);
			pr_live_sts_process(liveblock->livelist);
		}		
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_live_sts_process(struct live_list *llist)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("%5s %10s \n","","-- pr_live_sts_process --");
#endif
//--------------------------

	printf("\n--------------------------------------------------------------------------------\n");
	printf("	live list:\n");
	printf("--------------------------------------------------------------------------------\n");

	if(llist)
	{
		for(; llist; llist=llist->tail)
		{
			if(llist->live)
			{
				pr_live_exp_process(llist->live);
			}		
		}
	}
}

//===========================================================================
// pasm_exp_process
//===========================================================================
PUBLIC	void	pr_live_exp_process(struct live *live)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("%20s %10s \n\n","","--pr_live_exp_process --");
#endif
//--------------------------

	if(live)
	{
		printf("var_id=%d, reg_id=%d, name=%s\n", live->var_id, live->reg_id, live->name);
	}
}
