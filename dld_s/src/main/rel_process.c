//===========================================================================
// rel_process.c
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

PRIVATE	s8 tmp_buf_s[TRUNK_SIZE];
PRIVATE s8 tmp_buf_b[TRUNK_SIZE];
PRIVATE s8 temp_buf[64];
//===========================================================================
// main
//===========================================================================
PUBLIC	void	section_content_symbol_rel_process(s8 *buf, u32 size, struct obj_info *oinfo)
{
	
	//------------------------------------------------------------------
	// inintial variables
	//------------------------------------------------------------------
	s32 len	= sizeof(struct elf_symtab);
	s32 i	= size / len;
	s32 j	= size % len;
	s32 k;
	s32 offset_base = 0;
	u16 section_index;
	struct elf_symtab * symb = (struct elf_symtab*)buf;

	if(j == 0)
	{
		for(k=0; k<i; k++, symb++)
		{
			struct elf_symtab * elf_s	= symb;

			switch((elf_s->info)&0xF)
			{	
				case ELF_NOTYPE:
					offset_base = (oinfo->text_info.dst_start_addr +vir_offset) -section_content_offset;			
					break;
				case ELF_FUNC:
					offset_base = (oinfo->text_info.dst_start_addr +vir_offset) -section_content_offset;			
					break;
				case ELF_OBJECT:
					offset_base = vir_data_offset;
				case ELF_SECTION:
					
				case ELF_FILE:
					
					break;
			}
			
			//check if _start
			if(chk_start(oinfo, elf_s) == TRUE)
			{
				offset_base = (oinfo->text_info.dst_start_addr +vir_offset) -section_content_offset;
			}

			elf_s->strtab_index	+= oinfo->strtab_info.offset;
			elf_s->value		+= offset_base;	
		}
	}
	
	
}


//===========================================================================
// main
//===========================================================================
PUBLIC	void	section_content_reltext_rel_process(s8 *buf, u32 size, struct obj_info *oinfo)
{
	
	//------------------------------------------------------------------
	// inintial variables
	//------------------------------------------------------------------
	
	u32 symtab_index	= sum_size_symtab / sizeof(struct elf_symtab);

	s32 len	= sizeof(struct rel32);
	s32 i	= size / len;
	s32 j	= size % len;
	s32 k;
	s32 offset_base = 0;

	struct rel32 * rel	= buf;

	if(j == 0)
	{
		for(k=0; k<i; k++, rel++)
		{
			rel->offset	+= oinfo->text_info.offset;

			u32 r_info	= (rel->info)>>8;			
			r_info		+= symtab_index;
			r_info		<<= 8;			
			rel->info	= r_info | ((rel->info) & 0xFF);
		} 
	}
	
	
}



//===========================================================================
// main
//===========================================================================
PUBLIC	void	do_rel(s8* filename, struct objinfo_list *src_list, struct obj_info *dsti)
{
	//------------------------------------------------------------------
	// file open
	//------------------------------------------------------------------
	FILE *ft	= fopen(filename,"r+");

	if(ft == NULL)
	{
		printf("error::can not open read file %s\n", filename);
		exit(1);
	}
	else
	{
		printf("open file for relocated process successfully(%s) !!! \n\n", filename);
	}

	//------------------------------------------------------------------
	// relocated
	//------------------------------------------------------------------
	s32 i, j;	
	

	//------------------------------------------------------------------
	// read info from reltab
	//------------------------------------------------------------------
	s32 x, y, z, length, len;

	len	= dsti->reltext_info.size;
	y	= len / TRUNK_SIZE + 1;

	for(x=0; x<y; x++, len=len-TRUNK_SIZE)
	{
		//------------------------------------------------------------------
		// read info from reltext_info into tmp_buf_s
		//------------------------------------------------------------------
		empty_buf(tmp_buf_s, TRUNK_SIZE);
		fseek(ft, (dsti->reltext_info.src_start_addr + x * TRUNK_SIZE), SEEK_SET);

		if(y == 1)
		{
			length 	= dsti->reltext_info.size;
			
		}
		else if((x+1)==y)
		{
			length 	= len % TRUNK_SIZE;			
		}
		else
		{
			length	= TRUNK_SIZE;					
		}

		fread(tmp_buf_s, length, 1, ft);

		//------------------------------------------------------------------
		// process
		//------------------------------------------------------------------
		struct rel32 *rel	= (struct rel32*)tmp_buf_s;

		j	= length / sizeof(struct rel32);

		for(i=0; i<j; i++, rel++)
		{
			//------------------------------------------------------------------
			// read info from reltab
			//------------------------------------------------------------------	
			u32	rel_info	= (rel->info) >> 8; 
			u32	rel_offset	= rel->offset;

			do_rel_upd(ft, rel_info, rel_offset, dsti);				
		}
	}	

	fclose(ft);	
}


