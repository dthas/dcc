//===========================================================================
// ins_lib.c
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
// ins_mov_reg_2_imm_32_build
//===========================================================================
PUBLIC	struct ins_mov*	ins_mov_reg_2_imm_32_build(u32 reg, s32 data)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mov_reg_2_imm_32_build(s) -- \n");
#endif
//--------------------------
	struct ins_mov *p	= malloc(sizeof(struct ins_mov));

	p->k			= INS_MOV_REG_2_IMM_32;
	
	p->len			= 5;

	p->m.mov_reg_2_imm_32.data	= data;

	p->m.mov_reg_2_imm_32.format_1	= (0xb8| reg);
	

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mov_reg_2_imm_32_build(e) -- \n\n");
#endif
//--------------------------

	return p;	
}

//===========================================================================
// ins_mov_reg_2_reg_32_build
//===========================================================================
PUBLIC	struct ins_mov*	ins_mov_reg_2_reg_32_build(u32 reg, u32 rm)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mov_reg_2_reg_32_build(s) -- ,reg=0x%x, rm=0x%x\n", reg, rm);
#endif
//--------------------------
	struct ins_mov *p	= malloc(sizeof(struct ins_mov));

	p->k			= INS_MOV_REG_2_REG_32;
	
	p->len			= 2;

	p->m.mov_reg_2_reg_32.format_1		= 0x8b;

	p->m.mov_reg_2_reg_32.format_2		= (((MOD_RM_REG)<<SHIFT_BIT_MOD) | ((reg)<<SHIFT_BIT_REG) | rm);
	

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mov_reg_2_reg_32_build(e) -- \n\n");
#endif
//--------------------------

	return p;	
}


//===========================================================================
// ins_mov_reg_2_mem_32_build
//===========================================================================
PUBLIC	struct ins_mov*	ins_mov_reg_2_mem_32_build(u32 reg, s8 offset)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mov_reg_2_mem_32_build(s) -- \n");
#endif
//--------------------------
	struct ins_mov *p	= malloc(sizeof(struct ins_mov));

	p->k			= INS_MOV_REG_2_MEM_32;
	
	p->len			= 3;

	p->m.mov_reg_2_mem_32.format_1		= 0x8b;

	p->m.mov_reg_2_mem_32.format_2		= (((MOD_OFFSET_8)<<SHIFT_BIT_MOD) | ((reg)<<SHIFT_BIT_REG) | RM_DS_EBP);

	p->m.mov_reg_2_mem_32.offset		= offset;
	

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mov_reg_2_mem_32_build(e) -- \n\n");
#endif
//--------------------------

	return p;	
}


//===========================================================================
// ins_mov_mem_2_reg_32_build
//===========================================================================
PUBLIC	struct ins_mov*	ins_mov_mem_2_reg_32_build(u32 reg, s8 offset)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mov_mem_2_reg_32_build(s) -- \n");
#endif
//--------------------------
	struct ins_mov *p	= malloc(sizeof(struct ins_mov));

	p->k			= INS_MOV_MEM_2_REG_32;
	
	p->len			= 3;

	p->m.mov_mem_2_reg_32.format_1		= 0x89;

	p->m.mov_mem_2_reg_32.format_2		= (((MOD_OFFSET_8)<<SHIFT_BIT_MOD) | ((reg)<<SHIFT_BIT_REG) | RM_DS_EBP);

	p->m.mov_mem_2_reg_32.offset		= offset;
	

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mov_mem_2_reg_32_build(e) -- \n\n");
#endif
//--------------------------

	return p;	
}


//===========================================================================
// ins_mov_numb_2_reg_32_build
//===========================================================================
PUBLIC	struct ins_mov*	ins_mov_numb_2_reg_32_build(u32 reg, u32 addr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mov_numb_2_reg_32_build(s) -- \n");
#endif
//--------------------------
	struct ins_mov *p	= malloc(sizeof(struct ins_mov));

	p->k			= INS_MOV_NUMB_2_REG_32;
	
	p->len			= 6;

	p->m.mov_numb_2_reg_32.format_1		= 0x89;

	p->m.mov_numb_2_reg_32.format_2		= (((MOD_NOOFFSET)<<SHIFT_BIT_MOD) | ((reg)<<SHIFT_BIT_REG) | RM_DS_EBP);

	p->m.mov_numb_2_reg_32.addr		= addr;
	

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mov_numb_2_reg_32_build(e) -- \n\n");
#endif
//--------------------------

	return p;	
}

