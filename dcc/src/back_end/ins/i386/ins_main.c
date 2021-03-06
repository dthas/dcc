//===========================================================================
// ins_main.c
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
#include	"dcc_graph.h"
#include	"dcc_ins.h"
#include	"dcc_prototype.h"

#define	INS_DEBUG


//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ins_main()
{
	printf("==================================================================\n");
	printf("	ins_main\n");
	printf("==================================================================\n");	

//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- print_ins -- (pcur_file=0x%x)\n",pcur_file);
#endif
//--------------------------

	icur_file	= file_build(NULL);

	ins_file_process(pcur_file, icur_file, gcurfile);
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ins_file_process(struct pasm_file *f, struct ins_file *i, struct graph_file *g)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_file_process -- \n");
#endif
//--------------------------
	for(; g; g=g->tail)
	{
		if(g->glist != NULL)
		{
			break;
		}
	}

	for(; f; f=f->tail, g=g->tail)
	{
		struct ins_stslist *istslist 	= ins_stslist_build(NULL);

		ins_stslist_process(f->stslist, istslist, g->glist);

		struct ins_file *ifile	= file_build(istslist);
		ins_add2file(ifile, i);
	}
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ins_stslist_process(struct pasm_stslist *stslist, struct ins_stslist *istslist, struct graph_list *glist)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("-- ins_stslist_process(glist=0x%x) -- \n\n", glist);
#endif
//--------------------------
	
	struct ins_sts *ists;

	for(; glist; glist=glist->tail)
	{
		if(glist->g != NULL)
		{
			break;
		}
	}

	for(; stslist; stslist=stslist->tail)
	{
		if(stslist->sts)
		{
			ists = ins_sts_process(stslist->sts, glist->g, istslist);	

			if(ists)
			{
				struct ins_stslist *ists_list 	= ins_stslist_build(ists);
				ins_add2stslist(ists_list, istslist);			
			}					
		}	
	}

	
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	struct ins_sts *	ins_sts_process(struct pasm_sts  *sts, struct graph *g, struct ins_stslist *istslist)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%5s %10s \n","","-- pasm_sts_process --");
#endif
//--------------------------

	if(sts)
	{
		struct ins_explist * iexplist = iexplist_build(NULL);
		u32 label;
		struct ins_sts *ists 	= NULL;

		switch(sts->k)
		{
			case PASM_LABEL_L:
				sts_kind= INS_LABEL_L;

				ins_label_l_list_process(sts->s.exp_sts.pexplist, iexplist, g);
				label	= INS_LABEL_L;
				ists	= ins_sts_build(label, iexplist);
				break;
			case PASM_LABEL_J:
				sts_kind= INS_LABEL_J;

				ins_label_j_list_process(sts->s.exp_sts.pexplist, iexplist, g);
				label	= INS_LABEL_J;
				ists	= ins_sts_build(label, iexplist);
				break;
			case PASM_JUMP_RETURN:
				sts_kind= INS_JUMP_RETURN;

				ins_jumplist_process(sts->s.exp_sts.pexplist, iexplist, g);
				label	= INS_JUMP_RETURN;
				ists	= ins_sts_build(label, iexplist);
				break;
			case PASM_EXP:
				sts_kind= INS_EXP;

				ins_explist_process(sts->s.exp_sts.pexplist, iexplist, g);
				label	= INS_EXP;
				ists	= ins_sts_build(label, iexplist);
				break;
			case PASM_SELECT:				
				ins_select_process(sts, iexplist, g, istslist);				
				ists = NULL;
				break;
			case PASM_ITERATION_FOR:
				ins_iteration_for_process(sts, iexplist, g, istslist);				
				ists = NULL;
				break;

			case PASM_ITERATION_WHILE:
				ins_iteration_while_process(sts, iexplist, g, istslist);				
				ists = NULL;
				break;
			case PASM_ITERATION_DOWHILE:
				ins_iteration_dowhile_process(sts, iexplist, g, istslist);				
				ists = NULL;
				break;
			default:
				break;
		}

		return ists;
	}
}


