//===========================================================================
// dnasm_type.h
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

#ifndef	_DNASM_TYPE_H_
#define	_DNASM_TYPE_H_

#define	PUBLIC		
#define	PRIVATE	static

#define	NULL	'\0'

typedef	unsigned long long	u64;
typedef	unsigned int		u32;
typedef	unsigned short		u16;
typedef	unsigned char		u8;

typedef	long long		s64;
typedef	int			s32;
typedef	short			s16;
typedef	char			s8;

enum sym_type 
{
	U64 = 0, U32, U16, U8, S64, S32, S16, S8, STRING
};


#endif
