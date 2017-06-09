//===========================================================================
// ir_main.c
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
#include 	<math.h>
#include	"dcc_main.h"
#include	"dcc_lex_char.h"
#include	"dcc_lex_word.h"
#include	"dcc_parse.h"
#include	"dcc_seman.h"
#include	"dcc_frame.h"
#include	"dcc_ir.h"
#include	"dcc_prototype.h"

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
// exp_build()
//===========================================================================
PUBLIC	struct ir_exp *	exp_build()
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- exp_build  -- \n");
#endif
//--------------------------

	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	if(!ret_exp)
	{
		printf("exp_build() malloc failed!!\n");
		exit(1);
	}

	return ret_exp;
}

//===========================================================================
// abop_build()
//===========================================================================
PUBLIC	struct ir_exp *	abop_build(struct ir_exp *left, struct ir_exp *right, u32 op)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- abop_build  -- \n");
#endif
//--------------------------

	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	ret_exp->e.abop.left	= left;
	ret_exp->e.abop.right	= right;
	ret_exp->e.abop.op	= op;

	return ret_exp;
}

//===========================================================================
// var_exp_build(struct s_var *v)
//===========================================================================
PUBLIC	struct ir_exp *	ir_var_exp_build(struct s_var *v)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- var_exp_build  -- \n");
#endif
//--------------------------

	s32	var_offset	= 0;
	s32 	i_var_offset	= 0;
	s8 	src_buf[IR_NAME_LEN];
	s32 	total_len	= 0;
	s8	*p	= NULL;
	
	s8 l_flg_pointer	= FALSE;
	struct symbol *	sym 	= symtbl_search(v->var_name);

	if(sym)
	{
		l_flg_pointer	= sym->flg_pointer;
		
		var_offset	= sym->i_var_offset;		
	}
	else
	{
		struct s_var*	v_1 = search_var_s(v->var_name);

		if(!v_1)
		{
			printf("[error]::ir_var_exp_build, sym not exist!!! \n\n");
			exit(1);
		}

		var_offset	= v_1->offset;		
	}
	
	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	if(ret_exp)
	{
		if(l_flg_pointer)
		{
			void *p	= malloc(sizeof(v->len));

			if(p)
			{
				ret_exp->k		= IR_VARADDR;
				ret_exp->e.var.pvar	= v;

				ret_exp->e.var.var_addr	= v->var_addr;
				ret_exp->e.var.var_len	= v->len;
				ret_exp->e.var.var_type	= v->type_id;

				strcopy(ret_exp->e.var.name, v->var_name);
				ret_exp->e.var.name[strlen(ret_exp->e.var.name)]	= NULL;	

				total_len	= 0;
				p		= NULL;

				empty_buf(src_buf, IR_NAME_LEN);

				strcopy(src_buf, "ebp");
				total_len	= strlen(src_buf);
				
				src_buf[total_len]	= (var_offset >= 0) ? '+' : '-';
				total_len++;

				p		= &src_buf[total_len];

				i_var_offset	= abs(var_offset);

				empty_buf(ir_temp_buf, IR_NAME_LEN);
				ir_temp_buf[0]	= '0';
				ir_temp_buf[1]	= 'x';
				h2s(i_var_offset, &ir_temp_buf[2]);

				strcopy(p ,ir_temp_buf);
				total_len		+=strlen(p);

				src_buf[total_len]	= NULL;
				
				strcopy(ret_exp->e.var.label, src_buf);
				ret_exp->e.var.label[strlen(ret_exp->e.var.label)]	= NULL;
				
				ret_exp->e.var.var_id	= v->var_id;			

				ret_exp->e.var.align_1	= NULL;
				ret_exp->e.var.align_2	= NULL;

				*(u32*)(v->var_addr)	= p;
			}
		}
		else
		{
			ret_exp->k		= IR_VARADDR;
			ret_exp->e.var.pvar	= v;

			ret_exp->e.var.var_addr	= v->var_addr;
			ret_exp->e.var.var_len	= v->len;
			ret_exp->e.var.var_type	= v->type_id;

			strcopy(ret_exp->e.var.name, v->var_name);
			ret_exp->e.var.name[strlen(ret_exp->e.var.name)]	= NULL;	
			
			total_len	= 0;
			p		= NULL;
			
			empty_buf(src_buf, IR_NAME_LEN);

			strcopy(src_buf, "ebp");
			total_len	= strlen(src_buf);
			
			src_buf[total_len]	= (var_offset >= 0) ? '+' : '-';
			total_len++;

			p		= &src_buf[total_len];
			
			i_var_offset	= abs(var_offset);			

			empty_buf(ir_temp_buf, IR_NAME_LEN);
			ir_temp_buf[0]	= '0';
			ir_temp_buf[1]	= 'x';
			h2s(i_var_offset, &ir_temp_buf[2]);
		
			strcopy(p ,ir_temp_buf);
			total_len		+=strlen(p);

			src_buf[total_len]	= NULL;

			strcopy(ret_exp->e.var.label, src_buf);
			ret_exp->e.var.label[strlen(ret_exp->e.var.label)]	= NULL;
			
			ret_exp->e.var.var_id	= v->var_id;
			
			ret_exp->e.var.align_1	= NULL;
			ret_exp->e.var.align_2	= NULL;
		}
	}
	else
	{
		printf("var_exp_build() malloc failed!!\n");
		exit(1);
	}

	return ret_exp;
}