//===========================================================================
// ins_mov_reg_2_numb_32_build
//===========================================================================
PUBLIC	struct ins_mov*	ins_mov_reg_2_numb_32_build(u32 reg, u32 addr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mov_reg_2_numb_32_build(s) -- \n");
#endif
//--------------------------
	struct ins_mov *p	= malloc(sizeof(struct ins_mov));

	p->k			= INS_MOV_REG_2_NUMB_32;
	
	p->len			= 6;

	p->m.mov_reg_2_numb_32.format_1		= 0x8b;

	p->m.mov_reg_2_numb_32.format_2		= (((MOD_NOOFFSET)<<SHIFT_BIT_MOD) | ((reg)<<SHIFT_BIT_REG) | RM_DS_EBP);

	p->m.mov_reg_2_numb_32.addr		= addr;
	

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mov_reg_2_numb_32_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}


//===========================================================================
// ins_add_reg_2_reg_32_build
//===========================================================================
PUBLIC	struct ins_add*	ins_add_reg_2_reg_32_build(u32 reg, u32 rm)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_add_reg_2_reg_32_build(s) -- \n");
#endif
//--------------------------
	struct ins_add *p	= malloc(sizeof(struct ins_add));

	p->k			= INS_ADD_REG_2_REG_32;
	
	p->len			= 2;

	p->m.add_reg_2_reg_32.format_1		= 0x03;

	p->m.add_reg_2_reg_32.format_2		= (((MOD_RM_REG)<<SHIFT_BIT_MOD) | ((reg)<<SHIFT_BIT_REG) | rm);

	
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_add_reg_2_reg_32_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_add_reg_2_imm_32_build
//===========================================================================
PUBLIC	struct ins_add*	ins_add_reg_2_imm_32_build(u32 rm, s32 data)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_add_reg_2_imm_32_build(s) -- \n");
#endif
//--------------------------
	struct ins_add *p	= malloc(sizeof(struct ins_add));

	p->k			= INS_ADD_REG_2_IMM_32;
	
	p->len			= 6;

	p->m.add_reg_2_imm_32.format_1		= 0x83;

	p->m.add_reg_2_imm_32.format_2		= ((((MOD_RM_REG)<<SHIFT_BIT_MOD) | rm) & 0xc7);	//11000111b

	p->m.add_reg_2_imm_32.data		= data;

	
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_add_reg_2_imm_32_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_add_reg_2_imm_8_build
//===========================================================================
PUBLIC	struct ins_add*	ins_add_reg_2_imm_8_build(u32 rm, s8 data)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_add_reg_2_imm_8_build(s) -- \n");
#endif
//--------------------------
	struct ins_add *p	= malloc(sizeof(struct ins_add));

	p->k			= INS_ADD_REG_2_IMM_8;
	
	p->len			= 3;

	p->m.add_reg_2_imm_8.format_1		= 0x83;

	p->m.add_reg_2_imm_8.format_2		= ((((MOD_RM_REG)<<SHIFT_BIT_MOD) | rm) & 0xc7);	//11000111b

	p->m.add_reg_2_imm_8.data		= data;

	
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_add_reg_2_imm_8_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_push_reg_32_build
//===========================================================================
PUBLIC	struct ins_push*	ins_push_reg_32_build(u32 reg)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_push_reg_32_build(s) -- \n");
#endif
//--------------------------
	struct ins_push *p	= malloc(sizeof(struct ins_push));

	p->k			= INS_PUSH_REG_32;
	
	p->len			= 1;

	p->m.push_reg_32.format_1		= 0x50 | reg;
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_push_reg_32_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}


//===========================================================================
// ins_push_mem_32_build
//===========================================================================
PUBLIC	struct ins_push*	ins_push_mem_32_build(u32 rm, s8 offset)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_push_mem_32_build(s) -- \n");
#endif
//--------------------------
	struct ins_push *p	= malloc(sizeof(struct ins_push));

	p->k			= INS_PUSH_MEM_32;
	
	p->len			= 3;

	p->m.push_mem_32.format_1	= 0xff;

	p->m.push_mem_32.format_2	= (((MOD_OFFSET_8)<<SHIFT_BIT_MOD) | ((0x6)<<SHIFT_BIT_REG) | rm);

	p->m.push_mem_32.offset		= offset;
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_push_mem_32_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}


