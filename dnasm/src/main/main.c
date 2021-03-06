//===========================================================================
// main.c
//   Copyright (C) 2013 Free Software Foundation, Inc.
//   Originally by ZhaoFeng Liang <zhf.liang@outlook.com>
//
//This file is part of DTAHS_DNASM.
//
//DTAHS_DNASM is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or 
//(at your option) any later version.
//
//DTAHS_DNASM is distributed in the hope that it will be useful,
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

//===========================================================================
// main
//===========================================================================
PUBLIC	s32	main(s32 argc, s8*argv[])
{
	printf("--start dnasm--,%d, %s\n",argc, argv[1]);

	pre_main(argv[1]);

	lex_init();

	lex_main("src/temp/pre_output.asm");

	symtbl_init();

	parse_init();

	seman_init();		

	var_init();		

	ir_init();

	ins_init();		

	process();

	symtbl_print();

	print_typelist();

	print_g_varlist();

	print_ir();

	pasm_main();

	pr_pasm_main();

	ins_main();

	pr_ins_main();

	ins_update();

	printf("ins_update finish !!!\n\n");

	pr_ins_main();

	mcode_main(argv[1]);

	printf("--end dnasm--\n");
	
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