//===========================================================================
// var_exp_update
//===========================================================================
PUBLIC	struct ir_exp*	ir_var_exp_update(struct ir_exp *exp, s8 *struct_member_name, s32 kind)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- var_exp_update  -- \n");
#endif
//--------------------------

	struct ir_exp*ret_exp;

	switch(kind)
	{
		case IR_STRUCT:
			ret_exp	= ir_var_exp_update_1(exp, struct_member_name);
			break;
		case IR_POINTER:
			ret_exp	= ir_var_exp_update_2(exp, struct_member_name);
			break;
		default:
			break;
	}

	return exp;
}




//===========================================================================
// var_exp_update_1::for struct
//===========================================================================
PUBLIC	struct ir_exp*	ir_var_exp_update_1(struct ir_exp *exp, s8 *struct_member_name)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- var_exp_update  -- \n");
#endif
//--------------------------
	
	s32	var_offset	= 0;
	s32 	i_var_offset	= 0;
	s8 	src_buf[IR_NAME_LEN];
	s32 	total_len	= 0;
	s8	*p	= NULL;
	
	struct symbol *	sym 	= symtbl_search(exp->e.var.pvar->var_name);

	if(sym)
	{
		var_offset	= sym->i_var_offset;
	}
	else
	{
		printf("[error]::ir_var_exp_update_1, sym not exist!!! \n\n");
		exit(1);
	}
	
	if(struct_member_name)
	{
		s8 flg = FALSE;
		struct s_type *t	= check_type_t(exp->e.var.pvar->true_type_id);

		struct member_list *mb	= &(t->mblist);
		for(; mb; mb=mb->tail)
		{
			if(strcmp(mb->name, struct_member_name) == TRUE)
			{
				flg = TRUE;
				break; 
			}
		}

		if(!flg)
		{
			printf("\n[error]::ir_var_exp_update_1::cur_var(%s) is not a structure member !! exit\n\n",struct_member_name);
			exit(1);
		}
		else
		{
			exp->k			= IR_VARADDR;
			exp->e.var.var_addr	= exp->e.var.pvar->var_addr + mb->m_offset;
			exp->e.var.var_len	= mb->len;
			exp->e.var.var_type	= mb->type_ts;

			s32 len	= strlen(exp->e.var.name);

			total_len	= 0;
			p		= NULL;
			
			empty_buf(src_buf, IR_NAME_LEN);

			strcopy(src_buf, "ebp");
			total_len	= strlen(src_buf);
			
			src_buf[total_len]	= (var_offset >= 0) ? '+' : '-'; 
			total_len++;

			i_var_offset	= abs(var_offset);
			empty_buf(ir_temp_buf, IR_NAME_LEN);
			ir_temp_buf[0]	= '0';
			ir_temp_buf[1]	= 'x';
			h2s(i_var_offset, &ir_temp_buf[2]);

			p		= &src_buf[total_len];
		
			strcopy(p ,ir_temp_buf);
			total_len	+=strlen(p);

			src_buf[total_len]	= (var_offset) ? '+' : '-'; 
			total_len++;

			empty_buf(ir_temp_buf, IR_NAME_LEN);

			i2s(mb->m_offset, &ir_temp_buf[0]);			
		
			p		= &src_buf[total_len];

			strcopy(p ,ir_temp_buf);
			total_len		+=strlen(p);

			src_buf[total_len]	= NULL;			

			strcopy(exp->e.var.label, src_buf);
			exp->e.var.label[strlen(exp->e.var.label)]	= NULL;

			exp->e.var.name[len]	= '.';
		
			strcopy(&(exp->e.var.name[len+1]), struct_member_name);
			exp->e.var.name[strlen(struct_member_name)+len+1]	= NULL;		
		}
	}
	
	return exp;
}


