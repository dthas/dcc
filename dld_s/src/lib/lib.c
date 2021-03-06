//===========================================================================
// lib.c
//   Copyright (C) 2013 Free Software Foundation, Inc.
//   Originally by ZhaoFeng Liang <zhf.liang@outlook.com>
//
//This file is part of DTHAS_DLD.
//
//DTHAS_DLD is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or 
//(at your option) any later version.
//
//DTHAS_DLD is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with DTHAS; If not, see <http://www.gnu.org/licenses/>.  
//===========================================================================
#include	"dld_global.h"
#include	"dld_type.h"
#include	<stdio.h>
#include	"dld_prototype.h"

//===========================================================================
// fill '\0' to an buffer
//===========================================================================
PUBLIC	void	empty_buf(u32 start_addr, u32 size_in_byte)
{
	u32 size= size_in_byte;
	s8 *p	= (s8*)start_addr;

	u32 i;
	for(i=0; i < size; i++)
	{
		p[i] = '\0';
	} 
}

//===========================================================================
// strcopy(char *dest, char *src)
//===========================================================================
PUBLIC 	void 	strcopy(char *dest, char *src)
{
	while(*src != NULL)
	{
		*dest = *src;
		dest++;
		src++;
	}
}

//===========================================================================
// strcopy(char *dest, char *src)
//===========================================================================
PUBLIC 	void 	strcpy(char *dest, char *src, s32 len)
{
	s32 i;

	for(i=0; i<len; i++)
	{
		*dest++ = *src++;
	}	
}

//===========================================================================
// strcopy(char *dest, char *src)
//===========================================================================
PUBLIC 	void 	memcpy(u8 *dest, u8 *src, s32 len)
{
	s32 i;

	for(i=0; i<len; i++)
	{
		*dest++ = *src++;
	}	
}

//===========================================================================
// strcopy(char *dest, char *src)
//===========================================================================
PUBLIC 	int 	strlen(char *buf)
{
	int len = 0;

	while(*buf != NULL)
	{
		len++;
		buf++;
	}

	return len;
}

//===========================================================================
// strcopy(char *dest, char *src)
//===========================================================================
PUBLIC 	s8 	strcmp(char *dest, char *src)
{
	s32	lend = strlen(dest);
	s32	lens = strlen(src);

	if(lend != lens)
	{
		return FALSE;
	}

	for(; lend > 0; lend--)
	{
		if(*dest++ != *src++)
		{
			break;
		}		
	}

	if(lend == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//===========================================================================
// main
//===========================================================================
PUBLIC 	u8 	s2i(s8 * str)
{
	s32 len	= strlen(str);
	s32 sum = 0;

	s32 i,j,k;
	for(i=len-1, j=0; i>=0; i--,j++)
	{
		k 	= str[i] - '0';
		k 	= k * squ(j, 10);
		sum	= sum + k;
	}

	return sum;
}

//===========================================================================
// main
//===========================================================================
PUBLIC 	u32 	s2h(s8 * str)
{
	s32 len	= strlen(str);
	s32 sum = 0;
	s32 temp= 0;

	s32 i,j,k;
	for(i=len-1, j=0; i>=0; i--,j++)
	{
		switch(str[i])
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				k 	= str[i] - '0';
				break;
			case 'a':
				k	= 10;
				break;
			case 'b':
				k	= 11;
				break;
			case 'c':
				k	= 12;
				break;
			case 'd':
				k	= 13;
				break;
			case 'e':
				k	= 14;
				break;
			case 'f':
				k	= 15;
				break;
			default:
				break;
		}
		
		temp	= squ(j, 16);

		k 	= k * temp;

		sum	= sum + k;		
	}

	return sum;
}

//===========================================================================
// main
//===========================================================================
PUBLIC 	u8 	c2i(s8 ch)
{
	return(ch - 0x30);
}

//===========================================================================
// main
//===========================================================================
PUBLIC 	s32 	squ(s32 num, s32 ind)
{
	s32 i; 
	s32 res = 1;
	for(i=0; i<num; i++)
	{
		res = res * ind;
	}

	return res;
}

//===========================================================================
// i2s(int val, char *buf)
//===========================================================================
PUBLIC void i2s(int val, char *buf)
{
	int reminder 	= val % 10;
	val 		= val / 10;

	push_t(buf, reminder + '0');

	if(val != 0)
	{
		i2s(val, buf);
	}
}

//===========================================================================
// h2s(int val, char *buf)
//===========================================================================
PUBLIC void h2s(int val, char *buf)
{
	int reminder 	= val % 16;
	val 		= val / 16;

	if(reminder > 9)
	{
		push_t(buf, reminder -10 + 'a');
	}
	else
	{
		push_t(buf, reminder + '0');
	}

	if(val != 0)
	{
		h2s(val, buf);
	}
}

//===========================================================================
// h2s(int val, char *buf)
//===========================================================================
PUBLIC void i2h(int val, char *buf)
{
	int tmp_v;
	int i = 28;
	int j = 0;	

	s8 flg = 0;

	for(i=28; i>=0; i=i-4)
	{
		tmp_v = val >> i;
		tmp_v &= 0xF;

		if((tmp_v > 0) || (flg))
		{
			if(tmp_v < 9)
			{
				tmp_v = tmp_v + '0';
			}
			else
			{
				tmp_v = tmp_v + 87; 	//if tmp_v=10, then tmp_v = 87 + 10 = 97 = 'a'
			}
		
			*(buf+j) = tmp_v;
			j++;

			flg = 1;
		}
	}

	*(buf+j) = '\0';
}

//===========================================================================
// i2s(int val, char *buf)
//===========================================================================
PUBLIC void push_t(char *buf, char val)
{
	char tmp_buf[64];

	clear_buf(tmp_buf,64);

	strcopy(tmp_buf, buf);

	*buf = val;
	
	strcopy((buf+1), tmp_buf);
}

//===========================================================================
// clear_buf(char *buf, int len)
//===========================================================================
PUBLIC	void clear_buf(char *buf, int len)
{
	int i;
	for(i=0;i<len;i++)
	{
		*(buf+i) = '\0';
	}
}
