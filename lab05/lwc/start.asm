section .text
	
global _start
global read
global write
global open
global close
global strlen

extern main
_start:
	lea	ecx,[esp+4]
	push	ecx
	push	DWORD [esp+4]
	call	main
        mov     ebx,eax
	mov	eax,1
	int 0x80
read:
	mov	eax,3
	mov	ebx,[esp+4]
	mov	ecx,[esp+8]
	mov	edx,[esp+12]
	int 0x80
	ret
write:
	mov	eax,4
	mov	ebx,[esp+4]
	mov	ecx,[esp+8]
	mov	edx,[esp+12]
	int 0x80
	ret
open:
	mov	eax,5
	mov	ebx,[esp+4]
	mov	ecx,[esp+8]
	mov	edx,[esp+12]
	int 0x80
	ret
close:
	mov	eax,6
	mov	ebx,[esp+4]
	int 0x80
	ret
strlen:
	mov 	ecx,0
loop:
	mov	edx,[esp+8]
	movzx	edx, BYTE [edx]
	test	edx,edx
	je	finish
	add	ecx,1
	add	DWORD [edx],1
	jmp	loop
finish:
	mov 	eax,ecx
	ret