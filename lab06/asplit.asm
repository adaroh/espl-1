
section	.text
    global _start			;must be declared for linker (ld)
    global getopt
    global error
    global fread
    global fwrite
    global fopen
    global fclose
    



extern main
_start:					;tell linker entry point
	mov	edi,DWORD 0	;edi is the counter for our checksum
	mov	esi,DWORD 1	;esi is the counter for the number of files created
	push	ebp
	mov	ebp, esp
	call	fopen
	mov 	ebx.eax		;copy file descriptor to ebx
	
loop:
	call fread
	mov ecx,eax		;copy number of bytes read to ecx
	
	
	
error:
	
	
	



fread:
	mov	eax,3
	mov	ecx,chunk
	mov	edx,DWORD 1024
	int 0x80
	ret

fwrite:				;write to file or print to screen
	mov	eax,4
	mov	ebx,[esp+4]
	mov	ecx,[esp+8]
	mov	edx,[esp+12]
	int 0x80
	ret

openRead:
	mov	eax,5
	mov	ebx,[esp+8]
	mov	ecx,0
	int 0x80
	ret

openWrite:
	mov	eax,5
	mov	ebx,[esp+8]
	mov	ecx,577
	mov	edx,666o
	int 0x80
	ret
fclose:
	mov	eax,6
	mov	ebx,[esp+4]
	int 0x80
	ret


section	.data

chunk	resb 1024
newFile	resb 100
filename db [esp+8]



printf

rewind ???
strcat

