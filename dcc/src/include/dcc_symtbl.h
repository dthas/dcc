//===========================================================================
// dcc_symtbl.h
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

#ifndef	_DCC_SYMTBL_H_
#define	_DCC_SYMTBL_H_

#define	SYMTBL_SIZE		107
#define	SYMBOL_NAME_LEN		64

#define	HASH_IND		59377

#define	SCOPE_GLOBAL		1
#define	SCOPE_FILE		2
#define	SCOPE_FUNCTION		3

struct parm_type_list
{	
	s32	id;

	s32	type_scs;		//storage_class_specifier
	s32	type_ts;		//type_specifier
	s32	type_tq;		//type_qualifier
	s32	len;			//count by bytes
	u32	m_offset;		// the address that allocated in run time
	s8	name[SYMBOL_NAME_LEN];

	struct parm_type_list *head;
	struct parm_type_list *tail;	
};

struct member_list
{
	s32	type_scs;		//storage_class_specifier
	s32	type_ts;		//type_specifier
	s32	type_tq;		//type_qualifier
	s32	len;			//count by bytes
	u32	m_offset;		// the address that allocated in run time
	s8	name[SYMBOL_NAME_LEN];

	struct member_list *head;
	struct member_list *tail;	
};

struct struct_union
{
	s8	name[SYMBOL_NAME_LEN];
	struct member_list mblist;
};

struct symbol
{
	s32	id;
	s8	name[SYMBOL_NAME_LEN];
	s32	type_scs;		//storage_class_specifier
	s32	type_ts;		//type_specifier
	s32	type_tq;		//type_qualifier
	s32	len;			//count by bytes
	s8	flg_array;		//whether is an array
	s8	flg_pointer;		//whether is a pointer
	s8	flg_func;		//whether is a function
	s32	val_i;
	s8	val_s[SYMBOL_NAME_LEN];
	s32	scope_1;		// SCOPE_GLOBAL, SCOPE_FILE, SCOPE_FUNCTION
	s32	scope_2;		// function id , if scope_1 is SCOPE_FUNCTION
	u32	m_addr;			// the address that allocated in run time
	s32	i_var_offset;		// the offset between ebp and the var define in the function 
	s8	label[SYMBOL_NAME_LEN];	// the label that is like "L0:",...
	
	struct struct_union 	su;
	struct parm_type_list	ptlist;

	struct symbol *head;
	struct symbol *tail;
};

struct symbol * p_symtbl;

PUBLIC s32 	sym_id;
PUBLIC s32 	g_var_id;

struct symbol sym_t;				//for temp
struct parm_type_list ptlist_t;		//for temp
struct member_list mblist_t;		//for temp

s32 function_id;			//for variables in function


#endif
