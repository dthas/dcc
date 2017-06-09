
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
	mov	ecx,0x3
	mov	dword[ebp+0x8],ecx

	mov	edx,0x5
	mov	dword[ebp+0xc],edx

	mov	ecx, dword[ebp+0xc]
	mov	edx, dword[ebp+0x8]
	add	edx, ecx
	mov	dword[temp_val], edx
	mov	esi, dword[temp_val]
	mov	dword[ebp-0x8],esi

	mov	ecx, dword[ebp+0xc]
	mov	edx, dword[ebp+0x8]
	cmp	ecx, edx
	ja	L4
	jmp	L5

L4:
	push	dword[ebp+0xc]
	call	L1
	add	esp, 0x4

	mov	dword[temp_val], eax

	jmp	L6

L5:
	push	dword[ebp+0x8]
	call	L1
	add	esp, 0x4

	mov	dword[temp_val], eax

L6:

	mov	esp, ebp
	pop	ebp
	ret

