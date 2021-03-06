//===========================================================================
// dcc_block.h
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

#ifndef	_DCC_BLOCK_H_
#define	_DCC_BLOCK_H_

//-------------------------------------------------------------------------
// block
//-------------------------------------------------------------------------
struct block
{
	struct pasm_stslist *stslist;
	struct block *head;
	struct block *tail;
};

struct blocklist
{
	struct block *block;
	struct blocklist *head;
	struct blocklist *tail;
};

struct block *cur_block;
struct blocklist *cur_blocklist;

#endif
