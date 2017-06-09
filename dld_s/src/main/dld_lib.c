//===========================================================================
// dld_lib.c
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

PRIVATE	s8 	dld_buf[TRUNK_SIZE];	//512
PRIVATE	s8	tmp_buf[TRUNK_SIZE];	//512

PRIVATE	s8 	section_tab[SECTION_NUM][20]	= {"",".text",".data",".bss",".rodata",".rel.text",".shstrtab",".symtab",".strtab",
							".comment", ".eh_frame", ".rel.eh_frame", ".note.GNU-stack"};
PRIVATE	s32	section_tab_index[SECTION_NUM]	= {0, 1, 7, 13, 18, 26, 36, 46, 54, 62, 71, 81, 95};

PRIVATE	struct section_header section_h[SECTION_NUM];

PRIVATE	s32	content_offset;

//===========================================================================
// read_obj(s8* filename, struct objinfo_list *oi_list)
//===========================================================================
PUBLIC	s32	read_obj(s8* filename, struct objinfo_list *oi_list)
{
	//------------------------------------------------------------------
	// declaration
	//------------------------------------------------------------------
	s32 i,j;
	s8 *p;

	//------------------------------------------------------------------
	// file open
	//------------------------------------------------------------------
	fr	= fopen(filename,"r");

	if(fr == NULL)
	{
		printf("error::can not open read file %s\n", filename);
		exit(1);
	}
	else
	{
		printf("open file %s successfully !!! \n\n", filename);
	}

	//------------------------------------------------------------------
	// elf info into dld_buf
	//------------------------------------------------------------------
	fseek(fr, 0, SEEK_SET);

	empty_buf(dld_buf, TRUNK_SIZE);
	
	fread(dld_buf, TRUNK_SIZE, 1, fr);

	struct elf_header *elfh	= (struct elf_header*)dld_buf;

	u32	section_header_offset		= elfh->section_header_offset;
	u16	section_header_size		= elfh->section_header_size;
	u16	section_header_num		= elfh->section_header_num;
	u16	section_header_strtab_index	= elfh->section_header_strtab_index;

	//------------------------------------------------------------------
	// read shstrtab into tmp_buf
	//------------------------------------------------------------------
	u32	section_header_strtab_offset	= section_header_offset + section_header_size * section_header_strtab_index;

	fseek(fr, section_header_strtab_offset, SEEK_SET);

	empty_buf(tmp_buf, TRUNK_SIZE);

	fread(tmp_buf, TRUNK_SIZE, 1, fr);

	struct section_header	*sech	= (struct section_header *)tmp_buf;

	u32 section_strtab_offset	= sech->offset;

	fseek(fr, section_strtab_offset, SEEK_SET);

	empty_buf(tmp_buf, TRUNK_SIZE);

	fread(tmp_buf, TRUNK_SIZE, 1, fr);

	//------------------------------------------------------------------
	// read each section info into struct obj_info
	//------------------------------------------------------------------
	struct obj_info	*oi	= malloc(sizeof(struct obj_info));

	strcopy(&(oi->filename), filename);
	oi->filename[strlen(filename)]	= NULL;

	fseek(fr, section_header_offset, SEEK_SET);
	
	empty_buf(dld_buf, TRUNK_SIZE);

	fread(dld_buf, TRUNK_SIZE, 1, fr);

	p = dld_buf;

	for(i=0; (i<TRUNK_SIZE) && (i<(section_header_num * section_header_size)); i+=SECTION_HEADER_SIZE, p+=SECTION_HEADER_SIZE)
	{
		struct section_header *sh	= (struct section_header*)p;

		//null
		if(strcmp((tmp_buf + sh->name), "") == TRUE)
		{
			oi->null_info.src_start_addr	= 0;
			oi->null_info.dst_start_addr	= 0;
			oi->null_info.size		= 0;
			oi->null_info.offset		= 0;
			oi->null_info.align_offset	= 0;
			continue;
		}

		//data
		if(strcmp((tmp_buf + sh->name), ".data") == TRUE)
		{
			oi->data_info.src_start_addr	= sh->offset;
			oi->data_info.dst_start_addr	= 0;
			oi->data_info.size		= sh->size;
			oi->data_info.offset		= 0;
			oi->data_info.align_offset	= 16 - (sh->size % 16);
			continue;
		}

		//text
		if(strcmp((tmp_buf + sh->name), ".text") == TRUE)
		{
			oi->text_info.src_start_addr	= sh->offset;
			oi->text_info.dst_start_addr	= 0;
			oi->text_info.size		= sh->size;
			oi->text_info.offset		= 0;
			oi->text_info.align_offset	= 16 - (sh->size % 16);
			continue;
		}

		//bss
		if(strcmp((tmp_buf + sh->name), ".bss") == TRUE)
		{
			oi->bss_info.src_start_addr	= sh->offset;
			oi->bss_info.dst_start_addr	= 0;
			oi->bss_info.size		= sh->size;
			oi->bss_info.offset		= 0;
			oi->bss_info.align_offset	= 16 - (sh->size % 16);
			continue;
		}

		//rodata
		if(strcmp((tmp_buf + sh->name), ".rodata") == TRUE)
		{
			oi->rodata_info.src_start_addr	= sh->offset;
			oi->rodata_info.dst_start_addr	= 0;
			oi->rodata_info.size		= sh->size;
			oi->rodata_info.offset		= 0;
			oi->rodata_info.align_offset	= 16 - (sh->size % 16);
			continue;
		}

		//reltext
		if(strcmp((tmp_buf + sh->name), ".rel.text") == TRUE)
		{
			oi->reltext_info.src_start_addr	= sh->offset;
			oi->reltext_info.dst_start_addr	= 0;
			oi->reltext_info.size		= sh->size;
			oi->reltext_info.offset		= 0;
			oi->reltext_info.align_offset	= 16 - (sh->size % 16);
			continue;
		}

		//shstrtab
		if(strcmp((tmp_buf + sh->name), ".shstrtab") == TRUE)
		{
			oi->shstrtab_info.src_start_addr= sh->offset;
			oi->shstrtab_info.dst_start_addr	= 0;
			oi->shstrtab_info.size		= sh->size;
			oi->shstrtab_info.offset		= 0;
			oi->shstrtab_info.align_offset	= 16 - (sh->size % 16);
			continue;
		}

		//symtab
		if(strcmp((tmp_buf + sh->name), ".symtab") == TRUE)
		{
			oi->symtab_info.src_start_addr	= sh->offset;
			oi->symtab_info.dst_start_addr	= 0;
			oi->symtab_info.size		= sh->size;
			oi->symtab_info.offset		= 0;
			oi->symtab_info.align_offset	= 16 - (sh->size % 16);
			continue;
		}

		//strtab
		if(strcmp((tmp_buf + sh->name), ".strtab") == TRUE)
		{
			oi->strtab_info.src_start_addr	= sh->offset;
			oi->strtab_info.dst_start_addr	= 0;
			oi->strtab_info.size		= sh->size;
			oi->strtab_info.offset		= 0;
			oi->strtab_info.align_offset	= 16 - (sh->size % 16);
			continue;
		}

		//eh_frame
		if(strcmp((tmp_buf + sh->name), ".eh_frame") == TRUE)
		{
			oi->eh_frame_info.src_start_addr	= sh->offset;
			oi->eh_frame_info.dst_start_addr	= 0;
			oi->eh_frame_info.size		= sh->size;
			oi->eh_frame_info.offset		= 0;
			oi->eh_frame_info.align_offset	= 16 - (sh->size % 16);
			continue;
		}

		//rel_eh_frame
		if(strcmp((tmp_buf + sh->name), ".rel.eh_frame") == TRUE)
		{
			oi->rel_eh_frame_info.src_start_addr	= sh->offset;
			oi->rel_eh_frame_info.dst_start_addr	= 0;
			oi->rel_eh_frame_info.size		= sh->size;
			oi->rel_eh_frame_info.offset		= 0;
			oi->rel_eh_frame_info.align_offset	= 16 - (sh->size % 16);
			continue;
		}

		//note_gnu_stack
		if(strcmp((tmp_buf + sh->name), ".note.GNU-stack") == TRUE)
		{
			oi->note_gnu_stack_info.src_start_addr	= sh->offset;
			oi->note_gnu_stack_info.dst_start_addr	= 0;
			oi->note_gnu_stack_info.size		= sh->size;
			oi->note_gnu_stack_info.offset		= 0;
			oi->note_gnu_stack_info.align_offset	= 16 - (sh->size % 16);
			continue;
		}

		//comment
		if(strcmp((tmp_buf + sh->name), ".comment") == TRUE)
		{
			oi->comment_info.src_start_addr	= sh->offset;
			oi->comment_info.dst_start_addr	= 0;
			oi->comment_info.size		= sh->size;
			oi->comment_info.offset		= 0;
			oi->comment_info.align_offset	= 16 - (sh->size % 16);
			continue;
		}		
	}

	struct objinfo_list *srclist	= objlist_build(oi);
	dld_add2objlist(srclist, oi_list);

	//------------------------------------------------------------------
	// file close
	//------------------------------------------------------------------
	fclose(fr);
}

