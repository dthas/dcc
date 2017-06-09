//===========================================================================
// main_lib.c
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

#include	"dld_global.h"
#include	"dld_type.h"
#include	<stdio.h>
#include	"dld_elf.h"
#include	"dld_main.h"
#include	"dld_prototype.h"

#define	DLD_DEBUG

//===========================================================================
// section_copy(struct section_header *dst, struct section_header *src)
//===========================================================================
PUBLIC	void	section_copy(struct section_header *dst, struct section_header *src)
{
	printf("==================================================================\n");
	printf("	section_copy\n");
	printf("==================================================================\n");

	dst->name	= src->name;
	dst->type	= src->type;
	dst->flags	= src->flags;
	dst->addr	= src->addr;
	dst->offset	= src->offset;
	dst->size	= src->size;
	dst->link	= src->link;
	dst->info	= src->info;
	dst->addr_align	= src->addr_align;
	dst->entry_size	= src->entry_size;
}

//===========================================================================
// align_16_file(FILE *foutput, s32 num)
//===========================================================================
PUBLIC	s32	align_16_file(FILE *foutput, s32 offset)
{
	s32 num	= 16 - (offset % 16);

	s8 i,j;
	for(j=0x90, i=0; i<num; i++)
	{
		fwrite(&j,sizeof(char),1,foutput);
	}

	return num;
}

//===========================================================================
// align_16_file(FILE *foutput, s32 num)
//===========================================================================
PUBLIC	s32	align_16_mem(s32 offset)
{
	s32 num	= offset + (16 - (offset % 16));	

	return num;
}

//===========================================================================
// objlist_build
//===========================================================================
PUBLIC	struct objinfo_list *	objlist_build(struct obj_info *oinfo)
{
//--------------------------
//test
#ifdef	DLD_DEBUG
	printf("	-- dbtablist_build  -- \n");
#endif
//--------------------------

	struct objinfo_list *obj_list	= malloc(sizeof(struct objinfo_list));

	if(!obj_list)
	{
		printf("objlist_build() malloc failed!!\n");
		exit(1);
	}

	obj_list->oinfo	= oinfo;
	obj_list->head	= NULL;
	obj_list->tail	= NULL;

	return obj_list;
}

//===========================================================================
// dld_add2objlist
//===========================================================================
PUBLIC	s8	dld_add2objlist(struct objinfo_list *src, struct objinfo_list * dst)
{
//--------------------------
//test
#ifdef	DLD_DEBUG
	printf("	-- dld_add2objlist  -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}


//===========================================================================
// offsetlist_build
//===========================================================================
PUBLIC	struct offset_list *	offsetlist_build(s32 offset)
{
//--------------------------
//test
#ifdef	DLD_DEBUG
	printf("	-- offsetlist_build(s)  -- \n\n");
#endif
//--------------------------

	struct offset_list *off_list	= malloc(sizeof(struct offset_list));

	if(!off_list)
	{
		printf("offsetlist_build() malloc failed!!\n");
		exit(1);
	}

	off_list->offset= offset;
	off_list->head	= NULL;
	off_list->tail	= NULL;

//--------------------------
//test
#ifdef	DLD_DEBUG
	printf("	-- offsetlist_build(e)  -- \n\n");
#endif
//--------------------------

	return off_list;
}

//===========================================================================
// dld_add2offsetlist
//===========================================================================
PUBLIC	s8	dld_add2offsetlist(struct offset_list *src, struct offset_list * dst)
{
//--------------------------
//test
#ifdef	DLD_DEBUG
	printf("	-- dld_add2offsetlist(s)  dst=0x%x, dst->tail=0x%x-- \n\n", dst, dst->tail);
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;

//--------------------------
//test
#ifdef	DLD_DEBUG
	printf("	-- dld_add2offsetlist(e)  -- \n\n");
#endif
//--------------------------

}
