//===========================================================================
// parse_func.c
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
#include	"dnasm_prototype.h"
#include	"dnasm_main.h"
#include	"dnasm_lex_char.h"
#include	"dnasm_lex_word.h"
#include	"dnasm_parse.h"
#include	"dnasm_seman.h"
#include	"dnasm_label.h"
#include	"dnasm_ir.h"
#include	"dnasm_frame.h"

PRIVATE	s8	production_tab_info[PARSE_PRODUCTIONS][IDEN_LEN]	= {
	"primary_expression","postfix_expression","postfix_expression_1","multiplicative_expression","multiplicative_expression_1",
	"additive_expression","additive_expression_1","expression","declaration_list","declaration_list_1",
	"declaration","declaration_1", "storage_class_specifier", "type_specifier","declarator",
	"statement_1","statement_2","direct_declarator","statement","statement_list",
	"statement_list_1","mov_sts","add_sts","sub_sts","mul_sts",
	"div_sts","call_sts","ret_sts","jmp_sts","ja_sts",
	"jb_sts","je_sts","jae_sts","jbe_sts","jne_sts",
	"push_sts","pop_sts","cmp_sts",	"translate_unit","translate_unit_1",
	"external_declaration"
	};


PRIVATE	struct ir_exp *	primary_expression(struct ir_exp *exp);
PRIVATE	struct ir_exp *	xor_expression();
PRIVATE	struct ir_exp *	xor_expression_1(struct ir_exp *exp);
PRIVATE	struct ir_exp *	multiplicative_expression();
PRIVATE	struct ir_exp *	multiplicative_expression_1(struct ir_exp *exp);
PRIVATE	struct ir_exp *	additive_expression();
PRIVATE	struct ir_exp *	additive_expression_1(struct ir_exp *exp);
PRIVATE	struct ir_exp*	expression();
PRIVATE	void	type_specifier();
PRIVATE	void	storage_class_specifier();
PRIVATE	void	declaration();
PRIVATE	void	declaration_1();
PRIVATE	void	declarator();
PRIVATE	struct ir_sts *	statement();
PRIVATE	struct ir_sts *	statement_1();
PRIVATE	struct ir_sts *	statement_2();
PRIVATE	struct ir_sts *	mov_sts();
PRIVATE	struct ir_sts *	add_sts();
PRIVATE	struct ir_sts *	sub_sts();
PRIVATE	struct ir_sts *	mul_sts();
PRIVATE	struct ir_sts *	div_sts();
PRIVATE	struct ir_sts *	call_sts();
PRIVATE	struct ir_sts *	ret_sts();
PRIVATE	struct ir_sts *	jmp_sts();
PRIVATE	struct ir_sts *	ja_sts();
PRIVATE	struct ir_sts *	jb_sts();
PRIVATE	struct ir_sts *	je_sts();
PRIVATE	struct ir_sts *	jae_sts();
PRIVATE	struct ir_sts *	jbe_sts();
PRIVATE	struct ir_sts *	jne_sts();
PRIVATE	struct ir_sts *	push_sts();
PRIVATE	struct ir_sts *	pop_sts();
PRIVATE	struct ir_sts *	cmp_sts();
PRIVATE	struct ir_sts *	xor_sts();
PRIVATE	struct ir_sts *	int_sts();
PRIVATE	void	declaration_list();
PRIVATE	void	declaration_list_1();
PRIVATE	void	statement_list();
PRIVATE	void	statement_list_1();
PRIVATE	void	translate_unit();
PRIVATE	void	translate_unit_1();
PRIVATE	void	external_declaration();


#define	PARSE_DEBUG	
//===========================================================================
//parse_entry()
//===========================================================================
PUBLIC	void	parse_entry()
{
	translate_unit();
}


