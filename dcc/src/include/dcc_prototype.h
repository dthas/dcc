//===========================================================================
// dcc_prototype.h
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

#ifndef	_DCC_PROTOTYPE_H_
#define	_DCC_PROTOTYPE_H_

//pre
PUBLIC	void	pre_main(s8 *filename);

//pre_lex_state_tab.c
PUBLIC	void	pre_lex_char_statetab_init();

//pre_parse_state_tab.c
PUBLIC	void	pre_lex_word_statetab_init();

//lib.c
PUBLIC	void	empty_buf(u32 start_addr, u32 size_in_byte);
PUBLIC 	void 	strcopy(char *dest, char *src);
PUBLIC 	void 	strcpy(char *dest, char *src, s32 len);
PUBLIC 	void 	memcpy(u8 *dest, u8 *src, s32 len);
PUBLIC 	int 	strlen(char *buf);
PUBLIC 	s8 	strcmp(char *dest, char *src);
PUBLIC 	u8 	s2i(s8 * str);
PUBLIC 	u8 	c2i(s8 ch);
PUBLIC 	s32 	squ(s32 num, s32 ind);
PUBLIC	void 	push_t(char *buf, char val);
PUBLIC	void	clear_buf(char *buf, int len);
PUBLIC	void	i2s(int val, char *buf);
PUBLIC 	void 	h2s(int val, char *buf);
PUBLIC 	void 	i2h(int val, char *buf);

//symbol_main.c
PUBLIC	void	symtbl_init();
PUBLIC	void	symtbl_print();
PUBLIC	s8	symtbl_del(s8 *name);
PUBLIC	struct symbol *	symtbl_search(s8 *name);
PUBLIC	struct symbol *	symtbl_search_s(s8 *name, s32 scope_2);
PUBLIC	struct symbol *	symtbl_search_i(s32 id);
PUBLIC	void	symbol_empty(struct symbol *sym);
PUBLIC	void	symtbl_add_s(struct symbol *sym);
PUBLIC	s8	symtbl_add(s8 *name, s32 type_scs, s32 type_ts, s32 type_tq, s32 len, s8 flg_array, s8 flg_pointer, s8 flg_func, s32 val_i, s8 *val_s, s32 scope_1, s32 scope_2, u32 m_addr, s32 i_var_offset, s8* label, struct struct_union *su, struct parm_type_list *ptlist);
PUBLIC	s8	symtbl_upd(s8 *name, s32 type_scs, s32 type_ts, s32 type_tq, s32 len, s8 flg_array, s8 flg_pointer, s8 flg_func, s32 val_i, s8 *val_s, s32 scope_1, s32 scope_2, u32 m_addr, s32 i_var_offset,  s8* label, struct parm_type_list *ptlist);
PUBLIC	struct symbol *	symbol_crt(s8 *name, s32 type_scs, s32 type_ts, s32 type_tq, s32 len, s8 flg_array, s8 flg_pointer, s8 flg_func, s32 val_i, s8 *val_s, s32 scope_1, s32 scope_2, u32 m_addr, s32 i_var_offset, s8 *label, struct struct_union *su, struct parm_type_list *ptlist);
PUBLIC	void	symtbl_print_1(struct symbol *p);
PUBLIC	s8	symtbl_validate(struct symbol *sym);
PUBLIC	struct symbol *	symtbl_validate_s(s8 *name);
PUBLIC	void	ptlist_empty(struct parm_type_list *ptlist);
PUBLIC	void	ptlist_add_s(struct parm_type_list *ptlist);
PUBLIC 	s8 	parm_type_list_copy(struct parm_type_list *dest, struct parm_type_list *src);
PUBLIC	void	param_type_list_print(struct parm_type_list *ptlist);
PUBLIC	void	mblist_empty(struct member_list *mblist);
PUBLIC	void	mblist_add_s(struct member_list *mblist);
PUBLIC	void	mblist_add_t(struct member_list *src_mblist, struct member_list *dst_mblist);
PUBLIC 	s8 	struct_union_copy(struct struct_union *dst_su, struct struct_union *src_su);
PUBLIC	void	struct_union_print(struct struct_union *su);
PUBLIC	void	type_member_print(struct member_list *mblist);
PUBLIC	void	symbol_pre_set(struct symbol *sym);

