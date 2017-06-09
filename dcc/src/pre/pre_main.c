//===========================================================================
// pre_main.c
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
#include	"dcc_pre.h"
#include	<stdio.h>
#include	"dcc_prototype.h"

//===========================================================================
// init
//===========================================================================
PRIVATE	void	pre_start()
{
	printf("--pre start---\n");

}

//===========================================================================
// init
//===========================================================================
PRIVATE	void	pre_end()
{
	printf("--pre end---\n");
}


//===========================================================================
// pre_set_inputfile
//===========================================================================
PRIVATE	void	pre_set_inputfile(s8 *src, s8 *dst)
{
	s8 ch;

	FILE *frp	= fopen(src,"r");
	FILE *fwp	= fopen(dst,"w");

	if(frp == NULL)
	{
		printf("error::can not open read file %s\n", src);
		exit(1);
	}

	if(fwp == NULL)
	{
		printf("error::can not open write file %s\n", dst);
		exit(1);
	}

	while((ch=fgetc(frp)) != EOF)
	{
		fputc(ch, fwp);	
	}
	
	fclose(frp);
	fclose(fwp);
}


//===========================================================================
// main
//===========================================================================
PUBLIC	void	pre_main(s8 *filename)
{
	s8 output_file[]	= "src/temp/pre_output.c";

	//------------------------------------------------------------------
	// init message 
	//------------------------------------------------------------------
	pre_start();

	//------------------------------------------------------------------
	// read src file into pre_output.c 
	//------------------------------------------------------------------
	pre_set_inputfile(filename, output_file);

	//------------------------------------------------------------------
	// end 
	//------------------------------------------------------------------
	pre_end();
}
