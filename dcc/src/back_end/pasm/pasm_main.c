//===========================================================================
// pasm_main.c
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
#include	"dcc_label.h"
#include	"dcc_frame.h"
#include	"dcc_ir.h"
#include	"dcc_pasm.h"
#include	"dcc_prototype.h"

#define	PASM_DEBUG

PRIVATE	s8 exp_kind_info[8][IR_WORD_LEN] = {"IR_ABOP", "IR_CALL", "IR_VARADDR", "IR_ASSIGN", "IR_COND", "IR_RELATE", "IR_POSTFIX", "UNARY"};

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

s8 *pname	=NULL;
u32 val_addr	=0;
u32 val_len	=0;
s32 val_id	=-1;

s8 flg_abop	= FALSE;
s8 flg_call	= FALSE;
s8 flg_relate	= FALSE;
s8 flg_unary	= FALSE;

s8 flg_select	= FALSE;

struct pasm_exp pe_t;
//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pasm_main()
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- pasm_main -- (cur_file=0x%x)\n",cur_file);
#endif
//--------------------------

	pcur_file	= pasm_file_build(NULL);

	pasm_file_process(cur_file, pcur_file);
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pasm_file_process(struct ir_file *f, struct pasm_file *pf)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- pasm_file_process -- \n");
#endif
//--------------------------

	for(; f; f=f->tail)
	{
		struct pasm_stslist *plist 	= pasm_stslist_build(NULL);

		pasm_stslist_process(f->stslist, plist);

		struct pasm_file *pfile	= file_build(plist);
		pasm_add2file(pfile, pf);
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pasm_stslist_process(struct ir_stslist *stslist, struct pasm_stslist *pstslist)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("-- pasm_stslist_process -- \n");
#endif
//--------------------------

	for(; stslist; stslist=stslist->tail)
	{
		if(stslist->sts)
		{
			struct pasm_sts *psts = pasm_sts_process(stslist->sts);

			if(psts)
			{
				struct pasm_stslist *plist 	= pasm_stslist_build(psts);
				pasm_add2stslist(plist, pstslist);			
			}
		}
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	struct pasm_sts *	pasm_sts_process(struct ir_sts *sts)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%5s %10s \n","","-- pasm_sts_process --");
#endif
//--------------------------

	if(sts)
	{
		struct pasm_explist * plist = pexplist_build(NULL);
		u32 label;
		struct pasm_sts *psts 	= NULL;
		
		switch(sts->k)
		{
			case IR_LABELS:
				if(sts->s.exp_sts.explist)
				{
					pasm_explist_process(sts->s.exp_sts.explist, plist);

					label	= PASM_LABEL_L;
					psts	= pasm_sts_build(label, plist);
				}
				break;
			case IR_JUMP_RETURN:
				if(sts->s.exp_sts.explist)
				{
					pasm_explist_process(sts->s.exp_sts.explist, plist);

					label	= PASM_JUMP_RETURN;
					psts	= pasm_sts_build(label, plist);
				}
				break;
			case IR_EXP:
				if(sts->s.exp_sts.explist)
				{
					pasm_explist_process(sts->s.exp_sts.explist, plist);

					label	= PASM_EXP;
					psts	= pasm_sts_build(label, plist);
				}
				
				break;

			case IR_SELECT:
				if(sts->s.select_sts.explist)
				{
					psts		= pasm_select_process(sts);							
				}
				
				break;
			case IR_ITERATION_FOR:
				psts		= pasm_iteration_for_process(sts);
								
				break;
			case IR_ITERATION_WHILE:
				psts		= pasm_iteration_while_process(sts);
								
				break;
			case IR_ITERATION_DOWHILE:
				psts		= pasm_iteration_dowhile_process(sts);
								
				break;

			default:
				break;
		}
		return psts;
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	struct pasm_sts *	pasm_select_process(struct ir_sts *sts)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%15s %10s\n","","-- pasm_select_process --");
#endif
//--------------------------

	struct pasm_exp *p = NULL;
	struct pasm_sts *psts 	= NULL;
	u32 label;
	s8 *tl, *fl, *el;

	label	= PASM_SELECT;
	psts	= pasm_sts_build(label, NULL);

	struct pasm_explist * pexplist = pexplist_build(NULL);
	
	if(psts)
	{
		if(sts->s.select_sts.explist)
		{
			//if exp
			pasm_explist_process(sts->s.select_sts.explist, pexplist);
			psts->s.select_sts.pexplist	= pexplist;			
		}

		//then sts
		if(sts->s.select_sts.then_sts)
		{	
			psts->s.select_sts.then_sts = pasm_sts_process(sts->s.select_sts.then_sts);			
		}	

		//else sts
		if(sts->s.select_sts.else_sts)
		{
			psts->s.select_sts.else_sts = pasm_sts_process(sts->s.select_sts.else_sts);			
		}
	}

	return psts;		
}

//===========================================================================
// pasm_iteration_for_process
//===========================================================================
PUBLIC	struct pasm_sts *	pasm_iteration_for_process(struct ir_sts *sts)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%15s %10s\n","","-- pasm_iteration_for_process --");
#endif
//--------------------------

	u32 label		= PASM_ITERATION_FOR;
	struct pasm_sts *psts	= pasm_sts_build(label, NULL);

	if(psts)
	{
		//init exp
		if(sts->s.for_sts.init_sts)
		{
			psts->s.for_sts.init_sts = pasm_sts_process(sts->s.for_sts.init_sts);			
		}

		//cond exp
		if(sts->s.for_sts.cond_sts)
		{
			psts->s.for_sts.cond_sts = pasm_sts_process(sts->s.for_sts.cond_sts);			
		}

		//next exp
		if(sts->s.for_sts.next_explist)
		{
			struct pasm_explist * next_pexplist = pexplist_build(NULL);

			pasm_explist_process(sts->s.for_sts.next_explist, next_pexplist);
			psts->s.for_sts.next_pexplist	= next_pexplist;			
		}

		// sts
		if(sts->s.for_sts.sts)
		{	
			psts->s.for_sts.sts = pasm_sts_process(sts->s.for_sts.sts);
		}	

		//loop label
		label_build(psts->s.for_sts.l_label);		
	}

	return psts;		
}


//===========================================================================
// pasm_iteration_while_process
//===========================================================================
PUBLIC	struct pasm_sts *	pasm_iteration_while_process(struct ir_sts *sts)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%15s %10s\n","","-- pasm_iteration_while_process --");
#endif
//--------------------------

	u32 label		= PASM_ITERATION_WHILE;
	struct pasm_sts *psts	= pasm_sts_build(label, NULL);

	if(psts)
	{
		//cond exp
		if(sts->s.while_sts.cond_explist)
		{
			struct pasm_explist * cond_pexplist = pexplist_build(NULL);

			pasm_explist_process(sts->s.while_sts.cond_explist, cond_pexplist);
			psts->s.while_sts.cond_pexplist	= cond_pexplist;			
		}

		// sts
		if(sts->s.while_sts.sts)
		{	
			psts->s.while_sts.sts = pasm_sts_process(sts->s.while_sts.sts);
		}	

		//loop label
		label_build(psts->s.while_sts.l_label);		
	}

	return psts;		
}

