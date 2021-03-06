//===========================================================================
// ir_main.c
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
#include 	<math.h>
#include	"dnasm_main.h"
#include	"dnasm_lex_char.h"
#include	"dnasm_lex_word.h"
#include	"dnasm_parse.h"
#include	"dnasm_seman.h"
#include	"dnasm_frame.h"
#include	"dnasm_ir.h"
#include	"dnasm_prototype.h"

#define	IR_DEBUG

PRIVATE	s8 	ir_temp_buf[IR_NAME_LEN];
//===========================================================================
// abop_build()
//===========================================================================
PUBLIC	void	ir_init()
{
	cur_file	= file_build(NULL);
}

//===========================================================================
// file_build
//===========================================================================
PUBLIC	struct ir_file *	file_build(struct ir_stslist *stslist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- file_build  -- \n");
#endif
//--------------------------

	struct ir_file *ret_file	= malloc(sizeof(struct ir_file));

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
PUBLIC	s8	ir_add2file(struct ir_file *src, struct ir_file * dst)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_add2file  -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}

//===========================================================================
// sts_build()
//===========================================================================
PUBLIC	struct ir_sts *	sts_build()
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- sts_build  -- \n");
#endif
//--------------------------

	struct ir_sts *ret_sts	= malloc(sizeof(struct ir_sts));

	if(!ret_sts)
	{
		printf("ir_sts() malloc failed!!\n");
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// stslist_build()
//===========================================================================
PUBLIC	struct ir_stslist *	stslist_build(struct ir_sts *sts)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- stslist_build  -- \n");
#endif
//--------------------------

	struct ir_stslist *ret_stslist	= malloc(sizeof(struct ir_stslist));

	if(!ret_stslist)
	{
		printf("ir_stslist() malloc failed!!\n");
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
PUBLIC	s8	ir_add2stslist(struct ir_stslist *src, struct ir_stslist * dst)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_add2stslist  -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}

//===========================================================================
// exp_build()
//===========================================================================
PUBLIC	struct ir_explist *	explist_build(struct ir_exp *exp)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- explist_build  -- \n");
#endif
//--------------------------

	struct ir_explist *ret_explist	= malloc(sizeof(struct ir_explist));

	if(!ret_explist)
	{
		printf("explist_build() malloc failed!!\n");
		exit(1);
	}

	ret_explist->exp	= exp;
	ret_explist->head	= NULL;
	ret_explist->tail	= NULL;

	return ret_explist;
}

//===========================================================================
// ir_add2explist
//===========================================================================
PUBLIC	s8	ir_add2explist(struct ir_explist *src, struct ir_explist * dst)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_add2explist  -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}


//===========================================================================
// var_exp_build(struct s_var *v)
//===========================================================================
PUBLIC	struct ir_exp *	ir_var_exp_build(struct s_var *v)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_var_exp_build  -- \n");
#endif
//--------------------------

	struct symbol *	sym 	= symtbl_search(v->var_name);

	if(!sym)
	{
		struct s_var*	v_1 = search_var_s(v->var_name);

		if(!v_1)
		{
			printf("[error]::ir_var_exp_build, sym not exist!!! \n\n");
			exit(1);
		}
	}

	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	if(ret_exp)
	{
		ret_exp->k		= IR_EXP_VARADDR;
		ret_exp->e.var.pvar	= v;

		ret_exp->e.var.var_len	= v->len;
		ret_exp->e.var.var_type	= v->type_id;

		strcopy(ret_exp->e.var.name, v->var_name);
		ret_exp->e.var.name[strlen(ret_exp->e.var.name)]	= NULL;	

		strcopy(ret_exp->e.var.label, ret_exp->e.var.name);
		ret_exp->e.var.label[strlen(ret_exp->e.var.label)]	= NULL;

		ret_exp->e.var.var_id	= v->var_id;
		
		ret_exp->e.var.align_1	= NULL;
		ret_exp->e.var.align_2	= NULL;
	}
	else
	{
		printf("var_exp_build() malloc failed!!\n");
		exit(1);
	}

	return ret_exp;
}


