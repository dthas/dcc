//===========================================================================
// dnasm_ins.h
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

#ifndef	_DNASM_INS_H_
#define	_DNASM_INS_H_

#define	INS_NAME_LEN	64
//-------------------------------------------------------------------------
// ins 
//-------------------------------------------------------------------------

// format_1:	------dw
#define	SHIFT_BIT_W	0
#define	SHIFT_BIT_D	1
#define	SHIFT_BIT_OP	2

// format_2:	oorrrmmm
#define	SHIFT_BIT_MOD	6
#define	SHIFT_BIT_REG	3	
#define	SHIFT_BIT_RM	0

// mode
#define	MOD_NOOFFSET	0
#define	MOD_OFFSET_8	1
#define	MOD_OFFSET_32	2
#define	MOD_RM_REG	3

// R/M address method
#define	RM_DS_EAX	0
#define	RM_DS_ECX	1
#define	RM_DS_EDX	2
#define	RM_DS_EBX	3
#define	RM_SPECIAL	4
#define	RM_DS_EBP	5
#define	RM_DS_ESI	6
#define	RM_DS_EDI	7



//-------------------------------------------------------------------------
// variable
//-------------------------------------------------------------------------

#define	INS_LEN		128

#define	REG_NUM		8

#define	REG_EAX		0
#define	REG_ECX		1
#define	REG_EDX		2
#define	REG_EBX		3
#define	REG_ESP		4
#define	REG_EBP		5
#define	REG_ESI		6
#define	REG_EDI		7



enum ins_sts_kind
{
	INS_STS_MOV, INS_STS_ADD, INS_STS_SUB, INS_STS_MUL, INS_STS_DIV, INS_STS_CALL, INS_STS_RET, INS_STS_JMP, INS_STS_JA, 
	INS_STS_JB,  INS_STS_JE,	INS_STS_JAE, INS_STS_JBE, INS_STS_JNE, INS_STS_PUSH, INS_STS_POP, INS_STS_CMP, INS_STS_LABEL,
	INS_STS_XOR, INS_STS_INT
};

enum ins_mov_kind
{
	INS_MOV_REG_2_IMM_32=20, INS_MOV_REG_2_REG_32, INS_MOV_REG_2_MEM_32, INS_MOV_MEM_2_REG_32, INS_MOV_NUMB_2_REG_32, INS_MOV_REG_2_NUMB_32
};

enum ins_add_kind
{
	INS_ADD_REG_2_REG_32=40, INS_ADD_REG_2_IMM_32, INS_ADD_REG_2_IMM_8
};

enum ins_push_kind
{
	INS_PUSH_REG_32=60, INS_PUSH_MEM_32
};

enum ins_pop_kind
{
	INS_POP_REG_32=80
};

enum ins_call_kind
{
	INS_CALL_32=100
};

enum ins_ret_kind
{
	INS_RET_32=120
};

enum ins_xor_kind
{
	INS_XOR_REG_2_REG_32=140
};

enum ins_mul_kind
{
	INS_MUL_REG_16=160
};

enum ins_div_kind
{
	INS_DIV_REG_16=180
};

enum ins_sub_kind
{
	INS_SUB_REG_2_REG_32=200
};

enum ins_cmp_kind
{
	INS_CMP_REG_2_REG_32=220
};

enum ins_ja_kind
{
	INS_JA_8=240
};

enum ins_jmp_kind
{
	INS_JMP_8=260
};

enum ins_jae_kind
{
	INS_JAE_8=280
};

enum ins_je_kind
{
	INS_JE_8=300
};

enum ins_jb_kind
{
	INS_JB_8=320
};

enum ins_jbe_kind
{
	INS_JBE_8=340
};

enum ins_jne_kind
{
	INS_JNE_8=360
};

enum ins_label_kind
{
	INS_LABEL_32=380
};

enum ins_int_kind
{
	INS_INT_8=400
};

//-------------------------------------------------------------------------
// jne
//-------------------------------------------------------------------------

struct ins_jne
{
	enum ins_jne_kind k;
	
	union
	{
		struct{u8 format_1; s8 offset; s8 label[INS_NAME_LEN];} jne_8;			//jne L4
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// jbe
//-------------------------------------------------------------------------

struct ins_jbe
{
	enum ins_jbe_kind k;
	
