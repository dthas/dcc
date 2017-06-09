//===========================================================================
// symbol_main.c
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

#include	"dnasm_global.h"
#include	"dnasm_type.h"
#include	<stdio.h>
#include	"dnasm_lex_char.h"
#include	"dnasm_lex_word.h"
#include	"dnasm_parse.h"
#include	"dnasm_symtbl.h"
#include	"dnasm_prototype.h"


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
		p->len		= 0;
		p->val_i	= 0;
		p->val_i_1	= 0;
		p->flag		= 0;
		p->attr		= 0;
		p->addr		= 0;		//for relocate in ins_update.c
		
		strcopy(p->name, "");
		strcopy(p->val_s, "");
		strcopy(p->label, "");
	}

	sym_id	= 1;

	g_var_id	= 1;

	symtbl_add("EAX", GLOBAL, DWORD, 4, 0, NULL, "EAX", FLAG_SYM, ATTR_VAR);
	symtbl_add("EBX", GLOBAL, DWORD, 4, 0, NULL, "EBX", FLAG_SYM, ATTR_VAR);
	symtbl_add("ECX", GLOBAL, DWORD, 4, 0, NULL, "ECX", FLAG_SYM, ATTR_VAR);
	symtbl_add("EDX", GLOBAL, DWORD, 4, 0, NULL, "EDX", FLAG_SYM, ATTR_VAR);
	symtbl_add("EBP", GLOBAL, DWORD, 4, 0, NULL, "EBP", FLAG_SYM, ATTR_VAR);
	symtbl_add("ESP", GLOBAL, DWORD, 4, 0, NULL, "ESP", FLAG_SYM, ATTR_VAR);
	symtbl_add("ESI", GLOBAL, DWORD, 4, 0, NULL, "ESI", FLAG_SYM, ATTR_VAR);
	symtbl_add("EDI", GLOBAL, DWORD, 4, 0, NULL, "EDI", FLAG_SYM, ATTR_VAR);
	symtbl_add("CS", GLOBAL, DWORD, 4, 0, NULL, "CS", FLAG_SYM, ATTR_VAR);
	symtbl_add("DS", GLOBAL, DWORD, 4, 0, NULL, "DS", FLAG_SYM, ATTR_VAR);
	symtbl_add("ES", GLOBAL, DWORD, 4, 0, NULL, "ES", FLAG_SYM, ATTR_VAR);
	symtbl_add("EIP", GLOBAL, DWORD, 4, 0, NULL, "EIP", FLAG_SYM, ATTR_VAR);
	symtbl_add("DWORD", GLOBAL, DWORD, 4, 0, NULL, "DWORD", FLAG_SYM, ATTR_VAR);
	symtbl_add("WORD", GLOBAL, WORD, 2, 0, NULL, "WORD", FLAG_SYM, ATTR_VAR);
	symtbl_add("BYTE", GLOBAL, BYTE, 1, 0, NULL, "BYTE", FLAG_SYM, ATTR_VAR);

	symtbl_add("eax", GLOBAL, DWORD, 4, 0, NULL, "eax", FLAG_SYM, ATTR_VAR);
	symtbl_add("ebx", GLOBAL, DWORD, 4, 0, NULL, "ebx", FLAG_SYM, ATTR_VAR);
	symtbl_add("ecx", GLOBAL, DWORD, 4, 0, NULL, "ecx", FLAG_SYM, ATTR_VAR);
	symtbl_add("edx", GLOBAL, DWORD, 4, 0, NULL, "edx", FLAG_SYM, ATTR_VAR);
	symtbl_add("ebp", GLOBAL, DWORD, 4, 0, NULL, "ebp", FLAG_SYM, ATTR_VAR);
	symtbl_add("esp", GLOBAL, DWORD, 4, 0, NULL, "esp", FLAG_SYM, ATTR_VAR);
	symtbl_add("esi", GLOBAL, DWORD, 4, 0, NULL, "esi", FLAG_SYM, ATTR_VAR);
	symtbl_add("edi", GLOBAL, DWORD, 4, 0, NULL, "edi", FLAG_SYM, ATTR_VAR);
	symtbl_add("cs", GLOBAL, DWORD, 4, 0, NULL, "cs", FLAG_SYM, ATTR_VAR);
	symtbl_add("ds", GLOBAL, DWORD, 4, 0, NULL, "ds", FLAG_SYM, ATTR_VAR);
	symtbl_add("es", GLOBAL, DWORD, 4, 0, NULL, "es", FLAG_SYM, ATTR_VAR);
	symtbl_add("eip", GLOBAL, DWORD, 4, 0, NULL, "eip", FLAG_SYM, ATTR_VAR);
	symtbl_add("dword", GLOBAL, DWORD, 4, 0, NULL, "dword", FLAG_SYM, ATTR_VAR);
	symtbl_add("word", GLOBAL, WORD, 2, 0, NULL, "word", FLAG_SYM, ATTR_VAR);
	symtbl_add("byte", GLOBAL, BYTE, 1, 0, NULL, "byte", FLAG_SYM, ATTR_VAR);	
	symtbl_add("bx", GLOBAL, WORD, 2, 0, NULL, "bx", FLAG_SYM, ATTR_VAR);	
}