//===========================================================================
//primary_expression()
//===========================================================================
PRIVATE	struct ir_exp *	primary_expression(struct ir_exp *exp) 
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- primary_expression(1)  -- token=%d\n\n", token);
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp * ret_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(!parse_production_tab[PRODUCTION_1][FIRST_SET][token])
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_1][IDEN_LEN],token);
		exit(1);
	}
	else if(token == OP_L_PARENTHESE)
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_exp	= expression();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		get_tok();

		if(token != OP_R_PARENTHESE)
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_1][IDEN_LEN],token);
			exit(1);
		}		
	}
	else if((token == IDENTIFIER) || (token == EAX) || (token == EBX) || (token == ECX) || (token == EDX)
				      || (token == EBP) || (token == ESP) || (token == ESI) || (token == EDI) 
				      || (token == BX))
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		cur_var	= symtbl_search(p_cur_token->val_s);

		if(cur_var)
		{				
			ret_exp	= ir_var_exp_build(cur_var);

			if(token == IDENTIFIER)
			{
				ret_exp->s	= IR_MEM;
			}
			else
			{
				ret_exp->s	= IR_REG;
			}
			ret_exp->len	= 4;
		}
		else if(flg_cmpcond_g)
		{
			ret_exp	= malloc(sizeof(struct ir_exp));

			if(ret_exp)
			{
				ret_exp->k		= IR_EXP_VARADDR;
				ret_exp->e.var.pvar	= NULL;

				ret_exp->e.var.var_len	= 4;
				ret_exp->e.var.var_type	= DWORD;

				strcopy(ret_exp->e.var.name, p_cur_token->val_s);
				ret_exp->e.var.name[strlen(ret_exp->e.var.name)]	= NULL;	

				strcopy(ret_exp->e.var.label, ret_exp->e.var.name);
				ret_exp->e.var.label[strlen(ret_exp->e.var.label)]	= NULL;

				ret_exp->e.var.var_id	= 0;
		
				ret_exp->e.var.align_1	= NULL;
				ret_exp->e.var.align_2	= NULL;		

			}
			ret_exp->s	= IR_MEM;			
		}	
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	}	
	else if(token == CONST_STRING)
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		strcopy(&(sym_t.val_s), p_cur_token->val_s);
		sym_t.name[strlen(p_cur_token->val_s)]	= NULL;	
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		sym_t.val_i	= s2h(p_cur_token->val_s+2);	//skip 0x		
		sym_t.val_i_1	= sym_t.val_i;

		ret_exp		= ir_const_exp_build(sym_t.val_i);
		
		if(!flg_abop_g)
		{
			ret_exp->s	= IR_IMM;
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}	

	return ret_exp;	
}

//===========================================================================
// multiplicative_expression()
//===========================================================================
PRIVATE	struct ir_exp *	multiplicative_expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- multiplicative_expression  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp *ret_exp	= NULL;

	ret_exp	= primary_expression(ret_exp);
	ret_exp	= multiplicative_expression_1(ret_exp);

	return ret_exp;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

}

//===========================================================================
// multiplicative_expression_1()
//===========================================================================
PRIVATE	struct ir_exp *	multiplicative_expression_1(struct ir_exp *exp)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- multiplicative_expression_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_35][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_35][FOLLOW_SET][token])
		{
			uget_tok(1);
			return exp;
		}
		else
		{
			//
		}
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ir_exp *ret_exp 	= ir_abop_exp_build(0, NULL, NULL);

		ret_exp->e.abop.op	= token;
		ret_exp->e.abop.left	= exp;
		ret_exp->e.abop.right	= primary_expression(exp);

		ret_exp	= multiplicative_expression_1(ret_exp);

		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	}

	return NULL;
}


//===========================================================================
// additive_expression()
//===========================================================================
PRIVATE	struct ir_exp *	additive_expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- additive_expression  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp *ret_exp	= NULL;

	ret_exp	= multiplicative_expression();	
	ret_exp	= additive_expression_1(ret_exp);

	return ret_exp;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

//===========================================================================
// additive_expression()
//===========================================================================
PRIVATE	struct ir_exp *	additive_expression_1(struct ir_exp *exp)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- additive_expression_1  -- \n\n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_36][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_36][FOLLOW_SET][token])
		{
			uget_tok(1);
			return exp;
		}
		else
		{
			//
		}
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		flg_abop_g	= TRUE;

		struct ir_exp *ret_exp 	= ir_abop_exp_build(0, NULL, NULL);

		ret_exp->e.abop.op	= token;
		ret_exp->e.abop.left	= exp;
		ret_exp->e.abop.right	= multiplicative_expression();

		ret_exp	= additive_expression_1(ret_exp);

		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~				
	}

	return NULL;
}



