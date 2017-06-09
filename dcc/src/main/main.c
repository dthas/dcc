//===========================================================================
// main.c
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

//===========================================================================
// main
//===========================================================================
PUBLIC	s32	main(s32 argc, s8*argv[])
{
	printf("--start dcc--,%d, %s\n",argc, argv[1]);

	symtbl_init();

	pre_main(argv[1]);

	lex_init();

	lex_main();

	parse_init();

	seman_init();		

	frame_init();		

	ir_init();		

	label_init();		

	process();

	symtbl_print();

	print_typelist();

	printframelist();

	print_g_varlist();

	print_ir();

	pasm_main();

	pr_pasm_main();

	pr_block_main();

	live_main();

	pr_live_main();

	graph_main();

	pr_graph_main();

	alloc_main();

	pr_alloc_main();

	ins_main();

	pr_ins_main();

	asm_main();

	printf("--end dcc--\n");
	
	return 0;
}


//===========================================================================
// process
//===========================================================================
PUBLIC	void	process()
{
	printf("-- process begin --\n");

	parse();
	
	printf("-- process end --\n");
}
