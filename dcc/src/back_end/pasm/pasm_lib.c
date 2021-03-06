//===========================================================================
// ir_code_lib.c
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
#include	"dcc_prototype.h"

#define	PASM_DEBUG

//===========================================================================
// add(u32 src, u32 dst)
//===========================================================================
PUBLIC	struct pasm_exp*	add(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- add -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_ADD;

	p->e.add.src_reg	= src;
	p->e.add.src_id		= src_id;
	p->e.add.dst_reg	= dst;
	p->e.add.dst_id		= dst_id;

	p->e.add.src_len	= src_len;
	p->e.add.dst_len	= dst_len;

	strcopy(p->e.add.src_name, src_name);
	p->e.add.src_name[strlen(p->e.add.src_name)]	= NULL;	

	strcopy(p->e.add.dst_name, dst_name);
	p->e.add.dst_name[strlen(p->e.add.dst_name)]	= NULL;	

	return	p;
}

//===========================================================================
// minus(u32 src, u32 dst)
//===========================================================================
PUBLIC	struct pasm_exp*	minus(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- minus -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_MINUS;

	p->e.minus.src_reg		= src;
	p->e.minus.src_id	= src_id;
	p->e.minus.dst_reg		= dst;
	p->e.minus.dst_id	= dst_id;

	p->e.minus.src_len	= src_len;
	p->e.minus.dst_len	= dst_len;

	strcopy(p->e.minus.src_name, src_name);
	p->e.minus.src_name[strlen(p->e.minus.src_name)]	= NULL;	

	strcopy(p->e.minus.dst_name, dst_name);
	p->e.minus.dst_name[strlen(p->e.minus.dst_name)]	= NULL;	

	return	p;	
}

//===========================================================================
// minus(u32 src, u32 dst)
//===========================================================================
PUBLIC	struct pasm_exp*	mul(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- mul -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_MUL;

	p->e.mul.src_reg		= src;
	p->e.mul.src_id	= src_id;
	p->e.mul.dst_reg		= dst;
	p->e.mul.dst_id	= dst_id;

	p->e.mul.src_len	= src_len;
	p->e.mul.dst_len	= dst_len;

	strcopy(p->e.mul.src_name, src_name);
	p->e.mul.src_name[strlen(p->e.mul.src_name)]	= NULL;	

	strcopy(p->e.mul.dst_name, dst_name);
	p->e.mul.dst_name[strlen(p->e.mul.dst_name)]	= NULL;	

	return	p;	
}

//===========================================================================
// minus(u32 src, u32 dst)
//===========================================================================
PUBLIC	struct pasm_exp*	div(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- div -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_DIV;

	p->e.div.src_reg		= src;
	p->e.div.src_id	= src_id;
	p->e.div.dst_reg		= dst;
	p->e.div.dst_id	= dst_id;
	
	p->e.div.src_len	= src_len;
	p->e.div.dst_len	= dst_len;

	strcopy(p->e.div.src_name, src_name);
	p->e.div.src_name[strlen(p->e.div.src_name)]	= NULL;	

	strcopy(p->e.div.dst_name, dst_name);
	p->e.div.dst_name[strlen(p->e.div.dst_name)]	= NULL;	

	return	p;	
}

//===========================================================================
// minus(u32 src, u32 dst)
//===========================================================================
PUBLIC	struct pasm_exp*	mod(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- mod -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_MOD;

	p->e.mod.src_reg		= src;
	p->e.mod.src_id	= src_id;
	p->e.mod.dst_reg		= dst;
	p->e.mod.dst_id	= dst_id;
	
	p->e.mod.src_len	= src_len;
	p->e.mod.dst_len	= dst_len;

	strcopy(p->e.mod.src_name, src_name);
	p->e.mod.src_name[strlen(p->e.mod.src_name)]	= NULL;	

	strcopy(p->e.mod.dst_name, dst_name);
	p->e.mod.dst_name[strlen(p->e.mod.dst_name)]	= NULL;	

	return	p;	
}

