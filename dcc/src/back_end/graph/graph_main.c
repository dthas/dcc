//===========================================================================
// graph_main.c
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
PUBLIC	void	graph_main()
{	
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("-- print_graph -- (lcur_file=0x%x)\n",lcur_file);
#endif
//--------------------------

	gcurfile	= graph_file_build(NULL);
	
	graph_file_process(lcur_file, gcurfile);
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	graph_file_process(struct live_file *f, struct graph_file *gf)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("-- graph_file_process -- \n");
#endif
//--------------------------

	for(; f; f=f->tail)
	{
		if(f->liveblock)
		{
			struct graph_list *glist 	= graphlist_build(NULL);

			graph_stslist_process(f->liveblock, glist);

			struct graph_file *gfile	= graph_file_build(glist);
			graph_add2file(gfile, gf); 
		}
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	graph_stslist_process(struct live_block *liveblock, struct graph_list *glist)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("-- graph_stslist_process -- \n");
#endif
//--------------------------

	s32 i;
	for(i=0; liveblock; liveblock=liveblock->tail, i++)
	{
		if(liveblock->livelist)
		{
			struct graph *g		= graph_build(NULL, NULL);

			graph_sts_process(liveblock->livelist, g);

			struct graph_list *gl	= graphlist_build(g);
			graph_add2list(gl, glist);

			liveblock->livelist->g	= g;
		}		
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	graph_sts_process(struct live_list *llist, struct graph *g)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("%5s %10s \n","","-- graph_sts_process --");
#endif
//--------------------------

	if(llist)
	{
		//--------------------------------------------------------------------------------
		//1) get vertex list
		//--------------------------------------------------------------------------------
		struct vertex_list *vlist	= vertexlist_build(NULL);		

		for(; llist; llist=llist->tail)
		{
			if(llist->live)
			{
				graph_exp_process(llist->live, vlist);
			}		
		}		

		vertex_add2list(vlist->tail, g->vlist);		

		//--------------------------------------------------------------------------------
		//2) build edges of the graph
		//--------------------------------------------------------------------------------
		struct vertex_list *v1, *v2;
		for(v1=vlist->tail; v1; v1=v1->tail)
		{
			for(v2=vlist->tail; (v2 && (v1 != v2)); v2=v2->tail)
			{				
				struct edge_list *el =	edge_search_v(g, v1->v, v2->v);				

				if(!el)
				{
					struct edge *e 		= edge_build(v1->v, v2->v);
					struct edge_list *elist	= edgelist_build(e);
					edge_add2list(elist, g->elist);
				}				
			}			
		}
	}
}

//===========================================================================
// pasm_exp_process
//===========================================================================
PUBLIC	void	graph_exp_process(struct live *live, struct vertex_list *vlist)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("%20s %10s(live=0x%x, vlist=0x%x) \n\n","","--graph_exp_process --", live, vlist);
#endif
//--------------------------

	if(live)
	{
		struct vertex *v 	= vertex_build(live->var_id);
		struct vertex_list *vl	= vertexlist_build(v);
		vertex_add2list(vl, vlist);
	}
}