//===========================================================================
// assignment_operator()
//===========================================================================
PRIVATE	struct ir_exp*	expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- expression(s)  -- \n\n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp	*ret_exp_1 	= NULL;
	struct ir_exp	*ret_exp_2	= NULL;	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(!parse_production_tab[PRODUCTION_5][FIRST_SET][token])
	{
		printf("error:%s,token:%d\n\n",production_tab_info[PRODUCTION_5][IDEN_LEN],token);
		exit(1);
	}
	else
	{
		if((token == DWORD)||(token == WORD)||(token == BYTE))
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			postfix_var_len	= check_type_l(token);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			get_tok();
			if(token != OP_L_BRACKET)
			{
				printf("error:%s,token:%d\n\n",production_tab_info[PRODUCTION_5][IDEN_LEN],token);
				exit(1);
			}
			else
			{
				ret_exp_1	= additive_expression(ret_exp_1);

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				ret_exp_1->len	= postfix_var_len;

				postfix_var_len	= NULL;

				flg_abop_g	= FALSE;
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

				get_tok();
				if(token != OP_R_BRACKET)
				{
					printf("error:%s,token:%d\n\n",production_tab_info[PRODUCTION_5][IDEN_LEN],token);
					exit(1);
				}				
			}
		}
		else
		{
			uget_tok(1);
			ret_exp_1 	= additive_expression(ret_exp_1);			
		}
	}
	

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_explist * explist_t = explist_build(ret_exp_1);
	ir_add2explist(explist_t, cur_explist);	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	return ret_exp_2;	
}


//===========================================================================
// storage_class_specifier()
//===========================================================================
PRIVATE	void	storage_class_specifier()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- storage_class_specifier  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_9][FIRST_SET][token])
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_9][IDEN_LEN],token);
		exit(1);
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		if(token == EXTERN)
		{
			flg_extern_g	= TRUE;
		}

		if(token == GLOBAL)
		{
			flg_global_g	= TRUE;
		}
		
		sym_t.type_scs	= token;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}	
}

//===========================================================================
// type_specifier()
//===========================================================================
PRIVATE	void	type_specifier()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- type_specifier  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_10][FIRST_SET][token])
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_10][IDEN_LEN],token);
		exit(1);
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		sym_t.type_ts	= token;

		switch(token)
		{
			case DB:
				sym_t.len	= 1;
				break;
			case DW:
				sym_t.len	= 2;
				break;	
			case DD:
				sym_t.len	= 4;
				break;
			case DQ:
				sym_t.len	= 8;
				break;
			case DT:
				sym_t.len	= 16;
				break;
			case DY:
				sym_t.len	= 32;
				break;
			case RESB:
				get_tok();
				sym_t.len	= 1 * (s2h(p_cur_token->val_s+2));
				uget_tok(1);
				break;
			case RESW:
				get_tok();
				sym_t.len	= 2 * (s2h(p_cur_token->val_s+2));
				uget_tok(1);
				break;
			case RESQ:
				get_tok();
				sym_t.len	= 4 * (s2h(p_cur_token->val_s+2));
				uget_tok(1);
				break;
			case RESY:
				get_tok();
				sym_t.len	= 8 * (s2h(p_cur_token->val_s+2));
				uget_tok(1);
				break;
			default:
				break;
		}		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
}

//===========================================================================
// declaration()
//===========================================================================
PRIVATE	void	declaration()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- declaration(1) -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_7][FIRST_SET][token])
	{
		if(parse_production_tab[PRODUCTION_9][FIRST_SET][token])
		{
			uget_tok(1);
			storage_class_specifier();

			get_tok();

			if(token == IDENTIFIER)
			{
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				if(flg_extern_g)
				{
					strcopy(&(sym_t.name), p_cur_token->val_s);
					sym_t.name[strlen(p_cur_token->val_s)]	= NULL;

					sym_t.flag	= FLAG_EXTERN;
					sym_t.attr	= ATTR_FUN;
		
					symtbl_add_s(&sym_t);
					symbol_empty(&sym_t);

					flg_extern_g	= FALSE;
				}
				
				if(flg_global_g)
				{
					strcopy(&(sym_t.name), p_cur_token->val_s);
					sym_t.name[strlen(p_cur_token->val_s)]	= NULL;

					sym_t.flag	= FLAG_GLOBAL;
					sym_t.attr	= ATTR_FUN;
		
					symtbl_add_s(&sym_t);
					symbol_empty(&sym_t);

					flg_global_g	= FALSE;
				}
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			}
			else
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_7][IDEN_LEN],token);
				exit(1);
			}
		}
		else if(parse_production_tab[PRODUCTION_8][FIRST_SET][token])
		{
			uget_tok(1);
			declaration_1();
		}
		else if(parse_production_tab[PRODUCTION_8][FOLLOW_SET][token])
		{
			uget_tok(1);
			type_specifier();
			declarator();

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
			sym_t.flag	= FLAG_DATA;

			symtbl_add_s(&sym_t);
			symbol_empty(&sym_t);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}		
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_7][IDEN_LEN],token);
		exit(1);
	}	

}


