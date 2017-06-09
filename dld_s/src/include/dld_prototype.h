//===========================================================================
// dld_prototype.h
//   Copyright (C) 2013 Free Software Foundation, Inc.
//   Originally by ZhaoFeng Liang <zhf.liang@outlook.com>
//
//This file is part of DTHAS_DLD.
//
//DTHAS_DLD is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or 
//(at your option) any later version.
//
//DTHAS_DLD is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with DTHAS; If not, see <http://www.gnu.org/licenses/>.  
//===========================================================================

#ifndef	_DLD_PROTOTYPE_H_
#define	_DLD_PROTOTYPE_H_


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
PUBLIC 	u32 	s2h(s8 * str);


//external functions
PUBLIC	s32 printf_exec(char *cmd, char *value);
PUBLIC	s32 prints(char *cmd, ...);
PUBLIC	dld_ex_write(int fd, const void *buf, int count);
PUBLIC	s32 	printcr();

//elf
PUBLIC	struct elf_header *	elf_header_build(u32 entry, u32 section_header_offset, u32 program_header_offset, u32 flags, u16 program_header_size, u16 program_header_num, u16 type);
PUBLIC	struct section_header *	section_header_build(s32 index, s32 type, s32 flags, s32 addr, s32 offset, s32 size, s32 link, s32 info, s32 align, s32 entry_size);
PUBLIC	struct program_header *	program_header_build(s32 type, s32 offset, u32 vir_addr, u32 file_addr, u32 file_size, u32 mem_size, s32 flag, s32 align);
PUBLIC	s8	elf_add2strlist(struct strtab_list *src, struct strtab_list * dst);
PUBLIC	struct strtab_list *	strtablist_build(struct strtab *str);
PUBLIC	s8	elf_add2symlist(struct elfsymtab_list *src, struct elfsymtab_list * dst);
PUBLIC	struct elfsymtab_list *	elfsymtablist_build(struct elf_symtab *sym);
PUBLIC	s8	elf_add2rellist(struct rel32_list *src, struct rel32_list * dst);
PUBLIC	struct rel32_list *	rel32list_build(struct rel32 *rel);
PUBLIC	struct dbtab_list *	dbtablist_build(struct dbtab *db);
PUBLIC	s8	elf_add2dblist(struct dbtab_list *src, struct dbtab_list * dst);
PUBLIC	void	dld_add_program_header(FILE *foutput, u32 p_offset, u32 v_addr, u32 p_addr, u32 p_file_size, u32 p_mem_size, u32 p_flag, u32 p_type);

//main.c
PUBLIC	s32	main(s32 argc, s8*argv[]);
PUBLIC	struct objinfo_list *	objlist_build(struct obj_info *oinfo);
PUBLIC	s8	dld_add2objlist(struct objinfo_list *src, struct objinfo_list * dst);

//dld_lib.c
PUBLIC	s32	read_obj(s8* filename, struct objinfo_list *oi_list);
PUBLIC	s32	exe_obj(struct objinfo_list *src_list, struct obj_info *dsti);
PUBLIC	s32	output_obj(s8* filename, struct objinfo_list *src_list, struct obj_info *dsti);

PUBLIC	void	dld_add_elf_header(FILE *foutput);

//rel_process.c
PUBLIC	void	section_content_data_rel_process(s8 *buf, u32 size, s32 file_offset);
PUBLIC	void	section_content_symbol_rel_process(s8 *buf, u32 size, struct obj_info *oinfo);
PUBLIC	void	section_content_reltext_rel_process(s8 *buf, u32 size, struct obj_info *oinfo);
PUBLIC	void	do_upd_symtab(s8* filename, struct objinfo_list *src_list, struct obj_info *dsti);
PUBLIC	struct offset_list * chk_strtab(s8 *src, struct obj_info *dsti, FILE *ft, struct offset_list *olist, u32 index);
PUBLIC	void	do_upd_elfstart(s8* filename, struct objinfo_list *src_list, struct obj_info *dsti);
PUBLIC	void	do_rel_upd(FILE *ft, u32 rel_info, u32 rel_offset, struct obj_info *dsti);
PUBLIC	s8 chk_start(struct obj_info *oinfo, struct elf_symtab * elf_s);
PUBLIC	void chk_symtab(struct offset_list *ol, struct obj_info *dsti, FILE *ft, u16 section_index, u32 val);

//main_lib_1.c
PUBLIC	void	pr_objinfo_list(struct objinfo_list *olist);
PUBLIC	void	pr_objinfo(struct obj_info *oi);
PUBLIC	void	pr_symtab(s8* filename, struct obj_info *dsti);
PUBLIC	void	pr_shstrtab(s8* filename, struct obj_info *dsti);
PUBLIC	void	pr_reltext(s8* filename, struct obj_info *dsti);
PUBLIC	void	pr_strtab(s8* filename, struct obj_info *dsti);

#endif
