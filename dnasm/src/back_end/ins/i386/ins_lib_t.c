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
#include	"dnasm_prototype.h"

#define	INS_DEBUG

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_ins_main()
{
	printf("==================================================================\n");
	printf("	ins print\n");
	printf("==================================================================\n");

	pr_ins_file_process(icur_file);
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_ins_file_process(struct ins_file *f)
{
	for(; f; f=f->tail)
	{
		pr_ins_stslist_process(f->stslist);
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_ins_stslist_process(struct ins_stslist *stslist)
{
	for(; stslist; stslist=stslist->tail)
	{
		pr_ins_sts_process(stslist->sts);		
	}	
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pr_ins_sts_process(struct ins_sts  *sts)
{
	if(sts)
	{
		switch(sts->k)
		{
			case INS_STS_LABEL:
				pr_ins_label_process(sts->s.label_sts.instr);
				break;			
			case INS_STS_MOV:
				pr_ins_mov_process(sts->s.mov_sts.instr);
				break;
			case INS_STS_ADD:
				pr_ins_add_process(sts->s.add_sts.instr);
				break;
			case INS_STS_SUB:
				pr_ins_sub_process(sts->s.sub_sts.instr);
				break;
			case INS_STS_MUL:
				pr_ins_mul_process(sts->s.mul_sts.instr);
				break;
			case INS_STS_DIV:
				pr_ins_div_process(sts->s.div_sts.instr);
				break;
			case INS_STS_CALL:
				pr_ins_call_process(sts->s.call_sts.instr);
				break;
			case INS_STS_RET:
				pr_ins_ret_process(sts->s.ret_sts.instr);
				break;
			case INS_STS_JMP:
				pr_ins_jmp_process(sts->s.jmp_sts.instr);
				break;
			case INS_STS_JA:
				pr_ins_ja_process(sts->s.ja_sts.instr);
				break;
			case INS_STS_JB:
				pr_ins_jb_process(sts->s.jb_sts.instr);
				break;
			case INS_STS_JE:
				pr_ins_je_process(sts->s.je_sts.instr);
				break;
			case INS_STS_JAE:
				pr_ins_jae_process(sts->s.jae_sts.instr);
				break;
			case INS_STS_JBE:
				pr_ins_jbe_process(sts->s.jbe_sts.instr);
				break;
			case INS_STS_JNE:
				pr_ins_jne_process(sts->s.jne_sts.instr);
				break;
			case INS_STS_PUSH:
				pr_ins_push_process(sts->s.push_sts.instr);
				break;
			case INS_STS_POP:
				pr_ins_pop_process(sts->s.pop_sts.instr);
				break;
			case INS_STS_CMP:
				pr_ins_cmp_process(sts->s.cmp_sts.instr);
				break;
			case INS_STS_XOR:
				pr_ins_xor_process(sts->s.cmp_sts.instr);
				break;

			default:
				break;
		}
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_cmp_process(struct ins_str *instr)
{
	switch(instr->e.ins_cmp.k)
	{	
		case INS_CMP_REG_2_REG_32:
			printf("0x%x:	cmp(kind=%d, len=%d, format_1=0x%x, format_2=0x%x)\n\n", instr->offset,
				instr->e.ins_cmp.k, instr->e.ins_cmp.len, 
				instr->e.ins_cmp.m.cmp_reg_2_reg_32.format_1, instr->e.ins_cmp.m.cmp_reg_2_reg_32.format_2);
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_label_process(struct ins_str *instr)
{
	switch(instr->e.ins_label.k)
	{	
		case INS_LABEL_32:
			printf("0x%x:	label(kind=%d, len=%d, name=%s, offset=0x%x)\n\n", instr->offset,
				instr->e.ins_label.k, instr->e.ins_label.len, 
				instr->e.ins_label.m.label.name, instr->e.ins_label.m.label.offset);
			break;
		default:
			break;
	}	
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_ret_process(struct ins_str *instr)
{
	switch(instr->e.ins_ret.k)
	{	
		case INS_RET_32:
			printf("0x%x:	ret(kind=%d, len=%d, format_1=0x%x)\n\n", instr->offset,
				instr->e.ins_ret.k, instr->e.ins_ret.len, 
				instr->e.ins_ret.m.ret_32.format_1);

			break;
		default:
			break;
	}	
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_div_process(struct ins_str *instr)
{
	switch(instr->e.ins_div.k)
	{	
		case INS_DIV_REG_16:
			printf("0x%x:	div(kind=%d, len=%d, prefix=0x%x, format_1=0x%x, format_2=0x%x)\n\n", instr->offset,
				instr->e.ins_div.k, instr->e.ins_div.len, 
				instr->e.ins_div.m.div_reg_16.prefix, instr->e.ins_div.m.div_reg_16.format_1, 
				instr->e.ins_div.m.div_reg_16.format_2);
			break;
		default:
			break;
	}	
}


//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_mul_process(struct ins_str *instr)
{
	switch(instr->e.ins_mul.k)
	{	
		case INS_MUL_REG_16:
			printf("0x%x:	mul(kind=%d, len=%d, prefix=0x%x, format_1=0x%x, format_2=0x%x)\n\n", instr->offset,
				instr->e.ins_mul.k, instr->e.ins_mul.len, 
				instr->e.ins_mul.m.mul_reg_16.prefix, instr->e.ins_mul.m.mul_reg_16.format_1, 
				instr->e.ins_mul.m.mul_reg_16.format_2);
			break;
		default:
			break;
	}	
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_sub_process(struct ins_str *instr)
{
	switch(instr->e.ins_sub.k)
	{	
		case INS_SUB_REG_2_REG_32:
			printf("0x%x:	sub(kind=%d, len=%d, format_1=0x%x, format_2=0x%x)\n\n", instr->offset,
				instr->e.ins_sub.k, instr->e.ins_sub.len, 
				instr->e.ins_sub.m.sub_reg_2_reg_32.format_1, instr->e.ins_sub.m.sub_reg_2_reg_32.format_2);
			break;
		default:
			break;
	}	
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_xor_process(struct ins_str *instr)
{
	switch(instr->e.ins_xor.k)
	{	
		case INS_XOR_REG_2_REG_32:
			printf("0x%x:	xor(kind=%d, len=%d, format_1=0x%x, format_2=0x%x)\n\n", instr->offset,
				instr->e.ins_xor.k, instr->e.ins_xor.len, 
				instr->e.ins_xor.m.xor_reg_2_reg_32.format_1, instr->e.ins_xor.m.xor_reg_2_reg_32.format_2);			
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_add_process(struct ins_str *instr)
{
	switch(instr->e.ins_add.k)
	{	
		case INS_ADD_REG_2_REG_32:
			printf("0x%x:	add(kind=%d, len=%d, format_1=0x%x, format_2=0x%x)\n\n", instr->offset,
				instr->e.ins_add.k, instr->e.ins_add.len, 
				instr->e.ins_add.m.add_reg_2_reg_32.format_1, instr->e.ins_add.m.add_reg_2_reg_32.format_2);
			break;
		case INS_ADD_REG_2_IMM_32:
			printf("0x%x:	add(kind=%d, len=%d, format_1=0x%x, format_2=0x%x, data=0x%x)\n\n", instr->offset,
				instr->e.ins_add.k, instr->e.ins_add.len, 
				instr->e.ins_add.m.add_reg_2_imm_32.format_1,instr->e.ins_add.m.add_reg_2_imm_32.format_2,
				instr->e.ins_add.m.add_reg_2_imm_32.data);
			break;
		default:
			break;
	}	
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_pop_process(struct ins_str *instr)
{
	switch(instr->e.ins_pop.k)
	{	
		case INS_POP_REG_32:
			printf("0x%x:	pop(kind=%d, len=%d, format_1=0x%x)\n\n", instr->offset,
				instr->e.ins_pop.k, instr->e.ins_pop.len, 
				instr->e.ins_pop.m.pop_reg_32.format_1);
			break;
		default:
			break;
	}	
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_push_process(struct ins_str *instr)
{
	switch(instr->e.ins_push.k)
	{	
		case INS_PUSH_REG_32:
			printf("0x%x:	push(kind=%d, len=%d, format_1=0x%x)\n\n", instr->offset,
				instr->e.ins_push.k, instr->e.ins_push.len, 
				instr->e.ins_push.m.push_reg_32.format_1);
			break;
		case INS_PUSH_MEM_32:
			printf("0x%x:	push(kind=%d, len=%d, format_1=0x%x, format_2=0x%x, offset=0x%x)\n\n", instr->offset,
				instr->e.ins_push.k, instr->e.ins_push.len, 
				instr->e.ins_push.m.push_mem_32.format_1, instr->e.ins_push.m.push_mem_32.format_2,
				(instr->e.ins_push.m.push_mem_32.offset & 0xFF));
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_mov_process(struct ins_str *instr)
{
	switch(instr->e.ins_mov.k)
	{	
		case INS_MOV_REG_2_REG_32:
			printf("0x%x:	mov(kind=%d, len=%d, format_1=0x%x, format_2=0x%x)\n\n", instr->offset,
				instr->e.ins_mov.k, instr->e.ins_mov.len, 
				instr->e.ins_mov.m.mov_reg_2_reg_32.format_1, instr->e.ins_mov.m.mov_reg_2_reg_32.format_2);
			break;
		case INS_MOV_REG_2_IMM_32:
			printf("0x%x:	mov(kind=%d, len=%d, format_1=0x%x, data=0x%x)\n\n", instr->offset,
				instr->e.ins_mov.k, instr->e.ins_mov.len, 
				instr->e.ins_mov.m.mov_reg_2_imm_32.format_1, instr->e.ins_mov.m.mov_reg_2_imm_32.data);
			break;
		case INS_MOV_REG_2_MEM_32:
			printf("0x%x:	mov(kind=%d, len=%d, format_1=0x%x, format_2=0x%x, offset=0x%x)\n\n",  instr->offset,
				instr->e.ins_mov.k, instr->e.ins_mov.len, 
				instr->e.ins_mov.m.mov_reg_2_mem_32.format_1, instr->e.ins_mov.m.mov_reg_2_mem_32.format_2,
				(instr->e.ins_mov.m.mov_reg_2_mem_32.offset & 0xFF));
			break;
		case INS_MOV_MEM_2_REG_32:
			printf("0x%x:	mov(kind=%d, len=%d, format_1=0x%x, format_2=0x%x, offset=0x%x)\n\n",  instr->offset,
				instr->e.ins_mov.k, instr->e.ins_mov.len, 
				instr->e.ins_mov.m.mov_mem_2_reg_32.format_1, instr->e.ins_mov.m.mov_mem_2_reg_32.format_2,
				(instr->e.ins_mov.m.mov_mem_2_reg_32.offset & 0xFF));
			break;
		case INS_MOV_NUMB_2_REG_32:
			printf("0x%x:	mov(kind=%d, len=%d, format_1=0x%x, format_2=0x%x, addr=0x%x)\n\n",  instr->offset,
				instr->e.ins_mov.k, instr->e.ins_mov.len, 
				instr->e.ins_mov.m.mov_numb_2_reg_32.format_1, instr->e.ins_mov.m.mov_numb_2_reg_32.format_2,
				instr->e.ins_mov.m.mov_numb_2_reg_32.addr);
			break;
		case INS_MOV_REG_2_NUMB_32:
			printf("0x%x:	mov(kind=%d, len=%d, format_1=0x%x, format_2=0x%x, addr=0x%x)\n\n",  instr->offset,
				instr->e.ins_mov.k, instr->e.ins_mov.len, 
				instr->e.ins_mov.m.mov_reg_2_numb_32.format_1, instr->e.ins_mov.m.mov_reg_2_numb_32.format_2,
				instr->e.ins_mov.m.mov_reg_2_numb_32.addr);
			break;
		default:
			break;
	}	
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_jmp_process(struct ins_str *instr)
{
	switch(instr->e.ins_jmp.k)
	{	
		case INS_JMP_8:
			printf("0x%x:	jmp(kind=%d, len=%d, format_1=0x%x, label=%s, offset=0x%x)\n\n", instr->offset,
				instr->e.ins_jmp.k, instr->e.ins_jmp.len, 
				instr->e.ins_jmp.m.jmp_8.format_1, instr->e.ins_jmp.m.jmp_8.label,
				(instr->e.ins_jmp.m.jmp_8.offset & 0xFF));
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_ja_process(struct ins_str *instr)
{
	switch(instr->e.ins_ja.k)
	{	
		case INS_JA_8:
			printf("0x%x:	ja(kind=%d, len=%d, format_1=0x%x, label=%s, offset=0x%x)\n\n", instr->offset,
				instr->e.ins_ja.k, instr->e.ins_ja.len, 
				instr->e.ins_ja.m.ja_8.format_1, instr->e.ins_ja.m.ja_8.label,
				(instr->e.ins_ja.m.ja_8.offset & 0xFF));
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_jb_process(struct ins_str *instr)
{
	switch(instr->e.ins_jb.k)
	{	
		case INS_JB_8:
			printf("0x%x:	jb(kind=%d, len=%d, format_1=0x%x, label=%s, offset=0x%x)\n\n", instr->offset,
				instr->e.ins_jb.k, instr->e.ins_jb.len, 
				instr->e.ins_jb.m.jb_8.format_1, instr->e.ins_jb.m.jb_8.label,
				(instr->e.ins_jb.m.jb_8.offset & 0xFF));
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_je_process(struct ins_str *instr)
{
	switch(instr->e.ins_je.k)
	{	
		case INS_JE_8:
			printf("0x%x:	je(kind=%d, len=%d, format_1=0x%x, label=%s, offset=0x%x)\n\n", instr->offset,
				instr->e.ins_je.k, instr->e.ins_je.len, 
				instr->e.ins_je.m.je_8.format_1, instr->e.ins_je.m.je_8.label,
				(instr->e.ins_je.m.je_8.offset & 0xFF));
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_jae_process(struct ins_str *instr)
{
	switch(instr->e.ins_jae.k)
	{	
		case INS_JAE_8:
			printf("0x%x:	jae(kind=%d, len=%d, format_1=0x%x, label=%s, offset=0x%x)\n\n", instr->offset,
				instr->e.ins_jae.k, instr->e.ins_jae.len, 
				instr->e.ins_jae.m.jae_8.format_1, instr->e.ins_jae.m.jae_8.label,
				(instr->e.ins_jae.m.jae_8.offset & 0xFF));
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_jbe_process(struct ins_str *instr)
{
	switch(instr->e.ins_jbe.k)
	{	
		case INS_JBE_8:
			printf("0x%x:	jbe(kind=%d, len=%d, format_1=0x%x, label=%s, offset=0x%x)\n\n", instr->offset,
				instr->e.ins_jbe.k, instr->e.ins_jbe.len, 
				instr->e.ins_jbe.m.jbe_8.format_1, instr->e.ins_jbe.m.jbe_8.label,
				(instr->e.ins_jbe.m.jbe_8.offset & 0xFF));
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_jne_process(struct ins_str *instr)
{
	switch(instr->e.ins_jne.k)
	{	
		case INS_JNE_8:
			printf("0x%x:	jne(kind=%d, len=%d, format_1=0x%x, label=%s, offset=0x%x)\n\n", instr->offset,
				instr->e.ins_jne.k, instr->e.ins_jne.len, 
				instr->e.ins_jne.m.jne_8.format_1, instr->e.ins_jne.m.jne_8.label,
				(instr->e.ins_jne.m.jne_8.offset & 0xFF));
			break;
		default:
			break;
	}
}

//===========================================================================
// ins_exp_process
//===========================================================================
PUBLIC	void	pr_ins_call_process(struct ins_str *instr)
{
	switch(instr->e.ins_call.k)
	{	
		case INS_CALL_32:
			printf("0x%x:	call(kind=%d, len=%d, format_1=0x%x, label=%s, offset=0x%x)\n\n", instr->offset,
				instr->e.ins_call.k, instr->e.ins_call.len, 
				instr->e.ins_call.m.call_32.format_1, instr->e.ins_call.m.call_32.label,
				instr->e.ins_call.m.call_32.offset);
			break;
		default:
			break;
	}
}