//===========================================================================
// move(u32 *addr, u32 val)
//===========================================================================
PUBLIC	struct pasm_exp *	move(s32 res_id, u32 res_addr, u32 res_type_len, u32 val_addr, u32 val_type_len, s8 *res_name, s8* val_name)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- move -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_MOV;

	p->e.move.res_id	= res_id;
	p->e.move.res_reg	= res_addr;
	p->e.move.res_type_len	= res_type_len;
	p->e.move.val		= val_addr;
	p->e.move.val_type_len	= val_type_len;	

	strcopy(p->e.move.res_name, res_name);
	p->e.move.res_name[strlen(p->e.move.res_name)]	= NULL;	

	strcopy(p->e.move.val_name, val_name);
	p->e.move.val_name[strlen(p->e.move.val_name)]	= NULL;	
	
	return	p;
}


//===========================================================================
//cmp(u32 left, u32 right)
//===========================================================================
PUBLIC	struct pasm_exp *	cmp(u32 left, u32 left_id,u32 left_len, u32 right, u32 right_id, u32 right_len, u32 op)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- cmp -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_CMP;

	p->e.cmp.left		= left;
	p->e.cmp.left_type_len	= left_len;
	p->e.cmp.left_id	= left_id;
	p->e.cmp.right		= right;
	p->e.cmp.right_type_len	= right_len;
	p->e.cmp.right_id	= right_id;
	p->e.cmp.op		= op;
	
	return	p;

	
}

//===========================================================================
//jump(struct relate *cond, u32 label_1, u32 label_2)
//===========================================================================
PUBLIC	struct pasm_exp *	jump(struct pasm_exp  *cond, u32 label_1, u32 label_2)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- jump -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_JUMP;

	p->e.jump.cond		= cond;
	p->e.jump.label_1	= label_1;
	p->e.jump.label_2	= label_2;
		
	return	p;
}

//===========================================================================
// mem(u32 *addr, u32 offset)
//===========================================================================
PUBLIC	struct pasm_exp *	mem(s32 id, u32 *addr, u32 type_len, u32 num, s8 *name)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- mem -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_MEM;

	p->e.mem.id		= id;
	p->e.mem.addr		= addr;
	p->e.mem.type_len	= type_len;
	p->e.mem.num		= num;

	strcopy(p->e.mem.src_name, name);
	p->e.mem.src_name[strlen(p->e.mem.src_name)]	= NULL;	
		
	return	p;
}

//===========================================================================
// load(u32 *addr, u32 offset)
//===========================================================================
PUBLIC	struct pasm_exp *	load(s32 id, u32 *addr, u32 type_len, u32 num)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- load -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_LOAD_MEM;

	struct pasm_exp *m	= mem(id, addr, type_len, num, NULL);

	p->e.load.m		= m;
				
	return	p;
}

//===========================================================================
// save(u32 *addr, u32 offset, u32 val)
//===========================================================================
PUBLIC	struct pasm_exp *	save(s32 id, u32 *addr, u32 type_len, u32 num, u32 val)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- save -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_SAVE_MEM;

	struct pasm_exp *m	= mem(id, addr, type_len, num, NULL);

	p->e.save.val		= val;
			
	return	p;
	
}

//===========================================================================
// call(s8* label, struct ir_pvlist *pvlist)
//===========================================================================
PUBLIC	struct pasm_exp *	call(s8* label, struct pasm_explist *ppv, u32 ret_len, u32 ret_addr)
//PUBLIC	struct pasm_exp *	call(s8* label, struct ir_exp *ppv, u32 ret_len, u32 ret_addr)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- call -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_CALL;

	p->e.call.label_name	= label;	
	p->e.call.ppv		= ppv;
	p->e.call.ret_addr	= ret_addr;
	p->e.call.ret_len	= ret_len;
	
	return	p;
	
}

//===========================================================================
// label(s8* label_name, u32 id)
//===========================================================================
PUBLIC	struct pasm_exp *	label(s8* label_name, u32 id)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- label -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	if(p)
	{
		p->k			= PASM_LABEL;
		p->e.label.label_name	= label_name;
		p->e.label.label_id	= id;
	}
	
	return	p;
	
}


//===========================================================================
// push(u32 var_addr, u32 var_type_len, s8 *name)
//===========================================================================
PUBLIC	struct pasm_exp *	push(u32 var_addr, u32 var_type_len, s8 *name)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- push -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_PUSH;

	p->e.push.var_addr	= var_addr;
	p->e.push.var_len	= var_type_len;
	
	strcopy(p->e.push.name, name);
	p->e.push.name[strlen(p->e.push.name)]	= NULL;	
	
	return	p;
}

