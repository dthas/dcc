//===========================================================================
// ins_update.c
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
#include	"dnasm_ins.h"
#include	"dnasm_elf.h"
#include	"dnasm_prototype.h"

#define	INS_DEBUG

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ins_update()
{
	printf("==================================================================\n");
	printf("	ins update\n");
	printf("==================================================================\n");

	upd_ins_file_process(icur_file);
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	upd_ins_file_process(struct ins_file *f)
{
	for(; f; f=f->tail)
	{
		upd_ins_stslist_process(f->stslist);
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	upd_ins_stslist_process(struct ins_stslist *stslist)
{
	for(; stslist; stslist=stslist->tail)
	{
		upd_ins_sts_process(stslist->sts);		
	}	
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	upd_ins_sts_process(struct ins_sts  *sts)
{
	if(sts)
	{
		switch(sts->k)
		{
			case INS_STS_CALL:
				upd_ins_call_process(sts->s.call_sts.instr);
				break;
			case INS_STS_JMP:
				upd_ins_jmp_process(sts->s.jmp_sts.instr);
				break;
			case INS_STS_JA:
				upd_ins_ja_process(sts->s.ja_sts.instr);
				break;
			case INS_STS_JB:
				upd_ins_jb_process(sts->s.jb_sts.instr);
				break;
			case INS_STS_JE:
				upd_ins_je_process(sts->s.je_sts.instr);
				break;
			case INS_STS_JAE:
				upd_ins_jae_process(sts->s.jae_sts.instr);
				break;
			case INS_STS_JBE:
				upd_ins_jbe_process(sts->s.jbe_sts.instr);
				break;
			case INS_STS_JNE:
				upd_ins_jne_process(sts->s.jne_sts.instr);
				break;
			default:
				break;
		}
	}
}


//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	upd_ins_jmp_process(struct ins_str *instr)
{
	struct symbol *	sym	= symtbl_search(instr->e.ins_jmp.m.jmp_8.label);
	if(!sym)
	{
		printf("upd_ins_jmp_process::error, can not find the symbol:%s !!!\n\n", instr->e.ins_jmp.m.jmp_8.label);
	}

	instr->e.ins_jmp.m.jmp_8.offset = sym->val_i - (instr->offset + instr->e.ins_jmp.len);	

	sym->val_i_1	= sym->val_i;	
	sym->val_i	= instr->e.ins_jmp.m.jmp_8.offset;
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	upd_ins_ja_process(struct ins_str *instr)
{
	struct symbol *	sym	= symtbl_search(instr->e.ins_ja.m.ja_8.label);
	if(!sym)
	{
		printf("upd_ins_ja_process::error, can not find the symbol:%s !!!\n\n", instr->e.ins_ja.m.ja_8.label);
	}

	instr->e.ins_ja.m.ja_8.offset = sym->val_i - (instr->offset + instr->e.ins_ja.len);

	sym->val_i_1	= sym->val_i;	
	sym->val_i	= instr->e.ins_ja.m.ja_8.offset;
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	upd_ins_jb_process(struct ins_str *instr)
{
	struct symbol *	sym	= symtbl_search(instr->e.ins_jb.m.jb_8.label);
	if(!sym)
	{
		printf("upd_ins_jb_process::error, can not find the symbol:%s !!!\n\n", instr->e.ins_jb.m.jb_8.label);
	}

	instr->e.ins_jb.m.jb_8.offset = sym->val_i - (instr->offset + instr->e.ins_jb.len);

	sym->val_i_1	= sym->val_i;	
	sym->val_i	= instr->e.ins_jb.m.jb_8.offset;
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	upd_ins_je_process(struct ins_str *instr)
{
	struct symbol *	sym	= symtbl_search(instr->e.ins_je.m.je_8.label);
	if(!sym)
	{
		printf("upd_ins_je_process::error, can not find the symbol:%s !!!\n\n", instr->e.ins_je.m.je_8.label);
	}

	instr->e.ins_je.m.je_8.offset = sym->val_i - (instr->offset + instr->e.ins_je.len);

	sym->val_i_1	= sym->val_i;
	sym->val_i	= instr->e.ins_je.m.je_8.offset;
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	upd_ins_jae_process(struct ins_str *instr)
{
	struct symbol *	sym	= symtbl_search(instr->e.ins_jae.m.jae_8.label);
	if(!sym)
	{
		printf("upd_ins_jae_process::error, can not find the symbol:%s !!!\n\n", instr->e.ins_jae.m.jae_8.label);
	}

	instr->e.ins_jae.m.jae_8.offset = sym->val_i - (instr->offset + instr->e.ins_jae.len);

	sym->val_i_1	= sym->val_i;	
	sym->val_i	= instr->e.ins_jae.m.jae_8.offset;
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	upd_ins_jbe_process(struct ins_str *instr)
{
	struct symbol *	sym	= symtbl_search(instr->e.ins_jbe.m.jbe_8.label);
	if(!sym)
	{
		printf("upd_ins_jbe_process::error, can not find the symbol:%s !!!\n\n", instr->e.ins_jbe.m.jbe_8.label);
	}

	instr->e.ins_jbe.m.jbe_8.offset = sym->val_i - (instr->offset + instr->e.ins_jbe.len);

	sym->val_i_1	= sym->val_i;
	sym->val_i	= instr->e.ins_jbe.m.jbe_8.offset;
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	upd_ins_jne_process(struct ins_str *instr)
{
	struct symbol *	sym	= symtbl_search(instr->e.ins_jne.m.jne_8.label);
	if(!sym)
	{
		printf("upd_ins_jne_process::error, can not find the symbol:%s !!!\n\n", instr->e.ins_jne.m.jne_8.label);
	}

	instr->e.ins_jne.m.jne_8.offset = sym->val_i - (instr->offset + instr->e.ins_jne.len);

	sym->val_i_1	= sym->val_i;	
	sym->val_i	= instr->e.ins_jne.m.jne_8.offset;
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	upd_ins_call_process(struct ins_str *instr)
{
	struct symbol *	sym	= symtbl_search(instr->e.ins_call.m.call_32.label);
	if(!sym)
	{
		printf("upd_ins_call_process::error, can not find the symbol:%s !!!\n\n", instr->e.ins_call.m.call_32.label);
	}

	instr->e.ins_call.m.call_32.offset = sym->val_i - (instr->offset + instr->e.ins_call.len);

	sym->val_i	= instr->e.ins_call.m.call_32.offset;

	//--------------------------------------------------------
	//for relocate table
	sym->addr	= instr->offset + sizeof(instr->e.ins_call.m.call_32.format_1);
	
	struct symbol *p;
	s8 flag_f = FALSE;
	s32 i, num;
	
	//get num, which is the index within strtab in future
	for(i=0, num=1; i<SYMTBL_SIZE; i++)
	{
		if(flag_f)
		{
			break;
		}

		for(p=(*(p_symtbl+i)).tail; p!=NULL; p=p->tail)
		{
			if(p->flag != FLAG_SYM)
			{
				if(strcmp(p->name, sym->name) == TRUE)
				{
					flag_f = TRUE;
					break;
				}

				//for index
				num++;
			}

						
		}
	}

	struct rel32	  *rel	= malloc(sizeof(struct rel32));
	rel->offset		= sym->addr;

	switch(sym->attr)
	{
		case ATTR_FUN:
			rel->info	= num; 
			rel->info	= ((rel->info)<<8)| R_386_PC32;
			break;
		case ATTR_VAR:
			rel->info	= num; 
			rel->info	= ((rel->info)<<8)|  R_386_32;					
			break;
		default:
			break;
	} 	

	//add to relocate list
	struct rel32_list *rellist	= rel32list_build(rel);
	elf_add2rellist(rellist, rell);

	reltab_offset	+= sizeof(struct rel32);	
	//--------------------------------------------------------	
}


