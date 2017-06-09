//===========================================================================
// graph_lib_t.c
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
#include	"dcc_graph.h"
#include	"dcc_prototype.h"

#define	GRAPH_DEBUG

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_graph_main()
{	
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("-- pr_graph_main -- (gcur_file=0x%x)\n",gcurfile);
#endif
//--------------------------

	printf("==================================================================\n");
	printf("	GRAPH print\n");
	printf("==================================================================\n");


	pr_graph_file_process(gcurfile);
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_graph_file_process(struct graph_file *f)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("-- pr_graph_file_process -- \n");
#endif
//--------------------------

	for(; f; f=f->tail)
	{
		if(f->glist)
		{
			pr_graph_stslist_process(f->glist);
		}
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_graph_stslist_process(struct graph_list *glist)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("-- pr_graph_stslist_process -- \n");
#endif
//--------------------------

	printf("\n--------------------------------------------------------------------------------\n");
	printf("	graph list(block):\n");
	printf("--------------------------------------------------------------------------------\n");

	s32 i;
	for(i=0; glist; glist=glist->tail, i++)
	{
		if(glist->g)
		{
			printf("%d)\n",i);
			pr_graph_sts_process(glist->g);
		}		
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_graph_sts_process(struct graph *g)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("%5s %10s \n","","-- pr_graph_sts_process --");
#endif
//--------------------------

	printf("\n--------------------------------------------------------------------------------\n");
	printf("	graph:\n");
	printf("--------------------------------------------------------------------------------\n");

	if(g)
	{
		//--------------------------------------------------------------------------------
		//1) print vertexs
		//--------------------------------------------------------------------------------
		struct vertex_list *vlist	= g->vlist->tail;
		for(; vlist; vlist=vlist->tail)
		{
			if(vlist->v)
			{
				pr_graph_vertex_process(vlist->v);
			}		
		}
		
		//--------------------------------------------------------------------------------
		//2) print edges
		//--------------------------------------------------------------------------------
		struct edge_list *elist	= g->elist;
		for(; elist; elist=elist->tail)
		{
			if(elist->e)
			{
				pr_graph_edge_process(elist->e);
			}
		}
	}
}

//===========================================================================
// pasm_exp_process
//===========================================================================
PUBLIC	void	pr_graph_vertex_process(struct vertex *v)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("%20s %10s \n\n","","-- pr_graph_vertex_process --");
#endif
//--------------------------

	if(v)
	{
		printf("v_id=%d\n", v->v_id);
	}
}

//===========================================================================
// pasm_exp_process
//===========================================================================
PUBLIC	void	pr_graph_edge_process(struct edge *e)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("%20s %10s \n\n","","-- pr_graph_edge_process --");
#endif
//--------------------------

	if(e)
	{
		if(e->v_s)
		{
			printf("v1_id=%d, ", e->v_s->v_id);
		}

		if(e->v_e)
		{
			printf("v2_id=%d\n", e->v_e->v_id);
		}
	}
}
