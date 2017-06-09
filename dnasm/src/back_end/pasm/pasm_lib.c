//===========================================================================
// ir_code_lib.c
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
#include	"dnasm_frame.h"
#include	"dnasm_ir.h"
#include	"dnasm_pasm.h"
#include	"dnasm_prototype.h"

#define	PASM_DEBUG

//===========================================================================
// add(u32 src, u32 dst)
//===========================================================================
PUBLIC	struct pasm_exp*	add(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- add -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_EXP_ADD;

	p->e.add.src_reg	= src;
	p->e.add.src_id		= src_id;
	p->e.add.dst_reg	= dst;
	p->e.add.dst_id		= dst_id;

	p->e.add.src_len	= src_len;
	p->e.add.dst_len	= dst_len;

	strcopy(p->e.add.src_name, src_name);
	p->e.add.src_name[strlen(p->e.add.src_name)]	= NULL;	

	strcopy(p->e.add.dst_name, dst_name);
	p->e.add.dst_name[strlen(p->e.add.dst_name)]	= NULL;	

	return	p;
}

//===========================================================================
// minus(u32 src, u32 dst)
//===========================================================================
PUBLIC	struct pasm_exp*	minus(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- minus -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_EXP_SUB;

	p->e.minus.src_reg		= src;
	p->e.minus.src_id	= src_id;
	p->e.minus.dst_reg		= dst;
	p->e.minus.dst_id	= dst_id;

	p->e.minus.src_len	= src_len;
	p->e.minus.dst_len	= dst_len;

	strcopy(p->e.minus.src_name, src_name);
	p->e.minus.src_name[strlen(p->e.minus.src_name)]	= NULL;	

	strcopy(p->e.minus.dst_name, dst_name);
	p->e.minus.dst_name[strlen(p->e.minus.dst_name)]	= NULL;	

	return	p;	
}

//===========================================================================
// minus(u32 src, u32 dst)
//===========================================================================
PUBLIC	struct pasm_exp*	mul(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- mul -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_EXP_MUL;

	p->e.mul.src_reg		= src;
	p->e.mul.src_id	= src_id;
	p->e.mul.dst_reg		= dst;
	p->e.mul.dst_id	= dst_id;

	p->e.mul.src_len	= src_len;
	p->e.mul.dst_len	= dst_len;

	strcopy(p->e.mul.src_name, src_name);
	p->e.mul.src_name[strlen(p->e.mul.src_name)]	= NULL;	

	strcopy(p->e.mul.dst_name, dst_name);
	p->e.mul.dst_name[strlen(p->e.mul.dst_name)]	= NULL;	

	return	p;	
}

//===========================================================================
// minus(u32 src, u32 dst)
//===========================================================================
PUBLIC	struct pasm_exp*	div(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- div -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_EXP_DIV;

	p->e.div.src_reg		= src;
	p->e.div.src_id	= src_id;
	p->e.div.dst_reg		= dst;
	p->e.div.dst_id	= dst_id;

	p->e.div.src_len	= src_len;
	p->e.div.dst_len	= dst_len;

	strcopy(p->e.div.src_name, src_name);
	p->e.div.src_name[strlen(p->e.div.src_name)]	= NULL;	

	strcopy(p->e.div.dst_name, dst_name);
	p->e.div.dst_name[strlen(p->e.div.dst_name)]	= NULL;	

	return	p;	
}


//===========================================================================
// pop(u32 var_addr, u32 var_type_len, s8 *name)
//===========================================================================
PUBLIC	void	reset_pasm(struct pasm_exp *pe)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- reset pasm -- \n");
#endif
//--------------------------

	s32 len	= sizeof(struct pasm_exp);

	s32 i;
	for(i=0; i<len; i++)
	{
		*((s8*)pe+i)	= NULL;
	}
}

//===========================================================================
// label(s8* label_name, u32 id)
//===========================================================================
PUBLIC	struct pasm_exp *	label(s8* label_name, u32 id)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- label -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	if(p)
	{
		p->k			= PASM_EXP_LABEL;
		p->e.label.label_name	= label_name;
		p->e.label.label_id	= id;
	}
	
	return	p;	
}

//===========================================================================
// label(s8* label_name, u32 id)
//===========================================================================
PUBLIC	struct pasm_exp *	var(s8* var_name)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- var -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	if(p)
	{
		p->k			= PASM_EXP_VAR;
		p->e.var.var_name	= var_name;		
	}
	
	return	p;
	
}