//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ins_select_process(struct pasm_sts *sts, struct ins_explist * iexplist, struct graph *g, struct ins_stslist *istslist)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%15s %10s\n","","-- ins_select_process --");
#endif
//--------------------------
	s8 *tl, *fl, *el;
	u32 label;
	struct ins_sts *ists 	= NULL;
	s8 flg_out = FALSE;

	tl = NULL;
	fl = NULL;
	el = NULL;

	//---------------------------------------------------------------------
	// get true label, false label, end label
	//---------------------------------------------------------------------
	struct pasm_explist *explist = sts->s.select_sts.pexplist;

	for(; explist; explist=explist->tail)
	{
		if(explist->exp)
		{
			switch(explist->exp->k)
			{
				case PASM_ABOVE:
					tl	= explist->exp->e.above.t_label;
					fl	= explist->exp->e.above.f_label;
					el	= explist->exp->e.above.e_label;

					flg_out	= TRUE;
					break;
				case PASM_LOW:
					tl	= explist->exp->e.low.t_label;
					fl	= explist->exp->e.low.f_label;
					el	= explist->exp->e.low.e_label;

					flg_out	= TRUE;
					break;
				case PASM_EQUAL:
					tl	= explist->exp->e.equal.t_label;
					fl	= explist->exp->e.equal.f_label;
					el	= explist->exp->e.equal.e_label;

					flg_out	= TRUE;
					break;
				case PASM_NOT_EQUAL:
					tl	= explist->exp->e.not_equal.t_label;
					fl	= explist->exp->e.not_equal.f_label;
					el	= explist->exp->e.not_equal.e_label;

					flg_out	= TRUE;
					break;
				case PASM_ABOVE_EQUAL:
					tl	= explist->exp->e.above_equal.t_label;
					fl	= explist->exp->e.above_equal.f_label;
					el	= explist->exp->e.above_equal.e_label;

					flg_out	= TRUE;
					break;
				case PASM_LOW_EQUAL:
					tl	= explist->exp->e.low_equal.t_label;
					fl	= explist->exp->e.low_equal.f_label;
					el	= explist->exp->e.low_equal.e_label;

					flg_out	= TRUE;
					break;
				default:
					break;
			}
			
		}

		if(flg_out)
		{
			break;
		}
	}	

	//---------------------------------------------------------------------
	//if exp
	//---------------------------------------------------------------------
	ins_explist_process(sts->s.select_sts.pexplist, iexplist, g);
	label	= INS_SELECT;
	ists	= ins_sts_build(label, iexplist);

	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}

	//---------------------------------------------------------------------
	//then sts
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_1 = iexplist_build(NULL);
	ins_label_s_build(tl, iexplist_1);
	label	= INS_LABEL_J;
	ists	= ins_sts_build(label, iexplist_1);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}

	ists	= ins_sts_process(sts->s.select_sts.then_sts, g, istslist);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}

	struct ins_explist * iexplist_10 = iexplist_build(NULL);
	ins_jump_build(el, iexplist_10);
	label	= INS_JMP;
	ists	= ins_sts_build(label, iexplist_10);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}

	//---------------------------------------------------------------------
	//else sts
	//---------------------------------------------------------------------
	if(fl)
	{
		struct ins_explist * iexplist_2 = iexplist_build(NULL);
		ins_label_s_build(fl, iexplist_2);
		label	= INS_LABEL_J;
		ists	= ins_sts_build(label, iexplist_2);
		if(ists)
		{
			struct ins_stslist *ists_list 	= ins_stslist_build(ists);
			ins_add2stslist(ists_list, istslist);			
		}

		ists	= ins_sts_process(sts->s.select_sts.else_sts, g, istslist);
		if(ists)
		{
			struct ins_stslist *ists_list 	= ins_stslist_build(ists);
			ins_add2stslist(ists_list, istslist);			
		}		
	}

	//---------------------------------------------------------------------
	//end label
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_3 = iexplist_build(NULL);
	ins_label_s_build(el, iexplist_3);
	label	= INS_LABEL_J;
	ists	= ins_sts_build(label, iexplist_3);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}
}


