//===========================================================================
// alloc_lib.c
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

//===========================================================================
// regs_reset
//===========================================================================
PUBLIC	s8 	regs_reset()
{
//--------------------------
//test
#ifdef	ALLOC_DEBUG
	printf("-- regs_reset -- \n");
#endif
//--------------------------

	s32 i;
	for(i=0; i<REG_NUM; i++)
	{
		(g_reg + i)->var_id	= NULL;
		(g_reg + i)->reg_id	= NULL;
		(g_reg + i)->status	= REG_FREE;
	}
}

//===========================================================================
// reg_reset
//===========================================================================
PUBLIC	s8 	reg_reset(s32 reg_index)
{
//--------------------------
//test
#ifdef	ALLOC_DEBUG
	printf("-- reg_reset -- \n");
#endif
//--------------------------

	(g_reg + reg_index)->var_id	= NULL;
	(g_reg + reg_index)->reg_id	= NULL;
	(g_reg + reg_index)->status	= REG_FREE;
}

//===========================================================================
// reg_reset
//===========================================================================
PUBLIC	s8 	reg_lock(s32 reg_index, s32 var_id)
{
//--------------------------
//test
#ifdef	ALLOC_DEBUG
	printf("-- reg_lock -- \n");
#endif
//--------------------------

	(g_reg + reg_index)->var_id	= var_id;
	(g_reg + reg_index)->reg_id	= reg_index;
	(g_reg + reg_index)->status	= REG_LOCK;
}

//===========================================================================
// reg_reset
//===========================================================================
PUBLIC	s32	reg_select(s32 var_id)
{
//--------------------------
//test
#ifdef	ALLOC_DEBUG
	printf("-- reg_select -- \n");
#endif
//--------------------------

	s32 i;
	for(i=0; i<REG_NUM; i++)
	{
		if((g_reg + i)->var_id == var_id)
		{
			return i;
		}
	}

	for(i=0; i<REG_NUM; i++)
	{
		if((g_reg + i)->status == REG_LOCK)
		{
			continue;
		}
		else
		{
			break;
		}
	}

	(g_reg + i)->status = REG_LOCK;

	return i;
}

//===========================================================================
// reg_status_check()
//===========================================================================
PUBLIC	s32	reg_status_check()
{
//--------------------------
//test
#ifdef	ALLOC_DEBUG
	printf("-- reg_status_check -- \n");
#endif
//--------------------------

	s32 i;
	for(i=0; i<REG_NUM; i++)
	{
		if((g_reg + i)->status == REG_LOCK)
		{
			continue;
		}
		else
		{
			break;
		}
	}

	if(i >= REG_NUM)
	{
		return REG_LOCKALL;
	}
	else
	{
		return REG_NORMAL;
	}
}


//===========================================================================
// reg_status_check()
//===========================================================================
PUBLIC	s32	reg_spill(struct graph *g, struct vertex_list *vl_src)
{
//--------------------------
//test
#ifdef	ALLOC_DEBUG
	printf("-- reg_spill(s) -- \n");
#endif
//--------------------------
	struct vertex_list *vl_dst;
	struct edge_list *el	= NULL;
	s8 flg;
	s32 i;
	for(i=0; i<REG_NUM; i++)
	{
		flg = TRUE;
		for(vl_dst=g->vlist->tail; vl_dst; vl_dst=vl_dst->tail)
		{
			el =	edge_search_v(g, vl_src->v, vl_dst->v);

			if((el) && (vl_src->v != vl_dst->v))
			{
				if(((g_reg + i)->var_id == el->e->v_s->v_id) || ((g_reg + i)->var_id == el->e->v_e->v_id))
				{
					flg = FALSE;
					break;
				}
			}
		}

		if(flg)
		{
			break;
		}
	}

//--------------------------
//test
#ifdef	ALLOC_DEBUG
	printf("-- reg_spill(e) -- \n");
#endif
//--------------------------


	if(i >= REG_NUM)
	{
		printf("[error]::spill failed !!! \n\n");
		exit(0);
	}
	else
	{
		(g_reg + i)->status	= REG_FREE;

		return i;
	}
}
