//===========================================================================
// alloc_main.c
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
#include	"dcc_live.h"
#include	"dcc_graph.h"
#include	"dcc_alloc.h"
#include	"dcc_prototype.h"

#define	ALLOC_DEBUG

PRIVATE struct s_reg reg[REG_NUM]	= {{0, REG_EAX, REG_FREE}, {0, REG_EBX, REG_FREE}, {0, REG_ECX, REG_FREE}, {0, REG_EDX, REG_FREE},
						{0, REG_ESI, REG_FREE}, {0, REG_EDI, REG_FREE}};
//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	alloc_main()
{	
//--------------------------
//test
#ifdef	ALLOC_DEBUG
	printf("-- alloc_main -- (gcur_file=0x%x)\n",gcurfile);
#endif
//--------------------------

	g_reg	= reg;

	regs_reset();

	alloc_file_process(gcurfile);
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	alloc_file_process(struct graph_file *f)
{
//--------------------------
//test
#ifdef	ALLOC_DEBUG
	printf("-- alloc_file_process -- \n");
#endif
//--------------------------

	for(; f; f=f->tail)
	{
		if(f->glist)
		{
			alloc_stslist_process(f->glist);
		}
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	alloc_stslist_process(struct graph_list *glist)
{
//--------------------------
//test
#ifdef	ALLOC_DEBUG
	printf("-- alloc_stslist_process -- \n");
#endif
//--------------------------

	s32 i;
	for(i=0; glist; glist=glist->tail, i++)
	{
		if(glist->g)
		{
			printf("%d)\n",i);
			alloc_sts_process(glist->g);
		}		
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	alloc_sts_process(struct graph *g)
{
//--------------------------
//test
#ifdef	ALLOC_DEBUG
	printf("%5s %10s \n","","-- alloc_sts_process --");
#endif
//--------------------------

	if(g)
	{
		//--------------------------------------------------------------------------------
		//1) alloc regs for each var
		//--------------------------------------------------------------------------------
		struct vertex_list *vl_1;
		s32 reg_id;
		for(vl_1=g->vlist; vl_1; vl_1=vl_1->tail)
		{
			s32 status = reg_status_check();			

			if(status == REG_LOCKALL)
			{
				if(vl_1->v)
				{
					vl_1->v->r_id	= reg_spill(g, vl_1);
					reg[vl_1->v->r_id].var_id = vl_1->v->v_id;
				}				
			}
			else
			{
				if(vl_1->v)
				{
					vl_1->v->r_id	= reg_select(vl_1->v->v_id);
					reg[vl_1->v->r_id].var_id = vl_1->v->v_id;
				}
			}	
		}		
	}
}
