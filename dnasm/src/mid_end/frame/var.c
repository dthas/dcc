//===========================================================================
// var.c
//   Copyright (C) 2013 Free Software Foundation, Inc.
//   Originally by ZhaoFeng Liang <zhf.liang@outlook.com>
//
//This file is part of DTHAS_DNASM.
//
//DTHAS_DNASM is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or 
//(at your option) any later version.
//
//DTHAS_DNASM is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with DTHAS; If not, see <http://www.gnu.org/licenses/>.  
//===========================================================================

#include	"dnasm_global.h"
#include	"dnasm_type.h"
#include	"dnasm_symtbl.h"
#include	<stdio.h>
#include	"dnasm_main.h"
#include	"dnasm_lex_char.h"
#include	"dnasm_lex_word.h"
#include	"dnasm_parse.h"
#include	"dnasm_seman.h"
#include	"dnasm_ir.h"
#include	"dnasm_label.h"
#include	"dnasm_frame.h"
#include	"dnasm_prototype.h"

#define	VAR_DEBUG

struct s_varlist varlist;

//===========================================================================
// var_build
//===========================================================================
PUBLIC	void	var_init()
{
	pvarlist	= &varlist;		//for global var	
	g_var_addr_offset	= 0;		
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

	len	= check_type_l(sym->type_ts);

	g_var_addr_offset += len;

	offset	= g_var_addr_offset;
	
	var		= var_build_1(sym->name, true_type_id, type_id, offset, len,  var_id);
		
	add_var2varlist(var, &varlist);

//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- var_build(e)  -- \n");
#endif
//--------------------------

	return var;
}

//===========================================================================
// var_build_1
//===========================================================================
PUBLIC	struct s_var *	var_build_1(s8* name, s32 true_type_id, s32 type_id, s32 offset, s32 len, s32 var_id)
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
	var->var_offset	= offset;
	var->len	= len;
	
//--------------------------
//test
#ifdef	FRAME_DEBUG
	printf("	-- var_build_1(e)  -- \n");
#endif
//--------------------------

	return var;
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
	vlist->var.var_offset	= var->var_offset;
	vlist->var.len		= var->len;
	vlist->var.var_id	= var->var_id;

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

	return NULL;
}


//===========================================================================
// printvarlist()
//===========================================================================
PUBLIC	s8	printvarlist(struct s_varlist *p)
{
	printf("\n	**************************************************************************************************\n");
	printf("	%10s| %10s| %10s| %10s| %10s| %10s| \n", "var_id", "var_name","offset","type","true_type", "len");
	printf("	---------------------------------------------------------------------------------------------------\n");

	for(p=p->tail; p; p=p->tail)
	{
		printf("	%10d| %10s| %10d| %10s| %10s| %10d| \n", p->var.var_id, p->var.var_name, p->var.var_offset, check_type_s_1(p->var.type_id), check_type_s(p->var.true_type_id), p->var.len);		
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
