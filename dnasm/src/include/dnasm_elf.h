//===========================================================================
// dnasm_elf.h
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

#ifndef	_DNASM_ELF_H_
#define	_DNASM_ELF_H_

#define	ELF_HEADER_SIZE		52	//bytes
#define	ELF_VERSION		1	//
#define	ELF_MACHINE_X86		3	//Intel x86
#define	ELF_TYPE_REL		1	//relocated files

#define	ELF_IDEN_LEN		16	//bytes
#define	ELF_IDEN_32_FILE	1	//iden[4]
#define	ELF_IDEN_LITTLE_END	1	//iden[5]
#define	ELF_IDEN_VERSION	1	//iden[6]

#define	SECTION_HEADER_SIZE	40	//bytes	

#define	SECTION_NUM		13

#define	SECTION_INDEX_NULL		0
#define	SECTION_INDEX_TEXT		1
#define	SECTION_INDEX_DATA		2
#define	SECTION_INDEX_BSS		3
#define	SECTION_INDEX_RODATA		4
#define	SECTION_INDEX_RELTEXT		5
#define	SECTION_INDEX_SHSTRTAB		6
#define	SECTION_INDEX_SYMTAB		7
#define	SECTION_INDEX_STRTAB		8
#define	SECTION_INDEX_COMMENT		9
#define	SECTION_INDEX_EH_FRAME		10
#define	SECTION_INDEX_REL_EH_FRAME	11
#define	SECTION_INDEX_NOTE_GNU_STACK	12

#define	SECTION_TYPE_NULL	0
#define	SECTION_TYPE_PROGBITS	1
#define	SECTION_TYPE_SYMTAB	2
#define	SECTION_TYPE_STRTAB	3
#define	SECTION_TYPE_RELA	4
#define	SECTION_TYPE_HASH	5
#define	SECTION_TYPE_DYNAMIC	6
#define	SECTION_TYPE_NOTE	7
#define	SECTION_TYPE_NOBITS	8
#define	SECTION_TYPE_REL	9
#define	SECTION_TYPE_RESERVE	10
#define	SECTION_TYPE_DNYSYM	11	

#define	SECTION_ALIGN_DATA	4	//4 bytes align
#define	SECTION_ALIGN_TEXT	16	//16 bytes align
#define	SECTION_ALIGN_SHSTRTAB	1	//1 byte align
#define	SECTION_ALIGN_SYMTAB	4	//16 byte align
#define	SECTION_ALIGN_STRTAB	1	//0 byte align
#define	SECTION_ALIGN_RELTEXT	4	//4 bytes align
#define	SECTION_ALIGN_BSS	4	//4 bytes align
#define	SECTION_ALIGN_RODATA	1	//1 bytes align
#define	SECTION_ALIGN_COMMENT	1	//1 bytes align
#define	SECTION_ALIGN_EH_FRAME	4	//4 bytes align

#define	SECTION_FLAGS_WRITE	0x1
#define	SECTION_FLAGS_ALLOC	0x2
#define	SECTION_FLAGS_EXE	0x4

#define	SECTION_DATA_START_ADDR	0x248	//0x40(elf_header+12) + 0x28 * 13(all the section header)
#define	SECTION_SHSTRTAB_LEN	110	//the size of section_tab[SECTION_NUM][20]

#define	SECTION_HEADER_START_ADDR	0x40

#define	SCOPE_LOCAL		0
#define	SCOPE_GLOBAL		1
#define	SCOPE_WEAK		2

#define	ELF_NOTYPE		0
#define	ELF_OBJECT		1
#define	ELF_FUNC		2
#define	ELF_SECTION		3
#define	ELF_FILE		4

#define	SHN_ABS			0xfff1

#define	R_386_32		1	//for var
#define	R_386_PC32		2	//for function

//-------------------------------------------------------------------------
// ELF header
//-------------------------------------------------------------------------

struct elf_header
{
	u8 	iden[ELF_IDEN_LEN];	//16 bytes
	u16	type;
	u16	machine;
	u32	version;
	u32	entry;
	u32	program_header_offset;
	u32	section_header_offset;
	u32	flags;
	u16	elf_header_size;
	u16	program_header_size;
	u16	program_header_num;
	u16	section_header_size;
	u16	section_header_num;
	u16	section_header_strtab_index;
};

//-------------------------------------------------------------------------
// section header
//-------------------------------------------------------------------------

struct section_header
{
	u32	name;
	u32	type;
	u32	flags;
	u32	addr;
	u32	offset;
	u32	size;
	u32	link;
	u32	info;
	u32	addr_align;
	u32	entry_size;
};

//-------------------------------------------------------------------------
// rel
//-------------------------------------------------------------------------

struct rel32
{
	u32	offset;
	u32	info;
};

struct rel32_list
{
	struct rel32 *rel;
	
	struct rel32_list *head;
	struct rel32_list *tail;
};

//-------------------------------------------------------------------------
// symtab
//-------------------------------------------------------------------------

struct elf_symtab
{
	u32	strtab_index;
	u32	value;
	u32	size;
	u8	info;
	u8	other;
	u16	section_index;
};

struct elfsymtab_list
{
	struct elf_symtab *sym;
	
	struct elfsymtab_list *head;
	struct elfsymtab_list *tail;
};

//-------------------------------------------------------------------------
// strtab
//-------------------------------------------------------------------------
struct strtab
{
	s8	str[20];
};

struct strtab_list
{
	struct strtab *str;
	
	struct strtab_list *head;
	struct strtab_list *tail;
};

//-------------------------------------------------------------------------
// dbtab
//-------------------------------------------------------------------------
struct dbtab
{
	s32	val;
};

struct dbtab_list
{
	struct dbtab *db;
	
	struct dbtab_list *head;
	struct dbtab_list *tail;
};

struct rel32_list *rell;
struct elfsymtab_list	*esyml;
struct strtab_list *strl;
struct dbtab_list *dbl;

#endif