//===========================================================================
// ins_iteration_for_process
//===========================================================================
PUBLIC	void	ins_iteration_for_process(struct pasm_sts *sts, struct ins_explist * iexplist, struct graph *g, struct ins_stslist *istslist)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%15s %10s\n","","-- ins_iteration_for_process --");
#endif
//--------------------------
	s8 *tl, *fl, *el, *ll;
	u32 label;
	struct ins_sts *ists 	= NULL;

	s8 flg_out = FALSE;

	tl = NULL;
	fl = NULL;
	el = NULL;

	ll = sts->s.for_sts.l_label;

	//---------------------------------------------------------------------
	// get true label, false label, end label
	//---------------------------------------------------------------------
	struct pasm_explist *explist = (sts->s.for_sts.cond_sts)->s.exp_sts.pexplist;

	for(; explist; explist=explist->tail)
	{
		if(explist->exp)
		{
			switch(explist->exp->k)
			{
				case PASM_ABOVE:
					tl	= explist->exp->e.above.t_label;
					fl	= explist->exp->e.above.f_label;
					el	= explist->exp->e.above.e_label;

					flg_out	= TRUE;
					break;
				case PASM_LOW:
					tl	= explist->exp->e.low.t_label;
					fl	= explist->exp->e.low.f_label;
					el	= explist->exp->e.low.e_label;

					flg_out	= TRUE;
					break;
				case PASM_EQUAL:
					tl	= explist->exp->e.equal.t_label;
					fl	= explist->exp->e.equal.f_label;
					el	= explist->exp->e.equal.e_label;

					flg_out	= TRUE;
					break;
				case PASM_NOT_EQUAL:
					tl	= explist->exp->e.not_equal.t_label;
					fl	= explist->exp->e.not_equal.f_label;
					el	= explist->exp->e.not_equal.e_label;

					flg_out	= TRUE;
					break;
				case PASM_ABOVE_EQUAL:
					tl	= explist->exp->e.above_equal.t_label;
					fl	= explist->exp->e.above_equal.f_label;
					el	= explist->exp->e.above_equal.e_label;

					flg_out	= TRUE;
					break;
				case PASM_LOW_EQUAL:
					tl	= explist->exp->e.low_equal.t_label;
					fl	= explist->exp->e.low_equal.f_label;
					el	= explist->exp->e.low_equal.e_label;

					flg_out	= TRUE;
					break;
				default:
					break;
			}
			
		}

		if(flg_out)
		{
			break;
		}
	}	

	//---------------------------------------------------------------------
	//init sts
	//---------------------------------------------------------------------
	ists	= ins_sts_process(sts->s.for_sts.init_sts, g, istslist);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}

	//---------------------------------------------------------------------
	//loop label(sts)
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_1 = iexplist_build(NULL);

	ins_label_s_build(ll, iexplist_1);
	label	= INS_LABEL_J;
	ists	= ins_sts_build(label, iexplist_1);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}	

	//---------------------------------------------------------------------
	//cond sts
	//---------------------------------------------------------------------
	ists	= ins_sts_process(sts->s.for_sts.cond_sts, g, istslist);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}	

	//---------------------------------------------------------------------
	//sts
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_3 = iexplist_build(NULL);
	ins_label_s_build(tl, iexplist_3);
	label	= INS_LABEL_J;
	ists	= ins_sts_build(label, iexplist_3);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}	
	
	ists	= ins_sts_process(sts->s.for_sts.sts, g, istslist);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}

	//---------------------------------------------------------------------
	//next exp
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_4 = iexplist_build(NULL);
	ins_explist_process(sts->s.for_sts.next_pexplist, iexplist_4, g);
	label	= INS_EXP;
	ists	= ins_sts_build(label, iexplist_4);

	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}

	//---------------------------------------------------------------------
	// jmp true label
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_5 = iexplist_build(NULL);
	ins_jump_build(ll, iexplist_5);
	label	= INS_JMP;
	ists	= ins_sts_build(label, iexplist_5);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}

	//---------------------------------------------------------------------
	// false label
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_6 = iexplist_build(NULL);
	ins_label_s_build(fl, iexplist_6);
	label	= INS_LABEL_J;
	ists	= ins_sts_build(label, iexplist_6);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}	

	//---------------------------------------------------------------------
	//end label
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_7 = iexplist_build(NULL);
	ins_label_s_build(el, iexplist_7);
	label	= INS_LABEL_J;
	ists	= ins_sts_build(label, iexplist_7);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}	
}