//===========================================================================
// declaration_1()
//===========================================================================
PRIVATE	void	declaration_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- declaration_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_8][FIRST_SET][token])
	{		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		strcopy(&(sym_t.name), p_cur_token->val_s);
		sym_t.name[strlen(p_cur_token->val_s)]	= NULL;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_8][IDEN_LEN],token);
		exit(1);
	}
}



//===========================================================================
// declarator()
//===========================================================================
PRIVATE	void	declarator()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- declarator  -- \n\n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp*	ret_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_11][FIRST_SET][token])
	{
		if(token == CONST_S_QUOTE)	// '
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ret_exp		= primary_expression(NULL);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			
			get_tok();
			if(token != CONST_S_QUOTE)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_11][IDEN_LEN],token);
				exit(1);
			}
		}
		else if(parse_production_tab[PRODUCTION_5][FIRST_SET][token])
		{
			uget_tok(1);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ret_exp		= primary_expression(NULL);

			sym_t.len	= check_type_l(sym_t.type_ts);
			sym_t.len	*= sym_t.val_i;
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_39][IDEN_LEN],token);
		exit(1);
	}
}


//===========================================================================
// statement()
//===========================================================================
PRIVATE	struct ir_sts *	statement()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- statement  -- \n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= NULL;

	get_tok();

	if(parse_production_tab[PRODUCTION_39][FIRST_SET][token])
	{
		uget_tok(1);
		ret_sts	= statement_1();
	}
	else if(parse_production_tab[PRODUCTION_39][FOLLOW_SET][token])
	{
		uget_tok(1);
		ret_sts	= statement_2();
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_12][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;	
}

//===========================================================================
// statement()
//===========================================================================
PRIVATE	struct ir_sts *	statement_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- statement_1  -- token=%d\n\n", token);
#endif
//--------------------------

	struct ir_sts * ret_sts	= NULL;

	get_tok();

	if(parse_production_tab[PRODUCTION_39][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		strcopy(&(sym_t.name), p_cur_token->val_s);
		sym_t.name[strlen(p_cur_token->val_s)]	= NULL;

		sym_t.attr	= ATTR_FUN;

		struct symbol *s = symtbl_search(p_cur_token->val_s);
		if(!s)
		{
			symtbl_add_s(&sym_t);
			symbol_empty(&sym_t);
		}
		else
		{
			s8 flag = s->flag;

			if((flag == FLAG_GLOBAL) || (flag == FLAG_EXTERN))
			{
				symtbl_del(s->name);

				sym_t.flag	= flag;
				symtbl_add_s(&sym_t);
				symbol_empty(&sym_t);				
			}
			else
			{
				printf("error::symbol:%s redefined(flag=%d) !!!\n\n", p_cur_token->val_s, flag);
				exit(0);
			}
		}		

		struct ir_exp *	irexp_t		= ir_label_exp_build(p_cur_token->val_s, 0);
		struct ir_explist *irexplist_t 	= explist_build(irexp_t);
		struct ir_sts *sts_t 		= ir_labelsts_build(irexplist_t);
		struct ir_sts_list *stslist_t 	= stslist_build(sts_t);
		ir_add2stslist(stslist_t, cur_stslist);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		get_tok();

		if(token != OP_COLON)
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_39][IDEN_LEN],token);
			exit(1);
		}
	}

	return ret_sts;
}


