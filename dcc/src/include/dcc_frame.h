//===========================================================================
// dcc_frame.h
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

#ifndef	_DCC_FRAME_H_
#define	_DCC_FRAME_H_

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
	s32 	offset;
	s32	len;		//pointer, default is 4
	s32 	len_1;		//real len
	s32	total_len;	//for array
	u32	var_addr;	//point to each var
};

struct s_varlist
{
	struct s_var var;	

	struct s_varlist *head;
	struct s_varlist *tail;
};

//-------------------------------------------------------------------------
// frame
//-------------------------------------------------------------------------
struct s_frame
{
	u32	pframe_addr;		//ebp, which is the frame pointer

	s32 	func_id;
	s8 	func_name[VAR_NAME_LEN];
	s8 	label_name[VAR_NAME_LEN];

	s32	ret_val;

	struct s_varlist varlist;
};

struct s_framelist
{
	struct s_frame frame;

	struct s_framelist *head;
	struct s_framelist *tail;
};

//-------------------------------------------------------------------------
// variables
//-------------------------------------------------------------------------
struct s_framelist *pframelist;

struct s_varlist *pvarlist;

struct s_var	*cur_var;

#endif
