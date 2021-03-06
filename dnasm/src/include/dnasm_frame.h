//===========================================================================
// dnasm_frame.h
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

#ifndef	_DNASM_FRAME_H_
#define	_DNASM_FRAME_H_

#define	VAR_NAME_LEN	64

//-------------------------------------------------------------------------
// var
//-------------------------------------------------------------------------
struct s_var
{
	s32	var_id;

	s8 	var_name[VAR_NAME_LEN];
	s32	true_type_id;	
	s32	type_id;
	s32	len;
	s32	var_offset;			
};

struct s_varlist
{
	struct s_var var;	

	struct s_varlist *head;
	struct s_varlist *tail;
};

//-------------------------------------------------------------------------
// variables
//-------------------------------------------------------------------------
struct s_varlist *pvarlist;

s32	g_var_addr_offset;

struct s_var	*cur_var;

#endif