//===========================================================================
// statement()
//===========================================================================
PRIVATE	struct ir_sts *	statement_2()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- statement_2  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts_1	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_15][FIRST_SET][token])
	{
		uget_tok(1);

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= mov_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_16][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= add_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_17][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= sub_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_18][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= mul_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_19][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= div_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_20][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= call_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_21][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= ret_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_22][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= jmp_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_23][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= ja_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_24][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= jb_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_25][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= je_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_26][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= jae_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_27][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= jbe_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_28][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= jne_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_29][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= push_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_30][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= pop_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_31][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= cmp_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_13][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= xor_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_45][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts_1	= int_sts();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_38][IDEN_LEN],token);
		exit(1);
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts_list *stslist 	= stslist_build(ret_sts_1);
	ir_add2stslist(stslist, cur_stslist);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	

	return ret_sts_1;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	mov_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- mov_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *src_exp	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_15][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		cur_explist	= explist_build(NULL);
		src_exp		= expression();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		get_tok();

//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- mov_sts(1)  -- \n\n");
#endif
//--------------------------

		if(token == OP_COMMA)
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			dst_exp	= expression();
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}
		else
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_15][IDEN_LEN],token);
			exit(1);
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts = ir_movsts_build(cur_explist);				
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_15][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	add_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- add_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *src_exp	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_16][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		cur_explist	= explist_build(NULL);
		src_exp		= expression();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		get_tok();
		if(token == OP_COMMA)
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			dst_exp	= expression();
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}
		else
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_16][IDEN_LEN],token);
			exit(1);
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts = ir_addsts_build(cur_explist);			
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_16][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	sub_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- sub_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *src_exp	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_17][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		cur_explist	= explist_build(NULL);
		src_exp		= expression();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		get_tok();
		if(token == OP_COMMA)
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			dst_exp	= expression();
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}
		else
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_17][IDEN_LEN],token);
			exit(1);
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts = ir_substs_build(cur_explist);			
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_17][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}	

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	mul_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- mul_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_18][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		cur_explist	= explist_build(NULL);
		dst_exp		= expression();
		
		ret_sts = ir_mulsts_build(cur_explist);			
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_18][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	div_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- div_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_19][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		cur_explist	= explist_build(NULL);
		dst_exp		= expression();
		
		ret_sts = ir_divsts_build(cur_explist);			
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_19][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	call_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- call_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_20][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		flg_cmpcond_g	= TRUE;

		cur_explist	= explist_build(NULL);
		dst_exp		= expression();
		
		ret_sts = ir_callsts_build(cur_explist);		

		flg_cmpcond_g	= FALSE;	
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_20][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	ret_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- ret_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_21][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		cur_explist	= explist_build(NULL);
				
		ret_sts = ir_retsts_build();		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_21][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	jmp_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- jmp_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_22][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		flg_cmpcond_g	= TRUE;

		cur_explist	= explist_build(NULL);
		dst_exp		= expression();
		
		ret_sts = ir_jmpsts_build(cur_explist);	

		flg_cmpcond_g	= FALSE;		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_22][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	ja_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- ja_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_23][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		flg_cmpcond_g	= TRUE;

		cur_explist	= explist_build(NULL);
		dst_exp		= expression();
		
		ret_sts = ir_jasts_build(cur_explist);		

		flg_cmpcond_g	= FALSE;	
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_23][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	jb_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- jb_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_24][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		flg_cmpcond_g	= TRUE;

		cur_explist	= explist_build(NULL);
		dst_exp		= expression();
		
		ret_sts = ir_jbsts_build(cur_explist);	

		flg_cmpcond_g	= FALSE;		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_24][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	je_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- je_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_25][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		flg_cmpcond_g	= TRUE;

		cur_explist	= explist_build(NULL);
		dst_exp		= expression();
		
		ret_sts = ir_jests_build(cur_explist);		

		flg_cmpcond_g	= FALSE;	
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_25][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	jae_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- jae_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_26][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		flg_cmpcond_g	= TRUE;

		cur_explist	= explist_build(NULL);
		dst_exp		= expression();
		
		ret_sts = ir_jaests_build(cur_explist);		

		flg_cmpcond_g	= FALSE;	
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_26][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	jbe_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- jbe_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_27][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		flg_cmpcond_g	= TRUE;

		cur_explist	= explist_build(NULL);
		dst_exp		= expression();
		
		ret_sts = ir_jbests_build(cur_explist);	

		flg_cmpcond_g	= FALSE;		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_27][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	jne_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- jne_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_28][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		flg_cmpcond_g	= TRUE;

		cur_explist	= explist_build(NULL);
		dst_exp		= expression();
		
		ret_sts = ir_jnests_build(cur_explist);		

		flg_cmpcond_g	= FALSE;	
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_28][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	push_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- push_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_29][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		cur_explist	= explist_build(NULL);
		dst_exp		= expression();
		
		ret_sts = ir_pushsts_build(cur_explist);			
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_29][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	pop_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- pop_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_30][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		cur_explist	= explist_build(NULL);
		dst_exp		= expression();
		
		ret_sts = ir_popsts_build(cur_explist);			
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_30][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	cmp_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- cmp_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *src_exp	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_31][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		cur_explist	= explist_build(NULL);
		src_exp		= expression();

		get_tok();
		if(token == OP_COMMA)
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			dst_exp	= expression();
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}
		else
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_31][IDEN_LEN],token);
			exit(1);
		}

		ret_sts = ir_cmpsts_build(cur_explist);			
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_31][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// mov_sts()
//===========================================================================
PRIVATE	struct ir_sts *	xor_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- xor_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *src_exp	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_13][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		cur_explist	= explist_build(NULL);
		src_exp		= expression();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		get_tok();
		if(token == OP_COMMA)
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			dst_exp	= expression();
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}
		else
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_13][IDEN_LEN],token);
			exit(1);
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts = ir_xorsts_build(cur_explist);			
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_13][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}


