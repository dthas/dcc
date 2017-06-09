//===========================================================================
// dcc_seman.h
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

#ifndef	_DCC_SEMAN_H_
#define	_DCC_SEMAN_H_

//-------------------------------------------------------------------------
// type list
//-------------------------------------------------------------------------
#define	TYPE_NAME_LEN		64
#define	TYPE_ID_SELFDEF_INIT	1000

struct s_type
{
	s32	true_type_id;		//int, long, float, double, char, void, short
	s32	type_id;
	s32	len;			//count by bytes
	s8	type_name[TYPE_NAME_LEN];
	
	struct member_list mblist; 
};

struct s_typelist
{
	struct s_type	ty;

	struct s_typelist *head;
	struct s_typelist *tail;
};

struct s_typelist *p_typelist;

s32 type_id_selfdef;

#endif
