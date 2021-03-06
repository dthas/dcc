//===========================================================================
// ins_lib.c
//   Copyright (C) 2013 Free Software Foundation, Inc.
//   Originally by ZhaoFeng Liang <zhf.liang@outlook.com>
//
//This file is part of DTAHS_DCC.
//
//DTAHS_DCC is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or 
//(at your option) any later version.
//
//DTAHS_DCC is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with DTHAS; If not, see <http://www.gnu.org/licenses/>.  
//===========================================================================

#include	"dcc_global.h"
#include	"dcc_type.h"
#include	"dcc_symtbl.h"
#include	<stdio.h>
#include	"dcc_main.h"
#include	"dcc_lex_char.h"
#include	"dcc_lex_word.h"
#include	"dcc_parse.h"
#include	"dcc_seman.h"
#include	"dcc_frame.h"
#include	"dcc_ir.h"
#include	"dcc_pasm.h"
#include	"dcc_block.h"
#include	"dcc_ins.h"
#include	"dcc_prototype.h"

#define	INS_DEBUG

PRIVATE	s8 	ins_temp_buf[INS_LEN];
PRIVATE	s8	regs[REG_NUM][4]	= {"eax", "ebx", "ecx", "edx", "esi", "edi"};
//===========================================================================
// ins_add_build
//===========================================================================
PUBLIC	struct ins*	ins_add_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_add_build -- \n");
#endif
//--------------------------

	s8	*src_name, *dst_name, *res_name;
	u32	src_len, dst_len, res_len;	

	src_len	= exp->e.add.src_len;
	dst_len	= exp->e.add.dst_len;

	src_name= exp->e.add.src_name;
	dst_name= exp->e.add.dst_name;
	
	//------------------------------------------------------------------
	// source	:: mov	ebx, byte[src_addr]
	//------------------------------------------------------------------
	s32 total_len	= 0;
	s8	*p	= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);

	s8 src_str[INS_LEN];
	empty_buf(src_str, INS_LEN);
	strcopy(src_str , "\tmov	");
			
	total_len		= strlen(src_str);
	p			= &src_str[total_len];

	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	//1) "mov ebx, byte"
	if(src_len != 0)
	{
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(src_len,  ins_temp_buf);
	
		src_str[total_len]	= ',';
		total_len++;
		src_str[total_len]	= ' ';
		total_len		= strlen(src_str);
		p			= &src_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);
	
		//2)"mov ebx, byte[
		src_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		src_str[total_len]	= ',';
		total_len++;
	}
	
	
	p			= &src_str[total_len];
	strcopy(p ,src_name);
	total_len		+=strlen(p);

	if(src_len)
	{
		//4)"mov ebx, byte[0x111111]
		src_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	src_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

	if(isrcexp)
	{
		strcopy(isrcexp->str ,src_str);
		isrcexp->str[strlen(isrcexp->str)]= NULL;

		isrcexp->head		= NULL;
		isrcexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *isrcelist	= iexplist_build(isrcexp);

	//8)
	ins_add2explist(isrcelist, iexplist);

	//------------------------------------------------------------------
	// dest	::	mov	eax, byte[dst_addr]
	//------------------------------------------------------------------
	
	total_len	= 0;
	p		= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);
		
	s8 dst_str[INS_LEN];
	empty_buf(dst_str, INS_LEN);
	strcopy(dst_str , "\tmov	");

	total_len		= strlen(dst_str);
	p			= &dst_str[total_len];

	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	//1) "mov eax, byte"
	if(dst_len != 0)
	{
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(dst_len,  ins_temp_buf);
	
		dst_str[total_len]	= ',';
		total_len++;
		dst_str[total_len]	= ' ';
		total_len		= strlen(dst_str);
		p			= &dst_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);

		//2)"mov ebx, byte[
		dst_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		dst_str[total_len]	= ',';
		total_len++;
	}
		
	p			= &dst_str[total_len];
	strcopy(p ,dst_name);
	total_len		+=strlen(p);

	if(dst_len)
	{
		//4)"mov ebx, byte[0x111111]
		dst_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	dst_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	idstexp	= malloc(sizeof(struct ins_exp));

	if(idstexp)
	{
		strcopy(idstexp->str ,dst_str);
		idstexp->str[strlen(idstexp->str)]= NULL;

		idstexp->head		= NULL;
		idstexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *idstelist	= iexplist_build(idstexp);

	//8)
	ins_add2explist(idstelist, iexplist);

	//------------------------------------------------------------------
	// result	::add	eax, ebx
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);	

	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tadd	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,", ");
	total_len		+=strlen(p);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	iresexp	= malloc(sizeof(struct ins_exp));

	if(iresexp)
	{
		strcopy(iresexp->str ,ins_temp_buf);
		iresexp->str[strlen(iresexp->str)]= NULL;

		iresexp->head		= NULL;
		iresexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ireselist	= iexplist_build(iresexp);

	//4)
	ins_add2explist(ireselist, iexplist);	

	//------------------------------------------------------------------
	// result is saved to dst:: mov byte[0x111111], eax
	//------------------------------------------------------------------
	
	if(dst_len != 0)
	{
		res_name	= dst_name;
		res_len		= dst_len;
	}
	else
	{
		res_name	= src_name;
		res_len		= src_len;
	}	

	total_len	= 0;
	p		= NULL;

	s8 ret_str[INS_LEN];
	empty_buf(ret_str, INS_LEN);

	if(sts_kind == INS_JUMP_RETURN)
	{
		strcopy(ret_str , "\tmov	eax, eax");
		ret_str[strlen(ret_str)]= NULL;
	}
	else
	{
		//1) "mov	dword[temp_val], "
		strcopy(ret_str , "\tmov	dword[temp_val], ");
		total_len		= strlen(ret_str);

		//2)"mov byte[0x111111], eax
		p			= &ret_str[total_len];
		strcopy(p ,&regs[reg_dst]);
		total_len		+=strlen(p);
	
		//3)"mov byte[0x111111]
		ret_str[total_len]	= NULL;		
	}

	//6)
	struct ins_exp*	iretexp	= malloc(sizeof(struct ins_exp));

	if(iretexp)
	{
		strcopy(iretexp->str ,ret_str);
		iretexp->str[strlen(iretexp->str)]= NULL;

		iretexp->head		= NULL;
		iretexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *iretelist	= iexplist_build(iretexp);

	//8)
	ins_add2explist(iretelist, iexplist);
}


//===========================================================================
// ins_minus_build
//===========================================================================
PUBLIC	struct ins*	ins_minus_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_minus_build -- \n");
#endif
//--------------------------

	s32 total_len	= 0;
	s8	*p	= NULL;

	s8	*src_name, *dst_name, *res_name;
	u32	src_len, dst_len, res_len;	

	src_len	= exp->e.minus.src_len;
	dst_len	= exp->e.minus.dst_len;

	src_name= exp->e.minus.src_name;
	dst_name= exp->e.minus.dst_name;

	//------------------------------------------------------------------
	// mov	ebx, byte[src_addr]
	//------------------------------------------------------------------
	
	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);
		
	s8 src_str[INS_LEN];
	empty_buf(src_str, INS_LEN);
	strcopy(src_str , "\tmov	");

	total_len		= strlen(src_str);
	p			= &src_str[total_len];

	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	//1) "mov ebx, byte"
	if(src_len != 0)
	{
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(src_len,  ins_temp_buf);
	
		src_str[total_len]	= ',';
		total_len++;
		src_str[total_len]	= ' ';
		total_len		= strlen(src_str);
		p			= &src_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);

		//2)"mov ebx, byte[
		src_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		src_str[total_len]	= ',';
		total_len++;
	}

		
	p			= &src_str[total_len];
	strcopy(p ,src_name);
	total_len		+=strlen(p);

	if(src_len != 0)
	{
		//4)"mov ebx, byte[0x111111]
		src_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	src_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

	if(isrcexp)
	{
		strcopy(isrcexp->str ,src_str);
		isrcexp->str[strlen(isrcexp->str)]= NULL;

		isrcexp->head		= NULL;
		isrcexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *isrcelist	= iexplist_build(isrcexp);

	//8)
	ins_add2explist(isrcelist, iexplist);

	//------------------------------------------------------------------
	// mov	eax, byte[dst_addr]
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);
		
	s8 dst_str[INS_LEN];
	empty_buf(dst_str, INS_LEN);
	strcopy(dst_str , "\tmov	");

	total_len		= strlen(dst_str);
	p			= &dst_str[total_len];

	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	if(dst_len != 0)
	{
		//1) "mov eax, byte"
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(dst_len,  ins_temp_buf);
	
		dst_str[total_len]	= ',';
		total_len++;
		dst_str[total_len]	= ' ';
		total_len		= strlen(dst_str);
		p			= &dst_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);

		//2)"mov ebx, byte[
		dst_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		dst_str[total_len]	= ',';
		total_len++;
	}
		
	p			= &dst_str[total_len];
	strcopy(p ,dst_name);
	total_len		+=strlen(p);	

	if(dst_len != 0)
	{
		//4)"mov ebx, byte[0x111111]
		dst_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	dst_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	idstexp	= malloc(sizeof(struct ins_exp));

	if(idstexp)
	{
		strcopy(idstexp->str ,dst_str);
		idstexp->str[strlen(idstexp->str)]= NULL;

		idstexp->head		= NULL;
		idstexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *idstelist	= iexplist_build(idstexp);

	//8)
	ins_add2explist(idstelist, iexplist);

	//------------------------------------------------------------------
	// minus	eax, ebx
	//------------------------------------------------------------------
	
	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);

	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tsub	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,", ");
	total_len		+=strlen(p);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	iresexp	= malloc(sizeof(struct ins_exp));

	if(iresexp)
	{
		strcopy(iresexp->str ,ins_temp_buf);
		iresexp->str[strlen(iresexp->str)]= NULL;

		iresexp->head		= NULL;
		iresexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ireselist	= iexplist_build(iresexp);

	//4)
	ins_add2explist(ireselist, iexplist);

	//------------------------------------------------------------------
	// result is saved to dst:: mov byte[0x111111], eax
	//------------------------------------------------------------------
	
	if(dst_len != 0)
	{
		res_name	= dst_name;
		res_len		= dst_len;
	}
	else
	{
		res_name	= src_name;
		res_len		= src_len;
	}
	
	total_len	= 0;
	p		= NULL;

	s8 ret_str[INS_LEN];
	empty_buf(ret_str, INS_LEN);

	if(sts_kind == INS_JUMP_RETURN)
	{
		strcopy(ret_str , "\tmov	eax, eax");
		ret_str[strlen(ret_str)]= NULL;
	}
	else
	{
		//1) "mov	dword[temp_val], "
		strcopy(ret_str , "\tmov	dword[temp_val], ");
		total_len		= strlen(ret_str);

		//2)"mov byte[0x111111], eax
		p			= &ret_str[total_len];
		strcopy(p ,&regs[reg_src]);
		total_len		+=strlen(p);
	
		//3)"mov byte[0x111111]
		ret_str[total_len]	= NULL;		
	}

	//6)
	struct ins_exp*	iretexp	= malloc(sizeof(struct ins_exp));

	if(iretexp)
	{
		strcopy(iretexp->str ,ret_str);
		iretexp->str[strlen(iretexp->str)]= NULL;

		iretexp->head		= NULL;
		iretexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *iretelist	= iexplist_build(iretexp);

	//8)
	ins_add2explist(iretelist, iexplist);
}


//===========================================================================
// ins_mul_build
//===========================================================================
PUBLIC	struct ins*	ins_mul_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mul_build -- \n");
#endif
//--------------------------

	s32 total_len	= 0;
	s8	*p	= NULL;	
	
	s8	*src_name, *dst_name, *res_name;
	u32	src_len, dst_len, res_len;	

	src_len	= exp->e.mul.src_len;
	dst_len	= exp->e.mul.dst_len;

	src_name= exp->e.mul.src_name;
	dst_name= exp->e.mul.dst_name;

	//------------------------------------------------------------------
	// push	eax
	//------------------------------------------------------------------
	s8 push_str[INS_LEN];
	empty_buf(push_str, INS_LEN);
	strcopy(push_str , "\tpush	eax");

	push_str[strlen(push_str)]	= NULL;
	
	//2)
	struct ins_exp* ipushexp	= malloc(sizeof(struct ins_exp));

	if(ipushexp)
	{
		strcopy(ipushexp->str ,push_str);
		ipushexp->str[strlen(ipushexp->str)]= NULL;

		ipushexp->head		= NULL;
		ipushexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ipushlist	= iexplist_build(ipushexp);

	//4)
	ins_add2explist(ipushlist, iexplist);

	//------------------------------------------------------------------
	// push	ebx
	//------------------------------------------------------------------
	empty_buf(push_str, INS_LEN);
	strcopy(push_str , "\tpush	ebx");

	push_str[strlen(push_str)]	= NULL;
	
	//2)
	ipushexp	= malloc(sizeof(struct ins_exp));

	if(ipushexp)
	{
		strcopy(ipushexp->str ,push_str);
		ipushexp->str[strlen(ipushexp->str)]= NULL;

		ipushexp->head		= NULL;
		ipushexp->tail		= NULL;		
	}

	//3)
	ipushlist	= iexplist_build(ipushexp);

	//4)
	ins_add2explist(ipushlist, iexplist);

	//------------------------------------------------------------------
	// push	edx
	//------------------------------------------------------------------
	empty_buf(push_str, INS_LEN);
	strcopy(push_str , "\tpush	edx");

	push_str[strlen(push_str)]	= NULL;
	
	//2)
	ipushexp	= malloc(sizeof(struct ins_exp));

	if(ipushexp)
	{
		strcopy(ipushexp->str ,push_str);
		ipushexp->str[strlen(ipushexp->str)]= NULL;

		ipushexp->head		= NULL;
		ipushexp->tail		= NULL;		
	}

	//3)
	ipushlist	= iexplist_build(ipushexp);

	//4)
	ins_add2explist(ipushlist, iexplist);

	//------------------------------------------------------------------
	// xor	edx, edx
	//------------------------------------------------------------------
	empty_buf(push_str, INS_LEN);
	strcopy(push_str , "\txor	edx, edx");

	push_str[strlen(push_str)]	= NULL;
	
	//2)
	ipushexp	= malloc(sizeof(struct ins_exp));

	if(ipushexp)
	{
		strcopy(ipushexp->str ,push_str);
		ipushexp->str[strlen(ipushexp->str)]= NULL;

		ipushexp->head		= NULL;
		ipushexp->tail		= NULL;		
	}

	//3)
	ipushlist	= iexplist_build(ipushexp);

	//4)
	ins_add2explist(ipushlist, iexplist);

	//------------------------------------------------------------------
	// mov	ebx, byte[src_addr]
	//------------------------------------------------------------------
	
	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);
		
	s8 src_str[INS_LEN];
	empty_buf(src_str, INS_LEN);
	strcopy(src_str , "\tmov	");

	total_len		= strlen(src_str);
	p			= &src_str[total_len];

	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	if(src_len != 0)
	{
		//1) "mov ebx, byte"
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(src_len,  ins_temp_buf);
	
		src_str[total_len]	= ',';
		total_len++;
		src_str[total_len]	= ' ';
		total_len		= strlen(src_str);
		p			= &src_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);

		//2)"mov ebx, byte[
		src_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		src_str[total_len]	= ',';
		total_len++;
	}
		
	p			= &src_str[total_len];
	strcopy(p ,src_name);
	total_len		+=strlen(p);

	if(src_len != 0)
	{
		//4)"mov ebx, byte[0x111111]
		src_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	src_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

	if(isrcexp)
	{
		strcopy(isrcexp->str ,src_str);
		isrcexp->str[strlen(isrcexp->str)]= NULL;

		isrcexp->head		= NULL;
		isrcexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *isrcelist	= iexplist_build(isrcexp);

	//8)
	ins_add2explist(isrcelist, iexplist);

	//------------------------------------------------------------------
	// mov	eax, byte[dst_addr]
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);
		
	s8 dst_str[INS_LEN];
	empty_buf(dst_str, INS_LEN);
	strcopy(dst_str , "\tmov	");

	total_len		= strlen(dst_str);
	p			= &dst_str[total_len];

	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	if(dst_len != 0)
	{
		//1) "mov eax, byte"
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(dst_len,  ins_temp_buf);
	
		dst_str[total_len]	= ',';
		total_len++;
		dst_str[total_len]	= ' ';
		total_len		= strlen(dst_str);
		p			= &dst_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);

		//2)"mov ebx, byte[
		dst_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		dst_str[total_len]	= ',';
		total_len++;
	}
		
	p			= &dst_str[total_len];
	strcopy(p ,dst_name);
	total_len		+=strlen(p);


	if(dst_len != 0)
	{
		//4)"mov ebx, byte[0x111111]
		dst_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	dst_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	idstexp	= malloc(sizeof(struct ins_exp));

	if(idstexp)
	{
		strcopy(idstexp->str ,dst_str);
		idstexp->str[strlen(idstexp->str)]= NULL;

		idstexp->head		= NULL;
		idstexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *idstelist	= iexplist_build(idstexp);

	//8)
	ins_add2explist(idstelist, iexplist);

	//------------------------------------------------------------------
	// mul	eax, ebx
	//------------------------------------------------------------------
	
	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	strcopy(ins_temp_buf, "\tmul	bx");
	total_len		=strlen(ins_temp_buf);
	ins_temp_buf[total_len]	= NULL;

	
	//2)
	struct ins_exp*	iresexp	= malloc(sizeof(struct ins_exp));

	if(iresexp)
	{
		strcopy(iresexp->str ,ins_temp_buf);
		iresexp->str[strlen(iresexp->str)]= NULL;

		iresexp->head		= NULL;
		iresexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ireselist	= iexplist_build(iresexp);

	//4)
	ins_add2explist(ireselist, iexplist);

	//------------------------------------------------------------------
	// result is saved to dst:: mov byte[0x111111], eax
	//------------------------------------------------------------------
	
	if(dst_len != 0)
	{
		res_name	= dst_name;
		res_len		= dst_len;
	}
	else
	{
		res_name	= src_name;
		res_len		= src_len;
	}
	
	total_len	= 0;
	p		= NULL;

	s8 ret_str[INS_LEN];
	empty_buf(ret_str, INS_LEN);

	if(sts_kind == INS_JUMP_RETURN)
	{
		strcopy(ret_str , "\tmov	eax, eax");
		ret_str[strlen(ret_str)]= NULL;
	}
	else
	{
		//1) "mov	dword[temp_val], "
		strcopy(ret_str , "\tmov	dword[temp_val], ");
		total_len		= strlen(ret_str);

		//2)"mov byte[0x111111], eax
		p			= &ret_str[total_len];
		strcopy(p ,&regs[reg_dst]);
		total_len		+=strlen(p);
	
		//3)"mov byte[0x111111]
		ret_str[total_len]	= NULL;		
	}

	//6)
	struct ins_exp*	iretexp	= malloc(sizeof(struct ins_exp));

	if(iretexp)
	{
		strcopy(iretexp->str ,ret_str);
		iretexp->str[strlen(iretexp->str)]= NULL;

		iretexp->head		= NULL;
		iretexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *iretelist	= iexplist_build(iretexp);

	//8)
	ins_add2explist(iretelist, iexplist);

	//------------------------------------------------------------------
	// pop	edx
	//------------------------------------------------------------------
	s8 pop_str[INS_LEN];
	empty_buf(pop_str, INS_LEN);
	strcopy(pop_str , "\tpop	edx");

	pop_str[strlen(pop_str)]	= NULL;
	
	//2)
	struct ins_exp* ipopexp	= malloc(sizeof(struct ins_exp));

	if(ipopexp)
	{
		strcopy(ipopexp->str ,pop_str);
		ipopexp->str[strlen(ipopexp->str)]= NULL;

		ipopexp->head		= NULL;
		ipopexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ipoplist	= iexplist_build(ipopexp);

	//4)
	ins_add2explist(ipoplist, iexplist);

	//------------------------------------------------------------------
	// pop	ebx
	//------------------------------------------------------------------
	pop_str[INS_LEN];
	empty_buf(pop_str, INS_LEN);
	strcopy(pop_str , "\tpop	ebx");

	pop_str[strlen(pop_str)]	= NULL;
	
	//2)
	ipopexp	= malloc(sizeof(struct ins_exp));

	if(ipopexp)
	{
		strcopy(ipopexp->str ,pop_str);
		ipopexp->str[strlen(ipopexp->str)]= NULL;

		ipopexp->head		= NULL;
		ipopexp->tail		= NULL;		
	}

	//3)
	ipoplist	= iexplist_build(ipopexp);

	//4)
	ins_add2explist(ipoplist, iexplist);

	//------------------------------------------------------------------
	// pop	eax
	//------------------------------------------------------------------
	pop_str[INS_LEN];
	empty_buf(pop_str, INS_LEN);
	strcopy(pop_str , "\tpop	eax\n");

	pop_str[strlen(pop_str)]	= NULL;
	
	//2)
	ipopexp	= malloc(sizeof(struct ins_exp));

	if(ipopexp)
	{
		strcopy(ipopexp->str ,pop_str);
		ipopexp->str[strlen(ipopexp->str)]= NULL;

		ipopexp->head		= NULL;
		ipopexp->tail		= NULL;		
	}

	//3)
	ipoplist	= iexplist_build(ipopexp);

	//4)
	ins_add2explist(ipoplist, iexplist);
}


//===========================================================================
// ins_div_build
//===========================================================================
PUBLIC	struct ins*	ins_div_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_div_build -- \n");
#endif
//--------------------------

	s32 total_len	= 0;
	s8	*p	= NULL;	
	
	s8	*src_name, *dst_name, *res_name;
	u32	src_len, dst_len, res_len;	

	src_len	= exp->e.div.src_len;
	dst_len	= exp->e.div.dst_len;

	src_name= exp->e.div.src_name;
	dst_name= exp->e.div.dst_name;
	
	//------------------------------------------------------------------
	// push	eax
	//------------------------------------------------------------------
	s8 push_str[INS_LEN];
	empty_buf(push_str, INS_LEN);
	strcopy(push_str , "\tpush	eax");

	push_str[strlen(push_str)]	= NULL;
	
	//2)
	struct ins_exp* ipushexp	= malloc(sizeof(struct ins_exp));

	if(ipushexp)
	{
		strcopy(ipushexp->str ,push_str);
		ipushexp->str[strlen(ipushexp->str)]= NULL;

		ipushexp->head		= NULL;
		ipushexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ipushlist	= iexplist_build(ipushexp);

	//4)
	ins_add2explist(ipushlist, iexplist);

	//------------------------------------------------------------------
	// push	ebx
	//------------------------------------------------------------------
	empty_buf(push_str, INS_LEN);
	strcopy(push_str , "\tpush	ebx");

	push_str[strlen(push_str)]	= NULL;
	
	//2)
	ipushexp	= malloc(sizeof(struct ins_exp));

	if(ipushexp)
	{
		strcopy(ipushexp->str ,push_str);
		ipushexp->str[strlen(ipushexp->str)]= NULL;

		ipushexp->head		= NULL;
		ipushexp->tail		= NULL;		
	}

	//3)
	ipushlist	= iexplist_build(ipushexp);

	//4)
	ins_add2explist(ipushlist, iexplist);

	//------------------------------------------------------------------
	// push	edx
	//------------------------------------------------------------------
	empty_buf(push_str, INS_LEN);
	strcopy(push_str , "\tpush	edx");

	push_str[strlen(push_str)]	= NULL;
	
	//2)
	ipushexp	= malloc(sizeof(struct ins_exp));

	if(ipushexp)
	{
		strcopy(ipushexp->str ,push_str);
		ipushexp->str[strlen(ipushexp->str)]= NULL;

		ipushexp->head		= NULL;
		ipushexp->tail		= NULL;		
	}

	//3)
	ipushlist	= iexplist_build(ipushexp);

	//4)
	ins_add2explist(ipushlist, iexplist);

	//------------------------------------------------------------------
	// xor	edx, edx
	//------------------------------------------------------------------
	empty_buf(push_str, INS_LEN);
	strcopy(push_str , "\txor	edx, edx");

	push_str[strlen(push_str)]	= NULL;
	
	//2)
	ipushexp	= malloc(sizeof(struct ins_exp));

	if(ipushexp)
	{
		strcopy(ipushexp->str ,push_str);
		ipushexp->str[strlen(ipushexp->str)]= NULL;

		ipushexp->head		= NULL;
		ipushexp->tail		= NULL;		
	}

	//3)
	ipushlist	= iexplist_build(ipushexp);

	//4)
	ins_add2explist(ipushlist, iexplist);

	//------------------------------------------------------------------
	// mov	ebx, byte[src_addr]
	//------------------------------------------------------------------
	
	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);
		
	s8 src_str[INS_LEN];
	empty_buf(src_str, INS_LEN);
	strcopy(src_str , "\tmov	");

	total_len		= strlen(src_str);
	p			= &src_str[total_len];

	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	if(src_len != 0)
	{
		//1) "mov ebx, byte"
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(src_len,  ins_temp_buf);
	
		src_str[total_len]	= ',';
		total_len++;
		src_str[total_len]	= ' ';
		total_len		= strlen(src_str);
		p			= &src_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);


		//2)"mov ebx, byte[
		src_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		src_str[total_len]	= ',';
		total_len++;
	}
		
	p			= &src_str[total_len];
	strcopy(p ,src_name);
	total_len		+=strlen(p);

	if(src_len != 0)
	{
		//4)"mov ebx, byte[0x111111]
		src_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	src_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

	if(isrcexp)
	{
		strcopy(isrcexp->str ,src_str);
		isrcexp->str[strlen(isrcexp->str)]= NULL;

		isrcexp->head		= NULL;
		isrcexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *isrcelist	= iexplist_build(isrcexp);

	//8)
	ins_add2explist(isrcelist, iexplist);

	//------------------------------------------------------------------
	// mov	eax, byte[dst_addr]
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);
		
	s8 dst_str[INS_LEN];
	empty_buf(dst_str, INS_LEN);
	strcopy(dst_str , "\tmov	");

	total_len		= strlen(dst_str);
	p			= &dst_str[total_len];

	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	if(dst_len != 0)
	{
		//1) "mov eax, byte"
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(dst_len,  ins_temp_buf);
	
		dst_str[total_len]	= ',';
		total_len++;
		dst_str[total_len]	= ' ';
		total_len		= strlen(dst_str);
		p			= &dst_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);

		//2)"mov ebx, byte[
		dst_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		dst_str[total_len]	= ',';
		total_len++;
	}
		
	p			= &dst_str[total_len];
	strcopy(p ,dst_name);
	total_len		+=strlen(p);


	if(dst_len != 0)
	{
		//4)"mov ebx, byte[0x111111]
		dst_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	dst_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	idstexp	= malloc(sizeof(struct ins_exp));

	if(idstexp)
	{
		strcopy(idstexp->str ,dst_str);
		idstexp->str[strlen(idstexp->str)]= NULL;

		idstexp->head		= NULL;
		idstexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *idstelist	= iexplist_build(idstexp);

	//8)
	ins_add2explist(idstelist, iexplist);

	//------------------------------------------------------------------
	// div	ebx
	//------------------------------------------------------------------
	
	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	strcopy(ins_temp_buf, "\tdiv	bx");
	total_len		=strlen(ins_temp_buf);
	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	iresexp	= malloc(sizeof(struct ins_exp));

	if(iresexp)
	{
		strcopy(iresexp->str ,ins_temp_buf);
		iresexp->str[strlen(iresexp->str)]= NULL;

		iresexp->head		= NULL;
		iresexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ireselist	= iexplist_build(iresexp);

	//4)
	ins_add2explist(ireselist, iexplist);

	//------------------------------------------------------------------
	// result is saved to dst:: mov byte[0x111111], eax
	//------------------------------------------------------------------	
	
	if(dst_len != 0)
	{
		res_name	= dst_name;
		res_len		= dst_len;
	}
	else
	{
		res_name	= src_name;
		res_len		= src_len;
	}
	
	total_len	= 0;
	p		= NULL;

	s8 ret_str[INS_LEN];
	empty_buf(ret_str, INS_LEN);

	if(sts_kind == INS_JUMP_RETURN)
	{
		strcopy(ret_str , "\tmov	eax, eax");
		ret_str[strlen(ret_str)]= NULL;
	}
	else
	{
		//1) "mov	dword[temp_val], "
		strcopy(ret_str , "\tmov	dword[temp_val], ");
		total_len		= strlen(ret_str);

		//2)"mov byte[0x111111], eax
		p			= &ret_str[total_len];

		strcopy(p , "eax");

		total_len		+=strlen(p);
	
		//3)"mov byte[0x111111]
		ret_str[total_len]	= NULL;		
	}
	
	//6)
	struct ins_exp*	iretexp	= malloc(sizeof(struct ins_exp));

	if(iretexp)
	{
		strcopy(iretexp->str ,ret_str);
		iretexp->str[strlen(iretexp->str)]= NULL;

		iretexp->head		= NULL;
		iretexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *iretelist	= iexplist_build(iretexp);

	//8)
	ins_add2explist(iretelist, iexplist);

	//------------------------------------------------------------------
	// pop	edx
	//------------------------------------------------------------------
	s8 pop_str[INS_LEN];
	empty_buf(pop_str, INS_LEN);
	strcopy(pop_str , "\tpop	edx");

	pop_str[strlen(pop_str)]	= NULL;
	
	//2)
	struct ins_exp* ipopexp	= malloc(sizeof(struct ins_exp));

	if(ipopexp)
	{
		strcopy(ipopexp->str ,pop_str);
		ipopexp->str[strlen(ipopexp->str)]= NULL;

		ipopexp->head		= NULL;
		ipopexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ipoplist	= iexplist_build(ipopexp);

	//4)
	ins_add2explist(ipoplist, iexplist);

	//------------------------------------------------------------------
	// pop	ebx
	//------------------------------------------------------------------
	pop_str[INS_LEN];
	empty_buf(pop_str, INS_LEN);
	strcopy(pop_str , "\tpop	ebx");

	pop_str[strlen(pop_str)]	= NULL;
	
	//2)
	ipopexp	= malloc(sizeof(struct ins_exp));

	if(ipopexp)
	{
		strcopy(ipopexp->str ,pop_str);
		ipopexp->str[strlen(ipopexp->str)]= NULL;

		ipopexp->head		= NULL;
		ipopexp->tail		= NULL;		
	}

	//3)
	ipoplist	= iexplist_build(ipopexp);

	//4)
	ins_add2explist(ipoplist, iexplist);

	//------------------------------------------------------------------
	// pop	eax
	//------------------------------------------------------------------
	pop_str[INS_LEN];
	empty_buf(pop_str, INS_LEN);
	strcopy(pop_str , "\tpop	eax\n");

	pop_str[strlen(pop_str)]	= NULL;
	
	//2)
	ipopexp	= malloc(sizeof(struct ins_exp));

	if(ipopexp)
	{
		strcopy(ipopexp->str ,pop_str);
		ipopexp->str[strlen(ipopexp->str)]= NULL;

		ipopexp->head		= NULL;
		ipopexp->tail		= NULL;		
	}

	//3)
	ipoplist	= iexplist_build(ipopexp);

	//4)
	ins_add2explist(ipoplist, iexplist);
}


//===========================================================================
// ins_mod_build
//===========================================================================
PUBLIC	struct ins*	ins_mod_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mod_build -- \n");
#endif
//--------------------------

	s32 total_len	= 0;
	s8	*p	= NULL;

	s8	*src_name, *dst_name, *res_name;
	u32	src_len, dst_len, res_len;	

	src_len	= exp->e.mod.src_len;
	dst_len	= exp->e.mod.dst_len;

	src_name= exp->e.mod.src_name;
	dst_name= exp->e.mod.dst_name;

	//------------------------------------------------------------------
	// push	eax
	//------------------------------------------------------------------
	s8 push_str[INS_LEN];
	empty_buf(push_str, INS_LEN);
	strcopy(push_str , "\tpush	eax");

	push_str[strlen(push_str)]	= NULL;
	
	//2)
	struct ins_exp* ipushexp	= malloc(sizeof(struct ins_exp));

	if(ipushexp)
	{
		strcopy(ipushexp->str ,push_str);
		ipushexp->str[strlen(ipushexp->str)]= NULL;

		ipushexp->head		= NULL;
		ipushexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ipushlist	= iexplist_build(ipushexp);

	//4)
	ins_add2explist(ipushlist, iexplist);

	//------------------------------------------------------------------
	// push	ebx
	//------------------------------------------------------------------
	empty_buf(push_str, INS_LEN);
	strcopy(push_str , "\tpush	ebx");

	push_str[strlen(push_str)]	= NULL;
	
	//2)
	ipushexp	= malloc(sizeof(struct ins_exp));

	if(ipushexp)
	{
		strcopy(ipushexp->str ,push_str);
		ipushexp->str[strlen(ipushexp->str)]= NULL;

		ipushexp->head		= NULL;
		ipushexp->tail		= NULL;		
	}

	//3)
	ipushlist	= iexplist_build(ipushexp);

	//4)
	ins_add2explist(ipushlist, iexplist);

	//------------------------------------------------------------------
	// push	edx
	//------------------------------------------------------------------
	empty_buf(push_str, INS_LEN);
	strcopy(push_str , "\tpush	edx");

	push_str[strlen(push_str)]	= NULL;
	
	//2)
	ipushexp	= malloc(sizeof(struct ins_exp));

	if(ipushexp)
	{
		strcopy(ipushexp->str ,push_str);
		ipushexp->str[strlen(ipushexp->str)]= NULL;

		ipushexp->head		= NULL;
		ipushexp->tail		= NULL;		
	}

	//3)
	ipushlist	= iexplist_build(ipushexp);

	//4)
	ins_add2explist(ipushlist, iexplist);

	//------------------------------------------------------------------
	// xor	edx, edx
	//------------------------------------------------------------------
	empty_buf(push_str, INS_LEN);
	strcopy(push_str , "\txor	edx, edx");

	push_str[strlen(push_str)]	= NULL;
	
	//2)
	ipushexp	= malloc(sizeof(struct ins_exp));

	if(ipushexp)
	{
		strcopy(ipushexp->str ,push_str);
		ipushexp->str[strlen(ipushexp->str)]= NULL;

		ipushexp->head		= NULL;
		ipushexp->tail		= NULL;		
	}

	//3)
	ipushlist	= iexplist_build(ipushexp);

	//4)
	ins_add2explist(ipushlist, iexplist);

	//------------------------------------------------------------------
	// mov	ebx, byte[src_addr]
	//------------------------------------------------------------------
	
	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);
		
	s8 src_str[INS_LEN];
	empty_buf(src_str, INS_LEN);
	strcopy(src_str , "\tmov	");

	total_len		= strlen(src_str);
	p			= &src_str[total_len];

	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	if(src_len != 0)
	{
		//1) "mov ebx, byte"
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(src_len,  ins_temp_buf);
	
		src_str[total_len]	= ',';
		total_len++;
		src_str[total_len]	= ' ';
		total_len		= strlen(src_str);
		p			= &src_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);


		//2)"mov ebx, byte[
		src_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		src_str[total_len]	= ',';
		total_len++;
	}
		
	p			= &src_str[total_len];
	strcopy(p ,src_name);
	total_len		+=strlen(p);


	if(src_len != 0)
	{
		//4)"mov ebx, byte[0x111111]
		src_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	src_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

	if(isrcexp)
	{
		strcopy(isrcexp->str ,src_str);
		isrcexp->str[strlen(isrcexp->str)]= NULL;

		isrcexp->head		= NULL;
		isrcexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *isrcelist	= iexplist_build(isrcexp);

	//8)
	ins_add2explist(isrcelist, iexplist);

	//------------------------------------------------------------------
	// mov	eax, byte[dst_addr]
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);
		
	s8 dst_str[INS_LEN];
	empty_buf(dst_str, INS_LEN);
	strcopy(dst_str , "\tmov	");

	total_len		= strlen(dst_str);
	p			= &dst_str[total_len];

	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	if(dst_len != 0)
	{
		//1) "mov eax, byte"
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(dst_len,  ins_temp_buf);
	
		dst_str[total_len]	= ',';
		total_len++;
		dst_str[total_len]	= ' ';
		total_len		= strlen(dst_str);
		p			= &dst_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);

		//2)"mov ebx, byte[
		dst_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		dst_str[total_len]	= ',';
		total_len++;
	}
		
	p			= &dst_str[total_len];
	strcopy(p ,dst_name);
	total_len		+=strlen(p);

	if(dst_len != 0)
	{
		//4)"mov ebx, byte[0x111111]
		dst_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	dst_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	idstexp	= malloc(sizeof(struct ins_exp));

	if(idstexp)
	{
		strcopy(idstexp->str ,dst_str);
		idstexp->str[strlen(idstexp->str)]= NULL;

		idstexp->head		= NULL;
		idstexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *idstelist	= iexplist_build(idstexp);

	//8)
	ins_add2explist(idstelist, iexplist);

	//------------------------------------------------------------------
	// mod	eax, ebx
	//------------------------------------------------------------------
	
	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	strcopy(ins_temp_buf, "\tdiv	bx");
	total_len		=strlen(ins_temp_buf);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	iresexp	= malloc(sizeof(struct ins_exp));

	if(iresexp)
	{
		strcopy(iresexp->str ,ins_temp_buf);
		iresexp->str[strlen(iresexp->str)]= NULL;

		iresexp->head		= NULL;
		iresexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ireselist	= iexplist_build(iresexp);

	//4)
	ins_add2explist(ireselist, iexplist);

	//------------------------------------------------------------------
	// result is saved to dst:: mov byte[0x111111], eax
	//------------------------------------------------------------------	
	
	if(dst_len != 0)
	{
		res_name	= dst_name;
		res_len		= dst_len;
	}
	else
	{
		res_name	= src_name;
		res_len		= src_len;
	}
	
	total_len	= 0;
	p		= NULL;

	s8 ret_str[INS_LEN];
	empty_buf(ret_str, INS_LEN);

	if(sts_kind == INS_JUMP_RETURN)
	{
		strcopy(ret_str , "\tmov	eax, eax");
		ret_str[strlen(ret_str)]= NULL;
	}
	else
	{
		//1) "mov	dword[temp_val], "
		strcopy(ret_str , "\tmov	dword[temp_val], ");
		total_len		= strlen(ret_str);

		//2)"mov byte[0x111111], eax
		p			= &ret_str[total_len];

		strcopy(p , "edx");

		total_len		+=strlen(p);
	
		//3)"mov byte[0x111111]
		ret_str[total_len]	= NULL;		
	}


	//6)
	struct ins_exp*	iretexp	= malloc(sizeof(struct ins_exp));

	if(iretexp)
	{
		strcopy(iretexp->str ,ret_str);
		iretexp->str[strlen(iretexp->str)]= NULL;

		iretexp->head		= NULL;
		iretexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *iretelist	= iexplist_build(iretexp);

	//8)
	ins_add2explist(iretelist, iexplist);

	//------------------------------------------------------------------
	// pop	edx
	//------------------------------------------------------------------
	s8 pop_str[INS_LEN];
	empty_buf(pop_str, INS_LEN);
	strcopy(pop_str , "\tpop	edx");

	pop_str[strlen(pop_str)]	= NULL;
	
	//2)
	struct ins_exp* ipopexp	= malloc(sizeof(struct ins_exp));

	if(ipopexp)
	{
		strcopy(ipopexp->str ,pop_str);
		ipopexp->str[strlen(ipopexp->str)]= NULL;

		ipopexp->head		= NULL;
		ipopexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ipoplist	= iexplist_build(ipopexp);

	//4)
	ins_add2explist(ipoplist, iexplist);

	//------------------------------------------------------------------
	// pop	ebx
	//------------------------------------------------------------------
	pop_str[INS_LEN];
	empty_buf(pop_str, INS_LEN);
	strcopy(pop_str , "\tpop	ebx");

	pop_str[strlen(pop_str)]	= NULL;
	
	//2)
	ipopexp	= malloc(sizeof(struct ins_exp));

	if(ipopexp)
	{
		strcopy(ipopexp->str ,pop_str);
		ipopexp->str[strlen(ipopexp->str)]= NULL;

		ipopexp->head		= NULL;
		ipopexp->tail		= NULL;		
	}

	//3)
	ipoplist	= iexplist_build(ipopexp);

	//4)
	ins_add2explist(ipoplist, iexplist);

	//------------------------------------------------------------------
	// pop	eax
	//------------------------------------------------------------------
	pop_str[INS_LEN];
	empty_buf(pop_str, INS_LEN);
	strcopy(pop_str , "\tpop	eax\n");

	pop_str[strlen(pop_str)]	= NULL;
	
	//2)
	ipopexp	= malloc(sizeof(struct ins_exp));

	if(ipopexp)
	{
		strcopy(ipopexp->str ,pop_str);
		ipopexp->str[strlen(ipopexp->str)]= NULL;

		ipopexp->head		= NULL;
		ipopexp->tail		= NULL;		
	}

	//3)
	ipoplist	= iexplist_build(ipopexp);

	//4)
	ins_add2explist(ipoplist, iexplist);
}


//===========================================================================
// ins_move_build
//===========================================================================
PUBLIC	struct ins*	ins_move_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_val)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_move_build -- \n");
#endif
//--------------------------

	if(exp->e.move.res_type_len == 0)
	{
		return NULL;
	}
	
	s32 total_len	= 0;
	s8	*p	= NULL;

	//------------------------------------------------------------------
	// mov	ebx, byte[src_addr]
	//------------------------------------------------------------------
	
	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);
		
	s8 src_str[INS_LEN];
	empty_buf(src_str, INS_LEN);
	strcopy(src_str , "\tmov	");

	total_len		= strlen(src_str);
	p			= &src_str[total_len];

	strcopy(p ,&regs[reg_val]);
	total_len		+=strlen(p);

	if(exp->e.move.val_type_len)
	{
		if(exp->e.move.val_type_len != PASM_ADDRESS_FLG)
		{
			//1) "mov eax, byte"
			empty_buf(ins_temp_buf, INS_LEN);
			ins_type(exp->e.move.val_type_len,  ins_temp_buf);
	
			src_str[total_len]	= ',';
			total_len++;
			src_str[total_len]	= ' ';
			total_len		= strlen(src_str);
			p			= &src_str[total_len];

			strcopy(p ,ins_temp_buf);
			total_len		+=strlen(p);

			//2)"mov ebx, byte[
			src_str[total_len]	= '[';
			total_len++;

			p			= &src_str[total_len];
			strcopy(p ,exp->e.move.val_name);
			total_len		+=strlen(p);

			src_str[total_len]	= ']';
			total_len++;
		}
		else
		{
			//------------------------------------------------------------------
			// only for the address of variable, eg: a = &b;
			// assume that the address of &b is (ebp+8)
			// 1) mov esi, ebp
			// 2) add esi, 8
			//------------------------------------------------------------------
			//1)mov reg, ebp
			p			= &src_str[total_len];
			strcopy(p ,", ebp");
			total_len		+=strlen(p);

			//2)"mov ebx, byte[0x111111]
			src_str[total_len]	= NULL;
	
			//3)
			struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

			if(isrcexp)
			{
				strcopy(isrcexp->str ,src_str);
				isrcexp->str[strlen(isrcexp->str)]= NULL;

				isrcexp->head		= NULL;
				isrcexp->tail		= NULL;		
			}

			//4)
			struct ins_explist *isrcelist	= iexplist_build(isrcexp);

			//5)
			ins_add2explist(isrcelist, iexplist);

			//6) "add reg, offset"
			empty_buf(src_str, INS_LEN);
			total_len	= 0;

			p			= &src_str[total_len];

			s8 *qt			= exp->e.move.val_name+3;
			if(*(qt) == '+')
			{
				strcopy(p ,"\tadd	");
			}
			else if(*(qt) == '-')
			{
				strcopy(p ,"\tsub	");
			}

			total_len		+=strlen(p);

			p			= &src_str[total_len];
			strcopy(p ,&regs[reg_val]);
			total_len		+=strlen(p);

			p			= &src_str[total_len];
			strcopy(p ,", ");
			total_len		+=strlen(p);

			p			= &src_str[total_len];
			strcopy(p , (exp->e.move.val_name+4));
			total_len		+=strlen(p);
			
			total_len++;
		}
	}
	else
	{
		src_str[total_len]	= ',';
		total_len++;

		if(strcmp(exp->e.move.val_name, "temp_val"))
		{
			p			= &src_str[total_len];
			strcopy(p ,"dword[temp_val]");
			total_len		+=strlen(p);
		}
		else
		{
			p			= &src_str[total_len];
			strcopy(p ,exp->e.move.val_name);
			total_len		+=strlen(p);
		}
	}

	//5)"mov ebx, byte[0x111111]
	src_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

	if(isrcexp)
	{
		strcopy(isrcexp->str ,src_str);
		isrcexp->str[strlen(isrcexp->str)]= NULL;

		isrcexp->head		= NULL;
		isrcexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *isrcelist	= iexplist_build(isrcexp);

	//8)
	ins_add2explist(isrcelist, iexplist);	

	//------------------------------------------------------------------
	// result is saved to dst:: mov byte[0x111111], eax
	//------------------------------------------------------------------
	
	//1) "mov	"
	//empty_buf(ins_temp_buf, INS_LEN);
		
	s8 ret_str[INS_LEN]	= "\tmov	";
	total_len		= strlen(ret_str);
	
	//1) "mov byte"
	empty_buf(ins_temp_buf, INS_LEN);
	ins_type(exp->e.move.res_type_len,  ins_temp_buf);

	p			= &ret_str[total_len];
	strcopy(p ,ins_temp_buf);
	total_len		+=strlen(p);

	//2)"mov byte[
	ret_str[total_len]	= '[';
	total_len++;
		
	//3) "mov byte[0x111111"
	p			= &ret_str[total_len];
	strcopy(p ,exp->e.move.res_name);
	total_len		+=strlen(p);	

	//4)"mov byte[0x111111],
	ret_str[total_len]	= ']';
	total_len++;
	ret_str[total_len]	= ',';
	total_len++;

	//4)get reminder	:: "mov byte[0x111111], edx
	p			= &ret_str[total_len];
	strcopy(p ,&regs[reg_val]);
	total_len		+=strlen(p);
	
	//5)"mov byte[0x111111]
	ret_str[total_len]	= NULL;	
	
	//6)
	struct ins_exp*	iretexp	= malloc(sizeof(struct ins_exp));

	if(iretexp)
	{
		strcopy(iretexp->str ,ret_str);
		iretexp->str[strlen(iretexp->str)]= NULL;

		iretexp->head		= NULL;
		iretexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *iretelist	= iexplist_build(iretexp);

	//8)
	ins_add2explist(iretelist, iexplist);
}


//===========================================================================
// ins_label_build
//===========================================================================
PUBLIC	struct ins*	ins_label_build(struct pasm_exp *exp, struct ins_explist * iexplist)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_label_build -- \n");
#endif
//--------------------------

	s32 total_len	= 0;
	s8	*p	= NULL;

	//------------------------------------------------------------------
	// mov	ebx, byte[src_addr]
	//------------------------------------------------------------------
	
	//1) "mov	"
	s8 src_str[INS_LEN]	= "";
	total_len		= strlen(src_str);
	p			= &src_str[total_len];

	strcopy(p ,exp->e.label.label_name);
	total_len		+=strlen(p);

	//2)
	src_str[total_len]	= ':';
	total_len++;

	//3)
	p			= &src_str[total_len];
	strcopy(p , "\n\tpush	ebp\n");
	total_len		+=strlen(p);

	//4)
	p			= &src_str[total_len];
	strcopy(p , "\tmov	ebp, esp");
	total_len		+=strlen(p);


	src_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

	if(isrcexp)
	{
		strcopy(isrcexp->str ,src_str);
		isrcexp->str[strlen(isrcexp->str)]= NULL;

		isrcexp->head		= NULL;
		isrcexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *isrcelist	= iexplist_build(isrcexp);

	//8)
	ins_add2explist(isrcelist, iexplist);	
}

//===========================================================================
// ins_call_build
//===========================================================================
PUBLIC	struct ins*	ins_call_build(struct pasm_exp *exp, struct ins_explist * iexplist)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_call_build -- \n");
#endif
//--------------------------

	s32 total_len	= 0;
	s8	*p	= NULL;
	s32 nr_params_offset;

	//------------------------------------------------------------------
	// parameter	:: push byte[src_addr]
	//------------------------------------------------------------------
	struct pasm_explist *pv	= exp->e.call.ppv;
	
	for(nr_params_offset=0; pv; pv=pv->tail)
	{
		struct pasm_exp *pexp	= pv->exp;

		if(pexp)
		{
			//1) "push	dword"
			empty_buf(ins_temp_buf, INS_LEN);
		
			s8 src_str[INS_LEN]	= "\tpush	dword";
			total_len		= strlen(src_str);
	
			//2)"push	dword[
			src_str[total_len]	= '[';
			total_len++;
		
			//3) "push dword[0x111111"
			p			= &src_str[total_len];
			strcopy(p ,pexp->e.mem.src_name);
			total_len		+=strlen(p);

			//4)"mov ebx, byte[0x111111]
			src_str[total_len]	= ']';
			total_len++;

			//5)"mov ebx, byte[0x111111]
			src_str[total_len]	= NULL;
	
			//6)
			struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

			if(isrcexp)
			{
				strcopy(isrcexp->str ,src_str);
				isrcexp->str[strlen(isrcexp->str)]= NULL;

				isrcexp->head		= NULL;
				isrcexp->tail		= NULL;		
			}

			//7)
			struct ins_explist *isrcelist	= iexplist_build(isrcexp);

			//8)
			ins_add2explist(isrcelist, iexplist);
			
			nr_params_offset	+= 4;
		}
	}	

	//------------------------------------------------------------------
	// call	funcname
	//------------------------------------------------------------------
	
	//1) "call	funcname"
	empty_buf(ins_temp_buf, INS_LEN);
	
	strcopy(ins_temp_buf, "\tcall	");
	total_len		=strlen(ins_temp_buf);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,exp->e.call.label_name);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	iresexp	= malloc(sizeof(struct ins_exp));

	if(iresexp)
	{
		strcopy(iresexp->str ,ins_temp_buf);
		iresexp->str[strlen(iresexp->str)]= NULL;

		iresexp->head		= NULL;
		iresexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ireselist	= iexplist_build(iresexp);

	//4)
	ins_add2explist(ireselist, iexplist);

	//------------------------------------------------------------------
	// pop	params
	//------------------------------------------------------------------
	empty_buf(ins_temp_buf, INS_LEN);	
	
	ins_temp_buf[0] = '0';
	ins_temp_buf[1] = 'x';

	h2s(nr_params_offset, &ins_temp_buf[2]);	

	s8 pop_str[INS_LEN];
	empty_buf(pop_str, INS_LEN);

	total_len	= 0;
	p		= &pop_str[total_len];	

	strcopy(p , "\tadd	esp, ");
	total_len	+= strlen(p);

	p		= &pop_str[total_len];
	strcopy(p , ins_temp_buf);
	total_len		+=strlen(p);

	pop_str[total_len]	= '\n';
	pop_str[total_len+1]	= NULL;
	
	//2)
	struct ins_exp* ipopexp	= malloc(sizeof(struct ins_exp));

	if(ipopexp)
	{
		strcopy(ipopexp->str ,pop_str);
		ipopexp->str[strlen(ipopexp->str)]= NULL;

		ipopexp->head		= NULL;
		ipopexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ipoplist	= iexplist_build(ipopexp);

	//4)
	ins_add2explist(ipoplist, iexplist);

	//------------------------------------------------------------------
	// result is saved to dst:: mov byte[0x111111], eax
	//------------------------------------------------------------------
	
	total_len	= 0;
	p		= NULL;

	s8 ret_str[INS_LEN];
	empty_buf(ret_str, INS_LEN);

	//1) "mov	dword[temp_val], "
	strcopy(ret_str , "\tmov	dword[temp_val], eax");
	total_len		= strlen(ret_str);

	//3)"mov byte[0x111111]
	ret_str[total_len]	= NULL;

	//6)
	struct ins_exp*	iretexp	= malloc(sizeof(struct ins_exp));

	if(iretexp)
	{
		strcopy(iretexp->str ,ret_str);
		iretexp->str[strlen(iretexp->str)]= NULL;

		iretexp->head		= NULL;
		iretexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *iretelist	= iexplist_build(iretexp);

	//8)
	ins_add2explist(iretelist, iexplist);

}

//===========================================================================
// ins_jump_return_build
//===========================================================================
PUBLIC	struct ins*	ins_jump_return_build(struct pasm_explist *explist, struct ins_explist * iexplist)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_jump_return_build -- \n");
#endif
//--------------------------

	s32 total_len	= 0;
	s8	*p	= NULL;

	//------------------------------------------------------------------
	// mov	ebx, byte[src_addr]
	//------------------------------------------------------------------
	
	//1) "mov	"
	s8 src_str[INS_LEN];	
	empty_buf(src_str, INS_LEN);

	//3)
	p			= src_str;
	strcopy(p , "\n\tmov	esp, ebp\n");
	total_len		+=strlen(p);

	//4)
	p			= &src_str[total_len];
	strcopy(p , "\tpop	ebp\n");
	total_len		+=strlen(p);

	//5)
	p			= &src_str[total_len];
	strcopy(p , "\tret\n");
	total_len		+=strlen(p);

	src_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

	if(isrcexp)
	{
		strcopy(isrcexp->str ,src_str);
		isrcexp->str[strlen(isrcexp->str)]= NULL;

		isrcexp->head		= NULL;
		isrcexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *isrcelist	= iexplist_build(isrcexp);

	//8)
	ins_add2explist(isrcelist, iexplist);	
}



//===========================================================================
// ins_jump_build
//===========================================================================
PUBLIC	struct ins*	ins_jump_build(s8 *target, struct ins_explist * iexplist)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_jump_build -- \n");
#endif
//--------------------------

	s32 total_len	= 0;
	s8	*p	= NULL;

	//------------------------------------------------------------------
	// mov	ebx, byte[src_addr]
	//------------------------------------------------------------------
	
	//1) "mov	"
	s8 src_str[INS_LEN];	
	empty_buf(src_str, INS_LEN);

	//3)
	p			= src_str;
	strcopy(p , "\tjmp	");
	total_len		+=strlen(p);

	//4)
	p			= &src_str[total_len];
	strcopy(p , target);
	total_len		+=strlen(p);

	//5)
	p			= &src_str[total_len];
	strcopy(p , "\n");
	total_len		+=strlen(p);

	src_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

	if(isrcexp)
	{
		strcopy(isrcexp->str ,src_str);
		isrcexp->str[strlen(isrcexp->str)]= NULL;

		isrcexp->head		= NULL;
		isrcexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *isrcelist	= iexplist_build(isrcexp);

	//8)
	ins_add2explist(isrcelist, iexplist);	
}

//===========================================================================
// ins_type
//===========================================================================
PUBLIC	void	ins_type(u32 type_len, s8* buf)
{
	switch(type_len)
	{
		case 1:
			strcopy(buf, "byte");
			buf[4]	= NULL;
			break;
		case 2:
			strcopy(buf, "word");
			buf[4]	= NULL;
			break;
		case 4:
			strcopy(buf, "dword");
			buf[5]	= NULL;
			break;
		default:
			strcopy(buf, "dword");
			buf[5]	= NULL;
			break;
	}
}

//===========================================================================
// ins_label_build
//===========================================================================
PUBLIC	struct ins*	ins_label_s_build(s8 *label, struct ins_explist * iexplist)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_label_s_build(s) -- \n");
#endif
//--------------------------

	s32 total_len	= 0;
	s8	*p	= NULL;

	//------------------------------------------------------------------
	// mov	ebx, byte[src_addr]
	//------------------------------------------------------------------
	
	//1) "mov	"
	s8 src_str[INS_LEN]	= "";
	total_len		= strlen(src_str);
	p			= &src_str[total_len];

	strcopy(p ,label);
	total_len		+=strlen(p);

	//2)
	src_str[total_len]	= ':';
	total_len++;

	src_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

	if(isrcexp)
	{
		strcopy(isrcexp->str ,src_str);
		isrcexp->str[strlen(isrcexp->str)]= NULL;

		isrcexp->head		= NULL;
		isrcexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *isrcelist	= iexplist_build(isrcexp);

	//8)
	ins_add2explist(isrcelist, iexplist);	

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_label_s_build(e) -- \n\n");
#endif
//--------------------------
}

//===========================================================================
// ins_above_build
//===========================================================================
PUBLIC	struct ins*	ins_above_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst, s8 *tl, s8 *fl, s8 *el)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_above_build(s) -- \n");
#endif
//--------------------------

	s8	*src_name, *dst_name, *res_name;
	u32	src_len, dst_len, res_len;	

	src_len	= exp->e.above.src_len;
	dst_len	= exp->e.above.dst_len;

	src_name= exp->e.above.src_name;
	dst_name= exp->e.above.dst_name;
	
	//------------------------------------------------------------------
	// source	:: mov	ebx, byte[src_addr]
	//------------------------------------------------------------------
	s32 total_len	= 0;
	s8	*p	= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);

	s8 src_str[INS_LEN];
	empty_buf(src_str, INS_LEN);
	strcopy(src_str , "\tmov	");
			
	total_len		= strlen(src_str);
	p			= &src_str[total_len];

	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	//1) "mov ebx, byte"
	if(src_len != 0)
	{
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(src_len,  ins_temp_buf);
	
		src_str[total_len]	= ',';
		total_len++;
		src_str[total_len]	= ' ';
		total_len		= strlen(src_str);
		p			= &src_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);
	
		//2)"mov ebx, byte[
		src_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		src_str[total_len]	= ',';
		total_len++;
	}
	
	p			= &src_str[total_len];
	strcopy(p ,src_name);
	total_len		+=strlen(p);

	if(src_len)
	{
		//4)"mov ebx, byte[0x111111]
		src_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	src_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

	if(isrcexp)
	{
		strcopy(isrcexp->str ,src_str);
		isrcexp->str[strlen(isrcexp->str)]= NULL;

		isrcexp->head		= NULL;
		isrcexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *isrcelist	= iexplist_build(isrcexp);

	//8)
	ins_add2explist(isrcelist, iexplist);

	//------------------------------------------------------------------
	// dest	::	mov	eax, byte[dst_addr]
	//------------------------------------------------------------------
	
	total_len	= 0;
	p		= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);
		
	s8 dst_str[INS_LEN];
	empty_buf(dst_str, INS_LEN);
	strcopy(dst_str , "\tmov	");

	total_len		= strlen(dst_str);
	p			= &dst_str[total_len];

	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	//1) "mov eax, byte"
	if(dst_len != 0)
	{
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(dst_len,  ins_temp_buf);
	
		dst_str[total_len]	= ',';
		total_len++;
		dst_str[total_len]	= ' ';
		total_len		= strlen(dst_str);
		p			= &dst_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);

		//2)"mov ebx, byte[
		dst_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		dst_str[total_len]	= ',';
		total_len++;
	}
		
	p			= &dst_str[total_len];
	strcopy(p ,dst_name);
	total_len		+=strlen(p);

	if(dst_len)
	{
		//4)"mov ebx, byte[0x111111]
		dst_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	dst_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	idstexp	= malloc(sizeof(struct ins_exp));

	if(idstexp)
	{
		strcopy(idstexp->str ,dst_str);
		idstexp->str[strlen(idstexp->str)]= NULL;

		idstexp->head		= NULL;
		idstexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *idstelist	= iexplist_build(idstexp);

	//8)
	ins_add2explist(idstelist, iexplist);

	//------------------------------------------------------------------
	// result	::cmp	eax, ebx
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tcmp	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,", ");
	total_len		+=strlen(p);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	iresexp	= malloc(sizeof(struct ins_exp));

	if(iresexp)
	{
		strcopy(iresexp->str ,ins_temp_buf);
		iresexp->str[strlen(iresexp->str)]= NULL;

		iresexp->head		= NULL;
		iresexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ireselist	= iexplist_build(iresexp);

	//4)
	ins_add2explist(ireselist, iexplist);

	//------------------------------------------------------------------
	// ja	label_1(true label)
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tja	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,tl);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	itlexp	= malloc(sizeof(struct ins_exp));

	if(itlexp)
	{
		strcopy(itlexp->str ,ins_temp_buf);
		itlexp->str[strlen(itlexp->str)]= NULL;

		itlexp->head		= NULL;
		itlexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *itlelist	= iexplist_build(itlexp);

	//4)
	ins_add2explist(itlelist, iexplist);

	//------------------------------------------------------------------
	// jmp false_label
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tjmp	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,fl);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	itlexp_1	= malloc(sizeof(struct ins_exp));

	if(itlexp_1)
	{
		strcopy(itlexp_1->str ,ins_temp_buf);
		itlexp_1->str[strlen(itlexp_1->str)]= NULL;

		itlexp_1->head		= NULL;
		itlexp_1->tail		= NULL;		
	}

	//3)
	struct ins_explist *itlelist_1	= iexplist_build(itlexp_1);

	//4)
	ins_add2explist(itlelist_1, iexplist);

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_above_build(e) -- \n\n");
#endif
//--------------------------	
}

//===========================================================================
// ins_low_build
//===========================================================================
PUBLIC	struct ins*	ins_low_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst, s8 *tl, s8 *fl, s8 *el)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_low_build(s) -- \n");
#endif
//--------------------------

	s8	*src_name, *dst_name, *res_name;
	u32	src_len, dst_len, res_len;	

	src_len	= exp->e.low.src_len;
	dst_len	= exp->e.low.dst_len;

	src_name= exp->e.low.src_name;
	dst_name= exp->e.low.dst_name;
	
	//------------------------------------------------------------------
	// source	:: mov	ebx, byte[src_addr]
	//------------------------------------------------------------------
	s32 total_len	= 0;
	s8	*p	= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);

	s8 src_str[INS_LEN];
	empty_buf(src_str, INS_LEN);
	strcopy(src_str , "\tmov	");
			
	total_len		= strlen(src_str);
	p			= &src_str[total_len];

	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	//1) "mov ebx, byte"
	if(src_len != 0)
	{
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(src_len,  ins_temp_buf);
	
		src_str[total_len]	= ',';
		total_len++;
		src_str[total_len]	= ' ';
		total_len		= strlen(src_str);
		p			= &src_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);
	
		//2)"mov ebx, byte[
		src_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		src_str[total_len]	= ',';
		total_len++;
	}
	
	
	p			= &src_str[total_len];
	strcopy(p ,src_name);
	total_len		+=strlen(p);

	if(src_len)
	{
		//4)"mov ebx, byte[0x111111]
		src_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	src_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

	if(isrcexp)
	{
		strcopy(isrcexp->str ,src_str);
		isrcexp->str[strlen(isrcexp->str)]= NULL;

		isrcexp->head		= NULL;
		isrcexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *isrcelist	= iexplist_build(isrcexp);

	//8)
	ins_add2explist(isrcelist, iexplist);

	//------------------------------------------------------------------
	// dest	::	mov	eax, byte[dst_addr]
	//------------------------------------------------------------------
	
	total_len	= 0;
	p		= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);
		
	s8 dst_str[INS_LEN];
	empty_buf(dst_str, INS_LEN);
	strcopy(dst_str , "\tmov	");

	total_len		= strlen(dst_str);
	p			= &dst_str[total_len];

	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	//1) "mov eax, byte"
	if(dst_len != 0)
	{
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(dst_len,  ins_temp_buf);
	
		dst_str[total_len]	= ',';
		total_len++;
		dst_str[total_len]	= ' ';
		total_len		= strlen(dst_str);
		p			= &dst_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);

		//2)"mov ebx, byte[
		dst_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		dst_str[total_len]	= ',';
		total_len++;
	}
		
	p			= &dst_str[total_len];
	strcopy(p ,dst_name);
	total_len		+=strlen(p);

	if(dst_len)
	{
		//4)"mov ebx, byte[0x111111]
		dst_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	dst_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	idstexp	= malloc(sizeof(struct ins_exp));

	if(idstexp)
	{
		strcopy(idstexp->str ,dst_str);
		idstexp->str[strlen(idstexp->str)]= NULL;

		idstexp->head		= NULL;
		idstexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *idstelist	= iexplist_build(idstexp);

	//8)
	ins_add2explist(idstelist, iexplist);

	//------------------------------------------------------------------
	// result	::cmp	eax, ebx
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tcmp	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,", ");
	total_len		+=strlen(p);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	iresexp	= malloc(sizeof(struct ins_exp));

	if(iresexp)
	{
		strcopy(iresexp->str ,ins_temp_buf);
		iresexp->str[strlen(iresexp->str)]= NULL;

		iresexp->head		= NULL;
		iresexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ireselist	= iexplist_build(iresexp);

	//4)
	ins_add2explist(ireselist, iexplist);

	//------------------------------------------------------------------
	// ja	label_1(true label)
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tjb	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,tl);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	itlexp	= malloc(sizeof(struct ins_exp));

	if(itlexp)
	{
		strcopy(itlexp->str ,ins_temp_buf);
		itlexp->str[strlen(itlexp->str)]= NULL;

		itlexp->head		= NULL;
		itlexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *itlelist	= iexplist_build(itlexp);

	//4)
	ins_add2explist(itlelist, iexplist);

	//------------------------------------------------------------------
	// jmp false_label
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tjmp	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,fl);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	itlexp_1	= malloc(sizeof(struct ins_exp));

	if(itlexp_1)
	{
		strcopy(itlexp_1->str ,ins_temp_buf);
		itlexp_1->str[strlen(itlexp_1->str)]= NULL;

		itlexp_1->head		= NULL;
		itlexp_1->tail		= NULL;		
	}

	//3)
	struct ins_explist *itlelist_1	= iexplist_build(itlexp_1);

	//4)
	ins_add2explist(itlelist_1, iexplist);

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_low_build(e) -- \n\n");
#endif
//--------------------------	
}



//===========================================================================
// ins_equal_build
//===========================================================================
PUBLIC	struct ins*	ins_equal_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst, s8 *tl, s8 *fl, s8 *el)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_equal_build(s) -- \n");
#endif
//--------------------------

	s8	*src_name, *dst_name, *res_name;
	u32	src_len, dst_len, res_len;	

	src_len	= exp->e.equal.src_len;
	dst_len	= exp->e.equal.dst_len;

	src_name= exp->e.equal.src_name;
	dst_name= exp->e.equal.dst_name;
	
	//------------------------------------------------------------------
	// source	:: mov	ebx, byte[src_addr]
	//------------------------------------------------------------------
	s32 total_len	= 0;
	s8	*p	= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);

	s8 src_str[INS_LEN];
	empty_buf(src_str, INS_LEN);
	strcopy(src_str , "\tmov	");
			
	total_len		= strlen(src_str);
	p			= &src_str[total_len];

	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	//1) "mov ebx, byte"
	if(src_len != 0)
	{
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(src_len,  ins_temp_buf);
	
		src_str[total_len]	= ',';
		total_len++;
		src_str[total_len]	= ' ';
		total_len		= strlen(src_str);
		p			= &src_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);
	
		//2)"mov ebx, byte[
		src_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		src_str[total_len]	= ',';
		total_len++;
	}
	
	
	p			= &src_str[total_len];
	strcopy(p ,src_name);
	total_len		+=strlen(p);

	if(src_len)
	{
		//4)"mov ebx, byte[0x111111]
		src_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	src_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

	if(isrcexp)
	{
		strcopy(isrcexp->str ,src_str);
		isrcexp->str[strlen(isrcexp->str)]= NULL;

		isrcexp->head		= NULL;
		isrcexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *isrcelist	= iexplist_build(isrcexp);

	//8)
	ins_add2explist(isrcelist, iexplist);

	//------------------------------------------------------------------
	// dest	::	mov	eax, byte[dst_addr]
	//------------------------------------------------------------------
	
	total_len	= 0;
	p		= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);
		
	s8 dst_str[INS_LEN];
	empty_buf(dst_str, INS_LEN);
	strcopy(dst_str , "\tmov	");

	total_len		= strlen(dst_str);
	p			= &dst_str[total_len];

	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	//1) "mov eax, byte"
	if(dst_len != 0)
	{
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(dst_len,  ins_temp_buf);
	
		dst_str[total_len]	= ',';
		total_len++;
		dst_str[total_len]	= ' ';
		total_len		= strlen(dst_str);
		p			= &dst_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);

		//2)"mov ebx, byte[
		dst_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		dst_str[total_len]	= ',';
		total_len++;
	}
		
	p			= &dst_str[total_len];
	strcopy(p ,dst_name);
	total_len		+=strlen(p);

	if(dst_len)
	{
		//4)"mov ebx, byte[0x111111]
		dst_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	dst_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	idstexp	= malloc(sizeof(struct ins_exp));

	if(idstexp)
	{
		strcopy(idstexp->str ,dst_str);
		idstexp->str[strlen(idstexp->str)]= NULL;

		idstexp->head		= NULL;
		idstexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *idstelist	= iexplist_build(idstexp);

	//8)
	ins_add2explist(idstelist, iexplist);

	//------------------------------------------------------------------
	// result	::cmp	eax, ebx
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tcmp	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,", ");
	total_len		+=strlen(p);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	iresexp	= malloc(sizeof(struct ins_exp));

	if(iresexp)
	{
		strcopy(iresexp->str ,ins_temp_buf);
		iresexp->str[strlen(iresexp->str)]= NULL;

		iresexp->head		= NULL;
		iresexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ireselist	= iexplist_build(iresexp);

	//4)
	ins_add2explist(ireselist, iexplist);

	//------------------------------------------------------------------
	// ja	label_1(true label)
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tje	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,tl);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	itlexp	= malloc(sizeof(struct ins_exp));

	if(itlexp)
	{
		strcopy(itlexp->str ,ins_temp_buf);
		itlexp->str[strlen(itlexp->str)]= NULL;

		itlexp->head		= NULL;
		itlexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *itlelist	= iexplist_build(itlexp);

	//4)
	ins_add2explist(itlelist, iexplist);

	//------------------------------------------------------------------
	// jmp false_label
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tjmp	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,fl);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	itlexp_1	= malloc(sizeof(struct ins_exp));

	if(itlexp_1)
	{
		strcopy(itlexp_1->str ,ins_temp_buf);
		itlexp_1->str[strlen(itlexp_1->str)]= NULL;

		itlexp_1->head		= NULL;
		itlexp_1->tail		= NULL;		
	}

	//3)
	struct ins_explist *itlelist_1	= iexplist_build(itlexp_1);

	//4)
	ins_add2explist(itlelist_1, iexplist);

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_equal_build(e) -- \n\n");
#endif
//--------------------------	
}


//===========================================================================
// ins_not_equal_build
//===========================================================================
PUBLIC	struct ins*	ins_not_equal_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst, s8 *tl, s8 *fl, s8 *el)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_not_equal_build(s) -- \n");
#endif
//--------------------------

	s8	*src_name, *dst_name, *res_name;
	u32	src_len, dst_len, res_len;	

	src_len	= exp->e.not_equal.src_len;
	dst_len	= exp->e.not_equal.dst_len;

	src_name= exp->e.not_equal.src_name;
	dst_name= exp->e.not_equal.dst_name;
	
	//------------------------------------------------------------------
	// source	:: mov	ebx, byte[src_addr]
	//------------------------------------------------------------------
	s32 total_len	= 0;
	s8	*p	= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);

	s8 src_str[INS_LEN];
	empty_buf(src_str, INS_LEN);
	strcopy(src_str , "\tmov	");
			
	total_len		= strlen(src_str);
	p			= &src_str[total_len];

	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	//1) "mov ebx, byte"
	if(src_len != 0)
	{
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(src_len,  ins_temp_buf);
	
		src_str[total_len]	= ',';
		total_len++;
		src_str[total_len]	= ' ';
		total_len		= strlen(src_str);
		p			= &src_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);
	
		//2)"mov ebx, byte[
		src_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		src_str[total_len]	= ',';
		total_len++;
	}	
	
	p			= &src_str[total_len];
	strcopy(p ,src_name);
	total_len		+=strlen(p);

	if(src_len)
	{
		//4)"mov ebx, byte[0x111111]
		src_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	src_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

	if(isrcexp)
	{
		strcopy(isrcexp->str ,src_str);
		isrcexp->str[strlen(isrcexp->str)]= NULL;

		isrcexp->head		= NULL;
		isrcexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *isrcelist	= iexplist_build(isrcexp);

	//8)
	ins_add2explist(isrcelist, iexplist);

	//------------------------------------------------------------------
	// dest	::	mov	eax, byte[dst_addr]
	//------------------------------------------------------------------
	
	total_len	= 0;
	p		= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);
		
	s8 dst_str[INS_LEN];
	empty_buf(dst_str, INS_LEN);
	strcopy(dst_str , "\tmov	");

	total_len		= strlen(dst_str);
	p			= &dst_str[total_len];

	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	//1) "mov eax, byte"
	if(dst_len != 0)
	{
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(dst_len,  ins_temp_buf);
	
		dst_str[total_len]	= ',';
		total_len++;
		dst_str[total_len]	= ' ';
		total_len		= strlen(dst_str);
		p			= &dst_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);

		//2)"mov ebx, byte[
		dst_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		dst_str[total_len]	= ',';
		total_len++;
	}
		
	p			= &dst_str[total_len];
	strcopy(p ,dst_name);
	total_len		+=strlen(p);

	if(dst_len)
	{
		//4)"mov ebx, byte[0x111111]
		dst_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	dst_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	idstexp	= malloc(sizeof(struct ins_exp));

	if(idstexp)
	{
		strcopy(idstexp->str ,dst_str);
		idstexp->str[strlen(idstexp->str)]= NULL;

		idstexp->head		= NULL;
		idstexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *idstelist	= iexplist_build(idstexp);

	//8)
	ins_add2explist(idstelist, iexplist);

	//------------------------------------------------------------------
	// result	::cmp	eax, ebx
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tcmp	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,", ");
	total_len		+=strlen(p);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	iresexp	= malloc(sizeof(struct ins_exp));

	if(iresexp)
	{
		strcopy(iresexp->str ,ins_temp_buf);
		iresexp->str[strlen(iresexp->str)]= NULL;

		iresexp->head		= NULL;
		iresexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ireselist	= iexplist_build(iresexp);

	//4)
	ins_add2explist(ireselist, iexplist);

	//------------------------------------------------------------------
	// ja	label_1(true label)
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tjne	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,tl);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	itlexp	= malloc(sizeof(struct ins_exp));

	if(itlexp)
	{
		strcopy(itlexp->str ,ins_temp_buf);
		itlexp->str[strlen(itlexp->str)]= NULL;

		itlexp->head		= NULL;
		itlexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *itlelist	= iexplist_build(itlexp);

	//4)
	ins_add2explist(itlelist, iexplist);

	//------------------------------------------------------------------
	// jmp false_label
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tjmp	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,fl);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	itlexp_1	= malloc(sizeof(struct ins_exp));

	if(itlexp_1)
	{
		strcopy(itlexp_1->str ,ins_temp_buf);
		itlexp_1->str[strlen(itlexp_1->str)]= NULL;

		itlexp_1->head		= NULL;
		itlexp_1->tail		= NULL;		
	}

	//3)
	struct ins_explist *itlelist_1	= iexplist_build(itlexp_1);

	//4)
	ins_add2explist(itlelist_1, iexplist);

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_not_equal_build(e) -- \n\n");
#endif
//--------------------------	
}


