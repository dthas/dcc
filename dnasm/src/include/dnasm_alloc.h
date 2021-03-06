//===========================================================================
// dnasm_alloc.h
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

#ifndef	_DNASM_ALLOC_H_
#define	_DNASM_ALLOC_H_

#define	REG_FREE	0
#define	REG_LOCK	1

#define	REG_LOCKALL	2
#define	REG_NORMAL	3

//-------------------------------------------------------------------------
// reg
//-------------------------------------------------------------------------
struct s_reg
{
	s32	var_id;
	s32	reg_id;

	s32	status;
};


struct s_reg *g_reg;

#endif