//===========================================================================
// var_exp_build(struct s_var *v)
//===========================================================================
PUBLIC	struct ir_exp *	ir_string_exp_build(s8 *str)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- string_exp_build  -- \n");
#endif
//--------------------------

	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	if(ret_exp)
	{
		s32 len_t	= strlen(str);

		ret_exp->k		= IR_EXP_VARADDR;
		ret_exp->e.var.var_addr	= (s8*)malloc(len_t);
		ret_exp->e.var.var_len	= len_t;
		ret_exp->e.var.var_type	= BYTE;
		ret_exp->e.var.pvar	= NULL;

		s8 *p = (s8*)(ret_exp->e.var.var_addr);
		strcopy(p , str);
		*(p + len_t)	= NULL;	

		ret_exp->e.var.align_1	= NULL;
		ret_exp->e.var.align_2	= NULL;
	}
	else
	{
		printf("string_exp_build() malloc failed!!\n");
		exit(1);
	}

	return ret_exp;
}


//===========================================================================
// const_exp_build(struct s_var *v)
//===========================================================================
PUBLIC	struct ir_exp *	ir_const_exp_build(s32 num)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- const_exp_build(s)  -- \n");
#endif
//--------------------------

	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	if(ret_exp)
	{
		s8	ins_temp_buf[IR_NAME_LEN];

		s32 len_t	= sizeof(s32*);

		ret_exp->k		= IR_EXP_VARADDR;
		ret_exp->e.var.var_addr	= (s32*)malloc(len_t);

		ret_exp->e.var.var_len	= 0;
		ret_exp->e.var.var_type	= DWORD;
		ret_exp->e.var.pvar	= NULL;

		ret_exp->e.var.align_1	= NULL;
		ret_exp->e.var.align_2	= NULL;

		switch(ret_exp->e.var.var_type)
		{
			case DWORD:
				*(s32*)(ret_exp->e.var.var_addr) = num;					
				
				empty_buf(ins_temp_buf, IR_NAME_LEN);
				h2s(num, ins_temp_buf);
			
				strcopy(ret_exp->e.var.label ,ins_temp_buf);
				ret_exp->e.var.label[strlen(ret_exp->e.var.label)]	= NULL;
				break;
			default:
				break;
		}
	}
	else
	{
		printf("const_exp_build() malloc failed!!\n");
		exit(1);
	}

