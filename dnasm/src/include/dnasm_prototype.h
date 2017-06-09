//===========================================================================
// dnasm_prototype.h
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

#ifndef	_DNASM_PROTOTYPE_H_
#define	_DNASM_PROTOTYPE_H_

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
PUBLIC 	u8 	s2h(s8 * str);

//symbol_main.c
PUBLIC	void	symtbl_init();
PUBLIC	struct symbol *	symbol_crt(s8 *name, s32 type_scs, s32 type_ts, s32 len, s32 val_i, s8 *val_s, s8 *label, s8 flag, s8 attr);
PUBLIC	s8	symtbl_add(s8 *name, s32 type_scs, s32 type_ts, s32 len, s32 val_i, s8 *val_s, s8* label, s8 flag, s8 attr);
PUBLIC	s8	symtbl_validate(struct symbol *sym);
PUBLIC	struct symbol *	symtbl_validate_s(s8 *name);
PUBLIC	void	symtbl_add_s(struct symbol *sym);
PUBLIC	s8	symtbl_del(s8 *name);
PUBLIC	s8	symtbl_upd(s8 *name, s32 type_scs, s32 type_ts, s32 len, s32 val_i, s8 *val_s, s8* label, s8 flag, s8 attr);
PUBLIC	struct symbol *	symtbl_search(s8 *name);
PUBLIC	struct symbol *	symtbl_search_i(s32 id);
PUBLIC	void	symtbl_print();
PUBLIC	void	symbol_empty(struct symbol *sym);

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

//parse_func.c
PUBLIC	void	parse_entry();

//seman_main.c
PUBLIC	void	seman_init();

//seman_type.c
PUBLIC	void	init_typelist();
PUBLIC	s8	add_typelist(s32 true_type_id, s32 len, s8 *src_name, s8 *dst_name);
PUBLIC	void	print_typelist();
PUBLIC	s8*	check_type_s(s32 type_id);
PUBLIC	s8*	check_type_s_1(s32 type_id);
PUBLIC	s32	check_type_i(s8 *name);
PUBLIC	s32	check_type_l(s32 type_id);
PUBLIC	struct s_type*	check_type_t(s32 type_id);
PUBLIC	struct s_type*	check_type_t_1(s32 type_id);

//seman_lib.c


