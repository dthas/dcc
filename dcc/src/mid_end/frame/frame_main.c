//===========================================================================
// frame_main.c
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
#include	"dcc_ir.h"
#include	"dcc_label.h"
#include	"dcc_frame.h"
#include	"dcc_prototype.h"

#define	FRAME_DEBUG

struct s_framelist framelist;
//===========================================================================
// var_build
//===========================================================================
PUBLIC	void	frame_init()
{
	pframelist	= &framelist;

	cur_var		= NULL;

	var_init();
}

//===========================================================================
// framelist_search_s
//===========================================================================
PUBLIC	struct s_frame*	framelist_search_s(s8 *name)
{
//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- framelist_search_s(s)  -- \n");
#endif
//--------------------------

	struct s_framelist *p	= &framelist;

	for(; p; p=p->tail)
	{
		if(strcmp(p->frame.func_name, name) == TRUE) 
		{
			return &(p->frame);
		}		
	}

	return NULL;

//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- framelist_search_s(e)  -- \n");
#endif
//--------------------------
}


//===========================================================================
// fun_build
//===========================================================================
PUBLIC	s8	fun_build(struct symbol *sym)
{
//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- fun_build(s)  -- \n");
#endif
//--------------------------

	//------------------------------------------------------------------
	// create label
	//------------------------------------------------------------------
	clear_buf(sym->label,SYMBOL_NAME_LEN);
	label_build(sym->label);

	//------------------------------------------------------------------
	// param list of the function
	//------------------------------------------------------------------
	frame_build(sym);	
	
	sym->i_var_offset	= -4;

//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- fun_build(e)  -- \n");
#endif
//--------------------------
}

//===========================================================================
// frame_build
//===========================================================================
PUBLIC	s8	frame_build(struct symbol *sym)
{
//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- frame_build(s)  -- \n");
#endif
//--------------------------

	//------------------------------------------------------------------
	// create frame
	//------------------------------------------------------------------
	struct s_framelist * p_framelist= malloc(sizeof(struct s_framelist));
	struct s_frame	*fr		= &(p_framelist->frame);

	strcopy(fr->func_name, sym->name);
	fr->func_name[strlen(fr->func_name)]	= NULL;

	strcopy(fr->label_name, sym->label);
	fr->label_name[strlen(fr->label_name)]	= NULL;

	fr->func_id	= sym->id;
	fr->ret_val	= 0;
	fr->pframe_addr	= 0;

	//------------------------------------------------------------------
	// param list of the function
	//------------------------------------------------------------------	
	struct parm_type_list *pt=sym->ptlist.tail;

	u32 var_len = pt->len;	

	u32 offset=offset + var_len + var_len;		//ebp + eip
	for(; pt; offset+=var_len, pt=pt->tail)
	{
		struct s_var *var	= var_build_1(pt->name, pt->type_ts, pt->type_ts, offset, var_len, pt->len, pt->len, pt->id);
		add_var2frame(var, fr);
 
		pt->m_offset		= offset;	// size of each pointer is 4 bytes
		
		var_len = pt->len;
	}	

	//------------------------------------------------------------------
	// add frame to framelist
	//------------------------------------------------------------------	
	struct s_framelist *p	= &framelist;

	for(; p->tail; p=p->tail);
	{}

	p_framelist->head	= p;
	p->tail		= p_framelist;
	p_framelist->tail	= NULL;
}

//===========================================================================
// frame_upd_funcid()
//===========================================================================
PUBLIC	s8	frame_upd_funcid(s8 *name, s32 sym_id)
{
	struct s_framelist *p	= &framelist;

	for(; p; p=p->tail)
	{
		if(strcmp(p->frame.func_name, name) == TRUE) 
		{
			p->frame.func_id = sym_id;
			break;
		}		
	}	
}

//===========================================================================
// add_var2frame
//===========================================================================
PUBLIC	s8	printframelist()
{
	struct s_framelist *p = &framelist;

	for(p=p->tail; p; p=p->tail)
	{
		printf("\n==================================================\n");
		printf("%10s| %10s| %10s| %10s| \n", "pframe_addr","func_id","func_name","ret_val");
		printf("----------------------------------------------------\n");
		printf("%10d| %10d| %10s| %10d| \n", p->frame.pframe_addr, p->frame.func_id, p->frame.func_name, p->frame.ret_val);		

		printvarlist_in_frame(p);

		printf("==================================================\n");		
			
	}
}

//===========================================================================
// printvarlist()
//===========================================================================
PUBLIC	s8	printvarlist_in_frame(struct s_frame *fr)
{
	struct s_varlist *p = &(fr->varlist);

	printf("\n	***************************************************************************************************\n");
	printf("	%10s |%10s| %10s| %10s| %10s| %10s| %10s| %10s|\n", "var_id","var_name","offset","type","true_type", "len","len_1","total_len");
	printf("	--------------------------------------------------------------------------------------------------\n");

	for(p=p->tail; p; p=p->tail)
	{
		printf("	%10d| %10s| %10d| %10s| %10s| %10d| %10d|%10d|\n", p->var.var_id, p->var.var_name, p->var.offset, check_type_s_1(p->var.type_id), check_type_s(p->var.true_type_id), p->var.len, p->var.len_1, p->var.total_len);		
	}

	printf("	**************************************************************************************************\n");	
}
