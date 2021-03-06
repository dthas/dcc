//===========================================================================
// parse_main.c
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
#include	<stdio.h>
#include	"dnasm_prototype.h"
#include	"dnasm_main.h"
#include	"dnasm_lex_char.h"
#include	"dnasm_lex_word.h"
#include	"dnasm_parse.h"
#include	"dnasm_symtbl.h"

PRIVATE	struct s_stack	data_stack;
PRIVATE	struct s_queue	data_queue;

//===========================================================================
// main
//===========================================================================
PUBLIC	void	parse_init()
{
	s32 i;

	parse_productiontab_init();

	parse_production	= PRODUCTION_1;

	postfix_var_len		= 0;

	flg_abop_g		= FALSE;

	flg_cmpcond_g		= FALSE;
	flg_extern_g		= FALSE;

	flg_global_g		= FALSE;

	symbol_empty(&sym_t);
}

//===========================================================================
// main
//===========================================================================
PUBLIC	void	parse()
{
	parse_entry();
}
