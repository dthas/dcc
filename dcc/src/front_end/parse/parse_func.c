//===========================================================================
// parse_func.c
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
#include	"dcc_prototype.h"
#include	"dcc_main.h"
#include	"dcc_lex_char.h"
#include	"dcc_lex_word.h"
#include	"dcc_parse.h"
#include	"dcc_seman.h"
#include	"dcc_label.h"
#include	"dcc_ir.h"
#include	"dcc_frame.h"

PRIVATE	s8	production_tab_info[PARSE_PRODUCTIONS][IDEN_LEN]	= {
	"primary_expression", "postfix_expression", "argument_expression_list", "unary_expression", "unary_operator", 
	"cast_expression", "multiplicative_expression", "additive_expression", "shift_expression", "relational_expression", 
	"equality_expression", "and_expression", "exclusive_or_expression", "inclusive_or_expression", "logical_and_expression", 
	"logical_or_expression", "conditional_expression", "assignment_expression", "assignment_operator", "expression", 
	"constant_expression", "declaration", "declaration_specifiers", "init_declarator_list", "init_declarator", 
	"storage_class_specifier", "type_specifier", "struct_or_union_specifier", "struct_or_union", "struct_declaration_list", 
	"struct_declaration", "specifier_qualifier_list", "struct_declarator_list", "struct_declarator", "enum_specifier", 
	"enumerator_list", "enumerator", "type_qualifier", "declarator", "direct_declarator", 
	"pointer", "type_qualifier_list", "parameter_type_list", "parameter_list", "parameter_declaration", 
	"identifier_list", "type_name", "abstract_declarator", "direct_abstract_declarator", "initializer", 
	"initializer_list", "statement", "labeled_statement", "compound_statement", "declaration_list", 
	"statement_list", "expression_statement", "selection_statement", "iteration_statement", "jump_statement", 
	"translation_unit", "external_declaration", "function_definition",
	"postfix_expression_1","argument_expression_list_1","multiplicative_expression_1","additive_expression_1","shift_expression_1",
	"relational_expression_1","equality_expression_1","and_expression_1","exclusive_or_expression_1","inclusive_or_expression_1",
	"logical_and_expression_1","logical_or_expression_1","conditional_expression_1","expression_1","declaration_1",
	"declaration_specifiers_1","declaration_specifiers_2","init_declarator_list_1","init_declarator_1","struct_or_union_specifier_1",
	"struct_or_union_specifier_2","struct_or_union_specifier_3","struct_declaration_list_1","specifier_qualifier_list_1","specifier_qualifier_list_2",
	"struct_declarator_list_1","struct_declarator_1","struct_declarator_2","enum_specifier_1","enum_specifier_2",
	"enumerator_list_1","enumerator_1","direct_declarator_1","direct_declarator_2","direct_declarator_3",
	"direct_declarator_4","pointer_1","pointer_2","type_qualifier_list_1","parameter_type_list_1",
	"parameter_list_1","parameter_declaration_1","identifier_list_1","type_name_1","abstract_declarator_1",
	"abstract_declarator_2","direct_abstract_declarator_1","direct_abstract_declarator_2","direct_abstract_declarator_3","direct_abstract_declarator_4",
	"initializer_1","initializer_2","initializer_list_1","compound_statement_1","compound_statement_2",
	"declaration_list_1","statement_list_1","selection_statement_1","selection_statement_2","iteration_statement_1",
	"jump_statement_1","translate_unit_1","function_definition_1","function_definition_2","function_definition_3",
	"function_definition_4"};


PRIVATE	struct ir_exp *	primary_expression(struct ir_exp *exp);
PRIVATE	struct ir_exp *	postfix_expression();
PRIVATE	struct ir_exp *	postfix_expression_1(struct ir_exp *exp);
PRIVATE	struct ir_exp *	argument_expression_list();
PRIVATE	struct ir_exp *	argument_expression_list_1(struct ir_exp *exp);
PRIVATE	struct ir_exp *	unary_expression();
PRIVATE	s32	unary_operator();
PRIVATE	struct ir_exp *	cast_expression();
PRIVATE	struct ir_exp *	multiplicative_expression();
PRIVATE	struct ir_exp *	multiplicative_expression_1(struct ir_exp *exp);
PRIVATE	struct ir_exp *	additive_expression();
PRIVATE	struct ir_exp *	additive_expression_1(struct ir_exp *exp);
PRIVATE	struct ir_exp *	shift_expression();
PRIVATE	struct ir_exp *	shift_expression_1(struct ir_exp *exp);
PRIVATE	struct ir_exp *	relational_expression();
PRIVATE	struct ir_exp *	relational_expression_1(struct ir_exp *exp);
PRIVATE	struct ir_exp *	equality_expression();
PRIVATE	struct ir_exp *	equality_expression_1(struct ir_exp *exp);
PRIVATE	struct ir_exp *	and_expression();
PRIVATE	struct ir_exp *	and_expression_1(struct ir_exp *exp);
PRIVATE	struct ir_exp *	exclusive_or_expression();
PRIVATE	struct ir_exp *	exclusive_or_expression_1(struct ir_exp *exp);
PRIVATE	struct ir_exp *	inclusive_or_expression();
PRIVATE	struct ir_exp *	inclusive_or_expression_1(struct ir_exp *exp);
PRIVATE	struct ir_exp *	logical_and_expression();
PRIVATE	struct ir_exp *	logical_and_expression_1(struct ir_exp *exp);
PRIVATE	struct ir_exp *	logical_or_expression();
PRIVATE	struct ir_exp *	logical_or_expression_1(struct ir_exp *exp);
PRIVATE	struct ir_exp *	conditional_expression();
PRIVATE	struct ir_exp *	conditional_expression_1(struct ir_exp *exp);
PRIVATE	struct ir_exp *	assignment_expression();
PRIVATE	s32	assignment_operator();
PRIVATE	struct ir_exp *	expression();
PRIVATE	struct ir_exp *	expression_1(struct ir_exp *exp);
PRIVATE	struct ir_exp *	constant_expression();
PRIVATE	void	declaration();
PRIVATE	void	declaration_1();
PRIVATE	void	declaration_specifiers();
PRIVATE	void	declaration_specifiers_1();
PRIVATE	void	declaration_specifiers_2();
PRIVATE	void	init_declarator_list();
PRIVATE	void	init_declarator_list_1();
PRIVATE	void	init_declarator();
PRIVATE	void	init_declarator_1();
PRIVATE	void	storage_class_specifier();
PRIVATE	void	type_specifier();
PRIVATE	void	struct_or_union_specifier();
PRIVATE	void	struct_or_union_specifier_1();
PRIVATE	void	struct_or_union_specifier_2();
PRIVATE	void	struct_or_union_specifier_3();
PRIVATE	void	struct_or_union();
PRIVATE	void	struct_declaration_list();
PRIVATE	void	struct_declaration_list_1();
PRIVATE	void	struct_declaration();
PRIVATE	void	specifier_qualifier_list();
PRIVATE	void	specifier_qualifier_list_1();
PRIVATE	void	specifier_qualifier_list_2();
PRIVATE	void	struct_declarator_list();
PRIVATE	void	struct_declarator_list_1();
PRIVATE	void	struct_declarator();
PRIVATE	void	struct_declarator_1();
PRIVATE	void	struct_declarator_2();
PRIVATE	void	enum_specifier();
PRIVATE	void	enum_specifier_1();
PRIVATE	void	enum_specifier_2();
PRIVATE	void	enumerator_list();
PRIVATE	void	enumerator_list_1();
PRIVATE	void	enumerator();
PRIVATE	void	enumerator_1();
PRIVATE	void	type_qualifier();
PRIVATE	void	declarator();
PRIVATE	void	direct_declarator();
PRIVATE	void	direct_declarator_1();
PRIVATE	void	pointer();
PRIVATE	void	pointer_1();
PRIVATE	void	pointer_2();
PRIVATE	void	type_qualifier_list();
PRIVATE	void	type_qualifier_list_1();
PRIVATE	void	parameter_type_list();
PRIVATE	void	parameter_type_list_1();
PRIVATE	void	parameter_list();
PRIVATE	void	parameter_list_1();
PRIVATE	void	parameter_declaration();
PRIVATE	void	parameter_declaration_1();
PRIVATE	void	identifier_list();
PRIVATE	void	identifier_list_1();
PRIVATE	void	type_name();
PRIVATE	void	type_name_1();
PRIVATE	void	abstract_declarator();
PRIVATE	void	abstract_declarator_1();
PRIVATE	void	abstract_declarator_2();
PRIVATE	void	direct_abstract_declarator();
PRIVATE	void	direct_abstract_declarator_1();
PRIVATE	void	initializer();
PRIVATE	void	initializer_1();
PRIVATE	void	initializer_2();
PRIVATE	void	initializer_list();
PRIVATE	void	initializer_list_1();
PRIVATE struct ir_sts*	statement();
PRIVATE	struct ir_sts*	labeled_statement();
PRIVATE	struct ir_sts*	compound_statement();
PRIVATE	void	compound_statement_1();
PRIVATE	void	compound_statement_2();
PRIVATE	void	declaration_list();
PRIVATE	void	declaration_list_1();
PRIVATE	void	statement_list();
PRIVATE	void	statement_list_1();
PRIVATE	struct ir_sts*	expression_statement();
PRIVATE	struct ir_sts*	selection_statement();
PRIVATE	struct ir_sts *	selection_statement_1(struct ir_sts * sts, struct ir_exp *ret_exp, struct ir_sts * then_sts);
PRIVATE	struct ir_sts *	selection_statement_2(struct ir_sts * sts, struct ir_sts *else_sts);
PRIVATE	struct ir_sts*	iteration_statement();
PRIVATE	void	iteration_statement_1(struct ir_sts * ret_sts, struct ir_sts * sts, struct ir_exp *ret_exp);
PRIVATE	struct ir_sts*	jump_statement();
PRIVATE	void	jump_statement_1();
PRIVATE	void	translate_unit();
PRIVATE	void	translate_unit_1();
PRIVATE	void	external_declaration();
PRIVATE	void	function_definition();
PRIVATE	void	function_definition_1();
PRIVATE	void	function_definition_2();
PRIVATE	void	function_definition_3();
PRIVATE	void	function_definition_4();

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
	printf("	-- primary_expression  -- \n");
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
	else if(token == IDENTIFIER)
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		if(!symtbl_search_s(p_cur_token->val_s, function_id))
		{
			if(!symtbl_search(p_cur_token->val_s))
			{
				printf("\n[error]::primary_exp::variable(%s) not define in function(%d)!! exit\n\n",p_cur_token->val_s, function_id);
				exit(1);
			}			
		}

		
		//not a function
		if(!framelist_search_s(p_cur_token->val_s))
		{				
			cur_var	= search_var_s(p_cur_token->val_s);

			if(!cur_var)
			{
				printf("\n[error]::primary_exp::cur_var(%s) not define in !! exit\n\n",p_cur_token->val_s);
				exit(1);
			}
				 
			if(cur_var->type_id == STRUCT)
			{													
			}
	
			ret_exp	= ir_var_exp_build(cur_var);
		}
							
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(token == CONST_STRING)
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		strcopy(&(sym_t.val_s),p_cur_token->val_s);
		sym_t.val_s[strlen(&(sym_t.val_s))]	= NULL;

		if(flg_val_func)
		{
			if(symtbl_search(p_tmp_token->val_s))		// during declaring an array, the symbol is not in symbol table now
			{
				ir_fun_exp_update(exp, p_cur_token->val_s);				
			}
		}
		else
		{
			ret_exp	= ir_string_exp_build(sym_t.val_s);
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		sym_t.val_i	= s2i(p_cur_token->val_s);		
		ret_exp		= ir_const_exp_build(sym_t.val_i);		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}	

	return ret_exp;	
}