//===========================================================================
// var_exp_update_1::for pointer
//===========================================================================
PUBLIC	struct ir_exp*	ir_var_exp_update_2(struct ir_exp *exp, s8 *struct_member_name)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- var_exp_update_2  -- \n");
#endif
//--------------------------

	s32	var_offset	= 0;
	s32 	i_var_offset	= 0;
	s8 	src_buf[IR_NAME_LEN];
	s32 	total_len	= 0;
	s8	*p	= NULL;
	
	struct symbol *	sym 	= symtbl_search(exp->e.var.pvar->var_name);

	if(sym)
	{
		var_offset	= sym->i_var_offset;
	}
	else
	{
		printf("[error]::ir_var_exp_update_1, sym not exist!!! \n\n");
		exit(1);
	}

	s8 flg = FALSE;
	struct s_type *t	= check_type_t(exp->e.var.pvar->true_type_id);

	struct member_list *mb	= &(t->mblist);
	
	for(; mb; mb=mb->tail)
	{
		if(strcmp(mb->name, struct_member_name) == TRUE)
		{
			flg = TRUE;
			break; 
		}
	}

	if(!flg)
	{
		printf("\n[error]::ir_var_exp_update_2::cur_var(%s) is not a structure member !! exit\n\n",struct_member_name);
		exit(1);
	}
	else
	{
		exp->k			= IR_VARADDR;
		exp->e.var.var_addr	= exp->e.var.pvar->var_addr + mb->m_offset;
		exp->e.var.var_len	= mb->len;
		exp->e.var.var_type	= mb->type_ts;

		s32 len	= strlen(exp->e.var.name);
		
		total_len	= 0;
		p		= NULL;
			
		empty_buf(src_buf, IR_NAME_LEN);

		strcopy(src_buf, "ebp");
		total_len	= strlen(src_buf);
			
		src_buf[total_len]	= (var_offset >= 0) ? '+' : '-'; 
		total_len++;
		
		i_var_offset	= abs(var_offset);
		empty_buf(ir_temp_buf, IR_NAME_LEN);
		ir_temp_buf[0]	= '0';
		ir_temp_buf[1]	= 'x';
		h2s(i_var_offset, &ir_temp_buf[2]);

		p		= &src_buf[total_len];
		
		strcopy(p ,ir_temp_buf);
		total_len	+=strlen(p);

		src_buf[total_len]	= (var_offset) ? '+' : '-'; 
		total_len++;

		empty_buf(ir_temp_buf, IR_NAME_LEN);
		
		i2s(mb->m_offset, &ir_temp_buf[0]);
			
		p		= &src_buf[total_len];

		strcopy(p ,ir_temp_buf);
		total_len		+=strlen(p);

		src_buf[total_len]	= NULL;			
		strcopy(exp->e.var.label, src_buf);
		exp->e.var.label[strlen(exp->e.var.label)]	= NULL;		

		exp->e.var.name[len]	= '-';
		exp->e.var.name[len+1]	= '>';
		
		strcopy(&(exp->e.var.name[len+2]), struct_member_name);
		exp->e.var.name[strlen(struct_member_name)+len+2]	= NULL;	

	
	}	

	return exp;
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

		ret_exp->k		= IR_VARADDR;
		ret_exp->e.var.var_addr	= (s8*)malloc(len_t);
		ret_exp->e.var.var_len	= len_t;
		ret_exp->e.var.var_type	= CHAR;
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
	printf("	-- const_exp_build  -- \n");