//lex_main.c
PUBLIC	void 	lex_init();
PUBLIC	void	process();
PUBLIC	s32	add_tok(FILE *fr, s8 *word);
PUBLIC	void	lex_main();

//lex_lib.c
PUBLIC	void	tokenlist_print();
PUBLIC	void	tokenlist_add(s32 token, s8 *val_s);
PUBLIC	void	tokenlist_init();
PUBLIC	void	get_tok();
PUBLIC	void	uget_tok(s32 num);

// lex_char_state_tab.c
PUBLIC	void	lex_char_statetab_init();

// parse_main.c
PUBLIC	void	parse_init();
PUBLIC	void	parse();

//parse_production_tab.c
PUBLIC	void	parse_productiontab_init();

//parse_lib.c
PUBLIC	void	i_queue(s32 token_t);
PUBLIC	s32	o_queue();

//parse_func.c
PUBLIC	void	parse_entry();

//seman_main.c
PUBLIC	void	seman_init();

//seman_type.c
PUBLIC	void	init_typelist();
PUBLIC	s8	add_typelist(s32 true_type_id, s32 len, s8 *src_name, s8 *dst_name, struct member_list *mb);
PUBLIC	void	print_typelist();
PUBLIC	s8*	check_type_s(s32 type_id);
PUBLIC	s8*	check_type_s_1(s32 type_id);
PUBLIC	s32	check_type_i(s8 *name);
PUBLIC	s32	check_type_l(s32 type_id);
PUBLIC	struct s_type*	check_type_t(s32 type_id);
PUBLIC	struct s_type*	check_type_t_1(s32 type_id);

//seman_lib.c
PUBLIC	s8	is_struct();
PUBLIC	s8	is_pointer();
PUBLIC	s8	is_function();
PUBLIC	s8	is_array();

//ir_main.c
PUBLIC	void	ir_init();
PUBLIC	struct ir_file *	file_build(struct ir_stslist *stslist);
PUBLIC	s8	ir_add2file(struct ir_file *src, struct ir_file * dst);
PUBLIC	struct ir_stslist *	stslist_build(struct ir_sts *sts);
PUBLIC	s8	ir_add2stslist(struct ir_stslist *src, struct ir_stslist * dst);
PUBLIC	struct ir_explist *	explist_build(struct ir_exp *exp);
PUBLIC	s8	ir_add2explist(struct ir_explist *src, struct ir_explist * dst);
PUBLIC	struct ir_exp *	exp_build();
PUBLIC	struct ir_exp *	ir_const_exp_build(s32 num);
PUBLIC	struct ir_exp *	ir_string_exp_build(s8 *str);
PUBLIC	struct ir_exp *	ir_var_exp_build(struct s_var *v);
PUBLIC	struct ir_exp *	ir_fun_exp_build(s8 *func_name);
PUBLIC	struct ir_sts *	ir_expsts_build(struct ir_explist *explist);

PUBLIC	struct ir_exp*	ir_var_exp_update(struct ir_exp *exp, s8 *struct_member_name, s32 kind);
PUBLIC	struct ir_exp*	ir_var_exp_update_1(struct ir_exp *exp, s8 *struct_member_name);
PUBLIC	struct ir_exp*	ir_var_exp_update_2(struct ir_exp *exp, s8 *struct_member_name);

PUBLIC	struct ir_exp *	ir_const_exp_update(struct ir_exp *exp, s32 array_num);
PUBLIC	struct ir_exp *	ir_fun_exp_update(struct ir_exp *exp, s8* func_name);

