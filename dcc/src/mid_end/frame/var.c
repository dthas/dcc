//===========================================================================
// var.c
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

#define	VAR_DEBUG

struct s_varlist varlist;

//===========================================================================
// var_build
//===========================================================================
PUBLIC	void	var_init()
{
	pvarlist	= &varlist;		//for global var
}

//===========================================================================
// var_build
// each var in the frame is a pointer, which is size of 4 bytes
//===========================================================================
PUBLIC	struct s_var*	var_build(struct symbol *sym)
{
//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- var_build(s)  -- \n");
#endif
//--------------------------

	struct s_var *var;

	struct symbol *symfun;
	u32 offset;
	
	u32 len, len_1, total_len, type_id,true_type_id;
	s32 var_id;

	var_id		= sym_id;

	type_id		= sym->type_ts;
	true_type_id	= sym->type_ts;

	if(sym->type_ts == STRUCT)
	{
		true_type_id = check_type_i(sym->su.name);

		if(true_type_id)
		{
			len_1 	= check_type_l(true_type_id);
			len 	= sizeof(int*);
		}
		else
		{
			printf("[error]:var_build fault!!(true_type_id=%d,name=%s)\n",true_type_id,sym->su.name);
			exit(1);
		}
	}
	else
	{
		len_1	= check_type_l(sym->type_ts);
		len 	= sizeof(int*);
	}

	total_len	= len_1;
	
	if(sym->flg_array)
	{
		total_len	*= sym->val_i;
	}
	
	if(sym->flg_pointer)
	{
		len		= sizeof(int*);
		len_1		= sizeof(int*);
		total_len	= sizeof(int*);
	}

	//------------------------------------------------------------------
	// the whole var allocation
	//------------------------------------------------------------------
	if(sym->scope_1 == SCOPE_FUNCTION)
	{
		symfun	= symtbl_search_i(sym->scope_2);
		
		symfun->i_var_offset	-= total_len;					
				
		sym->m_addr		= symfun->m_addr;
		sym->i_var_offset	= symfun->i_var_offset;	//ebp of the function + offset

		
		var			= var_build_1(sym->name, true_type_id, type_id, symfun->i_var_offset, len, len_1, total_len, var_id);
		
		struct s_frame *fr	= framelist_search_s(symfun->name);

		if(!fr)
		{
			printf("[error]:no this frame!!, function_name=%s\n",sym->name);
			exit(1);
		}
		else
		{
			add_var2frame(var, fr);
		}		
	}
	else
	{
		void *p	= malloc(len);				//global, outside of the function		
		sym->m_addr		= p;

		sym->i_var_offset	= -4;

		var		= var_build_1(sym->name, true_type_id, type_id, sym->i_var_offset, len, len_1, total_len, var_id);
		
		add_var2varlist(var, &varlist);

	}
	return var;
}

//===========================================================================
// var_build_1
//===========================================================================
PUBLIC	struct s_var *	var_build_1(s8* name, s32 true_type_id, s32 type_id, s32 offset, s32 len, s32 len_1, s32 total_len, s32 var_id)
{
//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- var_build_1(s)  -- \n");
#endif
//--------------------------
	struct s_var *var	= malloc(sizeof(struct s_var));

	strcopy(var->var_name, name);
	var->var_name[strlen(var->var_name)]	= NULL;
	
	var->var_id	= var_id;

	var->true_type_id = true_type_id;
	var->type_id	= type_id;
	var->offset	= offset;
	var->len	= len;
	var->len_1	= len_1;
	var->total_len	= total_len;
	
	var->var_addr	= malloc(sizeof(total_len));

	*(s32*)(var->var_addr)	= NULL;		// the content of the variable is NULL	

	return var;
}


//===========================================================================
// add_var2frame
//===========================================================================
PUBLIC	s8	add_var2frame(struct s_var *var, struct s_frame *fr)
{
//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- add_var2frame(s)  -- \n");
#endif
//--------------------------

	//------------------------------------------------------------------
	// create varlist(src)
	//------------------------------------------------------------------
	struct s_varlist *vlist	= malloc(sizeof(struct s_varlist));

	strcopy(vlist->var.var_name, var->var_name);
	vlist->var.var_name[strlen(vlist->var.var_name)]	= NULL;

	vlist->var.true_type_id	= var->true_type_id;
	vlist->var.type_id	= var->type_id;
	vlist->var.offset	= var->offset;
	vlist->var.len		= var->len;
	vlist->var.len_1	= var->len_1;
	vlist->var.total_len	= var->total_len;
	vlist->var.var_addr	= var->var_addr;	
	vlist->var.var_id	= var->var_id;

	//------------------------------------------------------------------
	// dest
	//------------------------------------------------------------------
	struct s_varlist *p = &(fr->varlist);

	//------------------------------------------------------------------
	// add src to dest
	//------------------------------------------------------------------
	for(; p->tail; p=p->tail)
	{}

	vlist->head	= p;
	p->tail		= vlist;
	vlist->tail	= NULL;
}

