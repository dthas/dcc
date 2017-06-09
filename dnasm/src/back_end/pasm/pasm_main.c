//===========================================================================
// pasm_main.c
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
#include	"dnasm_label.h"
#include	"dnasm_frame.h"
#include	"dnasm_ir.h"
#include	"dnasm_pasm.h"
#include	"dnasm_prototype.h"

#define	PASM_DEBUG

PRIVATE	s8 exp_kind_info[8][IR_WORD_LEN] = {"IR_EXP_ABOP", "IR_EXP_VARADDR", "IR_LABEL"};

PRIVATE	s8 word_info[IR_WORD_NUM][IR_WORD_LEN] = {
					"TIMES","DW","DD","DQ","DT","DY","RESB","RESW","RESQ","RESY",
	"INCBIN","EQU","DB","ADD","SUB","MUL","DIV","MOV","JMP","CALL",
	"RET","JA","JB","JE","JAE","JBE","JNE","GLOBAL","EXTERN","PUSH",
	"POP","EAX","EBX","ECX","EDX","EBP","ESP","ESI","EDI","CS",
	"EIP","DS","ES","SECTION","BYTE","WORD","DWORD","CMP","BITS","XOR",
	"BX","","IDENTIFIER","SPACE","SEMICOLON","CONST_DEC","ELLIPSIS","CONST_INT_8","CONST_INT_16","CONST_INT_32",
"CONST_INT_64","CONST_INT_128","CONST_BACKSLASH","CONST_QMARK","CONST_S_QUOTE","CONST_D_QUOTE","CONST_OCT","CONST_HEX","CONST_STRING","CONST_FLOAT",
	"CONST_DOUBLE","CONST_CR","","","","","","","OP_COLON","OP_COMMA",
	"OP_PLUS","OP_MINUS","OP_MUL","OP_DIV","OP_L_PARENTHESE","OP_R_PARENTHESE","OP_L_BRACKET","OP_R_BRACKET","PARSE_END"
				};

s8 *pname	=NULL;
u32 val_addr	=0;
u32 val_len	=0;
s32 val_id	=-1;

s8 flg_abop	= FALSE;

