
[BITS	32]
global	L0
global	L1
extern	printi
extern	printcr

[section .data]
;==================================================================
;global
;==================================================================

temp_val	resb	4

[section .text]

;--------------------------------------------------------------
L1:
	push	ebp
	mov	ebp, esp
;--------------------------------------------------------------
	mov	eax, dword[ebp+0x8]
	mov	dword[ebp-0x8],eax

	mov	eax,0x7
	mov	ebx, dword[ebp-0x8]
	add	ebx, eax
	mov	dword[temp_val], ebx
	mov	eax,dword[temp_val]
	mov	dword[ebp-0x8],eax

	mov	eax,0x3
	mov	ebx, dword[ebp-0x8]
	add	ebx, eax
	mov	dword[temp_val], ebx
	mov	ebx,dword[temp_val]
	mov	dword[ebp-0xc],ebx

	push	dword[ebp-0xc]
	call	printi
	add	esp, 0x4

	mov	dword[temp_val], eax

	push	dword[ebp-0x8]
	call	printcr
	add	esp, 0x4

	mov	dword[temp_val], eax


	mov	esp, ebp
	pop	ebp
	ret


;--------------------------------------------------------------
L0:
	push	ebp
	mov	ebp, esp
;--------------------------------------------------------------
	mov	ecx,0x2
	mov	dword[ebp+0x8],ecx

	mov	edx,0x4
	mov	dword[ebp+0xc],edx

	push	eax
	push	ebx
	push	edx
	xor	edx, edx
	mov	ebx, dword[ebp+0xc]
	mov	eax, dword[ebp+0x8]
	mul	bx
	mov	dword[temp_val], eax
	pop	edx
	pop	ebx
	pop	eax

	mov	esi, dword[temp_val]
	mov	dword[ebp-0x8],esi

	push	dword[ebp-0x8]
	call	L1
	add	esp, 0x4

	mov	dword[temp_val], eax


	mov	esp, ebp
	pop	ebp
	ret

