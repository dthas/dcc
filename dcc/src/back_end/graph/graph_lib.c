//===========================================================================
// graph_lib.c
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
#include	"dcc_live.h"
#include	"dcc_graph.h"
#include	"dcc_prototype.h"

#define	GRAPH_DEBUG

//===========================================================================
// vertex_build
//===========================================================================
PUBLIC	struct vertex *	vertex_build(s32 v_id)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("-- vertex_build -- \n");
#endif
//--------------------------

	struct vertex *v	= malloc(sizeof(struct vertex));

	if(!v)
	{
		printf("[error]::live:: allocate fail !!! \n\n");
		exit(0);
	}

	v->v_id		= v_id;
	v->r_id		= NULL;
	

	return v;
}

//===========================================================================
// ref_check
//===========================================================================
PUBLIC	struct vertex_list *	vertexlist_build(struct vertex *v)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("-- vertexlist_build -- \n");
#endif
//--------------------------

	struct vertex_list *p	= malloc(sizeof(struct vertex_list));

	if(!p)
	{
		printf("[error]::live:: live list allocate fail !!! \n\n");
	}

	p->v	= v;
	p->head	= NULL;
	p->tail	= NULL;

	return p;
}

//===========================================================================
// ref_check
//===========================================================================
PUBLIC	s8	vertex_add2list(struct vertex_list *src, struct vertex_list *dst)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("-- vertex_add2list, src=%x, dst=%x -- \n", src, dst);
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;	
}

//===========================================================================
// file_build
//===========================================================================
PUBLIC	struct edge *	edge_build(struct vertex *v1, struct vertex *v2)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("	-- edge_build  -- \n");
#endif
//--------------------------

	struct edge *e	= malloc(sizeof(struct edge));

	if(!e)
	{
		printf("live_file() malloc failed!!\n");
		exit(1);
	}

	e->v_s	= v1;
	e->v_e	= v2;
	
	return e;
}

//===========================================================================
// ref_check
//===========================================================================
PUBLIC	struct edge_list *	edgelist_build(struct edge *e)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("-- edgelist_build -- \n");
#endif
//--------------------------

	struct edge_list *p	= malloc(sizeof(struct edge_list));

	if(!p)
	{
		printf("[error]::live:: live list allocate fail !!! \n\n");
	}

	p->e	= e;
	p->head	= NULL;
	p->tail	= NULL;

	return p;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	s8	edge_add2list(struct edge_list *src, struct edge_list * dst)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("	-- edge_add2list  -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}

//===========================================================================
// file_build
//===========================================================================
PUBLIC	struct graph *	graph_build(struct vertex_list *vlist, struct edge_list *elist)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("	-- graph_build  -- \n");
#endif
//--------------------------

	struct graph *g	= malloc(sizeof(struct graph));

	if(!g)
	{
		printf("live_blcok() malloc failed!!\n");
		exit(1);
	}

	g->vlist	= vertexlist_build(NULL);
	g->elist	= edgelist_build(NULL);
	
	return g;
}

//===========================================================================
// ref_check
//===========================================================================
PUBLIC	struct graph_list *	graphlist_build(struct graph *g)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("-- graphlist_build -- \n");
#endif
//--------------------------

	struct graph_list *p	= malloc(sizeof(struct graph_list));

	if(!p)
	{
		printf("[error]::live:: live list allocate fail !!! \n\n");
	}

	p->g	= g;
	p->head	= NULL;
	p->tail	= NULL;

	return p;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	s8	graph_add2list(struct graph_list *src, struct graph_list * dst)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("	-- graph_add2list  -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}

//===========================================================================
// graph_build
//===========================================================================
PUBLIC	struct graph_file *	graph_file_build(struct graph_list *glist)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("	-- graph_file_build  -- \n");
#endif
//--------------------------

	struct graph_file *ret_file	= malloc(sizeof(struct graph_file));

	if(!ret_file)
	{
		printf("graph_file() malloc failed!!\n");
		exit(1);
	}

	ret_file->glist	= glist;
	ret_file->head	= NULL;
	ret_file->tail	= NULL;

	return ret_file;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	s8	graph_add2file(struct graph_file *src, struct graph_file * dst)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("	-- graph_add2file  -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}

//===========================================================================
// edge_search
//===========================================================================
PUBLIC	struct edge_list *	edge_search_v(struct graph *g, struct vertex *v1, struct vertex *v2)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("	-- edge_search_v(graph=0x%x, v1=0x%x, v2=0x%x)  -- \n\n", g, v1, v2);
#endif
//--------------------------

	struct edge_list *el	= g->elist->tail;

	for(; el; el=el->tail)
	{
		if((el->e) && v1 && v2)
		{
			if((v1->v_id == 0) && (v2->v_id == 0))
			{
			}
			else if(el->e->v_s && el->e->v_e)
			{
				if(((el->e->v_s->v_id == v1->v_id) && (el->e->v_e->v_id == v2->v_id)) 
					|| ((el->e->v_s->v_id == v2->v_id) && (el->e->v_e->v_id == v1->v_id)))
				{
					return el;
					break;
				}
			}
		}
	}

	return NULL;
}

//===========================================================================
// edge_search
//===========================================================================
PUBLIC	struct edge_list* edge_search_e(struct graph *g, struct edge *e)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("	-- edge_search_e  -- \n");
#endif
//--------------------------

	struct edge_list *el	= g->elist;

	s32 v1_id	= e->v_s->v_id;
	s32 v2_id	= e->v_e->v_id;

	for(; el; el=el->tail)
	{
		if(((el->e->v_s->v_id == v1_id) && (el->e->v_e->v_id == v2_id)) 
			|| ((el->e->v_s->v_id == v2_id) && (el->e->v_e->v_id == v1_id)))
		{
			return el;
			break;
		}
	}

	return NULL;
}

