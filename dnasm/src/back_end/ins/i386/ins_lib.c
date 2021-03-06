//===========================================================================
// ins_lib.c
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
#include	"dnasm_pasm.h"
#include	"dnasm_block.h"
#include	"dnasm_elf.h"
#include	"dnasm_ins.h"
#include	"dnasm_prototype.h"

#define	INS_DEBUG

PRIVATE	s8 	ins_temp_buf[INS_LEN];
PRIVATE	s8	regs_32[REG_NUM][4]	= {"eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"};
PRIVATE	s8	regs_16[REG_NUM][4]	= {"ax", "cx", "dx", "bx", "sp", "bp", "si", "di"};

//===========================================================================
// ins_ret_build
//===========================================================================
PUBLIC	struct ins_str *	ins_ret_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_ret_build -- \n");
#endif
//--------------------------

	struct ins_ret *p;	

	p	= ins_ret_32_build();

	instr->e.ins_ret.m.ret_32.format_1	= p->m.ret_32.format_1;

	instr->k		= INS_STS_RET;

	instr->e.ins_ret.k	= p->k;
	instr->e.ins_ret.len	= p->len;
}


//===========================================================================
// ins_jmp_build
//===========================================================================
PUBLIC	struct ins_str *	ins_xor_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_xor_build(s) -- \n");
#endif
//--------------------------
	struct pasm_exp *exp;
	u32 reg=NULL;
	u32 rm=NULL;
	s32 data=NULL;
	struct ins_xor *p;

	

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// dst
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	switch(exp->s)
	{
		case PASM_REG:
			//for test
			printf("ins_xor_build::rm=%s\n\n",exp->e.var.var_name);

			rm	= chk_reg_i(exp->e.var.var_name);			
			break;

		default:
			break;
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// src
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	for(pexplist=pexplist->tail; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
		
	switch(exp->s)
	{
		case PASM_REG:
			reg	= chk_reg_i(exp->e.var.var_name);

			p	= ins_xor_reg_2_reg_32_build(rm, reg);

			instr->e.ins_xor.m.xor_reg_2_reg_32.format_1	= p->m.xor_reg_2_reg_32.format_1;
			instr->e.ins_xor.m.xor_reg_2_reg_32.format_2	= p->m.xor_reg_2_reg_32.format_2;
			break;
		default:
			break;
	}

	instr->k		= INS_STS_XOR;

	instr->e.ins_xor.k	= p->k;
	instr->e.ins_xor.len	= p->len;
	
	

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_xor_build(e) -- \n\n");
#endif
//--------------------------	
}

//===========================================================================
// ins_add_build
//===========================================================================
PUBLIC	struct ins_str *	ins_add_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_add_build -- \n");
#endif
//--------------------------

	struct pasm_exp *exp;
	u32 reg=NULL;
	u32 rm=NULL;
	s32 data=NULL;
	struct ins_add *p;

	

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// dst
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	switch(exp->s)
	{
		case PASM_REG:
			rm	= chk_reg_i(exp->e.var.var_name);			
			break;

		default:
			break;
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// src
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	for(pexplist=pexplist->tail; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
		
	switch(exp->s)
	{
		case PASM_REG:
			reg	= chk_reg_i(exp->e.var.var_name);

			p	= ins_add_reg_2_reg_32_build(rm, reg);

			instr->e.ins_add.m.add_reg_2_reg_32.format_1	= p->m.add_reg_2_reg_32.format_1;
			instr->e.ins_add.m.add_reg_2_reg_32.format_2	= p->m.add_reg_2_reg_32.format_2;
			break;
		case PASM_IMM:
			data	= s2h(exp->e.var.var_name);			

			p	= ins_add_reg_2_imm_8_build(rm, data);

			instr->e.ins_add.m.add_reg_2_imm_8.format_1	= p->m.add_reg_2_imm_8.format_1;
			instr->e.ins_add.m.add_reg_2_imm_8.format_2	= p->m.add_reg_2_imm_8.format_2;
			instr->e.ins_add.m.add_reg_2_imm_8.data		= p->m.add_reg_2_imm_8.data;			
			
			break;

		default:
			break;
	}

	instr->k		= INS_STS_ADD;

	instr->e.ins_add.k	= p->k;
	instr->e.ins_add.len	= p->len;
}


//===========================================================================
// ins_minus_build
//===========================================================================
PUBLIC	struct ins_str *	ins_sub_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_sub_build -- \n");
#endif
//--------------------------
	struct pasm_exp *exp;
	u32 reg=NULL;
	u32 rm=NULL;
	s32 data=NULL;
	struct ins_sub *p;

	

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// dst
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	switch(exp->s)
	{
		case PASM_REG:			
			rm	= chk_reg_i(exp->e.var.var_name);			
			break;

		default:
			break;
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// src
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	for(pexplist=pexplist->tail; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
		
	switch(exp->s)
	{
		case PASM_REG:	

			reg	= chk_reg_i(exp->e.var.var_name);

			p	= ins_sub_reg_2_reg_32_build(rm, reg);

			instr->e.ins_sub.m.sub_reg_2_reg_32.format_1	= p->m.sub_reg_2_reg_32.format_1;
			instr->e.ins_sub.m.sub_reg_2_reg_32.format_2	= p->m.sub_reg_2_reg_32.format_2;
			break;
		default:
			break;
	}

	instr->k		= INS_STS_SUB;

	instr->e.ins_sub.k	= p->k;
	instr->e.ins_sub.len	= p->len;
	
}


//===========================================================================
// ins_mul_build
//===========================================================================
PUBLIC	struct ins_str *	ins_mul_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mul_build -- \n");
#endif
//--------------------------

	struct pasm_exp *exp;
	u32 reg=NULL;
	u32 rm=NULL;
	s32 data=NULL;
	struct ins_mul *p;	

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// dst
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	switch(exp->s)
	{
		case PASM_REG:			
			rm	= chk_reg_i(exp->e.var.var_name);

			p	= ins_mul_reg_16_build(rm);

			instr->e.ins_mul.m.mul_reg_16.prefix	= p->m.mul_reg_16.prefix;
			instr->e.ins_mul.m.mul_reg_16.format_1	= p->m.mul_reg_16.format_1;
			instr->e.ins_mul.m.mul_reg_16.format_2	= p->m.mul_reg_16.format_2;
			
			break;

		default:
			break;
	}	

	instr->k		= INS_STS_MUL;

	instr->e.ins_mul.k	= p->k;
	instr->e.ins_mul.len	= p->len;
}




//===========================================================================
// ins_div_build
//===========================================================================
PUBLIC	struct ins_str *	ins_div_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_div_build -- \n");
#endif
//--------------------------

	struct pasm_exp *exp;
	u32 reg=NULL;
	u32 rm=NULL;
	s32 data=NULL;
	struct ins_div *p;	

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// dst
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	switch(exp->s)
	{
		case PASM_REG:			
			rm	= chk_reg_i(exp->e.var.var_name);

			p	= ins_div_reg_16_build(rm);

			instr->e.ins_div.m.div_reg_16.prefix	= p->m.div_reg_16.prefix;
			instr->e.ins_div.m.div_reg_16.format_1	= p->m.div_reg_16.format_1;
			instr->e.ins_div.m.div_reg_16.format_2	= p->m.div_reg_16.format_2;
			
			break;

		default:
			break;
	}	

	instr->k		= INS_STS_DIV;

	instr->e.ins_div.k	= p->k;
	instr->e.ins_div.len	= p->len;
}


//===========================================================================
// ins_move_build
//===========================================================================
PUBLIC	struct ins_str *	ins_mov_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_mov_build -- \n");
#endif
//--------------------------
	struct pasm_exp *exp;
	u32 reg=NULL;
	u32 rm=NULL;
	u32 addr=NULL;
	s8 offset=NULL;
	s32 data=NULL;
	struct ins_mov *p;

	s8 flg_reg = FALSE;
	s8 flg_mem = FALSE;
	s8 flg_addr= FALSE;

	//add on 2013-9-13
	s8 data_name[INS_NAME_LEN];
	

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// dst
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	switch(exp->s)
	{
		case PASM_REG:
			rm	= chk_reg_i(exp->e.var.var_name);

			flg_reg = TRUE;			
			break;
		case PASM_MEM:
			switch(exp->k)
			{
				case PASM_EXP_ADD:
					rm	= chk_reg_i(exp->e.add.dst_name);
					offset	= s2h(exp->e.add.src_name);
					
					flg_mem	= TRUE;
					break;
				case PASM_EXP_SUB:					
					rm 	= chk_reg_i(exp->e.minus.dst_name);
					offset	= 0xFF - s2h(exp->e.minus.src_name) + 1;
					
					flg_mem	= TRUE;
					break;
				case PASM_EXP_VAR:					
					addr 	= chk_reg_i(exp->e.var.var_name);					
					
					empty_buf(data_name, INS_NAME_LEN);
					strcopy(data_name, exp->e.var.var_name);
					data_name[strlen(exp->e.var.var_name)]	= NULL;				
					
					flg_addr= TRUE;
					break;
				default:
					break;
			}

			
			break;

		default:
			break;
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// src
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	for(pexplist=pexplist->tail; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
		
	switch(exp->s)
	{
		case PASM_REG:			
			reg	= chk_reg_i(exp->e.var.var_name);

			if(flg_reg)
			{
				p	= ins_mov_reg_2_reg_32_build(rm, reg);

				instr->e.ins_mov.m.mov_reg_2_reg_32.format_1	= p->m.mov_reg_2_reg_32.format_1;
				instr->e.ins_mov.m.mov_reg_2_reg_32.format_2	= p->m.mov_reg_2_reg_32.format_2;
			}
			else if(flg_mem)
			{
				p	= ins_mov_mem_2_reg_32_build(reg, offset);

				instr->e.ins_mov.m.mov_mem_2_reg_32.format_1	= p->m.mov_mem_2_reg_32.format_1;
				instr->e.ins_mov.m.mov_mem_2_reg_32.format_2	= p->m.mov_mem_2_reg_32.format_2;
				instr->e.ins_mov.m.mov_mem_2_reg_32.offset	= p->m.mov_mem_2_reg_32.offset;
			}
			else if(flg_addr)
			{
				p	= ins_mov_numb_2_reg_32_build(reg, addr);

				instr->e.ins_mov.m.mov_numb_2_reg_32.format_1	= p->m.mov_numb_2_reg_32.format_1;
				instr->e.ins_mov.m.mov_numb_2_reg_32.format_2	= p->m.mov_numb_2_reg_32.format_2;
				instr->e.ins_mov.m.mov_numb_2_reg_32.addr	= p->m.mov_numb_2_reg_32.addr;

				//--------------------------------------------------------				
				//for relocate table
				struct symbol *	sym	= symtbl_search(data_name);
				if(!sym)
				{
					printf("ins_mov_process::error, can not find the symbol:%s !!!\n\n", data_name);
				}

				struct symbol *p;
				s8 flag_f = FALSE;
				s32 i, num;
	
				//get num, which is the index within strtab in future
				for(i=0, num=1; i<SYMTBL_SIZE; i++)
				{
					if(flag_f)
					{
						break;
					}

					for(p=(*(p_symtbl+i)).tail; p!=NULL; p=p->tail)
					{
						if(p->flag != FLAG_SYM)
						{
							if(strcmp(p->name, data_name) == TRUE)
							{
								flag_f = TRUE;
								break;
							}

							//for index
							num++;
						}

						
					}
				}

				struct rel32	  *rel	= malloc(sizeof(struct rel32));
				rel->offset		= ins_code_offset + sizeof(instr->e.ins_mov.m.mov_numb_2_reg_32.format_1) + 
								sizeof(instr->e.ins_mov.m.mov_numb_2_reg_32.format_2);

				switch(sym->attr)
				{
					case ATTR_FUN:
						rel->info	= num; 
						rel->info	= ((rel->info)<<8)| R_386_PC32;
						break;
					case ATTR_VAR:
						rel->info	= num; 
						rel->info	= ((rel->info)<<8)|  R_386_32;					
						break;
					default:
						break;
				} 	

				//add to relocate list
				struct rel32_list *rellist	= rel32list_build(rel);
				elf_add2rellist(rellist, rell);

				reltab_offset	+= sizeof(struct rel32);				
				//--------------------------------------------------------
			}
			break;
		case PASM_MEM:
			switch(exp->k)
			{
				case PASM_EXP_ADD:
					reg 	= chk_reg_i(exp->e.add.dst_name);
					offset	= s2h(exp->e.add.src_name);

					p	= ins_mov_reg_2_mem_32_build(rm, offset);

					instr->e.ins_mov.m.mov_reg_2_mem_32.format_1	= p->m.mov_reg_2_mem_32.format_1;
					instr->e.ins_mov.m.mov_reg_2_mem_32.format_2	= p->m.mov_reg_2_mem_32.format_2;
					instr->e.ins_mov.m.mov_reg_2_mem_32.offset	= p->m.mov_reg_2_mem_32.offset;
					break;
				case PASM_EXP_SUB:					
					reg 	= chk_reg_i(exp->e.minus.dst_name);
					offset	= 0xFF - s2h(exp->e.minus.src_name) + 1;				

					p	= ins_mov_reg_2_mem_32_build(rm, offset);

					instr->e.ins_mov.m.mov_reg_2_mem_32.format_1	= p->m.mov_reg_2_mem_32.format_1;
					instr->e.ins_mov.m.mov_reg_2_mem_32.format_2	= p->m.mov_reg_2_mem_32.format_2;
					instr->e.ins_mov.m.mov_reg_2_mem_32.offset	= p->m.mov_reg_2_mem_32.offset;
					break;
				case PASM_EXP_VAR:					
					addr 	= chk_reg_i(exp->e.var.var_name);
					
					p	= ins_mov_reg_2_numb_32_build(rm, addr);

					instr->e.ins_mov.m.mov_reg_2_numb_32.format_1	= p->m.mov_reg_2_numb_32.format_1;
					instr->e.ins_mov.m.mov_reg_2_numb_32.format_2	= p->m.mov_reg_2_numb_32.format_2;
					instr->e.ins_mov.m.mov_reg_2_numb_32.addr	= p->m.mov_reg_2_numb_32.addr;

					//----------------------------------------------------
					empty_buf(data_name, INS_NAME_LEN);
					strcopy(data_name, exp->e.var.var_name);
					data_name[strlen(exp->e.var.var_name)]	= NULL;
					
					//for relocate table
					struct symbol *	sym	= symtbl_search(data_name);
					if(!sym)
					{
						printf("ins_mov_process::error, can not find the symbol:%s !!!\n\n", data_name);
					}

					struct symbol *p;
					s8 flag_f = FALSE;
					s32 i, num;
	
					//get num, which is the index within strtab in future
					for(i=0, num=1; i<SYMTBL_SIZE; i++)
					{
						if(flag_f)
						{
							break;
						}

						for(p=(*(p_symtbl+i)).tail; p!=NULL; p=p->tail)
						{
							if(p->flag != FLAG_SYM)
							{
								if(strcmp(p->name, data_name) == TRUE)
								{
									flag_f = TRUE;
									break;
								}

								//for index
								num++;
							}

						
						}
					}

					struct rel32	  *rel	= malloc(sizeof(struct rel32));
					rel->offset		= ins_code_offset + sizeof(instr->e.ins_mov.m.mov_numb_2_reg_32.format_1) + 
									sizeof(instr->e.ins_mov.m.mov_numb_2_reg_32.format_2);

					switch(sym->attr)
					{
						case ATTR_FUN:
							rel->info	= num; 
							rel->info	= ((rel->info)<<8)| R_386_PC32;
							break;
						case ATTR_VAR:
							rel->info	= num; 
							rel->info	= ((rel->info)<<8)|  R_386_32;					
							break;
						default:
							break;
					} 	

					//add to relocate list
					struct rel32_list *rellist	= rel32list_build(rel);
					elf_add2rellist(rellist, rell);

					reltab_offset	+= sizeof(struct rel32);					
					//--------------------------------------------------------


					break;
				default:
					break;
			}
			break;
		case PASM_IMM:
			data	= s2h(exp->e.var.var_name);			

			p	= ins_mov_reg_2_imm_32_build(rm, data);

			instr->e.ins_mov.m.mov_reg_2_imm_32.format_1	= p->m.mov_reg_2_imm_32.format_1;
			instr->e.ins_mov.m.mov_reg_2_imm_32.data	= p->m.mov_reg_2_imm_32.data;			
			break;

		default:
			break;
	}

	instr->k		= INS_STS_MOV;

	instr->e.ins_mov.k	= p->k;
	instr->e.ins_mov.len	= p->len;
	
}


//===========================================================================
// ins_label_build
//===========================================================================
PUBLIC	struct ins_str *	ins_label_build(struct pasm_explist *pexplist, struct ins_str * instr, s32 offset)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_label_build -- \n");
#endif
//--------------------------

	struct pasm_exp *exp;
	s8 *t=NULL;
	
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// dst
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}

	t = exp->e.label.label_name;			
			
	struct symbol *	sym	= symtbl_search(t);
	if(sym)
	{
		sym->val_i	= offset;

		sym->val_i_1	= sym->val_i;
	}
	else
	{
		printf("ins_lib::no such symbol:%s !!! \n\n");
		exit(0);
	}

	struct ins_label *p	= ins_label_32_build(t, offset);

	instr->k		= INS_STS_LABEL;

	instr->e.ins_label.k	= p->k;
	instr->e.ins_label.len	= p->len;

	instr->e.ins_label.m.label.offset	= p->m.label.offset;

	strcopy(&(instr->e.ins_label.m.label.name), p->m.label.name);
	instr->e.ins_label.m.label.name[strlen(p->m.label.name)]	= NULL;	

	sym->addr	= offset;	
}