//===========================================================================
// ins_iteration_while_process
//===========================================================================
PUBLIC	void	ins_iteration_while_process(struct pasm_sts *sts, struct ins_explist * iexplist, struct graph *g, struct ins_stslist *istslist)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%15s %10s\n","","-- ins_iteration_while_process --");
#endif
//--------------------------
	s8 *tl, *fl, *el, *ll;
	u32 label;
	struct ins_sts *ists 	= NULL;

	s8 flg_out = FALSE;

	tl = NULL;
	fl = NULL;
	el = NULL;

	ll = sts->s.while_sts.l_label;

	//---------------------------------------------------------------------
	// get true label, false label, end label
	//---------------------------------------------------------------------
	struct pasm_explist *explist = sts->s.while_sts.cond_pexplist;

	for(; explist; explist=explist->tail)
	{
		if(explist->exp)
		{
			switch(explist->exp->k)
			{
				case PASM_ABOVE:
					tl	= explist->exp->e.above.t_label;
					fl	= explist->exp->e.above.f_label;
					el	= explist->exp->e.above.e_label;

					flg_out	= TRUE;
					break;
				case PASM_LOW:
					tl	= explist->exp->e.low.t_label;
					fl	= explist->exp->e.low.f_label;
					el	= explist->exp->e.low.e_label;

					flg_out	= TRUE;
					break;
				case PASM_EQUAL:
					tl	= explist->exp->e.equal.t_label;
					fl	= explist->exp->e.equal.f_label;
					el	= explist->exp->e.equal.e_label;

					flg_out	= TRUE;
					break;
				case PASM_NOT_EQUAL:
					tl	= explist->exp->e.not_equal.t_label;
					fl	= explist->exp->e.not_equal.f_label;
					el	= explist->exp->e.not_equal.e_label;

					flg_out	= TRUE;
					break;
				case PASM_ABOVE_EQUAL:
					tl	= explist->exp->e.above_equal.t_label;
					fl	= explist->exp->e.above_equal.f_label;
					el	= explist->exp->e.above_equal.e_label;

					flg_out	= TRUE;
					break;
				case PASM_LOW_EQUAL:
					tl	= explist->exp->e.low_equal.t_label;
					fl	= explist->exp->e.low_equal.f_label;
					el	= explist->exp->e.low_equal.e_label;

					flg_out	= TRUE;
					break;
				default:
					break;
			}
			
		}

		if(flg_out)
		{
			break;
		}
	}	

	//---------------------------------------------------------------------
	//loop label(sts)
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_1 = iexplist_build(NULL);

	ins_label_s_build(ll, iexplist_1);
	label	= INS_LABEL_J;
	ists	= ins_sts_build(label, iexplist_1);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}

	//---------------------------------------------------------------------
	//next exp
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_2 = iexplist_build(NULL);
	ins_explist_process(sts->s.while_sts.cond_pexplist, iexplist_2, g);
	label	= INS_SELECT;
	ists	= ins_sts_build(label, iexplist_2);

	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}

	//---------------------------------------------------------------------
	//sts
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_3 = iexplist_build(NULL);
	ins_label_s_build(tl, iexplist_3);
	label	= INS_LABEL_J;
	ists	= ins_sts_build(label, iexplist_3);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}
	
	ists	= ins_sts_process(sts->s.while_sts.sts, g, istslist);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}

	//---------------------------------------------------------------------
	// jmp true label
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_4 = iexplist_build(NULL);
	ins_jump_build(ll, iexplist_4);
	label	= INS_JMP;
	ists	= ins_sts_build(label, iexplist_4);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}

	//---------------------------------------------------------------------
	// false label
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_5 = iexplist_build(NULL);
	ins_label_s_build(fl, iexplist_5);
	label	= INS_LABEL_J;
	ists	= ins_sts_build(label, iexplist_5);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}	

	//---------------------------------------------------------------------
	//end label
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_6 = iexplist_build(NULL);
	ins_label_s_build(el, iexplist_6);
	label	= INS_LABEL_J;
	ists	= ins_sts_build(label, iexplist_6);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}	
}