	union
	{
		struct{u8 format_1; s8 offset; s8 label[INS_NAME_LEN];} jbe_8;			//jbe L4
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// jb
//-------------------------------------------------------------------------

struct ins_jb
{
	enum ins_jb_kind k;
	
	union
	{
		struct{u8 format_1; s8 offset; s8 label[INS_NAME_LEN];} jb_8;			//jb L4
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// je
//-------------------------------------------------------------------------

struct ins_je
{
	enum ins_je_kind k;
	
	union
	{
		struct{u8 format_1; s8 offset; s8 label[INS_NAME_LEN];} je_8;			//je L4
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// jae
//-------------------------------------------------------------------------

struct ins_jae
{
	enum ins_jae_kind k;
	
	union
	{
		struct{u8 format_1; s8 offset; s8 label[INS_NAME_LEN];} jae_8;			//jae L4
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// jmp
//-------------------------------------------------------------------------

struct ins_jmp
{
	enum ins_jmp_kind k;
	
	union
	{
		struct{u8 format_1; s8 offset; s8 label[INS_NAME_LEN];} jmp_8;			//jmp L4
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// ja
//-------------------------------------------------------------------------

struct ins_ja
{
	enum ins_ja_kind k;
	
	union
	{
		struct{u8 format_1; s8 offset; s8 label[INS_NAME_LEN];} ja_8;			//ja L4
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// cmp
//-------------------------------------------------------------------------

struct ins_cmp
{
	enum ins_cmp_kind k;
	
	union
	{
		struct{u8 format_1; u8 format_2;} cmp_reg_2_reg_32;	//cmp edx, ecx
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// sub
//-------------------------------------------------------------------------

struct ins_sub
{
	enum ins_sub_kind k;
	
	union
	{
		struct{u8 format_1; u8 format_2;} sub_reg_2_reg_32;	//sub edx, ecx
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// div
//-------------------------------------------------------------------------

struct ins_div
{
	enum ins_div_kind k;
	
	union
	{
		struct{u8 prefix; u8 format_1; u8 format_2;} div_reg_16;	//div bx
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// mul
//-------------------------------------------------------------------------

struct ins_mul
{
	enum ins_mul_kind k;
	
	union
	{
		struct{u8 prefix; u8 format_1; u8 format_2;} mul_reg_16;	//mul bx
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// xor
//-------------------------------------------------------------------------

struct ins_xor
{
	enum ins_xor_kind k;
	
	union
	{
		struct{u8 format_1; u8 format_2;} xor_reg_2_reg_32;	//xor edx, edx
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// ret
//-------------------------------------------------------------------------

struct ins_ret
{
	enum ins_ret_kind k;
	
	union
	{
		struct{u8 format_1} ret_32;				//ret
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// call
//-------------------------------------------------------------------------

struct ins_call
{
	enum ins_call_kind k;
	
	union
	{
		struct{u8 format_1; s32 offset; s8 label[INS_NAME_LEN];} call_32;				//call L1
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// pop
//-------------------------------------------------------------------------

struct ins_pop
{
	enum ins_pop_kind k;
	
	union
	{
		struct{u8 format_1;} pop_reg_32;				//pop ebp
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// push
//-------------------------------------------------------------------------

struct ins_push
{
	enum ins_push_kind k;
	
	union
	{
		struct{u8 format_1;} push_reg_32;				//push ebp
		struct{u8 format_1; u8 format_2; s8 offset;} push_mem_32;	//push dword[ebp + 0x8]
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// mov
//-------------------------------------------------------------------------

struct ins_mov
{
	enum ins_mov_kind k;
	
	union
	{
		struct{u8 format_1; s32 data;} mov_reg_2_imm_32;		//mov ecx, 3
		struct{u8 format_1; u8 format_2;} mov_reg_2_reg_32;		//mov ebp, eax
		struct{u8 format_1; u8 format_2; s8 offset;} mov_reg_2_mem_32;	//mov eax, dword[ebp + 0x8]
		struct{u8 format_1; u8 format_2; s8 offset;} mov_mem_2_reg_32;	//mov dword[ebp - 0x8], eax
		struct{u8 format_1; u8 format_2; u32 addr;} mov_numb_2_reg_32;	//mov dword[temp_val], ebx
		struct{u8 format_1; u8 format_2; u32 addr;} mov_reg_2_numb_32;	//mov ebx, dword[temp_val]
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// add
//-------------------------------------------------------------------------

struct ins_add
{
	enum ins_add_kind k;
	