//===========================================================================
// int_sts()
//===========================================================================
PRIVATE	struct ir_sts *	int_sts()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- int_sts  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	struct ir_exp *dst_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_45][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		cur_explist	= explist_build(NULL);
		dst_exp		= expression();
		
		ret_sts = ir_intsts_build(cur_explist);			
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_45][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// declaration_list()
//===========================================================================
PRIVATE	void	declaration_list()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- declaration_list(1)  -- \n");
#endif
//--------------------------


	declaration();
	declaration_list_1();
}


//===========================================================================
// declaration_list_1()
//===========================================================================
PRIVATE	void	declaration_list_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- declaration_list_1  -- \n");
#endif
//--------------------------


	get_tok();

	if(parse_production_tab[PRODUCTION_37][FIRST_SET][token]) 
	{
		uget_tok(1);
		declaration();
		declaration_list_1();
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_37][FOLLOW_SET][token])
		{
			uget_tok(1);
			return;
		}
		else
		{
			//
		}
	}
}

//===========================================================================
// statement_list()
//===========================================================================
PRIVATE	void	statement_list()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- statement_list  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	cur_stslist	= stslist_build(NULL);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	statement();
	statement_list_1();
}

//===========================================================================
// statement_list_1()
//===========================================================================
PRIVATE	void	statement_list_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- statement_list_1  -- \n\n");
#endif
//--------------------------

	struct ir_sts * ret_sts	= NULL;
	
	get_tok();

	if(parse_production_tab[PRODUCTION_40][FIRST_SET][token]) 
	{
		uget_tok(1);
		statement();
		statement_list_1();
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ir_file	*f = file_build(cur_stslist);
		ir_add2file(f, cur_file);

		cur_stslist	= NULL;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		if(!parse_production_tab[PRODUCTION_40][FOLLOW_SET][token])
		{
			uget_tok(1);
			return;
		}
		else
		{
			//
		}
	}
}



//===========================================================================
// translate_unit()
//===========================================================================
PRIVATE	void	translate_unit()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- translate_unit -- \n");
#endif
//--------------------------

	external_declaration();
	translate_unit_1();
}

//===========================================================================
// translate_unit_1()
//===========================================================================
PRIVATE	void	translate_unit_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- translate_unit_1 -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_41][FIRST_SET][token]) 
	{
		uget_tok(1);
		external_declaration();
		translate_unit_1();		
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_41][FOLLOW_SET][token])
		{
			uget_tok(1);
			return;
		}
		else
		{
			//
		}
	}
}

//===========================================================================
// external_declaration()
//===========================================================================
PRIVATE	void	external_declaration()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- external_declaration -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_33][FIRST_SET][token]) 
	{
		if(token == IDENTIFIER)
		{
			get_tok();
			if(token == OP_COLON)
			{
				uget_tok(2);
				statement_list();
			}
			else
			{
				uget_tok(2);
				declaration_list();
			}
		}
		else if(parse_production_tab[PRODUCTION_42][FIRST_SET][token])	// '['
		{
			get_tok();

			if(!parse_production_tab[PRODUCTION_34][FIRST_SET][token])
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_33][IDEN_LEN],token);
				exit(1);
			}
			else
			{				
				primary_expression(NULL);

				get_tok();
				if(token != OP_R_BRACKET)
				{
					printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_33][IDEN_LEN],token);
					exit(1);
				}
			}
		}
		else if(parse_production_tab[PRODUCTION_14][FIRST_SET][token])
		{
			uget_tok(1);
			statement_list();
		}
		else if(parse_production_tab[PRODUCTION_6][FIRST_SET][token])
		{
			uget_tok(1);
			declaration_list();
		}		
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_33][FOLLOW_SET][token])
		{
			uget_tok(1);
			return;
		}
		else
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_33][IDEN_LEN],token);
			exit(1);
		}
	}	
}