#endif
//--------------------------

	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	if(ret_exp)
	{
		s8	ins_temp_buf[IR_NAME_LEN];

		s32 len_t	= sizeof(s32*);

		ret_exp->k		= IR_VARADDR;
		ret_exp->e.var.var_addr	= (s32*)malloc(len_t);

		ret_exp->e.var.var_len	= 0;
		
		ret_exp->e.var.var_type	= INT;
		ret_exp->e.var.pvar	= NULL;

		ret_exp->e.var.align_1	= NULL;
		ret_exp->e.var.align_2	= NULL;

		switch(ret_exp->e.var.var_type)
		{
			case INT:
				*(s32*)(ret_exp->e.var.var_addr) = num;	
				
				empty_buf(ins_temp_buf, IR_NAME_LEN);
				ins_temp_buf[0]	= '0';
				ins_temp_buf[1]	= 'x';
				h2s(num, &ins_temp_buf[2]);
			
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

	return ret_exp;
}

//===========================================================================
// var_exp_update
//===========================================================================
PUBLIC	struct ir_exp *	ir_const_exp_update(struct ir_exp *exp, s32 array_num)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_const_exp_update  -- \n");
#endif
//--------------------------

	exp->e.var.var_addr	= exp->e.var.pvar->var_addr + exp->e.var.var_len * array_num;	

	return exp;	
}


//===========================================================================
// fun_exp_build(struct s_var *v)
//===========================================================================
PUBLIC	struct ir_exp *	ir_fun_exp_build(s8 *func_name)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- fun_exp_build  -- \n");
#endif
//--------------------------

	struct symbol *sym	= symtbl_search(func_name);

	if(!sym)
	{
		printf("fun_exp_build()::func_name(%s) not define!!\n",func_name);
		exit(1);
	}

	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	if(ret_exp)
	{
		//kind
		ret_exp->k		= IR_CALL;
		
		if(sym->type_scs == EXTERN)
		{
			//label
			ret_exp->e.call.label_name	= sym->name;
		}
		else
		{
			//label
			ret_exp->e.call.label_name	= sym->label;
		}

		//ret_type
		ret_exp->e.call.ret_type	= sym->type_scs;

		//ret_len
		ret_exp->e.call.ret_len		= sym->len;

		//ret_addr
		ret_exp->e.call.ret_addr	= malloc(sizeof(s32*));
		
		ret_exp->e.call.align_1		= NULL;
		ret_exp->e.call.align_2		= NULL;		

		//pvlist
		ret_exp->e.call.ppv		= NULL;		
	}
	else
	{
		printf("fun_exp_build() malloc failed!!\n");
		exit(1);
	}

	return ret_exp;
}

//===========================================================================
// fun_exp_update(struct ir_exp *exp)
//===========================================================================
PUBLIC	struct ir_exp *	ir_fun_exp_update(struct ir_exp *exp, s8* func_name)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- fun_exp_update -- \n");
#endif
//--------------------------

	struct symbol *	sym	= symtbl_search(func_name);

	if(!sym)
	{
		printf("fun_exp_update()::func_name(%s) not define!!\n",func_name);
		exit(1);
	}

	struct ir_explist *p	= cur_explist;

	s8 flg = FALSE;
	for(; p; p=p->tail)
	{
		if(strcmp(p->exp->e.call.label_name, sym->label) == TRUE)
		{
			flg	= TRUE;
			break;
		}
	}

	if(!flg)
	{
		printf("fun_exp_update()::No such label(%s) in func_name(%s) !!\n", sym->label, func_name);
		exit(1);
	}	
	
	return exp;
}

