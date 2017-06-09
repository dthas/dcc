//===========================================================================
// block_lib.c
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
#include	"dcc_prototype.h"

#define	BLOCK_DEBUG

//===========================================================================
// block_build
//===========================================================================
PUBLIC	struct block*	block_build(struct pasm_stslist *stslist)
{
//--------------------------
//test
#ifdef	BLOCK_DEBUG
	printf("-- block_build -- \n");
#endif
//--------------------------

	struct block*	p	= malloc(sizeof(struct block));

	if(p)
	{
		p->stslist	= stslist;
		p->head		= NULL;
		p->tail		= NULL;		
	}

	return	p;
}

//===========================================================================
// add2block
//===========================================================================
PUBLIC	s8	add2block(struct block *src, struct block *dst)
{
//--------------------------
//test
#ifdef	BLOCK_DEBUG
	printf("-- add2block -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}


//===========================================================================
// blocklist_build
//===========================================================================
PUBLIC	struct blocklist*	blocklist_build(struct block *block)
{
//--------------------------
//test
#ifdef	BLOCK_DEBUG
	printf("-- blocklist_build -- \n");
#endif
//--------------------------

	struct blocklist*	p	= malloc(sizeof(struct blocklist));

	if(p)
	{
		p->block	= block;
		p->head		= NULL;
		p->tail		= NULL;		
	}

	return	p;
}

//===========================================================================
// block_build
//===========================================================================
PUBLIC	s8	add2blocklist(struct blocklist *src, struct blocklist *dst)
{
//--------------------------
//test
#ifdef	BLOCK_DEBUG
	printf("-- add2blocklist -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}