//===========================================================================
// ins_above_equal_build
//===========================================================================
PUBLIC	struct ins*	ins_above_equal_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst, s8 *tl, s8 *fl, s8 *el)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_above_equal_build(s) -- \n");
#endif
//--------------------------

	s8	*src_name, *dst_name, *res_name;
	u32	src_len, dst_len, res_len;	

	src_len	= exp->e.above_equal.src_len;
	dst_len	= exp->e.above_equal.dst_len;

	src_name= exp->e.above_equal.src_name;
	dst_name= exp->e.above_equal.dst_name;
	
	//------------------------------------------------------------------
	// source	:: mov	ebx, byte[src_addr]
	//------------------------------------------------------------------
	s32 total_len	= 0;
	s8	*p	= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);

	s8 src_str[INS_LEN];
	empty_buf(src_str, INS_LEN);
	strcopy(src_str , "\tmov	");
			
	total_len		= strlen(src_str);
	p			= &src_str[total_len];

	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	//1) "mov ebx, byte"
	if(src_len != 0)
	{
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(src_len,  ins_temp_buf);
	
		src_str[total_len]	= ',';
		total_len++;
		src_str[total_len]	= ' ';
		total_len		= strlen(src_str);
		p			= &src_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);
	
		//2)"mov ebx, byte[
		src_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		src_str[total_len]	= ',';
		total_len++;
	}
		
	p			= &src_str[total_len];
	strcopy(p ,src_name);
	total_len		+=strlen(p);

	if(src_len)
	{
		//4)"mov ebx, byte[0x111111]
		src_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	src_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

	if(isrcexp)
	{
		strcopy(isrcexp->str ,src_str);
		isrcexp->str[strlen(isrcexp->str)]= NULL;

		isrcexp->head		= NULL;
		isrcexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *isrcelist	= iexplist_build(isrcexp);

	//8)
	ins_add2explist(isrcelist, iexplist);

	//------------------------------------------------------------------
	// dest	::	mov	eax, byte[dst_addr]
	//------------------------------------------------------------------
	
	total_len	= 0;
	p		= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);
		
	s8 dst_str[INS_LEN];
	empty_buf(dst_str, INS_LEN);
	strcopy(dst_str , "\tmov	");

	total_len		= strlen(dst_str);
	p			= &dst_str[total_len];

	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	//1) "mov eax, byte"
	if(dst_len != 0)
	{
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(dst_len,  ins_temp_buf);
	
		dst_str[total_len]	= ',';
		total_len++;
		dst_str[total_len]	= ' ';
		total_len		= strlen(dst_str);
		p			= &dst_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);

		//2)"mov ebx, byte[
		dst_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		dst_str[total_len]	= ',';
		total_len++;
	}
		
	p			= &dst_str[total_len];
	strcopy(p ,dst_name);
	total_len		+=strlen(p);

	if(dst_len)
	{
		//4)"mov ebx, byte[0x111111]
		dst_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	dst_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	idstexp	= malloc(sizeof(struct ins_exp));

	if(idstexp)
	{
		strcopy(idstexp->str ,dst_str);
		idstexp->str[strlen(idstexp->str)]= NULL;

		idstexp->head		= NULL;
		idstexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *idstelist	= iexplist_build(idstexp);

	//8)
	ins_add2explist(idstelist, iexplist);

	//------------------------------------------------------------------
	// result	::cmp	eax, ebx
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tcmp	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,", ");
	total_len		+=strlen(p);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	iresexp	= malloc(sizeof(struct ins_exp));

	if(iresexp)
	{
		strcopy(iresexp->str ,ins_temp_buf);
		iresexp->str[strlen(iresexp->str)]= NULL;

		iresexp->head		= NULL;
		iresexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ireselist	= iexplist_build(iresexp);

	//4)
	ins_add2explist(ireselist, iexplist);

	//------------------------------------------------------------------
	// ja	label_1(true label)
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tjae	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,tl);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	itlexp	= malloc(sizeof(struct ins_exp));

	if(itlexp)
	{
		strcopy(itlexp->str ,ins_temp_buf);
		itlexp->str[strlen(itlexp->str)]= NULL;

		itlexp->head		= NULL;
		itlexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *itlelist	= iexplist_build(itlexp);

	//4)
	ins_add2explist(itlelist, iexplist);

	//------------------------------------------------------------------
	// jmp false_label
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tjmp	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,fl);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	itlexp_1	= malloc(sizeof(struct ins_exp));

	if(itlexp_1)
	{
		strcopy(itlexp_1->str ,ins_temp_buf);
		itlexp_1->str[strlen(itlexp_1->str)]= NULL;

		itlexp_1->head		= NULL;
		itlexp_1->tail		= NULL;		
	}

	//3)
	struct ins_explist *itlelist_1	= iexplist_build(itlexp_1);

	//4)
	ins_add2explist(itlelist_1, iexplist);

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_above_equal_build(e) -- \n\n");
#endif
//--------------------------	
}