//===========================================================================
// ins_iteration_dowhile_process
//===========================================================================
PUBLIC	void	ins_iteration_dowhile_process(struct pasm_sts *sts, struct ins_explist * iexplist, struct graph *g, struct ins_stslist *istslist)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%15s %10s\n","","-- ins_iteration_dowhile_process --");
#endif
//--------------------------
	s8 *tl, *fl, *el, *ll;
	u32 label;
	struct ins_sts *ists 	= NULL;

	s8 flg_out = FALSE;

	tl = NULL;
	fl = NULL;
	el = NULL;

	ll = sts->s.dowhile_sts.l_label;

	//---------------------------------------------------------------------
	// get true label, false label, end label
	//---------------------------------------------------------------------
	struct pasm_explist *explist = sts->s.dowhile_sts.cond_pexplist;

	for(; explist; explist=explist->tail)
	{
		if(explist->exp)
		{
			switch(explist->exp->k)
			{
				case PASM_ABOVE:
					tl	= explist->exp->e.above.t_label;
					fl	= explist->exp->e.above.f_label;
					el	= explist->exp->e.above.e_label;

					flg_out	= TRUE;
					break;
				case PASM_LOW:
					tl	= explist->exp->e.low.t_label;
					fl	= explist->exp->e.low.f_label;
					el	= explist->exp->e.low.e_label;

					flg_out	= TRUE;
					break;
				case PASM_EQUAL:
					tl	= explist->exp->e.equal.t_label;
					fl	= explist->exp->e.equal.f_label;
					el	= explist->exp->e.equal.e_label;

					flg_out	= TRUE;
					break;
				case PASM_NOT_EQUAL:
					tl	= explist->exp->e.not_equal.t_label;
					fl	= explist->exp->e.not_equal.f_label;
					el	= explist->exp->e.not_equal.e_label;

					flg_out	= TRUE;
					break;
				case PASM_ABOVE_EQUAL:
					tl	= explist->exp->e.above_equal.t_label;
					fl	= explist->exp->e.above_equal.f_label;
					el	= explist->exp->e.above_equal.e_label;

					flg_out	= TRUE;
					break;
				case PASM_LOW_EQUAL:
					tl	= explist->exp->e.low_equal.t_label;
					fl	= explist->exp->e.low_equal.f_label;
					el	= explist->exp->e.low_equal.e_label;

					flg_out	= TRUE;
					break;
				default:
					break;
			}
			
		}

		if(flg_out)
		{
			break;
		}
	}	

	//---------------------------------------------------------------------
	//sts
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_3 = iexplist_build(NULL);
	ins_label_s_build(tl, iexplist_3);
	label	= INS_LABEL_J;
	ists	= ins_sts_build(label, iexplist_3);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}
	
	ists	= ins_sts_process(sts->s.dowhile_sts.sts, g, istslist);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}

	//---------------------------------------------------------------------
	//next exp
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_2 = iexplist_build(NULL);
	ins_explist_process(sts->s.dowhile_sts.cond_pexplist, iexplist_2, g);
	label	= INS_SELECT;
	ists	= ins_sts_build(label, iexplist_2);

	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}

	//---------------------------------------------------------------------
	// false label
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_5 = iexplist_build(NULL);
	ins_label_s_build(fl, iexplist_5);
	label	= INS_LABEL_J;
	ists	= ins_sts_build(label, iexplist_5);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}	

	//---------------------------------------------------------------------
	//end label
	//---------------------------------------------------------------------
	struct ins_explist * iexplist_6 = iexplist_build(NULL);
	ins_label_s_build(el, iexplist_6);
	label	= INS_LABEL_J;
	ists	= ins_sts_build(label, iexplist_6);
	if(ists)
	{
		struct ins_stslist *ists_list 	= ins_stslist_build(ists);
		ins_add2stslist(ists_list, istslist);			
	}	
}

//===========================================================================
// ir_explist_process(struct ir_explist *explist)
//===========================================================================
PUBLIC	void	ins_explist_process(struct pasm_explist *explist, struct ins_explist * iexplist, struct graph *g)
{
//--------------------------
//test
#ifdef	PASM_DEBUG
	printf("%15s %10s\n","","-- ins_explist_process --");
#endif
//--------------------------

	for(; explist; explist=explist->tail)
	{
		if(explist->exp)
		{
			struct graph *g	= vertex_search_g(explist->exp->livelist);
			if(!g)
			{
				printf("[error]:ins_exp_process::g is NULL\n\n");
				exit(0);
			}			
			ins_exp_process(explist->exp, iexplist, g);
		}				
	}
}