//===========================================================================
// ins_call_build
//===========================================================================
PUBLIC	struct ins_str *	ins_call_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_call_build -- \n");
#endif
//--------------------------

	struct pasm_exp *exp;

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	u32 reg, rm;
	s8 offset;
	struct ins_call *p;
	switch(exp->s)
	{
		case PASM_MEM:
			switch(exp->k)
			{
				case PASM_EXP_VAR:
					printf("ins_call_build::label=%s\n\n",exp->e.var.var_name);
					
					p	= ins_call_32_build(exp->e.var.var_name);

					instr->e.ins_call.m.call_32.format_1	= p->m.call_32.format_1;
					instr->e.ins_call.m.call_32.offset	= p->m.call_32.offset;

					strcopy(instr->e.ins_call.m.call_32.label, p->m.call_32.label);
					instr->e.ins_call.m.call_32.label[strlen(p->m.call_32.label)]	= NULL;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	instr->k		= INS_STS_CALL;

	instr->e.ins_call.k	= p->k;
	instr->e.ins_call.len	= p->len;

}


//===========================================================================
// ins_jump_build
//===========================================================================
PUBLIC	struct ins_str *	ins_jump_build(s8 *target, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_jump_build -- \n");
#endif
//--------------------------

	
}

//===========================================================================
// ins_above_build
//===========================================================================
PUBLIC	struct ins_str *	ins_ja_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_ja_build(s) -- \n");
#endif
//--------------------------

	struct pasm_exp *exp;

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	u32 reg, rm;
	s8 offset;
	struct ins_ja *p;
	switch(exp->s)
	{
		case PASM_MEM:
			switch(exp->k)
			{
				case PASM_EXP_VAR:
					printf("ins_ja_build::label=%s\n\n",exp->e.var.var_name);
					
					p	= ins_ja_8_build(exp->e.var.var_name);

					instr->e.ins_ja.m.ja_8.format_1	= p->m.ja_8.format_1;
					instr->e.ins_ja.m.ja_8.offset	= p->m.ja_8.offset;

					strcopy(instr->e.ins_ja.m.ja_8.label, p->m.ja_8.label);
					instr->e.ins_ja.m.ja_8.label[strlen(p->m.ja_8.label)]	= NULL;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	instr->k		= INS_STS_JA;

	instr->e.ins_ja.k	= p->k;
	instr->e.ins_ja.len	= p->len;

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_ja_build(e) -- \n\n");
#endif
//--------------------------	
}

//===========================================================================
// ins_low_build
//===========================================================================
PUBLIC	struct ins_str *	ins_jb_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_low_build(s) -- \n");
#endif
//--------------------------

	struct pasm_exp *exp;

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	u32 reg, rm;
	s8 offset;
	struct ins_jb *p;
	switch(exp->s)
	{
		case PASM_MEM:
			switch(exp->k)
			{
				case PASM_EXP_VAR:
					printf("ins_jb_build::label=%s\n\n",exp->e.var.var_name);
					
					p	= ins_jb_8_build(exp->e.var.var_name);

					instr->e.ins_jb.m.jb_8.format_1	= p->m.jb_8.format_1;
					instr->e.ins_jb.m.jb_8.offset	= p->m.jb_8.offset;

					strcopy(instr->e.ins_jb.m.jb_8.label, p->m.jb_8.label);
					instr->e.ins_jb.m.jb_8.label[strlen(p->m.jb_8.label)]	= NULL;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	instr->k		= INS_STS_JB;

	instr->e.ins_jb.k	= p->k;
	instr->e.ins_jb.len	= p->len;

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
PUBLIC	struct ins_str *	ins_je_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_equal_build(s) -- \n");
#endif
//--------------------------

	struct pasm_exp *exp;

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	u32 reg, rm;
	s8 offset;
	struct ins_je *p;
	switch(exp->s)
	{
		case PASM_MEM:
			switch(exp->k)
			{
				case PASM_EXP_VAR:
					printf("ins_je_build::label=%s\n\n",exp->e.var.var_name);
					
					p	= ins_je_8_build(exp->e.var.var_name);

					instr->e.ins_je.m.je_8.format_1	= p->m.je_8.format_1;
					instr->e.ins_je.m.je_8.offset	= p->m.je_8.offset;

					strcopy(instr->e.ins_je.m.je_8.label, p->m.je_8.label);
					instr->e.ins_je.m.je_8.label[strlen(p->m.je_8.label)]	= NULL;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	instr->k		= INS_STS_JE;

	instr->e.ins_je.k	= p->k;
	instr->e.ins_je.len	= p->len;


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
PUBLIC	struct ins_str *	ins_jne_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_not_equal_build(s) -- \n");
#endif
//--------------------------

	struct pasm_exp *exp;

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	u32 reg, rm;
	s8 offset;
	struct ins_jne *p;
	switch(exp->s)
	{
		case PASM_MEM:
			switch(exp->k)
			{
				case PASM_EXP_VAR:
					printf("ins_jne_build::label=%s\n\n",exp->e.var.var_name);
					
					p	= ins_jne_8_build(exp->e.var.var_name);

					instr->e.ins_jne.m.jne_8.format_1	= p->m.jne_8.format_1;
					instr->e.ins_jne.m.jne_8.offset	= p->m.jne_8.offset;

					strcopy(instr->e.ins_jne.m.jne_8.label, p->m.jne_8.label);
					instr->e.ins_jne.m.jne_8.label[strlen(p->m.jne_8.label)]	= NULL;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	instr->k		= INS_STS_JNE;

	instr->e.ins_jne.k	= p->k;
	instr->e.ins_jne.len	= p->len;

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
PUBLIC	struct ins_str *	ins_jae_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_above_equal_build(s) -- \n");
#endif
//--------------------------

	struct pasm_exp *exp;

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	u32 reg, rm;
	s8 offset;
	struct ins_jae *p;
	switch(exp->s)
	{
		case PASM_MEM:
			switch(exp->k)
			{
				case PASM_EXP_VAR:
					printf("ins_jae_build::label=%s\n\n",exp->e.var.var_name);
					
					p	= ins_jae_8_build(exp->e.var.var_name);

					instr->e.ins_jae.m.jae_8.format_1	= p->m.jae_8.format_1;
					instr->e.ins_jae.m.jae_8.offset	= p->m.jae_8.offset;

					strcopy(instr->e.ins_jae.m.jae_8.label, p->m.jae_8.label);
					instr->e.ins_jae.m.jae_8.label[strlen(p->m.jae_8.label)]	= NULL;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	instr->k		= INS_STS_JAE;

	instr->e.ins_jae.k	= p->k;
	instr->e.ins_jae.len	= p->len;

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
PUBLIC	struct ins_str *	ins_jbe_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_low_equal_build(s) -- \n");
#endif
//--------------------------

	struct pasm_exp *exp;

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	u32 reg, rm;
	s8 offset;
	struct ins_jbe *p;
	switch(exp->s)
	{
		case PASM_MEM:
			switch(exp->k)
			{
				case PASM_EXP_VAR:
					printf("ins_jbe_build::label=%s\n\n",exp->e.var.var_name);
					
					p	= ins_jbe_8_build(exp->e.var.var_name);

					instr->e.ins_jbe.m.jbe_8.format_1	= p->m.jbe_8.format_1;
					instr->e.ins_jbe.m.jbe_8.offset	= p->m.jbe_8.offset;

					strcopy(instr->e.ins_jbe.m.jbe_8.label, p->m.jbe_8.label);
					instr->e.ins_jbe.m.jbe_8.label[strlen(p->m.jbe_8.label)]	= NULL;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	instr->k		= INS_STS_JBE;

	instr->e.ins_jbe.k	= p->k;
	instr->e.ins_jbe.len	= p->len;

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_low_equal_build(e) -- \n\n");
#endif
//--------------------------	
}

//===========================================================================
// ins_cmp_build
//===========================================================================
PUBLIC	struct ins_str *	ins_cmp_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_cmp_build(s) -- \n");
#endif
//--------------------------

	struct pasm_exp *exp;
	u32 reg=NULL;
	u32 rm=NULL;
	s32 data=NULL;
	struct ins_cmp *p;

	

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// dst
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	switch(exp->s)
	{
		case PASM_REG:
			//for test
			printf("ins_cmp_build::rm=%s\n\n",exp->e.var.var_name);

			rm	= chk_reg_i(exp->e.var.var_name);			
			break;

		default:
			break;
	}

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	// src
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	for(pexplist=pexplist->tail; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
		
	switch(exp->s)
	{
		case PASM_REG:
			reg	= chk_reg_i(exp->e.var.var_name);

			p	= ins_cmp_reg_2_reg_32_build(rm, reg);

			instr->e.ins_cmp.m.cmp_reg_2_reg_32.format_1	= p->m.cmp_reg_2_reg_32.format_1;
			instr->e.ins_cmp.m.cmp_reg_2_reg_32.format_2	= p->m.cmp_reg_2_reg_32.format_2;
			break;
		default:
			break;
	}

	instr->k		= INS_STS_CMP;

	instr->e.ins_cmp.k	= p->k;
	instr->e.ins_cmp.len	= p->len;

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_cmp_build(e) -- \n\n");
#endif
//--------------------------	
}

//===========================================================================
// ins_push_build
//===========================================================================
PUBLIC	struct ins_str *	ins_push_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_push_build(s) -- \n");
#endif
//--------------------------
	
	struct pasm_exp *exp;

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	

	//struct pasm_exp *exp = pexplist->exp;
	
	u32 reg, rm;
	s8 offset;
	struct ins_push *p;
	switch(exp->s)
	{
		case PASM_REG:
			reg	= chk_reg_i(exp->e.var.var_name);
			p	= ins_push_reg_32_build(reg);

			instr->e.ins_push.m.push_reg_32.format_1	= p->m.push_reg_32.format_1;
			break;

		case PASM_MEM:
			switch(exp->k)
			{
				case PASM_EXP_ADD:
					rm 	= chk_reg_i(exp->e.add.dst_name);
					offset	= s2h(exp->e.add.src_name);

					p	= ins_push_mem_32_build(rm, offset);

					instr->e.ins_push.m.push_mem_32.format_1	= p->m.push_mem_32.format_1;
					instr->e.ins_push.m.push_mem_32.format_2	= p->m.push_mem_32.format_2;
					instr->e.ins_push.m.push_mem_32.offset		= p->m.push_mem_32.offset;
					break;
				case PASM_EXP_SUB:					
					rm 	= chk_reg_i(exp->e.minus.dst_name);
					offset	= 0xFF - s2h(exp->e.minus.src_name) + 1;
					
					p	= ins_push_mem_32_build(rm, offset);

					instr->e.ins_push.m.push_mem_32.format_1	= p->m.push_mem_32.format_1;
					instr->e.ins_push.m.push_mem_32.format_2	= p->m.push_mem_32.format_2;
					instr->e.ins_push.m.push_mem_32.offset		= p->m.push_mem_32.offset;
					break;
				default:
					break;
			}
			break;
		case PASM_IMM:
			break;
		default:
			break;
	}

	instr->k		= INS_STS_PUSH;

	instr->e.ins_push.k	= p->k;
	instr->e.ins_push.len	= p->len;

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_push_build(e) -- \n\n");
#endif
//--------------------------	
}


//===========================================================================
// ins_pop_build
//===========================================================================
PUBLIC	struct ins_str *	ins_pop_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_pop_build(s) -- \n");
#endif
//--------------------------

	struct pasm_exp *exp;

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	u32 reg, rm;
	s8 offset;
	struct ins_pop *p;
	switch(exp->s)
	{
		case PASM_REG:
			reg	= chk_reg_i(exp->e.var.var_name);
			p	= ins_pop_reg_32_build(reg);

			instr->e.ins_pop.m.pop_reg_32.format_1	= p->m.pop_reg_32.format_1;
			break;

		default:
			break;
	}

	instr->k		= INS_STS_POP;

	instr->e.ins_pop.k	= p->k;
	instr->e.ins_pop.len	= p->len;

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_pop_build(e) -- \n\n");
#endif
//--------------------------	
}

//===========================================================================
// ins_jmp_build
//===========================================================================
PUBLIC	struct ins_str *	ins_jmp_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_jmp_build(s) -- \n");
#endif
//--------------------------

	struct pasm_exp *exp;

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	u32 reg, rm;
	s8 offset;
	struct ins_jmp *p;
	switch(exp->s)
	{
		case PASM_MEM:
			switch(exp->k)
			{
				case PASM_EXP_VAR:
					printf("ins_jmp_build::label=%s\n\n",exp->e.var.var_name);
					
					p	= ins_jmp_8_build(exp->e.var.var_name);

					instr->e.ins_jmp.m.jmp_8.format_1	= p->m.jmp_8.format_1;
					instr->e.ins_jmp.m.jmp_8.offset		= p->m.jmp_8.offset;

					strcopy(instr->e.ins_jmp.m.jmp_8.label, p->m.jmp_8.label);
					instr->e.ins_jmp.m.jmp_8.label[strlen(p->m.jmp_8.label)]	= NULL;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	instr->k		= INS_STS_JMP;

	instr->e.ins_jmp.k	= p->k;
	instr->e.ins_jmp.len	= p->len;

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_jmp_build(e) -- \n\n");
#endif
//--------------------------	
}



//===========================================================================
// chk_reg_i(s8 *name)
//===========================================================================
PUBLIC	u32	chk_reg_i(s8 *name)
{
	u32 i;
	for(i=0; i<REG_NUM; i++)
	{
		if(strcmp(name, &regs_32[i][0]))
		{
			return i;
		}
	}

	for(i=0; i<REG_NUM; i++)
	{
		if(strcmp(name, &regs_16[i][0]))
		{
			return i;
		}
	}

	struct symbol *	sym	= symtbl_search(name);
	if(sym)
	{
		return sym->val_i;
	}

	printf("error::no such register::%s !!! \n\n", name);
	exit(0);
}




//===========================================================================
// ins_int_build
//===========================================================================
PUBLIC	struct ins_str *	ins_int_build(struct pasm_explist *pexplist, struct ins_str * instr)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_int_build(s) -- \n");
#endif
//--------------------------

	struct pasm_exp *exp;

	for(; pexplist; pexplist=pexplist->tail)
	{
		if(exp = pexplist->exp)
		{
			break;
		}
	}
	
	u8 data;
	s8 offset;
	struct ins_int *p;
	switch(exp->s)
	{
		case PASM_IMM:
			data	= s2h(exp->e.var.var_name);	
			p	= ins_int_imm_8_build(data);

			instr->e.ins_int.m.int_imm_8.format_1	= p->m.int_imm_8.format_1;
			instr->e.ins_int.m.int_imm_8.data	= p->m.int_imm_8.data;			
			break;

		default:
			break;
	}

	instr->k		= INS_STS_INT;

	instr->e.ins_int.k	= p->k;
	instr->e.ins_int.len	= p->len;

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_int_build(e) -- \n\n");
#endif
//--------------------------	
}
