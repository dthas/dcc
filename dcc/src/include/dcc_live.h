//===========================================================================
// dcc_live.h
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

#ifndef	_DCC_LIVE_H_
#define	_DCC_LIVE_H_


#define	LIVE_NAME_LEN		64

//-------------------------------------------------------------------------
// whole file
//-------------------------------------------------------------------------
struct live
{
	s8	name[LIVE_NAME_LEN];
	s32	var_id;
	s32 	reg_id;	
};

struct live_list
{
	struct graph *g;

	struct live *live;
	struct live_list *head;
	struct live_list *tail;
};

struct live_block
{
	struct live_list *livelist;
	struct live_block *head;
	struct live_block *tail;
};

struct live_file
{
	struct live_block *liveblock;
	struct live_file *head;
	struct live_file *tail;
};

struct live_file	*lcur_file;

#endif