//===========================================================================
// ins_label_l_list_process
//===========================================================================
PUBLIC	void	ins_label_l_list_process(struct pasm_explist *explist, struct ins_explist * iexplist, struct graph *g)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("%15s %10s\n","","-- ins_label_l_list_process --");
#endif
//--------------------------

	for(; explist; explist=explist->tail)
	{
		ins_exp_process(explist->exp, iexplist, g);		
	}
}

//===========================================================================
// ins_label_j_list_process
//===========================================================================
PUBLIC	void	ins_label_j_list_process(struct pasm_explist *explist, struct ins_explist * iexplist, struct graph *g)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("%15s %10s\n","","-- ins_label_j_list_process --");
#endif
//--------------------------

	for(; explist; explist=explist->tail)
	{
		ins_exp_process(explist->exp, iexplist, g);		
	}
}

//===========================================================================
// ins_jumplist_process
//===========================================================================
PUBLIC	void	ins_jumplist_process(struct pasm_explist *explist, struct ins_explist * iexplist, struct graph *g)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("%15s %10s\n","","-- ins_jumplist_process --");
#endif
//--------------------------	

	ins_jump_return_build(explist, iexplist);
}


//===========================================================================
// pasm_exp_process
//===========================================================================
PUBLIC	struct ins*	ins_exp_process(struct pasm_exp *exp, struct ins_explist * iexplist, struct graph *g)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("%20s %10s \n\n","","--ins_exp_process --");
#endif
//--------------------------

	s32 src_reg = NULL;
	s32 dst_reg = NULL;
	s8 *tl, *fl, *el;

	if(exp)
	{
		switch(exp->k)
		{
			case PASM_ADD:
				src_reg	= vertex_search_var(g, exp->e.add.src_id);
				dst_reg	= vertex_search_var(g, exp->e.add.dst_id);
				return ins_add_build(exp, iexplist, dst_reg, src_reg);							
				break;

			case PASM_MINUS:
				src_reg	= vertex_search_var(g, exp->e.minus.src_id);
				dst_reg	= vertex_search_var(g, exp->e.minus.dst_id);
				return ins_minus_build(exp, iexplist, src_reg, dst_reg);	
				break;

			case PASM_MUL:
				src_reg	= REG_EAX;
				dst_reg	= REG_EBX;
				return ins_mul_build(exp, iexplist, dst_reg, src_reg);		
				break;

			case PASM_DIV:				
				src_reg	= REG_EAX;
				dst_reg	= REG_EBX;
				return ins_div_build(exp, iexplist, src_reg, dst_reg);				
				break;

			case PASM_MOD:				
				src_reg	= REG_EAX;
				dst_reg	= REG_EBX;
				return ins_mod_build(exp, iexplist, src_reg, dst_reg);				
				break;			

			case PASM_CALL:
				return ins_call_build(exp, iexplist);
				break;

			case PASM_LABEL:
				return ins_label_build(exp, iexplist);
				break;

			case PASM_MOV:
				src_reg	= vertex_search_var(g, exp->e.move.res_id);
				return ins_move_build(exp, iexplist, src_reg);
				break;

			case PASM_MEM:
				//array bound is counted in pasm_main.c
				break;

			case PASM_CMP:
				
				break;

			case PASM_LOAD_MEM:
				//not use	
				break;
				

			case PASM_SAVE_MEM:
				//not use
				break;

			case PASM_JUMP:
				
				break;

			case PASM_ABOVE:
				src_reg	= vertex_search_var(g, exp->e.above.src_id);
				dst_reg	= vertex_search_var(g, exp->e.above.dst_id);
				tl	= exp->e.above.t_label;
				fl	= exp->e.above.f_label;
				el	= exp->e.above.e_label;
				return ins_above_build(exp, iexplist, dst_reg, src_reg, tl, fl, el);
				break;

			case PASM_LOW:
				src_reg	= vertex_search_var(g, exp->e.low.src_id);
				dst_reg	= vertex_search_var(g, exp->e.low.dst_id);
				tl	= exp->e.low.t_label;
				fl	= exp->e.low.f_label;
				el	= exp->e.low.e_label;
				return ins_low_build(exp, iexplist, dst_reg, src_reg, tl, fl, el);
				break;

			case PASM_EQUAL:
				src_reg	= vertex_search_var(g, exp->e.equal.src_id);
				dst_reg	= vertex_search_var(g, exp->e.equal.dst_id);
				tl	= exp->e.equal.t_label;
				fl	= exp->e.equal.f_label;
				el	= exp->e.equal.e_label;
				return ins_equal_build(exp, iexplist, dst_reg, src_reg, tl, fl, el);
				break;

			case PASM_NOT_EQUAL:
				src_reg	= vertex_search_var(g, exp->e.not_equal.src_id);
				dst_reg	= vertex_search_var(g, exp->e.not_equal.dst_id);
				tl	= exp->e.not_equal.t_label;
				fl	= exp->e.not_equal.f_label;
				el	= exp->e.not_equal.e_label;
				return ins_not_equal_build(exp, iexplist, dst_reg, src_reg, tl, fl, el);
				break;
	
			case PASM_ABOVE_EQUAL:
				src_reg	= vertex_search_var(g, exp->e.above_equal.src_id);
				dst_reg	= vertex_search_var(g, exp->e.above_equal.dst_id);
				tl	= exp->e.above_equal.t_label;
				fl	= exp->e.above_equal.f_label;
				el	= exp->e.above_equal.e_label;
				return ins_above_equal_build(exp, iexplist, dst_reg, src_reg, tl, fl, el);
				break;

			case PASM_LOW_EQUAL:
				src_reg	= vertex_search_var(g, exp->e.low_equal.src_id);
				dst_reg	= vertex_search_var(g, exp->e.low_equal.dst_id);
				tl	= exp->e.low_equal.t_label;
				fl	= exp->e.low_equal.f_label;
				el	= exp->e.low_equal.e_label;
				return ins_low_equal_build(exp, iexplist, dst_reg, src_reg, tl, fl, el);
				break;

			default:
				break;
		}
	}
}