//===========================================================================
//postfix_expression() 
//===========================================================================
PRIVATE	struct ir_exp *	postfix_expression() 
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- postfix_expression  -- \n");
#endif
//--------------------------	

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp *ret_exp	= primary_expression(ret_exp);
	
	ret_exp	= postfix_expression_1(ret_exp);	

	return ret_exp;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

//===========================================================================
//PRIVATE	void	postfix_expression_1()
//===========================================================================
PRIVATE	struct ir_exp *	postfix_expression_1(struct ir_exp *exp)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- postfix_expression_1  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp *	ret_exp;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();	

	if(!parse_production_tab[PRODUCTION_64][FIRST_SET][token]) 
	{
		if(!parse_production_tab[PRODUCTION_64][FOLLOW_SET][token])
		{
			uget_tok(1);
			return exp;
		}
		else
		{
			//
		}
	}

	switch(token)
	{
		case OP_DOT:
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			p_tmp_token	= p_pre_token;

			ret_exp	= ir_postfix_exp_build(0, NULL, NULL);

			ret_exp->e.postfix.op	= IR_STRUCT;
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			get_tok();
			if(token == IDENTIFIER)
			{
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				is_struct();	
				
				ret_exp->e.postfix.left	= ir_var_exp_update(exp, p_cur_token->val_s, IR_STRUCT);
				
				ret_exp->e.postfix.right	= NULL;		
				
				ret_exp	= postfix_expression_1(ret_exp);

				return ret_exp;
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			}
			else
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_64][IDEN_LEN],token);
				exit(1);
			}
			break;

		case OP_POINTOR:
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			p_tmp_token	= p_pre_token;

			flg_val_pointer	= TRUE;	

			ret_exp	= ir_postfix_exp_build(0, NULL, NULL);
			
			ret_exp->e.postfix.op	= IR_POINTER;
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			get_tok();
			if(token == IDENTIFIER)
			{
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~				
				is_pointer();				
			
				ret_exp->e.postfix.left	= ir_var_exp_update(exp, p_cur_token->val_s, IR_POINTER);
				ret_exp->e.postfix.right= ir_string_exp_build(p_cur_token->val_s);
				
				ret_exp	= postfix_expression_1(ret_exp);

				return ret_exp;
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			}
			else
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_64][IDEN_LEN],token);
				exit(1);
			}
			break;
		
		case OP_PLUS_PLUS:
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ret_exp	= ir_postfix_exp_build(0, NULL, NULL);

			ret_exp->e.postfix.op	= IR_INC;
			ret_exp->e.postfix.left	= exp;		//identifier, array name
			ret_exp->e.postfix.right= ir_const_exp_build(1);

			ret_exp	= postfix_expression_1(ret_exp);

			return ret_exp;
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			break;

		case OP_MINUS_MINUS:			
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ret_exp	= ir_postfix_exp_build(0, NULL, NULL);

			ret_exp->e.postfix.op	= IR_DEC;
			ret_exp->e.postfix.left	= exp;		//identifier, array name
			ret_exp->e.postfix.right= ir_const_exp_build(1);

			ret_exp	= postfix_expression_1(ret_exp);

			return ret_exp;
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			break;

		case OP_L_BRACKET:
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
			is_array();

			flg_val_array	= TRUE;	
			p_tmp_token	= p_pre_token;
			
			ret_exp	= ir_postfix_exp_build(0, NULL, NULL);

			ret_exp->e.postfix.left	= exp;		//identifier, array name
			ret_exp->e.postfix.op	= IR_ARRAY;
			
			ret_exp->e.postfix.right= expression();			
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			get_tok();

			if(token == OP_R_BRACKET)
			{
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				flg_val_array	= FALSE;			
				
				ret_exp	= postfix_expression_1(ret_exp);

				return ret_exp;
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			}	
			else
			{
				printf("error:%s,token:%d\n\n",production_tab_info[PRODUCTION_64][IDEN_LEN],token);
				exit(1);
			}
			break;

		case OP_L_PARENTHESE:
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			is_function();

			flg_val_func	= TRUE;	

			p_tmp_token	= p_pre_token;
			
			ret_exp	= ir_fun_exp_build(p_pre_token->val_s);			

			cur_parm_explist	= explist_build(NULL);			
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


			get_tok();

			if((!parse_production_tab[PRODUCTION_3][FIRST_SET][token]) && (token != OP_R_PARENTHESE))
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_64][IDEN_LEN],token);
				exit(1);
			}
			else if(token == OP_R_PARENTHESE)
			{
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				flg_val_func	= FALSE;
				
				ret_exp->e.call.ppv	= NULL;

				ret_exp	= postfix_expression_1(ret_exp);

				return ret_exp;
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			}			
			else
			{
				uget_tok(1);
				
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				struct ir_exp *	ret_exp_1	= argument_expression_list(ret_exp_1);				
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

				get_tok();

				if(token == OP_R_PARENTHESE)
				{
					//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					flg_val_func	= FALSE;
					
					ret_exp->e.call.ppv	= cur_parm_explist;								

					ret_exp	= postfix_expression_1(ret_exp);
					
					return ret_exp;
					//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				}	
				else
				{
					printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_64][IDEN_LEN],token);
					exit(1);
				}				
			}
			break;
		default:
			break;
	}

	return ret_exp;	
}

//===========================================================================
//PRIVATE	void	argument_expression_list()
//===========================================================================
PRIVATE	struct ir_exp *	argument_expression_list()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- argument_expression_list  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_3][FIRST_SET][token])
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_3][IDEN_LEN],token);
		exit(1);
	}
	else
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ir_exp *ret_exp 	= ir_assign_exp_build(0, NULL, NULL);

		ret_exp->e.assign.op	= IR_OP_NULL;
		ret_exp->e.assign.res	= assignment_expression();
		ret_exp->e.assign.val	= NULL;
		
		struct ir_explist * explist_t = explist_build(ret_exp);
		ir_add2explist(explist_t, cur_parm_explist);
		
		ret_exp 	= argument_expression_list_1(ret_exp);

		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
}


//===========================================================================
//PRIVATE	void	argument_expression_list_1()
//===========================================================================
PRIVATE	struct ir_exp *	argument_expression_list_1(struct ir_exp *exp)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- argument_expression_list_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_65][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_65][FOLLOW_SET][token])
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
		flg_val_array	= FALSE;		
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;
		
		struct ir_exp *ret_exp 	= ir_assign_exp_build(0, NULL, NULL);

		ret_exp->e.assign.op	= IR_OP_NULL;		
		ret_exp->e.assign.res	= assignment_expression();
		ret_exp->e.assign.val	= NULL;
		
		struct ir_explist * explist_t = explist_build(ret_exp);
		ir_add2explist(explist_t, cur_parm_explist);
		
		ret_exp 	= argument_expression_list_1(ret_exp);

		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
}

//===========================================================================
//PRIVATE	void	unary_expression()
//===========================================================================
PRIVATE	struct ir_exp *	unary_expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- unary_expression  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_2][FIRST_SET][token])
	{
		uget_tok(1);
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ir_exp *ret_exp	= postfix_expression();

		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_5][FIRST_SET][token])
	{
		uget_tok(1);		

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ir_exp *ret_exp 	= ir_unary_exp_build(0, NULL);

		ret_exp->e.unary.op	= unary_operator();
		ret_exp->e.unary.left	= cast_expression();
		
		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if((token == OP_PLUS_PLUS)||(token == OP_MINUS_MINUS))
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ir_exp *ret_exp 	= ir_unary_exp_build(0, NULL);

		ret_exp->e.unary.op	= token;
		ret_exp->e.unary.left	= unary_expression();
		ret_exp->e.unary.right	= ir_const_exp_build(1);
		
		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(token == SIZEOF)
	{
		get_tok();

		if(token == OP_L_PARENTHESE)
		{
			get_tok();

			if(parse_production_tab[PRODUCTION_47][FIRST_SET][token])
			{
				uget_tok(1);
				
				type_name();
			
				get_tok();

				if(token != OP_R_PARENTHESE)
				{
					printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_4][IDEN_LEN],token);
					exit(1);
				}

				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				struct ir_exp *ret_exp 	= ir_unary_exp_build(0, NULL);

				ret_exp->e.unary.op	= SIZEOF;
				ret_exp->e.unary.left	= NULL;
				
				return ret_exp;
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			}
			else
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_4][IDEN_LEN],token);
				exit(1);
			}
		}
		else if(parse_production_tab[PRODUCTION_4][FIRST_SET][token])
		{
			uget_tok(1);			

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			struct ir_exp *ret_exp 	= ir_unary_exp_build(0, NULL);

			ret_exp->e.unary.op	= token;	//sizeof
			ret_exp->e.unary.left	= unary_expression();
			
			return ret_exp;
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}
		else
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_4][IDEN_LEN],token);
			exit(1);
		}		
	}

	return NULL;
}

