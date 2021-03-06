//===========================================================================
// symbol_main.c
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
#include	<stdio.h>
#include	"dcc_lex_char.h"
#include	"dcc_lex_word.h"
#include	"dcc_parse.h"
#include	"dcc_symtbl.h"
#include	"dcc_prototype.h"


PRIVATE s32	hashing(s8 *str);

PRIVATE	struct symbol symtbl[SYMTBL_SIZE];

#define	SYMTBL_DEBUG
//===========================================================================
// main
//===========================================================================
PUBLIC	void	symtbl_init()
{
//--------------------------
//test
#ifdef	SYMTBL_DEBUG
	printf("	-- symtbl_init()  -- \n");
#endif
//--------------------------

	p_symtbl	=  symtbl;

	struct symbol *p;
	s8 i;
	for(i=0, p=&symtbl[i]; i<SYMTBL_SIZE; i++)
	{
		p->head		= NULL;
		p->tail		= NULL;
		p->id		= 0;
		p->type_scs	= 0;
		p->type_ts	= 0;
		p->type_tq	= 0;
		p->len		= 0;
		p->flg_array	= FALSE;
		p->flg_pointer	= FALSE;
		p->flg_func	= FALSE;
		p->val_i	= 0;
		p->scope_1	= 0;
		p->scope_2	= 0;
		p->m_addr	= 0;
		p->i_var_offset	= 0;

		p->su.mblist.type_scs	= 0;
		p->su.mblist.type_ts	= 0;
		p->su.mblist.type_tq	= 0;
		p->su.mblist.len	= 0;
		p->su.mblist.m_offset	= 0;
		p->su.mblist.head	= NULL;
		p->su.mblist.tail	= NULL;

		p->ptlist.type_scs	= 0;
		p->ptlist.len		= 0;
		p->ptlist.type_ts	= 0;
		p->ptlist.type_tq	= 0;
		p->ptlist.m_offset	= 0;
		p->ptlist.head		= NULL;
		p->ptlist.tail		= NULL;

		strcopy(p->name, "");
		strcopy(p->val_s, "");
		strcopy(p->label, "");
	}

	sym_id	= 1;
	function_id	= 0;
	g_var_id	= 1;
}

//===========================================================================
// symbol_crt
//===========================================================================
PUBLIC	struct symbol *	symbol_crt(s8 *name, s32 type_scs, s32 type_ts, s32 type_tq, s32 len, s8 flg_array, s8 flg_pointer, s8 flg_func, s32 val_i, s8 *val_s, s32 scope_1, s32 scope_2, u32 m_addr, s32 i_var_offset, s8 *label, struct struct_union *su, struct parm_type_list *ptlist)
{
	s32 length;

	struct symbol *sym	= malloc(sizeof(struct symbol));

	if(sym == NULL)
	{
		return FALSE;
	}	
	
	sym->id		= sym_id++;
	sym->type_scs	= type_scs;
	sym->type_ts	= type_ts;
	sym->type_tq	= type_tq;
	sym->len	= len;
	sym->flg_array	= flg_array;
	sym->flg_pointer= flg_pointer;
	sym->flg_func	= flg_func;
	sym->val_i	= val_i;
	sym->scope_1	= scope_1;
	sym->scope_2	= scope_2;
	sym->m_addr	= m_addr;
	sym->i_var_offset= i_var_offset;
	sym->head	= NULL;
	sym->tail	= NULL;


	if((sym->type_ts == STRUCT) || (sym->type_ts == UNION))
	{		
		struct_union_copy(&(sym->su), su);	
	}

	if(sym->flg_func)
	{		
		parm_type_list_copy(&(sym->ptlist), ptlist);				
	}

	strcopy(sym->name, name);

	if(sym->flg_func)
	{
		frame_upd_funcid(sym->name, sym->id);			
	}

	if(val_s != NULL)
	{
		strcopy(sym->val_s, val_s);
	}

	strcopy(sym->label, label);	
	
	if(!symtbl_validate(sym))
	{
		printf("\n[error]::symbol_crt()::redefinition:%s !! exit\n\n",sym->name);
		exit(1);
	}

	return sym;
}

