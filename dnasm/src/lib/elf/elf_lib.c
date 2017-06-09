//===========================================================================
// elf_lib.c
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
#include	"dnasm_elf.h"
#include	"dnasm_prototype.h"

#define	ELF_DEBUG

//===========================================================================
// rel32list_build
//===========================================================================
PUBLIC	struct rel32_list *	rel32list_build(struct rel32 *rel)
{
//--------------------------
//test
#ifdef	ELF_DEBUG
	printf("	-- rel32list_build  -- \n");
#endif
//--------------------------

	struct rel32_list *rel_list	= malloc(sizeof(struct rel32_list));

	if(!rel_list)
	{
		printf("rel32list_build() malloc failed!!\n");
		exit(1);
	}

	rel_list->rel	= rel;
	rel_list->head	= NULL;
	rel_list->tail	= NULL;

	return rel_list;
}

//===========================================================================
// elf_add2elflist
//===========================================================================
PUBLIC	s8	elf_add2rellist(struct rel32_list *src, struct rel32_list * dst)
{
//--------------------------
//test
#ifdef	ELF_DEBUG
	printf("	-- elf_add2rellist  -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}

//===========================================================================
// elfsymtablist_build
//===========================================================================
PUBLIC	struct elfsymtab_list *	elfsymtablist_build(struct elf_symtab *sym)
{
//--------------------------
//test
#ifdef	ELF_DEBUG
	printf("	-- elfsymtablist_build  -- \n");
#endif
//--------------------------

	struct elfsymtab_list *sym_list	= malloc(sizeof(struct elfsymtab_list));

	if(!sym_list)
	{
		printf("elfsymtablist_build() malloc failed!!\n");
		exit(1);
	}

	sym_list->sym	= sym;
	sym_list->head	= NULL;
	sym_list->tail	= NULL;

	return sym_list;
}

//===========================================================================
// elf_add2rellist
//===========================================================================
PUBLIC	s8	elf_add2symlist(struct elfsymtab_list *src, struct elfsymtab_list * dst)
{
//--------------------------
//test
#ifdef	ELF_DEBUG
	printf("	-- elf_add2symlist  -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}

//===========================================================================
// strtablist_build
//===========================================================================
PUBLIC	struct strtab_list *	strtablist_build(struct strtab *str)
{
//--------------------------
//test
#ifdef	ELF_DEBUG
	printf("	-- strtablist_build  -- \n");
#endif
//--------------------------

	struct strtab_list *str_list	= malloc(sizeof(struct strtab_list));

	if(!str_list)
	{
		printf("strtablist_build() malloc failed!!\n");
		exit(1);
	}

	str_list->str	= str;
	str_list->head	= NULL;
	str_list->tail	= NULL;

	return str_list;
}

//===========================================================================
// elf_add2strlist
//===========================================================================
PUBLIC	s8	elf_add2strlist(struct strtab_list *src, struct strtab_list * dst)
{
//--------------------------
//test
#ifdef	ELF_DEBUG
	printf("	-- elf_add2strlist  -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}


//===========================================================================
// dbtablist_build
//===========================================================================
PUBLIC	struct dbtab_list *	dbtablist_build(struct dbtab *db)
{
//--------------------------
//test
#ifdef	ELF_DEBUG
	printf("	-- dbtablist_build  -- \n");
#endif
//--------------------------

	struct dbtab_list *str_list	= malloc(sizeof(struct dbtab_list));

	if(!str_list)
	{
		printf("dbtablist_build() malloc failed!!\n");
		exit(1);
	}

	str_list->db	= db;
	str_list->head	= NULL;
	str_list->tail	= NULL;

	return str_list;
}

//===========================================================================
// elf_add2dblist
//===========================================================================
PUBLIC	s8	elf_add2dblist(struct dbtab_list *src, struct dbtab_list * dst)
{
//--------------------------
//test
#ifdef	ELF_DEBUG
	printf("	-- elf_add2dblist  -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}
