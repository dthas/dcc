//===========================================================================
// mcode_lib.c
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
#include	"dnasm_block.h"
#include	"dnasm_elf.h"
#include	"dnasm_ins.h"
#include	"dnasm_prototype.h"

#define	MCODE_DEBUG

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
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
// align_16(FILE *foutput, s32 num)
//===========================================================================
PUBLIC	s32	align_16(FILE *foutput, s32 offset)
{
	s32 num	= 16 - (offset % 16);

	s8 i,j;
	for(j=0, i=0; i<num; i++)
	{
		fwrite(&j,sizeof(char),1,foutput);
	}

	return num;
}