//===========================================================================
// main
//===========================================================================
PUBLIC	void	do_upd_symtab(s8* filename, struct objinfo_list *src_list, struct obj_info *dsti)
{
	//------------------------------------------------------------------
	// file open
	//------------------------------------------------------------------
	FILE *ft	= fopen(filename,"r+");

	if(ft == NULL)
	{
		printf("error::can not open read file %s\n", filename);
		exit(1);
	}
	else
	{
		printf("open file for relocated process successfully(%s) !!! \n\n", filename);
	}

	//------------------------------------------------------------------
	// relocated
	//------------------------------------------------------------------
	s32 i, j;	
	

	//------------------------------------------------------------------
	// read info from symtab
	//------------------------------------------------------------------
	s32 x, y, z, length, len;

	len	= dsti->symtab_info.size;
	y	= len / TRUNK_SIZE + 1;

	for(x=0; x<y; x++, len=len-TRUNK_SIZE)
	{
		//------------------------------------------------------------------
		// read info from symtab_info into tmp_buf_s
		//------------------------------------------------------------------
		empty_buf(tmp_buf_s, TRUNK_SIZE);
		fseek(ft, (dsti->symtab_info.src_start_addr + x * TRUNK_SIZE), SEEK_SET);

		if(y == 1)
		{
			length 	= dsti->symtab_info.size;
			
		}
		else if((x+1)==y)
		{
			length 	= len % TRUNK_SIZE;			
		}
		else
		{
			length	= TRUNK_SIZE;					
		}

		fread(tmp_buf_s, length, 1, ft);

		//------------------------------------------------------------------
		// process
		//------------------------------------------------------------------
		struct elf_symtab *symb	= (struct elf_symtab*)tmp_buf_s;

		j	= length / sizeof(struct elf_symtab);

		for(i=0; i<j; i++, symb++)
		{
			struct elf_symtab * elf_s	= (struct elf_symtab*)symb;

			if((((elf_s->info>>4)&0xF) == SCOPE_GLOBAL) && (elf_s->section_index != SECTION_INDEX_NULL))
			{
				u32	val		= elf_s->value;
				u32	src_addr	= dsti->strtab_info.src_start_addr + elf_s->strtab_index;
				u16	section_index	= elf_s->section_index;
				
				//get src string
				empty_buf(temp_buf, 64);	
				fseek(ft, src_addr, SEEK_SET);
				fread(temp_buf, 64, 1, ft);

				if(strcmp(g_entry.label, temp_buf) == TRUE)
				{
					g_entry.addr	= val;
				}

				//get offset list from strtab
				struct offset_list *ol	= malloc(sizeof(struct offset_list));
				ol->offset	= 0;
				ol->head	= NULL;
				ol->tail	= NULL;
				chk_strtab(temp_buf, dsti, ft, ol, elf_s->strtab_index);

				chk_symtab(ol, dsti, ft, section_index, val);			
			}	
		}		
	}	

	fclose(ft);	
}


