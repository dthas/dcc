//===========================================================================
// printf.c
//   Copyright (C) 2013 Free Software Foundation, Inc.
//   Originally by ZhaoFeng Liang <zhf.liang@outlook.com>
//
//This file is part of DTHAS.
//
//DTHAS is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 2 of the License, or 
//(at your option) any later version.
//
//DTHAS is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with DTHAS; If not, see <http://www.gnu.org/licenses/>.  
//===========================================================================

int 	printi(int w);
int 	prints(char *cmd, ...);
int 	printf_exec(char *cmd, char *value);
int 	printcr();

extern	int 	strlen(char *buf);
extern	void	clear_buf(char *buf, int len);
extern	void	i2s(int val, char *buf);
extern	void 	strcopy(char *dest, char *src);
extern	void 	h2s(int val, char *buf);
extern	void	empty_buf(int start_addr, int size_in_byte);
extern	void	h2s_a(int num, char *buf);

//===========================================================================
// prints(char *cmd, ...)
//===========================================================================
int 	prints(char *cmd, ...)
{
	char *value = (char*)((char*)(&cmd) + 4);

	int ret = printf_exec(cmd, value);

	return ret;
}

//===========================================================================
// printf_exec(char *cmd, char *value)
//===========================================================================
int 	printf_exec(char *cmd, char *value)
{
	char output_buf[512];
	char tmp_buf[64];
	int  len = 0;
	char *head = output_buf;
	int  num;
	int  ret;
	int  i=0;
	
	while(*cmd)
	{
		if (*cmd == '%')
		{
			switch(*(++cmd))
			{
				case 'd' :
					clear_buf(tmp_buf,64);

					num = *(int*)(value);
					i2s(num, tmp_buf);
											
					len 	+= strlen(tmp_buf);			
					strcopy(head, tmp_buf);
					
					head 	+= len;
					value 	+= 4;
					cmd++;
					break;
				case 's' :
					len 	+= strlen((char*)(*(int*)value));  			
					strcopy(head, (char*)(*(int*)value));
					
					head 	+= len;
					value 	+= 4;
					cmd++;
					break;
				case 'c' :
					*head = *(value);
										
					head++;
					value 	+= 4;
					cmd++;
					break;
				case 'x' :
					clear_buf(tmp_buf,64);	

					num = *(int*)(value);
					i2h(num, tmp_buf);
					len 	+= strlen(tmp_buf);			
					strcopy(head, tmp_buf);	

					head 	+= len;
					value 	+= 4;
					cmd++;
					break;
				default:
					break;
			}
				
		}
		else
		{
			*head = *cmd;
			head++;
			cmd++;
		}
	}

	dcc_ex_write(output_buf, (head - output_buf));
}

//===========================================================================
// printi(int w)
//===========================================================================
int 	printi(int w)
{
	char tmp_buf[64];
	int len;

	empty_buf(tmp_buf, 64);	

	h2s_a(w, tmp_buf);
	len	= strlen(tmp_buf);
	
	dcc_ex_write(tmp_buf, len);
}

//===========================================================================
// printcr(int w)
//===========================================================================
int 	printcr(int w)
{
	char tmp_buf[64];
	int len;

	empty_buf(tmp_buf, 64);

	len	= 2;
	tmp_buf[0]	= 0xa;
	tmp_buf[1]	= '\0';
	
	dcc_ex_write(tmp_buf, len);
}