PUBLIC	struct ir_exp *	ir_assign_exp_build(s32 op, struct ir_exp *res, struct ir_exp *val);
PUBLIC	struct ir_exp *	ir_cond_exp_build(struct ir_exp *cond, struct ir_exp *op_1, struct ir_exp *op_2);
PUBLIC	struct ir_exp *	ir_postfix_exp_build(s32 op, struct ir_exp *left, struct ir_exp *right);
PUBLIC	struct ir_exp *	ir_postfix_exp_update(struct ir_exp *postfix_exp, struct ir_exp *val);
PUBLIC	struct ir_exp *	ir_unary_exp_build(s32 op, struct ir_exp *left);
PUBLIC	struct ir_exp *	ir_label_exp_build(s8 *label_name, u32 label_id);
PUBLIC	struct ir_sts *	ir_labelsts_build(struct ir_explist *explist);
PUBLIC	struct ir_exp *	ir_null_exp_build(u32 val1, u32 val2, u32 val3);
PUBLIC	struct ir_sts *	ir_selectsts_build(struct ir_explist *explist, struct ir_sts *then_sts, struct ir_sts *else_sts);
PUBLIC	s8	ir_selectsts_update_1(struct ir_sts *sts, struct ir_explist *explist);
PUBLIC	s8	ir_selectsts_update_2(struct ir_sts *sts, struct ir_sts *then_sts);
PUBLIC	s8	ir_selectsts_update_3(struct ir_sts *sts, struct ir_sts *else_sts);
PUBLIC	struct ir_sts *ir_iteration_for_sts_build(struct ir_sts *init_sts,struct ir_sts *cond_sts,struct ir_explist *next_explist,struct ir_sts *sts);
PUBLIC	s8	ir_iteration_for_sts_update_1(struct ir_sts *sts, struct ir_sts *init_sts);
PUBLIC	s8	ir_iteration_for_sts_update_2(struct ir_sts *sts, struct ir_sts *cond_sts);
PUBLIC	s8	ir_iteration_for_sts_update_3(struct ir_sts *sts, struct ir_explist *next_explist);
PUBLIC	s8	ir_iteration_for_sts_update_4(struct ir_sts *sts, struct ir_sts *sts_1);
PUBLIC	struct ir_sts *	ir_iteration_while_sts_build(struct ir_explist *cond_explist, struct ir_sts *sts);
PUBLIC	s8	ir_iteration_while_sts_update_1(struct ir_sts *sts, struct ir_explist *cond_explist);
PUBLIC	s8	ir_iteration_while_sts_update_2(struct ir_sts *sts, struct ir_sts *sts_1);
PUBLIC	struct ir_sts *	ir_iteration_dowhile_sts_build(struct ir_explist *cond_explist, struct ir_sts *sts);
PUBLIC	s8	ir_iteration_dowhile_sts_update_1(struct ir_sts *sts, struct ir_explist *cond_explist);
PUBLIC	s8	ir_iteration_dowhile_sts_update_2(struct ir_sts *sts, struct ir_sts *sts_1);

//ir_list_lib.c
PUBLIC	void	ir_file_print(struct ir_file *f);
PUBLIC	void	ir_pvlist_print(struct ir_pvlist *pvlist);
PUBLIC	void	ir_var_print(struct ir_exp* exp);
PUBLIC	void	ir_exp_print(struct ir_exp *exp);
PUBLIC	void	ir_explist_print(struct ir_explist *explist);
PUBLIC	void	ir_labellist_print(struct ir_explist *explist);
PUBLIC	void	ir_select_print(struct ir_explist *explist, struct ir_sts *then_sts, struct ir_sts *else_sts);
PUBLIC	void	ir_iteration_for_print(struct ir_sts *sts);
PUBLIC	void	ir_iteration_while_print(struct ir_sts *sts);
PUBLIC	void	ir_iteration_dowhile_print(struct ir_sts *sts);

//pasm_main.c
PUBLIC	void	pasm_main();
PUBLIC	void	pasm_stslist_process(struct ir_stslist *stslist, struct pasm_stslist *pstslist);
PUBLIC	struct pasm_sts *	pasm_sts_process(struct ir_sts *sts);
PUBLIC	void	pasm_explist_process(struct ir_explist *explist, struct pasm_explist *pexplist);

PUBLIC	struct pasm_explist *	pexplist_build(struct pasm_exp *exp);
PUBLIC	s8	pasm_add2explist(struct pasm_explist *src, struct pasm_explist * dst);
PUBLIC	struct pasm_sts *	pasm_sts_build(u32 kind, struct pasm_explist *p);
PUBLIC	struct pasm_stslist *	pasm_stslist_build(struct pasm_sts *sts);
PUBLIC	s8	pasm_add2stslist(struct pasm_stslist *src, struct pasm_stslist * dst);
PUBLIC	void	pasm_file_process(struct ir_file *f, struct pasm_file *pf);
PUBLIC	s8	pasm_add2file(struct pasm_file *src, struct pasm_file * dst);
PUBLIC	struct pasm_exp *	pasm_exp_process(struct ir_exp *exp, struct pasm_explist *pexplist);
PUBLIC	struct pasm_file *	pasm_file_build(struct pasm_stslist *stslist);
PUBLIC	struct pasm_sts *	pasm_select_process(struct ir_sts *sts);
PUBLIC	struct pasm_sts *	pasm_iteration_for_process(struct ir_sts *sts);
PUBLIC	struct pasm_sts *	pasm_iteration_while_process(struct ir_sts *sts);
PUBLIC	struct pasm_sts *	pasm_iteration_dowhile_process(struct ir_sts *sts);

