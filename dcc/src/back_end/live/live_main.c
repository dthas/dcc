//===========================================================================
// live_main.c
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
#include	"dcc_block.h"
#include	"dcc_live.h"
#include	"dcc_prototype.h"

#define	LIVE_DEBUG

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	live_main()
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("-- live main ----");
#endif
//--------------------------

	lcur_file	= live_file_build(NULL);

	live_file_process(pcur_file, lcur_file);
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	live_file_process(struct pasm_file *f, struct live_file *lf)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("-- live_file_process -- \n");
#endif
//--------------------------
	s8 flg = FALSE;

	for(; f; f=f->tail)
	{
		struct live_block * lb = live_block_build(NULL);

		live_stslist_process(f->stslist, lb);
		struct live_file *lfile 	= live_file_build(lb);
		live_add2file(lfile, lf);
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	s8	live_stslist_process(struct pasm_stslist *stslist, struct live_block * lb)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("-- live_stslist_process -- \n");
#endif
//--------------------------
	
	for(; stslist; stslist=stslist->tail)
	{
		if(stslist->sts)
		{
			if(stslist->sts->k == PASM_LABEL_L)
			{
				continue;
			}
			live_sts_process(stslist->sts, lb);
		}				
	}	
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	s8	live_sts_process(struct pasm_sts  *sts, struct live_block * lb)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("%5s %10s \n","","-- live_sts_process --");
#endif
//--------------------------

	if(sts)
	{
		struct live_list *llist= livelist_build(NULL);

		switch(sts->k)
		{
			case PASM_LABEL_L:
			case PASM_LABEL_J:				
				break;
			case PASM_EXP:
				live_explist_process(sts->s.exp_sts.pexplist,llist);
				struct live_block *lb_s	= live_block_build(llist);
				if(lb_s)
				{
					live_add2block(lb_s, lb);
				}				
				break;
			case PASM_SELECT:
				live_explist_process(sts->s.select_sts.pexplist, llist);
				struct live_block *lb_s_1	= live_block_build(llist);
				if(lb_s_1)
				{
					live_add2block(lb_s_1, lb);
				}

				live_sts_process(sts->s.select_sts.then_sts, lb);

				if(sts->s.select_sts.else_sts)
				{
					live_sts_process(sts->s.select_sts.else_sts, lb);
				}				
				break;
			case PASM_ITERATION_FOR:
				if(sts->s.for_sts.init_sts)
				{
					live_sts_process(sts->s.for_sts.init_sts, lb);
				}

				if(sts->s.for_sts.cond_sts)
				{
					live_sts_process(sts->s.for_sts.cond_sts, lb);
				}				

				if(sts->s.for_sts.next_pexplist)
				{
					live_explist_process(sts->s.for_sts.next_pexplist, llist);
					struct live_block *lb_s_30	= live_block_build(llist);
					if(lb_s_30)
					{
						live_add2block(lb_s_30, lb);
					}
				}

				live_sts_process(sts->s.for_sts.sts, lb);				
				break;

			case PASM_ITERATION_WHILE:
				if(sts->s.while_sts.cond_pexplist)
				{
					live_explist_process(sts->s.while_sts.cond_pexplist, llist);
					struct live_block *lb_s_30	= live_block_build(llist);
					if(lb_s_30)
					{
						live_add2block(lb_s_30, lb);
					}
				}

				live_sts_process(sts->s.while_sts.sts, lb);				
				break;
			case PASM_ITERATION_DOWHILE:
				live_sts_process(sts->s.dowhile_sts.sts, lb);

				if(sts->s.dowhile_sts.cond_pexplist)
				{
					live_explist_process(sts->s.dowhile_sts.cond_pexplist, llist);
					struct live_block *lb_s_30	= live_block_build(llist);
					if(lb_s_30)
					{
						live_add2block(lb_s_30, lb);
					}
				}				
				break;
			default:
				break;
		}		
	}	
}


//===========================================================================
// live_labellist_process
//===========================================================================
PUBLIC	void	live_labellist_process(struct pasm_explist *explist, struct live_list *livelist)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("%15s %10s\n","","-- live_labellist_process --");
#endif
//--------------------------

	printf("\n=====================================================================================\n");
	printf("	New block(live):\n");
	printf("=====================================================================================\n");

	for(; explist; explist=explist->tail)
	{				
	}
}
//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	live_explist_process(struct pasm_explist *explist, struct live_list *livelist)
{
//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("%15s %10s\n","","-- live_explist_process --");
#endif
//--------------------------


	for(; explist; explist=explist->tail)
	{
		struct pasm_explist *cur_explist	= explist;

		if(explist->exp)
		{
			live_exp_process(explist->exp, cur_explist, livelist);			
		}				
	}	
}