//===========================================================================
// ins_pop_reg_32_build
//===========================================================================
PUBLIC	struct ins_pop*	ins_pop_reg_32_build(u32 reg)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_pop_reg_32_build(s) -- \n");
#endif
//--------------------------
	struct ins_pop *p	= malloc(sizeof(struct ins_pop));

	p->k			= INS_POP_REG_32;
	
	p->len			= 1;

	p->m.pop_reg_32.format_1		= 0x58 | reg;
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_pop_reg_32_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_call_32_build
//===========================================================================
PUBLIC	struct ins_call*	ins_call_32_build(s8 *label)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_call_32_build(s) -- \n");
#endif
//--------------------------
	struct ins_call *p	= malloc(sizeof(struct ins_call));

	p->k			= INS_CALL_32;
	
	p->len			= 5;

	p->m.call_32.format_1		= 0xe8;

	p->m.call_32.offset		= 0;

	strcopy(p->m.call_32.label, label);
	p->m.call_32.label[strlen(label)]	= NULL;
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_call_32_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_ret_32_build
//===========================================================================
PUBLIC	struct ins_ret*	ins_ret_32_build()
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_ret_32_build(s) -- \n");
#endif
//--------------------------
	struct ins_ret *p	= malloc(sizeof(struct ins_ret));

	p->k			= INS_RET_32;
	
	p->len			= 1;

	p->m.ret_32.format_1		= 0xc3;
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_ret_32_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_xor_reg_2_reg_32_build
//===========================================================================
PUBLIC	struct ins_xor*	ins_xor_reg_2_reg_32_build(u32 reg, u32 rm)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_xor_reg_2_reg_32_build(s) -- \n");
#endif
//--------------------------
	struct ins_xor *p	= malloc(sizeof(struct ins_xor));

	p->k			= INS_XOR_REG_2_REG_32;
	
	p->len			= 2;

	p->m.xor_reg_2_reg_32.format_1		= 0x31;

	p->m.xor_reg_2_reg_32.format_2		= (((MOD_RM_REG)<<SHIFT_BIT_MOD) | ((reg)<<SHIFT_BIT_REG) | rm);
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_xor_reg_2_reg_32_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}