//===========================================================================
// main
//===========================================================================
PUBLIC	void	do_upd_elfstart(s8* filename, struct objinfo_list *src_list, struct obj_info *dsti)
{
	//------------------------------------------------------------------
	// file open
	//------------------------------------------------------------------
	FILE *ft	= fopen(filename,"r+");

	if(ft == NULL)
	{
		printf("error::can not open read file %s\n", filename);
		exit(1);
	}
	else
	{
		printf("open file for relocated process successfully(%s) !!! \n\n", filename);
	}

	//------------------------------------------------------------------
	// read info from symtab
	//------------------------------------------------------------------
	s32 x, y, z, length, len;

	len	= TRUNK_SIZE;
	
	//------------------------------------------------------------------
	// read info from symtab_info into tmp_buf_s
	//------------------------------------------------------------------
	empty_buf(tmp_buf_s, TRUNK_SIZE);
	fseek(ft, elf_header_offset, SEEK_SET);
	fread(tmp_buf_s, TRUNK_SIZE, 1, ft);

	//------------------------------------------------------------------
	// process
	//------------------------------------------------------------------
	struct elf_header *elfh	= (struct elf_header*)tmp_buf_s;

	elfh->entry	= g_entry.addr;

	//------------------------------------------------------------------
	// update ELF file
	//------------------------------------------------------------------
	fseek(ft, elf_header_offset, SEEK_SET);
	fwrite(tmp_buf_s, TRUNK_SIZE , 1, ft);		

	fclose(ft);	
}


//===========================================================================
// main
//===========================================================================
PUBLIC	struct offset_list * chk_strtab(s8 *src, struct obj_info *dsti, FILE *ft, struct offset_list *olist, u32 index)
{
	//------------------------------------------------------------------
	// read info from strtab
	//------------------------------------------------------------------
	s32 x, y, z, length, len;

	len	= dsti->strtab_info.size;
	y	= len / TRUNK_SIZE + 1;

	for(x=0; x<y; x++)
	{
		//------------------------------------------------------------------
		// read info from symtab_info into tmp_buf_s
		//------------------------------------------------------------------
		empty_buf(tmp_buf_b, TRUNK_SIZE);
		fseek(ft, (dsti->strtab_info.src_start_addr + x * TRUNK_SIZE), SEEK_SET);

		if(y == 1)
		{
			length 	= dsti->strtab_info.size;
		}
		else if((x+1)==y)
		{
			length 	= len % TRUNK_SIZE;		
		}
		else
		{
			length	= TRUNK_SIZE;					
		}

		fread(tmp_buf_b, length, 1, ft);

		s8 *p = tmp_buf_b;
		s32 i,j,len_1,k;
		j	= length;
		
		for(i=0,k=0, len_1=0; (i<j); i+=len_1, p+=len_1, k++)
		{
			if(p)
			{
				if(i == index)
				{
					continue;
				}

				if(strcmp(src, p) == TRUE)
				{
					struct offset_list *	offlist = offsetlist_build(i);
					dld_add2offsetlist(offlist, olist);					
				}

				len_1	= strlen(p) + 1;				
			}
			else
			{
				len_1 = 1;
			}
		}
	}

	return olist;
}


//===========================================================================
// do_rel_upd
//===========================================================================
PUBLIC	void	do_rel_upd(FILE *ft, u32 rel_info, u32 rel_offset, struct obj_info *dsti)
{
	//------------------------------------------------------------------
	// relocated
	//------------------------------------------------------------------
	s32 i, j, k;	
	

	//------------------------------------------------------------------
	// read info from reltab
	//------------------------------------------------------------------
	s32 x, y, z, length, len;

	len	= sizeof(struct elf_symtab);
	i	= ((rel_info+1) * len) / TRUNK_SIZE;
	j	= ((rel_info+1) * len) % TRUNK_SIZE;
	k	= j / len;

	empty_buf(tmp_buf_b, TRUNK_SIZE);
	fseek(ft, (dsti->symtab_info.src_start_addr + i * TRUNK_SIZE), SEEK_SET);
	fread(tmp_buf_b, TRUNK_SIZE, 1, ft);

	struct elf_symtab *p	= (struct elf_symtab *)tmp_buf_b;
	p	+= (k-1);

	u32	new_value;
	u32 update_offset;

	switch((p->info) & 0xF)
	{
		case ELF_NOTYPE:
			new_value	= p->value - (rel_offset + 4) - vir_offset;
			update_offset	= dsti->text_info.src_start_addr + rel_offset;			
			break;
		case ELF_FUNC:
			new_value	= p->value - (rel_offset + 4) - vir_offset;
			update_offset	= dsti->text_info.src_start_addr + rel_offset;
			break;
		case ELF_OBJECT:
			new_value	= p->value;			
			update_offset	= dsti->text_info.src_start_addr + rel_offset;
			break;
	}

	//------------------------------------------------------------------
	// update
	//------------------------------------------------------------------
	fseek(ft, update_offset , SEEK_SET);	

	fwrite(&new_value, 4 , 1, ft);	
}

