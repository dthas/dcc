//===========================================================================
// ir_lib.c
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
#include	"dcc_prototype.h"

#define	IR_DEBUG

PRIVATE	s8 word_info[IR_WORD_NUM][IR_WORD_LEN] = {
					"AUTO","BREAK","CASE","CHAR","CONST","CONTINUE","DEFAULT","DO","DOUBLE","ELSE",
					"ENUM","EXTERN","FLOAT","FOR","GOTO","IF","INT","LONG",	"REGISTER","RETURN",
					"SHORT","SIGNED","SIZEOF","STATIC","STRUCT","SWITCH","TYPEDEF","UNION",	"UNSIGNED","VOID",
					"VOLATILE","WHILE","IDENTIFIER","SPACE","COMMENT_S","COMMENT_M_BEGIN","COMMENT_M_END","SEMICOLON","CONST_DEC","TYPE_NAME",
					"ELLIPSIS","","CONST_S_INT_8","CONST_S_INT_16","CONST_S_INT_32","CONST_S_INT_64","CONST_S_INT_128","CONST_U_INT_8","CONST_U_INT_16","CONST_U_INT_32",
					"CONST_U_INT_64","CONST_U_INT_128","","","","CONST_NL","CONST_HT","CONST_VT","CONST_BS","CONST_CR",
					"CONST_FF","CONST_BEL","CONST_BACKSLASH","CONST_QMARK","CONST_S_QUOTE","CONST_D_QUOTE","CONST_OCT","CONST_HEX","","CONST_STRING",
					"CONST_FLOAT","CONST_DOUBLE","CONST_S_SCIENCE","CONST_U_SCIENCE","","","","","","",
					"+","-","*","/","%","&","!","~","|","^",
					"++","--","&&","||","==","<=",">=","!=","+=","-=",
					"*=","/=","%=","<<",">>","<<=",">>=","&=","|=","^=",
					"=","?","<",">",",",".","->",":","paramlist","",
					"(",")","[","]","{","}","struct","array"
				};

PRIVATE	s8 sts_kind_info[2][IR_WORD_LEN] = {"IR_JUMP","IR_EXP"};

PRIVATE	s8 exp_kind_info[8][IR_WORD_LEN] = {"IR_ABOP", "IR_CALL", "IR_VARADDR", "IR_ASSIGN", "IR_COND", "IR_RELATE", "IR_POSTFIX", "UNARY"};


//===========================================================================
// ir_explist_print(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	print_ir()
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("-- print_ir -- (cur_file=0x%x)\n",cur_file);
#endif
//--------------------------

	ir_file_print(cur_file);
}

//===========================================================================
// ir_explist_print(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ir_file_print(struct ir_file *f)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("-- ir_file_print -- \n");
#endif
//--------------------------

	for(; f; f=f->tail)
	{
		ir_stslist_print(f->stslist);
	}
}

//===========================================================================
// ir_explist_print(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ir_stslist_print(struct ir_stslist *stslist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("-- ir_stslist_print -- \n");
#endif
//--------------------------

	for(; stslist; stslist=stslist->tail)
	{
		ir_sts_print(stslist->sts);
	}
}

//===========================================================================
// ir_explist_print(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ir_sts_print(struct ir_sts *sts)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("%5s %10s (sts=0x%10x) \n","","-- ir_sts_print --",sts);
#endif
//--------------------------

	if(sts)
	{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("%5s %10s (sts_kind=%10s) \n","","----",sts_kind_info[sts->k]);
#endif
//--------------------------

		switch(sts->k)
		{
			case IR_LABELS:
				ir_labellist_print(sts->s.label_sts.explist);
				break;
			case IR_EXP:
				ir_explist_print(sts->s.exp_sts.explist);
				break;
			case IR_JUMP_RETURN:
				ir_jumplist_print(sts->s.jump_sts.explist);
				break;
			case IR_SELECT:
				ir_select_print(sts->s.select_sts.explist, sts->s.select_sts.then_sts, sts->s.select_sts.else_sts);
				break;
			case IR_ITERATION_FOR:
				ir_iteration_for_print(sts);
				break;
			case IR_ITERATION_WHILE:
				ir_iteration_while_print(sts);
				break;
			case IR_ITERATION_DOWHILE:
				ir_iteration_dowhile_print(sts);
				break;
			default:
				break;
		}
	}
}

