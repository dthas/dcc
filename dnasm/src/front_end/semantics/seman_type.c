//===========================================================================
// seman_type.c
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
#include	"dnasm_prototype.h"

#define	SEMAN_DEBUG

struct s_typelist typelist;

//===========================================================================
// init_typelist()
//===========================================================================
PUBLIC	void	init_typelist()
{
//--------------------------
//test
#ifdef	SEMAN_DEBUG
	printf("	-- init_typelist  -- \n");
#endif
//--------------------------

	type_id_selfdef	= TYPE_ID_SELFDEF_INIT;

	p_typelist	= &typelist;

	typelist.head 		= NULL;
	typelist.tail		= NULL;
	typelist.ty.true_type_id= 0;
	typelist.ty.type_id	= 0;
	typelist.ty.type_name[0]= NULL;

	add_typelist(DB, 1, "db", "db");
	add_typelist(DW, 2, "dw", "dw");
	add_typelist(DD, 4, "dd", "dd");
	add_typelist(DQ, 8, "dq", "dq");
	add_typelist(DT, 16, "dt", "dt");
	add_typelist(DY, 32, "dy", "dy");
	add_typelist(RESB, 1, "resb", "resb");
	add_typelist(RESW, 2, "resw", "resw");
	add_typelist(RESQ, 4, "resq", "resq");
	add_typelist(RESY, 8, "resy", "resy");

	add_typelist(BYTE, 1, "byte", "byte");
	add_typelist(WORD, 2, "word", "word");
	add_typelist(DWORD, 4, "dword", "dword");
	
	print_typelist();
}

//===========================================================================
// check_type(u32 type_id)
//===========================================================================
PUBLIC	s8*	check_type_s(s32 type_id)
{
	struct s_typelist *p	= &typelist;
	for(; p; p=p->tail)
	{
		if(type_id == p->ty.true_type_id)
		{
			return p->ty.type_name;
		}
	}

	printf("[error]::check_type::Illegal type::%d\n\n", type_id);

	return NULL;
}

//===========================================================================
// check_type(u32 type_id)
//===========================================================================
PUBLIC	s8*	check_type_s_1(s32 type_id)
{
	if(!type_id)
	{
		return "NONE";
	}

	struct s_typelist *p	= &typelist;
	for(; p; p=p->tail)
	{
		if(type_id == p->ty.type_id)
		{
			return (p_word+(p->ty.type_id)*20);
		}
	}

	printf("[error]::check_type::Illegal type::%d\n\n", type_id);	
	
	return NULL;
}

//===========================================================================
// check_type(u32 type_id)
//===========================================================================
PUBLIC	s32	check_type_i(s8 *name)
{
	struct s_typelist *p	= &typelist;
	for(; p; p=p->tail)
	{
		if(strcmp(name, p->ty.type_name) == TRUE)
		{
			return p->ty.true_type_id;
		}
	}

	printf("[error]::check_type::Illegal type::%s\n\n", name);
	
	return FALSE;
}

//===========================================================================
// check_type(u32 type_id)
//===========================================================================
PUBLIC	s32	check_type_l(s32 type_id)
{
	struct s_typelist *p	= &typelist;
	for(; p; p=p->tail)
	{
		if(type_id == p->ty.true_type_id)
		{
			return p->ty.len;
		}
	}

	printf("[error]::check_type::Illegal type::%d\n\n", type_id);
	
	return NULL;
}

//===========================================================================
// check_type(u32 type_id)
//===========================================================================
PUBLIC	struct s_type*	check_type_t(s32 type_id)
{
	struct s_typelist *p	= &typelist;
	for(; p; p=p->tail)
	{
		if(type_id == p->ty.true_type_id)
		{
			return &(p->ty);
		}
	}

	printf("[error]::check_type::Illegal type::%d\n\n", type_id);
	
	return NULL;
}

//===========================================================================
// check_type(u32 type_id)
//===========================================================================
PUBLIC	struct s_type*	check_type_t_1(s32 type_id)
{
	struct s_typelist *p	= &typelist;
	for(; p; p=p->tail)
	{
		if(type_id == p->ty.type_id)
		{
			return &(p->ty);
		}
	}

	printf("[error]::check_type::Illegal type::%d\n\n", type_id);
	
	return NULL;
}


//===========================================================================
// add_typelist()
//===========================================================================
PUBLIC	s8	add_typelist(s32 true_type_id, s32 len, s8 *src_name, s8 *dst_name)
{
//--------------------------
//test
#ifdef	SEMAN_DEBUG
	printf("	-- add_typelist(s)  -- \n");
#endif
//--------------------------

	s8 flg = FALSE;
	struct s_typelist *p	= &typelist;

	if(!true_type_id)
	{		
		for(; p!=NULL; p=p->tail)
		{
			if(strcmp(src_name, p->ty.type_name) == TRUE)
			{
				flg	= TRUE;
				break;
			}			
		}

		if(!flg)
		{
			printf("[error]::add_typelist::Illegal type::%s\n\n", src_name);
			exit(1);
		}
		else
		{
			true_type_id	= p->ty.true_type_id;
		}	
	}

	struct s_typelist *tylist = malloc(sizeof(struct s_typelist));

	tylist->ty.true_type_id		= true_type_id;
	tylist->ty.type_id		= true_type_id;
	tylist->ty.len			= len;
		
	strcopy(tylist->ty.type_name, dst_name);
	tylist->ty.type_name[strlen(dst_name)]	= NULL;	

	p	= &typelist;
	for(; p->tail; p=p->tail)
	{}
	
	p->tail		= tylist;
	tylist->head	= p;
	tylist->tail	= NULL;

//--------------------------
//test
#ifdef	SEMAN_DEBUG
	printf("	-- add_typelist(e)  -- \n");
#endif
//--------------------------
}

//===========================================================================
// print_typelist()
//===========================================================================
PUBLIC	void	print_typelist()
{
	printf("\n\n	====================================================\n");
	printf("	%12s| %10s| %12s| %10s|\n", "true_typeid","type_id","len(bytes)","name");
	printf("	----------------------------------------------------\n");

	struct s_typelist *tylist= &typelist;

	for(; tylist; tylist = tylist->tail)
	{
		printf("	%12d| %10s| %12d| %10s|\n", tylist->ty.true_type_id, (tylist->ty.type_id == 0? "NONE":(p_word+(tylist->ty.type_id)*20)), tylist->ty.len, tylist->ty.type_name);
	}

	printf("	====================================================\n");
}