//===========================================================================
// pasm_iteration_dowhile_process
//===========================================================================
PUBLIC	struct pasm_sts *	pasm_iteration_dowhile_process(struct ir_sts *sts)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%15s %10s\n","","-- pasm_iteration_dowhile_process --");
#endif
//--------------------------

	u32 label		= PASM_ITERATION_DOWHILE;
	struct pasm_sts *psts	= pasm_sts_build(label, NULL);

	if(psts)
	{
		// sts
		if(sts->s.dowhile_sts.sts)
		{	
			psts->s.dowhile_sts.sts = pasm_sts_process(sts->s.dowhile_sts.sts);
		}

		//cond exp
		if(sts->s.dowhile_sts.cond_explist)
		{
			struct pasm_explist * cond_pexplist = pexplist_build(NULL);

			pasm_explist_process(sts->s.dowhile_sts.cond_explist, cond_pexplist);
			psts->s.dowhile_sts.cond_pexplist	= cond_pexplist;			
		}			

		//loop label
		label_build(psts->s.dowhile_sts.l_label);		
	}

	return psts;		
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pasm_explist_process(struct ir_explist *explist, struct pasm_explist *pexplist)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%15s %10s\n","","-- pasm_explist_process --");
#endif
//--------------------------


	for(; explist; explist=explist->tail)
	{
		if(explist->exp)
		{
			pasm_exp_process(explist->exp, pexplist);
		}
	}
}