//===========================================================================
// ir_explist_print(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ir_explist_print(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("%15s %10s (explist=0x%x) \n","","-- ir_explist_print --",explist);
#endif
//--------------------------


	for(; explist; explist=explist->tail)
	{
		ir_exp_print(explist->exp);
	}
}

//===========================================================================
// ir_explist_print(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ir_labellist_print(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("%15s %10s (explist=0x%x) \n","","-- ir_labellist_print --",explist);
#endif
//--------------------------


	for(; explist; explist=explist->tail)
	{
		ir_exp_print(explist->exp);
	}
}

//===========================================================================
// ir_explist_print(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ir_jumplist_print(struct ir_explist *explist)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("%15s %10s (explist=0x%x) \n","","-- ir_jumplist_print --",explist);
#endif
//--------------------------


	for(; explist; explist=explist->tail)
	{
		ir_exp_print(explist->exp);
	}
}


//===========================================================================
// ir_explist_print(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ir_select_print(struct ir_explist *explist, struct ir_sts *then_sts, struct ir_sts *else_sts)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("%15s %10s (explist=0x%x) \n","","-- ir_explist_print --",explist);
#endif
//--------------------------

	//if exp
	for(; explist; explist=explist->tail)
	{
		ir_exp_print(explist->exp);
	}

	//then sts
	ir_sts_print(then_sts);

	//else sts
	ir_sts_print(else_sts);
}

//===========================================================================
// ir_explist_print(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ir_iteration_for_print(struct ir_sts *sts)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("%15s %10s (sts=0x%x) \n","","-- ir_iteration_for_print(s) --",sts);
#endif
//--------------------------

	//init sts
	ir_sts_print(sts->s.for_sts.init_sts);

	//cond sts
	ir_sts_print(sts->s.for_sts.cond_sts);

	//next explist
	struct ir_explist *explist = sts->s.for_sts.next_explist;
	for(; explist; explist=explist->tail)
	{
		ir_exp_print(explist->exp);
	}

	//sts
	ir_sts_print(sts->s.for_sts.sts);

//--------------------------
//test
#ifdef	IR_DEBUG
	printf("%15s %10s \n","","-- ir_iteration_for_print(e) --");
#endif
//--------------------------
}

//===========================================================================
// ir_iteration_while_print(struct ir_sts *sts)
//===========================================================================
PUBLIC	void	ir_iteration_while_print(struct ir_sts *sts)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("%15s %10s (sts=0x%x) \n","","-- ir_iteration_while_print(s) --",sts);
#endif
//--------------------------

	//cond explist
	struct ir_explist *explist = sts->s.while_sts.cond_explist;
	for(; explist; explist=explist->tail)
	{
		ir_exp_print(explist->exp);
	}

	//sts
	ir_sts_print(sts->s.while_sts.sts);

//--------------------------
//test
#ifdef	IR_DEBUG
	printf("%15s %10s \n","","-- ir_iteration_while_print(e) --");
#endif
//--------------------------
}

//===========================================================================
// ir_iteration_dowhile_print(struct ir_sts *sts)
//===========================================================================
PUBLIC	void	ir_iteration_dowhile_print(struct ir_sts *sts)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("%15s %10s (sts=0x%x) \n","","-- ir_iteration_dowhile_print(s) --",sts);
#endif
//--------------------------

	//sts
	ir_sts_print(sts->s.dowhile_sts.sts);

	//cond explist
	struct ir_explist *explist = sts->s.dowhile_sts.cond_explist;
	for(; explist; explist=explist->tail)
	{
		ir_exp_print(explist->exp);
	}
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("%15s %10s \n","","-- ir_iteration_dowhile_print(e) --");
#endif
//--------------------------
}