//===========================================================================
// pop(u32 var_addr, u32 var_type_len, s8 *name)
//===========================================================================
PUBLIC	struct pasm_exp *	pop(u32 var_addr, u32 var_type_len, s8 *name)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- pop -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_POP;

	p->e.pop.var_addr	= var_addr;
	p->e.pop.var_len	= var_type_len;
	
	strcopy(p->e.pop.name, name);
	p->e.pop.name[strlen(p->e.pop.name)]	= NULL;	
	
	return	p;
}



//===========================================================================
// pop(u32 var_addr, u32 var_type_len, s8 *name)
//===========================================================================
PUBLIC	void	reset_pasm(struct pasm_exp *pe)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- reset pasm -- \n");
#endif
//--------------------------

	s32 len	= sizeof(struct pasm_exp);

	s32 i;
	for(i=0; i<len; i++)
	{
		*((s8*)pe+i)	= NULL;
	}
}


//===========================================================================
// above(u32 src, u32 dst)
//===========================================================================
PUBLIC	struct pasm_exp*	above(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl, s8 *fl, s8 *el)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- above -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_ABOVE;

	p->e.above.src_reg		= src;
	p->e.above.src_id	= src_id;
	p->e.above.dst_reg		= dst;
	p->e.above.dst_id	= dst_id;
	
	p->e.above.src_len	= src_len;
	p->e.above.dst_len	= dst_len;

	strcopy(p->e.above.src_name, src_name);
	p->e.above.src_name[strlen(p->e.above.src_name)]	= NULL;	

	strcopy(p->e.above.dst_name, dst_name);
	p->e.above.dst_name[strlen(p->e.above.dst_name)]	= NULL;	

	strcopy(p->e.above.t_label, tl);
	p->e.above.t_label[strlen(p->e.above.t_label)]		= NULL;	

	strcopy(p->e.above.f_label, fl);
	p->e.above.f_label[strlen(p->e.above.f_label)]		= NULL;	

	strcopy(p->e.above.e_label, el);
	p->e.above.e_label[strlen(p->e.above.e_label)]		= NULL;	

	return	p;

	
}

//===========================================================================
// low(u32 src, u32 dst)
//===========================================================================
PUBLIC	struct pasm_exp*	low(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl, s8 *fl, s8 *el)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- low -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_LOW;

	p->e.low.src_reg		= src;
	p->e.low.src_id	= src_id;
	p->e.low.dst_reg		= dst;
	p->e.low.dst_id	= dst_id;
	
	p->e.low.src_len	= src_len;
	p->e.low.dst_len	= dst_len;

	strcopy(p->e.low.src_name, src_name);
	p->e.low.src_name[strlen(p->e.low.src_name)]	= NULL;	

	strcopy(p->e.low.dst_name, dst_name);
	p->e.low.dst_name[strlen(p->e.low.dst_name)]	= NULL;	

	strcopy(p->e.low.t_label, tl);
	p->e.low.t_label[strlen(p->e.low.t_label)]		= NULL;	

	strcopy(p->e.low.f_label, fl);
	p->e.low.f_label[strlen(p->e.low.f_label)]		= NULL;	

	strcopy(p->e.low.e_label, el);
	p->e.low.e_label[strlen(p->e.low.e_label)]		= NULL;

	return	p;	
}


//===========================================================================
// equal(u32 src, u32 dst)
//===========================================================================
PUBLIC	struct pasm_exp*	equal(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl, s8 *fl, s8 *el)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- equal -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_EQUAL;

	p->e.equal.src_reg		= src;
	p->e.equal.src_id	= src_id;
	p->e.equal.dst_reg		= dst;
	p->e.equal.dst_id	= dst_id;
	
	p->e.equal.src_len	= src_len;
	p->e.equal.dst_len	= dst_len;

	strcopy(p->e.equal.src_name, src_name);
	p->e.equal.src_name[strlen(p->e.equal.src_name)]	= NULL;	

	strcopy(p->e.equal.dst_name, dst_name);
	p->e.equal.dst_name[strlen(p->e.equal.dst_name)]	= NULL;	

	strcopy(p->e.equal.t_label, tl);
	p->e.equal.t_label[strlen(p->e.equal.t_label)]		= NULL;	

	strcopy(p->e.equal.f_label, fl);
	p->e.equal.f_label[strlen(p->e.equal.f_label)]		= NULL;	

	strcopy(p->e.equal.e_label, el);
	p->e.equal.e_label[strlen(p->e.equal.e_label)]		= NULL;

	return	p;	
}