//===========================================================================
// symbol_crt
//===========================================================================
PUBLIC	struct symbol *	symbol_crt(s8 *name, s32 type_scs, s32 type_ts, s32 len, s32 val_i, s8 *val_s, s8 *label, s8 flag, s8 attr)
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
	sym->len	= len;
	sym->val_i	= val_i;
	sym->head	= NULL;
	sym->tail	= NULL;
	sym->flag	= flag;
	sym->attr	= attr;

	strcopy(sym->name, name);

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
// symtbl_add
//===========================================================================
PUBLIC	s8	symtbl_add(s8 *name, s32 type_scs, s32 type_ts, s32 len, s32 val_i, s8 *val_s, s8* label, s8 flag, s8 attr)
{
	struct symbol *sym	= symbol_crt(name, type_scs, type_ts, len, val_i, val_s, label, flag, attr);

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
		return FALSE;
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

	symtbl_add(sym->name, sym->type_scs, sym->type_ts, sym->len, sym->val_i, sym->val_s, sym->label, sym->flag, sym->attr);	
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
PUBLIC	s8	symtbl_upd(s8 *name, s32 type_scs, s32 type_ts, s32 len, s32 val_i, s8 *val_s, s8* label, s8 flag, s8 attr)
{
	struct symbol *	p = symtbl_search(name);

	if(p == NULL)
	{
		printf("No symbol %s in symbol table\n", name);
		return FALSE;
	}

	p->type_scs	= type_scs;
	p->type_ts	= type_ts;
	p->len		= len;
	p->val_i	= val_i;
	p->flag		= flag;
	p->attr		= attr;
	
	strcopy(p->val_s, val_s);

	strcopy(p->label, label);
	
	return TRUE;
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
			printf("\n=========================================================================================\n");
			printf("%5s| %10s| %5s| %10s| %10s| %10s| %3s| %10s| %10s\n", "id","name","val_i","val_s","type_scs","type_ts","len",
				"label", "flag", "attr");
			printf("-----------------------------------------------------------------------------------------\n");

			printf("%5d| %10s| %5d| %10s| %10s| %10s| %3d| %10s|\n", p->id, p->name,p->val_i, p->val_s, (p->type_scs == 0? "NONE":(p_word+(p->type_scs)*20)), (p->type_ts == 0? "NONE":(p_word+(p->type_ts)*20)), p->len, p->label, p->flag, p->attr);

			printf("=========================================================================================\n");	
		}
	}


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
	sym->len	= 0;
	sym->val_i	= 0;
	sym->val_i_1	= 0;
	sym->val_s[0]	= NULL;
	sym->label[0]	= NULL;
	sym->head	= NULL;
	sym->tail	= NULL;		
	sym->flag	= FLAG_TEXT;
	sym->attr	= ATTR_VAR;
	sym->addr	= 0;	
}