//===========================================================================
// ir_explist_print(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ir_exp_print(struct ir_exp *exp)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("%20s %10s \n\n","","-- ir_exp_print --");
#endif
//--------------------------

	struct ir_exp *t;

	if(exp)
	{
		switch(exp->k)
		{
			case IR_ABOP:
				for(; exp->e.abop.left; exp=exp->e.abop.right)
				{					
					ir_exp_print(exp->e.abop.left);

					printf("%s\n", &word_info[exp->e.abop.op][0]);

					ir_exp_print(exp->e.abop.right);
				}
				printf("\n");

				break;

			case IR_UNARY:
				printf("%s\n", &word_info[exp->e.unary.op][0]);

				ir_exp_print(exp->e.unary.left);
				ir_exp_print(exp->e.unary.right);				

				printf("\n");

				break;

			case IR_CALL:
				printf("(func) %s, paramlist=%x\n", exp->e.call.label_name, exp->e.call.ppv);
				
				struct ir_explist *plist = exp->e.call.ppv;
				for(; plist; plist=plist->tail)
				{
					if(plist->exp)
					{
						ir_exp_print(plist->exp);
					}
				}

				break;

			case IR_VARADDR:
				ir_var_print(exp);
				break;

			case IR_ASSIGN:					
				for(; exp; exp=exp->e.assign.val)
				{					
					ir_exp_print(exp->e.assign.res);

					printf(" %s (%d)", &word_info[exp->e.assign.op][0], exp->e.assign.op);
				}
				break;

			case IR_COND:
				printf("condition:");
				ir_var_print(exp->e.cond.cond);
	
				printf(" ? ");
			
				for(; exp->e.cond.op_1; exp=exp->e.cond.op_2)
				{
					ir_var_print(exp->e.cond.op_1);
					printf(" : ");
				}
				printf("\n");

				break;

			case IR_RELATE:				
				for(; exp->e.relate.left; exp=exp->e.relate.right)
				{
					ir_exp_print(exp->e.relate.left);

					printf("%s\n", &word_info[exp->e.relate.op][0]);

					ir_exp_print(exp->e.relate.right);
				}
				printf("\n");

				break;

			case IR_LABEL:
			
				printf("label_name: %s,  label_id: %d ", exp->e.label.label_name, exp->e.label.label_id);

				printf("\n");

				break;

			case IR_POSTFIX:
			
				switch(exp->e.postfix.op)
				{
					case IR_STRUCT:
						ir_var_print(exp->e.postfix.left);		//struct name					
						break;

					case IR_POINTER:
						ir_var_print(exp->e.postfix.left);
						printf("->");
						break;

					case IR_ARRAY:
						ir_var_print(exp->e.postfix.left);
						printf("[");
						ir_exp_print(exp->e.postfix.right);
						printf("]\n");
						break;					
					case IR_INC:
						ir_var_print(exp->e.postfix.left);
						printf("++");
						break;

					case IR_DEC:
						ir_var_print(exp->e.postfix.left);
						printf("--");
						break;

					default:
						break;
				}

				printf("\n");

				break;

			default:
				break;
		}
	}
}


//===========================================================================
// ir_var_print(struct ir_exp* exp)
//===========================================================================
PUBLIC	void	ir_var_print(struct ir_exp* exp)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("%30s ----ir_var_print(s) ,kind=%d, var_type=%d\n","", exp->k,exp->e.var.var_type);	
#endif
//--------------------------

	s32 var_type	= exp->e.var.var_type;
	u32 var_len	= exp->e.var.var_len;

	if(var_type > 100)
	{
		var_type	= STRUCT;
	}

	switch(var_type)
	{
		case INT:
			printf("%35s (name=%s)%d [name_addr=%x, var_addr=%x]","", (s8*)(exp->e.var.name), *(s32*)(exp->e.var.var_addr),
				(exp->e.var.name), (exp->e.var.var_addr));
			break;
		case CHAR:
			printf("%35s (char)%s [name_addr=%x, var_addr=%x]","", (s8*)(exp->e.var.name), (s8*)(exp->e.var.var_addr),
				(exp->e.var.name), (exp->e.var.var_addr));		
			break;
		case STRUCT:
			printf("%35s (struct)%s [name_addr=%x]", "", (s8*)(exp->e.var.name), (exp->e.var.name));			
			break;
		default:
			break;
	}
}


//===========================================================================
// ir_pvlist_print(struct ir_pvlist *pvlist)
//===========================================================================
PUBLIC	void	ir_pvlist_print(struct ir_pvlist *pvlist)
{
	printf("	parmlist:(");

	for(; pvlist; pvlist=pvlist->tail)
	{
		ir_var_print(pvlist->exp);
		printf(",");
	}

	printf(")\n");
}