//===========================================================================
// chk_start
//===========================================================================
PUBLIC	s8 chk_start(struct obj_info *oinfo, struct elf_symtab * elf_s)
{
	//------------------------------------------------------------------
	// file open
	//------------------------------------------------------------------
	FILE *ft	= fopen(oinfo->filename,"r+");

	if(ft == NULL)
	{
		printf("error::can not open read file %s\n", oinfo->filename);
		exit(1);
	}
	else
	{
		printf("open file for relocated process successfully(%s) !!! \n\n", oinfo->filename);
	}

	//------------------------------------------------------------------
	// relocated
	//------------------------------------------------------------------
	s32 i, j, k;	
	
	s32 x, y, z, length, len;

	i	= elf_s->strtab_index / TRUNK_SIZE;
	j	= elf_s->strtab_index % TRUNK_SIZE;
	
	empty_buf(tmp_buf_s, TRUNK_SIZE);
	fseek(ft, (oinfo->strtab_info.src_start_addr + i * TRUNK_SIZE), SEEK_SET);
	fread(tmp_buf_s, TRUNK_SIZE, 1, ft);

	s8 *p	= tmp_buf_s;
	p	+= j;

	if(strcmp(p, g_entry.label) == TRUE)
	{
		printf("chk_start::true, p=%s, g=%s!!!\n\n", p, g_entry.label);

		fclose(ft);
		return TRUE;
	}
	else
	{
		printf("chk_start::false, p=%s, g=%s!!!\n\n", p, g_entry.label);

		fclose(ft);
		return FALSE;
	}
}


//===========================================================================
// main
//===========================================================================
PUBLIC	void chk_symtab(struct offset_list *ol, struct obj_info *dsti, FILE *ft, u16 section_index, u32 val)
{
	//------------------------------------------------------------------
	// read info from symtab
	//------------------------------------------------------------------
	s32 x, y, z, length, len;

	len	= dsti->symtab_info.size;
	y	= len / TRUNK_SIZE + 1;

	for(x=0; x<y; x++)
	{
		//------------------------------------------------------------------
		// read info from symtab_info into tmp_buf_b
		//------------------------------------------------------------------
		empty_buf(tmp_buf_b, TRUNK_SIZE);
		fseek(ft, (dsti->symtab_info.src_start_addr + x * TRUNK_SIZE), SEEK_SET);

		if(y == 1)
		{
			length 	= dsti->symtab_info.size;
		}
		else if((x+1)==y)
		{
			length 	= len % TRUNK_SIZE;		
		}
		else
		{
			length	= TRUNK_SIZE;					
		}

		fread(tmp_buf_b, length, 1, ft);

		s32 i,j,k;
		j	= length;
		
		u32	x_1;
		struct elf_symtab *p	= (struct elf_symtab*)tmp_buf_b;
		s32	len_1		= length / sizeof(struct elf_symtab);
				
		for(x_1=0; x_1<len_1; x_1++, p++)
		{
			struct offset_list *olist = ol;
			for(olist=olist->tail; olist; olist=olist->tail)
			{
				if(olist->offset == p->strtab_index)
				{
					p->value	= val;					
					p->section_index= section_index;
				}
			}
		}

		fseek(ft, (dsti->symtab_info.src_start_addr + x * TRUNK_SIZE), SEEK_SET);
		fwrite(tmp_buf_b, length , 1, ft);
	}
}