//===========================================================================
//PRIVATE	void	unary_operator()
//===========================================================================
PRIVATE	s32	unary_operator()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- unary_operator  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_5][FIRST_SET][token])
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_5][IDEN_LEN],token);
		exit(1);
	}

	return token;	
}


//===========================================================================
// cast_expression()
//===========================================================================
PRIVATE	struct ir_exp *	cast_expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- cast_expression  -- \n\n");
#endif
//--------------------------

	get_tok();

	if(token == OP_L_PARENTHESE)
	{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- cast_expression(1)  -- \n\n");
#endif
//--------------------------

		get_tok();

		if(parse_production_tab[PRODUCTION_47][FIRST_SET][token])
		{
			uget_tok(1);

			type_name();
			
			get_tok();

			if(token != OP_R_PARENTHESE)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_6][IDEN_LEN],token);
				exit(1);
			}			

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			struct ir_exp *ret_exp	= cast_expression();

			return ret_exp;
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}
		else
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_6][IDEN_LEN],token);
			exit(1);
		}
	}
	else if(parse_production_tab[PRODUCTION_4][FIRST_SET][token])
	{
		uget_tok(1);		

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ir_exp *ret_exp	= unary_expression();

		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_6][IDEN_LEN],token);
		exit(1);
	}
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
	struct ir_exp *ret_exp	= cast_expression();
	
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

	if(!parse_production_tab[PRODUCTION_66][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_66][FOLLOW_SET][token])
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
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;

		struct ir_exp *ret_exp 	= ir_abop_exp_build(0, NULL, NULL);

		ret_exp->e.abop.op	= token;
		ret_exp->e.abop.left	= exp;
		
		ret_exp->e.abop.right	= cast_expression();
		
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

	//multiplicative_expression();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp *ret_exp	= multiplicative_expression();
	
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
	printf("	-- additive_expression_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_67][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_67][FOLLOW_SET][token])
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
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;

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
// shift_expression()
//===========================================================================
PRIVATE	struct ir_exp *	shift_expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- shift_expression  -- \n");
#endif
//--------------------------	
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp *ret_exp	= additive_expression();
	
	ret_exp	= shift_expression_1(ret_exp);

	return ret_exp;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

//===========================================================================
// shift_expression_1()
//===========================================================================
PRIVATE	struct ir_exp *	shift_expression_1(struct ir_exp *exp)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- shift_expression_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_68][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_68][FOLLOW_SET][token])
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
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;

		struct ir_exp *ret_exp 	= ir_abop_exp_build(0, NULL, NULL);

		ret_exp->e.abop.op	= token;
		ret_exp->e.abop.left	= exp;		
		ret_exp->e.abop.right	= additive_expression();
		
		ret_exp	= shift_expression_1(ret_exp);

		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}

	return NULL;
}

//===========================================================================
// relational_expression()
//===========================================================================
PRIVATE	struct ir_exp *	relational_expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- relational_expression  -- \n");
#endif
//--------------------------

	//shift_expression();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp *ret_exp	= shift_expression();
	
	ret_exp	= relational_expression_1(ret_exp);

	return ret_exp;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

//===========================================================================
// relational_expression_1()
//===========================================================================
PRIVATE	struct ir_exp *	relational_expression_1(struct ir_exp *exp)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- relational_expression_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_69][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_69][FOLLOW_SET][token])
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
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;

		struct ir_exp *ret_exp 	= ir_relate_exp_build(0, NULL, NULL);

		ret_exp->e.relate.op	= token;
		ret_exp->e.relate.left	= exp;		
		ret_exp->e.relate.right	= shift_expression();
		
		ret_exp	= relational_expression_1(ret_exp);

		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}

	return NULL;
}

//===========================================================================
// equality_expression()
//===========================================================================
PRIVATE	struct ir_exp *	equality_expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- equality_expression  -- \n");
#endif
//--------------------------	

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp *ret_exp	= relational_expression();
	
	ret_exp	= equality_expression_1(ret_exp);

	return ret_exp;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

//===========================================================================
// equality_expression_1()
//===========================================================================
PRIVATE	struct ir_exp *	equality_expression_1(struct ir_exp *exp)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- equality_expression_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_70][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_70][FOLLOW_SET][token])
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
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;

		struct ir_exp *ret_exp 	= ir_relate_exp_build(0, NULL, NULL);

		ret_exp->e.relate.op	= token;
		ret_exp->e.relate.left	= exp;		
		ret_exp->e.relate.right	= relational_expression();
		
		ret_exp	= equality_expression_1(ret_exp);

		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}

	return NULL;
}

//===========================================================================
// and_expression()
//===========================================================================
PRIVATE	struct ir_exp *	and_expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- and_expression  -- \n");
#endif
//--------------------------	

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp *ret_exp	= equality_expression();
	
	ret_exp	= and_expression_1(ret_exp);

	return ret_exp;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

//===========================================================================
// and_expression_1()
//===========================================================================
PRIVATE	struct ir_exp *	and_expression_1(struct ir_exp *exp)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- and_expression_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_71][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_71][FOLLOW_SET][token])
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
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;

		struct ir_exp *ret_exp 	= ir_relate_exp_build(0, NULL, NULL);

		ret_exp->e.relate.op	= token;
		ret_exp->e.relate.left	= exp;		
		ret_exp->e.relate.right	= equality_expression();
		
		ret_exp	= and_expression_1(ret_exp);

		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}

	return NULL;
}

//===========================================================================
// exclusive_or_expression()
//===========================================================================
PRIVATE	struct ir_exp *	exclusive_or_expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- exclusive_or_expression  -- \n");
#endif
//--------------------------	

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp *ret_exp	= and_expression();
	
	ret_exp	= exclusive_or_expression_1(ret_exp);

	return ret_exp;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

//===========================================================================
// exclusive_or_expression_1()
//===========================================================================
PRIVATE	struct ir_exp *	exclusive_or_expression_1(struct ir_exp *exp)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- exclusive_or_expression_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_72][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_72][FOLLOW_SET][token])
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
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;

		struct ir_exp *ret_exp 	= ir_relate_exp_build(0, NULL, NULL);

		ret_exp->e.relate.op	= token;
		ret_exp->e.relate.left	= exp;
		ret_exp->e.relate.right	= and_expression();
	
		ret_exp	= exclusive_or_expression_1(ret_exp);

		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	
	return NULL;
}


//===========================================================================
// inclusive_or_expression()
//===========================================================================
PRIVATE	struct ir_exp *	inclusive_or_expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- inclusive_or_expression  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp *ret_exp	= exclusive_or_expression();
	
	ret_exp	= inclusive_or_expression_1(ret_exp);

	return ret_exp;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

//===========================================================================
// inclusive_or_expression_1()
//===========================================================================
PRIVATE	struct ir_exp *	inclusive_or_expression_1(struct ir_exp *exp)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- inclusive_or_expression_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_73][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_73][FOLLOW_SET][token])
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
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;

		struct ir_exp *ret_exp 	= ir_relate_exp_build(0, NULL, NULL);

		ret_exp->e.relate.op	= token;
		ret_exp->e.relate.left	= exp;		
		ret_exp->e.relate.right	= exclusive_or_expression();
		
		ret_exp	= inclusive_or_expression_1(ret_exp);

		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}

	return NULL;
}

//===========================================================================
// inclusive_or_expression()
//===========================================================================
PRIVATE	struct ir_exp*	logical_and_expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- logical_and_expression  -- \n");
#endif
//--------------------------	

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp *ret_exp	= inclusive_or_expression();
	
	ret_exp	= logical_and_expression_1(ret_exp);

	return ret_exp;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

//===========================================================================
// inclusive_or_expression_1()
//===========================================================================
PRIVATE	struct ir_exp*	logical_and_expression_1(struct ir_exp* exp)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- logical_and_expression_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_74][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_74][FOLLOW_SET][token])
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
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;

		struct ir_exp *ret_exp 	= ir_relate_exp_build(0, NULL, NULL);

		ret_exp->e.relate.op	= token;
		ret_exp->e.relate.left	= exp;		
		ret_exp->e.relate.right	= inclusive_or_expression();
		
		ret_exp	= logical_and_expression_1(ret_exp);

		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}

	return NULL;
}

//===========================================================================
// logical_or_expression()
//===========================================================================
PRIVATE	struct ir_exp*	logical_or_expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- logical_or_expression  -- \n");
#endif
//--------------------------	

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp *ret_exp	= logical_and_expression();
	
	ret_exp	= logical_or_expression_1(ret_exp);

	return ret_exp;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

//===========================================================================
// logical_or_expression_1()
//===========================================================================
PRIVATE	struct ir_exp*	logical_or_expression_1(struct ir_exp*	exp)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- logical_or_expression_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_75][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_75][FOLLOW_SET][token])
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
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;

		struct ir_exp *ret_exp 	= ir_relate_exp_build(0, NULL, NULL);

		ret_exp->e.relate.op	= token;
		ret_exp->e.relate.left	= exp;		
		ret_exp->e.relate.right	= logical_and_expression();
		
		ret_exp	= logical_or_expression_1(ret_exp);

		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}

	return NULL;
}

//===========================================================================
// conditional_expression()
//===========================================================================
PRIVATE	struct ir_exp*	conditional_expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- conditional_expression  -- \n");
#endif
//--------------------------	

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	struct ir_exp *ret_exp	= logical_or_expression();
	
	ret_exp	= conditional_expression_1(ret_exp);

	return ret_exp;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
}


//===========================================================================
// conditional_expression_1()
//===========================================================================
PRIVATE	struct ir_exp*	conditional_expression_1(struct ir_exp *cond)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- conditional_expression_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_76][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_76][FOLLOW_SET][token])
		{
			uget_tok(1);
			return cond;
		}
		else
		{
			//
		}
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;
		
		struct ir_exp *ret_exp	= ir_cond_exp_build(NULL, NULL, NULL);
		ret_exp->e.cond.cond	= cond;		
		ret_exp->e.cond.op_1	= expression();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		get_tok();
		if(token != OP_COLON)
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_76][IDEN_LEN],token);
			exit(1);
		}
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;
		
		ret_exp->e.cond.op_2	= conditional_expression();

		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
	}

	return NULL;
}