//===========================================================================
// read_obj(s8* filename, struct objinfo_list *oi_list)
//===========================================================================
PUBLIC	s32	exe_obj(struct objinfo_list *src_list, struct obj_info *dsti)
{
	u32 addr[SECTION_NUM], size[SECTION_NUM], align_offset[SECTION_NUM];
	s32 i;
	struct objinfo_list *sl;
		
	//------------------------------------------------------------------
	// fill in the summary infomation 
	//------------------------------------------------------------------
	empty_buf(addr, (SECTION_NUM * 4));
	empty_buf(size, (SECTION_NUM * 4));
	empty_buf(align_offset, (SECTION_NUM * 4));

	sl	= src_list;

	i=1;
	for(; sl ; sl=sl->tail)
	{
		if(sl->oinfo)
		{
			size[0]	+= 0;
			size[1]	+= sl->oinfo->text_info.size;
			size[2]	+= sl->oinfo->data_info.size;		
			size[3]	+= sl->oinfo->bss_info.size;
			size[4]	+= sl->oinfo->rodata_info.size;
			size[5]	+= sl->oinfo->reltext_info.size;
			size[6]	= SECTION_SHSTRTAB_LEN;
			size[7]	+= sl->oinfo->symtab_info.size;
			size[8]	+= sl->oinfo->strtab_info.size;
			size[9]	+= sl->oinfo->comment_info.size;
			size[10]+= sl->oinfo->eh_frame_info.size;
			size[11]+= sl->oinfo->rel_eh_frame_info.size;
			size[12]+= sl->oinfo->note_gnu_stack_info.size;

			align_offset[0]	+= 0;
			align_offset[1]	+= sl->oinfo->text_info.align_offset;
			align_offset[2]	+= sl->oinfo->data_info.align_offset;		
			align_offset[3]	+= sl->oinfo->bss_info.align_offset;
			align_offset[4]	+= sl->oinfo->rodata_info.align_offset;
			align_offset[5]	+= sl->oinfo->reltext_info.align_offset;
			align_offset[6]	+= sl->oinfo->shstrtab_info.align_offset;			
			align_offset[7]	+= sl->oinfo->symtab_info.align_offset;
			align_offset[8]	+= sl->oinfo->strtab_info.align_offset;
			align_offset[9]	+= sl->oinfo->comment_info.align_offset;
			align_offset[10]+= sl->oinfo->eh_frame_info.align_offset;
			align_offset[11]+= sl->oinfo->rel_eh_frame_info.align_offset;
			align_offset[12]+= sl->oinfo->note_gnu_stack_info.align_offset;
		}
	}

	size[8]++;

	addr[0]	= section_content_offset;
	addr[1]	= addr[0] + size[0];	
	addr[2]	= addr[1] + size[1] + align_offset[1];
	addr[3]	= addr[2] + size[2];
	addr[4]	= addr[3] + size[3];
	addr[5]	= addr[4] + size[4];
	addr[6]	= addr[5] + size[5];
	addr[7]	= addr[6] + size[6];
	addr[8]	= addr[7] + size[7];
	addr[9]	= addr[8] + size[8];
	addr[10]= addr[9] + size[9];
	addr[11]= addr[10]+ size[10];
	addr[12]= addr[11]+ size[11];

	dsti->null_info.src_start_addr		= addr[0];
	dsti->text_info.src_start_addr		= addr[1];
	dsti->data_info.src_start_addr		= addr[2];	
	dsti->bss_info.src_start_addr		= addr[3];
	dsti->rodata_info.src_start_addr	= addr[4];
	dsti->reltext_info.src_start_addr	= addr[5];
	dsti->shstrtab_info.src_start_addr	= addr[6];
	dsti->symtab_info.src_start_addr	= addr[7];
	dsti->strtab_info.src_start_addr	= addr[8];
	dsti->comment_info.src_start_addr	= addr[9];
	dsti->eh_frame_info.src_start_addr	= addr[10];
	dsti->rel_eh_frame_info.src_start_addr	= addr[11];
	dsti->note_gnu_stack_info.src_start_addr= addr[12];

	dsti->null_info.size		= size[0];	
	dsti->text_info.size		= size[1] + align_offset[1];
	dsti->data_info.size		= size[2];	
	dsti->bss_info.size		= size[3];
	dsti->rodata_info.size		= size[4];
	dsti->reltext_info.size		= size[5];
	dsti->shstrtab_info.size	= size[6];
	dsti->symtab_info.size		= size[7];
	dsti->strtab_info.size		= size[8];
	dsti->comment_info.size		= size[9];
	dsti->eh_frame_info.size	= size[10];
	dsti->rel_eh_frame_info.size	= size[11];
	dsti->note_gnu_stack_info.size	= size[12];

	//------------------------------------------------------------------
	// recompute the address and size of each section within src_list 
	//	and output to dst_list
	//------------------------------------------------------------------
	empty_buf(addr, (SECTION_NUM * 4));
	empty_buf(size, (SECTION_NUM * 4));

	addr[0]	= dsti->null_info.src_start_addr;
	addr[1]	= dsti->text_info.src_start_addr;
	addr[2]	= dsti->data_info.src_start_addr;	
	addr[3]	= dsti->bss_info.src_start_addr;
	addr[4]	= dsti->rodata_info.src_start_addr;
	addr[5]	= dsti->reltext_info.src_start_addr;
	addr[6]	= dsti->shstrtab_info.src_start_addr;
	addr[7]	= dsti->symtab_info.src_start_addr;
	addr[8]	= dsti->strtab_info.src_start_addr;
	addr[9]	= dsti->comment_info.src_start_addr;
	addr[10]= dsti->eh_frame_info.src_start_addr;
	addr[11]= dsti->rel_eh_frame_info.src_start_addr;
	addr[12]= dsti->note_gnu_stack_info.src_start_addr;

	size[0]	= 0;
	size[1]	= 0;
	size[2]	= 0;
	size[3]	= 0;
	size[4]	= 0;
	size[5]	= 0;
	size[6]	= 0;
	size[7]	= 0;
	size[8]	= 0;
	size[9]	= 0;
	size[10]= 0;
	size[11]= 0;
	size[12]= 0;

	align_offset[0]	= 0;
	align_offset[1]	= 0;
	align_offset[2]	= 0;
	align_offset[3]	= 0;
	align_offset[4]	= 0;
	align_offset[5]	= 0;
	align_offset[6]	= 0;
	align_offset[7]	= 0;
	align_offset[8]	= 0;
	align_offset[9]	= 0;
	align_offset[10]= 0;
	align_offset[11]= 0;
	align_offset[12]= 0;

	sl	= src_list;
	i=1;
	for(i=0; sl ; sl=sl->tail)
	{
		if(sl->oinfo)
		{
			sl->oinfo->null_info.dst_start_addr		= addr[0];
			sl->oinfo->text_info.dst_start_addr		= addr[1];
			sl->oinfo->data_info.dst_start_addr		= addr[2];			
			sl->oinfo->bss_info.dst_start_addr		= addr[3];
			sl->oinfo->rodata_info.dst_start_addr		= addr[4];
			sl->oinfo->reltext_info.dst_start_addr		= addr[5];
			sl->oinfo->shstrtab_info.dst_start_addr		= addr[6];
			sl->oinfo->symtab_info.dst_start_addr		= addr[7];
			sl->oinfo->strtab_info.dst_start_addr		= addr[8];
			sl->oinfo->comment_info.dst_start_addr		= addr[9];
			sl->oinfo->eh_frame_info.dst_start_addr		= addr[10];
			sl->oinfo->rel_eh_frame_info.dst_start_addr	= addr[11];
			sl->oinfo->note_gnu_stack_info.dst_start_addr	= addr[12];
	
			sl->oinfo->null_info.offset		= size[0];			
			sl->oinfo->text_info.offset		= size[1] + align_offset[1];
			sl->oinfo->data_info.offset		= size[2];			
			sl->oinfo->bss_info.offset		= size[3];
			sl->oinfo->rodata_info.offset		= size[4];
			sl->oinfo->reltext_info.offset		= size[5];
			sl->oinfo->shstrtab_info.offset		= size[6];
			sl->oinfo->symtab_info.offset		= size[7];
			sl->oinfo->strtab_info.offset		= size[8];
			sl->oinfo->comment_info.offset		= size[9];
			sl->oinfo->eh_frame_info.offset		= size[10];
			sl->oinfo->rel_eh_frame_info.offset	= size[11];
			sl->oinfo->note_gnu_stack_info.offset	= size[12];

			size[0]	+= 0;
			size[1]	+= sl->oinfo->text_info.size;
			size[2]	+= sl->oinfo->data_info.size;			
			size[3]	+= sl->oinfo->bss_info.size;
			size[4]	+= sl->oinfo->rodata_info.size;
			size[5]	+= sl->oinfo->reltext_info.size;			
			size[6]	= 0;
			size[7]	+= sl->oinfo->symtab_info.size;
			size[8]	+= sl->oinfo->strtab_info.size;
			size[9]	+= sl->oinfo->comment_info.size;
			size[10]+= sl->oinfo->eh_frame_info.size;
			size[11]+= sl->oinfo->rel_eh_frame_info.size;
			size[12]+= sl->oinfo->note_gnu_stack_info.size;

			align_offset[0]	+= 0;
			align_offset[1]	+= sl->oinfo->text_info.align_offset;
			align_offset[2]	+= sl->oinfo->data_info.align_offset;			
			align_offset[3]	+= sl->oinfo->bss_info.align_offset;
			align_offset[4]	+= sl->oinfo->rodata_info.align_offset;
			align_offset[5]	+= sl->oinfo->reltext_info.align_offset;			
			align_offset[6]	+= sl->oinfo->shstrtab_info.align_offset;			
			align_offset[7]	+= sl->oinfo->symtab_info.align_offset;
			align_offset[8]	+= sl->oinfo->strtab_info.align_offset;
			align_offset[9]	+= sl->oinfo->comment_info.align_offset;
			align_offset[10]+= sl->oinfo->eh_frame_info.align_offset;
			align_offset[11]+= sl->oinfo->rel_eh_frame_info.align_offset;
			align_offset[12]+= sl->oinfo->note_gnu_stack_info.align_offset;

			addr[0]	+= 0;			
			addr[1]	+= sl->oinfo->text_info.size + sl->oinfo->text_info.align_offset;
			addr[2]	+= sl->oinfo->data_info.size;			
			addr[3]	+= sl->oinfo->bss_info.size;
			addr[4]	+= sl->oinfo->rodata_info.size;
			addr[5]	+= sl->oinfo->reltext_info.size;

			//addr[6]	+= sl->oinfo->shstrtab_info.size;

			addr[7]	+= sl->oinfo->symtab_info.size;
			addr[8]	+= sl->oinfo->strtab_info.size;
			addr[9]	+= sl->oinfo->comment_info.size;
			addr[10]+= sl->oinfo->eh_frame_info.size;
			addr[11]+= sl->oinfo->rel_eh_frame_info.size;
			addr[12]+= sl->oinfo->note_gnu_stack_info.size;	

			i++;					
		}
	}

	u32 m1	= dsti->text_info.size / PAGE_SIZE + 1;
	
	vir_data_offset	= vir_offset + m1 * PAGE_SIZE;	
	
	vir_data_offset	+= dsti->text_info.size;	
}

