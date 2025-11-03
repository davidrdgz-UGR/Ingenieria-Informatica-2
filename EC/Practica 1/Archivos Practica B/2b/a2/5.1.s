.data

lista:	.int 0xffffffff, 1
n:	.int (. - lista) / 4
resultado: .quad 0

.text
	.globl _start

_start:
	mov $lista, %rdi
	mov n, %esi
	call suma
	mov %eax, resultado
	mov %edx, resultado + 4
	
	mov $60, %eax
	mov resultado, %rdi
	syscall
	
######################################################
# unsigned long long suma(unsigned *lista, unsigned n)
#            edx:eax                  rdi         esi
######################################################

suma:
	xor %eax, %eax # resultado = 0 (parte baja)
	xor %edx, %edx # resultado = 0 (parte alta)
	xor %ecx, %ecx # i = 0
.Lbucle:
	cmp %ecx, %esi # n - i
	je .Lfin 
	add (%rdi,%rcx,4), %eax # r += lista[i]
	jnc .Lcont
	inc %edx	
.Lcont:
	inc %ecx
	jmp .Lbucle
.Lfin:	
	ret