//===========================================================================
// assignment_expression()
//===========================================================================
PRIVATE	struct ir_exp*	assignment_expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- assignment_expression  -- \n");
#endif
//--------------------------
	
	s32 i;
	s8 flg;

	flg = FALSE;
	i=0;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp *ret_exp	= ir_assign_exp_build(0, NULL, NULL);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if(flg_val_array)
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
		if(!ret_exp->e.assign.res)
		{
			ret_exp->e.assign.res	= conditional_expression();
		}
		else
		{
			ret_exp->e.assign.val	= conditional_expression();
		}		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else
	{
		do
		{
			get_tok();
			i++;

			if(parse_production_tab[PRODUCTION_19][FIRST_SET][token])
			{
				flg	= TRUE;
				break;
			} 

		}while(token != SEMICOLON);

		if(flg)
		{
			uget_tok(i);		

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ret_exp->e.assign.res	= unary_expression();
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			

			get_tok();
			if(token != OP_R_BRACKET)
			{
				uget_tok(1);
			}			

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ret_exp->e.assign.op	= assignment_operator();			
			ret_exp->e.assign.val	= assignment_expression();
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}
		else
		{
			uget_tok(i);			

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if(!ret_exp->e.assign.res)
			{
				ret_exp->e.assign.res	= conditional_expression();
			}
			else
			{
				ret_exp->e.assign.val	= conditional_expression();
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	return ret_exp;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

//===========================================================================
// assignment_operator()
//===========================================================================
PRIVATE	s32	assignment_operator()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- assignment_operator  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_19][FIRST_SET][token])
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_19][IDEN_LEN],token);
		exit(1);
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}

	return token;
}

//===========================================================================
// assignment_operator()
//===========================================================================
PRIVATE	struct ir_exp*	expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- expression  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp*  ret_exp	= assignment_expression();
	
	if(!flg_val_array)
	{
		struct ir_explist * explist_t = explist_build(ret_exp);
		ir_add2explist(explist_t, cur_explist);
	}
	
	
	ret_exp	= expression_1(ret_exp);

	return ret_exp;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
}

//===========================================================================
// expression_1()
//===========================================================================
PRIVATE	struct ir_exp*	expression_1(struct ir_exp* exp)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- expression_1  -- \n");
#endif
//--------------------------	

	get_tok();

	if(!parse_production_tab[PRODUCTION_77][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_77][FOLLOW_SET][token])
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
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;		
		
		struct ir_exp*	ret_exp	= ir_assign_exp_build(0, NULL, NULL);
		ret_exp->e.assign.op	= IR_ASSIGN;
		ret_exp->e.assign.res	= exp;
		ret_exp->e.assign.val	= assignment_expression();
		
		struct ir_explist * explist_t = explist_build(ret_exp);
		ir_add2explist(explist_t, cur_explist);

		ret_exp	= expression_1(ret_exp);

		return ret_exp;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
}

//===========================================================================
// constant_expression()
//===========================================================================
PRIVATE	struct ir_exp*	constant_expression()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- constant_expression  -- \n");
#endif
//--------------------------	

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp*	ret_exp	= conditional_expression();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}


//===========================================================================
// declaration()
//===========================================================================
PRIVATE	void	declaration()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- declaration -- \n");
#endif
//--------------------------

	declaration_specifiers();
	declaration_1();
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
	
	if(token == SEMICOLON)
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		sym_t.len	= check_type_l(sym_t.type_ts);

		symbol_pre_set(&sym_t);
		
		if(sym_t.flg_func)
		{
			fun_build(&sym_t);
		}
		else
		{
			var_build(&sym_t);
		}

		symtbl_add_s(&sym_t);
		symbol_empty(&sym_t);		
		
		flg_val_array	= FALSE;
		flg_val_func	= FALSE;
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		return;
	}
	else if(parse_production_tab[PRODUCTION_24][FIRST_SET][token])
	{
		uget_tok(1);
		init_declarator_list();

		get_tok();
		if(token != SEMICOLON)
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_78][IDEN_LEN],token);
			exit(1);
		}
		else
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
			if(sym_t.type_scs == TYPEDEF)
			{
				s8 *src_name	= check_type_s(sym_t.type_ts);

				s32 len		= check_type_l(sym_t.type_ts);				

				add_typelist(0, len, src_name , p_pre_token->val_s, NULL);

				symbol_empty(&sym_t);
			}
			else
			{
				sym_t.len	= check_type_l(sym_t.type_ts);

				symbol_pre_set(&sym_t);

				if(sym_t.flg_func)
				{
					fun_build(&sym_t);
				}
				else
				{
					var_build(&sym_t);
				}

				symtbl_add_s(&sym_t);
				symbol_empty(&sym_t);
			}
			
			flg_val_array	= FALSE;
			flg_val_func	= FALSE;
			flg_val_pointer	= FALSE;
			flg_val_struct_union	= FALSE;
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_78][IDEN_LEN],token);
		exit(1);
	}
}

//===========================================================================
// declaration_specifiers()
//===========================================================================
PRIVATE	void	declaration_specifiers()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- declaration_specifiers  -- \n");
#endif
//--------------------------

	declaration_specifiers_1();
	declaration_specifiers_2();
}

//===========================================================================
// declaration_specifiers_1()
//===========================================================================
PRIVATE	void	declaration_specifiers_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- declaration_specifiers_1  -- \n");
#endif
//--------------------------

	s32 ty;

	get_tok();

	if(parse_production_tab[PRODUCTION_26][FIRST_SET][token])
	{
		uget_tok(1);
		storage_class_specifier();
	}
	else if(parse_production_tab[PRODUCTION_27][FIRST_SET][token])
	{
		uget_tok(1);
		type_specifier();
	}
	else if(parse_production_tab[PRODUCTION_38][FIRST_SET][token])
	{
		uget_tok(1);
		type_qualifier();
	}
	else if(token == ELLIPSIS)
	{		
		uget_tok(1);
		return ;
	}
	else if(ty = check_type_i(p_cur_token->val_s))		//type_name
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		sym_t.type_ts	= ty;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_79][IDEN_LEN],token);
		exit(1);
	}
}

//===========================================================================
// declaration_specifiers_2()
//===========================================================================
PRIVATE	void	declaration_specifiers_2()
{	
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- declaration_specifiers_2  -- \n");
#endif
//--------------------------
	
	get_tok();	

	if(parse_production_tab[PRODUCTION_80][FIRST_SET][token])
	{
		uget_tok(1);
		declaration_specifiers();
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_80][FOLLOW_SET][token])
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
// init_declarator_list()
//===========================================================================
PRIVATE	void	init_declarator_list()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- init_declarator_list  -- \n");
#endif
//--------------------------

	init_declarator();
	init_declarator_list_1();
}


//===========================================================================
// init_declarator_list_1()
//===========================================================================
PRIVATE	void	init_declarator_list_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- init_declarator_list_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_81][FIRST_SET][token])
	{	
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		sym_t.len	= check_type_l(sym_t.type_ts);

		symbol_pre_set(&sym_t);		

		if(sym_t.flg_func)
		{
			fun_build(&sym_t);
		}
		else
		{
			var_build(&sym_t);
		}

		symtbl_add_s(&sym_t);		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		init_declarator();
		init_declarator_list_1();
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_81][FOLLOW_SET][token])
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
// init_declarator()
//===========================================================================
PRIVATE	void	init_declarator()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- init_declarator  -- \n");
#endif
//--------------------------

	declarator();
	init_declarator_1();
}

//===========================================================================
// init_declarator_1()
//===========================================================================
PRIVATE	void	init_declarator_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- init_declarator_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(token == OP_EQU)
	{		
		initializer();
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_82][FOLLOW_SET][token])
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

	if(!parse_production_tab[PRODUCTION_26][FIRST_SET][token])
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_26][IDEN_LEN],token);
		exit(1);
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		if(!flg_param)
		{
			sym_t.type_scs	= token;
		}
		else
		{
			ptlist_t.type_scs	= token;
		}
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

	if(!parse_production_tab[PRODUCTION_27][FIRST_SET][token])
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_27][IDEN_LEN],token);
		exit(1);
	}
	else if(parse_production_tab[PRODUCTION_28][FIRST_SET][token])
	{
		uget_tok(1);
		struct_or_union_specifier();
	}
	else if(parse_production_tab[PRODUCTION_35][FIRST_SET][token])
	{
		uget_tok(1);
		enum_specifier();
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		if(!flg_param)
		{
			if(flg_struct_union)
			{
				mblist_t.type_ts	= token;
			}
			else if((token == STRUCT)||(token == UNION))
			{				
			}
			else if(token == ENUM)
			{
			}
			else
			{
				sym_t.type_ts	= token;
			}
		}
		else
		{
			ptlist_t.type_ts	= token;			
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
}

//===========================================================================
// struct_or_union_specifier()
//===========================================================================
PRIVATE	void	struct_or_union_specifier()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- struct_or_union_specifier  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	flg_struct_union	= TRUE;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	struct_or_union();
	struct_or_union_specifier_1();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	flg_struct_union	= FALSE;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

//===========================================================================
// struct_or_union_specifier_1()
//===========================================================================
PRIVATE	void	struct_or_union_specifier_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- struct_or_union_specifier_1  -- \n");
#endif
//--------------------------

	struct_or_union_specifier_2();
	struct_or_union_specifier_3();
}

//===========================================================================
// struct_or_union_specifier_2()
//===========================================================================
PRIVATE	void	struct_or_union_specifier_2()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- struct_or_union_specifier_2  -- \n");
#endif
//--------------------------

	get_tok();

	if(token != IDENTIFIER)
	{
		if(!parse_production_tab[PRODUCTION_84][FOLLOW_SET][token])
		{
			uget_tok(1);
			return;
		}
		else
		{
			//
		}	
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		strcopy(&(sym_t.su.name), p_cur_token->val_s);
		sym_t.su.name[strlen(p_cur_token->val_s)]	= NULL;		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
}

//===========================================================================
// struct_or_union_specifier_3()
//===========================================================================
PRIVATE	void	struct_or_union_specifier_3()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- struct_or_union_specifier_3  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_85][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_85][FOLLOW_SET][token])
		{
			uget_tok(1);
			return;
		}
		else
		{
			//
		}	
	}
	else
	{		
		struct_declaration_list();

		get_tok();

		if(token != OP_R_BRACE)
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_85][IDEN_LEN],token);
			exit(1);
		}
	}
}


//===========================================================================
// struct_or_union()
//===========================================================================
PRIVATE	void	struct_or_union()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- struct_or_union  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_29][FIRST_SET][token])
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_29][IDEN_LEN],token);
		exit(1);	
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		sym_t.type_ts	= token;
		flg_struct_union	= TRUE;				
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
}