//===========================================================================
// ins_low_equal_build
//===========================================================================
PUBLIC	struct ins*	ins_low_equal_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst, s8 *tl, s8 *fl, s8 *el)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_low_equal_build(s) -- \n");
#endif
//--------------------------

	s8	*src_name, *dst_name, *res_name;
	u32	src_len, dst_len, res_len;	

	src_len	= exp->e.low_equal.src_len;
	dst_len	= exp->e.low_equal.dst_len;

	src_name= exp->e.low_equal.src_name;
	dst_name= exp->e.low_equal.dst_name;
	
	//------------------------------------------------------------------
	// source	:: mov	ebx, byte[src_addr]
	//------------------------------------------------------------------
	s32 total_len	= 0;
	s8	*p	= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);

	s8 src_str[INS_LEN];
	empty_buf(src_str, INS_LEN);
	strcopy(src_str , "\tmov	");
			
	total_len		= strlen(src_str);
	p			= &src_str[total_len];

	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	//1) "mov ebx, byte"
	if(src_len != 0)
	{
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(src_len,  ins_temp_buf);
	
		src_str[total_len]	= ',';
		total_len++;
		src_str[total_len]	= ' ';
		total_len		= strlen(src_str);
		p			= &src_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);
	
		//2)"mov ebx, byte[
		src_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		src_str[total_len]	= ',';
		total_len++;
	}
	
	
	p			= &src_str[total_len];
	strcopy(p ,src_name);
	total_len		+=strlen(p);

	if(src_len)
	{
		//4)"mov ebx, byte[0x111111]
		src_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	src_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	isrcexp	= malloc(sizeof(struct ins_exp));

	if(isrcexp)
	{
		strcopy(isrcexp->str ,src_str);
		isrcexp->str[strlen(isrcexp->str)]= NULL;

		isrcexp->head		= NULL;
		isrcexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *isrcelist	= iexplist_build(isrcexp);

	//8)
	ins_add2explist(isrcelist, iexplist);

	//------------------------------------------------------------------
	// dest	::	mov	eax, byte[dst_addr]
	//------------------------------------------------------------------
	
	total_len	= 0;
	p		= NULL;

	//1) "mov	"
	empty_buf(ins_temp_buf, INS_LEN);
		
	s8 dst_str[INS_LEN];
	empty_buf(dst_str, INS_LEN);
	strcopy(dst_str , "\tmov	");

	total_len		= strlen(dst_str);
	p			= &dst_str[total_len];

	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	//1) "mov eax, byte"
	if(dst_len != 0)
	{
		empty_buf(ins_temp_buf, INS_LEN);
		ins_type(dst_len,  ins_temp_buf);
	
		dst_str[total_len]	= ',';
		total_len++;
		dst_str[total_len]	= ' ';
		total_len		= strlen(dst_str);
		p			= &dst_str[total_len];

		strcopy(p ,ins_temp_buf);
		total_len		+=strlen(p);

		//2)"mov ebx, byte[
		dst_str[total_len]	= '[';
		total_len++;
	}
	else
	{
		dst_str[total_len]	= ',';
		total_len++;
	}
		
	p			= &dst_str[total_len];
	strcopy(p ,dst_name);
	total_len		+=strlen(p);

	if(dst_len)
	{
		//4)"mov ebx, byte[0x111111]
		dst_str[total_len]	= ']';
		total_len++;
	}

	//5)"mov ebx, byte[0x111111]
	dst_str[total_len]	= NULL;
	
	//6)
	struct ins_exp*	idstexp	= malloc(sizeof(struct ins_exp));

	if(idstexp)
	{
		strcopy(idstexp->str ,dst_str);
		idstexp->str[strlen(idstexp->str)]= NULL;

		idstexp->head		= NULL;
		idstexp->tail		= NULL;		
	}

	//7)
	struct ins_explist *idstelist	= iexplist_build(idstexp);

	//8)
	ins_add2explist(idstelist, iexplist);

	//------------------------------------------------------------------
	// result	::cmp	eax, ebx
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tcmp	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,&regs[reg_src]);
	total_len		+=strlen(p);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,", ");
	total_len		+=strlen(p);

	p			= &ins_temp_buf[total_len];
	strcopy(p ,&regs[reg_dst]);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	iresexp	= malloc(sizeof(struct ins_exp));

	if(iresexp)
	{
		strcopy(iresexp->str ,ins_temp_buf);
		iresexp->str[strlen(iresexp->str)]= NULL;

		iresexp->head		= NULL;
		iresexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *ireselist	= iexplist_build(iresexp);

	//4)
	ins_add2explist(ireselist, iexplist);

	//------------------------------------------------------------------
	// ja	label_1(true label)
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tjbe	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,tl);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	itlexp	= malloc(sizeof(struct ins_exp));

	if(itlexp)
	{
		strcopy(itlexp->str ,ins_temp_buf);
		itlexp->str[strlen(itlexp->str)]= NULL;

		itlexp->head		= NULL;
		itlexp->tail		= NULL;		
	}

	//3)
	struct ins_explist *itlelist	= iexplist_build(itlexp);

	//4)
	ins_add2explist(itlelist, iexplist);

	//------------------------------------------------------------------
	// jmp false_label
	//------------------------------------------------------------------
	total_len	= 0;
	p		= NULL;

	//1) "mov ebx, byte"
	empty_buf(ins_temp_buf, INS_LEN);
	
	p			= &ins_temp_buf[total_len];
	strcopy(ins_temp_buf, "\tjmp	");
	total_len		=strlen(ins_temp_buf);
	
	p			= &ins_temp_buf[total_len];
	strcopy(p ,fl);
	total_len		+=strlen(p);

	ins_temp_buf[total_len]	= NULL;

	//2)
	struct ins_exp*	itlexp_1	= malloc(sizeof(struct ins_exp));

	if(itlexp_1)
	{
		strcopy(itlexp_1->str ,ins_temp_buf);
		itlexp_1->str[strlen(itlexp_1->str)]= NULL;

		itlexp_1->head		= NULL;
		itlexp_1->tail		= NULL;		
	}

	//3)
	struct ins_explist *itlelist_1	= iexplist_build(itlexp_1);

	//4)
	ins_add2explist(itlelist_1, iexplist);

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_low_equal_build(e) -- \n\n");
#endif
//--------------------------	
}
