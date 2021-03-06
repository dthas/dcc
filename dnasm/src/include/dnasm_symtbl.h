//===========================================================================
// dnasm_symtbl.h
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

#ifndef	_DNASM_SYMTBL_H_
#define	_DNASM_SYMTBL_H_

#define	SYMTBL_SIZE		107
#define	SYMBOL_NAME_LEN		64

#define	HASH_IND		59377

#define	FLAG_SYM		1
#define	FLAG_TEXT		2
#define	FLAG_DATA		3
#define	FLAG_EXTERN		4
#define	FLAG_GLOBAL		5
#define	FLAG_FILE		6

#define	ATTR_VAR		1
#define	ATTR_FUN		2

struct symbol
{
	s32	id;
	s8	name[SYMBOL_NAME_LEN];
	s32	type_scs;		//storage_class_specifier
	s32	type_ts;		//type_specifier
	s32	len;			//count by bytes
	s32	val_i;
	s32	val_i_1;
	s8	val_s[SYMBOL_NAME_LEN];
	s8 	flag;
	s8 	attr;			//1:variable; 2:function;
	u32	addr;
	
	s8	label[SYMBOL_NAME_LEN];	// the label that is like "L0:",...
	
	struct symbol *head;
	struct symbol *tail;
};

struct symbol * p_symtbl;

PUBLIC s32 	sym_id;
PUBLIC s32 	g_var_id;

struct symbol sym_t;				//for temp


#endif