//===========================================================================
// struct_declaration_list()
//===========================================================================
PRIVATE	void	struct_declaration_list()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- struct_declaration_list  -- \n");
#endif
//--------------------------

	struct_declaration();
	struct_declaration_list_1();
}

//===========================================================================
// struct_declaration_list_1()
//===========================================================================
PRIVATE	void	struct_declaration_list_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- struct_declaration_list_1  -- \n");
#endif
//--------------------------
	
	get_tok();

	if(parse_production_tab[PRODUCTION_30][FIRST_SET][token])
	{
		uget_tok(1);

		struct_declaration();
		struct_declaration_list_1();	
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_86][FOLLOW_SET][token])
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
// struct_declaration()
//===========================================================================
PRIVATE	void	struct_declaration()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- struct_declaration  -- \n");
#endif
//--------------------------

	specifier_qualifier_list();
	struct_declarator_list();

	get_tok();

	if(token != SEMICOLON)
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_31][IDEN_LEN],token);
		exit(1);
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		mblist_t.len	= check_type_l(mblist_t.type_ts);

		mblist_add_s(&mblist_t);
		mblist_empty(&mblist_t);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
}


//===========================================================================
// specifier_qualifier_list()
//===========================================================================
PRIVATE	void	specifier_qualifier_list()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- specifier_qualifier_list  -- \n");
#endif
//--------------------------

	specifier_qualifier_list_1();
	specifier_qualifier_list_2();
}

//===========================================================================
// specifier_qualifier_list_1()
//===========================================================================
PRIVATE	void	specifier_qualifier_list_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- specifier_qualifier_list_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_27][FIRST_SET][token])
	{
		uget_tok(1);
		type_specifier();
	}
	else if(parse_production_tab[PRODUCTION_38][FIRST_SET][token])
	{
		uget_tok(1);
		type_qualifier();
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_87][IDEN_LEN],token);
		exit(1);
	}
	
}

//===========================================================================
// specifier_qualifier_list_2()
//===========================================================================
PRIVATE	void	specifier_qualifier_list_2()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- specifier_qualifier_list_2  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_32][FIRST_SET][token])
	{
		uget_tok(1);
		specifier_qualifier_list();
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_88][FOLLOW_SET][token])
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
// struct_declarator_list()
//===========================================================================
PRIVATE	void	struct_declarator_list()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- struct_declarator_list  -- \n");
#endif
//--------------------------

	struct_declarator();
	struct_declarator_list_1();
}

//===========================================================================
// struct_declarator_list_1()
//===========================================================================
PRIVATE	void	struct_declarator_list_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- struct_declarator_list_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_89][FIRST_SET][token])
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		mblist_t.len	= check_type_l(mblist_t.type_ts);

		mblist_add_s(&mblist_t);		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		struct_declarator();
		struct_declarator_list_1();
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_89][FOLLOW_SET][token])
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
// struct_declarator()
//===========================================================================
PRIVATE	void	struct_declarator()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- struct_declarator  -- \n");
#endif
//--------------------------

	struct_declarator_1();
	struct_declarator_2();
}


//===========================================================================
// struct_declarator_1()
//===========================================================================
PRIVATE	void	struct_declarator_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- struct_declarator_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_90][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_90][FOLLOW_SET][token])
		{
			uget_tok(1);
			return;
		}
		else
		{
			//
		}
	}
	else
	{
		uget_tok(1);
		declarator();
	}
}

//===========================================================================
// struct_declarator_1()
//===========================================================================
PRIVATE	void	struct_declarator_2()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- struct_declarator_2  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_91][FIRST_SET][token]) 	{
		
		constant_expression();		
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_91][FOLLOW_SET][token])
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
// enum_specifier()
//===========================================================================
PRIVATE	void	enum_specifier()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- enum_specifier  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_35][FIRST_SET][token]) 
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_35][IDEN_LEN],token);
		exit(1);		
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		sym_t.type_ts	= token;		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	
	enum_specifier_1();
	enum_specifier_2();
}

//===========================================================================
// enum_specifier_1()
//===========================================================================
PRIVATE	void	enum_specifier_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- enum_specifier_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_92][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_92][FOLLOW_SET][token])
		{
			uget_tok(1);
			return;
		}
		else
		{
			//
		}
	}
	else
	{
		//
	}
}

//===========================================================================
// enum_specifier_2()
//===========================================================================
PRIVATE	void	enum_specifier_2()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- enum_specifier_2  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_93][FIRST_SET][token]) 
	{		
		enumerator_list();

		get_tok();
		if(token != OP_R_BRACE)
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_93][IDEN_LEN],token);
			exit(1);
		}		
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_93][FOLLOW_SET][token])
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
// enumerator_list()
//===========================================================================
PRIVATE	void	enumerator_list()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- enumerator_list  -- \n");
#endif
//--------------------------

	enumerator();
	enumerator_list_1();
}

//===========================================================================
// enumerator_list_1()
//===========================================================================
PRIVATE	void	enumerator_list_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- enumerator_list_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_94][FIRST_SET][token])
	{		
		enumerator();
		enumerator_list_1();
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_94][FOLLOW_SET][token])
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
// enumerator()
//===========================================================================
PRIVATE	void	enumerator()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- enumerator  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_37][FIRST_SET][token])
	{		
		enumerator_1();
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_37][IDEN_LEN],token);
		exit(1);
	}
}

//===========================================================================
// enumerator_1()
//===========================================================================
PRIVATE	void	enumerator_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- enumerator_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_95][FIRST_SET][token])
	{		
		constant_expression();
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_95][FOLLOW_SET][token])
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
// type_qualifier()
//===========================================================================
PRIVATE	void	type_qualifier()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- type_qualifier  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_38][FIRST_SET][token])
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_38][IDEN_LEN],token);
		exit(1);
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		if(!flg_param)
		{
			if((sym_t.type_ts == STRUCT) || (sym_t.type_ts == UNION))
			{
				mblist_t.type_tq	= token;
			}
			else if(sym_t.type_ts == ENUM)
			{
				sym_t.type_tq	= token;
			}
			else
			{
				sym_t.type_tq	= token;
			}
		}
		else
		{
			ptlist_t.type_tq	= token;
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
	printf("	-- declarator  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_41][FIRST_SET][token])
	{
		uget_tok(1);
		pointer();
		direct_declarator();
	}
	else if(parse_production_tab[PRODUCTION_40][FIRST_SET][token])
	{
		uget_tok(1);
		direct_declarator();
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_39][IDEN_LEN],token);
		exit(1);
	}
}

//===========================================================================
// direct_declarator()
//===========================================================================
PRIVATE	void	direct_declarator()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- direct_declarator  -- \n");
#endif
//--------------------------

	get_tok();
	if(!parse_production_tab[PRODUCTION_40][FIRST_SET][token])
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_40][IDEN_LEN],token);
		exit(1);
	}



	if(token == IDENTIFIER)
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		if(!flg_param)
		{
			if(!flg_struct_union)
			{
				strcopy(&(sym_t.name), p_cur_token->val_s);
				sym_t.name[strlen(p_cur_token->val_s)]	= NULL;
			}
			else
			{
				strcopy(&(mblist_t.name), p_cur_token->val_s);
				mblist_t.name[strlen(p_cur_token->val_s)]	= NULL;
			}
		}
		else
		{
			strcopy(&(ptlist_t.name), p_cur_token->val_s);
			ptlist_t.name[strlen(p_cur_token->val_s)]	= NULL;
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		direct_declarator_1();
	}
	else if(token == OP_L_PARENTHESE)
	{		
		declarator();

		get_tok();
		if(token == OP_R_PARENTHESE)
		{			
			direct_declarator_1();
		}
		else
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_40][IDEN_LEN],token);
			exit(1);
		}
	}
}

//===========================================================================
// direct_declarator_1()
//===========================================================================
PRIVATE	void	direct_declarator_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- direct_declarator_1  -- \n");
#endif
//--------------------------

	get_tok();
	old_token = token;

	if(!parse_production_tab[PRODUCTION_96][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_96][FOLLOW_SET][token])
		{
			uget_tok(1);
			return;
		}
		else
		{
			//
		}
	}
	else
	{
		get_tok();

		if(parse_production_tab[PRODUCTION_43][FIRST_SET][token])
		{
			uget_tok(1);
			parameter_type_list();

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			sym_t.flg_func	= TRUE;
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			get_tok();
			if(token != OP_R_PARENTHESE)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_96][IDEN_LEN],token);
				exit(1);
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
			if(p_pre_token->token != ELLIPSIS)
			{
				ptlist_t.len	= check_type_l(ptlist_t.type_ts);

				ptlist_add_s(&ptlist_t);
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			
			direct_declarator_1();
		}
		else if((parse_production_tab[PRODUCTION_21][FIRST_SET][token]) && (old_token == OP_L_BRACKET))
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			sym_t.flg_array	= TRUE;
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			uget_tok(1);
			constant_expression();			

			get_tok();			

			if(token != OP_R_BRACKET)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_96][IDEN_LEN],token);
				exit(1);
			}
			
			direct_declarator_1();
		}
		else if(parse_production_tab[PRODUCTION_46][FIRST_SET][token]) 
		{
			uget_tok(1);
			identifier_list();			

			get_tok();
			if(token != OP_R_PARENTHESE)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_96][IDEN_LEN],token);
				exit(1);
			}
		
			direct_declarator_1();
		}
		else if((old_token == OP_L_PARENTHESE) && (token == OP_R_PARENTHESE))
		{			
			direct_declarator_1();
		}
		else if((old_token == OP_L_BRACKET) && (token == OP_R_BRACKET))
		{			
			direct_declarator_1();
		}
		else
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_96][IDEN_LEN],token);
			exit(1);
		}
	}
}


//===========================================================================
// pointer()
//===========================================================================
PRIVATE	void	pointer()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- pointer  -- \n");
#endif
//--------------------------

	get_tok();
	
	if(parse_production_tab[PRODUCTION_41][FIRST_SET][token]) 
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		sym_t.flg_pointer	= TRUE;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		pointer_1();
		pointer_2();
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_41][IDEN_LEN],token);
		exit(1);
	}
}