//===========================================================================
// output_obj(struct objinfo_list *src_list, struct objinfo_list *dst_list, struct obj_info *dsti)
//===========================================================================
PUBLIC	s32	output_obj(s8* output_file, struct objinfo_list *src_list,  struct obj_info *dsti)
{
	//------------------------------------------------------------------
	// declaration
	//------------------------------------------------------------------
	u32 file_size, mem_size, vir_addr, p_addr;

	//------------------------------------------------------------------
	// file open
	//------------------------------------------------------------------
	fw	= fopen(output_file,"w+");

	if(fw == NULL)
	{
		printf("error::can not open write file %s\n", output_file);
		exit(1);
	}

	//------------------------------------------------------------------
	// add elf header
	//------------------------------------------------------------------
	dld_add_elf_header(fw);		//0x8048000

	//------------------------------------------------------------------
	// add program header
	//------------------------------------------------------------------
	// (test)
	file_size 	= dsti->text_info.size;
	mem_size	= dsti->text_info.size;
	vir_addr	= vir_offset;
	p_addr		= vir_offset;
	dld_add_program_header(fw,  dsti->text_info.src_start_addr, vir_addr, p_addr, file_size, mem_size, 5, 1);		

	// (data)
	file_size 	= dsti->data_info.size;
	mem_size	= dsti->data_info.size;

	vir_addr	= vir_data_offset;
	p_addr		= vir_data_offset;

	dld_add_program_header(fw,  dsti->data_info.src_start_addr, vir_addr, p_addr,file_size, mem_size, 6, 1);		

	// (bss)
	file_size 	= dsti->bss_info.size;
	mem_size	= dsti->bss_info.size;
	vir_addr	= 0;
	p_addr		= 0;
	dld_add_program_header(fw,  0, 0, 0, file_size, mem_size, 7, 0x6474e551);	

	//------------------------------------------------------------------
	// add section header
	//------------------------------------------------------------------
	dld_add_section_header(fw);

	//------------------------------------------------------------------
	// add section content
	//------------------------------------------------------------------
	dld_add_section_content(fw, srcl);

	fclose(fw);
}

