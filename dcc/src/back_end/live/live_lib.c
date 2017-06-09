//===========================================================================
// live_lib.c
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
#include	"dcc_prototype.h"

#define	LIVE_DEBUG

//===========================================================================
// ref_check
//===========================================================================
PUBLIC	struct live *	live_build()
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("-- live_build -- \n");
#endif
//--------------------------

	struct live *live	= malloc(sizeof(struct live));

	if(!live)
	{
		printf("[error]::live:: allocate fail !!! \n\n");
	}

	live->var_id	= NULL;
	live->reg_id	= NULL;
	

	return live;
}

//===========================================================================
// ref_check
//===========================================================================
PUBLIC	struct livelist *	livelist_build(struct live *live)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("-- livelist_build -- \n");
#endif
//--------------------------

	struct live_list *p	= malloc(sizeof(struct live_list));

	if(!p)
	{
		printf("[error]::live:: live list allocate fail !!! \n\n");
	}

	p->live	= live;
	p->head	= NULL;
	p->tail	= NULL;

	return p;
}

//===========================================================================
// ref_check
//===========================================================================
PUBLIC	s8	live_add2list(struct live_list *src, struct live_list *dst)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("-- live_add2list, src=%x, dst=%x -- \n", src, dst);
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL; 
}


//===========================================================================
// ref_check
//===========================================================================
PUBLIC	s8	ref_check(s32 var_id, struct pasm_explist *explist)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("-- ref_check -- \n");
#endif
//--------------------------

	for(; explist; explist=explist->tail)
	{
		if(explist->exp)
		{
			if(ref_check_1(explist->exp, var_id))
			{
				return TRUE;
			}
		}		
	}

	return 	FALSE;
}

//===========================================================================
// pasm_exp_process
//===========================================================================
PUBLIC	s8	ref_check_1(struct pasm_exp *exp, s32 var_id)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("%20s %10s \n\n","","--ref_check_1(s) --");
#endif
//--------------------------

	struct pasm_explist *explist	= NULL;

	if(exp)
	{
		switch(exp->k)
		{
			case PASM_ADD:
				if((exp->e.add.src_id == var_id) || (exp->e.add.dst_id == var_id))
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
			
				break;

			case PASM_MINUS:
				if((exp->e.minus.src_id == var_id) || (exp->e.minus.dst_id == var_id))
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
				break;

			case PASM_MUL:
				if((exp->e.mul.src_id == var_id) || (exp->e.mul.dst_id == var_id))
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
				break;

			case PASM_DIV:
				if((exp->e.div.src_id == var_id) || (exp->e.div.dst_id == var_id))
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
				break;

			case PASM_MOD:
				if((exp->e.mod.src_id == var_id) || (exp->e.mod.dst_id == var_id))
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}		
				break;

			case PASM_MEM:
				if(exp->e.mem.id == var_id) 
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
				break;

			case PASM_CMP:
				if((exp->e.cmp.left_id == var_id) || (exp->e.cmp.right_id == var_id))
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
				break;

			case PASM_LOAD_MEM:
				//	
				break;
				

			case PASM_SAVE_MEM:
				//
				break;

			case PASM_JUMP:
				if((exp->e.jump.cond->e.cmp.left_id == var_id) || (exp->e.jump.cond->e.cmp.right_id == var_id))
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
				break;

			case PASM_CALL:
				explist = exp->e.call.ppv;
				for(; explist; explist=explist->tail)
				{
					if(explist->exp)
					{
						if(explist->exp->e.mem.id == var_id)
						{
							return TRUE;
						}
						else
						{
							return FALSE;
						}	
					}
				}
				break;

			case PASM_LABEL:
				//
				break;

			case PASM_MOV:
				if(exp->e.move.res_id == var_id)
				{
					return TRUE;
				}
				else
				{
					return FALSE;
				}
				break;

			default:
				break;
		}
	}
}


//===========================================================================
// file_build
//===========================================================================
PUBLIC	struct live_file *	live_file_build(struct live_block *liveblock)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("	-- live_file_build  -- \n");
#endif
//--------------------------

	struct live_file *ret_file	= malloc(sizeof(struct live_file));

	if(!ret_file)
	{
		printf("live_file() malloc failed!!\n");
		exit(1);
	}

	ret_file->liveblock	= liveblock;
	ret_file->head	= NULL;
	ret_file->tail	= NULL;

	return ret_file;
}


//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	s8	live_add2file(struct live_file *src, struct live_file * dst)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("	-- live_add2file  -- \n");
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
PUBLIC	struct live_block *	live_block_build(struct live_list *livelist)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("	-- live_block_build  -- \n");
#endif
//--------------------------

	struct live_block *ret	= malloc(sizeof(struct live_block));

	if(!ret)
	{
		printf("live_blcok() malloc failed!!\n");
		exit(1);
	}

	ret->livelist	= livelist;
	ret->head	= NULL;
	ret->tail	= NULL;

	return ret;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	s8	live_add2block(struct live_block *src, struct live_block * dst)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("	-- live_add2block  -- \n\n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}