struct pasm_exp pe_t;
//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	pasm_main()
{
	printf("==================================================================\n");
	printf("	pasm_main\n");
	printf("==================================================================\n");

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
			case IR_STS_MOV:
				if(sts->s.mov_sts.explist)
				{
					pasm_explist_process(sts->s.mov_sts.explist, plist);

					label	= PASM_STS_MOV;
					psts	= pasm_sts_build(label, plist);
				}				
				break;

			case IR_STS_ADD:
				if(sts->s.add_sts.explist)
				{
					pasm_explist_process(sts->s.add_sts.explist, plist);

					label	= PASM_STS_ADD;
					psts	= pasm_sts_build(label, plist);
				}				
				break;

			case IR_STS_SUB:
				if(sts->s.sub_sts.explist)
				{
					pasm_explist_process(sts->s.sub_sts.explist, plist);

					label	= PASM_STS_SUB;
					psts	= pasm_sts_build(label, plist);
				}				
				break;

			case IR_STS_MUL:
				if(sts->s.mul_sts.explist)
				{
					pasm_explist_process(sts->s.mul_sts.explist, plist);

					label	= PASM_STS_MUL;
					psts	= pasm_sts_build(label, plist);
				}				
				break;

			case IR_STS_DIV:
				if(sts->s.div_sts.explist)
				{
					pasm_explist_process(sts->s.div_sts.explist, plist);

					label	= PASM_STS_DIV;
					psts	= pasm_sts_build(label, plist);
				}				
				break;

			case IR_STS_CALL:
				if(sts->s.call_sts.explist)
				{
					pasm_explist_process(sts->s.call_sts.explist, plist);

					label	= PASM_STS_CALL;
					psts	= pasm_sts_build(label, plist);
				}				
				break;

			case IR_STS_RET:
				pasm_explist_process(sts->s.ret_sts.explist, plist);

				label	= PASM_STS_RET;
				psts	= pasm_sts_build(label, plist);								
				break;

			case IR_STS_JMP:
				if(sts->s.jmp_sts.explist)
				{
					pasm_explist_process(sts->s.jmp_sts.explist, plist);

					label	= PASM_STS_JMP;
					psts	= pasm_sts_build(label, plist);
				}				
				break;
		
			case IR_STS_JA:
				if(sts->s.ja_sts.explist)
				{
					pasm_explist_process(sts->s.ja_sts.explist, plist);

					label	= PASM_STS_JA;
					psts	= pasm_sts_build(label, plist);
				}				
				break;

			case IR_STS_JB:
				if(sts->s.jb_sts.explist)
				{
					pasm_explist_process(sts->s.jb_sts.explist, plist);

					label	= PASM_STS_JB;
					psts	= pasm_sts_build(label, plist);
				}				
				break;

			case IR_STS_JE:
				if(sts->s.je_sts.explist)
				{
					pasm_explist_process(sts->s.je_sts.explist, plist);

					label	= PASM_STS_JE;
					psts	= pasm_sts_build(label, plist);
				}				
				break;

			case IR_STS_JAE:
				if(sts->s.jae_sts.explist)
				{
					pasm_explist_process(sts->s.jae_sts.explist, plist);

					label	= PASM_STS_JAE;
					psts	= pasm_sts_build(label, plist);
				}				
				break;

			case IR_STS_JBE:
				if(sts->s.jbe_sts.explist)
				{
					pasm_explist_process(sts->s.jbe_sts.explist, plist);

					label	= PASM_STS_JBE;
					psts	= pasm_sts_build(label, plist);
				}				
				break;

			case IR_STS_JNE:
				if(sts->s.jne_sts.explist)
				{
					pasm_explist_process(sts->s.jne_sts.explist, plist);

					label	= PASM_STS_JNE;
					psts	= pasm_sts_build(label, plist);
				}				
				break;

			case IR_STS_PUSH:
				if(sts->s.push_sts.explist)
				{
					pasm_explist_process(sts->s.push_sts.explist, plist);

					label	= PASM_STS_PUSH;
					psts	= pasm_sts_build(label, plist);
				}				
				break;

			case IR_STS_POP:
				if(sts->s.pop_sts.explist)
				{
					pasm_explist_process(sts->s.pop_sts.explist, plist);

					label	= PASM_STS_POP;
					psts	= pasm_sts_build(label, plist);
				}				
				break;

			case IR_STS_CMP:
				if(sts->s.cmp_sts.explist)
				{
					pasm_explist_process(sts->s.cmp_sts.explist, plist);

					label	= PASM_STS_CMP;
					psts	= pasm_sts_build(label, plist);
				}				
				break;

			case IR_STS_LABEL:
				if(sts->s.label_sts.explist)
				{
					pasm_explist_process(sts->s.label_sts.explist, plist);

					label	= PASM_STS_LABEL;
					psts	= pasm_sts_build(label, plist);
				}
				break;
			case IR_STS_XOR:
				if(sts->s.xor_sts.explist)
				{
					pasm_explist_process(sts->s.xor_sts.explist, plist);

					label	= PASM_STS_XOR;
					psts	= pasm_sts_build(label, plist);
				}				
				break;			
			case IR_STS_INT:
				if(sts->s.int_sts.explist)
				{
					pasm_explist_process(sts->s.int_sts.explist, plist);

					label	= PASM_STS_INT;
					psts	= pasm_sts_build(label, plist);
				}				
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
	
	struct pasm_exp *p = NULL;
	
	if(exp)
	{
		switch(exp->k)
		{
			case IR_EXP_ABOP:

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
						
						default:
							break;
					}

										
				}

				if(p)
				{
					switch(exp->s)
					{
						case IR_REG:
							p->s	= PASM_REG;
							break;
						case IR_MEM:
							p->s	= PASM_MEM;
							break;
						case IR_IMM:
							p->s	= PASM_IMM;
							break;
						default:
							break;
					}

					struct pasm_explist *plist	= pexplist_build(p);
	
					if(plist)
					{
						pasm_add2explist(plist, pexplist);
					}
				}

				reset_pasm(&pe_t);

				flg_abop	= FALSE;

				break;		

			case IR_EXP_VARADDR:			
				
				if(!flg_abop)
				{
					p = var(exp->e.var.label);

					if(p)
					{
						switch(exp->s)
						{
							case IR_REG:
								p->s	= PASM_REG;
								break;
							case IR_MEM:
								p->s	= PASM_MEM;
								break;
							case IR_IMM:
								p->s	= PASM_IMM;
								break;
							default:
								break;
						}

						struct pasm_explist *plist	= pexplist_build(p);
	
						if(plist)
						{
							pasm_add2explist(plist, pexplist);
						}
					}			
				}
				else
				{
					val_addr= exp->e.var.var_addr;
					val_len	= exp->e.var.var_len;
					val_id	= exp->e.var.var_id;
					pname	= exp->e.var.label;					
				}
				break;

			case IR_EXP_LABEL:
				p = label(exp->e.label.label_name, exp->e.label.label_id);	

				if(p)
				{
					switch(exp->s)
					{
						case IR_REG:
							p->s	= PASM_REG;
							break;
						case IR_MEM:
							p->s	= PASM_MEM;
							break;
						case IR_IMM:
							p->s	= PASM_IMM;
							break;
						default:
							break;
					}

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
	ret_sts->s.mov_sts.pexplist	= p;

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