//===========================================================================
// add_var2varlist
//===========================================================================
PUBLIC	s8	add_var2varlist(struct s_var *var, struct s_varlist *p)
{
//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- add_var2varlist(s)  -- \n");
#endif
//--------------------------

	//------------------------------------------------------------------
	// create varlist(src)
	//------------------------------------------------------------------
	struct s_varlist *vlist	= malloc(sizeof(struct s_varlist));

	strcopy(vlist->var.var_name, var->var_name);
	vlist->var.var_name[strlen(vlist->var.var_name)]	= NULL;

	vlist->var.true_type_id	= var->true_type_id;
	vlist->var.type_id	= var->type_id;
	vlist->var.offset	= var->offset;
	vlist->var.len		= var->len;
	vlist->var.len_1	= var->len_1;
	vlist->var.total_len	= var->total_len;
	vlist->var.var_addr	= var->var_addr;	
	vlist->var.var_id	= var->var_id;

	//------------------------------------------------------------------
	// dest
	//------------------------------------------------------------------
	

	//------------------------------------------------------------------
	// add src to dest
	//------------------------------------------------------------------
	for(; p->tail; p=p->tail)
	{}

	vlist->head	= p;
	p->tail		= vlist;
	vlist->tail	= NULL;
}


//===========================================================================
// search_var
//===========================================================================
PUBLIC	struct s_var*	search_var_s(s8 *name)
{
//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- search_var(s)  -- \n");
#endif
//--------------------------

	//------------------------------------------------------------------
	// search in frames
	//------------------------------------------------------------------
	struct s_framelist *frl	= pframelist;

	for(; frl; frl=frl->tail)
	{
		struct s_varlist *varl	= &(frl->frame.varlist);

		for(; varl; varl=varl->tail)
		{
			if(strcmp(varl->var.var_name, name) == TRUE)
			{
				return &(varl->var);
			}
		}
	} 
	
	//------------------------------------------------------------------
	// search in global varlist
	//------------------------------------------------------------------
	struct s_varlist *gvarl	= pvarlist;

	for(; gvarl; gvarl=gvarl->tail)
	{
		if(strcmp(gvarl->var.var_name, name) == TRUE)
		{
			return &(gvarl->var);
		}
	} 	

//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- search_var(e)  -- \n");
#endif
//--------------------------

	return NULL;
}


//===========================================================================
// pvlist_build
//===========================================================================
PUBLIC	struct ir_pvlist*	pvlist_build(struct ir_exp *exp)
{
//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- pvlist_build(s)  -- \n");
#endif
//--------------------------

	struct ir_pvlist * pvlist	= malloc(sizeof(struct ir_pvlist));

	pvlist->exp	= exp;
	pvlist->head	= NULL;
	pvlist->tail	= NULL;

//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- pvlist_build(e)  -- \n");
#endif
//--------------------------

	return pvlist;
}


//===========================================================================
// add2pvlist
//===========================================================================
PUBLIC	s8	add2pvlist(struct ir_explist *srclist, struct ir_explist *dstlist)
{
//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- add2pvlist(s)  -- \n");
#endif
//--------------------------

	for(; dstlist->tail; dstlist=dstlist->tail)
	{}

	dstlist->tail	= srclist;
	srclist->head	= dstlist;
	srclist->tail	= NULL;

//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- add2pvlist(e)  -- \n");
#endif
//--------------------------

}


//===========================================================================
// printvarlist()
//===========================================================================
PUBLIC	s8	printvarlist(struct s_varlist *p)
{
	printf("\n	**************************************************************************************************\n");
	printf("	%10s| %10s| %10s| %10s| %10s| %10s| %10s|%10s|\n", "var_id", "var_name","offset","type","true_type", "len","len_1","total_len");
	printf("	---------------------------------------------------------------------------------------------------\n");

	for(p=p->tail; p; p=p->tail)
	{
		printf("	%10d| %10s| %10d| %10s| %10s| %10d| %10d| %10d|\n", p->var.var_id, p->var.var_name, p->var.offset, check_type_s_1(p->var.type_id), check_type_s(p->var.true_type_id), p->var.len, p->var.len_1, p->var.total_len);		
	}

	printf("	**************************************************************************************************\n");	
}

//===========================================================================
// printvarlist()
//===========================================================================
PUBLIC	s8	print_g_varlist()
{
	printf("\n==================================================\n");
	printf("%s\n", "Global var list:");
	printf("----------------\n");
			
	printvarlist(&varlist);

	printf("==================================================\n");
}