//===========================================================================
// ins_mul_reg_16_build
//===========================================================================
PUBLIC	struct ins_mul*	ins_mul_reg_16_build(u32 rm)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mul_reg_16_build(s) -- \n");
#endif
//--------------------------
	struct ins_mul *p	= malloc(sizeof(struct ins_mul));

	p->k			= INS_MUL_REG_16;
	
	p->len			= 3;

	p->m.mul_reg_16.prefix		= 0x66;

	p->m.mul_reg_16.format_1	= 0xf7;

	p->m.mul_reg_16.format_2	= (((MOD_RM_REG)<<SHIFT_BIT_MOD) | ((0x4)<<SHIFT_BIT_REG) | rm);
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mul_reg_16_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_div_reg_16_build
//===========================================================================
PUBLIC	struct ins_div*	ins_div_reg_16_build(u32 rm)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_div_reg_16_build(s) -- \n");
#endif
//--------------------------
	struct ins_div *p	= malloc(sizeof(struct ins_div));

	p->k			= INS_DIV_REG_16;
	
	p->len			= 3;

	p->m.div_reg_16.prefix		= 0x66;

	p->m.div_reg_16.format_1	= 0xf7;

	p->m.div_reg_16.format_2	= (((MOD_RM_REG)<<SHIFT_BIT_MOD) | ((0x6)<<SHIFT_BIT_REG) | rm);
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_div_reg_16_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_sub_reg_2_reg_32_build
//===========================================================================
PUBLIC	struct ins_sub*	ins_sub_reg_2_reg_32_build(u32 reg, u32 rm)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_sub_reg_2_reg_32_build(s) -- \n");
#endif
//--------------------------
	struct ins_sub *p	= malloc(sizeof(struct ins_sub));

	p->k			= INS_SUB_REG_2_REG_32;
	
	p->len			= 2;

	p->m.sub_reg_2_reg_32.format_1		= 0x2b;

	p->m.sub_reg_2_reg_32.format_2		= (((MOD_RM_REG)<<SHIFT_BIT_MOD) | ((reg)<<SHIFT_BIT_REG) | rm);
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_sub_reg_2_reg_32_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_cmp_reg_2_reg_32_build
//===========================================================================
PUBLIC	struct ins_cmp*	ins_cmp_reg_2_reg_32_build(u32 reg, u32 rm)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_cmp_reg_2_reg_32_build(s) -- \n");
#endif
//--------------------------
	struct ins_cmp *p	= malloc(sizeof(struct ins_cmp));

	p->k			= INS_CMP_REG_2_REG_32;
	
	p->len			= 2;

	p->m.cmp_reg_2_reg_32.format_1		= 0x39;

	p->m.cmp_reg_2_reg_32.format_2		= (((MOD_RM_REG)<<SHIFT_BIT_MOD) | ((rm)<<SHIFT_BIT_REG) | reg);
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_cmp_reg_2_reg_32_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_jmp_8_build
//===========================================================================
PUBLIC	struct ins_jmp*	ins_jmp_8_build(s8 *label)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_jmp_8_build(s) -- \n");
#endif
//--------------------------
	struct ins_jmp *p	= malloc(sizeof(struct ins_jmp));

	p->k			= INS_JMP_8;
	
	p->len			= 2;

	p->m.jmp_8.format_1		= 0xeb;

	p->m.jmp_8.offset		= 0;

	strcopy(p->m.jmp_8.label, label);
	p->m.jmp_8.label[strlen(label)]	= NULL;
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_jmp_8_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_ja_8_build
//===========================================================================
PUBLIC	struct ins_ja*	ins_ja_8_build(s8 *label)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_ja_8_build(s) -- \n");
#endif
//--------------------------
	struct ins_ja *p	= malloc(sizeof(struct ins_ja));

	p->k			= INS_JA_8;
	
	p->len			= 2;

	p->m.ja_8.format_1		= 0x77;

	p->m.ja_8.offset		= 0;

	strcopy(p->m.ja_8.label, label);
	p->m.ja_8.label[strlen(label)]	= NULL;
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_ja_8_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_jae_8_build
//===========================================================================
PUBLIC	struct ins_jae*	ins_jae_8_build(s8 *label)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_jae_8_build(s) -- \n");
#endif
//--------------------------
	struct ins_jae *p	= malloc(sizeof(struct ins_jae));

	p->k			= INS_JAE_8;
	
	p->len			= 2;

	p->m.jae_8.format_1		= 0x73;

	p->m.jae_8.offset		= 0;

	strcopy(p->m.jae_8.label, label);
	p->m.jae_8.label[strlen(label)]	= NULL;
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_jae_8_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_je_8_build
//===========================================================================
PUBLIC	struct ins_je*	ins_je_8_build(s8 *label)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_je_8_build(s) -- \n");
#endif
//--------------------------
	struct ins_je *p	= malloc(sizeof(struct ins_je));

	p->k			= INS_JE_8;
	
	p->len			= 2;

	p->m.je_8.format_1		= 0x74;

	p->m.je_8.offset		= 0;

	strcopy(p->m.je_8.label, label);
	p->m.je_8.label[strlen(label)]	= NULL;
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_je_8_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_jb_8_build
//===========================================================================
PUBLIC	struct ins_jb*	ins_jb_8_build(s8 *label)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_jb_8_build(s) -- \n");
#endif
//--------------------------
	struct ins_jb *p	= malloc(sizeof(struct ins_jb));

	p->k			= INS_JB_8;
	
	p->len			= 2;

	p->m.jb_8.format_1		= 0x72;

	p->m.jb_8.offset		= 0;

	strcopy(p->m.jb_8.label, label);
	p->m.jb_8.label[strlen(label)]	= NULL;
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_jb_8_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_jbe_8_build
//===========================================================================
PUBLIC	struct ins_jbe*	ins_jbe_8_build(s8 *label)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_jbe_8_build(s) -- \n");
#endif
//--------------------------
	struct ins_jbe *p	= malloc(sizeof(struct ins_jbe));

	p->k			= INS_JBE_8;
	
	p->len			= 2;

	p->m.jbe_8.format_1		= 0x76;

	p->m.jbe_8.offset		= 0;

	strcopy(p->m.jbe_8.label, label);
	p->m.jbe_8.label[strlen(label)]	= NULL;
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_jbe_8_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_jne_8_build
//===========================================================================
PUBLIC	struct ins_jne*	ins_jne_8_build(s8 *label)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_jne_8_build(s) -- \n");
#endif
//--------------------------
	struct ins_jne *p	= malloc(sizeof(struct ins_jne));

	p->k			= INS_JNE_8;
	
	p->len			= 2;

	p->m.jne_8.format_1		= 0x75;

	p->m.jne_8.offset		= 0;

	strcopy(p->m.jne_8.label, label);
	p->m.jne_8.label[strlen(label)]	= NULL;
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_jne_8_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

//===========================================================================
// ins_jne_8_build
//===========================================================================
PUBLIC	struct ins_label*	ins_label_32_build(s8* name , s32 offset)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_label_32_build(s) -- \n");
#endif
//--------------------------
	struct ins_label *p	= malloc(sizeof(struct ins_label));

	p->k			= INS_LABEL_32;
	
	p->len			= 0;

	p->m.label.offset	= offset;

	strcopy(&(p->m.label.name), name);
	p->m.label.name[strlen(name)]	= NULL;	
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_label_32_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}


//===========================================================================
// ins_int_imm_8_build
//===========================================================================
PUBLIC	struct ins_int*	ins_int_imm_8_build(u8 data)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_int_imm_8_build(s) -- \n");
#endif
//--------------------------
	struct ins_int *p	= malloc(sizeof(struct ins_int));

	p->k			= INS_INT_8;
	
	p->len			= 2;

	p->m.int_imm_8.format_1	= 0xcd;
	p->m.int_imm_8.data	= data;
		
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_int_imm_8_build(e) -- \n\n");
#endif
//--------------------------	

	return p;
}