//===========================================================================
// pasm_exp_process
//===========================================================================
PUBLIC	struct pasm_exp *	pasm_exp_process(struct ir_exp *exp, struct pasm_explist *pexplist)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%20s %10s \n","","--pasm_exp_process --");
#endif
//--------------------------

	struct ir_exp *t;
	struct pasm_exp *res	= NULL;
	struct pasm_explist *p_pmlist	= NULL;
	struct ir_explist *ir_pmlist	= NULL;
	struct pasm_exp *p_pmexp	= NULL;
	struct ir_exp	*ir_pmexp	= NULL;
	struct ir_exp *p1;
	s32 num_t	= 0;
	s32 num		=0;
	u32 l_res_addr	=0;
	u32 l_res_id	=0;
	u32 l_res_len	=0;
	s8  l_res_pname[PASM_NAME_LEN];
	u32 op		=0;
	s32 i=0;
	s8  tmp_buf[PASM_NAME_LEN];
	s8  temp_buf[PASM_NAME_LEN];	
	
	struct pasm_exp *p = NULL;
	
	if(exp)
	{
		switch(exp->k)
		{
			case IR_NULL:
				return NULL;
				break;

			case IR_ABOP:
				flg_abop	= TRUE;

				for(; exp->e.abop.left; exp=exp->e.abop.right)
				{
					struct pasm_exp *left	= pasm_exp_process(exp->e.abop.left, pexplist);					

					pe_t.k		= exp->e.abop.op;

					switch(pe_t.k)
					{
						case IR_PLUS:								
							pe_t.e.add.src_reg	= val_addr;
							pe_t.e.add.src_id	= val_id;
							pe_t.e.add.src_len	= val_len;

							strcopy(pe_t.e.add.src_name, pname);
							pe_t.e.add.src_name[strlen(pe_t.e.add.src_name)]	= NULL;				
							break;
						case IR_MINUS:
							pe_t.e.minus.src_reg	= val_addr;
							pe_t.e.minus.src_id	= val_id;
							pe_t.e.minus.src_len	= val_len;
							
							strcopy(pe_t.e.minus.src_name, pname);
							pe_t.e.minus.src_name[strlen(pe_t.e.minus.src_name)]	= NULL;				
							break;
						case IR_MUL:
							pe_t.e.mul.src_reg		= val_addr;
							pe_t.e.mul.src_id	= val_id;
							pe_t.e.mul.src_len	= val_len;
							
							strcopy(pe_t.e.mul.src_name, pname);
							pe_t.e.mul.src_name[strlen(pe_t.e.mul.src_name)]	= NULL;				
							break;
						case IR_DIV:
							pe_t.e.div.src_reg		= val_addr;
							pe_t.e.div.src_id	= val_id;
							pe_t.e.div.src_len	= val_len;
							
							strcopy(pe_t.e.div.src_name, pname);
							pe_t.e.div.src_name[strlen(pe_t.e.div.src_name)]	= NULL;				
							break;
						case IR_MOD:
							pe_t.e.mod.src_reg		= val_addr;
							pe_t.e.mod.src_id	= val_id;
							pe_t.e.mod.src_len	= val_len;
							
							strcopy(pe_t.e.mod.src_name, pname);
							pe_t.e.mod.src_name[strlen(pe_t.e.mod.src_name)]	= NULL;				
							break;
						default:
							break;
					}					

					struct pasm_exp *right	= pasm_exp_process(exp->e.abop.right, pexplist);
	
					switch(pe_t.k)
					{
						case IR_PLUS:								
							pe_t.e.add.dst_reg		= val_addr;
							pe_t.e.add.dst_id	= val_id;
							pe_t.e.add.dst_len	= val_len;
							
							strcopy(pe_t.e.add.dst_name, pname);
							pe_t.e.add.dst_name[strlen(pe_t.e.add.dst_name)]	= NULL;				
							break;
						case IR_MINUS:
							pe_t.e.minus.dst_reg	= val_addr;
							pe_t.e.minus.dst_id	= val_id;
							pe_t.e.minus.dst_len	= val_len;
							
							strcopy(pe_t.e.minus.dst_name, pname);
							pe_t.e.minus.dst_name[strlen(pe_t.e.minus.dst_name)]	= NULL;				
							break;
						case IR_MUL:
							pe_t.e.mul.dst_reg		= val_addr;
							pe_t.e.mul.dst_id	= val_id;
							pe_t.e.mul.dst_len	= val_len;
							
							strcopy(pe_t.e.mul.dst_name, pname);
							pe_t.e.mul.dst_name[strlen(pe_t.e.mul.dst_name)]	= NULL;			
							break;
						case IR_DIV:
							pe_t.e.div.dst_reg		= val_addr;
							pe_t.e.div.dst_id	= val_id;
							pe_t.e.div.dst_len	= val_len;
							
							strcopy(pe_t.e.div.dst_name, pname);
							pe_t.e.div.dst_name[strlen(pe_t.e.div.dst_name)]	= NULL;				
							break;
						case IR_MOD:
							pe_t.e.mod.dst_reg		= val_addr;
							pe_t.e.mod.dst_id	= val_id;
							pe_t.e.mod.dst_len	= val_len;
							
							strcopy(pe_t.e.mod.dst_name, pname);
							pe_t.e.mod.dst_name[strlen(pe_t.e.mod.dst_name)]	= NULL;				
							break;
						default:
							break;
					}
		
					switch(pe_t.k)
					{
						case IR_PLUS:	
							if(pe_t.e.add.dst_len == 0)
							{
								p = add(pe_t.e.add.dst_reg, pe_t.e.add.dst_id, pe_t.e.add.dst_len, 
									pe_t.e.add.src_reg, pe_t.e.add.src_id, pe_t.e.add.src_len,
									pe_t.e.add.dst_name, pe_t.e.add.src_name);
							}
							else
							{							
								p = add(pe_t.e.add.src_reg, pe_t.e.add.src_id, pe_t.e.add.src_len, 
									pe_t.e.add.dst_reg, pe_t.e.add.dst_id, pe_t.e.add.dst_len,
									pe_t.e.add.src_name, pe_t.e.add.dst_name);
							}
							break;
						case IR_MINUS:
							if(pe_t.e.minus.dst_len == 0)
							{
								p = minus(pe_t.e.minus.dst_reg, pe_t.e.minus.dst_id, pe_t.e.minus.dst_len, 
									pe_t.e.minus.src_reg, pe_t.e.minus.src_id, pe_t.e.minus.src_len,
									pe_t.e.minus.dst_name, pe_t.e.minus.src_name);
							}
							else
							{							
								p = minus(pe_t.e.minus.src_reg, pe_t.e.minus.src_id, pe_t.e.minus.src_len, 
									pe_t.e.minus.dst_reg, pe_t.e.minus.dst_id, pe_t.e.minus.dst_len,
									pe_t.e.minus.src_name, pe_t.e.minus.dst_name);
							}
							break;
						case IR_MUL:
							if(pe_t.e.mul.dst_len == 0)
							{
								p = mul(pe_t.e.mul.dst_reg, pe_t.e.mul.dst_id, pe_t.e.mul.dst_len, 
									pe_t.e.mul.src_reg, pe_t.e.mul.src_id, pe_t.e.mul.src_len,
									pe_t.e.mul.dst_name, pe_t.e.mul.src_name);
							}
							else
							{							
								p = mul(pe_t.e.mul.src_reg, pe_t.e.mul.src_id, pe_t.e.mul.src_len, 
									pe_t.e.mul.dst_reg, pe_t.e.mul.dst_id, pe_t.e.mul.dst_len,
									pe_t.e.mul.src_name, pe_t.e.mul.dst_name);
							}
							break;
						case IR_DIV:
							if(pe_t.e.div.dst_len == 0)
							{
								p = div(pe_t.e.div.dst_reg, pe_t.e.div.dst_id, pe_t.e.div.dst_len, 
									pe_t.e.div.src_reg, pe_t.e.div.src_id, pe_t.e.div.src_len,
									pe_t.e.div.dst_name, pe_t.e.div.src_name);
							}
							else
							{							
								p = div(pe_t.e.div.src_reg, pe_t.e.div.src_id, pe_t.e.div.src_len, 
									pe_t.e.div.dst_reg, pe_t.e.div.dst_id, pe_t.e.div.dst_len,
									pe_t.e.div.src_name, pe_t.e.div.dst_name);
							}
							break;
						case IR_MOD:
							if(pe_t.e.mod.dst_len == 0)
							{
								p = mod(pe_t.e.mod.dst_reg, pe_t.e.mod.dst_id, pe_t.e.mod.dst_len, 
									pe_t.e.mod.src_reg, pe_t.e.mod.src_id, pe_t.e.mod.src_len,
									pe_t.e.mod.dst_name, pe_t.e.mod.src_name);
							}
							else
							{							
								p = mod(pe_t.e.mod.src_reg, pe_t.e.mod.src_id, pe_t.e.mod.src_len, 
									pe_t.e.mod.dst_reg, pe_t.e.mod.dst_id, pe_t.e.mod.dst_len,
									pe_t.e.mod.src_name, pe_t.e.mod.dst_name);
							}
							break;
						default:
							break;
					}

					if(p)
					{
						struct pasm_explist *plist	= pexplist_build(p);
	
						if(plist)
						{
							pasm_add2explist(plist, pexplist);
						}
					}					
					reset_pasm(&pe_t);					
				}				
				break;

			case IR_UNARY:				
				flg_unary	= TRUE;

				p = NULL;

				switch(exp->e.unary.op)
				{
					case IR_INC:						
						p = add((exp->e.unary.left)->e.var.var_addr, (exp->e.unary.left)->e.var.var_id, 
								(exp->e.unary.left)->e.var.var_len,(exp->e.unary.right)->e.var.var_addr, 
								(exp->e.unary.right)->e.var.var_id,(exp->e.unary.right)->e.var.var_len,
								(exp->e.unary.left)->e.var.label, (exp->e.unary.right)->e.var.label);		
						break;
					case IR_DEC:
						
						p = minus((exp->e.unary.left)->e.var.var_addr, (exp->e.unary.left)->e.var.var_id,
								(exp->e.unary.left)->e.var.var_len,(exp->e.unary.right)->e.var.var_addr,
								(exp->e.unary.right)->e.var.var_id,(exp->e.unary.right)->e.var.var_len,
								(exp->e.unary.left)->e.var.label, (exp->e.unary.right)->e.var.label);		
						break;

					case IR_MUL:
						flg_unary	= FALSE;

						val_addr= (exp->e.unary.left)->e.var.var_addr;
						val_len = (exp->e.unary.left)->e.var.var_len;						
						val_id 	= (exp->e.unary.left)->e.var.var_id;

						switch(val_len)
						{
							case 4:
								val_addr = *(s32*)val_addr;
								break;
							default:
								break;
						}

						pname	=  (exp->e.unary.left)->e.var.label;
						break;

					 case IR_AND:
						flg_unary	= FALSE;

						val_addr= (exp->e.unary.left)->e.var.var_addr;						
						val_len	= PASM_ADDRESS_FLG;						
						pname	=(exp->e.unary.left)->e.var.label;
						break;
					default:
						break;					
				}
			
				if(p)
				{
					struct pasm_explist *plist	= pexplist_build(p);
	
					if(plist)
					{
						pasm_add2explist(plist, pexplist);
					}
				}
				
				break;

			case IR_LABEL:
				p = NULL;

				p = label(exp->e.label.label_name, exp->e.label.label_id);
			
				if(p)
				{
					struct pasm_explist *plist	= pexplist_build(p);
	
					if(plist)
					{
						pasm_add2explist(plist, pexplist);
					}
				}
				break;

			case IR_CALL:				
				flg_call	= TRUE;
				
				//paramlist
				ir_pmlist	= exp->e.call.ppv;
				p_pmlist	= pexplist_build(NULL);

				for(i=0; ir_pmlist; ir_pmlist=ir_pmlist->tail,i++)
				{
					struct ir_exp *ir_pmexp_1	= ir_pmlist->exp;

					for( ; ir_pmexp_1; ir_pmexp_1 = ir_pmexp_1->e.assign.val)
					{
						ir_pmexp	= ir_pmexp_1->e.assign.res;

						for( ; ir_pmexp; ir_pmexp = ir_pmexp->e.assign.val)
						{							
							p_pmexp	= mem((ir_pmexp->e.assign.res)->e.var.var_id, 
								(u32*)(ir_pmexp->e.assign.res)->e.var.var_addr, 
								   (ir_pmexp->e.assign.res)->e.var.var_len, 0, (ir_pmexp->e.assign.res)->e.var.label);

							struct pasm_explist	*pmlist_t	= pexplist_build(p_pmexp);
							pasm_add2explist(pmlist_t, p_pmlist);
						}
					}
					
				}				

				//add call
				p = NULL;
				p = call(exp->e.call.label_name, p_pmlist, exp->e.call.ret_len, exp->e.call.ret_addr);

				val_addr		= exp->e.call.ret_addr;
				val_len			= exp->e.call.ret_len;
				
				if(p)
				{
					struct pasm_explist *plist	= pexplist_build(p);
	
					if(plist)
					{
						pasm_add2explist(plist, pexplist);
					}
				}
				
				
				break;

			case IR_VARADDR:
				val_addr= exp->e.var.var_addr;
				val_len	= exp->e.var.var_len;
				val_id	= exp->e.var.var_id;				
				pname	= exp->e.var.label;
				break;

			case IR_ASSIGN:				
				flg_abop	= FALSE;				
				flg_call	= FALSE;				
				flg_relate	= FALSE;				
				flg_unary	= FALSE;				

				for(; exp; exp=exp->e.assign.val)
				{
					switch(exp->e.assign.op)
					{
						case IR_EQU:
							switch((exp->e.assign.res)->k)
							{
								case IR_VARADDR:
									l_res_addr	= (exp->e.assign.res)->e.var.var_addr;
									l_res_len	= (exp->e.assign.res)->e.var.var_len;
									clear_buf(l_res_pname, PASM_NAME_LEN);
									
									strcopy(l_res_pname, (exp->e.assign.res)->e.var.label);
									l_res_pname[strlen(l_res_pname)]	= NULL;				
									l_res_id	= (exp->e.assign.res)->e.var.var_id;
									continue;
									break;

								case IR_UNARY:
									switch((exp->e.assign.res)->e.unary.op)
									{
										case IR_MUL:
											l_res_addr= (exp->e.assign.res)->e.unary.left->e.var.var_addr;
											l_res_len = (exp->e.assign.res)->e.unary.left->e.var.var_len;
											l_res_id = (exp->e.assign.res)->e.unary.left->e.var.var_id;

											switch(l_res_len)
											{
												case 4:
													l_res_addr = *(s32*)l_res_addr;
													break;
												default:
													break;
											}

											clear_buf(l_res_pname, PASM_NAME_LEN);			
											strcopy(l_res_pname, 
												(exp->e.assign.res)->e.unary.left->e.var.label);
											l_res_pname[strlen(l_res_pname)]	= NULL;	
											continue;
											break;

										case IR_AND:
										case IR_NOT:
										case IR_PLUS:
										case IR_MINUS:
											l_res_addr= (exp->e.assign.res)->e.unary.left->e.var.var_addr;
											l_res_len = (exp->e.assign.res)->e.unary.left->e.var.var_len;
											clear_buf(l_res_pname, PASM_NAME_LEN);
											
											strcopy(l_res_pname, 
												(exp->e.assign.res)->e.unary.left->e.var.label);
											l_res_pname[strlen(l_res_pname)]	= NULL;		
											l_res_id = (exp->e.assign.res)->e.unary.left->e.var.var_id;
											continue;
											break;
										default:
											break;
									}									
									break;						

								case IR_POSTFIX:
									switch((exp->e.assign.res)->e.postfix.op)
									{
										case IR_STRUCT:
										case IR_POINTER:
										       l_res_addr=(exp->e.assign.res)->e.postfix.left->e.var.var_addr;
											l_res_len=(exp->e.assign.res)->e.postfix.left->e.var.var_len;
											clear_buf(l_res_pname, PASM_NAME_LEN);			
											strcopy(l_res_pname,
												(exp->e.assign.res)->e.postfix.left->e.var.label);
											l_res_pname[strlen(l_res_pname)]	= NULL;		
											l_res_id =(exp->e.assign.res)->e.postfix.left->e.var.var_id;
											continue;
											break;
										case IR_ARRAY:
											clear_buf(l_res_pname, PASM_NAME_LEN);
										       l_res_addr=(exp->e.assign.res)->e.postfix.left->e.var.var_addr;
											l_res_len=(exp->e.assign.res)->e.postfix.left->e.var.var_len;
											l_res_id =(exp->e.assign.res)->e.postfix.left->e.var.var_id;
											
											p1 = (exp->e.assign.res)->e.postfix.right;
						
											while(p1->k != IR_VARADDR)
											{
												p1=p1->e.assign.res;		
											}
						
											num_t	= *(s32*)(p1->e.var.var_addr);
											l_res_addr += l_res_len * num_t;
											
											empty_buf(tmp_buf, PASM_NAME_LEN);
											h2s(num_t, tmp_buf);

											strcopy(l_res_pname,"(");
											strcopy((l_res_pname+1),
												(exp->e.assign.res)->e.postfix.left->e.var.label);
											l_res_pname[strlen(l_res_pname)]	= ')';
											l_res_pname[strlen(l_res_pname)]	= '+';
											
											strcopy((l_res_pname+strlen(l_res_pname)), tmp_buf);
											l_res_pname[strlen(l_res_pname)]	= '*';

											empty_buf(tmp_buf, PASM_NAME_LEN);
											h2s(l_res_len, tmp_buf);
											strcopy((l_res_pname+strlen(l_res_pname)), tmp_buf);
											l_res_pname[strlen(l_res_pname)]	= NULL;
											continue;
											break;
										default:
											break;
									}
									break;
								default:
									break;
							}
							
							break;						
						default:
							break;
					}
					res = pasm_exp_process(exp->e.assign.res, pexplist);	

				}
				
				if(flg_abop)
				{
					p	= NULL;
					p 	= move(l_res_id, l_res_addr, l_res_len, val_addr, val_len, l_res_pname, "temp_val");
				}
				else if(flg_call)
				{
					p	= NULL;
					p 	= move(l_res_id, l_res_addr, l_res_len, val_addr, val_len, l_res_pname, "temp_val");
				}
				else if(flg_relate)
				{
					p	= NULL;					
				}
				else if(flg_unary)
				{
					p	= NULL;
					p 	= move(l_res_id, l_res_addr, l_res_len, val_addr, val_len, l_res_pname, "temp_val");
				}
				else
				{
					p	= NULL;
					p 	= move(l_res_id, l_res_addr, l_res_len, val_addr, val_len, l_res_pname, pname);
				}

				if(p)
				{
					struct pasm_explist *plist	= pexplist_build(p);
	
					if(plist)
					{
						pasm_add2explist(plist, pexplist);
					}
				}
				break;

			case IR_COND:
				p = NULL;

				p = jump(pasm_exp_process(exp->e.cond.cond, pexplist), 
					(exp->e.cond.op_1)->e.var.var_addr, ((exp->e.cond.op_2)->e.cond.op_1)->e.var.var_addr);
				
				if(p)
				{
					struct pasm_explist *plist	= pexplist_build(p);
	
					if(plist)
					{
						pasm_add2explist(plist, pexplist);
					}
				}
				break;

			case IR_RELATE:

				flg_relate	= TRUE;

				for(; exp->e.relate.left; exp=exp->e.relate.right)
				{
					struct pasm_exp *left	= pasm_exp_process(exp->e.relate.left,pexplist);	

					pe_t.k		= exp->e.relate.op;

					switch(pe_t.k)
					{
						case IR_ABOVE:								
							pe_t.e.above.src_reg	= val_addr;
							pe_t.e.above.src_id	= val_id;
							pe_t.e.above.src_len	= val_len;

							strcopy(pe_t.e.above.src_name, pname);
							pe_t.e.above.src_name[strlen(pe_t.e.above.src_name)]	= NULL;	
								
							break;
						case IR_LOW:
							pe_t.e.low.src_reg	= val_addr;
							pe_t.e.low.src_id	= val_id;
							pe_t.e.low.src_len	= val_len;
							
							strcopy(pe_t.e.low.src_name, pname);
							pe_t.e.low.src_name[strlen(pe_t.e.low.src_name)]	= NULL;	
							
							break;
						case IR_EQU_EQU:
							pe_t.e.equal.src_reg		= val_addr;
							pe_t.e.equal.src_id	= val_id;
							pe_t.e.equal.src_len	= val_len;
							
							strcopy(pe_t.e.equal.src_name, pname);
							pe_t.e.equal.src_name[strlen(pe_t.e.equal.src_name)]	= NULL;	

							
							break;
						case IR_NOT_EQU:
							pe_t.e.not_equal.src_reg		= val_addr;
							pe_t.e.not_equal.src_id	= val_id;
							pe_t.e.not_equal.src_len	= val_len;
							
							strcopy(pe_t.e.not_equal.src_name, pname);
							pe_t.e.not_equal.src_name[strlen(pe_t.e.not_equal.src_name)]	= NULL;	
							
							break;
						case IR_ABOVE_EQU:
							pe_t.e.above_equal.src_reg		= val_addr;
							pe_t.e.above_equal.src_id	= val_id;
							pe_t.e.above_equal.src_len	= val_len;
							
							strcopy(pe_t.e.above_equal.src_name, pname);
							pe_t.e.above_equal.src_name[strlen(pe_t.e.above_equal.src_name)]	= NULL;	
							
							break;

						case IR_LOW_EQU:
							pe_t.e.low_equal.src_reg		= val_addr;
							pe_t.e.low_equal.src_id	= val_id;
							pe_t.e.low_equal.src_len	= val_len;
							
							strcopy(pe_t.e.low_equal.src_name, pname);
							pe_t.e.low_equal.src_name[strlen(pe_t.e.low_equal.src_name)]	= NULL;	
							
							break;
						default:
							break;
					}					

					struct pasm_exp *right	= pasm_exp_process(exp->e.relate.right, pexplist);
	
					switch(pe_t.k)
					{
						case IR_ABOVE:								
							pe_t.e.above.dst_reg		= val_addr;
							pe_t.e.above.dst_id	= val_id;
							pe_t.e.above.dst_len	= val_len;
							
							strcopy(pe_t.e.above.dst_name, pname);
							pe_t.e.above.dst_name[strlen(pe_t.e.above.dst_name)]	= NULL;
									
							break;
						case IR_LOW:
							pe_t.e.low.dst_reg	= val_addr;
							pe_t.e.low.dst_id	= val_id;
							pe_t.e.low.dst_len	= val_len;
							
							strcopy(pe_t.e.low.dst_name, pname);
							pe_t.e.low.dst_name[strlen(pe_t.e.low.dst_name)]	= NULL;	
							break;
						case IR_EQU_EQU:
							pe_t.e.equal.dst_reg		= val_addr;
							pe_t.e.equal.dst_id	= val_id;
							pe_t.e.equal.dst_len	= val_len;
							
							strcopy(pe_t.e.equal.dst_name, pname);
							pe_t.e.equal.dst_name[strlen(pe_t.e.equal.dst_name)]	= NULL;	

							break;
						case IR_NOT_EQU:
							pe_t.e.not_equal.dst_reg		= val_addr;
							pe_t.e.not_equal.dst_id	= val_id;
							pe_t.e.not_equal.dst_len	= val_len;
							
							strcopy(pe_t.e.not_equal.dst_name, pname);
							pe_t.e.not_equal.dst_name[strlen(pe_t.e.not_equal.dst_name)]	= NULL;	
							break;
						case IR_ABOVE_EQU:
							pe_t.e.above_equal.dst_reg		= val_addr;
							pe_t.e.above_equal.dst_id	= val_id;
							pe_t.e.above_equal.dst_len	= val_len;
							
							strcopy(pe_t.e.above_equal.dst_name, pname);
							pe_t.e.above_equal.dst_name[strlen(pe_t.e.above_equal.dst_name)]	= NULL;	
							break;
						case IR_LOW_EQU:
							pe_t.e.low_equal.dst_reg		= val_addr;
							pe_t.e.low_equal.dst_id	= val_id;
							pe_t.e.low_equal.dst_len	= val_len;
							
							strcopy(pe_t.e.low_equal.dst_name, pname);
							pe_t.e.low_equal.dst_name[strlen(pe_t.e.low_equal.dst_name)]	= NULL;	
							break;
						default:
							break;
					}

					label_build(pe_t.e.above.t_label);
					label_build(pe_t.e.above.f_label);
					label_build(pe_t.e.above.e_label);				
		
					switch(pe_t.k)
					{
						case IR_ABOVE:	
							if(pe_t.e.above.dst_len == 0)
							{
								p = above(pe_t.e.above.dst_reg, pe_t.e.above.dst_id, pe_t.e.above.dst_len, 
									pe_t.e.above.src_reg, pe_t.e.above.src_id, pe_t.e.above.src_len,
									pe_t.e.above.dst_name, pe_t.e.above.src_name,
									pe_t.e.above.t_label, pe_t.e.above.f_label, pe_t.e.above.e_label);
							}
							else
							{							
								p = above(pe_t.e.above.src_reg, pe_t.e.above.src_id, pe_t.e.above.src_len, 
									pe_t.e.above.dst_reg, pe_t.e.above.dst_id, pe_t.e.above.dst_len,
									pe_t.e.above.src_name, pe_t.e.above.dst_name,
									pe_t.e.above.t_label, pe_t.e.above.f_label, pe_t.e.above.e_label);
							}
							break;
						case IR_LOW:
							if(pe_t.e.low.dst_len == 0)
							{
								p = low(pe_t.e.low.dst_reg, pe_t.e.low.dst_id, pe_t.e.low.dst_len, 
									pe_t.e.low.src_reg, pe_t.e.low.src_id, pe_t.e.low.src_len,
									pe_t.e.low.dst_name, pe_t.e.low.src_name,
									pe_t.e.low.t_label, pe_t.e.low.f_label, pe_t.e.low.e_label);
							}
							else
							{							
								p = low(pe_t.e.low.src_reg, pe_t.e.low.src_id, pe_t.e.low.src_len, 
									pe_t.e.low.dst_reg, pe_t.e.low.dst_id, pe_t.e.low.dst_len,
									pe_t.e.low.src_name, pe_t.e.low.dst_name,
									pe_t.e.low.t_label, pe_t.e.low.f_label, pe_t.e.low.e_label);
							}
							break;
						case IR_EQU_EQU:
							if(pe_t.e.equal.dst_len == 0)
							{
								p = equal(pe_t.e.equal.dst_reg, pe_t.e.equal.dst_id, pe_t.e.equal.dst_len, 
									pe_t.e.equal.src_reg, pe_t.e.equal.src_id, pe_t.e.equal.src_len,
									pe_t.e.equal.dst_name, pe_t.e.equal.src_name,
									pe_t.e.equal.t_label, pe_t.e.equal.f_label, pe_t.e.equal.e_label);
							}
							else
							{							
								p = equal(pe_t.e.equal.src_reg, pe_t.e.equal.src_id, pe_t.e.equal.src_len, 
									pe_t.e.equal.dst_reg, pe_t.e.equal.dst_id, pe_t.e.equal.dst_len,
									pe_t.e.equal.src_name, pe_t.e.equal.dst_name,
									pe_t.e.equal.t_label, pe_t.e.equal.f_label, pe_t.e.equal.e_label);
							}
							break;
						case IR_NOT_EQU:
							if(pe_t.e.not_equal.dst_len == 0)
							{
								p = not_equal(pe_t.e.not_equal.dst_reg, pe_t.e.not_equal.dst_id, 										pe_t.e.not_equal.dst_len, pe_t.e.not_equal.src_reg, 
									pe_t.e.not_equal.src_id, pe_t.e.not_equal.src_len,
									pe_t.e.not_equal.dst_name, pe_t.e.not_equal.src_name,
									pe_t.e.not_equal.t_label, pe_t.e.not_equal.f_label, pe_t.e.not_equal.e_label);
							}
							else
							{							
								p = not_equal(pe_t.e.not_equal.src_reg, pe_t.e.not_equal.src_id, 										pe_t.e.not_equal.src_len, pe_t.e.not_equal.dst_reg, 
									pe_t.e.not_equal.dst_id, pe_t.e.not_equal.dst_len,
									pe_t.e.not_equal.src_name, pe_t.e.not_equal.dst_name,
									pe_t.e.not_equal.t_label, pe_t.e.not_equal.f_label, pe_t.e.not_equal.e_label);
							}
							break;
						case IR_ABOVE_EQU:
							if(pe_t.e.above_equal.dst_len == 0)
							{
								p = above_equal(pe_t.e.above_equal.dst_reg,pe_t.e.above_equal.dst_id,
									pe_t.e.above_equal.dst_len, pe_t.e.above_equal.src_reg, 
									pe_t.e.above_equal.src_id, pe_t.e.above_equal.src_len,
									pe_t.e.above_equal.dst_name, pe_t.e.above_equal.src_name,
									pe_t.e.above_equal.t_label, pe_t.e.above_equal.f_label, 									pe_t.e.above_equal.e_label);
							}
							else
							{							
								p = above_equal(pe_t.e.above_equal.src_reg, pe_t.e.above_equal.src_id, 										pe_t.e.above_equal.src_len, pe_t.e.above_equal.dst_reg, 
									pe_t.e.above_equal.dst_id, pe_t.e.above_equal.dst_len, 
									pe_t.e.above_equal.src_name, pe_t.e.above_equal.dst_name,
									pe_t.e.above_equal.t_label, pe_t.e.above_equal.f_label, 									pe_t.e.above_equal.e_label);
							}
							break;
						case IR_LOW_EQU:
							if(pe_t.e.low_equal.dst_len == 0)
							{
								p = low_equal(pe_t.e.low_equal.dst_reg,pe_t.e.low_equal.dst_id,
									pe_t.e.low_equal.dst_len, pe_t.e.low_equal.src_reg, 
									pe_t.e.low_equal.src_id, pe_t.e.low_equal.src_len,
									pe_t.e.low_equal.dst_name, pe_t.e.low_equal.src_name,
									pe_t.e.low_equal.t_label, pe_t.e.low_equal.f_label, pe_t.e.low_equal.e_label);
							}
							else
							{							
								p = low_equal(pe_t.e.low_equal.src_reg, pe_t.e.low_equal.src_id, 										pe_t.e.low_equal.src_len, pe_t.e.low_equal.dst_reg, 
									pe_t.e.low_equal.dst_id, pe_t.e.low_equal.dst_len, 
									pe_t.e.low_equal.src_name, pe_t.e.low_equal.dst_name,
									pe_t.e.low_equal.t_label, pe_t.e.low_equal.f_label, pe_t.e.low_equal.e_label);
							}
							break;
						default:
							break;
					}

					if(p)
					{
						struct pasm_explist *plist	= pexplist_build(p);
	
						if(plist)
						{
							pasm_add2explist(plist, pexplist);
						}
					}
				
					reset_pasm(&pe_t);					
				}
				
				break;

			case IR_POSTFIX:
				p = NULL;

				switch(exp->e.postfix.op)
				{
					case IR_STRUCT:
						val_addr= (exp->e.postfix.left)->e.var.var_addr;
						val_len	= (exp->e.postfix.left)->e.var.var_len;
						num	= 0;						
						val_id	= (exp->e.postfix.left)->e.var.var_id;
						
						p = mem(val_id, val_addr, val_len, num, (exp->e.postfix.left)->e.var.label);

						val_addr		= val_addr + val_len * num;
						val_len			= val_len;
						
						pname	= (exp->e.postfix.left)->e.var.label;							
						break;

					case IR_POINTER:
						val_addr= (exp->e.postfix.left)->e.var.var_addr;
						val_len	= (exp->e.postfix.left)->e.var.var_len;
						num	= 0;						
						val_id	= (exp->e.postfix.left)->e.var.var_id;						
						p = mem(val_id, val_addr, val_len, num, (exp->e.postfix.left)->e.var.label);

						val_addr		= val_addr + val_len * num;
						val_len			= val_len;
						
						pname	= (exp->e.postfix.left)->e.var.label;						
						
						break;

					case IR_ARRAY:
						val_addr	= (exp->e.postfix.left)->e.var.var_addr;
						val_len	= (exp->e.postfix.left)->e.var.var_len;
						
						val_id	= (exp->e.postfix.left)->e.var.var_id;
						
						struct ir_exp *p = exp->e.postfix.right;
						
						while(p->k != IR_VARADDR)
						{
							p=p->e.assign.res;							
						}
						
						num	= *(s32*)(p->e.var.var_addr);
						
						empty_buf(temp_buf, PASM_NAME_LEN);
						empty_buf(tmp_buf, PASM_NAME_LEN);
						h2s(num, tmp_buf);

						strcopy(temp_buf,"(");
						strcopy((temp_buf+1), (exp->e.postfix.left)->e.var.label);
						temp_buf[strlen(temp_buf)]	= ')';
						temp_buf[strlen(temp_buf)]	= '+';

						strcopy((temp_buf+strlen(temp_buf)), tmp_buf);
						temp_buf[strlen(temp_buf)]	= '*';

						empty_buf(tmp_buf, PASM_NAME_LEN);
						h2s((exp->e.postfix.left)->e.var.var_len, tmp_buf);
						strcopy((temp_buf+strlen(temp_buf)), tmp_buf);
						temp_buf[strlen(temp_buf)]	= NULL;	
						
						p = mem(val_id, val_addr, val_len, num, temp_buf);

						val_addr		= val_addr + val_len * num;
						val_len			= val_len;
						
						pname	= temp_buf;	

						break;

					case IR_INC:						
						p = add((exp->e.postfix.left)->e.var.var_addr, (exp->e.postfix.left)->e.var.var_id,
								(exp->e.postfix.left)->e.var.var_len, (exp->e.postfix.right)->e.var.var_addr,
								(exp->e.postfix.right)->e.var.var_id, (exp->e.postfix.right)->e.var.var_len,
								(exp->e.postfix.left)->e.var.label, (exp->e.postfix.right)->e.var.label);
						break;

					case IR_DEC:						
						p = minus((exp->e.postfix.left)->e.var.var_addr, (exp->e.postfix.left)->e.var.var_id, 
								(exp->e.postfix.left)->e.var.var_len, (exp->e.postfix.right)->e.var.var_addr, 
								(exp->e.postfix.right)->e.var.var_id,(exp->e.postfix.right)->e.var.var_len,
								(exp->e.postfix.left)->e.var.label, (exp->e.postfix.right)->e.var.label);
						break;

					default:
						break;
				}
				
				if(p)
				{
					struct pasm_explist *plist	= pexplist_build(p);
	
					if(plist)
					{
						pasm_add2explist(plist, pexplist);
					}
				}
				break;

			default:
				break;
		}
	}

	return p;
}



