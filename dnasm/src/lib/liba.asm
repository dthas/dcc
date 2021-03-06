;===========================================================================
; liba.asm
;   Copyright (C) 2013 Free Software Foundation, Inc.
;   Originally by ZhaoFeng Liang <zhf.liang@outlook.com>
;
;This file is part of DTHAS_DNASM.
;
;DTHAS_DNASM is free software; you can redistribute it and/or modify
;it under the terms of the GNU General Public License as published by
;the Free Software Foundation; either version 2 of the License, or 
;(at your option) any later version.
;
;DTHAS_DNASM is distributed in the hope that it will be useful,
;but WITHOUT ANY WARRANTY; without even the implied warranty of
;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;GNU General Public License for more details.
;
;You should have received a copy of the GNU General Public License
;along with DTHAS; If not, see <http://www.gnu.org/licenses/>.  
;===========================================================================
global	h2s_a
global	empty_buf_a
global	strlen_a

;========
strlen_a:
; strlen_a(char *buf)
; eax is the ret
;========
	push	ebx
	push	ecx

	mov	ebx, dword[esp + 12]	;buf
	xor	ecx, ecx
	

.1:
	cmp	byte[ebx + ecx], 0
	je	.3
	add	ecx, 1
	jmp	.1

.3
	mov	eax, ecx

	pop	ecx
	pop	ebx
	
	ret


;========
empty_buf_a:
; empty_buf_a(u32 buf_addr, u32 num)
;========
	push	ebx
	push	ecx

	mov	ecx, dword[esp + 16]	;num
	mov	ebx, dword[esp + 12]	;addr

.1:
	mov	byte[ebx + ecx], 0
	sub	ecx, 1
	cmp	ecx, 0
	ja	.1

	pop	ecx
	pop	ebx
	
	ret

;========
h2s_a:
; h2s_a(int num, char *buf)
;========
	push	eax
	push	ebx
	push	ecx
	push	edx
	push	esi

	mov	eax, dword[esp + 24]	; the num
	mov	esi, dword[esp + 28]	; the address of buf

	mov	edx,eax
	mov	cl,0x10
	shr	edx,cl
	mov	cl, 0x10
.1:	
	div	cl
	cmp	al, 0
	je	.3
	cmp	al, 9
	ja	.2

;0~9
	add	al, 0x30
	mov	byte[esi],al
	add	esi, 1
	mov	al, ah
	mov	ah, 0
	jmp	.1

;a~f
.2:
	add	al, 0x57
	mov	byte[esi],al
	add	esi, 1
	mov	al, ah
	mov	ah, 0
	jmp	.1
.3:
	cmp	ah, 9
	ja	.4

	add	ah, 0x30
	mov	byte[esi],ah
	add	esi, 1
	jmp	.5
.4:
	add	ah, 0x57
	mov	byte[esi],ah
	add	esi, 1
.5:
	
	pop	esi
	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
		
	ret