//===========================================================================
// pasm_exp_process
//===========================================================================
PUBLIC	void	live_exp_process(struct pasm_exp *exp, struct pasm_explist *cur_explist, struct live_list *live_list)
{

//--------------------------
//test
#ifdef	LIVE_DEBUG
	printf("%20s %10s exp=%x, cur_elist=%x, llist=%x\n\n","","--live_exp_process --", exp, cur_explist, live_list);
#endif
//--------------------------

	s8 flg = FALSE;
	struct live *live	= NULL;
	struct live_list *llist	= NULL;
	struct pasm_explist *pl	= NULL;

	if(exp)
	{		
		exp->livelist	= live_list;

		switch(exp->k)
		{
			case PASM_ADD:
				//-------------------------------------------------------------------
				// src
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.add.src_id, cur_explist);
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.add.src_id;

					strcopy(live->name, exp->e.add.src_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}					
				}	
				//-------------------------------------------------------------------
				// dst
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.add.dst_id, cur_explist);				
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.add.dst_id;

					strcopy(live->name, exp->e.add.dst_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}			
			
				break;

			case PASM_MINUS:				
				//-------------------------------------------------------------------
				// src
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.minus.src_id, cur_explist);
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.minus.src_id;

					strcopy(live->name, exp->e.minus.src_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}	
				//-------------------------------------------------------------------
				// dst
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.minus.dst_id, cur_explist);				
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.minus.dst_id;

					strcopy(live->name, exp->e.minus.dst_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}			
			
				break;

			case PASM_MUL:				
				//-------------------------------------------------------------------
				// src
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.mul.src_id, cur_explist);
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.mul.src_id;

					strcopy(live->name, exp->e.mul.src_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}	
				//-------------------------------------------------------------------
				// dst
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.mul.dst_id, cur_explist);				
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.mul.dst_id;

					strcopy(live->name, exp->e.mul.dst_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}			
			
				break;
				
			case PASM_DIV:				
				//-------------------------------------------------------------------
				// src
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.div.src_id, cur_explist);
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.div.src_id;

					strcopy(live->name, exp->e.div.src_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}	
				//-------------------------------------------------------------------
				// dst
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.div.dst_id, cur_explist);				
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.div.dst_id;

					strcopy(live->name, exp->e.div.dst_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}			
			
				break;

			case PASM_MOD:				
				//-------------------------------------------------------------------
				// src
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.mod.src_id, cur_explist);
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.mod.src_id;

					strcopy(live->name, exp->e.mod.src_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}	
				//-------------------------------------------------------------------
				// dst
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.mod.dst_id, cur_explist);				
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.mod.dst_id;

					strcopy(live->name, exp->e.mod.dst_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}			
			
				break;

			case PASM_MEM:
				flg 	= ref_check(exp->e.mem.id, cur_explist);				
					
				if(flg)
				{
					live		= live_build();
					live->var_id	= exp->e.mem.id;

					strcopy(live->name, exp->e.mem.src_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}
				break;

			case PASM_CMP:
				//-------------------------------------------------------------------
				// left
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.cmp.left_id, cur_explist);
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.cmp.left_id;

					strcopy(live->name, exp->e.cmp.src_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}
				//-------------------------------------------------------------------
				// right
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.cmp.right_id, cur_explist);				
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.cmp.right_id;

					strcopy(live->name, exp->e.cmp.dst_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}			
			
				break;

			case PASM_LOAD_MEM:
				//	
				break;
				

			case PASM_SAVE_MEM:
				//
				break;

			case PASM_JUMP:
				//-------------------------------------------------------------------
				// left
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.jump.cond->e.cmp.left_id, cur_explist);				
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.jump.cond->e.cmp.left_id;

					strcopy(live->name, exp->e.jump.cond->e.cmp.src_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}
				
				//-------------------------------------------------------------------
				// right
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.jump.cond->e.cmp.right_id, cur_explist);
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.jump.cond->e.cmp.right_id;

					strcopy(live->name, exp->e.jump.cond->e.cmp.dst_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}
			
				break;

			case PASM_CALL:				
				pl	= exp->e.call.ppv;

				for(; pl; pl=pl->tail)
				{
					if(pl->exp)
					{
						flg 	= ref_check(pl->exp->e.mem.id, cur_explist);						
					
						if(flg)
						{
							live		= live_build();
							live->var_id	= pl->exp->e.mem.id;

							strcopy(live->name, exp->e.mem.src_name);
							live->name[strlen(live->name)]	= NULL;	

							llist	= livelist_build(live);						
		
							if(llist)
							{
								live_add2list(llist, live_list);
							}
						}
					}							
				}
				break;

			case PASM_LABEL:
				//
				break;

			case PASM_MOV:				
				//-------------------------------------------------------------------
				// res
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.move.res_id, cur_explist);				
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.move.res_id;

					strcopy(live->name, exp->e.move.res_name);
					live->name[strlen(live->name)]	= NULL;	
				
					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}	

				//-------------------------------------------------------------------
				// val
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.move.val, cur_explist);				
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.move.val;

					strcopy(live->name, exp->e.move.val_name);
					live->name[strlen(live->name)]	= NULL;	
				
					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}				
			
				break;

			case PASM_ABOVE:				
				//-------------------------------------------------------------------
				// src
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.above.src_id, cur_explist);
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.above.src_id;

					strcopy(live->name, exp->e.above.src_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}					
				}	
				//-------------------------------------------------------------------
				// dst
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.above.dst_id, cur_explist);				
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.above.dst_id;

					strcopy(live->name, exp->e.above.dst_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}			
			
				break;
			
			case PASM_LOW:				
				//-------------------------------------------------------------------
				// src
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.low.src_id, cur_explist);
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.low.src_id;

					strcopy(live->name, exp->e.low.src_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}	
				//-------------------------------------------------------------------
				// dst
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.low.dst_id, cur_explist);				
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.low.dst_id;

					strcopy(live->name, exp->e.low.dst_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}			
			
				break;

			case PASM_EQUAL:				
				//-------------------------------------------------------------------
				// src
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.equal.src_id, cur_explist);
				
				if(flg)
				{					
					live	= live_build();
					live->var_id	= exp->e.equal.src_id;

					strcopy(live->name, exp->e.equal.src_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}					
				}	
				//-------------------------------------------------------------------
				// dst
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.equal.dst_id, cur_explist);				
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.equal.dst_id;

					strcopy(live->name, exp->e.equal.dst_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}		
			
				break;

			case PASM_NOT_EQUAL:				
				//-------------------------------------------------------------------
				// src
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.not_equal.src_id, cur_explist);
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.not_equal.src_id;

					strcopy(live->name, exp->e.not_equal.src_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}	
				//-------------------------------------------------------------------
				// dst
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.not_equal.dst_id, cur_explist);				
				
				if(flg)
				{					
					live	= live_build();
					live->var_id	= exp->e.not_equal.dst_id;

					strcopy(live->name, exp->e.not_equal.dst_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}		
			
				break;

			case PASM_ABOVE_EQUAL:				
				//-------------------------------------------------------------------
				// src
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.above_equal.src_id, cur_explist);
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.above_equal.src_id;

					strcopy(live->name, exp->e.above_equal.src_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}	
				//-------------------------------------------------------------------
				// dst
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.above_equal.dst_id, cur_explist);				
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.above_equal.dst_id;

					strcopy(live->name, exp->e.above_equal.dst_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}		
			
				break;

			case PASM_LOW_EQUAL:				
				//-------------------------------------------------------------------
				// src
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.low_equal.src_id, cur_explist);
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.low_equal.src_id;

					strcopy(live->name, exp->e.low_equal.src_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}	
				//-------------------------------------------------------------------
				// dst
				//-------------------------------------------------------------------
				flg 	= ref_check(exp->e.low_equal.dst_id, cur_explist);				
				
				if(flg)
				{
					live	= live_build();
					live->var_id	= exp->e.low_equal.dst_id;

					strcopy(live->name, exp->e.low_equal.dst_name);
					live->name[strlen(live->name)]	= NULL;	

					llist	= livelist_build(live);
		
					if(llist)
					{
						live_add2list(llist, live_list);
					}
				}		
			
				break;

			default:
				break;
		}
	}
}
