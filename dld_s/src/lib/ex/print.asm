;===========================================================================
; print.asm
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

;in printi(int num)

[BITS	32]
global	printi_a

extern	empty_buf_a
extern	strlen_a
extern	dld_ex_write
extern	h2s_a

[section .data]
temp_buf	resb	64

[section .text]

;===============================================================
printi_a:
;===============================================================

	push	eax
	push	ebx	

	;----------------------------------------------
	;empty_buf_a(64, buf)
	;----------------------------------------------
	mov	eax, 64
		
	push	eax
	push	temp_buf
	call	empty_buf_a
	add	esp, 8

	;----------------------------------------------
	;h2s_a(w, tmp_buf);
	;----------------------------------------------
	mov	ebx, dword[esp + 12]

	push	temp_buf
	push	ebx
	call	h2s_a
	add	esp, 8

	;----------------------------------------------
	;strlen_a(tmp_buf)
	;----------------------------------------------
	push	temp_buf
	call	strlen_a
	add	esp, 4
	;eax = strlen(tmp_buf)
	
	;----------------------------------------------
	;dld_ex_write(tmp_buf, len);
	;----------------------------------------------
	push	eax		; len
	push	temp_buf
	call	dld_ex_write
	add	esp, 8

	pop	ebx
	pop	eax

	ret
