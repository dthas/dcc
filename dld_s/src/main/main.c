//===========================================================================
// main.c
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
#include	"dld_global.h"
#include	"dld_type.h"
#include	<stdio.h>
#include	"dld_elf.h"
#include	"dld_main.h"
#include	"dld_prototype.h"

#define	DLD_DEBUG

//===========================================================================
// main
//===========================================================================
PUBLIC	s32	main(s32 argc, s8*argv[])
{
	
	printf("\n-------------------------------------------------------------------------\n");
	printf("	dld main\n");
	printf("-------------------------------------------------------------------------\n");

	srcl	= malloc(sizeof(struct objinfo_list));		//for the source section information of each object file(test.o, start.o,...)
	
	dsti	= malloc(sizeof(struct obj_info));		//for the output file(test)

	if(!srcl)
	{
		printf("error::malloc objinfo_list fail !!!\n\n");
		exit(0);
	}

	//------------------------------------------------------------------
	// initial struct
	//------------------------------------------------------------------
	s32 j;
	for(j=0; j<ELF_IDEN_LEN; j++)
	{
		g_entry.label[j]	= NULL;
	}

	g_entry.addr		= 0;
	g_entry.label[0]	= '_';
	g_entry.label[1]	= 's';
	g_entry.label[2]	= 't';
	g_entry.label[3]	= 'a';
	g_entry.label[4]	= 'r';
	g_entry.label[5]	= 't';
	g_entry.label[6]	= NULL;

	//------------------------------------------------------------------
	// inintial variables
	//------------------------------------------------------------------

	file_offset	= 0;
	vir_offset	= 0;	

	elf_header_offset	= 0;
	elf_header_size		= sizeof(struct elf_header);					//0x34
	program_header_offset	= elf_header_offset + elf_header_size; 				//0x34
	program_header_size	= sizeof(struct program_header) * 3;				//text,data,bss:: 0x20 * 3 = 0x60
		
	section_header_offset	= elf_header_offset + elf_header_size + program_header_size;	// 0x34 + 0x60 = 0x94
	section_header_size	= sizeof(struct section_header) * SECTION_NUM;			// 40 * 13
	
	section_content_offset	= SECTION_DATA_START_ADDR;					// 0x1000

	vir_offset	= s2h((argv[2]+2));		//0x8048000
	vir_data_offset	= 0;

	//------------------------------------------------------------------
	// get the section information of each file
	//------------------------------------------------------------------
	s32 i;
	for(i=4; i<argc; i++)
	{
		printf("%d) %s\n", i, argv[i]);

		read_obj(argv[i], srcl);
	}

	//------------------------------------------------------------------
	// combine all the section information and output to the dest file
	//------------------------------------------------------------------
	exe_obj(srcl, dsti);

	//------------------------------------------------------------------
	// output the target file
	//------------------------------------------------------------------
	s8 output_file[]	= "src/temp/test";

	output_obj(output_file, srcl, dsti);

	//------------------------------------------------------------------
	// update symtab do exe
	//------------------------------------------------------------------
	do_upd_symtab(output_file, srcl, dsti);

	//------------------------------------------------------------------
	// update elf header(_start)
	//------------------------------------------------------------------
	do_upd_elfstart(output_file, srcl, dsti);

	//------------------------------------------------------------------
	// relocate do exe
	//------------------------------------------------------------------
	do_rel(output_file, srcl, dsti);	
}