//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_expsts_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_expsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= malloc(sizeof(struct ir_sts));

	if(!ret_sts)
	{
		printf("ir_expsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= IR_EXP;
	ret_sts->s.exp_sts.explist	= explist;

	return ret_sts;
}

//===========================================================================
// assign_exp_build
//===========================================================================
PUBLIC	struct ir_exp *	ir_assign_exp_build(s32 op, struct ir_exp *res, struct ir_exp *val)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- assign_exp_build  -- \n");
#endif
//--------------------------

	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	if(ret_exp)
	{
		ret_exp->k		= IR_ASSIGN;
		ret_exp->e.assign.op	= op;
		ret_exp->e.assign.res	= res;
		ret_exp->e.assign.val	= val;
	}
	else
	{
		printf("assign_exp_build() malloc failed!!\n");
		exit(1);
	}

	return ret_exp;
}

//===========================================================================
// cond_exp_build
//===========================================================================
PUBLIC	struct ir_exp *	ir_cond_exp_build(struct ir_exp *cond, struct ir_exp *op_1, struct ir_exp *op_2)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- cond_exp_build  -- \n");
#endif
//--------------------------

	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	if(ret_exp)
	{
		ret_exp->k		= IR_COND;
		ret_exp->e.cond.cond	= cond;
		ret_exp->e.cond.op_1	= op_1;
		ret_exp->e.cond.op_2	= op_2;
	}
	else
	{
		printf("cond_exp_build() malloc failed!!\n");
		exit(1);
	}

	return ret_exp;
}

//===========================================================================
// relate_exp_build
//===========================================================================
PUBLIC	struct ir_exp *	ir_relate_exp_build(s32 op, struct ir_exp *left, struct ir_exp *right)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- relate_exp_build  -- \n");
#endif
//--------------------------

	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	if(ret_exp)
	{
		ret_exp->k		= IR_RELATE;
		ret_exp->e.relate.left	= left;
		ret_exp->e.relate.right	= right;		
	}
	else
	{
		printf("relate_exp_build() malloc failed!!\n");
		exit(1);
	}

	return ret_exp;
}

//===========================================================================
// abop_exp_build
//===========================================================================
PUBLIC	struct ir_exp *	ir_abop_exp_build(s32 op, struct ir_exp *left, struct ir_exp *right)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- abop_exp_build  -- \n");
#endif
//--------------------------

	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	if(ret_exp)
	{
		ret_exp->k		= IR_ABOP;
		ret_exp->e.abop.left	= left;
		ret_exp->e.abop.right	= right;
	}
	else
	{
		printf("abop_exp_build() malloc failed!!\n");
		exit(1);
	}

	return ret_exp;
}

//===========================================================================
// postfix_exp_build
//===========================================================================
PUBLIC	struct ir_exp *	ir_postfix_exp_build(s32 op, struct ir_exp *left, struct ir_exp *right)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- postfix_exp_build  -- \n");
#endif
//--------------------------

	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	if(ret_exp)
	{
		ret_exp->k		= IR_POSTFIX;
		ret_exp->e.postfix.left	= left;
		ret_exp->e.postfix.right= right;
		ret_exp->e.postfix.op	= op;
	}
	else
	{
		printf("postfix_exp_build() malloc failed!!\n");
		exit(1);
	}

	return ret_exp;
}

//===========================================================================
// postfix_exp_update
//===========================================================================
PUBLIC	struct ir_exp *	ir_postfix_exp_update(struct ir_exp *postfix_exp, struct ir_exp *val)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- postfix_exp_update  -- \n");
#endif
//--------------------------

	if(postfix_exp)
	{
		postfix_exp->e.postfix.right	= val;
	}

	return postfix_exp;
}