//===========================================================================
// pointer_1()
//===========================================================================
PRIVATE	void	pointer_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- pointer_1  -- \n");
#endif
//--------------------------

	get_tok();
	
	if(!parse_production_tab[PRODUCTION_100][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_100][FOLLOW_SET][token])
		{
			uget_tok(1);
			return;
		}
		else
		{
			//
		}
	}	
	else
	{
		uget_tok(1);
		type_qualifier_list();
	}
}

//===========================================================================
// pointer_2()
//===========================================================================
PRIVATE	void	pointer_2()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- pointer_2  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_101][FIRST_SET][token])
	{
		uget_tok(1);
		pointer();
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_101][FOLLOW_SET][token])
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
// type_qualifier_list()
//===========================================================================
PRIVATE	void	type_qualifier_list()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- type_qualifier_list  -- \n");
#endif
//--------------------------


	type_qualifier();
	type_qualifier_list_1();
}

//===========================================================================
// type_qualifier_list_1()
//===========================================================================
PRIVATE	void	type_qualifier_list_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- type_qualifier_list_1  -- \n");
#endif
//--------------------------

	get_tok();
	
	if(!parse_production_tab[PRODUCTION_102][FIRST_SET][token])
	{
		if(!parse_production_tab[PRODUCTION_102][FOLLOW_SET][token])
		{
			uget_tok(1);
			return;
		}
		else
		{
			//
		}
	}	
	else
	{
		uget_tok(1);
		type_qualifier();
		type_qualifier_list_1();
	}
}


//===========================================================================
// parameter_type_list()
//===========================================================================
PRIVATE	void	parameter_type_list()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- parameter_type_list  -- \n");
#endif
//--------------------------

	parameter_list();
	parameter_type_list_1();	
}

//===========================================================================
// parameter_type_list_1()
//===========================================================================
PRIVATE	void	parameter_type_list_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- parameter_type_list_1  -- \n");
#endif
//--------------------------

	get_tok();
	
	if(!parse_production_tab[PRODUCTION_103][FIRST_SET][token]) 
	{
		if(!parse_production_tab[PRODUCTION_103][FOLLOW_SET][token])
		{
			uget_tok(1);
			return;
		}
		else
		{
			//
		}
	}
	else
	{
		get_tok();
	
		if(token != ELLIPSIS) 
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_103][IDEN_LEN],token);
			exit(1);
		}		
	}
}

//===========================================================================
// parameter_list()
//===========================================================================
PRIVATE	void	parameter_list()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- parameter_list  -- \n");
#endif
//--------------------------

	parameter_declaration();
	parameter_list_1();
}


//===========================================================================
// parameter_list_1()
//===========================================================================
PRIVATE	void	parameter_list_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- parameter_list_1  -- \n");
#endif
//--------------------------

	get_tok();
	
	if(parse_production_tab[PRODUCTION_104][FIRST_SET][token]) 
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ptlist_t.len	= check_type_l(ptlist_t.type_ts);

		ptlist_add_s(&ptlist_t);
		ptlist_empty(&ptlist_t);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		parameter_declaration();
		parameter_list_1();
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_104][FOLLOW_SET][token])
		{			
			if(token == ELLIPSIS)
			{
				uget_tok(2);
				return;
			}
			else
			{
				uget_tok(1);
				return;
			}
		}
		else
		{
			//
		}
	}	
}

//===========================================================================
// parameter_declaration()
//===========================================================================
PRIVATE	void	parameter_declaration()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- parameter_declaration  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	flg_param	= TRUE;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	declaration_specifiers();

	parameter_declaration_1();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	flg_param	= FALSE;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

//===========================================================================
// parameter_declaration_1()
//===========================================================================
PRIVATE	void	parameter_declaration_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- parameter_declaration_1  -- \n");
#endif
//--------------------------
	
	get_tok();
	
	if(!parse_production_tab[PRODUCTION_105][FIRST_SET][token]) 
	{		
		if(token == ELLIPSIS)
		{
			uget_tok(1);
			return ;
		}
		else
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_105][IDEN_LEN],token);
			exit(1);
		}
	}
	
	switch(token)
	{
		case OP_MUL:						
			parameter_declaration_1();			
			break;
		case OP_L_PARENTHESE:			
			get_tok();
			if(token == OP_R_PARENTHESE)
			{
				uget_tok(2);
				abstract_declarator();
			}
			else
			{		
				parameter_declaration_1();
			}
			break;
		case OP_R_PARENTHESE:			
			break;
		case IDENTIFIER:
			uget_tok(1);
			declarator();
			break;
		case OP_L_BRACKET:
			uget_tok(1);
			abstract_declarator();
			break;
		default:
			break;
	}
}

//===========================================================================
// identifier_list()
//===========================================================================
PRIVATE	void	identifier_list()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- identifier_list  -- \n");
#endif
//--------------------------

	get_tok();
	
	if(!parse_production_tab[PRODUCTION_46][FIRST_SET][token]) 
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_46][IDEN_LEN],token);
		exit(1);
	}
	else
	{		
	}
	
	identifier_list_1();
}

//===========================================================================
// identifier_list_1()
//===========================================================================
PRIVATE	void	identifier_list_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- identifier_list_1  -- \n");
#endif
//--------------------------

	get_tok();
	
	if(parse_production_tab[PRODUCTION_106][FIRST_SET][token]) 
	{
		get_tok();

		if(token != IDENTIFIER) 
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_106][IDEN_LEN],token);
			exit(1);
		}
		else
		{
			identifier_list_1();
		}
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_106][FOLLOW_SET][token])
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
// type_name()
//===========================================================================
PRIVATE	void	type_name()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- type_name  -- \n");
#endif
//--------------------------

	specifier_qualifier_list();
	type_name_1();
}

//===========================================================================
// type_name_1()
//===========================================================================
PRIVATE	void	type_name_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- type_name_1  -- \n");
#endif
//--------------------------

	get_tok();
	
	if(parse_production_tab[PRODUCTION_107][FIRST_SET][token]) 
	{
		uget_tok(1);
		abstract_declarator();
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_107][FOLLOW_SET][token])
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
// abstract_declarator()
//===========================================================================
PRIVATE	void	abstract_declarator()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- abstract_declarator  -- \n");
#endif
//--------------------------

	abstract_declarator_1();
	abstract_declarator_2();
}

//===========================================================================
// abstract_declarator_1()
//===========================================================================
PRIVATE	void	abstract_declarator_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- abstract_declarator_1  -- \n");
#endif
//--------------------------

	get_tok();
	
	if(parse_production_tab[PRODUCTION_108][FIRST_SET][token]) 
	{
		uget_tok(1);
		pointer();
	}
	else if(parse_production_tab[PRODUCTION_108][FOLLOW_SET][token])
	{
		uget_tok(1);
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_108][IDEN_LEN],token);
		exit(1);
	}
}

//===========================================================================
// abstract_declarator_2()
//===========================================================================
PRIVATE	void	abstract_declarator_2()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- abstract_declarator_2  -- \n");
#endif
//--------------------------

	get_tok();
	
	if(parse_production_tab[PRODUCTION_109][FIRST_SET][token]) 
	{
		uget_tok(1);
		direct_abstract_declarator();
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_109][FOLLOW_SET][token])
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
// direct_abstract_declarator()
//===========================================================================
PRIVATE	void	direct_abstract_declarator()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- direct_abstract_declarator  -- \n");
#endif
//--------------------------

	get_tok();
	
	if(!parse_production_tab[PRODUCTION_49][FIRST_SET][token])
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_49][IDEN_LEN],token);
		exit(1);
	}

	if(token == OP_L_PARENTHESE)		
	{
		get_tok();

		if(parse_production_tab[PRODUCTION_43][FIRST_SET][token])
		{
			uget_tok(1);
			parameter_type_list();

			get_tok();
			if(token != OP_R_BRACKET)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_49][IDEN_LEN],token);
				exit(1);
			}
			
			direct_abstract_declarator_1();
		}
		else if(parse_production_tab[PRODUCTION_48][FIRST_SET][token])
		{
			uget_tok(1);
			abstract_declarator();

			get_tok();
			if(token != OP_R_BRACKET)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_49][IDEN_LEN],token);
				exit(1);
			}
			
			direct_abstract_declarator_1();
		}
		else if(token == OP_R_PARENTHESE)
		{
			direct_abstract_declarator_1();
		}
	}
	else if(old_token == OP_L_BRACKET)
	{
		get_tok();

		if(parse_production_tab[PRODUCTION_21][FIRST_SET][token])
		{
			uget_tok(1);
			constant_expression();

			get_tok();
			if(token != OP_R_BRACKET)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_49][IDEN_LEN],token);
				exit(1);
			}
			
			direct_abstract_declarator_1();
		}
		else if(token == OP_R_BRACKET)
		{
			direct_abstract_declarator_1();
		}
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_49][IDEN_LEN],token);
		exit(1);
	}
}

//===========================================================================
// direct_abstract_declarator_1()
//===========================================================================
PRIVATE	void	direct_abstract_declarator_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- direct_abstract_declarator_1  -- \n");
#endif
//--------------------------

	get_tok();	
	
	if(!parse_production_tab[PRODUCTION_110][FIRST_SET][token]) 
	{
		if(!parse_production_tab[PRODUCTION_110][FOLLOW_SET][token])
		{
			uget_tok(1);
			return;
		}
		else
		{
			//
		}
	}
	else
	{
		if(token == OP_L_PARENTHESE)		
		{
			get_tok();

			if(parse_production_tab[PRODUCTION_43][FIRST_SET][token])
			{
				uget_tok(1);
				parameter_type_list();

				get_tok();
				if(token != OP_R_BRACKET)
				{
					printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_49][IDEN_LEN],token);
					exit(1);
				}
				
				direct_abstract_declarator_1();
			}
			else if(parse_production_tab[PRODUCTION_48][FIRST_SET][token])
			{
				uget_tok(1);
				abstract_declarator();

				get_tok();
				if(token != OP_R_BRACKET)
				{
					printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_49][IDEN_LEN],token);
					exit(1);
				}
				
				direct_abstract_declarator_1();
			}
			else if(token == OP_R_PARENTHESE)
			{
				direct_abstract_declarator_1();
			}
		}
		else if(old_token == OP_L_BRACKET)
		{
			get_tok();

			if(parse_production_tab[PRODUCTION_21][FIRST_SET][token])
			{
				uget_tok(1);
				constant_expression();

				get_tok();
				if(token != OP_R_BRACKET)
				{
					printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_49][IDEN_LEN],token);
					exit(1);
				}
				
				direct_abstract_declarator_1();
			}
			else if(token == OP_R_BRACKET)
			{
				direct_abstract_declarator_1();
			}
		}
		else
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_49][IDEN_LEN],token);
			exit(1);
		}
	}
}

