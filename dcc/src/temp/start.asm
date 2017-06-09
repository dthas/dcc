[BITS	32]
extern	L0
global	_start

[section .text]

_start:
	mov	ebx, 0x5
	mov	eax, 0x43

	push	ebx		
	push	eax		
	call	L0
	add	esp, 0x8		

	mov	ebx, 0x0
	mov	eax, 0x1
	int	0x80
	