//===========================================================================
// pexplist_build
//===========================================================================
PUBLIC	struct pasm_explist *	pexplist_build(struct pasm_exp *exp)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("	-- pexplist_build  -- \n");
#endif
//--------------------------

	struct pasm_explist *ret_explist	= malloc(sizeof(struct pasm_explist));

	if(!ret_explist)
	{
		printf("pexplist_build() malloc failed!!\n");
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
PUBLIC	s8	pasm_add2explist(struct pasm_explist *src, struct pasm_explist * dst)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("	-- pasm_add2explist  -- \n");
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
PUBLIC	struct pasm_sts *	pasm_sts_build(u32 kind, struct pasm_explist *p)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("	-- pasm_sts_build  -- \n");
#endif
//--------------------------

	struct pasm_sts *ret_sts	= malloc(sizeof(struct pasm_sts));

	if(!ret_sts)
	{
		printf("pasm_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= kind;
	ret_sts->s.exp_sts.pexplist	= p;

	return ret_sts;
}

//===========================================================================
// stslist_build()
//===========================================================================
PUBLIC	struct pasm_stslist *	pasm_stslist_build(struct pasm_sts *sts)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("	-- pasm_stslist_build  -- \n");
#endif
//--------------------------

	struct pasm_stslist *ret_stslist	= malloc(sizeof(struct pasm_stslist));

	if(!ret_stslist)
	{
		printf("pasm_stslist() malloc failed!!\n");
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
PUBLIC	s8	pasm_add2stslist(struct pasm_stslist *src, struct pasm_stslist * dst)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("	-- pasm_add2stslist  -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}
	
	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}

//===========================================================================
// file_build
//===========================================================================
PUBLIC	struct pasm_file *	pasm_file_build(struct pasm_stslist *stslist)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("	-- pasm_file_build  -- \n");
#endif
//--------------------------

	struct pasm_file *ret_file	= malloc(sizeof(struct pasm_file));

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
PUBLIC	s8	pasm_add2file(struct pasm_file *src, struct pasm_file * dst)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("	-- pasm_add2file  -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}