//===========================================================================
// unary_exp_build
//===========================================================================
PUBLIC	struct ir_exp *	ir_unary_exp_build(s32 op, struct ir_exp *left)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- unary_exp_build  -- \n");
#endif
//--------------------------

	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	if(ret_exp)
	{
		ret_exp->k		= IR_UNARY;
		ret_exp->e.unary.left	= left;
		ret_exp->e.unary.op	= op;	
		ret_exp->e.unary.right	= NULL;	
	}
	else
	{
		printf("unary_exp_build() malloc failed!!\n");
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
		ret_exp->k			= IR_LABEL;
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

	ret_sts->k	= IR_LABELS;
	ret_sts->s.label_sts.explist	= explist;

	return ret_sts;
}


//===========================================================================
// ir_add2stslist
//===========================================================================
PUBLIC	struct ir_sts *	ir_jumpsts_return_build(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_jumpsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= malloc(sizeof(struct ir_sts));

	if(!ret_sts)
	{
		printf("ir_expsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= IR_JUMP_RETURN;
	ret_sts->s.jump_sts.explist	= explist;

	return ret_sts;
}


//===========================================================================
// ir_label_exp_build
//===========================================================================
PUBLIC	struct ir_exp *	ir_null_exp_build(u32 val1, u32 val2, u32 val3)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_null_exp_build  -- \n");
#endif
//--------------------------

	struct ir_exp *ret_exp	= malloc(sizeof(struct ir_exp));

	if(ret_exp)
	{
		ret_exp->k		= IR_NULL;
		ret_exp->e.null.align_1	= val1;
		ret_exp->e.null.align_2	= val2;	
		ret_exp->e.null.align_3	= val3;	
	}
	else
	{
		printf("ir_null_exp_build() malloc failed!!\n");
		exit(1);
	}

	return ret_exp;
}

//===========================================================================
// ir_selectsts_build
//===========================================================================
PUBLIC	struct ir_sts *	ir_selectsts_build(struct ir_explist *explist, struct ir_sts *then_sts, struct ir_sts *else_sts)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_selectsts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= malloc(sizeof(struct ir_sts));

	if(!ret_sts)
	{
		printf("ir_selectsts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= IR_SELECT;
	ret_sts->s.select_sts.explist	= explist;
	ret_sts->s.select_sts.then_sts	= then_sts;
	ret_sts->s.select_sts.else_sts	= else_sts;

	return ret_sts;
}


//===========================================================================
// ir_selectsts_build
//===========================================================================
PUBLIC	s8	ir_selectsts_update_1(struct ir_sts *sts, struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_selectsts_update_1  -- \n");
#endif
//--------------------------

	sts->s.select_sts.explist	= explist;
	
}

//===========================================================================
// ir_selectsts_build
//===========================================================================
PUBLIC	s8	ir_selectsts_update_2(struct ir_sts *sts, struct ir_sts *then_sts)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_selectsts_update_2  -- \n");
#endif
//--------------------------

	sts->s.select_sts.then_sts	= then_sts;
	
}

//===========================================================================
// ir_selectsts_build
//===========================================================================
PUBLIC	s8	ir_selectsts_update_3(struct ir_sts *sts, struct ir_sts *else_sts)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_selectsts_update_3  -- \n");
#endif
//--------------------------

	sts->s.select_sts.else_sts	= else_sts;	
}

//===========================================================================
// ir_iteration_for_sts_build
//===========================================================================
PUBLIC	struct ir_sts *	ir_iteration_for_sts_build(struct ir_sts *init_sts, struct ir_sts *cond_sts, struct ir_explist *next_explist, struct ir_sts *sts)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_iteration_for_sts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= malloc(sizeof(struct ir_sts));

	if(!ret_sts)
	{
		printf("ir_iteration_for_sts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= IR_ITERATION_FOR;

	ret_sts->s.for_sts.init_sts	= init_sts;
	ret_sts->s.for_sts.cond_sts	= cond_sts;
	ret_sts->s.for_sts.next_explist	= next_explist;
	ret_sts->s.for_sts.sts		= sts;

	return ret_sts;
}

//===========================================================================
// ir_iteration_for_sts_update_1
//===========================================================================
PUBLIC	s8	ir_iteration_for_sts_update_1(struct ir_sts *sts, struct ir_sts *init_sts)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_iteration_for_sts_update_1  -- \n");
#endif
//--------------------------

	sts->s.for_sts.init_sts	= init_sts;	
}