//===========================================================================
// symbol_pre_set(symbol *sym)
//===========================================================================
PUBLIC	void	symbol_pre_set(struct symbol *sym)
{	
	//------------------------------------------------------------------
	// member of struct
	//------------------------------------------------------------------
	if(sym->type_ts == STRUCT)
	{
		struct member_list *mb=sym->su.mblist.tail;
		u32 offset;
		for(offset=0; mb; offset += mb->len, mb=mb->tail)
		{		
			mb->m_offset	= offset;
		}
	}

	//------------------------------------------------------------------
	// struct
	//------------------------------------------------------------------
	if(sym->type_ts == STRUCT)
	{
		struct member_list *mb=sym->su.mblist.tail;

		sym->len = 0;

		for(; mb; mb=mb->tail)
		{
			sym->len += mb->len;
		}		
		
		s32 true_type_id = check_type_i(sym->su.name);

		if(!true_type_id)
		{
			add_typelist(STRUCT, sym->len, sym->su.name, sym->su.name, sym->su.mblist.tail);
		}
		else
		{
			sym->len = check_type_l(true_type_id);
		}		
	}

	//------------------------------------------------------------------
	// scope
	//------------------------------------------------------------------
	if(sym->flg_func)
	{
		if(sym->type_scs == STATIC)
		{
			sym->scope_1	= SCOPE_FILE;
		}
		else
		{
			sym->scope_1	= SCOPE_GLOBAL;
		}

		sym->scope_2	= 0; 		
	}
	else
	{
		if(g_function_inside)
		{
			sym->scope_1	= SCOPE_FUNCTION;
			sym->scope_2	= function_id;
		}
		else
		{
			if(sym->type_scs == STATIC)
			{
				sym->scope_1	= SCOPE_FILE;
			}
			else
			{
				sym->scope_1	= SCOPE_GLOBAL;
			}
			sym->scope_2	= 0;
		}
	}
}


//===========================================================================
// symtbl_add
//===========================================================================
PUBLIC	s8	symtbl_add(s8 *name, s32 type_scs, s32 type_ts, s32 type_tq, s32 len, s8 flg_array, s8 flg_pointer, s8 flg_func, s32 val_i, s8 *val_s, s32 scope_1, s32 scope_2, u32 m_addr, s32 i_var_offset, s8* label, struct struct_union *su, struct parm_type_list *ptlist)
{
	struct symbol *sym	= symbol_crt(name, type_scs, type_ts, type_tq, len, flg_array, flg_pointer, flg_func, val_i, val_s, scope_1, scope_2, m_addr, i_var_offset, label, su, ptlist);

	if(sym == NULL)
	{
		return FALSE;
	}
	
	s32 i			= hashing(name);
	s32 index		= i % SYMTBL_SIZE;

	sym->tail		= symtbl[index].tail;	
	symtbl[index].tail	= sym;
	sym->head		= &symtbl[index];

	return TRUE;
}