//ir_list.c
PUBLIC	void	ir_init();
PUBLIC	struct ir_file *	file_build(struct ir_stslist *stslist);
PUBLIC	s8	ir_add2file(struct ir_file *src, struct ir_file * dst);
PUBLIC	struct ir_stslist *	stslist_build(struct ir_sts *sts);
PUBLIC	s8	ir_add2stslist(struct ir_stslist *src, struct ir_stslist * dst);
PUBLIC	struct ir_explist *	explist_build(struct ir_exp *exp);
PUBLIC	s8	ir_add2explist(struct ir_explist *src, struct ir_explist * dst);
PUBLIC	struct ir_exp *	ir_const_exp_build(s32 num);
PUBLIC	struct ir_exp *	ir_string_exp_build(s8 *str);
PUBLIC	struct ir_exp *	ir_var_exp_build(struct s_var *v);
PUBLIC	struct ir_exp *	ir_postfix_exp_build(s32 op, struct ir_exp *left, struct ir_exp *right);
PUBLIC	struct ir_sts *	ir_movsts_build(struct ir_explist *explist);
PUBLIC	struct ir_sts *	ir_addsts_build(struct ir_explist *explist);
PUBLIC	struct ir_sts *	ir_substs_build(struct ir_explist *explist);
PUBLIC	struct ir_sts *	ir_mulsts_build(struct ir_explist *explist);
PUBLIC	struct ir_sts *	ir_divsts_build(struct ir_explist *explist);
PUBLIC	struct ir_sts *	ir_callsts_build(struct ir_explist *explist);
PUBLIC	struct ir_sts *	ir_retsts_build();
PUBLIC	struct ir_sts *	ir_jmpsts_build(struct ir_explist *explist);
PUBLIC	struct ir_sts *	ir_jasts_build(struct ir_explist *explist);
PUBLIC	struct ir_sts *	ir_jbsts_build(struct ir_explist *explist);
PUBLIC	struct ir_sts *	ir_jests_build(struct ir_explist *explist);
PUBLIC	struct ir_sts *	ir_jaests_build(struct ir_explist *explist);
PUBLIC	struct ir_sts *	ir_jbests_build(struct ir_explist *explist);
PUBLIC	struct ir_sts *	ir_jnests_build(struct ir_explist *explist);
PUBLIC	struct ir_sts *	ir_pushsts_build(struct ir_explist *explist);
PUBLIC	struct ir_sts *	ir_popsts_build(struct ir_explist *explist);
PUBLIC	struct ir_sts *	ir_cmpsts_build(struct ir_explist *explist);
PUBLIC	struct ir_exp *	ir_abop_exp_build(s32 op, struct ir_exp *left, struct ir_exp *right);
PUBLIC	struct ir_exp *	ir_label_exp_build(s8 *label_name, u32 label_id);
PUBLIC	struct ir_sts *	ir_labelsts_build(struct ir_explist *explist);
PUBLIC	struct ir_exp *	ir_relate_exp_build(s32 op, struct ir_exp *left, struct ir_exp *right);
PUBLIC	struct ir_sts *	ir_xorsts_build(struct ir_explist *explist);

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
PUBLIC	struct pasm_exp *	move(s32 res_id, u32 res_addr, u32 res_type_len, u32 val_addr, u32 val_type_len, s8 *res_name, s8* val_name);
PUBLIC	struct pasm_exp *	cmp(u32 left, u32 left_id,u32 left_len, u32 right, u32 right_id, u32 right_len, u32 op);
PUBLIC	struct pasm_exp *	jump(u32 label_1);
PUBLIC	struct pasm_exp *	call(u32 call_addr);
PUBLIC	struct pasm_exp *	push(u32 var_addr, u32 var_type_len, u32 reg,  s8 *name);
PUBLIC	struct pasm_exp *	pop(u32 var_addr, u32 var_type_len,  u32 reg, s8 *name);

PUBLIC	struct pasm_exp* 	above(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl,s8 *fl, s8 *el);
PUBLIC	struct pasm_exp*	low(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl, s8 *fl, s8 *el);
PUBLIC	struct pasm_exp*	equal(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl, s8 *fl, s8 *el);
PUBLIC	struct pasm_exp*	not_equal(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl, s8 *fl, s8 *el);
PUBLIC	struct pasm_exp*	above_equal(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl, s8 *fl, s8 *el);
PUBLIC	struct pasm_exp*	low_equal(u32 src, u32 src_id, u32 src_len, u32 dst, u32 dst_id, u32 dst_len, s8 *src_name, s8 *dst_name, s8 *tl, s8 *fl, s8 *el);
PUBLIC	struct pasm_exp *	label(s8* label_name, u32 id);

//pasm_lib_t.c
PUBLIC	void	pr_pasm_main();
PUBLIC	void	pr_pasm_file_process(struct pasm_file *f);
PUBLIC	void	pr_pasm_stslist_process(struct pasm_stslist *stslist);
PUBLIC	void	pr_pasm_sts_process(struct pasm_sts  *sts);
PUBLIC	void	pr_pasm_explist_process(struct pasm_explist *explist);
PUBLIC	void	pr_pasm_exp_process(struct pasm_exp *exp);
PUBLIC	void	pr_pasm_labellist_process(struct pasm_explist *explist);

//frame.c