//===========================================================================
// initializer()
//===========================================================================
PRIVATE	void	initializer()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- initializer  -- \n");
#endif
//--------------------------

	initializer_1();
	initializer_2();
}

//===========================================================================
// initializer_1()
//===========================================================================
PRIVATE	void	initializer_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- initializer_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_18][FIRST_SET][token]) 
	{
		uget_tok(1);
		assignment_expression();
	}
	else if(token == OP_L_BRACE)
	{		
		initializer_list();
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_114][IDEN_LEN],token);
		exit(1);
	}
}

//===========================================================================
// initializer_2()
//===========================================================================
PRIVATE	void	initializer_2()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- initializer_2  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_115][FIRST_SET][token]) 
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_115][IDEN_LEN],token);
		exit(1);
	}
	else
	{
		get_tok();

		if(token != OP_R_BRACE) 
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_115][IDEN_LEN],token);
			exit(1);
		}
	}
}

//===========================================================================
// initializer_list()
//===========================================================================
PRIVATE	void	initializer_list()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- initializer_list  -- \n");
#endif
//--------------------------

	initializer();
	initializer_list_1();
}

//===========================================================================
// initializer_list_1()
//===========================================================================
PRIVATE	void	initializer_list_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- initializer_list_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_116][FIRST_SET][token]) 
	{		
		initializer();
		initializer_list_1();
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_116][FOLLOW_SET][token])
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

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_54][FIRST_SET][token])
	{
		uget_tok(1);		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts	= compound_statement();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_58][FIRST_SET][token])
	{
		uget_tok(1);		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts	= selection_statement();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_59][FIRST_SET][token])
	{
		uget_tok(1);		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts	= iteration_statement();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_60][FIRST_SET][token])
	{
		uget_tok(1);		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts	= jump_statement();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if((parse_production_tab[PRODUCTION_53][FIRST_SET][token]) && (parse_production_tab[PRODUCTION_57][FIRST_SET][token]))
	{
		get_tok();

		if(token == OP_COLON)
		{
			uget_tok(2);			
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ret_sts	= labeled_statement();
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}
		else
		{
			uget_tok(2);			
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ret_sts	= expression_statement();
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}
	}
	else if(parse_production_tab[PRODUCTION_53][FIRST_SET][token])
	{
		uget_tok(1);		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts	= labeled_statement();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else if(parse_production_tab[PRODUCTION_57][FIRST_SET][token])
	{
		uget_tok(1);		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_sts	= expression_statement();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_52][IDEN_LEN],token);
		exit(1);
	}	

	return ret_sts;
}

//===========================================================================
// labeled_statement()
//===========================================================================
PRIVATE	struct ir_sts *	labeled_statement()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- labeled_statement  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(!parse_production_tab[PRODUCTION_53][FIRST_SET][token]) 
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_53][IDEN_LEN],token);
		exit(1);
	}

	switch(token)
	{
		case IDENTIFIER:
		case DEFAULT:
			get_tok();
			if(token != OP_COLON)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_53][IDEN_LEN],token);
				exit(1);
			}			
			
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ret_sts	= statement();
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			break;

		case CASE:			
			constant_expression();

			get_tok();
			if(token != OP_COLON)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_53][IDEN_LEN],token);
				exit(1);
			}
			
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ret_sts	= statement();
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			break;

		default:
			break;
	}

	return ret_sts;
}

//===========================================================================
// compound_statement()
//===========================================================================
PRIVATE	struct ir_sts *	compound_statement()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- compound_statement  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(!parse_production_tab[PRODUCTION_54][FIRST_SET][token]) 
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_54][IDEN_LEN],token);
		exit(1);
	}
	
	compound_statement_1();
	compound_statement_2();

	get_tok();

	if(token != OP_R_BRACE) 
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_54][IDEN_LEN],token);
		exit(1);
	}

	return ret_sts;
}

//===========================================================================
// compound_statement_1()
//===========================================================================
PRIVATE	void	compound_statement_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- compound_statement_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_117][FIRST_SET][token]) 
	{
		uget_tok(1);
		declaration_list();
	}
	else if(parse_production_tab[PRODUCTION_117][FOLLOW_SET][token])
	{
		uget_tok(1);
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_117][IDEN_LEN],token);
		exit(1);
	} 
}

//===========================================================================
// compound_statement_2()
//===========================================================================
PRIVATE	void	compound_statement_2()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- compound_statement_2  -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_118][FIRST_SET][token]) 
	{
		uget_tok(1);
		statement_list();
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_118][FOLLOW_SET][token])
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
// declaration_list()
//===========================================================================
PRIVATE	void	declaration_list()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- declaration_list  -- \n");
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

	if(parse_production_tab[PRODUCTION_119][FIRST_SET][token]) 
	{
		uget_tok(1);
		declaration();
		declaration_list_1();
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_119][FOLLOW_SET][token])
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
	
	struct symbol *s1	= symtbl_search_i(function_id);

	if(s1)
	{
		//add function label
		struct ir_exp *	irexp_t		= ir_label_exp_build(s1->label, label_id);
		struct ir_explist *irexplist_t 	= explist_build(irexp_t);
		struct ir_sts *sts_t 		= ir_labelsts_build(irexplist_t);
		struct ir_sts_list *stslist_t 	= stslist_build(sts_t);
		ir_add2stslist(stslist_t, cur_stslist);		
	}
	
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

	get_tok();

	if(parse_production_tab[PRODUCTION_120][FIRST_SET][token]) 
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

		if(!parse_production_tab[PRODUCTION_120][FOLLOW_SET][token])
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
// expression_statement()
//===========================================================================
PRIVATE	struct ir_sts *	expression_statement()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- expression_statement  -- \n\n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts *ret_sts	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(!parse_production_tab[PRODUCTION_57][FIRST_SET][token]) 
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_57][IDEN_LEN],token);
		exit(1);
	}

	if(token != SEMICOLON)
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		cur_explist	= explist_build(NULL);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		uget_tok(1);		

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		struct ir_exp* exp	= expression();
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		get_tok();

		if(token != SEMICOLON)
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_57][IDEN_LEN],token);
			exit(1);
		}
		else
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			struct ir_sts *sts 		= ir_expsts_build(cur_explist);
			
			if((!flg_select) && (!flg_iteration))
			{
				struct ir_sts_list *stslist 	= stslist_build(sts);
				ir_add2stslist(stslist, cur_stslist);			
			}	
			
			ret_sts	= sts;
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		}
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
		flg_val_array	= FALSE;
		flg_val_func	= FALSE;
		flg_val_pointer	= FALSE;
		flg_val_struct_union	= FALSE;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}

	return ret_sts;
}

//===========================================================================
// selection_statement()
//===========================================================================
PRIVATE	struct ir_sts *	selection_statement()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- selection_statement  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	struct ir_sts * ret_sts	= NULL;
		
	struct ir_exp * ret_exp	= NULL;
	struct ir_sts * then_sts= NULL;
	struct ir_sts * else_sts= NULL;	

	flg_select		= TRUE;

	struct ir_sts *sts 	= ir_selectsts_build(NULL, NULL, NULL);

	cur_explist		= explist_build(NULL);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	selection_statement_1(sts, ret_exp, then_sts);
	selection_statement_2(sts, else_sts);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts_list *stslist 	= stslist_build(sts);
	ir_add2stslist(stslist, cur_stslist);	

	flg_select		= FALSE;

	ret_sts = sts;
	return ret_sts;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

//===========================================================================
// selection_statement_1()
//===========================================================================
PRIVATE	struct ir_sts *	selection_statement_1(struct ir_sts * sts, struct ir_exp *ret_exp, struct ir_sts * then_sts)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- selection_statement_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_121][FIRST_SET][token]) 
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_121][IDEN_LEN],token);
		exit(1);
	}

	get_tok();
	if(token != OP_L_PARENTHESE)
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_121][IDEN_LEN],token);
		exit(1);
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	ret_exp		= expression();

	ir_selectsts_update_1(sts, cur_explist);	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();
	if(token != OP_R_PARENTHESE)
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_121][IDEN_LEN],token);
		exit(1);
	}	
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	then_sts	= statement();	

	ir_selectsts_update_2(sts, then_sts);

	return then_sts;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

//===========================================================================
// selection_statement_2()
//===========================================================================
PRIVATE	struct ir_sts *	selection_statement_2(struct ir_sts * sts, struct ir_sts * else_sts)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- selection_statement_2  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_122][FIRST_SET][token]) 
	{
		if(!parse_production_tab[PRODUCTION_122][FOLLOW_SET][token])
		{
			uget_tok(1);
			return;
		}
		else
		{
			//
		}
	}
	else
	{		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
		else_sts	= statement();

		ir_selectsts_update_3(sts, else_sts);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}

	return else_sts;
}