//===========================================================================
// edge_search_e
//===========================================================================
PUBLIC	s8	edge_delete_e(struct graph *g, struct edge *e)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("	-- edge_delete_e  -- \n");
#endif
//--------------------------
	struct edge_list * el	= edge_search_e(g, e);

	if(el)
	{
		struct edge_list *prev	= el->head;
		
		if(el->tail)
		{
			if(prev)
			{
				prev->tail	= el->tail;
				(el->tail)->head= prev;
			}
			else
			{
				g->elist->tail	= el->tail;
				(el->tail)->head= NULL;
			}
		}
		else
		{
			if(prev)
			{
				prev->tail	= NULL;
			}
			else
			{
				g->elist->tail	= NULL;
			}
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//===========================================================================
// edge_search_v
//===========================================================================
PUBLIC	s8	edge_delete_v(struct graph *g, struct vertex *v1, struct vertex *v2)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("	-- edge_delete_v  -- \n");
#endif
//--------------------------
	struct edge_list * el	= edge_search_v(g, v1, v2);

	if(el)
	{
		struct edge_list *prev	= el->head;
		
		if(el->tail)
		{
			if(prev)
			{
				prev->tail	= el->tail;
				(el->tail)->head= prev;
			}
			else
			{
				g->elist->tail	= el->tail;
				(el->tail)->head= NULL;
			}
		}
		else
		{
			if(prev)
			{
				prev->tail	= NULL;
			}
			else
			{
				g->elist->tail	= NULL;
			}
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


//===========================================================================
// file_build
//===========================================================================
PUBLIC	struct vertex_list *	vertex_search(struct graph *g, struct vertex *v)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("	-- vertex_search  -- \n");
#endif
//--------------------------

	struct vertex_list *vl	= g->vlist;

	for(; vl; vl=vl->tail)
	{
		if(vl->v->v_id == v->v_id)
		{
			return vl;
			break;
		}
	}

	return NULL;
}

//===========================================================================
// file_build
//===========================================================================
PUBLIC	s32	vertex_search_var(struct graph *g, s32 var_id)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("	-- vertex_search_var(s),g=0x%x  -- \n\n",g);
#endif
//--------------------------

	struct vertex_list *vl	= g->vlist;

	for(; vl; vl=vl->tail)
	{
		if(vl->v)
		{
			if(vl->v->v_id == var_id)
			{
				return vl->v->r_id;
				break;
			}
		}
	}

	printf("vertex_search_var::var_id=%d, not found!\n\n",var_id);
	exit(0);

	return NULL;
}

//===========================================================================
// vertex_search_v
//===========================================================================
PUBLIC	s8	vertex_delete(struct graph *g, struct vertex *v)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("	-- vertex_delete  -- \n");
#endif
//--------------------------
	struct vertex_list * vl	= vertex_search(g, v);

	if(vl)
	{
		struct vertex_list *prev	= vl->head;
		
		if(vl->tail)
		{
			if(prev)
			{
				prev->tail	= vl->tail;
				(vl->tail)->head= prev;
			}
			else
			{
				g->vlist->tail	= vl->tail;
				(vl->tail)->head= NULL;
			}
		}
		else
		{
			if(prev)
			{
				prev->tail	= NULL;
			}
			else
			{
				g->vlist->tail	= NULL;
			}
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//===========================================================================
// vertex_search_v
//===========================================================================
PUBLIC	struct graph *	vertex_search_g(struct live_list *livelist)
{
//--------------------------
//test
#ifdef	GRAPH_DEBUG
	printf("	-- vertex_search_g(s),livelist=0x%x  -- \n\n",livelist);
#endif
//--------------------------

	struct live_file *f = lcur_file;
	for(; f; f=f->tail)
	{
		if(f->liveblock)
		{
			struct live_block *liveblock = f->liveblock;
			for(; liveblock; liveblock=liveblock->tail)
			{
				if(liveblock->livelist)
				{
					struct live_list *llist	= liveblock->livelist;
					for(; llist; llist=llist->tail)
					{
						if(llist == livelist)
						{
							return llist->g;							
						}					
					}
				}		
			}
		}
	}

	return NULL;
}
