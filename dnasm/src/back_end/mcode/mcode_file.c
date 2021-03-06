//===========================================================================
// ins_lib_t.c
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

#define	MCODE_DEBUG

PRIVATE	s8 t;
//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_mcode_main(FILE *foutput)
{
	printf(";==================================================================\n");
	printf("	machine code file\n");
	printf(";==================================================================\n");

	pr_mcode_file_process(icur_file, foutput);
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_mcode_file_process(struct ins_file *f, FILE *foutput)
{
	for(; f; f=f->tail)
	{
		pr_mcode_stslist_process(f->stslist, foutput);
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_mcode_stslist_process(struct ins_stslist *stslist, FILE *foutput)
{
	for(; stslist; stslist=stslist->tail)
	{
		pr_mcode_sts_process(stslist->sts, foutput);		
	}	
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_mcode_sts_process(struct ins_sts  *sts, FILE *foutput)
{
	if(sts)
	{
		switch(sts->k)
		{
			case INS_STS_MOV:
				pr_mcode_mov_process(sts->s.mov_sts.instr, foutput);
				break;
			case INS_STS_ADD:
				pr_mcode_add_process(sts->s.add_sts.instr, foutput);
				break;
			case INS_STS_SUB:
				pr_mcode_sub_process(sts->s.sub_sts.instr, foutput);
				break;
			case INS_STS_MUL:
				pr_mcode_mul_process(sts->s.mul_sts.instr, foutput);
				break;
			case INS_STS_DIV:
				pr_mcode_div_process(sts->s.div_sts.instr, foutput);
				break;
			case INS_STS_CALL:
				pr_mcode_call_process(sts->s.call_sts.instr, foutput);
				break;
			case INS_STS_RET:
				pr_mcode_ret_process(sts->s.ret_sts.instr, foutput);
				break;
			case INS_STS_JMP:
				pr_mcode_jmp_process(sts->s.jmp_sts.instr, foutput);
				break;
			case INS_STS_JA:
				pr_mcode_ja_process(sts->s.ja_sts.instr, foutput);
				break;
			case INS_STS_JB:
				pr_mcode_jb_process(sts->s.jb_sts.instr, foutput);
				break;
			case INS_STS_JE:
				pr_mcode_je_process(sts->s.je_sts.instr, foutput);
				break;
			case INS_STS_JAE:
				pr_mcode_jae_process(sts->s.jae_sts.instr, foutput);
				break;
			case INS_STS_JBE:
				pr_mcode_jbe_process(sts->s.jbe_sts.instr, foutput);
				break;
			case INS_STS_JNE:
				pr_mcode_jne_process(sts->s.jne_sts.instr, foutput);
				break;
			case INS_STS_PUSH:
				pr_mcode_push_process(sts->s.push_sts.instr, foutput);
				break;
			case INS_STS_POP:
				pr_mcode_pop_process(sts->s.pop_sts.instr, foutput);
				break;
			case INS_STS_CMP:
				pr_mcode_cmp_process(sts->s.cmp_sts.instr, foutput);
				break;
			case INS_STS_XOR:
				pr_mcode_xor_process(sts->s.cmp_sts.instr, foutput);
				break;

			case INS_STS_INT:
				pr_mcode_int_process(sts->s.int_sts.instr, foutput);
				break;
			default:
				break;
		}
	}
}	


//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_cmp_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_cmp.k)
	{	
		case INS_CMP_REG_2_REG_32:
			t = (instr->e.ins_cmp.m.cmp_reg_2_reg_32.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_cmp.m.cmp_reg_2_reg_32.format_2)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}


//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_ret_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_ret.k)
	{	
		case INS_RET_32:
			t = (instr->e.ins_ret.m.ret_32.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_div_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_div.k)
	{	
		case INS_DIV_REG_16:
			t = (instr->e.ins_div.m.div_reg_16.prefix)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_div.m.div_reg_16.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_div.m.div_reg_16.format_2)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}


//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_mul_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_mul.k)
	{	
		case INS_MUL_REG_16:
			t = (instr->e.ins_mul.m.mul_reg_16.prefix)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mul.m.mul_reg_16.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mul.m.mul_reg_16.format_2)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_sub_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_sub.k)
	{	
		case INS_SUB_REG_2_REG_32:
			t = (instr->e.ins_sub.m.sub_reg_2_reg_32.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_sub.m.sub_reg_2_reg_32.format_2)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_xor_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_xor.k)
	{	
		case INS_XOR_REG_2_REG_32:
			t = (instr->e.ins_xor.m.xor_reg_2_reg_32.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_xor.m.xor_reg_2_reg_32.format_2)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_add_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_add.k)
	{	
		case INS_ADD_REG_2_REG_32:
			t = (instr->e.ins_add.m.add_reg_2_reg_32.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_add.m.add_reg_2_reg_32.format_2)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		case INS_ADD_REG_2_IMM_32:
			t = (instr->e.ins_add.m.add_reg_2_imm_32.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_add.m.add_reg_2_imm_32.format_2)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_add.m.add_reg_2_imm_32.data)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_add.m.add_reg_2_imm_32.data>>8)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_add.m.add_reg_2_imm_32.data>>16)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_add.m.add_reg_2_imm_32.data>>24)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		case INS_ADD_REG_2_IMM_8:
			t = (instr->e.ins_add.m.add_reg_2_imm_8.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_add.m.add_reg_2_imm_8.format_2)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_add.m.add_reg_2_imm_8.data)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
		
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_pop_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_pop.k)
	{	
		case INS_POP_REG_32:
			t = (instr->e.ins_pop.m.pop_reg_32.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_push_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_push.k)
	{	
		case INS_PUSH_REG_32:
			t = (instr->e.ins_push.m.push_reg_32.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		case INS_PUSH_MEM_32:
			t = (instr->e.ins_push.m.push_mem_32.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_push.m.push_mem_32.format_2)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_push.m.push_mem_32.offset)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_mov_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_mov.k)
	{	
		case INS_MOV_REG_2_REG_32:
			
			t = (instr->e.ins_mov.m.mov_reg_2_reg_32.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_reg_2_reg_32.format_2)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		case INS_MOV_REG_2_IMM_32:
			
			t = (instr->e.ins_mov.m.mov_reg_2_imm_32.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_reg_2_imm_32.data)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_reg_2_imm_32.data>>8)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_reg_2_imm_32.data>>16)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_reg_2_imm_32.data>>24)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		case INS_MOV_REG_2_MEM_32:
			
			t = (instr->e.ins_mov.m.mov_reg_2_mem_32.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_reg_2_mem_32.format_2)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_reg_2_mem_32.offset)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		case INS_MOV_MEM_2_REG_32:
			
			t = (instr->e.ins_mov.m.mov_mem_2_reg_32.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_mem_2_reg_32.format_2)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_mem_2_reg_32.offset)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		case INS_MOV_NUMB_2_REG_32:
			
			t = (instr->e.ins_mov.m.mov_numb_2_reg_32.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_numb_2_reg_32.format_2)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_numb_2_reg_32.addr)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_numb_2_reg_32.addr>>8)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_numb_2_reg_32.addr>>16)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_numb_2_reg_32.addr>>24)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		case INS_MOV_REG_2_NUMB_32:
			
			t = (instr->e.ins_mov.m.mov_reg_2_numb_32.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_reg_2_numb_32.format_2)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_reg_2_numb_32.addr)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_reg_2_numb_32.addr>>8)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_reg_2_numb_32.addr>>16)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_mov.m.mov_reg_2_numb_32.addr>>24)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
	
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_jmp_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_jmp.k)
	{	
		case INS_JMP_8:
			t = (instr->e.ins_jmp.m.jmp_8.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_jmp.m.jmp_8.offset)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_ja_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_ja.k)
	{	
		case INS_JA_8:
			t = (instr->e.ins_ja.m.ja_8.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = instr->e.ins_ja.m.ja_8.offset & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_jb_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_jb.k)
	{	
		case INS_JB_8:
			t = (instr->e.ins_jb.m.jb_8.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = instr->e.ins_jb.m.jb_8.offset & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_je_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_je.k)
	{	
		case INS_JE_8:
			t = (instr->e.ins_je.m.je_8.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = instr->e.ins_je.m.je_8.offset & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_jae_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_jae.k)
	{	
		case INS_JAE_8:
			t = (instr->e.ins_jae.m.jae_8.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = instr->e.ins_jae.m.jae_8.offset & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_jbe_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_jbe.k)
	{	
		case INS_JBE_8:
			t = (instr->e.ins_jbe.m.jbe_8.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = instr->e.ins_jbe.m.jbe_8.offset & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_jne_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_jne.k)
	{	
		case INS_JNE_8:
			t = (instr->e.ins_jne.m.jne_8.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = instr->e.ins_jne.m.jne_8.offset & 0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_call_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_call.k)
	{	
		case INS_CALL_32:
			t = (instr->e.ins_call.m.call_32.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_call.m.call_32.offset)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_call.m.call_32.offset>>8)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_call.m.call_32.offset>>16)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_call.m.call_32.offset>>24)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}


//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_mcode_int_process(struct ins_str *instr, FILE *foutput)
{
	switch(instr->e.ins_int.k)
	{	
		case INS_INT_8:
			t = (instr->e.ins_int.m.int_imm_8.format_1)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);

			t = (instr->e.ins_int.m.int_imm_8.data)&0xFF;
			fwrite(&t,sizeof(char),1,foutput);
			break;
		default:
			break;
	}
}
