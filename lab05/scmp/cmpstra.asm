section .text
	global cmpstr
cmpstr:
	push	ebp
	mov	ebp, esp
loop:
	mov 	ebx, [ebp+8]
	movzx	ebx, BYTE [ebx]
	mov 	ecx, [ebp+12]
	movzx	ecx, BYTE [ecx]
	cmp	ebx,0
	je	after
	cmp 	ebx, ecx
	jne	after
	add 	DWORD [ebp+8],1
	add 	DWORD [ebp+12],1
	jmp	loop
after:
	cmp 	ebx,ecx
	jg	greater
	jl	lesser
	je	equal
greater:
	mov 	eax,1
	jmp 	finish
lesser:
	mov 	eax,2
	jmp 	finish
equal:
	mov 	eax,0
	jmp 	finish
finish:
	mov 	esp,ebp
	pop 	ebp
	ret