//var.c
PUBLIC	void	var_init();
PUBLIC	struct s_var*	var_build(struct symbol *sym);
PUBLIC	struct s_var *	var_build_1(s8* name, s32 true_type_id, s32 type_id, s32 offset, s32 len, s32 var_id);
PUBLIC	s8	add_var2varlist(struct s_var *var, struct s_varlist *p);
PUBLIC	struct s_var*	search_var_s(s8 *name);
PUBLIC	s8	printvarlist(struct s_varlist *p);
PUBLIC	s8	print_g_varlist();

//ins_main.c
PUBLIC	void	ins_main();
PUBLIC	struct ins_str *	ins_exp_process(struct pasm_exp *exp, struct ins_explist * iexplist);
PUBLIC	struct ins_explist *	iexplist_build(struct ins_exp *exp);
PUBLIC	s8	ins_add2explist(struct ins_explist *src, struct ins_explist * dst);
PUBLIC	struct ins_sts *	ins_sts_build(u32 kind, struct ins_str *p);
PUBLIC	struct ins_stslist *	ins_stslist_build(struct ins_sts *sts);
PUBLIC	s8	ins_add2stslist(struct ins_stslist *src, struct ins_stslist * dst);
PUBLIC	struct ins_file *	ins_file_build(struct ins_stslist *stslist);
PUBLIC	s8	ins_add2file(struct ins_file *src, struct ins_file * dst);
PUBLIC	void	ins_jumplist_process(struct pasm_explist *explist, struct ins_explist * iexplist);
PUBLIC	void	ins_label_l_list_process(struct pasm_explist *explist, struct ins_explist * iexplist);
PUBLIC	void	ins_label_j_list_process(struct pasm_explist *explist, struct ins_explist * iexplist);
PUBLIC	void	ins_explist_process(struct pasm_explist *explist, struct ins_explist * iexplist);
PUBLIC	struct ins_sts *	ins_sts_process(struct pasm_sts  *sts, struct ins_stslist *istslist);
PUBLIC	void	ins_stslist_process(struct pasm_stslist *stslist, struct ins_stslist *istslist);
PUBLIC	void	ins_file_process(struct pasm_file *f, struct ins_file *i);

//ins_lib.c
PUBLIC	struct ins_str*	ins_add_build(struct pasm_explist *pexplist,struct ins_str *instr);
PUBLIC	struct ins_str*	ins_sub_build(struct pasm_explist *pexplist,struct ins_str *instr);
PUBLIC	struct ins_str*	ins_mul_build(struct pasm_explist *pexplist,struct ins_str *instr);
PUBLIC	struct ins_str*	ins_div_build(struct pasm_explist *pexplist,struct ins_str *instr);
PUBLIC	struct ins_str*	ins_mod_build(struct pasm_explist *pexplist,struct ins_str *instr);
PUBLIC	struct ins_str*	ins_mov_build(struct pasm_explist *pexplist,struct ins_str *instr);
PUBLIC	struct ins_str *	ins_label_build(struct pasm_explist *pexplist, struct ins_str * instr, s32 offset);
PUBLIC	struct ins_str*	ins_call_build(struct pasm_explist *pexplist,struct ins_str *instr);
PUBLIC	struct ins_str*	ins_jump_return_build(struct pasm_explist *explist,struct ins_str *instr);
PUBLIC	struct ins_str*	ins_jump_build(s8 *target,struct ins_str *instr);
PUBLIC	struct ins_str*	ins_ja_build(struct pasm_explist *pexplist,struct ins_str *instr);
PUBLIC	struct ins_str*	ins_jb_build(struct pasm_explist *pexplist,struct ins_str *instr);
PUBLIC	struct ins_str*	ins_je_build(struct pasm_explist *pexplist,struct ins_str *instr);
PUBLIC	struct ins_str*	ins_jne_build(struct pasm_explist *pexplist,struct ins_str *instr);
PUBLIC	struct ins_str*	ins_jae_build(struct pasm_explist *pexplist,struct ins_str *instr);
PUBLIC	struct ins_str*	ins_jbe_build(struct pasm_explist *pexplist,struct ins_str *instr);
PUBLIC	struct ins_str *	ins_int_build(struct pasm_explist *pexplist, struct ins_str * instr);