//pasm_lib.c
PUBLIC	struct pasm_exp *	add(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name);
PUBLIC	struct pasm_exp *	minus(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name);
PUBLIC	struct pasm_exp*	mul(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name);
PUBLIC	struct pasm_exp*	div(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name);
PUBLIC	struct pasm_exp*	mod(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name);
PUBLIC	struct pasm_exp *	move(s32 res_id, u32 res_addr, u32 res_type_len, u32 val_addr, u32 val_type_len, s8 *res_name, s8* val_name);
PUBLIC	struct pasm_exp *	cmp(u32 left, u32 left_id,u32 left_len, u32 right, u32 right_id, u32 right_len, u32 op);
PUBLIC	struct pasm_exp *	jump(struct pasm_exp  *cond, u32 label_1, u32 label_2);
PUBLIC	struct pasm_exp *	mem(s32 id, u32 *addr, u32 type_len, u32 num, s8 *name);
PUBLIC	struct pasm_exp *	load(s32 id, u32 *addr, u32 type_len, u32 num);
PUBLIC	struct pasm_exp *	save(s32 id, u32 *addr, u32 type_len, u32 num, u32 val);
PUBLIC	struct pasm_exp *	call(s8* label, struct pasm_explist *ppv, u32 ret_len, u32 ret_addr);
PUBLIC	struct pasm_exp *	label(s8* label_name, u32 id);
PUBLIC	struct pasm_exp *	push(u32 var_addr, u32 var_type_len, s8 *name);
PUBLIC	struct pasm_exp *	pop(u32 var_addr, u32 var_type_len, s8 *name);

PUBLIC	struct pasm_exp* 	above(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl,s8 *fl, s8 *el);
PUBLIC	struct pasm_exp*	low(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl, s8 *fl, s8 *el);
PUBLIC	struct pasm_exp*	equal(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl, s8 *fl, s8 *el);
PUBLIC	struct pasm_exp*	not_equal(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl, s8 *fl, s8 *el);
PUBLIC	struct pasm_exp*	above_equal(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl, s8 *fl, s8 *el);
PUBLIC	struct pasm_exp*	low_equal(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl, s8 *fl, s8 *el);

//pasm_lib_t.c
PUBLIC	void	pr_pasm_main();
PUBLIC	void	pr_pasm_file_process(struct pasm_file *f);
PUBLIC	void	pr_pasm_stslist_process(struct pasm_stslist *stslist);
PUBLIC	void	pr_pasm_sts_process(struct pasm_sts  *sts);
PUBLIC	void	pr_pasm_explist_process(struct pasm_explist *explist);
PUBLIC	void	pr_pasm_exp_process(struct pasm_exp *exp);
PUBLIC	void	pr_pasm_labellist_process(struct pasm_explist *explist);

//frame.c
PUBLIC	void	frame_init();
PUBLIC	struct s_frame*	framelist_search_s(s8 *name);
PUBLIC	s8	fun_build(struct symbol *sym);
PUBLIC	s8	frame_build(struct symbol *sym);
PUBLIC	s8	frame_upd_funcid(s8 *name, s32 sym_id);
PUBLIC	s8	printvarlist_in_frame(struct s_frame *fr);
PUBLIC	s8	printframelist();

//var.c
PUBLIC	void	var_init();
PUBLIC	struct s_var*	var_build(struct symbol *sym);
PUBLIC	struct s_var *	var_build_1(s8* name, s32 true_type_id, s32 type_id, s32 offset, s32 len, s32 len_1, s32 total_len, s32 var_id);
PUBLIC	s8	add_var2frame(struct s_var *var, struct s_frame *fr);
PUBLIC	s8	add_var2varlist(struct s_var *var, struct s_varlist *p);
PUBLIC	struct s_var*	search_var_s(s8 *name);
PUBLIC	s8	printvarlist(struct s_varlist *p);
PUBLIC	s8	print_g_varlist();
PUBLIC	struct ir_pvlist*	pvlist_build(struct ir_exp *exp);
PUBLIC	s8	add2pvlist(struct ir_explist *srclist, struct ir_explist *dstlist);

