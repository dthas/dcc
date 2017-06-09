//===========================================================================
// dcc_pre_lex.h
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

#ifndef	_DCC_PRE_LEX_WORD_H_
#define	_DCC_PRE_LEX_WORD_H_

PUBLIC s32 	*p_pre_lex_word_state_tab;
PUBLIC s32 	pre_lex_word_state;

//-------------------------------------------------------------------------
// state table param  
//-------------------------------------------------------------------------
#define	PRE_LEX_WORD_STATES		15		//

//-------------------------------------------------------------------------
// define states
//-------------------------------------------------------------------------
#define	PRE_LEX_WORD_STATE_END		-1		// end state 
#define	PRE_LEX_WORD_STATE1		0		// start state 
#define	PRE_LEX_WORD_STATE2		1		// include
#define	PRE_LEX_WORD_STATE3		2		// define
#define	PRE_LEX_WORD_STATE4		3		// undef
#define	PRE_LEX_WORD_STATE5		4		// line
#define	PRE_LEX_WORD_STATE6		5		// error
#define	PRE_LEX_WORD_STATE7		6		// pragma
#define	PRE_LEX_WORD_STATE8		7		// if
#define	PRE_LEX_WORD_STATE9		8		// ifdef
#define	PRE_LEX_WORD_STATE10		9		// ifndef
#define	PRE_LEX_WORD_STATE11		10		// elif
#define	PRE_LEX_WORD_STATE12		11		// else
#define	PRE_LEX_WORD_STATE13		12		// endif
#define	PRE_LEX_WORD_STATE14		13		//
#define	PRE_LEX_WORD_STATE15		14		//

#define	PRE_LEX_WORD_STATE16		15		// //
#define	PRE_LEX_WORD_STATE17		16		// /*
#define	PRE_LEX_WORD_STATE18		17		// */

//-------------------------------------------------------------------------
// define actions
//-------------------------------------------------------------------------
#define	LEX_WORD_NR_ACTION			18

#define	LEX_WORD_INCLUDE			0
#define	LEX_WORD_DEFINE			1
#define	LEX_WORD_UNDEF			2
#define	LEX_WORD_LINE			3
#define	LEX_WORD_ERROR			4
#define	LEX_WORD_PRAGMA			5
#define	LEX_WORD_IF			6
#define	LEX_WORD_IFDEF			7
#define	LEX_WORD_IFNDEF			8
#define	LEX_WORD_ELIF			9
#define	LEX_WORD_ELSE			10
#define	LEX_WORD_ENDIF			11

#define	LEX_WORD_PARAM1			12
#define	LEX_WORD_PARAM2			13
#define	LEX_WORD_END			14

#define	LEX_WORD_DIVDIV			15
#define	LEX_WORD_DIVMUL			16
#define	LEX_WORD_MULDIV			17

#endif