PUBLIC	u32	chk_reg_i(s8 *name);

//ins_lib_t.c
PUBLIC	void	pr_ins_main();
PUBLIC	void	pr_ins_file_process(struct ins_file *f);
PUBLIC	void	pr_ins_stslist_process(struct ins_stslist *stslist);
PUBLIC	void	pr_ins_sts_process(struct ins_sts  *sts);

PUBLIC	void	pr_ins_push_process(struct ins_str *instr);
PUBLIC	void	pr_ins_pop_process(struct ins_str *instr);
PUBLIC	void	pr_ins_add_process(struct ins_str *instr);
PUBLIC	void	pr_ins_sub_process(struct ins_str *instr);
PUBLIC	void	pr_ins_mul_process(struct ins_str *instr);
PUBLIC	void	pr_ins_div_process(struct ins_str *instr);
PUBLIC	void	pr_ins_xor_process(struct ins_str *instr);
PUBLIC	void	pr_ins_ret_process(struct ins_str *instr);
PUBLIC	void	pr_ins_mov_process(struct ins_str *instr);
PUBLIC	void	pr_ins_label_process(struct ins_str *instr);
PUBLIC	void	pr_ins_cmp_process(struct ins_str *instr);
PUBLIC	void	pr_ins_jmp_process(struct ins_str *instr);
PUBLIC	void	pr_ins_ja_process(struct ins_str *instr);

//ins_lib_1.c
PUBLIC	struct ins_mov*	ins_mov_reg_2_imm_32_build(u32 reg, s32 data);
PUBLIC	struct ins_mov*	ins_mov_reg_2_reg_32_build(u32 reg, u32 rm);
PUBLIC	struct ins_mov*	ins_mov_reg_2_mem_32_build(u32 reg, s8 offset);
PUBLIC	struct ins_mov*	ins_mov_mem_2_reg_32_build(u32 reg, s8 offset);
PUBLIC	struct ins_mov*	ins_mov_numb_2_reg_32_build(u32 reg, u32 addr);
PUBLIC	struct ins_mov*	ins_mov_reg_2_numb_32_build(u32 reg, u32 addr);
PUBLIC	struct ins_add*	ins_add_reg_2_reg_32_build(u32 reg, u32 rm);
PUBLIC	struct ins_add*	ins_add_reg_2_imm_32_build(u32 rm, s32 data);
PUBLIC	struct ins_add*	ins_add_reg_2_imm_8_build(u32 rm, s8 data);
PUBLIC	struct ins_push*	ins_push_reg_32_build(u32 reg);
PUBLIC	struct ins_push*	ins_push_mem_32_build(u32 rm, s8 offset);
PUBLIC	struct ins_pop*	ins_pop_reg_32_build(u32 reg);
PUBLIC	struct ins_call*	ins_call_32_build(s8 *label);
PUBLIC	struct ins_ret*	ins_ret_32_build();
PUBLIC	struct ins_xor*	ins_xor_reg_2_reg_32_build(u32 reg, u32 rm);
PUBLIC	struct ins_mul*	ins_mul_reg_16_build(u32 rm);
PUBLIC	struct ins_div*	ins_div_reg_16_build(u32 rm);
PUBLIC	struct ins_sub*	ins_sub_reg_2_reg_32_build(u32 reg, u32 rm);
PUBLIC	struct ins_cmp*	ins_cmp_reg_2_reg_32_build(u32 reg, u32 rm);
PUBLIC	struct ins_jmp*	ins_jmp_8_build(s8 *label);
PUBLIC	struct ins_ja*	ins_ja_8_build(s8 *label);
PUBLIC	struct ins_jae*	ins_jae_8_build(s8 *label);
PUBLIC	struct ins_je*	ins_je_8_build(s8 *label);
PUBLIC	struct ins_jb*	ins_jb_8_build(s8 *label);
PUBLIC	struct ins_jbe*	ins_jbe_8_build(s8 *label);
PUBLIC	struct ins_jne*	ins_jne_8_build(s8 *label);
PUBLIC	struct ins_label*	ins_label_32_build(s8* name , s32 offset);
PUBLIC	struct ins_int*	ins_int_imm_8_build(u8 data);

