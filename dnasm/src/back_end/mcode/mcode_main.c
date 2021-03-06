//===========================================================================
// mcode_main.c
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

PRIVATE	void	pr_mcode_symbol(FILE *foutput);
PRIVATE	void	pr_mcode_elf_header(FILE *foutput);
PRIVATE	void	pr_mcode_section_header(FILE *foutput);
PRIVATE	void	pr_mcode_section_content(FILE *foutput);

PRIVATE	s32	file_offset, obj_offset;
PRIVATE	s32	content_offset;

PRIVATE	s8 	section_tab[SECTION_NUM][20]	= {"",".text",".data",".bss",".rodata",".rel.text",".shstrtab",".symtab",".strtab",
							".comment", ".eh_frame", ".rel.eh_frame", ".note.GNU-stack"};
PRIVATE	s32	section_tab_index[SECTION_NUM]	= {0, 1, 7, 13, 18, 26, 36, 46, 54, 62, 71, 81, 95};

PRIVATE	struct section_header section_h[SECTION_NUM];

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	mcode_main(s8 *src_filename)
{
	printf("==================================================================\n");
	printf("	machine code main\n");
	printf("==================================================================\n");

	s8 output_file[INS_LEN];
	s32 i;
	for(i=0; (i<INS_LEN)&&(src_filename); i++, src_filename++)
	{
		if(*(src_filename) != '.')
		{
			output_file[i]	= *src_filename;
		}
		else
		{
			break;
		}
	}

	*(output_file+i+0)	= '.';
	*(output_file+i+1)	= 'o';
	*(output_file+i+2)	= NULL;
	
	FILE *fp	= fopen(output_file,"w");

	if(fp == NULL)
	{
		printf("error::can not open write file %s\n", output_file);
		exit(1);
	}

	file_offset	= 0;
	content_offset	= 0;

	obj_offset	= SECTION_DATA_START_ADDR;	//for content in header

	ins_data_offset	= 0;

	//for symtab
	esyml		= malloc(sizeof(struct elfsymtab_list));

	//for strtab
	strl		= malloc(sizeof(struct strtab_list));

	//for data tab
	dbl		= malloc(sizeof(struct dbtab_list));

	pr_mcode_symbol(fp);

	pr_mcode_title(fp);

	pr_mcode_content(fp);

	fclose(fp);
}

//===========================================================================
// pr_mcode_symbol(FILE *foutput)
//===========================================================================
PRIVATE	void	pr_mcode_symbol(FILE *foutput)
{
	printf("==================================================================\n");
	printf("	symbol list:\n");
	printf("==================================================================\n");

	struct symbol *p;
	s8 i,j,num;
	s32 len;
	
	num		= 1;	//for sdbtab[num]
	strtab_offset 	= 1;
	symtab_offset	= 0;

	for(i=0; i<SYMTBL_SIZE; i++)
	{
		for(p=(*(p_symtbl+i)).tail; p!=NULL; p=p->tail)
		{
			if(p->flag != FLAG_SYM)
			{
				struct elf_symtab *esym	= malloc(sizeof(struct elf_symtab));
				struct strtab	  *str	= malloc(sizeof(struct strtab));

				esym->strtab_index	= strtab_offset;				
				esym->value		= p->val_i_1;
				esym->size		= p->len;
				esym->other		= 0;

				len	= strlen(p->name);
				strcopy(&(str->str), p->name);
				str->str[len]	= NULL;

				strtab_offset	+= (len + 1);
				symtab_offset	+= sizeof(struct elf_symtab);

				switch(p->flag)
				{
					case FLAG_FILE:
						esym->info		= (SCOPE_LOCAL<<4) | ELF_FILE;					
						esym->section_index	= SHN_ABS;
									
						break;
					case FLAG_TEXT:
						esym->info		= (SCOPE_LOCAL<<4) | ELF_NOTYPE;					
						esym->section_index	= SECTION_INDEX_TEXT;						
						break;
					case FLAG_GLOBAL:
						esym->info		= (SCOPE_GLOBAL<<4) | ELF_NOTYPE;					
						esym->section_index	= SECTION_INDEX_TEXT;						
						break;
					case FLAG_DATA:
						esym->info		= (SCOPE_LOCAL<<4) | ELF_OBJECT;					
						esym->section_index	= SECTION_INDEX_DATA;

						//for data table
						struct dbtab	*db	= malloc(sizeof(struct dbtab));
						db->val			= p->val_i;

						//add to data list
						struct dbtab_list *dblist	= dbtablist_build(db);
						elf_add2dblist(dblist, dbl);
						
						esym->value		= ins_data_offset;

						ins_data_offset		+= p->len;					
						break;
					case FLAG_EXTERN:
						esym->info		= (SCOPE_GLOBAL<<4) | ELF_NOTYPE;					
						esym->section_index	= 0;						
						break;
					default:
						break;
				}

				//add to symtab list
				struct elfsymtab_list	*esymlist	= elfsymtablist_build(esym);
				elf_add2symlist(esymlist, esyml);
				
				//add to strlist
				struct strtab_list	*strlist	= strtablist_build(str);
				elf_add2strlist(strlist, strl);

				//for index
				num++;				
			}						
		}
	}
	printf("\n\n");
}