//===========================================================================
// not_equal(u32 src, u32 dst)
//===========================================================================
PUBLIC	struct pasm_exp*	not_equal(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl, s8 *fl, s8 *el)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- not_equal -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_NOT_EQUAL;

	p->e.not_equal.src_reg		= src;
	p->e.not_equal.src_id	= src_id;
	p->e.not_equal.dst_reg		= dst;
	p->e.not_equal.dst_id	= dst_id;
	
	p->e.not_equal.src_len	= src_len;
	p->e.not_equal.dst_len	= dst_len;

	strcopy(p->e.not_equal.src_name, src_name);
	p->e.not_equal.src_name[strlen(p->e.not_equal.src_name)]	= NULL;	

	strcopy(p->e.not_equal.dst_name, dst_name);
	p->e.not_equal.dst_name[strlen(p->e.not_equal.dst_name)]	= NULL;	

	strcopy(p->e.not_equal.t_label, tl);
	p->e.not_equal.t_label[strlen(p->e.not_equal.t_label)]		= NULL;	

	strcopy(p->e.not_equal.f_label, fl);
	p->e.not_equal.f_label[strlen(p->e.not_equal.f_label)]		= NULL;	

	strcopy(p->e.not_equal.e_label, el);
	p->e.not_equal.e_label[strlen(p->e.not_equal.e_label)]		= NULL;

	return	p;	
}

//===========================================================================
// above_equal(u32 src, u32 dst)
//===========================================================================
PUBLIC	struct pasm_exp*	above_equal(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl, s8 *fl, s8 *el)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- above_equal -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_ABOVE_EQUAL;

	p->e.above_equal.src_reg		= src;
	p->e.above_equal.src_id	= src_id;
	p->e.above_equal.dst_reg		= dst;
	p->e.above_equal.dst_id	= dst_id;
	
	p->e.above_equal.src_len	= src_len;
	p->e.above_equal.dst_len	= dst_len;

	strcopy(p->e.above_equal.src_name, src_name);
	p->e.above_equal.src_name[strlen(p->e.above_equal.src_name)]	= NULL;	

	strcopy(p->e.above_equal.dst_name, dst_name);
	p->e.above_equal.dst_name[strlen(p->e.above_equal.dst_name)]	= NULL;	

	strcopy(p->e.above_equal.t_label, tl);
	p->e.above_equal.t_label[strlen(p->e.above_equal.t_label)]		= NULL;	

	strcopy(p->e.above_equal.f_label, fl);
	p->e.above_equal.f_label[strlen(p->e.above_equal.f_label)]		= NULL;	

	strcopy(p->e.above_equal.e_label, el);
	p->e.above_equal.e_label[strlen(p->e.above_equal.e_label)]		= NULL;

	return	p;	
}

//===========================================================================
// low_equal(u32 src, u32 dst)
//===========================================================================
PUBLIC	struct pasm_exp*	low_equal(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl, s8 *fl, s8 *el)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- low_equal -- \n");
#endif
//--------------------------

	struct pasm_exp *p	= malloc(sizeof(struct pasm_exp));

	p->k			= PASM_LOW_EQUAL;

	p->e.low_equal.src_reg		= src;
	p->e.low_equal.src_id	= src_id;
	p->e.low_equal.dst_reg		= dst;
	p->e.low_equal.dst_id	= dst_id;
	
	p->e.low_equal.src_len	= src_len;
	p->e.low_equal.dst_len	= dst_len;

	strcopy(p->e.low_equal.src_name, src_name);
	p->e.low_equal.src_name[strlen(p->e.low_equal.src_name)]	= NULL;	

	strcopy(p->e.low_equal.dst_name, dst_name);
	p->e.low_equal.dst_name[strlen(p->e.low_equal.dst_name)]	= NULL;	

	strcopy(p->e.low_equal.t_label, tl);
	p->e.low_equal.t_label[strlen(p->e.low_equal.t_label)]		= NULL;	

	strcopy(p->e.low_equal.f_label, fl);
	p->e.low_equal.f_label[strlen(p->e.low_equal.f_label)]		= NULL;	

	strcopy(p->e.low_equal.e_label, el);
	p->e.low_equal.e_label[strlen(p->e.low_equal.e_label)]		= NULL;

	return	p;	
}