//===========================================================================
// validate(struct symbol *sym)
//===========================================================================
PUBLIC	s8	symtbl_validate(struct symbol *sym)
{
//--------------------------
//test
#ifdef	SYMTBL_DEBUG
	printf("	-- symtbl_validate()  -- \n");
#endif
//--------------------------


	struct symbol *	p = symtbl_search(sym->name);

	if(!p)
	{
		return TRUE;
	}
	else
	{
		if(p->scope_1 != sym->scope_1)
		{
			return TRUE;
		}
		else if(p->scope_2 != sym->scope_2)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

//===========================================================================
// validate(struct symbol *sym)
//===========================================================================
PUBLIC	struct symbol *	symtbl_validate_s(s8 *name)
{
//--------------------------
//test
#ifdef	SYMTBL_DEBUG
	printf("	-- symtbl_validate_s()  -- \n");
#endif
//--------------------------

	struct symbol *	p = symtbl_search(name);

	if(p)
	{
		return p;
	}
	else
	{
		printf("no such symbol:%s\n", name);
		return NULL;
	}
}

//===========================================================================
// symtbl_add
//===========================================================================
PUBLIC	void	symtbl_add_s(struct symbol *sym)
{
//--------------------------
//test
#ifdef	SYMTBL_DEBUG
	printf("	-- symtbl_add_s()  -- \n");
#endif
//--------------------------

	symtbl_add(sym->name, sym->type_scs, sym->type_ts, sym->type_tq, sym->len, sym->flg_array, sym->flg_pointer, sym->flg_func, sym->val_i, sym->val_s, sym->scope_1, sym->scope_2, sym->m_addr, sym->i_var_offset, sym->label, &(sym->su), &(sym->ptlist));
	
}

//===========================================================================
// symtbl_del()
//===========================================================================
PUBLIC	s8	symtbl_del(s8 *name)
{
	struct symbol *	p = symtbl_search(name);

	if(p == NULL)
	{
		printf("No symbol %s in symbol table\n", name);
		return FALSE;
	}

	(p->head)->tail	= p->tail;

	sym_id--;
	
	return TRUE;
}


//===========================================================================
// symtbl_upd()
//===========================================================================
PUBLIC	s8	symtbl_upd(s8 *name, s32 type_scs, s32 type_ts, s32 type_tq, s32 len, s8 flg_array, s8 flg_pointer, s8 flg_func, s32 val_i, s8 *val_s, s32 scope_1, s32 scope_2, u32 m_addr, s32 i_var_offset,  s8* label, struct parm_type_list *ptlist)
{
	struct symbol *	p = symtbl_search(name);

	if(p == NULL)
	{
		printf("No symbol %s in symbol table\n", name);
		return FALSE;
	}
	
	p->type_scs	= type_scs;
	p->type_ts	= type_ts;
	p->type_tq	= type_tq;
	p->len		= len;
	p->val_i	= val_i;
	p->flg_array	= flg_array;
	p->flg_pointer	= flg_pointer;
	p->flg_func	= flg_func;
	p->scope_1	= scope_1;
	p->scope_2	= scope_2;
	p->m_addr	= m_addr;
	p->i_var_offset = i_var_offset;
	
	strcopy(p->val_s, val_s);

	strcopy(p->label, label);
	
	return TRUE;
}


//===========================================================================
// symtbl_search
//===========================================================================
PUBLIC	struct symbol *	symtbl_search_s(s8 *name, s32 function_id)
{
//--------------------------
//test
#ifdef	SYMTBL_DEBUG
	printf("	-- symtbl_search_s(s)  -- \n");
#endif
//--------------------------

	//------------------------------------------------------------------
	// only symbol without function parameter list
	//------------------------------------------------------------------
	s32 i		= hashing(name);
	s32 index	= i % SYMTBL_SIZE;

	struct symbol *r = symtbl[index].tail;

	if(!r)
	{
		printf("r=NULL, index=%d, i=%d\n", index, i);
	}

	for(; r!=NULL; r=r->tail)
	{
		if(strcmp(r->name, name) == TRUE) 
		{
			if(r->flg_func)
			{
				return r;		// r is a function
			}
			else if (r->scope_2 == function_id)
			{
				return r;		// r is not a function
			}
		}
		
	}

	//------------------------------------------------------------------
	// with function parameter list
	//------------------------------------------------------------------

	s32 j;
	s8 flg_s = FALSE;
	struct symbol *p;

	for(j=0; j<SYMTBL_SIZE; j++)
	{
		for(p=symtbl[j].tail; p!=NULL; p=p->tail)
		{
			if(p->id == function_id)
			{
				flg_s = TRUE;
				break;
			}			
		}

		if(flg_s)
		{
			break;
		}				
	}

	if(flg_s)
	{
		//function parameters
		struct parm_type_list *cur	= &(p->ptlist);
		for(;cur;cur=cur->tail)
		{
			if(strcmp(cur->name, name) == TRUE)
			{
				return p;
			}
		}
	}	

	//------------------------------------------------------------------
	// with struct member list
	//------------------------------------------------------------------

	for(j=0; j<SYMTBL_SIZE; j++)
	{
		for(p=symtbl[j].tail; p!=NULL; p=p->tail)
		{
			if(strcmp(p->su.name, name) == TRUE)
			{
				return p;
			}
			else
			{
				struct member_list *mb	= &(p->su.mblist);		
		
				for(;mb;mb=mb->tail)
				{
					if(strcmp(mb->name, name) == TRUE)
					{
						return p;
					}
				}	
			}		
		}			
	}

	//------------------------------------------------------------------
	// Error
	//------------------------------------------------------------------	

	return NULL;
}

//===========================================================================
// symtbl_search
//===========================================================================
PUBLIC	struct symbol *	symtbl_search(s8 *name)
{
//--------------------------
//test
#ifdef	SYMTBL_DEBUG
	printf("	-- symtbl_search(s)  -- \n");
#endif
//--------------------------

	s32 i		= hashing(name);
	s32 index	= i % SYMTBL_SIZE;

	struct symbol *p;
	for(p=symtbl[index].tail; p!=NULL; p=p->tail)
	{
		if(strcmp(p->name, name) == TRUE)
		{
			return p;
		}
	}

	return NULL;
}



//===========================================================================
// symtbl_search_i
//===========================================================================
PUBLIC	struct symbol *	symtbl_search_i(s32 id)
{
//--------------------------
//test
#ifdef	SYMTBL_DEBUG
	printf("	-- symtbl_search_i(s)  -- \n");
#endif
//--------------------------

	s32 i;
	struct symbol *p;
	for(i=0; i<SYMTBL_SIZE; i++)
	{
		for(p=symtbl[i].tail; p!=NULL; p=p->tail)
		{
			if(p->id == id)
			{
				return p;
			}
		}
	}

//--------------------------
//test
#ifdef	SYMTBL_DEBUG
	printf("	-- symtbl_search_i(e)  -- \n");
#endif
//--------------------------
}


//===========================================================================
// symtbl_print()
//===========================================================================
PUBLIC	void	symtbl_print()
{
	struct symbol *p;
	s8 i,j;
	for(i=0; i<SYMTBL_SIZE; i++)
	{
		for(p=symtbl[i].tail; p!=NULL; p=p->tail)
		{
			printf("\n======================================================================================================================================================\n");
			printf("%5s| %10s| %5s| %10s| %10s| %10s| %10s| %3s| %5s| %5s| %3s| %6s| %6s| %10s| %10s| %10s|\n", "id","name","val_i","val_s","type_scs","type_ts","type_tq","len","array", "point","fun","scope1","scope2","m_addr(0x)","i_offset", "label");
			printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");

			printf("%5d| %10s| %5d| %10s| %10s| %10s| %10s| %3d| %5d| %5d| %3d| %6d| %6d| %10x| %10d| %10s|\n", p->id, p->name,p->val_i, p->val_s, (p->type_scs == 0? "NONE":(p_word+(p->type_scs)*20)), (p->type_ts == 0? "NONE":(p_word+(p->type_ts)*20)), (p->type_tq == 0? "NONE":(p_word+(p->type_tq)*20)), p->len, p->flg_array, p->flg_pointer, p->flg_func, p->scope_1,p->scope_2, p->m_addr, p->i_var_offset, p->label);		

			struct_union_print(&(p->su));

			param_type_list_print(&(p->ptlist));	
		
			printf("======================================================================================================================================================\n");	
		}
	}


}

//===========================================================================
// symtbl_print_1()
//===========================================================================
PUBLIC	void	symtbl_print_1(struct symbol *p)
{
	printf("\n======================================================================================================================================================\n");
	printf("%5s| %10s| %5s| %10s| %10s| %10s| %10s| %3s| %5s| %5s| %3s| %6s| %6s| %10s| %10s| %10s|\n", "id","name","val_i","val_s","type_scs","type_ts","type_tq","len","array", "point","fun","scope1","scope2","m_addr(0x)","i_offset", "label");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	printf("%5d| %10s| %5d| %10s| %10s| %10s| %10s| %3d| %5d| %5d| %3d| %6d| %6d| %10x| %10d| %10s|\n", p->id, p->name,p->val_i, p->val_s, (p->type_scs == 0? "NONE":(p_word+(p->type_scs)*20)), (p->type_ts == 0? "NONE":(p_word+(p->type_ts)*20)), (p->type_tq == 0? "NONE":(p_word+(p->type_tq)*20)), p->len, p->flg_array, p->flg_pointer, p->flg_func, p->scope_1,p->scope_2, p->m_addr, p->i_var_offset, p->label);		

	struct_union_print(&(p->su));

	param_type_list_print(&(p->ptlist));	
		
	printf("======================================================================================================================================================\n");		
	
}


//===========================================================================
// hashing
//===========================================================================
PRIVATE s32	hashing(s8 *str)
{
//--------------------------
//test
#ifdef	SYMTBL_DEBUG
	printf("	-- hashing(s)  -- \n");
#endif
//--------------------------

	s32 val = 0;
	
	for(; *str != NULL; str++)
	{
		val += ((*str) * HASH_IND + 11);
	}

//--------------------------
//test
#ifdef	SYMTBL_DEBUG
	printf("	-- hashing(e)  -- \n");
#endif
//--------------------------

	return val;
}


//===========================================================================
// symbol_crt
//===========================================================================
PUBLIC	void	symbol_empty(struct symbol *sym)
{
	sym->id		= 0;
	sym->name[0]	= NULL;
	sym->type_scs	= 0;
	sym->type_ts	= 0;
	sym->type_tq	= 0;
	sym->len	= 0;
	sym->flg_array	= FALSE;
	sym->flg_pointer= FALSE;
	sym->flg_func	= FALSE;
	sym->val_i	= 0;
	sym->val_s[0]	= NULL;
	sym->scope_1	= 0;
	sym->scope_2	= 0;
	sym->m_addr	= 0;
	sym->i_var_offset= 0;
	sym->label[0]	= NULL;
	sym->head	= NULL;
	sym->tail	= NULL;	

	sym->ptlist.type_scs	= 0;
	sym->ptlist.type_ts	= 0;
	sym->ptlist.type_tq	= 0;
	sym->ptlist.len		= 0;
	sym->ptlist.m_offset	= 0;
	sym->ptlist.head	= NULL;
	sym->ptlist.tail	= NULL;	

	sym->su.mblist.type_scs	= 0;
	sym->su.mblist.type_ts	= 0;
	sym->su.mblist.type_tq	= 0;
	sym->su.mblist.len	= 0;
	sym->su.mblist.m_offset	= 0;
	sym->su.mblist.head	= NULL;
	sym->su.mblist.tail	= NULL;		
}

//===========================================================================
// symbol_crt
//===========================================================================
PUBLIC	void	ptlist_empty(struct parm_type_list *ptlist)
{
	ptlist->type_scs= 0;
	ptlist->type_ts	= 0;
	ptlist->type_tq	= 0;
	ptlist->len	= 0;
	ptlist->m_offset	= 0;
	ptlist->name[0]	= NULL;
	ptlist->head	= NULL;
	ptlist->tail	= NULL;
}

//===========================================================================
// ptlist_add_s
// sym_t.ptlist -> 3 -> 2 -> 1 -> NULL
//===========================================================================
PUBLIC	void	ptlist_add_s(struct parm_type_list *ptlist)
{
//--------------------------
//test
#ifdef	SYMTBL_DEBUG
	printf("	-- ptlist_add_s()  -- \n");
#endif
//--------------------------

	struct parm_type_list *cur	= &(sym_t.ptlist);		
		
	struct parm_type_list *next 	= malloc(sizeof(struct parm_type_list));

	if(next)
	{
		next->type_scs	= ptlist->type_scs;
		next->type_ts	= ptlist->type_ts;
		next->type_tq	= ptlist->type_tq;
		next->len	= ptlist->len;
		next->m_offset	= ptlist->m_offset;

		strcopy(&(next->name[0]), &(ptlist->name[0]));

		next->id	= sym_id++;

		for(;cur->tail;cur=cur->tail)
		{
			if(strcmp(next->name, cur->name) == TRUE)
			{
				printf("\n[error]::function_paramlist::redefinition:%s(src::%s) !! exit\n\n",next->name,cur->name);
				exit(1);
			}
		}
		
		cur->tail	= next;
		next->head	= cur;
		next->tail	= NULL;
	}
	else
	{
		printf("malloc fail\n");
		
	}
}

//===========================================================================
// symtbl_print()
//===========================================================================
PUBLIC	void	param_type_list_print(struct parm_type_list *ptlist)
{
	s32 j;
	struct parm_type_list *pt=ptlist->tail;

	printf("	*********************************************************************************\n");
	printf("	param list:\n");
	printf("	 -------------------------------------------------------------------------------\n");
	printf("	%10s |%10s| %10s| %10s| %10s| %10s| %10s|\n", "id", "name","type_scs","type_ts","type_tq","len","m_offset");
	printf("	 -------------------------------------------------------------------------------\n");

	for(j=1; pt; pt=pt->tail, j++)
	{
		printf("	%10d| %10s| %10s| %10s| %10d| %10d|\n",  pt->id, pt->name, (pt->type_scs == 0? "NONE":(p_word+(pt->type_scs)*20)), (pt->type_ts == 0? "NONE":(p_word+(pt->type_ts)*20)), (pt->type_tq == 0? "NONE":(p_word+(pt->type_tq)*20)), pt->len, pt->m_offset);
	}

}

//===========================================================================
// list copy
//===========================================================================
PUBLIC 	s8 	parm_type_list_copy(struct parm_type_list *dst, struct parm_type_list *src)
{
	if(src->tail)
	{
		for(src=src->tail; src; src=src->tail, dst=dst->tail)
		{
			struct parm_type_list *next = malloc(sizeof(struct parm_type_list));

			if(next)
			{
				next->type_scs	= src->type_scs;
				next->type_ts	= src->type_ts;
				next->type_tq	= src->type_tq;
				next->len	= src->len;
				next->m_offset	= src->m_offset;

				strcopy(&(next->name[0]), &(src->name[0]));
				
				next->id	= src->id;

				dst->tail	= next;
				next->head	= dst;
				next->tail	= NULL;		
			}
		}
	}
}


//===========================================================================
// symbol_crt
//===========================================================================
PUBLIC	void	mblist_empty(struct member_list *mblist)
{
	mblist->type_scs= 0;
	mblist->type_ts	= 0;
	mblist->type_tq	= 0;
	mblist->len	= 0;
	mblist->m_offset	= 0;
	mblist->name[0]	= NULL;
	mblist->head	= NULL;
	mblist->tail	= NULL;
}

//===========================================================================
// mblist_add_s
// sym_t.mblist -> 3 -> 2 -> 1 -> NULL
//===========================================================================
PUBLIC	void	mblist_add_s(struct member_list *mblist)
{
//--------------------------
//test
#ifdef	SYMTBL_DEBUG
	printf("	-- mblist_add_s()  -- \n");
#endif
//--------------------------

	struct member_list *cur	= &(sym_t.su.mblist);		
		
	struct member_list *next 	= malloc(sizeof(struct member_list));

	if(next)
	{
		next->type_scs	= mblist->type_scs;
		next->type_ts	= mblist->type_ts;
		next->type_tq	= mblist->type_tq;
		next->len	= mblist->len;
		next->m_offset	= mblist->m_offset;

		strcopy(&(next->name[0]), &(mblist->name[0]));

		for(;cur->tail;cur=cur->tail)
		{
			if(strcmp(next->name, cur->name) == TRUE)
			{
				printf("\n[error]::struct_member::redefinition:%s(src::%s) !! exit\n\n",next->name,cur->name);
				exit(1);
			}
		}
		
		cur->tail	= next;
		next->head	= cur;
		next->tail	= NULL;
	}
	else
	{
		printf("malloc fail\n");
		
	}	
}

//===========================================================================
// mblist_add_t, just for seman_type.c
// sym_t.mblist -> 3 -> 2 -> 1 -> NULL
//===========================================================================
PUBLIC	void	mblist_add_t(struct member_list *src_mblist, struct member_list *dst_mblist)
{
//--------------------------
//test
#ifdef	SYMTBL_DEBUG
	printf("	-- mblist_add_t(s)  -- \n");
#endif
//--------------------------

	if(!src_mblist)
	{
		printf("mblist_add_t::src_mblist is NULL!!\n");
		exit(1);
	}

	for(; src_mblist; src_mblist=src_mblist->tail)
	{
		struct member_list *next 	= malloc(sizeof(struct member_list));

		if(next)
		{
			next->type_scs	= src_mblist->type_scs;
			next->type_ts	= src_mblist->type_ts;
			next->type_tq	= src_mblist->type_tq;
			next->len	= src_mblist->len;
			next->m_offset	= src_mblist->m_offset;

			strcopy(&(next->name[0]), &(src_mblist->name[0]));

			for(;dst_mblist->tail;dst_mblist=dst_mblist->tail)
			{
				if(strcmp(next->name, dst_mblist->name) == TRUE)
				{
					printf("\n[error]::struct_member::redefinition:%s(src::%s) !! exit\n\n",next->name,dst_mblist->name);
					exit(1);
				}
			}
		
			dst_mblist->tail= next;
			next->head	= dst_mblist;
			next->tail	= NULL;
		}
		else
		{
			printf("malloc fail\n");
		
		}	
	}

//--------------------------
//test
#ifdef	SYMTBL_DEBUG
	printf("	-- mblist_add_t(e)  -- \n");
#endif
//--------------------------
}


//===========================================================================
// symtbl_print()
//===========================================================================
PUBLIC	void	struct_union_print(struct struct_union *su)
{	
	s32 j;
	struct member_list *mb=su->mblist.tail;

	printf("	*************************************************************************\n");
	printf("	(%s)member list:\n", su->name);
	printf("	 ------------------------------------------------------------------------\n");
	printf("	%10s| %10s| %10s| %10s| %10s| %10s|\n", "name","type_scs","type_ts","type_tq","len", "m_offset");
	printf("	-------------------------------------------------------------------------\n");

	for(j=1; mb; mb=mb->tail, j++)
	{
		printf("	%10s| %10s| %10s| %10s| %10d| %10d|\n",  mb->name, (mb->type_scs == 0? "NONE":(p_word+(mb->type_scs)*20)), (mb->type_ts == 0? "NONE":(p_word+(mb->type_ts)*20)), (mb->type_tq == 0? "NONE":(p_word+(mb->type_tq)*20)), mb->len, mb->m_offset);
	}	
}

//===========================================================================
// type_member_print, just for seman_type.c
//===========================================================================
PUBLIC	void	type_member_print(struct member_list *mblist)
{	
	struct member_list *mb=mblist->tail;

	if(mb)
	{
		printf("	 		------------------------------------------------\n");
		printf("			(+)	%10s| %10s| %10s| %10s|\n", "name","type","len", "m_offset");
		printf("			------------------------------------------------\n");

		for(; mb; mb=mb->tail)
		{
			printf("				%10s| %10s| %10d|%10d| \n", mb->name,(mb->type_ts==0?"NONE":(p_word+(mb->type_ts)*20)),mb->len, mb->m_offset);
		}
	}	
}

//===========================================================================
// list copy
//===========================================================================
PUBLIC 	s8 	struct_union_copy(struct struct_union *dst_su, struct struct_union *src_su)
{
//--------------------------
//test
#ifdef	SYMTBL_DEBUG
	printf("	-- struct_union_copy()  -- \n");
#endif
//--------------------------

	strcopy(&(dst_su->name[0]), &(src_su->name[0]));

	struct member_list *src	= &(src_su->mblist);
	struct member_list *dst	= &(dst_su->mblist);

	if(src->tail)
	{
		for(src=src->tail; src; src=src->tail, dst=dst->tail)
		{
			struct member_list *next = malloc(sizeof(struct member_list));

			if(next)
			{
				next->type_scs	= src->type_scs;
				next->type_ts	= src->type_ts;
				next->type_tq	= src->type_tq;
				next->len	= src->len;
				next->m_offset	= src->m_offset;

				strcopy(&(next->name[0]), &(src->name[0]));

				dst->tail	= next;
				next->head	= dst;
				next->tail	= NULL;		
			}
		}
	}
}