//===========================================================================
// PUBLIC	void	pr_mcode_title(FILE *foutput, u32 text_size, u32 data_size)
//===========================================================================
PUBLIC	void	pr_mcode_title(FILE *foutput)
{
	pr_mcode_elf_header(foutput);
	pr_mcode_section_header(foutput);
}

//===========================================================================
// PUBLIC	void	pr_mcode_title(FILE *foutput, u32 text_size, u32 data_size)
//===========================================================================
PRIVATE	void	pr_mcode_elf_header(FILE *foutput)
{
	//==================================================================;
	//	add elf header
	//==================================================================;

	printf("add elf header(file_offset=0x%x)\n",file_offset);
	
	struct elf_header *elf_h = elf_header_build(0, 0x40, 0, 0, 0, 0);

	s8 *p= (s8*)elf_h;
	s32 i;
	for(i=0; i<ELF_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	//align 16 bytes
	s8 j;
	for(j=0; i<0x40; i++)
	{
		fwrite(&j,sizeof(char),1,foutput);
	}

	file_offset	+= 0x40;
}

//===========================================================================
// PUBLIC	void	pr_mcode_title(FILE *foutput, u32 text_size, u32 data_size)
//===========================================================================
PRIVATE	void	pr_mcode_section_header(FILE *foutput)
{
	s32	sec_name, sec_type, sec_flags, sec_addr, sec_offset, sec_size, sec_link, sec_info, sec_align, sec_entrysize;
	s32	text_size, data_size, bss_size, rodata_size, rel_size, shstrtab_size,symtab_size,strtab_size;
	s32	comment_size, eh_frame_size, rel_eh_frame_size, note_gnu_stack_size;
	struct section_header *sech;	
	s8 *p;
	s32 i,j;

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

	section_copy(&section_h[SECTION_INDEX_NULL], sech);

	//==================================================================;
	//	add section header(code)
	//==================================================================;

	printf("add section_text header(file_offset=0x%x)\n",file_offset);

	text_size	= ins_code_offset;

	sec_name	= section_tab_index[SECTION_INDEX_TEXT];
	sec_type	= SECTION_TYPE_PROGBITS;
	sec_flags	= SECTION_FLAGS_EXE | SECTION_FLAGS_ALLOC;
	sec_addr	= 0;
	sec_offset	= obj_offset;		//SECTION_DATA_START_ADDR + data_size;
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

	section_copy(&section_h[SECTION_INDEX_TEXT], sech);

	obj_offset	= ((obj_offset + text_size) / 16 + 1) * 16;	

	//==================================================================;
	//	add section header(data)
	//==================================================================;

	printf("add section_data header(file_offset=0x%x)\n",file_offset);

	data_size	= ins_data_offset;

	sec_name	= section_tab_index[SECTION_INDEX_DATA];
	sec_type	= SECTION_TYPE_PROGBITS;
	sec_flags	= SECTION_FLAGS_WRITE | SECTION_FLAGS_ALLOC;
	sec_addr	= 0;
	sec_offset	= obj_offset;		//SECTION_DATA_START_ADDR
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

	section_copy(&section_h[SECTION_INDEX_DATA], sech);
	
	obj_offset	= ((obj_offset + data_size) / 16 + 1) * 16;

	//==================================================================;
	//	add section header(bss)
	//==================================================================;

	printf("add section_bss header(file_offset=0x%x)\n",file_offset);

	bss_size	= 0;

	sec_name	= section_tab_index[SECTION_INDEX_BSS];
	sec_type	= SECTION_TYPE_NOBITS;
	sec_flags	= SECTION_FLAGS_WRITE | SECTION_FLAGS_ALLOC;
	sec_addr	= 0;
	sec_offset	= obj_offset;		//SECTION_DATA_START_ADDR + data_size + text_size;
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

	section_copy(&section_h[SECTION_INDEX_BSS], sech);
	
	obj_offset	= ((obj_offset + bss_size) / 16 + 1) * 16;
	
	//==================================================================;
	//	add section header(rodata)
	//==================================================================;

	printf("add section_rodata header(file_offset=0x%x)\n",file_offset);

	rodata_size	= 0;

	sec_name	= section_tab_index[SECTION_INDEX_RODATA];
	sec_type	= SECTION_TYPE_PROGBITS;
	sec_flags	= SECTION_FLAGS_ALLOC;
	sec_addr	= 0;
	sec_offset	= obj_offset;		//SECTION_DATA_START_ADDR + data_size + text_size + bss_size;
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

	section_copy(&section_h[SECTION_INDEX_RODATA], sech);
	
	obj_offset	= ((obj_offset + rodata_size) / 16 + 1) * 16;
	
	//==================================================================;
	//	add section header(rel.text)
	//==================================================================;

	printf("add section_reltext header(file_offset=0x%x)\n",file_offset);

	rel_size	= reltab_offset;

	sec_name	= section_tab_index[SECTION_INDEX_RELTEXT];
	sec_type	= SECTION_TYPE_REL;
	sec_flags	= 0;
	sec_addr	= 0;
	sec_offset	= obj_offset;		//SECTION_DATA_START_ADDR + data_size + text_size + bss_size + rodata_size;
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

	section_copy(&section_h[SECTION_INDEX_RELTEXT], sech);
	
	obj_offset	= ((obj_offset + rel_size) / 16 + 1) * 16;
	
	//==================================================================;
	//	add section header(shstrtab)
	//==================================================================;

	printf("add section_shstrtab header(file_offset=0x%x)\n",file_offset);

	shstrtab_size	= SECTION_SHSTRTAB_LEN;

	sec_name	= section_tab_index[SECTION_INDEX_SHSTRTAB];
	sec_type	= SECTION_TYPE_STRTAB;
	sec_flags	= 0;
	sec_addr	= 0;
	sec_offset	= obj_offset;		//SECTION_DATA_START_ADDR + data_size + text_size + bss_size + rodata_size + rel_size;
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

	section_copy(&section_h[SECTION_INDEX_SHSTRTAB], sech);
	
	obj_offset	= ((obj_offset + shstrtab_size) / 16 + 1) * 16;
	
	//==================================================================;
	//	add section header(symtab)
	//==================================================================;

	printf("add section_symtab header(file_offset=0x%x)\n",file_offset);

	symtab_size	= symtab_offset + 16;

	sec_name	= section_tab_index[SECTION_INDEX_SYMTAB];
	sec_type	= SECTION_TYPE_SYMTAB;
	sec_flags	= 0;
	sec_addr	= 0;
	sec_offset	= obj_offset;		//SECTION_DATA_START_ADDR + data_size + text_size + bss_size + rodata_size + rel_size + shstrtab_size;
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

	section_copy(&section_h[SECTION_INDEX_SYMTAB], sech);
	
	obj_offset	= ((obj_offset + symtab_size) / 16 + 1) * 16;
	
	//==================================================================;
	//	add section header(strtab)
	//==================================================================;

	printf("add section_strtab header(file_offset=0x%x, strtab_offset=0x%x)\n",file_offset, strtab_offset);

	strtab_size	= strtab_offset + 1;

	sec_name	= section_tab_index[SECTION_INDEX_STRTAB];
	sec_type	= SECTION_TYPE_STRTAB;
	sec_flags	= 0;
	sec_addr	= 0;
	sec_offset	= obj_offset; //SECTION_DATA_START_ADDR+data_size+text_size + bss_size + rodata_size + rel_size + shstrtab_size + symtab_size;
	sec_size	= strtab_size;
	sec_link	= 0;
	sec_info	= 0;
	sec_align	= SECTION_ALIGN_STRTAB;
	sec_entrysize	= 0;
	
	sech	= section_header_build(sec_name, sec_type, sec_flags, sec_addr, sec_offset, sec_size, sec_link, sec_info, sec_align, sec_entrysize);

	p= (s8*)sech;
	for(i=0; i<SECTION_HEADER_SIZE; i++, p++)
	{
		fwrite(p,sizeof(char),1,foutput);
	}

	file_offset	+= SECTION_HEADER_SIZE;

	section_copy(&section_h[SECTION_INDEX_STRTAB], sech);
	
	obj_offset	= ((obj_offset + strtab_size) / 16 + 1) * 16;


	//==================================================================;
	//	add section header(comment)
	//==================================================================;

	printf("add section_comment header(file_offset=0x%x)\n",file_offset);

	comment_size	= 0;

	sec_name	= section_tab_index[SECTION_INDEX_COMMENT];
	sec_type	= SECTION_TYPE_PROGBITS;
	sec_flags	= 0x30;						// MS
	sec_addr	= 0;
	sec_offset	= obj_offset;			//SECTION_COMMENT_START_ADDR
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

	section_copy(&section_h[SECTION_INDEX_COMMENT], sech);
	
	obj_offset	= ((obj_offset + comment_size) / 16 + 1) * 16;

	//==================================================================;
	//	add section header(eh_frame)
	//==================================================================;

	printf("add section_eh_frame header(file_offset=0x%x)\n",file_offset);

	eh_frame_size	= 0;

	sec_name	= section_tab_index[SECTION_INDEX_EH_FRAME];
	sec_type	= SECTION_TYPE_PROGBITS;
	sec_flags	= SECTION_FLAGS_ALLOC;				
	sec_addr	= 0;
	sec_offset	= obj_offset;		//
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

	section_copy(&section_h[SECTION_INDEX_EH_FRAME], sech);
	
	obj_offset	= ((obj_offset + eh_frame_size) / 16 + 1) * 16;

	//==================================================================;
	//	add section header(rel_eh_frame)
	//==================================================================;

	printf("add section_rel_eh_frame header(file_offset=0x%x)\n",file_offset);

	rel_eh_frame_size	= 0;

	sec_name	= section_tab_index[SECTION_INDEX_REL_EH_FRAME];
	sec_type	= SECTION_TYPE_REL;
	sec_flags	= 0;				
	sec_addr	= 0;
	sec_offset	= obj_offset;		//
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

	section_copy(&section_h[SECTION_INDEX_REL_EH_FRAME], sech);
	
	obj_offset	= ((obj_offset + rel_eh_frame_size) / 16 + 1) * 16;

	//==================================================================;
	//	add section header(note_gnu_stack)
	//==================================================================;

	printf("add section_note_gnu_stack header(file_offset=0x%x)\n",file_offset);

	note_gnu_stack_size	= 0;

	sec_name	= section_tab_index[SECTION_INDEX_NOTE_GNU_STACK];
	sec_type	= SECTION_TYPE_NOBITS;
	sec_flags	= SECTION_FLAGS_WRITE | SECTION_FLAGS_ALLOC;			
	sec_addr	= 0;
	sec_offset	= obj_offset;		//
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

	section_copy(&section_h[SECTION_INDEX_NOTE_GNU_STACK], sech);
	
	obj_offset	= ((obj_offset + note_gnu_stack_size) / 16 + 1) * 16;
}


//===========================================================================
// PUBLIC	void	pr_mcode_title(FILE *foutput, u32 text_size, u32 data_size)
//===========================================================================
PUBLIC	void	pr_mcode_content(FILE *foutput)
{
	s32 size, start_addr, i;
	s8 *p;
	s8 flg, t,j;

	content_offset	= SECTION_DATA_START_ADDR;

	//-------------------------------------------------------------------;
	//	add section content(text)
	//-------------------------------------------------------------------;
	printf("add section content(text::offset=0x%x)\n",content_offset);

	start_addr	= section_h[SECTION_INDEX_TEXT].offset;
	size		= section_h[SECTION_INDEX_TEXT].size;

	pr_mcode_main(foutput);

	content_offset	+= size;	
	content_offset	+= align_16(foutput, content_offset);	

	//-------------------------------------------------------------------;
	//	add section content(data)
	//-------------------------------------------------------------------;
	printf("add section content(data::offset=0x%x)\n\n",content_offset);

	start_addr	= section_h[SECTION_INDEX_DATA].offset;
	size		= section_h[SECTION_INDEX_DATA].size;

	struct dbtab_list *dblist	= dbl;

	if(dblist)
	{
		dblist 	= dblist->tail;
	}	

	for(; dblist ; dblist=dblist->tail)
	{
		if(dblist->db)
		{
			t = (dblist->db->val) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (dblist->db->val>>8) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
	
			t = (dblist->db->val>>16) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (dblist->db->val>>24) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			
		}
	}	

	content_offset	+= size;	
	content_offset	+= align_16(foutput, content_offset);
	
	//-------------------------------------------------------------------;
	//	add section content(bss)
	//-------------------------------------------------------------------;
	printf("add section content(bss::offset=0x%x)\n",content_offset);

	start_addr	= section_h[SECTION_INDEX_BSS].offset;
	size		= section_h[SECTION_INDEX_BSS].size;
	for(i=0; i<size; i++)
	{
	}
	
	content_offset	+= size;	
	content_offset	+= align_16(foutput, content_offset);

	//-------------------------------------------------------------------;
	//	add section content(rodata)
	//-------------------------------------------------------------------;
	printf("add section content(rodata::offset=0x%x)\n",content_offset);

	start_addr	= section_h[SECTION_INDEX_RODATA].offset;
	size		= section_h[SECTION_INDEX_RODATA].size;
	for(i=0; i<size; i++)
	{
	}

	content_offset	+= size;	
	content_offset	+= align_16(foutput, content_offset);

	//-------------------------------------------------------------------;
	//	add section content(rel.txt)
	//-------------------------------------------------------------------;
	printf("add section content(reltext::offset=0x%x)\n",content_offset);

	start_addr	= section_h[SECTION_INDEX_RELTEXT].offset;
	size		= section_h[SECTION_INDEX_RELTEXT].size;
	
	struct rel32_list *rellist	= rell;

	if(rellist)
	{
		rellist 	= rellist->tail;
	}	

	for(; rellist ; rellist=rellist->tail)
	{
		if(rellist->rel)
		{
			//offset
			t = (rellist->rel->offset) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (rellist->rel->offset>>8) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
	
			t = (rellist->rel->offset>>16) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (rellist->rel->offset>>24) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			
			//info
			t = (rellist->rel->info) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (rellist->rel->info>>8) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
	
			t = (rellist->rel->info>>16) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (rellist->rel->info>>24) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
		}
	}

	content_offset	+= size;	
	content_offset	+= align_16(foutput, content_offset);

	//-------------------------------------------------------------------;
	//	add section content(shstrtab)
	//-------------------------------------------------------------------;
	printf("add section content(shstrtab::offset=0x%x)\n",content_offset);

	start_addr	= section_h[SECTION_INDEX_SHSTRTAB].offset;
	size		= section_h[SECTION_INDEX_SHSTRTAB].size;

	p	= section_tab;
	flg	= TRUE;
	for(i=0; i<size; p++)
	{
		if(!(*p))
		{
			if(flg)
			{
				fwrite(p,sizeof(char),1,foutput);
				i++;
			}
			flg= FALSE;
		}
		else
		{
			fwrite(p,sizeof(char),1,foutput);
			i++;
			flg= TRUE;
		}
		
	}

	content_offset	+= size;	
	content_offset	+= align_16(foutput, content_offset);

	//-------------------------------------------------------------------;
	//	add section content(symtab)
	//-------------------------------------------------------------------;
	printf("add section content(symtab::offset=0x%x)\n",content_offset);

	//----------------------------------------------------------
	// array[0] is null
	//----------------------------------------------------------
	j=0;
	for(i=0; i<16; i++)
	{
		fwrite(&j,sizeof(char),1,foutput);
	}

	//----------------------------------------------------------
	// array[1] ~ array[n]
	//----------------------------------------------------------
	start_addr	= section_h[SECTION_INDEX_SYMTAB].offset;
	size		= section_h[SECTION_INDEX_SYMTAB].size;
	
	struct elfsymtab_list *symlist	= esyml;

	if(symlist)
	{
		symlist 	= symlist->tail;
	}	

	for(; symlist ; symlist=symlist->tail)
	{
		if(symlist->sym)
		{
			
			//strtab_index
			t = (symlist->sym->strtab_index) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (symlist->sym->strtab_index>>8) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
	
			t = (symlist->sym->strtab_index>>16) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (symlist->sym->strtab_index>>24) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			
			//value
			t = (symlist->sym->value) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (symlist->sym->value>>8) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
	
			t = (symlist->sym->value>>16) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (symlist->sym->value>>24) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			//size
			t = (symlist->sym->size) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (symlist->sym->size>>8) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
	
			t = (symlist->sym->size>>16) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (symlist->sym->size>>24) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			//info
			t = (symlist->sym->info) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			//other
			t = (symlist->sym->other) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			//section_index
			t = (symlist->sym->section_index) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (symlist->sym->section_index>>8) & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
		}
	}

	content_offset	+= (size + 16);	
	content_offset	+= align_16(foutput, content_offset);

	//-------------------------------------------------------------------;
	//	add section content(strtab)
	//-------------------------------------------------------------------;
	printf("add section content(strtab::offset=0x%x)\n",content_offset);

	//----------------------------------------------------------
	// strtab[0] is \0
	//----------------------------------------------------------
	j=0;
	fwrite(&j,sizeof(char),1,foutput);

	//----------------------------------------------------------
	// strtab[1] is filename:test.asm
	//----------------------------------------------------------
	
	//----------------------------------------------------------
	// strtab[2] ~ strtab[n]
	//----------------------------------------------------------
	start_addr	= section_h[SECTION_INDEX_STRTAB].offset;
	size		= section_h[SECTION_INDEX_STRTAB].size;
	
	struct strtab_list *strlist	= strl;

	if(strlist)
	{
		strlist 	= strlist->tail;
	}	

	s32 size_i;
	for(; strlist ; strlist=strlist->tail)
	{
		if(strlist->str)
		{			
			flg	= TRUE;
			p	= strlist->str->str;
			size_i	= strlen(p)+1;
			

			for(i=0; i<size_i; p++)
			{
				if(!(*p))
				{
					if(flg)
					{
						fwrite(p,sizeof(char),1,foutput);
						i++;
					}
					flg= FALSE;
				}
				else
				{
					fwrite(p,sizeof(char),1,foutput);
					i++;
					flg= TRUE;
				}
		
			}
		}
	}

	content_offset	+= size + 1;	
	content_offset	+= align_16(foutput, content_offset);

	printf("end(offset=0x%x, size=0x%x)\n",content_offset, size+1);

	//-------------------------------------------------------------------;
	//	add section content(comment)
	//-------------------------------------------------------------------;
	printf("add section content(rodata::offset=0x%x)\n",content_offset);

	start_addr	= section_h[SECTION_INDEX_COMMENT].offset;
	size		= section_h[SECTION_INDEX_COMMENT].size;
	for(i=0; i<size; i++)
	{
	}

	content_offset	+= size;	
	content_offset	+= align_16(foutput, content_offset);

	//-------------------------------------------------------------------;
	//	add section content(eh_frame)
	//-------------------------------------------------------------------;
	printf("add section content(rodata::offset=0x%x)\n",content_offset);

	start_addr	= section_h[SECTION_INDEX_EH_FRAME].offset;
	size		= section_h[SECTION_INDEX_EH_FRAME].size;
	for(i=0; i<size; i++)
	{
	}

	content_offset	+= size;	
	content_offset	+= align_16(foutput, content_offset);

	//-------------------------------------------------------------------;
	//	add section content(rel.eh_frame)
	//-------------------------------------------------------------------;
	printf("add section content(rodata::offset=0x%x)\n",content_offset);

	start_addr	= section_h[SECTION_INDEX_REL_EH_FRAME].offset;
	size		= section_h[SECTION_INDEX_REL_EH_FRAME].size;
	for(i=0; i<size; i++)
	{
	}

	content_offset	+= size;	
	content_offset	+= align_16(foutput, content_offset);

	//-------------------------------------------------------------------;
	//	add section content(note_gun_stack)
	//-------------------------------------------------------------------;
	printf("add section content(rodata::offset=0x%x)\n",content_offset);

	start_addr	= section_h[SECTION_INDEX_NOTE_GNU_STACK].offset;
	size		= section_h[SECTION_INDEX_NOTE_GNU_STACK].size;
	for(i=0; i<size; i++)
	{
	}

	content_offset	+= size;	
	content_offset	+= align_16(foutput, content_offset);
}