	union
	{
		struct{u8 format_1; u8 format_2;} add_reg_2_reg_32;		//add ebx, eax
		struct{u8 format_1; u8 format_2; s32 data;} add_reg_2_imm_32;		//add esp, 4
		struct{u8 format_1; u8 format_2; s8 data;} add_reg_2_imm_8;		//add esp, 4
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// add
//-------------------------------------------------------------------------

struct ins_label
{
	enum ins_label_kind k;
	
	union
	{
		struct{s8 name[INS_NAME_LEN]; s32 offset;} label;		
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// int
//-------------------------------------------------------------------------

struct ins_int
{
	enum ins_int_kind k;
	
	union
	{
		struct{u8 format_1; u8 data} int_imm_8;				//int 0x80
	}m;

	u32  len;
};

//-------------------------------------------------------------------------
// ins_str
//-------------------------------------------------------------------------

struct ins_str
{
	enum ins_sts_kind k;
	s32 offset;
	s8 ins[INS_NAME_LEN];

	union
	{
		struct ins_mov 	ins_mov;
		struct ins_add 	ins_add;
		struct ins_push ins_push;
		struct ins_pop 	ins_pop;
		struct ins_call ins_call;
		struct ins_ret 	ins_ret;
		struct ins_xor 	ins_xor;
		struct ins_mul 	ins_mul;
		struct ins_div 	ins_div;
		struct ins_sub 	ins_sub;
		struct ins_cmp 	ins_cmp;
		struct ins_jmp 	ins_jmp;
		struct ins_ja 	ins_ja;
		struct ins_jae 	ins_jae;
		struct ins_jb 	ins_jb;
		struct ins_jbe 	ins_jbe;
		struct ins_je 	ins_je;
		struct ins_jne 	ins_jne;
		struct ins_label ins_label;
		struct ins_int 	ins_int;
	}e;
};

//-------------------------------------------------------------------------
// ins_sts
//-------------------------------------------------------------------------
struct ins_sts
{
	enum ins_sts_kind k;
	

	union
	{	
		struct{struct ins_str *instr;} mov_sts;
		struct{struct ins_str *instr;} add_sts;
		struct{struct ins_str *instr;} sub_sts;
		struct{struct ins_str *instr;} mul_sts;
		struct{struct ins_str *instr;} div_sts;
		struct{struct ins_str *instr;} call_sts;
		struct{struct ins_str *instr;} ret_sts;
		struct{struct ins_str *instr;} jmp_sts;
		struct{struct ins_str *instr;} ja_sts;
		struct{struct ins_str *instr;} jb_sts;
		struct{struct ins_str *instr;} je_sts;
		struct{struct ins_str *instr;} jae_sts;
		struct{struct ins_str *instr;} jbe_sts;
		struct{struct ins_str *instr;} jne_sts;
		struct{struct ins_str *instr;} push_sts;
		struct{struct ins_str *instr;} pop_sts;
		struct{struct ins_str *instr;} cmp_sts;
		struct{struct ins_str *instr;} label_sts;
		struct{struct ins_str *instr;} xor_sts;
		struct{struct ins_str *instr;} int_sts;
	}s;
};

struct ins_stslist
{
	struct ins_sts *sts;
	struct ins_stslist *head;
	struct ins_stslist *tail;
};

//-------------------------------------------------------------------------
// whole file
//-------------------------------------------------------------------------
struct ins_file
{
	struct ins_stslist *stslist;
	struct ins_file *head;
	struct ins_file *tail;
};


struct ins_file	*icur_file;

s32 sts_kind;

PUBLIC	s32	ins_code_offset;
PUBLIC	s32	ins_data_offset;

PUBLIC	s32 	reltab_offset;
PUBLIC	s32 	strtab_offset;
PUBLIC	s32 	symtab_offset;
#endif