//block_main.c
PUBLIC	void	block_main();
PUBLIC	void	block_file_process(struct pasm_file *f);
PUBLIC	s8	block_stslist_process(struct pasm_stslist *stslist);
PUBLIC	s8	block_sts_process(struct pasm_sts  *sts);

//block_lib.c
PUBLIC	struct block*	block_build(struct pasm_stslist *stslist);
PUBLIC	s8	add2block(struct block *src, struct block *dst);
PUBLIC	struct blocklist*	blocklist_build(struct block *block);
PUBLIC	s8	add2blocklist(struct blocklist *src, struct blocklist *dst);

//block_lib_t.c
PUBLIC	void	pr_block_main();
PUBLIC	void	pr_block_file_process(struct pasm_file *f);
PUBLIC	void	pr_block_stslist_process(struct pasm_stslist *stslist);
PUBLIC	void	pr_block_sts_process(struct pasm_sts  *sts);
PUBLIC	void	pr_block_labellist_process(struct pasm_explist *explist);
PUBLIC	void	pr_block_explist_process(struct pasm_explist *explist);
PUBLIC	void	pr_block_exp_process(struct pasm_exp *exp);

//live_main.c
PUBLIC	void	live_main();
PUBLIC	void	live_file_process(struct pasm_file *f, struct live_file *lf);
PUBLIC	s8	live_stslist_process(struct pasm_stslist *stslist, struct live_block * lb);
PUBLIC	s8	live_sts_process(struct pasm_sts  *sts, struct live_block * lb);
PUBLIC	void	live_labellist_process(struct pasm_explist *explist, struct live_list *livelist);
PUBLIC	void	live_explist_process(struct pasm_explist *explist, struct live_list *livelist);
PUBLIC	void	live_exp_process(struct pasm_exp *exp, struct pasm_explist *cur_explist, struct live_list *live_list);

//live_lib.c
PUBLIC	struct live *	live_build();
PUBLIC	struct livelist *	livelist_build(struct live *live);
PUBLIC	s8	live_add2list(struct live_list *src, struct live_list *dst);
PUBLIC	s8	ref_check(s32 var_id, struct pasm_explist *explist);
PUBLIC	s8	ref_check_1(struct pasm_exp *exp, s32 var_id);
PUBLIC	struct live_file *	live_file_build(struct live_block *liveblock);
PUBLIC	s8	live_add2file(struct live_file *src, struct live_file * dst);
PUBLIC	struct live_block *	live_block_build(struct live_list *livelist);
PUBLIC	s8	live_add2block(struct live_block *src, struct live_block * dst);

//live_lib_t.c
PUBLIC	void	pr_live_main();
PUBLIC	void	pr_live_file_process(struct live_file *f);
PUBLIC	void	pr_live_stslist_process(struct live_block *liveblock);
PUBLIC	void	pr_live_sts_process(struct live_list *llist);
PUBLIC	void	pr_live_exp_process(struct live *live);

//graph_main.c
PUBLIC	void	graph_main();
PUBLIC	void	graph_file_process(struct live_file *f, struct graph_file *gf);
PUBLIC	void	graph_stslist_process(struct live_block *liveblock, struct graph_list *glist);
PUBLIC	void	graph_sts_process(struct live_list *llist, struct graph *g);
PUBLIC	void	graph_exp_process(struct live *live, struct vertex_list *vlist);

//graph_lib.c
PUBLIC	struct vertex *	vertex_build(s32 v_id);
PUBLIC	struct vertex_list *	vertexlist_build(struct vertex *v);
PUBLIC	s8	vertex_add2list(struct vertex_list *src, struct vertex_list *dst);
PUBLIC	struct edge *	edge_build(struct vertex *v1, struct vertex *v2);
PUBLIC	s8	edge_add2list(struct edge_list *src, struct edge_list * dst);
PUBLIC	struct graph *	graph_build(struct vertex_list *vlist, struct edge_list *elist);
PUBLIC	struct graph_list *	graphlist_build(struct graph *g);
PUBLIC	s8	graph_add2list(struct graph_list *src, struct graph_list * dst);
PUBLIC	struct graph_file *	graph_file_build(struct graph_list *glist);
PUBLIC	s8	graph_add2file(struct graph_file *src, struct graph_file * dst);
PUBLIC	struct edge_list *	edge_search_v(struct graph *g, struct vertex *v1, struct vertex *v2);
PUBLIC	struct edge_list* edge_search_e(struct graph *g, struct edge *e);
PUBLIC	s8	edge_delete_e(struct graph *g, struct edge *e);
PUBLIC	s8	edge_delete_v(struct graph *g, struct vertex *v1, struct vertex *v2);
PUBLIC	struct vertex_list *	vertex_search(struct graph *g, struct vertex *v);
PUBLIC	s8	vertex_delete(struct graph *g, struct vertex *v);
PUBLIC	struct edge_list *	edgelist_build(struct edge *e);
PUBLIC	s32	vertex_search_var(struct graph *g, s32 var_id);
PUBLIC	struct graph *	vertex_search_g(struct live_list *livelist);