//===========================================================================
// ir_iteration_for_sts_update_2
//===========================================================================
PUBLIC	s8	ir_iteration_for_sts_update_2(struct ir_sts *sts, struct ir_sts *cond_sts)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_iteration_for_sts_update_2  -- \n");
#endif
//--------------------------

	sts->s.for_sts.cond_sts	= cond_sts;	
}

//===========================================================================
// ir_iteration_for_sts_update_3
//===========================================================================
PUBLIC	s8	ir_iteration_for_sts_update_3(struct ir_sts *sts, struct ir_explist *next_explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_iteration_for_sts_update_3  -- \n\n");
#endif
//--------------------------

	sts->s.for_sts.next_explist	= next_explist;	
}

//===========================================================================
// ir_iteration_for_sts_update_4
//===========================================================================
PUBLIC	s8	ir_iteration_for_sts_update_4(struct ir_sts *sts, struct ir_sts *sts_1)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_iteration_for_sts_update_4  -- \n");
#endif
//--------------------------

	sts->s.for_sts.sts	= sts_1;	
}


//===========================================================================
// ir_iteration_while_sts_build
//===========================================================================
PUBLIC	struct ir_sts *	ir_iteration_while_sts_build(struct ir_explist *cond_explist, struct ir_sts *sts)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_iteration_while_sts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= malloc(sizeof(struct ir_sts));

	if(!ret_sts)
	{
		printf("ir_iteration_while_sts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= IR_ITERATION_WHILE;

	ret_sts->s.while_sts.cond_explist	= cond_explist;
	ret_sts->s.while_sts.sts		= sts;

	return ret_sts;
}

//===========================================================================
// ir_iteration_while_sts_update_1
//===========================================================================
PUBLIC	s8	ir_iteration_while_sts_update_1(struct ir_sts *sts, struct ir_explist *cond_explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_iteration_while_sts_update_1  -- \n\n");
#endif
//--------------------------

	sts->s.while_sts.cond_explist	= cond_explist;	
}

//===========================================================================
// ir_iteration_while_sts_update_2
//===========================================================================
PUBLIC	s8	ir_iteration_while_sts_update_2(struct ir_sts *sts, struct ir_sts *sts_1)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_iteration_while_sts_update_2  -- \n");
#endif
//--------------------------

	sts->s.while_sts.sts	= sts_1;	
}

//===========================================================================
// ir_iteration_dowhile_sts_build
//===========================================================================
PUBLIC	struct ir_sts *	ir_iteration_dowhile_sts_build(struct ir_explist *cond_explist, struct ir_sts *sts)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_iteration_dowhile_sts_build  -- \n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= malloc(sizeof(struct ir_sts));

	if(!ret_sts)
	{
		printf("ir_iteration_dowhile_sts_build::ir_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= IR_ITERATION_DOWHILE;

	ret_sts->s.dowhile_sts.cond_explist	= cond_explist;
	ret_sts->s.dowhile_sts.sts		= sts;

	return ret_sts;
}

//===========================================================================
// ir_iteration_dowhile_sts_update_1
//===========================================================================
PUBLIC	s8	ir_iteration_dowhile_sts_update_1(struct ir_sts *sts, struct ir_explist *cond_explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_iteration_dowhile_sts_update_1  -- \n\n");
#endif
//--------------------------

	sts->s.dowhile_sts.cond_explist	= cond_explist;	
}

//===========================================================================
// ir_iteration_dowhile_sts_update_2
//===========================================================================
PUBLIC	s8	ir_iteration_dowhile_sts_update_2(struct ir_sts *sts, struct ir_sts *sts_1)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("	-- ir_iteration_dowhile_sts_update_2  -- \n");
#endif
//--------------------------

	sts->s.dowhile_sts.sts	= sts_1;	
}