//ins_update.c
PUBLIC	void	upd_ins_call_process(struct ins_str *instr);
PUBLIC	void	upd_ins_jne_process(struct ins_str *instr);
PUBLIC	void	upd_ins_jbe_process(struct ins_str *instr);
PUBLIC	void	upd_ins_jae_process(struct ins_str *instr);
PUBLIC	void	upd_ins_je_process(struct ins_str *instr);
PUBLIC	void	upd_ins_jb_process(struct ins_str *instr);
PUBLIC	void	upd_ins_ja_process(struct ins_str *instr);
PUBLIC	void	upd_ins_jmp_process(struct ins_str *instr);
PUBLIC	void	upd_ins_sts_process(struct ins_sts  *sts);
PUBLIC	void	upd_ins_stslist_process(struct ins_stslist *stslist);
PUBLIC	void	upd_ins_file_process(struct ins_file *f);
PUBLIC	void	ins_update();

//mcode_file.c
PUBLIC	void	pr_mcode_main(FILE *foutput);
PUBLIC	void	pr_mcode_file_process(struct ins_file *f, FILE *foutput);
PUBLIC	void	pr_mcode_stslist_process(struct ins_stslist *stslist, FILE *foutput);
PUBLIC	void	pr_mcode_sts_process(struct ins_sts  *sts, FILE *foutput);
PUBLIC	void	pr_mcode_cmp_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_ret_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_div_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_mul_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_sub_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_xor_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_add_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_pop_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_push_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_mov_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_jmp_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_ja_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_jb_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_je_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_jae_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_jbe_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_jne_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_call_process(struct ins_str *instr, FILE *foutput);
PUBLIC	void	pr_mcode_int_process(struct ins_str *instr, FILE *foutput);

//mcode_main.c
PUBLIC	void	pr_mcode_title(FILE *foutput);
PUBLIC	void	pr_mcode_content(FILE *foutput);
PUBLIC	void	mcode_main(s8 *src_filename);

//mcode_lib.c
PUBLIC	s32	align_16(FILE *foutput, s32 offset);
PUBLIC	void	section_copy(struct section_header *dst, struct section_header *src);

//external functions
PUBLIC	s32 printf_exec(char *cmd, char *value);
PUBLIC	s32 prints(char *cmd, ...);
PUBLIC	dnasm_ex_write(int fd, const void *buf, int count);
PUBLIC	s32 	printcr();

//elf
PUBLIC	struct elf_header *	elf_header_build(u32 entry, u32 section_header_offset, u32 program_header_offset, u32 flags, u16 program_header_size, u16 program_header_num);
PUBLIC	struct section_header *	section_header_build(s32 index, s32 type, s32 flags, s32 addr, s32 offset, s32 size, s32 link, s32 info, s32 align, s32 entry_size);
PUBLIC	s8	elf_add2strlist(struct strtab_list *src, struct strtab_list * dst);
PUBLIC	struct strtab_list *	strtablist_build(struct strtab *str);
PUBLIC	s8	elf_add2symlist(struct elfsymtab_list *src, struct elfsymtab_list * dst);
PUBLIC	struct elfsymtab_list *	elfsymtablist_build(struct elf_symtab *sym);
PUBLIC	s8	elf_add2rellist(struct rel32_list *src, struct rel32_list * dst);
PUBLIC	struct rel32_list *	rel32list_build(struct rel32 *rel);
PUBLIC	struct dbtab_list *	dbtablist_build(struct dbtab *db);
PUBLIC	s8	elf_add2dblist(struct dbtab_list *src, struct dbtab_list * dst);

#endif