//graph_lib_t.c
PUBLIC	void	pr_graph_main();
PUBLIC	void	pr_graph_file_process(struct graph_file *f);
PUBLIC	void	pr_graph_stslist_process(struct graph_list *glist);
PUBLIC	void	pr_graph_sts_process(struct graph *g);
PUBLIC	void	pr_graph_vertex_process(struct vertex *v);
PUBLIC	void	pr_graph_edge_process(struct edge *e);

//alloc_main.c
PUBLIC	void	alloc_main();
PUBLIC	void	alloc_file_process(struct graph_file *f);
PUBLIC	void	alloc_stslist_process(struct graph_list *glist);
PUBLIC	void	alloc_sts_process(struct graph *g);

//pr_alloc_main.c
PUBLIC	void	pr_alloc_main();
PUBLIC	void	pr_alloc_file_process(struct graph_file *f);
PUBLIC	void	pr_alloc_stslist_process(struct graph_list *glist);
PUBLIC	void	pr_alloc_sts_process(struct graph *g);

//alloc_lib.c
PUBLIC	s8 	regs_reset();
PUBLIC	s8 	reg_reset(s32 reg_index);
PUBLIC	s8 	reg_lock(s32 reg_index, s32 var_id);
PUBLIC	s32	reg_select(s32 var_id);
PUBLIC	s32	reg_status_check();
PUBLIC	s32	reg_spill(struct graph *g, struct vertex_list *v_src);

//ins_main.c
PUBLIC	void	ins_main();
PUBLIC	struct ins*	ins_exp_process(struct pasm_exp *exp, struct ins_explist * iexplist, struct graph *g);
PUBLIC	struct ins_explist *	iexplist_build(struct ins_exp *exp);
PUBLIC	s8	ins_add2explist(struct ins_explist *src, struct ins_explist * dst);
PUBLIC	struct ins_sts *	ins_sts_build(u32 kind, struct ins_explist *p);
PUBLIC	struct ins_stslist *	ins_stslist_build(struct ins_sts *sts);
PUBLIC	s8	ins_add2stslist(struct ins_stslist *src, struct ins_stslist * dst);
PUBLIC	struct ins_file *	ins_file_build(struct ins_stslist *stslist);
PUBLIC	s8	ins_add2file(struct ins_file *src, struct ins_file * dst);
PUBLIC	void	ins_jumplist_process(struct pasm_explist *explist, struct ins_explist * iexplist, struct graph *g);
PUBLIC	void	ins_label_l_list_process(struct pasm_explist *explist, struct ins_explist * iexplist, struct graph *g);
PUBLIC	void	ins_label_j_list_process(struct pasm_explist *explist, struct ins_explist * iexplist, struct graph *g);
PUBLIC	void	ins_explist_process(struct pasm_explist *explist, struct ins_explist * iexplist, struct graph *g);
PUBLIC	struct ins_sts *	ins_sts_process(struct pasm_sts  *sts, struct graph *g, struct ins_stslist *istslist);
PUBLIC	void	ins_stslist_process(struct pasm_stslist *stslist, struct ins_stslist *istslist, struct graph_list *glist);
PUBLIC	void	ins_file_process(struct pasm_file *f, struct ins_file *i, struct graph_file *g);
PUBLIC	void	ins_select_process(struct pasm_sts *sts, struct ins_explist * iexplist, struct graph *g, struct ins_stslist *istslist);
PUBLIC	void	ins_iteration_for_process(struct pasm_sts *sts, struct ins_explist * iexplist, struct graph *g, struct ins_stslist *istslist);
PUBLIC	void	ins_iteration_while_process(struct pasm_sts *sts, struct ins_explist * iexplist, struct graph *g, struct ins_stslist *istslist);
PUBLIC	void	ins_iteration_dowhile_process(struct pasm_sts *sts, struct ins_explist * iexplist, struct graph *g, struct ins_stslist *istslist);

