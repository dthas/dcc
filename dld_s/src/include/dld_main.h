//===========================================================================
// dld_main.h
//   Copyright (C) 2013 Free Software Foundation, Inc.
//   Originally by ZhaoFeng Liang <zhf.liang@outlook.com>
//
//This file is part of DTHAS_DLD.
//
//DTHAS_DLD is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or 
//(at your option) any later version.
//
//DTHAS_DLD is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with DTHAS; If not, see <http://www.gnu.org/licenses/>.  
//===========================================================================

#ifndef	_DLD_MAIN_H_
#define	_DLD_MAIN_H_

#define	DLD_FILENAEM_LEN	64
#define	TRUNK_SIZE		1024
#define	SECTION_SIZE		512

//-------------------------------------------------------------------------
// section info
//-------------------------------------------------------------------------
struct section_info
{
	u32	src_start_addr;
	u32	dst_start_addr;
	u32	size;
	s32	offset;
	s32	align_offset;
};

//-------------------------------------------------------------------------
// object info
//-------------------------------------------------------------------------
struct obj_info
{
	s8	filename[DLD_FILENAEM_LEN];
	struct section_info	null_info;
	struct section_info	data_info;
	struct section_info	text_info;
	struct section_info	bss_info;
	struct section_info	rodata_info;
	struct section_info	reltext_info;
	struct section_info	shstrtab_info;
	struct section_info	symtab_info;
	struct section_info	strtab_info;
	struct section_info	comment_info;
	struct section_info	eh_frame_info;
	struct section_info	rel_eh_frame_info;
	struct section_info	note_gnu_stack_info;
};

//-------------------------------------------------------------------------
// object info
//-------------------------------------------------------------------------
struct objinfo_list
{
	struct obj_info *oinfo;
	
	struct objinfo_list *head;
	struct objinfo_list *tail;
};


//-------------------------------------------------------------------------
// offset_list
//-------------------------------------------------------------------------
struct offset_list
{
	s32	offset;
	
	struct offset_list *head;
	struct offset_list *tail;
};

//-------------------------------------------------------------------------
// variables
//-------------------------------------------------------------------------
FILE	*fr, *fw;

struct objinfo_list *srcl, *dstl;
struct obj_info *dsti;

PUBLIC	s32 	strtab_offset;
PUBLIC	s32 	symtab_offset;

u32	sum_size_symtab;

#endif
