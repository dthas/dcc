;===========================================================================
; write.asm
;   Copyright (C) 2013 Free Software Foundation, Inc.
;   Originally by ZhaoFeng Liang <zhf.liang@outlook.com>
;
;This file is part of DTHAS_DLD.
;
;DTHAS_DLD is free software; you can redistribute it and/or modify
;it under the terms of the GNU General Public License as published by
;the Free Software Foundation; either version 2 of the License, or 
;(at your option) any later version.
;
;DTHAS_DLD is distributed in the hope that it will be useful,
;but WITHOUT ANY WARRANTY; without even the implied warranty of
;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;GNU General Public License for more details.
;
;You should have received a copy of the GNU General Public License
;along with DTHAS; If not, see <http://www.gnu.org/licenses/>.  
;===========================================================================

;ssize_t write(int fd, const void *buf, size_t count)

[BITS	32]

NR_WRITE	equ	4
STDOUTPUT	equ	1

global	dld_ex_write

[section .data]

strmsg		db	"func write....."

len		equ	11

[section .text]

;===============================================================
dld_ex_write:
;===============================================================

	push	eax
	push	ebx
	push	ecx
	push	edx

	mov	eax, NR_WRITE

	mov	ebx, STDOUTPUT		; output to screen
	mov	ecx, dword[esp + 20]	;
	mov	edx, dword[esp + 24]	;

	int	0x80
	
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax

	ret
