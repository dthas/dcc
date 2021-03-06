//===========================================================================
// seman_lib.c
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
#include	"dcc_prototype.h"
#include	"dcc_main.h"
#include	"dcc_lex_char.h"
#include	"dcc_lex_word.h"
#include	"dcc_parse.h"

//===========================================================================
// is_struct()
//===========================================================================
PUBLIC	s8	is_struct()
{
//--------------------------
//test
#ifdef	SEMAN_DEBUG
	printf("	-- is_struct  -- \n");
#endif
//--------------------------

	s8 flg_mb	= FALSE;

	if(!symtbl_search_s(p_cur_token->val_s, function_id))
	{
		printf("\n[error]::expression::variable(%s) not define in function(%d)!! exit\n\n",p_cur_token->val_s, function_id);
		exit(1);
	}
	
	//p_pre_token is '.'
	if(p_pre_token->token	== OP_DOT)
	{
		struct s_token_list *p = p_pre_token->prev;

		struct symbol *	sym = symtbl_search_s(p->val_s, function_id);

		if(strcmp(sym->name, p->val_s) == TRUE)
		{
			if(sym->type_ts == STRUCT)
			{
				flg_mb	= TRUE;
			}
		}
		else
		{
			struct member_list *mb=sym->su.mblist.tail;

			for(; mb; mb=mb->tail)
			{
				if(strcmp(mb->name, p->val_s) == TRUE)
				{
					flg_mb	= TRUE;
				}
			}
		}

		if(!flg_mb)
		{
			printf("\n[error]::%s.%s is not a struct in function(%d)!! exit\n\n",p->val_s, p_cur_token->val_s, function_id);
			exit(1);
		}
	}
}


//===========================================================================
// is_pointer()
//===========================================================================
PUBLIC	s8	is_pointer()
{
//--------------------------
//test
#ifdef	SEMAN_DEBUG
	printf("	-- is_pointer(s)  -- \n");
#endif
//--------------------------


	if(!symtbl_search_s(p_cur_token->val_s, function_id))
	{
		printf("\n[error]::expression::variable(%s) not define in function(%d)!! exit\n\n",p_cur_token->val_s, function_id);
		exit(1);
	}

	
	//p_pre_token is '->'
	if(p_pre_token->token	== OP_POINTOR)
	{
		struct s_token_list *p = p_pre_token->prev;

		struct symbol *	sym = symtbl_search_s(p->val_s, function_id);

		if(!sym)
		{
			printf("\n[error]::%s->%s is not a pointer in function(%d)!! exit\n\n",p->val_s, p_cur_token->val_s, function_id);
			exit(1);
		}
		else if(!(sym->flg_pointer))
		{
			printf("\n[error]::%s->%s is not a pointer in function(%d)!! exit\n\n",p->val_s, p_cur_token->val_s, function_id);
			exit(1);
		}		
	}

//--------------------------
//test
#ifdef	SEMAN_DEBUG
	printf("	-- is_pointer(e)  -- \n");
#endif
//--------------------------

}

//===========================================================================
// is_pointer()
//===========================================================================
PUBLIC	s8	is_function()
{
//--------------------------
//test
#ifdef	SEMAN_DEBUG
	printf("	-- is_function(s)  -- \n");
#endif
//--------------------------
	
	//p_cur_token is '('
	if(p_cur_token->token	== OP_L_PARENTHESE)
	{
		struct symbol *	sym = symtbl_search_s(p_pre_token->val_s, function_id);

		if(!sym)
		{
			printf("\n[error]::%s is not a function!! exit\n\n",p_pre_token->val_s);
			exit(1);
		}
		else if(!(sym->flg_func))
		{
			printf("\n[error]::%s is not a function!! exit\n\n",p_pre_token->val_s);
			exit(1);
		}		
	}

//--------------------------
//test
#ifdef	SEMAN_DEBUG
	printf("	-- is_function(e)  -- \n");
#endif
//--------------------------

}

//===========================================================================
// is_array
//===========================================================================
PUBLIC	s8	is_array()
{
//--------------------------
//test
#ifdef	SEMAN_DEBUG
	printf("	-- is_array(s)  -- \n");
#endif
//--------------------------
	
	//p_cur_token is '('
	if(p_cur_token->token	== OP_L_BRACKET)
	{
		struct symbol *	sym = symtbl_search_s(p_pre_token->val_s, function_id);

		if(!sym)
		{
			printf("\n[error]::%s is not a array!! exit\n\n",p_pre_token->val_s);
			exit(1);
		}
		else if(!(sym->flg_array))
		{
			printf("\n[error]::%s is not a array!! exit\n\n",p_pre_token->val_s);
			exit(1);
		}		
	}

//--------------------------
//test
#ifdef	SEMAN_DEBUG
	printf("	-- is_array(e)  -- \n");
#endif
//--------------------------

}

