//===========================================================================
// parse_main.c
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
#include	<stdio.h>
#include	"dcc_prototype.h"
#include	"dcc_main.h"
#include	"dcc_lex_char.h"
#include	"dcc_lex_word.h"
#include	"dcc_parse.h"

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

	//for declaration
	flg_param	= FALSE;	//just for parameter_declaration
	flg_struct_union= FALSE;	//just for struct or union declaration
	g_function_inside	= FALSE;//just for judge a variable whether it's in a function


	//for exp
	flg_val_func	= FALSE;
	flg_val_pointer	= FALSE;
	flg_val_array	= FALSE;
	flg_val_struct_union	= FALSE;//

	//for select sentence
	flg_select	= FALSE;

	// for iteration
	flg_iteration	= FALSE;
}

//===========================================================================
// main
//===========================================================================
PUBLIC	void	parse()
{
	parse_entry();
}