//===========================================================================
// iexplist_build
//===========================================================================
PUBLIC	struct ins_explist *	iexplist_build(struct ins_exp *exp)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("	-- iexplist_build  -- \n");
#endif
//--------------------------

	struct ins_explist *ret_explist	= malloc(sizeof(struct ins_explist));

	if(!ret_explist)
	{
		printf("iexplist_build() malloc failed!!\n");
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
PUBLIC	s8	ins_add2explist(struct ins_explist *src, struct ins_explist * dst)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("	-- ins_add2explist  -- \n\n");
#endif
//--------------------------

	if(dst)
	{
		for(; dst->tail; dst=dst->tail)
		{}

		dst->tail	= src;
		src->head	= dst;
		src->tail	= NULL;
	}
}

//===========================================================================
// sts_build()
//===========================================================================
PUBLIC	struct ins_sts *	ins_sts_build(u32 kind, struct ins_explist *p)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("	-- ins_sts_build  -- \n");
#endif
//--------------------------

	struct ins_sts *ret_sts	= malloc(sizeof(struct ins_sts));

	if(!ret_sts)
	{
		printf("ins_sts() malloc failed!!\n");
		exit(1);
	}

	ret_sts->k	= kind;
	ret_sts->s.exp_sts.pexplist	= p;

	return ret_sts;
}

//===========================================================================
// stslist_build()
//===========================================================================
PUBLIC	struct ins_stslist *	ins_stslist_build(struct ins_sts *sts)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("	-- ins_stslist_build  -- \n");
#endif
//--------------------------

	struct ins_stslist *ret_stslist	= malloc(sizeof(struct ins_stslist));

	if(!ret_stslist)
	{
		printf("ins_stslist() malloc failed!!\n");
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
PUBLIC	s8	ins_add2stslist(struct ins_stslist *src, struct ins_stslist * dst)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("	-- ins_add2stslist(src=0x%x, dst=0x%x)  -- \n\n", src, dst);
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
PUBLIC	struct ins_file *	ins_file_build(struct ins_stslist *stslist)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("	-- ins_file_build  -- \n");
#endif
//--------------------------

	struct ins_file *ret_file	= malloc(sizeof(struct ins_file));

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
PUBLIC	s8	ins_add2file(struct ins_file *src, struct ins_file * dst)
{
//--------------------------
//test
#ifdef	INS_DEBUG
	printf("	-- ins_add2file  -- \n");
#endif
//--------------------------

	for(; dst->tail; dst=dst->tail)
	{}

	dst->tail	= src;
	src->head	= dst;
	src->tail	= NULL;
}