//===========================================================================
// iteration_statement()
//===========================================================================
PRIVATE	struct ir_sts *	iteration_statement()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- iteration_statement  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_sts * ret_sts	= NULL;
	struct ir_exp * ret_exp	= NULL;
	struct ir_sts * sts	= NULL;	
	struct ir_sts * init_sts= NULL;
	struct ir_sts * cond_sts= NULL;
	flg_iteration		= TRUE;

	cur_explist		= explist_build(NULL);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	get_tok();

	switch(token)
	{
		case WHILE:
			get_tok();
			if(token != OP_L_PARENTHESE)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_59][IDEN_LEN],token);
				exit(1);
			}
			
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			ret_sts	= ir_iteration_while_sts_build(NULL, NULL);
			
			ret_exp	= expression();

			ir_iteration_while_sts_update_1(ret_sts, cur_explist);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			get_tok();
			if(token != OP_R_PARENTHESE)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_59][IDEN_LEN],token);
				exit(1);
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
			sts	= statement();
			ir_iteration_while_sts_update_2(ret_sts, sts);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			break;

		case DO:
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
			ret_sts	= ir_iteration_dowhile_sts_build(NULL, NULL);
			
			sts	= statement();
			ir_iteration_dowhile_sts_update_2(ret_sts, sts);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			get_tok();
			if(token != WHILE)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_59][IDEN_LEN],token);
				exit(1);
			}

			get_tok();
			if(token != OP_L_PARENTHESE)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_59][IDEN_LEN],token);
				exit(1);
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
			cur_explist		= explist_build(NULL);
					
			ret_exp	= expression();
			ir_iteration_dowhile_sts_update_1(ret_sts, cur_explist);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			get_tok();
			if(token != OP_R_PARENTHESE)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_59][IDEN_LEN],token);
				exit(1);
			}

			get_tok();
			if(token != SEMICOLON)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_59][IDEN_LEN],token);
				exit(1);
			}

			break;

		case FOR:
			get_tok();
			if(token != OP_L_PARENTHESE)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_59][IDEN_LEN],token);
				exit(1);
			}			

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
			ret_sts			= ir_iteration_for_sts_build(NULL, NULL, NULL, NULL);			

			init_sts = expression_statement();
			ir_iteration_for_sts_update_1(ret_sts, init_sts);
				
			cond_sts = expression_statement();
			ir_iteration_for_sts_update_2(ret_sts, cond_sts);

			iteration_statement_1(ret_sts, sts, ret_exp);

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			break;
		default:
			break;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	struct ir_sts_list *stslist 	= stslist_build(ret_sts);
	ir_add2stslist(stslist, cur_stslist);	

	flg_iteration		= FALSE;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	return ret_sts;
}

//===========================================================================
// iteration_statement_1()
//===========================================================================
PRIVATE	void	iteration_statement_1(struct ir_sts * ret_sts, struct ir_sts * sts, struct ir_exp *ret_exp)
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- iteration_statement_1  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_123][FIRST_SET][token]) 
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_123][IDEN_LEN],token);
		exit(1);
	}

	if(token == OP_R_PARENTHESE)
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
		sts	= statement();
		
		ir_iteration_for_sts_update_3(ret_sts, NULL);
		ir_iteration_for_sts_update_4(ret_sts, sts);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	else
	{
		uget_tok(1);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		cur_explist		= explist_build(NULL);
		
		ret_exp	= expression();
		
		ir_iteration_for_sts_update_3(ret_sts, cur_explist);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		get_tok();
		if(token != OP_R_PARENTHESE)
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_123][IDEN_LEN],token);
			exit(1);
		}
		
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
		sts	= statement();
		
		ir_iteration_for_sts_update_4(ret_sts, sts);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
}


//===========================================================================
// jump_statement()
//===========================================================================
PRIVATE	struct ir_sts *	jump_statement()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- jump_statement  -- \n");
#endif
//--------------------------

	get_tok();

	if(!parse_production_tab[PRODUCTION_60][FIRST_SET][token]) 
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_60][IDEN_LEN],token);
		exit(1);
	}

	switch(token)
	{
		case GOTO:
			get_tok();
			if(token != IDENTIFIER)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_60][IDEN_LEN],token);
				exit(1);
			}

			get_tok();
			if(token != SEMICOLON)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_60][IDEN_LEN],token);
				exit(1);
			}

			break;

		case CONTINUE:
			get_tok();
			if(token != SEMICOLON)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_60][IDEN_LEN],token);
				exit(1);
			}

			break;

		case BREAK:
			get_tok();
			if(token != SEMICOLON)
			{
				printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_60][IDEN_LEN],token);
				exit(1);
			}

			break;

		case RETURN:			
			jump_statement_1();
			break;

		default:
			break;
	}
}

//===========================================================================
// jump_statement_1()
//===========================================================================
PRIVATE	void	jump_statement_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- jump_statement_1  -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct ir_exp * ret_exp	= NULL;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(!parse_production_tab[PRODUCTION_124][FIRST_SET][token]) 
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_124][IDEN_LEN],token);
		exit(1);
	}

	if(token != SEMICOLON)
	{
		uget_tok(1);		

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_exp	= expression();

		struct ir_explist * explist_t = explist_build(ret_exp);
		ir_add2explist(explist_t, cur_explist);		
		
		struct ir_sts *sts 		= ir_jumpsts_return_build(cur_explist);
		
		if((!flg_select) && (!flg_iteration))
		{
			struct ir_sts_list *stslist 	= stslist_build(sts);
			ir_add2stslist(stslist, cur_stslist);
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		get_tok();

		if(token != SEMICOLON)
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_124][IDEN_LEN],token);
			exit(1);
		}
	}
	else
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		ret_exp	= ir_null_exp_build(NULL, NULL, NULL);
		
		struct ir_explist * explist_t = explist_build(ret_exp);
		ir_add2explist(explist_t, cur_explist);		
		
		struct ir_sts *sts 		= ir_jumpsts_return_build(cur_explist);
		struct ir_sts_list *stslist 	= stslist_build(sts);
		ir_add2stslist(stslist, cur_stslist);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

	if(parse_production_tab[PRODUCTION_125][FIRST_SET][token]) 
	{
		uget_tok(1);
		external_declaration();
		translate_unit_1();		
	}
	else
	{
		if(!parse_production_tab[PRODUCTION_125][FOLLOW_SET][token])
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

	s32 temp_function_id = 0;

	get_tok();

	if(token == TYPEDEF)
	{
		uget_tok(1);
		declaration();
	}
	else if(token == EXTERN)
	{
		uget_tok(1);
		declaration();
	}
	else if(token == IDENTIFIER)					//type define by typedef before
	{
		if(check_type_i(p_cur_token->val_s))
		{
			uget_tok(1);
			declaration();
		}
	}
	else
	{
		if((parse_production_tab[PRODUCTION_63][FIRST_SET][token]) && (parse_production_tab[PRODUCTION_22][FIRST_SET][token])) 
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if(parse_production_tab[PRODUCTION_26][FIRST_SET][token])	//TYPEDEF, EXTERN, STATIC, AUTO, REGISTER
			{
				sym_t.type_scs	= token;
			} 
			else
			{
				sym_t.type_ts	= token;				//function return type
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

			get_tok();

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if(parse_production_tab[PRODUCTION_27][FIRST_SET][token])	//void, int ,float
			{
				sym_t.type_ts	= token;				//function return type
			}
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			else if(token == SEMICOLON)
			{
				uget_tok(2);
				declaration();
			}
			else if(token == OP_L_BRACE)	//struct
			{
				uget_tok(2);
				declaration();
			}
			else
			{
				if((parse_production_tab[PRODUCTION_78][FIRST_SET][token])&& (parse_production_tab[PRODUCTION_127][FIRST_SET][token]))
				{
					//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
					if(token == IDENTIFIER)
					{
						struct symbol * p = symtbl_search(p_cur_token->val_s);						
						if(p)
						{
							temp_function_id = p->id;						
						}
					}				
					//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

					get_tok();

					if(token == SEMICOLON)
					{
						uget_tok(3);
						declaration();
					}
					else if(token == OP_L_BRACE)	//struct
					{
						uget_tok(3);
						declaration();
					}
					else
					{		
						uget_tok(2);
						init_declarator_list();

						get_tok();
						if(token != SEMICOLON)
						{
							//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
							sym_t.flg_func	= FALSE;						
							//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

							if(parse_production_tab[PRODUCTION_128][FIRST_SET][token])
							{
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
								g_function_inside	= TRUE;

								function_id		= temp_function_id;
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

								uget_tok(1);
								declaration_list();
								compound_statement();

								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
								g_function_inside	= FALSE;
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
							}
							else if(parse_production_tab[PRODUCTION_128][FOLLOW_SET][token])
							{
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
								g_function_inside	= TRUE;

								function_id		= temp_function_id;
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

								uget_tok(1);
								compound_statement();

								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
								g_function_inside	= FALSE;
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
							}
				
						}
						else
						{
							//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
							sym_t.len	= check_type_l(sym_t.type_ts);

							symbol_pre_set(&sym_t);							

							if(sym_t.flg_func)
							{
								fun_build(&sym_t);
							}
							else
							{
								var_build(&sym_t);
							}

							symtbl_add_s(&sym_t);
							symbol_empty(&sym_t);
							//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
						}
					}
				} 
				else
				{
					printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_62][IDEN_LEN],token);
					exit(1);
				}
			}
		}
		else if(parse_production_tab[PRODUCTION_63][FIRST_SET][token])
		{
			uget_tok(1);
			function_definition();
		}
		else if(parse_production_tab[PRODUCTION_22][FIRST_SET][token])
		{
			uget_tok(1);
			declaration();
		}
		else
		{
			printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_62][IDEN_LEN],token);
			exit(1);
		}
	}
}

//===========================================================================
// function_definition()
//===========================================================================
PRIVATE	void	function_definition()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- function_definition -- \n");
#endif
//--------------------------

	function_definition_1();
	function_definition_2();
	function_definition_3();
	function_definition_4();
}

//===========================================================================
// function_definition_1()
//===========================================================================
PRIVATE	void	function_definition_1()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- function_definition_1 -- \n");
#endif
//--------------------------

	get_tok();

	if(parse_production_tab[PRODUCTION_126][FIRST_SET][token]) 
	{
		uget_tok(1);
		declaration_specifiers();
	}
	else if(parse_production_tab[PRODUCTION_126][FOLLOW_SET][token])
	{
		uget_tok(1);
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_126][IDEN_LEN],token);
		exit(1);
	}
}

//===========================================================================
// function_definition_2()
//===========================================================================
PRIVATE	void	function_definition_2()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- function_definition_2 -- \n");
#endif
//--------------------------

	declarator();
}

//===========================================================================
// function_definition_3()
//===========================================================================
PRIVATE	void	function_definition_3()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- function_definition_3 -- \n");
#endif
//--------------------------

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	g_function_inside	= TRUE;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	get_tok();

	if(parse_production_tab[PRODUCTION_128][FIRST_SET][token]) 
	{
		uget_tok(1);
		declaration_list();
	}
	else if(parse_production_tab[PRODUCTION_128][FOLLOW_SET][token])
	{
		uget_tok(1);
	}
	else
	{
		printf("error:%s,token:%d\n",production_tab_info[PRODUCTION_128][IDEN_LEN],token);
		exit(1);
	}
}

//===========================================================================
// function_definition_4()
//===========================================================================
PRIVATE	void	function_definition_4()
{
//--------------------------
//test
#ifdef	PARSE_DEBUG
	printf("	-- function_definition_4 -- \n");
#endif
//--------------------------	

	compound_statement();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	g_function_inside	= FALSE;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