//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- const_exp_build(e)  -- \n");
#endif
//--------------------------

	return ret_exp;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_movsts_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_movsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= malloc(sizeof(struct ir_sts));

	if(!ret_sts)
	{
		printf("ir_movsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= IR_STS_MOV;
	ret_sts->s.mov_sts.explist	= explist;

	return ret_sts;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_addsts_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_addsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= malloc(sizeof(struct ir_sts));

	if(!ret_sts)
	{
		printf("ir_addsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= IR_STS_ADD;
	ret_sts->s.add_sts.explist	= explist;

	return ret_sts;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_substs_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_substs_build  -- \n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= malloc(sizeof(struct ir_sts));

	if(!ret_sts)
	{
		printf("ir_substs_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= IR_STS_SUB;
	ret_sts->s.sub_sts.explist	= explist;

	return ret_sts;
}


//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_mulsts_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_mulsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= malloc(sizeof(struct ir_sts));

	if(!ret_sts)
	{
		printf("ir_mulsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= IR_STS_MUL;
	ret_sts->s.mul_sts.explist	= explist;

	return ret_sts;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_divsts_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_divsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= malloc(sizeof(struct ir_sts));

	if(!ret_sts)
	{
		printf("ir_divsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= IR_STS_DIV;
	ret_sts->s.div_sts.explist	= explist;

	return ret_sts;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_callsts_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_callsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= malloc(sizeof(struct ir_sts));

	if(!ret_sts)
	{
		printf("ir_callsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= IR_STS_CALL;
	ret_sts->s.call_sts.explist	= explist;

	return ret_sts;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_retsts_build()
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_retsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= malloc(sizeof(struct ir_sts));

	if(!ret_sts)
	{
		printf("ir_retsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= IR_STS_RET;
	
	return ret_sts;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_jmpsts_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_jmpsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * jmp_sts	= malloc(sizeof(struct ir_sts));

	if(!jmp_sts)
	{
		printf("ir_jmpsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	jmp_sts->k	= IR_STS_JMP;
	jmp_sts->s.jmp_sts.explist	= explist;

	return jmp_sts;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_jasts_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_jasts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * ja_sts	= malloc(sizeof(struct ir_sts));

	if(!ja_sts)
	{
		printf("ir_jasts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	ja_sts->k	= IR_STS_JA;
	ja_sts->s.ja_sts.explist	= explist;

	return ja_sts;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_jbsts_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_jbsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * jb_sts	= malloc(sizeof(struct ir_sts));

	if(!jb_sts)
	{
		printf("ir_jbsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	jb_sts->k	= IR_STS_JB;
	jb_sts->s.jb_sts.explist	= explist;

	return jb_sts;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_jests_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_jests_build  -- \n");
#endif
//--------------------------

	struct ir_sts * je_sts	= malloc(sizeof(struct ir_sts));

	if(!je_sts)
	{
		printf("ir_jests_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	je_sts->k	= IR_STS_JE;
	je_sts->s.je_sts.explist	= explist;

	return je_sts;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_jaests_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_jaests_build  -- \n");
#endif
//--------------------------

	struct ir_sts * jae_sts	= malloc(sizeof(struct ir_sts));

	if(!jae_sts)
	{
		printf("ir_jaests_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	jae_sts->k	= IR_STS_JAE;
	jae_sts->s.jae_sts.explist	= explist;

	return jae_sts;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_jbests_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_jbests_build  -- \n");
#endif
//--------------------------

	struct ir_sts * jbe_sts	= malloc(sizeof(struct ir_sts));

	if(!jbe_sts)
	{
		printf("ir_jbests_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	jbe_sts->k	= IR_STS_JBE;
	jbe_sts->s.jbe_sts.explist	= explist;

	return jbe_sts;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_jnests_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_jnests_build  -- \n");
#endif
//--------------------------

	struct ir_sts * jne_sts	= malloc(sizeof(struct ir_sts));

	if(!jne_sts)
	{
		printf("ir_jnests_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	jne_sts->k	= IR_STS_JNE;
	jne_sts->s.jne_sts.explist	= explist;

	return jne_sts;
}


//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_pushsts_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_pushsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * push_sts	= malloc(sizeof(struct ir_sts));

	if(!push_sts)
	{
		printf("ir_pushsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	push_sts->k	= IR_STS_PUSH;
	push_sts->s.push_sts.explist	= explist;

	return push_sts;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_popsts_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_popsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * pop_sts	= malloc(sizeof(struct ir_sts));

	if(!pop_sts)
	{
		printf("ir_popsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	pop_sts->k	= IR_STS_POP;
	pop_sts->s.pop_sts.explist	= explist;

	return pop_sts;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_cmpsts_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_cmpsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * cmp_sts	= malloc(sizeof(struct ir_sts));

	if(!cmp_sts)
	{
		printf("ir_cmpsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	cmp_sts->k	= IR_STS_CMP;
	cmp_sts->s.cmp_sts.explist	= explist;

	return cmp_sts;
}

//===========================================================================
// abop_exp_build
//===========================================================================
PUBLIC	struct ir_exp *	ir_abop_exp_build(s32 op, struct ir_exp *left, struct ir_exp *right)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_abop_exp_build  -- \n");
#endif
//--------------------------

	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	if(ret_exp)
	{
		ret_exp->k		= IR_EXP_ABOP;
		ret_exp->e.abop.left	= left;
		ret_exp->e.abop.right	= right;		
		ret_exp->s		= IR_MEM;
	}
	else
	{
		printf("abop_exp_build() malloc failed!!\n");
		exit(1);
	}

	return ret_exp;
}

//===========================================================================
// ir_label_exp_build
//===========================================================================
PUBLIC	struct ir_exp *	ir_label_exp_build(s8 *label_name, u32 label_id)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_label_exp_build  -- \n");
#endif
//--------------------------

	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	if(ret_exp)
	{
		ret_exp->k			= IR_EXP_LABEL;
		ret_exp->e.label.label_name	= label_name;
		ret_exp->e.label.label_id	= label_id;	
		ret_exp->e.label.align_1	= NULL;	
	}
	else
	{
		printf("ir_label_exp_build() malloc failed!!\n");
		exit(1);
	}

	return ret_exp;
}

//===========================================================================
// ir_labelsts_build
//===========================================================================
PUBLIC	struct ir_sts *	ir_labelsts_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_labelsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= malloc(sizeof(struct ir_sts));

	if(!ret_sts)
	{
		printf("ir_labelsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= IR_STS_LABEL;
	ret_sts->s.label_sts.explist	= explist;

	return ret_sts;
}


//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_xorsts_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_xorsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= malloc(sizeof(struct ir_sts));

	if(!ret_sts)
	{
		printf("ir_xorsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= IR_STS_XOR;
	ret_sts->s.add_sts.explist	= explist;

	return ret_sts;
}


//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_intsts_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_intsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * int_sts	= malloc(sizeof(struct ir_sts));

	if(!int_sts)
	{
		printf("ir_intsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	int_sts->k	= IR_STS_INT;
	int_sts->s.int_sts.explist	= explist;

	return int_sts;
}