//===========================================================================
// PUBLIC	void	dld_add_elf_header(FILE *foutput)
//===========================================================================
PUBLIC	void	dld_add_elf_header(FILE *foutput)
{
	//==================================================================;
	//	add elf header
	//==================================================================;
	struct elf_header *elf_h = elf_header_build(vir_offset, section_header_offset, program_header_offset, 0, PROGRAM_HEADER_SIZE,
							PROGRAM_HEADER_NUM, ELF_TYPE_EXE);

	s8 *p= (s8*)elf_h;
	s32 i;
	for(i=0; i<ELF_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	file_offset	+= section_header_offset;
}

//===========================================================================
// PUBLIC	void	dld_add_program_header(FILE *foutput)
//===========================================================================
PUBLIC	void	dld_add_program_header(FILE *foutput, u32 p_offset, u32 v_addr, u32 p_addr, u32 p_file_size, u32 p_mem_size, u32 p_flag, u32 p_type)
{
	//==================================================================;
	//	add program header
	//==================================================================;
	struct program_header *proh;
	u32 type, f_offset, vir_addr, phy_addr, file_size, mem_size, flag, addr_align;
	s8* p;
	s32 i;
	
	printf("add program header(text)(file_offset=0x%x, vir_offset)\n",f_offset, vir_offset);
	
	type		= p_type;
	f_offset	= p_offset;
	vir_addr	= v_addr;
	phy_addr	= p_addr;
	file_size	= p_file_size;
	mem_size	= p_mem_size;
	flag		= p_flag;

	addr_align	= 0x1000;	

	proh	= program_header_build(type, f_offset, vir_addr, phy_addr, file_size, mem_size, flag, addr_align);

	p= (s8*)proh;
	for(i=0; i<PROGRAM_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	file_offset	+= PROGRAM_HEADER_SIZE;
}


//===========================================================================
// PUBLIC	void	dld_add_section_header(FILE *foutput)
//===========================================================================
PUBLIC	void	dld_add_section_header(FILE *foutput)
{
	s32	sec_name, sec_type, sec_flags, sec_addr, sec_offset, sec_size, sec_link, sec_info, sec_align, sec_entrysize;
	s32	text_size, data_size, bss_size, rodata_size, rel_size, shstrtab_size,symtab_size,strtab_size;
	s32	comment_size, eh_frame_size, rel_eh_frame_size, note_gnu_stack_size;
	struct section_header *sech;	
	s8 *p;
	s32 i,j;
	u32	total_size;

	//==================================================================;
	//	add section header(null)
	//==================================================================;

	printf("add section_null header(file_offset=0x%x)\n",file_offset);
	
	sec_name	= section_tab_index[SECTION_INDEX_NULL];
	sec_type	= SECTION_TYPE_NULL;
	sec_flags	= 0;
	sec_addr	= 0;
	sec_offset	= 0;
	sec_size	= 0;
	sec_link	= 0;
	sec_info	= 0;
	sec_align	= 0;
	sec_entrysize	= 0;

	sech	= section_header_build(sec_name, sec_type, sec_flags, sec_addr, sec_offset, sec_size, sec_link, sec_info, sec_align, sec_entrysize);

	p= (s8*)sech;
	for(i=0; i<SECTION_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	file_offset	+= SECTION_HEADER_SIZE;

	total_size	= 0;

	section_copy(&section_h[SECTION_INDEX_NULL], sech);

	//==================================================================;
	//	add section header(code)
	//==================================================================;

	printf("add section_text header(file_offset=0x%x)\n",file_offset);

	text_size	= dsti->text_info.size;

	sec_name	= section_tab_index[SECTION_INDEX_TEXT];
	sec_type	= SECTION_TYPE_PROGBITS;
	sec_flags	= SECTION_FLAGS_EXE | SECTION_FLAGS_ALLOC;
	sec_addr	= vir_offset;
	sec_offset	= dsti->text_info.src_start_addr;		//SECTION_DATA_START_ADDR + data_size;
	sec_size	= text_size;
	sec_link	= 0;
	sec_info	= 0;
	sec_align	= SECTION_ALIGN_TEXT;
	sec_entrysize	= 0;
	
	sech	= section_header_build(sec_name, sec_type, sec_flags, sec_addr, sec_offset, sec_size, sec_link, sec_info, sec_align, sec_entrysize);

	p= (s8*)sech;
	for(i=0; i<SECTION_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	file_offset	+= SECTION_HEADER_SIZE;

	total_size	+= text_size;

	section_copy(&section_h[SECTION_INDEX_TEXT], sech);

	//==================================================================;
	//	add section header(data)
	//==================================================================;

	printf("add section_data header(file_offset=0x%x)\n",file_offset);

	data_size	= dsti->data_info.size;

	sec_name	= section_tab_index[SECTION_INDEX_DATA];
	sec_type	= SECTION_TYPE_PROGBITS;
	sec_flags	= SECTION_FLAGS_WRITE | SECTION_FLAGS_ALLOC;
	sec_addr	= vir_data_offset;
	sec_offset	= dsti->data_info.src_start_addr;		//SECTION_DATA_START_ADDR
	sec_size	= data_size;
	sec_link	= 0;
	sec_info	= 0;
	sec_align	= SECTION_ALIGN_DATA;
	sec_entrysize	= 0;
	
	sech	= section_header_build(sec_name, sec_type, sec_flags, sec_addr, sec_offset, sec_size, sec_link, sec_info, sec_align, sec_entrysize);

	p= (s8*)sech;
	for(i=0; i<SECTION_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	file_offset	+= SECTION_HEADER_SIZE;

	total_size	+= data_size;

	section_copy(&section_h[SECTION_INDEX_DATA], sech);	

	//==================================================================;
	//	add section header(bss)
	//==================================================================;

	printf("add section_bss header(file_offset=0x%x)\n",file_offset);

	bss_size	= 0;

	sec_name	= section_tab_index[SECTION_INDEX_BSS];
	sec_type	= SECTION_TYPE_NOBITS;
	sec_flags	= SECTION_FLAGS_WRITE | SECTION_FLAGS_ALLOC;
	sec_addr	= vir_offset + total_size;
	sec_offset	= dsti->bss_info.src_start_addr;		//SECTION_DATA_START_ADDR + data_size + text_size;
	sec_size	= bss_size;
	sec_link	= 0;
	sec_info	= 0;
	sec_align	= SECTION_ALIGN_BSS;
	sec_entrysize	= 0;
	
	sech	= section_header_build(sec_name, sec_type, sec_flags, sec_addr, sec_offset, sec_size, sec_link, sec_info, sec_align, sec_entrysize);

	p= (s8*)sech;
	for(i=0; i<SECTION_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	file_offset	+= SECTION_HEADER_SIZE;

	total_size	+= bss_size;

	section_copy(&section_h[SECTION_INDEX_BSS], sech);

	//==================================================================;
	//	add section header(rodata)
	//==================================================================;

	printf("add section_rodata header(file_offset=0x%x)\n",file_offset);

	rodata_size	= dsti->rodata_info.size;

	sec_name	= section_tab_index[SECTION_INDEX_RODATA];
	sec_type	= SECTION_TYPE_PROGBITS;
	sec_flags	= SECTION_FLAGS_ALLOC;
	sec_addr	= vir_offset + total_size;
	sec_offset	= dsti->rodata_info.src_start_addr;		//SECTION_DATA_START_ADDR + data_size + text_size + bss_size;
	sec_size	= rodata_size;
	sec_link	= 0;
	sec_info	= 0;
	sec_align	= SECTION_ALIGN_RODATA;
	sec_entrysize	= 0;
	
	sech	= section_header_build(sec_name, sec_type, sec_flags, sec_addr, sec_offset, sec_size, sec_link, sec_info, sec_align, sec_entrysize);

	p= (s8*)sech;
	for(i=0; i<SECTION_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	file_offset	+= SECTION_HEADER_SIZE;

	total_size	+= rodata_size;

	section_copy(&section_h[SECTION_INDEX_RODATA], sech);

	//==================================================================;
	//	add section header(rel.text)
	//==================================================================;

	printf("add section_reltext header(file_offset=0x%x)\n",file_offset);

	rel_size	= dsti->reltext_info.size;

	sec_name	= section_tab_index[SECTION_INDEX_RELTEXT];
	sec_type	= SECTION_TYPE_REL;
	sec_flags	= 0;
	sec_addr	= vir_offset + total_size;
	sec_offset	= dsti->reltext_info.src_start_addr;		//SECTION_DATA_START_ADDR + data_size + text_size + bss_size + rodata_size;
	sec_size	= rel_size;
	sec_link	= SECTION_INDEX_SYMTAB;
	sec_info	= SECTION_INDEX_TEXT;
	sec_align	= SECTION_ALIGN_RELTEXT;
	sec_entrysize	= sizeof(struct rel32);
	
	sech	= section_header_build(sec_name, sec_type, sec_flags, sec_addr, sec_offset, sec_size, sec_link, sec_info, sec_align, sec_entrysize);

	p= (s8*)sech;
	for(i=0; i<SECTION_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	file_offset	+= SECTION_HEADER_SIZE;

	total_size	+= rel_size;

	section_copy(&section_h[SECTION_INDEX_RELTEXT], sech);

	//==================================================================;
	//	add section header(shstrtab)
	//==================================================================;

	printf("add section_shstrtab header(file_offset=0x%x)\n",file_offset);

	shstrtab_size	= SECTION_SHSTRTAB_LEN;

	sec_name	= section_tab_index[SECTION_INDEX_SHSTRTAB];
	sec_type	= SECTION_TYPE_STRTAB;
	sec_flags	= 0;
	sec_addr	= vir_offset + total_size;
	sec_offset	= dsti->shstrtab_info.src_start_addr;	//SECTION_DATA_START_ADDR + data_size + text_size + bss_size + rodata_size + rel_size;
	sec_size	= shstrtab_size;
	sec_link	= 0;
	sec_info	= 0;
	sec_align	= SECTION_ALIGN_SHSTRTAB;
	sec_entrysize	= 0;
	
	sech	= section_header_build(sec_name, sec_type, sec_flags, sec_addr, sec_offset, sec_size, sec_link, sec_info, sec_align, sec_entrysize);

	p= (s8*)sech;
	for(i=0; i<SECTION_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	file_offset	+= SECTION_HEADER_SIZE;

	total_size	+= shstrtab_size;

	section_copy(&section_h[SECTION_INDEX_SHSTRTAB], sech);

	//==================================================================;
	//	add section header(symtab)
	//==================================================================;

	printf("add section_symtab header(file_offset=0x%x)\n",file_offset);

	symtab_size	= dsti->symtab_info.size;

	sec_name	= section_tab_index[SECTION_INDEX_SYMTAB];
	sec_type	= SECTION_TYPE_SYMTAB;
	sec_flags	= 0;
	sec_addr	= vir_offset + total_size;
	sec_offset	= dsti->symtab_info.src_start_addr;//SECTION_DATA_START_ADDR+data_size+text_size+bss_size+ rodata_size + rel_size + shstrtab_size;
	sec_size	= symtab_size;
	sec_link	= SECTION_INDEX_STRTAB;
	sec_info	= SECTION_INDEX_STRTAB;
	sec_align	= SECTION_ALIGN_SYMTAB;
	sec_entrysize	= sizeof(struct elf_symtab);
	
	sech	= section_header_build(sec_name, sec_type, sec_flags, sec_addr, sec_offset, sec_size, sec_link, sec_info, sec_align, sec_entrysize);

	p= (s8*)sech;
	for(i=0; i<SECTION_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	file_offset	+= SECTION_HEADER_SIZE;

	total_size	+= symtab_size;

	section_copy(&section_h[SECTION_INDEX_SYMTAB], sech);

	//==================================================================;
	//	add section header(strtab)
	//==================================================================;

	printf("add section_strtab header(file_offset=0x%x, strtab_offset=0x%x)\n",file_offset, strtab_offset);

	strtab_size	= dsti->strtab_info.size;

	sec_name	= section_tab_index[SECTION_INDEX_STRTAB];
	sec_type	= SECTION_TYPE_STRTAB;
	sec_flags	= 0;
	sec_addr	= vir_offset + total_size; 
	sec_offset	= dsti->strtab_info.src_start_addr; //SECTION_DATA_START_ADDR+data_size+text_size+bss_size+rodata_size+rel_size+shstrtab_size+ symtab_size;
	sec_size	= strtab_size;
	sec_link	= 0;
	sec_info	= SECTION_INDEX_TEXT;
	sec_align	= SECTION_ALIGN_STRTAB;
	sec_entrysize	= 0;
	
	sech	= section_header_build(sec_name, sec_type, sec_flags, sec_addr, sec_offset, sec_size, sec_link, sec_info, sec_align, sec_entrysize);

	p= (s8*)sech;
	for(i=0; i<SECTION_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	file_offset	+= SECTION_HEADER_SIZE;

	total_size	+= strtab_size;

	section_copy(&section_h[SECTION_INDEX_STRTAB], sech);

	//==================================================================;
	//	add section header(comment)
	//==================================================================;

	printf("add section_comment header(file_offset=0x%x)\n",file_offset);

	comment_size	= dsti->comment_info.size;

	sec_name	= section_tab_index[SECTION_INDEX_COMMENT];
	sec_type	= SECTION_TYPE_PROGBITS;
	sec_flags	= 0x30;						// MS
	sec_addr	= vir_offset + total_size;
	sec_offset	= dsti->comment_info.src_start_addr;		//SECTION_COMMENT_START_ADDR
	sec_size	= comment_size;
	sec_link	= 0;
	sec_info	= 0;
	sec_align	= SECTION_ALIGN_COMMENT;
	sec_entrysize	= 1;
	
	sech	= section_header_build(sec_name, sec_type, sec_flags, sec_addr, sec_offset, sec_size, sec_link, sec_info, sec_align, sec_entrysize);

	p= (s8*)sech;
	for(i=0; i<SECTION_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	file_offset	+= SECTION_HEADER_SIZE;

	total_size	+= comment_size;

	section_copy(&section_h[SECTION_INDEX_COMMENT], sech);

	//==================================================================;
	//	add section header(eh_frame)
	//==================================================================;

	printf("add section_eh_frame header(file_offset=0x%x)\n",file_offset);

	eh_frame_size	= dsti->eh_frame_info.size;

	sec_name	= section_tab_index[SECTION_INDEX_EH_FRAME];
	sec_type	= SECTION_TYPE_PROGBITS;
	sec_flags	= SECTION_FLAGS_ALLOC;				
	sec_addr	= vir_offset + total_size;
	sec_offset	= dsti->eh_frame_info.src_start_addr;		//
	sec_size	= eh_frame_size;
	sec_link	= 0;
	sec_info	= 0;
	sec_align	= SECTION_ALIGN_EH_FRAME;
	sec_entrysize	= 1;
	
	sech	= section_header_build(sec_name, sec_type, sec_flags, sec_addr, sec_offset, sec_size, sec_link, sec_info, sec_align, sec_entrysize);

	p= (s8*)sech;
	for(i=0; i<SECTION_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	file_offset	+= SECTION_HEADER_SIZE;

	total_size	+= eh_frame_size;

	section_copy(&section_h[SECTION_INDEX_EH_FRAME], sech);

	//==================================================================;
	//	add section header(rel_eh_frame)
	//==================================================================;

	printf("add section_rel_eh_frame header(file_offset=0x%x)\n",file_offset);

	rel_eh_frame_size	= dsti->rel_eh_frame_info.size;

	sec_name	= section_tab_index[SECTION_INDEX_REL_EH_FRAME];
	sec_type	= SECTION_TYPE_REL;
	sec_flags	= 0;				
	sec_addr	= vir_offset + total_size;
	sec_offset	= dsti->rel_eh_frame_info.src_start_addr;		//
	sec_size	= rel_eh_frame_size;
	sec_link	= SECTION_INDEX_SYMTAB;
	sec_info	= SECTION_INDEX_TEXT;
	sec_align	= SECTION_ALIGN_RELTEXT;
	sec_entrysize	= sizeof(struct rel32);
	
	sech	= section_header_build(sec_name, sec_type, sec_flags, sec_addr, sec_offset, sec_size, sec_link, sec_info, sec_align, sec_entrysize);

	p= (s8*)sech;
	for(i=0; i<SECTION_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	file_offset	+= SECTION_HEADER_SIZE;

	total_size	+= rel_eh_frame_size;

	section_copy(&section_h[SECTION_INDEX_REL_EH_FRAME], sech);

	//==================================================================;
	//	add section header(note_gnu_stack)
	//==================================================================;

	printf("add section_note_gnu_stack header(file_offset=0x%x)\n",file_offset);

	note_gnu_stack_size	= dsti->note_gnu_stack_info.size;

	sec_name	= section_tab_index[SECTION_INDEX_NOTE_GNU_STACK];
	sec_type	= SECTION_TYPE_NOBITS;
	sec_flags	= SECTION_FLAGS_WRITE | SECTION_FLAGS_ALLOC;			
	sec_addr	= vir_offset + total_size;
	sec_offset	= dsti->note_gnu_stack_info.src_start_addr;		//
	sec_size	= note_gnu_stack_size;
	sec_link	= 0;
	sec_info	= 0;
	sec_align	= SECTION_ALIGN_BSS;
	sec_entrysize	= 1;
	
	sech	= section_header_build(sec_name, sec_type, sec_flags, sec_addr, sec_offset, sec_size, sec_link, sec_info, sec_align, sec_entrysize);

	p= (s8*)sech;
	for(i=0; i<SECTION_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	file_offset	+= SECTION_HEADER_SIZE;

	total_size	+= note_gnu_stack_size;

	section_copy(&section_h[SECTION_INDEX_NOTE_GNU_STACK], sech);
}

//===========================================================================
// PUBLIC	void	dld_add_section_content(FILE *foutput)
//===========================================================================
PUBLIC	void	dld_add_section_content(FILE *foutput, struct objinfo_list *src_list)
{
	struct objinfo_list *sl;
	s8 *src, *dst;
	s32 len, i,j, k, f_offset, len_1;
	u32 src_start_addr, dst_start_addr;
	s8 flg_shstrtab = FALSE;

	sl	= src_list;
	i=1;
	sum_size_symtab = 0;

	for(; sl ; sl=sl->tail)
	{
		if(sl->oinfo)
		{
			//------------------------------------------------------------------
			// file open
			//------------------------------------------------------------------
			fr	= fopen(sl->oinfo->filename,"r");

			if(fr == NULL)
			{
				printf("error::can not open read file %s\n", sl->oinfo->filename);
				exit(1);
			}
			else
			{
				printf("open file %s successfully\n", sl->oinfo->filename);
			}
			
			//-------------------------------------------------------------------;
			//	add section content(text)
			//-------------------------------------------------------------------;
			len	= sl->oinfo->text_info.size;
			f_offset= sl->oinfo->text_info.offset;	
		
			j	= len / TRUNK_SIZE + 1;
			k	= len % TRUNK_SIZE;

			for(i=0; i<j; i++, len=len-TRUNK_SIZE)
			{
				empty_buf(dld_buf, TRUNK_SIZE);

				src_start_addr	= (sl->oinfo->text_info.src_start_addr + i*TRUNK_SIZE);
				dst_start_addr	= (sl->oinfo->text_info.dst_start_addr + i*TRUNK_SIZE);

				fseek(fr, src_start_addr, SEEK_SET);

				fread(dld_buf, TRUNK_SIZE, 1, fr);

				fseek(foutput, dst_start_addr, SEEK_SET);

				if(j == 1)
				{
					len_1	= sl->oinfo->text_info.size;					
				}
				else if((i+1)==j)
				{
					len_1	= k;					
				}
				else
				{
					len_1	= TRUNK_SIZE;					
				}

				fwrite(dld_buf,len_1,1,foutput);
				
				align_16_file(foutput, (16 - sl->oinfo->text_info.align_offset));				
			}

			//-------------------------------------------------------------------;
			//	add section content(data)
			//-------------------------------------------------------------------;
			len	= sl->oinfo->data_info.size;
			f_offset= sl->oinfo->data_info.offset;	
		
			j	= len / TRUNK_SIZE + 1;
			k	= len % TRUNK_SIZE;

			for(i=0; i<j; i++, len=len-TRUNK_SIZE)
			{
				empty_buf(dld_buf, TRUNK_SIZE);
				
				fseek(fr, (sl->oinfo->data_info.src_start_addr + i*TRUNK_SIZE), SEEK_SET);

				fread(dld_buf, TRUNK_SIZE, 1, fr);

				fseek(foutput, (sl->oinfo->data_info.dst_start_addr + i*TRUNK_SIZE), SEEK_SET);

				if(j == 1)
				{
					fwrite(dld_buf,sl->oinfo->data_info.size,1,foutput);
				}
				else if((i+1)==j)
				{
					fwrite(dld_buf,k,1,foutput);
				}
				else
				{
					fwrite(dld_buf,TRUNK_SIZE,1,foutput);
				}
			}			

			//-------------------------------------------------------------------;
			//	add section content(bss)
			//-------------------------------------------------------------------;
			len	= sl->oinfo->bss_info.size;
			f_offset= sl->oinfo->bss_info.offset;	
		
			j	= len / TRUNK_SIZE + 1;
			k	= len % TRUNK_SIZE;

			for(i=0; i<j; i++, len=len-TRUNK_SIZE)
			{
				empty_buf(dld_buf, TRUNK_SIZE);

				fseek(fr, (sl->oinfo->bss_info.src_start_addr + i*TRUNK_SIZE), SEEK_SET);

				fread(dld_buf, TRUNK_SIZE, 1, fr);

				fseek(foutput, (sl->oinfo->bss_info.dst_start_addr + i*TRUNK_SIZE), SEEK_SET);

				if(j == 1)
				{
					fwrite(dld_buf,sl->oinfo->bss_info.size,1,foutput);
				}
				else if((i+1)==j)
				{
					fwrite(dld_buf,k,1,foutput);
				}
				else
				{
					fwrite(dld_buf,TRUNK_SIZE,1,foutput);
				}
			}

			//-------------------------------------------------------------------;
			//	add section content(rodata)
			//-------------------------------------------------------------------;
			len	= sl->oinfo->rodata_info.size;
			f_offset= sl->oinfo->rodata_info.offset;	
		
			j	= len / TRUNK_SIZE + 1;
			k	= len % TRUNK_SIZE;

			for(i=0; i<j; i++, len=len-TRUNK_SIZE)
			{
				empty_buf(dld_buf, TRUNK_SIZE);

				fseek(fr, (sl->oinfo->rodata_info.src_start_addr + i*TRUNK_SIZE), SEEK_SET);

				fread(dld_buf, TRUNK_SIZE, 1, fr);

				fseek(foutput, (sl->oinfo->rodata_info.dst_start_addr + i*TRUNK_SIZE), SEEK_SET);

				if(j == 1)
				{
					fwrite(dld_buf,sl->oinfo->rodata_info.size,1,foutput);
				}
				else if((i+1)==j)
				{
					fwrite(dld_buf,k,1,foutput);
				}
				else
				{
					fwrite(dld_buf,TRUNK_SIZE,1,foutput);
				}
			}

			//-------------------------------------------------------------------;
			//	add section content(reltext)
			//-------------------------------------------------------------------;
			len	= sl->oinfo->reltext_info.size;
			f_offset= sl->oinfo->reltext_info.offset;	
		
			j	= len / TRUNK_SIZE + 1;
			k	= len % TRUNK_SIZE;

			for(i=0; i<j; i++, len=len-TRUNK_SIZE)
			{
				empty_buf(dld_buf, TRUNK_SIZE);

				fseek(fr, (sl->oinfo->reltext_info.src_start_addr + i*TRUNK_SIZE), SEEK_SET);

				fread(dld_buf, TRUNK_SIZE, 1, fr);

				fseek(foutput, (sl->oinfo->reltext_info.dst_start_addr + i*TRUNK_SIZE), SEEK_SET);

				if(j == 1)
				{
					section_content_reltext_rel_process(dld_buf, sl->oinfo->reltext_info.size, sl->oinfo);

					fwrite(dld_buf,sl->oinfo->reltext_info.size,1,foutput);
				}
				else if((i+1)==j)
				{
					section_content_reltext_rel_process(dld_buf, len, sl->oinfo);

					fwrite(dld_buf,k,1,foutput);
				}
				else
				{
					section_content_reltext_rel_process(dld_buf, TRUNK_SIZE, sl->oinfo);

					fwrite(dld_buf,TRUNK_SIZE,1,foutput);
				}
			}

			//-------------------------------------------------------------------;
			//	add section content(shstrtab)
			//-------------------------------------------------------------------;
			
			if(!flg_shstrtab)
			{
				len	= sl->oinfo->shstrtab_info.size;
				f_offset= sl->oinfo->shstrtab_info.offset;	
		
				j	= len / TRUNK_SIZE + 1;
				k	= len % TRUNK_SIZE;

				for(i=0; i<j; i++, len=len-TRUNK_SIZE)
				{
					empty_buf(dld_buf, TRUNK_SIZE);

					fseek(fr, (sl->oinfo->shstrtab_info.src_start_addr + i*TRUNK_SIZE), SEEK_SET);

					fread(dld_buf, TRUNK_SIZE, 1, fr);

					fseek(foutput, (sl->oinfo->shstrtab_info.dst_start_addr + i*TRUNK_SIZE), SEEK_SET);

					if(j == 1)
					{
						fwrite(dld_buf,sl->oinfo->shstrtab_info.size,1,foutput);
					}
					else if((i+1)==j)
					{
						fwrite(dld_buf,k,1,foutput);
					}
					else
					{
						fwrite(dld_buf,TRUNK_SIZE,1,foutput);
					}
				}

				flg_shstrtab	= TRUE;
			}
			
			//-------------------------------------------------------------------;
			//	add section content(symtab)
			//-------------------------------------------------------------------;
			len	= sl->oinfo->symtab_info.size;	
			f_offset= sl->oinfo->symtab_info.dst_start_addr;
		
			j	= len / TRUNK_SIZE + 1;
			k	= len % TRUNK_SIZE;

			for(i=0; i<j; i++, len=len-TRUNK_SIZE)
			{
				empty_buf(dld_buf, TRUNK_SIZE);

				fseek(fr, (sl->oinfo->symtab_info.src_start_addr + i*TRUNK_SIZE), SEEK_SET);

				fread(dld_buf, TRUNK_SIZE, 1, fr);

				fseek(foutput, (sl->oinfo->symtab_info.dst_start_addr + i*TRUNK_SIZE), SEEK_SET);

				if(j == 1)
				{
					section_content_symbol_rel_process(dld_buf, sl->oinfo->symtab_info.size, sl->oinfo);

					fwrite(dld_buf,sl->oinfo->symtab_info.size,1,foutput);
				}
				else if((i+1)==j)
				{
					section_content_symbol_rel_process(dld_buf, len, sl->oinfo);

					fwrite(dld_buf,k,1,foutput);
				}
				else
				{
					section_content_symbol_rel_process(dld_buf, TRUNK_SIZE, sl->oinfo);

					fwrite(dld_buf,TRUNK_SIZE,1,foutput);
				}
			}

			sum_size_symtab	+= sl->oinfo->symtab_info.size;

			//-------------------------------------------------------------------;
			//	add section content(strtab)
			//-------------------------------------------------------------------;
			len	= sl->oinfo->strtab_info.size;
			f_offset= sl->oinfo->strtab_info.offset;	
		
			j	= len / TRUNK_SIZE + 1;
			k	= len % TRUNK_SIZE;

			for(i=0; i<j; i++, len=len-TRUNK_SIZE)
			{
				empty_buf(dld_buf, TRUNK_SIZE);

				fseek(fr, (sl->oinfo->strtab_info.src_start_addr + i*TRUNK_SIZE), SEEK_SET);

				fread(dld_buf, TRUNK_SIZE, 1, fr);

				fseek(foutput, (sl->oinfo->strtab_info.dst_start_addr + i*TRUNK_SIZE), SEEK_SET);

				if(j == 1)
				{
					fwrite(dld_buf,sl->oinfo->strtab_info.size,1,foutput);
				}
				else if((i+1)==j)
				{
					fwrite(dld_buf,k,1,foutput);
				}
				else
				{
					fwrite(dld_buf,TRUNK_SIZE,1,foutput);
				}
			}

			//-------------------------------------------------------------------;
			//	add section content(comment)
			//-------------------------------------------------------------------;
			len	= sl->oinfo->comment_info.size;
			f_offset= sl->oinfo->comment_info.offset;	
		
			j	= len / TRUNK_SIZE + 1;
			k	= len % TRUNK_SIZE;

			for(i=0; i<j; i++, len=len-TRUNK_SIZE)
			{
				empty_buf(dld_buf, TRUNK_SIZE);

				fseek(fr, (sl->oinfo->comment_info.src_start_addr + i*TRUNK_SIZE), SEEK_SET);

				fread(dld_buf, TRUNK_SIZE, 1, fr);

				fseek(foutput, (sl->oinfo->comment_info.dst_start_addr + i*TRUNK_SIZE), SEEK_SET);

				if(j == 1)
				{
					fwrite(dld_buf,sl->oinfo->comment_info.size,1,foutput);
				}
				else if((i+1)==j)
				{					
					fwrite(dld_buf,k,1,foutput);
				}
				else
				{
					fwrite(dld_buf,TRUNK_SIZE,1,foutput);
				}

			}

			//-------------------------------------------------------------------;
			//	add section content(eh_frame)
			//-------------------------------------------------------------------;
			len	= sl->oinfo->eh_frame_info.size;
			f_offset= sl->oinfo->eh_frame_info.offset;	
		
			j	= len / TRUNK_SIZE + 1;
			k	= len % TRUNK_SIZE;

			for(i=0; i<j; i++, len=len-TRUNK_SIZE)
			{
				empty_buf(dld_buf, TRUNK_SIZE);

				fseek(fr, (sl->oinfo->eh_frame_info.src_start_addr + i*TRUNK_SIZE), SEEK_SET);

				fread(dld_buf, TRUNK_SIZE, 1, fr);

				fseek(foutput, (sl->oinfo->eh_frame_info.dst_start_addr + i*TRUNK_SIZE), SEEK_SET);

				if(j == 1)
				{
					fwrite(dld_buf,sl->oinfo->eh_frame_info.size,1,foutput);
				}
				else if((i+1)==j)
				{					
					fwrite(dld_buf,k,1,foutput);
				}
				else
				{
					fwrite(dld_buf,TRUNK_SIZE,1,foutput);
				}

			}

			//-------------------------------------------------------------------;
			//	add section content(rel_eh_frame)
			//-------------------------------------------------------------------;
			len	= sl->oinfo->rel_eh_frame_info.size;
			f_offset= sl->oinfo->rel_eh_frame_info.offset;	
		
			j	= len / TRUNK_SIZE + 1;
			k	= len % TRUNK_SIZE;

			for(i=0; i<j; i++, len=len-TRUNK_SIZE)
			{
				empty_buf(dld_buf, TRUNK_SIZE);

				fseek(fr, (sl->oinfo->rel_eh_frame_info.src_start_addr + i*TRUNK_SIZE), SEEK_SET);

				fread(dld_buf, TRUNK_SIZE, 1, fr);

				fseek(foutput, (sl->oinfo->rel_eh_frame_info.dst_start_addr + i*TRUNK_SIZE), SEEK_SET);

				if(j == 1)
				{
					fwrite(dld_buf,sl->oinfo->rel_eh_frame_info.size,1,foutput);
				}
				else if((i+1)==j)
				{
					fwrite(dld_buf,k,1,foutput);
				}
				else
				{
					fwrite(dld_buf,TRUNK_SIZE,1,foutput);
				}				
			}

			//-------------------------------------------------------------------;
			//	add section content(note_gnu_stack)
			//-------------------------------------------------------------------;
			len	= sl->oinfo->note_gnu_stack_info.size;
			f_offset= sl->oinfo->note_gnu_stack_info.offset;	
		
			j	= len / TRUNK_SIZE + 1;
			k	= len % TRUNK_SIZE;

			for(i=0; i<j; i++, len=len-TRUNK_SIZE)
			{
				empty_buf(dld_buf, TRUNK_SIZE);

				fseek(fr, (sl->oinfo->note_gnu_stack_info.src_start_addr + i*TRUNK_SIZE), SEEK_SET);

				fread(dld_buf, TRUNK_SIZE, 1, fr);

				fseek(foutput, (sl->oinfo->note_gnu_stack_info.dst_start_addr + i*TRUNK_SIZE), SEEK_SET);

				if(j == 1)
				{
					fwrite(dld_buf,sl->oinfo->note_gnu_stack_info.size,1,foutput);
				}
				else if((i+1)==j)
				{
					fwrite(dld_buf,k,1,foutput);
				}
				else
				{
					fwrite(dld_buf,TRUNK_SIZE,1,foutput);
				}				
			}


			//------------------------------------------------------------------
			// file close
			//------------------------------------------------------------------
			fclose(fr);		
		}
	}
	
}


