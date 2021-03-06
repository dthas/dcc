//===========================================================================
// main_lib_1.c
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

PRIVATE s8 pr_buf_s[SECTION_SIZE];
//===========================================================================
// pr_objinfo(struct objinfo_list *olist)
//===========================================================================
PUBLIC	void	pr_objinfo_list(struct objinfo_list *olist)
{
	printf("\n\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("	print object list\n");
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

	s32 i;
	for(i=0; olist ; olist=olist->tail, i++)
	{
		if(olist->oinfo)
		{
			printf("File(%i) : %s\n",i, olist->oinfo->filename);
			pr_objinfo(olist->oinfo);
		}
	}
}

//===========================================================================
// pr_objinfo(struct objinfo_list *olist)
//===========================================================================
PUBLIC	void	pr_objinfo(struct obj_info *oi)
{
	printf("===========================================================================================================================\n");
	printf("%8s |%8s| %8s| %8s| %8s| %8s| %8s| %8s| %8s| %8s | %8s| %8s| %8s| %8s\n",
	 "","null","text","data","bss","rodata","reltext","shstrtab","symtab", "strtab", "comment", "ehfr", "r_ehfr","stack");
	printf("---------------------------------------------------------------------------------------------------------------------------\n");

	printf("%8s | %8x| %8x| %8x| %8x| %8x| %8x| %8x| %8x| %8x|%8x| %8x| %8x| %8x|\n", "addr(s):", oi->null_info.src_start_addr,
		oi->text_info.src_start_addr, oi->data_info.src_start_addr,
		oi->bss_info.src_start_addr ,oi->rodata_info.src_start_addr,oi->reltext_info.src_start_addr,
		oi->shstrtab_info.src_start_addr,oi->symtab_info.src_start_addr,oi->strtab_info.src_start_addr,
		oi->comment_info.src_start_addr, oi->eh_frame_info.src_start_addr,oi->rel_eh_frame_info.src_start_addr,
		oi->note_gnu_stack_info.src_start_addr);

	printf("%8s | %8x| %8x| %8x| %8x| %8x| %8x| %8x| %8x| %8x|%8x| %8x| %8x| %8x|\n", "size:", oi->null_info.size,
		oi->text_info.size,oi->data_info.size,
		oi->bss_info.size ,oi->rodata_info.size,oi->reltext_info.size,
		oi->shstrtab_info.size,oi->symtab_info.size,oi->strtab_info.size,
		oi->comment_info.size, oi->eh_frame_info.size,oi->rel_eh_frame_info.size,
		oi->note_gnu_stack_info.size);

	printf("%8s | %8x| %8x| %8x| %8x| %8x| %8x| %8x| %8x| %8x|%8x| %8x| %8x| %8x|\n", "offset:", oi->null_info.offset,
		oi->text_info.offset, oi->data_info.offset,
		oi->bss_info.offset ,oi->rodata_info.offset,oi->reltext_info.offset,
		oi->shstrtab_info.offset,oi->symtab_info.offset,oi->strtab_info.offset,
		oi->comment_info.offset, oi->eh_frame_info.offset,oi->rel_eh_frame_info.offset,
		oi->note_gnu_stack_info.offset);
	
	printf("%8s | %8x| %8x| %8x| %8x| %8x| %8x| %8x| %8x| %8x|%8x| %8x| %8x| %8x|\n", "addr(d):", oi->null_info.dst_start_addr,
		oi->text_info.dst_start_addr, oi->data_info.dst_start_addr,
		oi->bss_info.dst_start_addr ,oi->rodata_info.dst_start_addr,oi->reltext_info.dst_start_addr,
		oi->shstrtab_info.dst_start_addr,oi->symtab_info.dst_start_addr,oi->strtab_info.dst_start_addr,
		oi->comment_info.dst_start_addr, oi->eh_frame_info.dst_start_addr,oi->rel_eh_frame_info.dst_start_addr,
		oi->note_gnu_stack_info.dst_start_addr);

	printf("%8s | %8x| %8x| %8x| %8x| %8x| %8x| %8x| %8x| %8x|%8x| %8x| %8x| %8x|\n", "addr(L):", 
		0,
		oi->text_info.src_start_addr + vir_offset - section_content_offset,
		oi->data_info.src_start_addr + vir_offset - section_content_offset,
		oi->bss_info.src_start_addr  + vir_offset - section_content_offset,
		oi->rodata_info.src_start_addr + vir_offset - section_content_offset,
		oi->reltext_info.src_start_addr + vir_offset - section_content_offset,
		oi->shstrtab_info.src_start_addr + vir_offset - section_content_offset,
		oi->symtab_info.src_start_addr + vir_offset - section_content_offset,
		oi->strtab_info.src_start_addr + vir_offset - section_content_offset,
		oi->comment_info.src_start_addr + vir_offset - section_content_offset,
		oi->eh_frame_info.src_start_addr + vir_offset - section_content_offset,
		oi->rel_eh_frame_info.src_start_addr + vir_offset - section_content_offset,
		oi->note_gnu_stack_info.src_start_addr + vir_offset - section_content_offset);
			
	printf("===========================================================================================================================\n");
}

//===========================================================================
// pr_objinfo(struct objinfo_list *olist)
//===========================================================================
PUBLIC	void	pr_symtab(s8* filename, struct obj_info *dsti)
{
	//------------------------------------------------------------------
	// file open
	//------------------------------------------------------------------
	FILE *ft	= fopen(filename,"r");

	if(ft == NULL)
	{
		printf("error::can not open read file %s\n", filename);
		exit(1);
	}
	else
	{
		printf("open file for pr_symtab successfully(%s) !!!, addr(dsti)=0x%x \n\n", filename, dsti);
	}

	//------------------------------------------------------------------
	// read info from symtab
	//------------------------------------------------------------------
	s32 i, j;
	s32 x, y, z, length, len;

	len	= dsti->symtab_info.size;
	y	= len / SECTION_SIZE + 1;

	printf("================================================================================================================\n");
	printf("%10s |%10s| %10s| %10s| %10s| %10s| %10s| \n", "num","index","value","size","info","other","sec_index");
	printf("----------------------------------------------------------------------------------------------------------------\n");

	for(x=0; x<y; x++, len=len-SECTION_SIZE)
	{
		//------------------------------------------------------------------
		// read info from symtab_info into tmp_buf_s
		//------------------------------------------------------------------
		empty_buf(pr_buf_s, SECTION_SIZE);
		fseek(ft, (dsti->symtab_info.src_start_addr + x * SECTION_SIZE), SEEK_SET);

		if(y == 1)
		{
			length 	= dsti->symtab_info.size;
			
		}
		else if((x+1)<=y)
		{
			length 	= len;			
		}
		else
		{
			length	= SECTION_SIZE;					
		}

		fread(pr_buf_s, length, 1, ft);

		//------------------------------------------------------------------
		// process
		//------------------------------------------------------------------
		struct elf_symtab *p	= (struct elf_symtab*)pr_buf_s;

		s32 i,j,len;
		len	= sizeof(struct elf_symtab);
		j	= length / len;

		
		for(i=0; i<j; i++, p++)
		{
			printf(" %10x| %10x| %10x| %10x| %10x| %10x| %10x| \n", i,p->strtab_index, p->value, p->size, p->info, 
				p->other, p->section_index);
		}		
		
	}

	printf("=================================================================================================================\n");

	fclose(ft);
}

//===========================================================================
// pr_objinfo(struct objinfo_list *olist)
//===========================================================================
PUBLIC	void	pr_reltext(s8* filename, struct obj_info *dsti)
{
	//------------------------------------------------------------------
	// file open
	//------------------------------------------------------------------
	FILE *ft	= fopen(filename,"r");

	if(ft == NULL)
	{
		printf("error::can not open read file %s\n", filename);
		exit(1);
	}
	else
	{
		printf("open file for pr_reltext successfully(%s) !!!, addr(dsti)=0x%x \n\n", filename, dsti);
	}

	//------------------------------------------------------------------
	// read info from reltab
	//------------------------------------------------------------------
	s32 i, j;
	s32 x, y, z, length, len;

	len	= dsti->reltext_info.size;
	y	= len / SECTION_SIZE + 1;

	printf("===========================================================================================================================\n");
	printf("%10s |%10s| %10s| \n", "num", "offset","info");
	printf("---------------------------------------------------------------------------------------------------------------------------\n");

	for(x=0; x<y; x++, len=len-SECTION_SIZE)
	{
		//------------------------------------------------------------------
		// read info from reltext_info into tmp_buf_s
		//------------------------------------------------------------------
		empty_buf(pr_buf_s, SECTION_SIZE);
		fseek(ft, (dsti->reltext_info.src_start_addr + x * SECTION_SIZE), SEEK_SET);

		if(y == 1)
		{
			length 	= dsti->reltext_info.size;
			
		}
		else if((x+1)<=y)
		{
			length 	= len;			
		}
		else
		{
			length	= SECTION_SIZE;					
		}

		fread(pr_buf_s, length, 1, ft);

		//------------------------------------------------------------------
		// process
		//------------------------------------------------------------------
		struct rel32 *p	= (struct rel32*)pr_buf_s;

		s32 i,j,len;
		len	= sizeof(struct rel32);
		j	= length / len;

		for(i=0; i<j; i++, p++)
		{
			printf(" %10x|%10x| %10x| \n", i, p->offset, p->info);
		}		
		
	}

	printf("=================================================================================================================\n");

	fclose(ft);
}


//===========================================================================
// pr_objinfo(struct objinfo_list *olist)
//===========================================================================
PUBLIC	void	pr_shstrtab(s8* filename, struct obj_info *dsti)
{
	//------------------------------------------------------------------
	// file open
	//------------------------------------------------------------------
	FILE *ft	= fopen(filename,"r");

	if(ft == NULL)
	{
		printf("error::can not open read file %s\n", filename);
		exit(1);
	}
	else
	{
		printf("open file for pr_shstrtab successfully(%s) !!!, addr(dsti)=0x%x \n\n", filename, dsti);
	}

	//------------------------------------------------------------------
	// read info from shstrtab
	//------------------------------------------------------------------
	s32 i, j;
	s32 x, y, z, length, len;

	len	= dsti->shstrtab_info.size;
	y	= len / SECTION_SIZE + 1;

	printf("===========================================================================================================================\n");
	printf("%10s |%10s| %30s| \n", "start_addr", "num","name");
	printf("---------------------------------------------------------------------------------------------------------------------------\n");

	for(x=0; x<y; x++, len=len-SECTION_SIZE)
	{
		//------------------------------------------------------------------
		// read info from shstrtab_info into tmp_buf_s
		//------------------------------------------------------------------
		empty_buf(pr_buf_s, SECTION_SIZE);
		fseek(ft, (dsti->shstrtab_info.src_start_addr + x * SECTION_SIZE), SEEK_SET);

		if(y == 1)
		{
			length 	= dsti->shstrtab_info.size;
			
		}
		else if((x+1)<=y)
		{
			length 	= len;			
		}
		else
		{
			length	= SECTION_SIZE;					
		}

		fread(pr_buf_s, length, 1, ft);

		//------------------------------------------------------------------
		// process
		//------------------------------------------------------------------
		s8 *p	= pr_buf_s;

		s32 i,j,len,num;
		j	= length;
		
		for(i=0,num=0; i<j; i+=len, p+=len)
		{
			if(p)
			{
				len	= strlen(p) + 1;
				printf(" %10x|%10x| %30s| \n", i, num, p);
				num++;
			}
		}		
		
	}

	printf("=================================================================================================================\n");

	fclose(ft);
}


//===========================================================================
// pr_objinfo(struct objinfo_list *olist)
//===========================================================================
PUBLIC	void	pr_strtab(s8* filename, struct obj_info *dsti)
{
	//------------------------------------------------------------------
	// file open
	//------------------------------------------------------------------
	FILE *ft	= fopen(filename,"r");

	if(ft == NULL)
	{
		printf("error::can not open read file %s\n", filename);
		exit(1);
	}
	else
	{
		printf("open file for pr_strtab successfully(%s) !!!, addr(dsti)=0x%x \n\n", filename, dsti);
	}

	//------------------------------------------------------------------
	// read info from strtab
	//------------------------------------------------------------------
	s32 i, j;
	s32 x, y, z, length, len;

	len	= dsti->strtab_info.size;
	y	= len / SECTION_SIZE + 1;

	printf("===========================================================================================================================\n");
	printf("%10s |%10s| %30s| \n", "start_addr", "num","name");
	printf("---------------------------------------------------------------------------------------------------------------------------\n");

	for(x=0; x<y; x++, len=len-SECTION_SIZE)
	{
		//------------------------------------------------------------------
		// read info from strtab_info into tmp_buf_s
		//------------------------------------------------------------------
		empty_buf(pr_buf_s, SECTION_SIZE);
		fseek(ft, (dsti->strtab_info.src_start_addr + x * SECTION_SIZE), SEEK_SET);

		if(y == 1)
		{
			length 	= dsti->strtab_info.size;
			
		}
		else if((x+1)<=y)
		{
			length 	= len;			
		}
		else
		{
			length	= SECTION_SIZE;					
		}

		fread(pr_buf_s, length, 1, ft);

		//------------------------------------------------------------------
		// process
		//------------------------------------------------------------------
		s8 *p	= pr_buf_s;

		s32 i,j,len,num;
		j	= length;
		
		for(i=0,num=0; i<j; i+=len, p+=len)
		{
			if(p)
			{
				len	= strlen(p) + 1;
				printf(" %10x|%10x| %30s| \n", i, num, p);
				num++;
			}
		}		
		
	}

	printf("=================================================================================================================\n");

	fclose(ft);
}
