[BITS	32]
extern	L0
[section .text]
global	_start

_start:
	mov	ebx, 5
	mov	eax, 67

	push	ebx		;5
	push	eax		;char 'C'
	call	L0
	add	esp, 8		;point to esi(pid)

	mov	ebx, 0
	mov	eax, 1
	int	0x80
	;jmp	$
	;hlt
