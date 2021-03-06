//===========================================================================
// ir_lib.c
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
#include	"dnasm_frame.h"
#include	"dnasm_ir.h"
#include	"dnasm_prototype.h"

#define	IR_DEBUG

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

PRIVATE	s8 sts_kind_info[19][IR_WORD_LEN] = {"IR_STS_MOV", "IR_STS_ADD", "IR_STS_SUB", "IR_STS_MUL", "IR_STS_DIV", "IR_STS_CALL", "IR_STS_RET",
						"IR_STS_JMP", "IR_STS_JA", "IR_STS_JB", "IR_STS_JE", "IR_STS_JAE", "IR_STS_JBE", "IR_STS_JNE",
						"IR_STS_PUSH", "IR_STS_POP", "IR_STS_CMP", "IR_STS_LABEL", "IR_STS_XOR"};

PRIVATE	s8 exp_kind_info[3][IR_WORD_LEN] = {"IR_EXP_ABOP", "IR_EXP_VARADDR", "IR_EXP_LABEL"};


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
			case IR_STS_MOV:
				ir_explist_print(sts->s.mov_sts.explist);
				break;
			case IR_STS_ADD:
				ir_explist_print(sts->s.add_sts.explist);
				break;
			case IR_STS_SUB:
				ir_explist_print(sts->s.sub_sts.explist);
				break;
			case IR_STS_MUL:
				ir_explist_print(sts->s.mul_sts.explist);
				break;
			case IR_STS_DIV:
				ir_explist_print(sts->s.div_sts.explist);
				break;
			case IR_STS_CALL:
				ir_explist_print(sts->s.call_sts.explist);
				break;
			case IR_STS_RET:
				ir_explist_print(sts->s.ret_sts.explist);
				break;
			case IR_STS_JMP:
				ir_explist_print(sts->s.jmp_sts.explist);
				break;
			case IR_STS_JA:
				ir_explist_print(sts->s.ja_sts.explist);
				break;
			case IR_STS_JB:
				ir_explist_print(sts->s.jb_sts.explist);
				break;
			case IR_STS_JE:
				ir_explist_print(sts->s.je_sts.explist);
				break;
			case IR_STS_JAE:
				ir_explist_print(sts->s.jae_sts.explist);
				break;
			case IR_STS_JBE:
				ir_explist_print(sts->s.jbe_sts.explist);
				break;
			case IR_STS_JNE:
				ir_explist_print(sts->s.jne_sts.explist);
				break;
			case IR_STS_PUSH:
				ir_explist_print(sts->s.push_sts.explist);
				break;
			case IR_STS_POP:
				ir_explist_print(sts->s.pop_sts.explist);
				break;
			case IR_STS_CMP:
				ir_explist_print(sts->s.cmp_sts.explist);
				break;
			case IR_STS_LABEL:
				ir_labellist_print(sts->s.label_sts.explist);
				break;
			case IR_STS_XOR:
				ir_explist_print(sts->s.xor_sts.explist);
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
PUBLIC	void	ir_exp_print(struct ir_exp *exp)
{
//--------------------------
//test
#ifdef	IR_DEBUG
	printf("%20s %10s (exp=%x)\n","","-- ir_exp_print --",exp);	
#endif
//--------------------------

	struct ir_exp *t;

	if(exp)
	{

//--------------------------
//test
#ifdef	IR_DEBUG
	printf("%25s ----(exp_kind=%s) \n","",exp_kind_info[exp->k - IR_EXPKIND_BASE]);
#endif
//--------------------------

		switch(exp->k)
		{
			case IR_EXP_ABOP:
				for(; exp->e.abop.left; exp=exp->e.abop.right)
				{
					ir_exp_print(exp->e.abop.left);

					printf("%s\n", &word_info[exp->e.abop.op][0]);

					ir_exp_print(exp->e.abop.right);
				}
				printf("\n");

				break;

			case IR_EXP_VARADDR:
				ir_var_print(exp);
				break;

			case IR_EXP_LABEL:			
				printf("label_name: %s,  label_id: %d ", exp->e.label.label_name, exp->e.label.label_id);
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

	switch(var_type)
	{
		case DWORD:
			printf("%35s (name=%s)","", (s8*)(exp->e.var.label));			
			break;
		case BYTE:
			printf("%35s (char%s)","", (s8*)(exp->e.var.label));		
			break;
		case WORD:
			printf("%35s (name=%s)","", (s8*)(exp->e.var.label));			
			break;
		default:
			break;
	}
}
