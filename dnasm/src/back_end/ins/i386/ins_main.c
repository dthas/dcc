//===========================================================================
// ins_main.c
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
#include	"dnasm_graph.h"
#include	"dnasm_elf.h"
#include	"dnasm_ins.h"
#include	"dnasm_prototype.h"

#define	INS_DEBUG

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ins_init()
{
	printf("==================================================================\n");
	printf("	ins_init\n");
	printf("==================================================================\n");	

	ins_code_offset	= 0;
	reltab_offset	= 0;

	//for relocate text in *.o within elf format
	rell		= malloc(sizeof(struct rel32_list));	
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ins_main()
{
	printf("==================================================================\n");
	printf("	ins_main\n");
	printf("==================================================================\n");	

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- print_ins -- (pcur_file=0x%x)\n",pcur_file);
#endif
//--------------------------

	icur_file	= file_build(NULL);

	ins_file_process(pcur_file, icur_file);
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ins_file_process(struct pasm_file *f, struct ins_file *i)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_file_process -- \n");
#endif
//--------------------------
	for(; f; f=f->tail)
	{
		struct ins_stslist *istslist 	= ins_stslist_build(NULL);

		ins_stslist_process(f->stslist, istslist);

		struct ins_file *ifile	= file_build(istslist);
		ins_add2file(ifile, i);
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ins_stslist_process(struct pasm_stslist *stslist, struct ins_stslist *istslist)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_stslist_process -- \n\n");
#endif
//--------------------------

	struct ins_sts *ists;

	for(; stslist; stslist=stslist->tail)
	{
		if(stslist->sts)
		{
			ists = ins_sts_process(stslist->sts, istslist);	

			if(ists)
			{
				struct ins_stslist *ists_list 	= ins_stslist_build(ists);
				ins_add2stslist(ists_list, istslist);			
			}					
		}	
	}	
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	struct ins_sts *	ins_sts_process(struct pasm_sts  *sts, struct ins_stslist *istslist)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%5s %10s \n","","-- pasm_sts_process --");
#endif
//--------------------------

	if(sts)
	{
		struct ins_str * instr = malloc(sizeof(struct ins_str));

		u32 label;
		struct ins_sts *ists 	= NULL;
		u32 ins_len = 0;

		
		switch(sts->k)
		{
			case PASM_STS_LABEL:
				sts_kind= INS_STS_LABEL;

				ins_label_build(sts->s.label_sts.pexplist, instr, ins_code_offset);						
				
				label	= INS_STS_LABEL;
				ists	= ins_sts_build(label, instr);

				ins_len	= 0;
				ists->s.label_sts.instr->offset	= ins_code_offset;
				break;			
			case PASM_STS_MOV:
				sts_kind= INS_STS_MOV;

				ins_mov_build(sts->s.mov_sts.pexplist, instr);	
				label	= INS_STS_MOV;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.mov_sts.instr->e.ins_mov.len;
				ists->s.mov_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_ADD:
				sts_kind= INS_STS_ADD;

				ins_add_build(sts->s.add_sts.pexplist, instr);	
				label	= INS_STS_ADD;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.add_sts.instr->e.ins_add.len;
				ists->s.add_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_SUB:
				sts_kind= INS_STS_SUB;

				ins_sub_build(sts->s.sub_sts.pexplist, instr);	
				label	= INS_STS_SUB;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.sub_sts.instr->e.ins_sub.len;
				ists->s.sub_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_MUL:
				sts_kind= INS_STS_MUL;

				ins_mul_build(sts->s.mul_sts.pexplist, instr);	
				label	= INS_STS_MUL;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.mul_sts.instr->e.ins_mul.len;
				ists->s.mul_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_DIV:
				sts_kind= INS_STS_DIV;

				ins_div_build(sts->s.div_sts.pexplist, instr);	
				label	= INS_STS_DIV;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.div_sts.instr->e.ins_div.len;
				ists->s.div_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_CALL:
				sts_kind= INS_STS_CALL;

				ins_call_build(sts->s.call_sts.pexplist, instr);	
				label	= INS_STS_CALL;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.call_sts.instr->e.ins_call.len;
				ists->s.call_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_RET:
				sts_kind= INS_STS_RET;

				ins_ret_build(sts->s.ret_sts.pexplist, instr);	
				label	= INS_STS_RET;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.ret_sts.instr->e.ins_ret.len;
				ists->s.ret_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_JMP:
				sts_kind= INS_STS_JMP;

				ins_jmp_build(sts->s.jmp_sts.pexplist, instr);	
				label	= INS_STS_JMP;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.jmp_sts.instr->e.ins_jmp.len;
				ists->s.jmp_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_JA:
				sts_kind= INS_STS_JA;

				ins_ja_build(sts->s.ja_sts.pexplist, instr);	
				label	= INS_STS_JA;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.ja_sts.instr->e.ins_ja.len;
				ists->s.ja_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_JB:
				sts_kind= INS_STS_JB;

				ins_jb_build(sts->s.jb_sts.pexplist, instr);	
				label	= INS_STS_JB;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.jb_sts.instr->e.ins_jb.len;
				ists->s.jb_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_JE:
				sts_kind= INS_STS_JE;

				ins_je_build(sts->s.je_sts.pexplist, instr);	
				label	= INS_STS_JE;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.je_sts.instr->e.ins_je.len;
				ists->s.je_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_JAE:
				sts_kind= INS_STS_JAE;

				ins_jae_build(sts->s.jae_sts.pexplist, instr);	
				label	= INS_STS_JAE;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.jae_sts.instr->e.ins_jae.len;
				ists->s.jae_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_JBE:
				sts_kind= INS_STS_JBE;

				ins_jbe_build(sts->s.jbe_sts.pexplist, instr);	
				label	= INS_STS_JBE;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.jbe_sts.instr->e.ins_jbe.len;
				ists->s.jbe_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_JNE:
				sts_kind= INS_STS_JNE;

				ins_jne_build(sts->s.jne_sts.pexplist, instr);	
				label	= INS_STS_JNE;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.jne_sts.instr->e.ins_jne.len;
				ists->s.jne_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_PUSH:
				sts_kind= INS_STS_PUSH;

				ins_push_build(sts->s.push_sts.pexplist, instr);	
				label	= INS_STS_PUSH;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.push_sts.instr->e.ins_push.len;
				ists->s.push_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_POP:
				sts_kind= INS_STS_POP;

				ins_pop_build(sts->s.pop_sts.pexplist, instr);	
				label	= INS_STS_POP;
				ists	= ins_sts_build(label, instr);
	
				ins_len	= ists->s.pop_sts.instr->e.ins_pop.len;
				ists->s.pop_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_CMP:
				sts_kind= INS_STS_CMP;

				ins_cmp_build(sts->s.cmp_sts.pexplist, instr);	
				label	= INS_STS_CMP;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.cmp_sts.instr->e.ins_cmp.len;
				ists->s.cmp_sts.instr->offset	= ins_code_offset;
				break;
			case PASM_STS_XOR:
				sts_kind= INS_STS_XOR;

				ins_xor_build(sts->s.xor_sts.pexplist, instr);	
				label	= INS_STS_XOR;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.xor_sts.instr->e.ins_xor.len;
				ists->s.xor_sts.instr->offset	= ins_code_offset;
				break;

			case PASM_STS_INT:
				sts_kind= INS_STS_INT;

				ins_int_build(sts->s.int_sts.pexplist, instr);	
				label	= INS_STS_INT;
				ists	= ins_sts_build(label, instr);

				ins_len	= ists->s.int_sts.instr->e.ins_int.len;
				ists->s.int_sts.instr->offset	= ins_code_offset;
				break;	
			
			default:
				break;
		}
		
		ins_code_offset	+= ins_len;

		return ists;
	}
}






//===========================================================================
// sts_build()
//===========================================================================
PUBLIC	struct ins_sts *	ins_sts_build(u32 kind, struct ins_str *p)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("	-- ins_sts_build  -- \n");
#endif
//--------------------------

	struct ins_sts *ret_sts	= malloc(sizeof(struct ins_sts));

	if(!ret_sts)
	{
		printf("ins_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= kind;
	ret_sts->s.mov_sts.instr	= p;

	return ret_sts;
}

//===========================================================================
// stslist_build()
//===========================================================================
PUBLIC	struct ins_stslist *	ins_stslist_build(struct ins_sts *sts)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("	-- ins_stslist_build  -- \n");
#endif
//--------------------------

	struct ins_stslist *ret_stslist	= malloc(sizeof(struct ins_stslist));

	if(!ret_stslist)
	{
		printf("ins_stslist() malloc failed!!\n");
		exit(1);
	}

	ret_stslist->sts	= sts;
	ret_stslist->head	= NULL;
	ret_stslist->tail	= NULL;

	return ret_stslist;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	s8	ins_add2stslist(struct ins_stslist *src, struct ins_stslist * dst)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("	-- ins_add2stslist(src=0x%x, dst=0x%x)  -- \n\n", src, dst);
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}

//===========================================================================
// file_build
//===========================================================================
PUBLIC	struct ins_file *	ins_file_build(struct ins_stslist *stslist)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("	-- ins_file_build  -- \n");
#endif
//--------------------------

	struct ins_file *ret_file	= malloc(sizeof(struct ins_file));

	if(!ret_file)
	{
		printf("ir_file() malloc failed!!\n");
		exit(1);
	}

	ret_file->stslist	= stslist;
	ret_file->head	= NULL;
	ret_file->tail	= NULL;

	return ret_file;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	s8	ins_add2file(struct ins_file *src, struct ins_file * dst)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("	-- ins_add2file  -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}

