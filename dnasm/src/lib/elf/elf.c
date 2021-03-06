//===========================================================================
// elf.c
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
// elf_header_build
//===========================================================================
PUBLIC	struct elf_header *	elf_header_build(u32 entry, u32 section_header_offset, u32 program_header_offset, u32 flags, u16 program_header_size, u16 program_header_num)
{
	printf("==================================================================\n");
	printf("	elf_header_build\n");
	printf("==================================================================\n");

	struct elf_header *elfh	= malloc(sizeof(struct elf_header));

	if(!elfh)
	{
		printf("error::can not alloc elf_header !!!\n\n");
		exit(0);
	}

	s32 i;
	for(i=0; i<ELF_IDEN_LEN; i++)
	{
		elfh->iden[i]	= NULL;
	}

	elfh->iden[0]	= 0x7F;				//DEL
	elfh->iden[1]	= 0x45;				//E
	elfh->iden[2]	= 0x4C;				//L
	elfh->iden[3]	= 0x46;				//F
	elfh->iden[4]	= ELF_IDEN_32_FILE;		//32bit file
	elfh->iden[5]	= ELF_IDEN_LITTLE_END;		//1
	elfh->iden[6]	= ELF_IDEN_VERSION;		//1

	elfh->type				= ELF_TYPE_REL;
	elfh->machine				= ELF_MACHINE_X86;
	elfh->version				= ELF_VERSION;
	elfh->entry				= entry;
	elfh->program_header_offset		= program_header_offset;
	elfh->section_header_offset		= section_header_offset	;	//default: 0x40;
	elfh->flags				= flags;
	elfh->elf_header_size			= ELF_HEADER_SIZE;		//52 bytes
	elfh->program_header_size		= program_header_size;		
	elfh->program_header_num		= program_header_num;		
	elfh->section_header_size		= SECTION_HEADER_SIZE;		//40 bytes
	elfh->section_header_num		= SECTION_NUM;			//9: null,.data,.text,.bss,.rodata,.rel.txt,.shstrtab,.symtab,.strtab
	elfh->section_header_strtab_index	= SECTION_INDEX_SHSTRTAB;	//6

	return elfh;
}

//===========================================================================
// section_header_build
//===========================================================================
PUBLIC	struct section_header *	section_header_build(s32 index, s32 type, s32 flags, s32 addr, s32 offset, s32 size, s32 link, s32 info, s32 align, s32 entry_size)
{
	printf("==================================================================\n");
	printf("	section_header_build\n");
	printf("==================================================================\n");

	struct section_header *sech	= malloc(sizeof(struct section_header));

	if(!sech)
	{
		printf("error::can not alloc section_header !!!\n\n");
		exit(0);
	}

	sech->name		= index;
	sech->type		= type;
	sech->flags		= flags;
	sech->addr		= addr;
	sech->offset		= offset;
	sech->size		= size;	
	sech->link		= link;
	sech->info		= info;
	sech->addr_align	= align;
	sech->entry_size	= entry_size;

	return sech;
}