//ins_lib.c
PUBLIC	struct ins*	ins_add_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst);
PUBLIC	struct ins*	ins_minus_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst);
PUBLIC	struct ins*	ins_mul_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst);
PUBLIC	struct ins*	ins_div_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst);
PUBLIC	struct ins*	ins_mod_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst);
PUBLIC	struct ins*	ins_move_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_val);
PUBLIC	struct ins*	ins_label_build(struct pasm_exp *exp, struct ins_explist * iexplist);
PUBLIC	struct ins*	ins_call_build(struct pasm_exp *exp, struct ins_explist * iexplist);
PUBLIC	struct ins*	ins_jump_return_build(struct pasm_explist *explist, struct ins_explist * iexplist);
PUBLIC	struct ins*	ins_jump_build(s8 *target, struct ins_explist * iexplist);
PUBLIC	struct ins*	ins_above_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst, s8 *tl, s8 *fl, s8 *el);
PUBLIC	struct ins*	ins_low_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst, s8 *tl, s8 *fl, s8 *el);
PUBLIC	struct ins*	ins_equal_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst, s8 *tl, s8 *fl, s8 *el);
PUBLIC	struct ins*	ins_not_equal_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst, s8 *tl, s8 *fl, s8 *el);
PUBLIC	struct ins*	ins_above_equal_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst, s8 *tl, s8 *fl, s8 *el);
PUBLIC	struct ins*	ins_low_equal_build(struct pasm_exp *exp, struct ins_explist * iexplist, u32 reg_src, u32 reg_dst, s8 *tl, s8 *fl, s8 *el);

//ins_lib_t.c
PUBLIC	void	pr_ins_main();
PUBLIC	void	pr_ins_file_process(struct ins_file *f);
PUBLIC	void	pr_ins_stslist_process(struct ins_stslist *stslist);
PUBLIC	void	pr_ins_sts_process(struct ins_sts  *sts);
PUBLIC	void	pr_ins_label_l_list_process(struct ins_explist *explist);
PUBLIC	void	pr_ins_label_j_list_process(struct ins_explist *explist);
PUBLIC	void	pr_ins_explist_process(struct ins_explist *explist);
PUBLIC	void	pr_ins_exp_process(struct ins_exp *exp);
PUBLIC	void	pr_ins_label_process(struct ins_exp *exp);

//asm_file.c
PUBLIC	void	pr_asm_main(FILE *foutput);
PUBLIC	void	pr_asm_file_process(struct ins_file *f, FILE *foutput);
PUBLIC	void	pr_asm_stslist_process(struct ins_stslist *stslist, FILE *foutput);
PUBLIC	void	pr_asm_sts_process(struct ins_sts  *sts, FILE *foutput);
PUBLIC	void	pr_asm_label_l_list_process(struct ins_explist *explist, FILE *foutput);
PUBLIC	void	pr_asm_label_j_list_process(struct ins_explist *explist, FILE *foutput);;
PUBLIC	void	pr_asm_explist_process(struct ins_explist *explist, FILE *foutput);
PUBLIC	void	pr_asm_exp_process(struct ins_exp *exp, FILE *foutput);
PUBLIC	void	pr_asm_label_l_process(struct ins_exp *exp, FILE *foutput);
PUBLIC	void	pr_asm_label_j_process(struct ins_exp *exp, FILE *foutput);
PUBLIC	void	pr_asm_jmp_process(struct ins_exp *exp, FILE *foutput);
PUBLIC	void	pr_asm_jmplist_process(struct ins_explist *explist, FILE *foutput);

//asm_main.c
PUBLIC	void	asm_main();
PUBLIC	void	pr_asm_title(FILE *foutput);
PUBLIC	void	pr_asm_var(FILE *foutput);

//external functions
PUBLIC	s32 printf_exec(char *cmd, char *value);
PUBLIC	s32 prints(char *cmd, ...);
PUBLIC	dcc_ex_write(int fd, const void *buf, int count);
PUBLIC	s32 	printcr();
#endif
