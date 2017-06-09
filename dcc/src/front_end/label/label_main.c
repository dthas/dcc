//===========================================================================
// label_main.c
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
#include	"dcc_symtbl.h"
#include	<stdio.h>
#include	"dcc_main.h"
#include	"dcc_lex_char.h"
#include	"dcc_lex_word.h"
#include	"dcc_parse.h"
#include	"dcc_seman.h"
#include	"dcc_label.h"
#include	"dcc_prototype.h"

#define	LABEL_DEBUG


//===========================================================================
// label_init()
//===========================================================================
PUBLIC	void	label_init()
{
//--------------------------
//test
#ifdef	LABEL_DEBUG
	printf("	-- label_init(s)  -- \n");
#endif
//--------------------------

	label_id	= LABEL_INIT;
}

//===========================================================================
// label_build()
//===========================================================================
PUBLIC	void	label_build(s8 *label)
{
//--------------------------
//test
#ifdef	LABEL_DEBUG
	printf("	-- label_build(s)  -- \n");
#endif
//--------------------------

	//------------------------------------------------------------------
	// create label_id and change it to string format
	//------------------------------------------------------------------
	s8 temp[LABEL_NAME_LEN];
	clear_buf(temp, LABEL_NAME_LEN);

	h2s(label_id, temp);

	label[strlen(temp)]	= NULL;	

	//------------------------------------------------------------------
	// copy "L" to label
	//------------------------------------------------------------------
	strcopy(label, "L");
	label[strlen(label)]	= NULL;

	//------------------------------------------------------------------
	// copy lname to label, L123:
	//------------------------------------------------------------------
	strcopy(&label[strlen(label)], temp);

	label[strlen(label)]	= NULL;	

	//------------------------------------------------------------------
	// label_id++
	//------------------------------------------------------------------
	label_id++;
}
