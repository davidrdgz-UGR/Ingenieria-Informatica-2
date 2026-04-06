	.file	"SumaVectoresC-global.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Faltan n\302\272 componentes del vector"
	.align 8
.LC2:
	.string	"/ V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC3:
	.string	"Tiempo(seg.):%11.9f\t / Tama\303\261o Vectores:%u\t/ V1[0]+V2[0]=V3[0](%8.6f+%8.6f=%8.6f) // V1[%d]+V2[%d]=V3[%d](%8.6f+%8.6f=%8.6f) /\n"
	.align 8
.LC4:
	.string	"Tiempo(seg.):%11.9f\t / Tama\303\261o Vectores:%lu\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB39:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$56, %rsp
	.cfi_def_cfa_offset 112
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	cmpl	$1, %edi
	jle	.L25
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol@PLT
	movl	%eax, %r12d
	cmpl	$10000000, %eax
	ja	.L15
	cmpl	$8, %eax
	ja	.L3
	testl	%eax, %eax
	je	.L4
	pxor	%xmm1, %xmm1
	movsd	.LC1(%rip), %xmm3
	leaq	v1(%rip), %r13
	leaq	v2(%rip), %rbp
	cvtsi2sdl	%eax, %xmm1
	xorl	%eax, %eax
	mulsd	%xmm3, %xmm1
	.p2align 4,,10
	.p2align 3
.L5:
	pxor	%xmm0, %xmm0
	movapd	%xmm1, %xmm2
	cvtsi2sdl	%eax, %xmm0
	mulsd	%xmm3, %xmm0
	addsd	%xmm0, %xmm2
	movsd	%xmm2, 0(%r13,%rax,8)
	movapd	%xmm1, %xmm2
	subsd	%xmm0, %xmm2
	movsd	%xmm2, 0(%rbp,%rax,8)
	addq	$1, %rax
	cmpl	%eax, %r12d
	ja	.L5
.L6:
	movq	%rsp, %rsi
	xorl	%edi, %edi
	leaq	v3(%rip), %r14
	call	clock_gettime@PLT
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L8:
	movsd	0(%r13,%rax,8), %xmm0
	addsd	0(%rbp,%rax,8), %xmm0
	movsd	%xmm0, (%r14,%rax,8)
	addq	$1, %rax
	cmpl	%eax, %r12d
	ja	.L8
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	movq	24(%rsp), %rax
	pxor	%xmm0, %xmm0
	subq	8(%rsp), %rax
	cvtsi2sdq	%rax, %xmm0
	pxor	%xmm1, %xmm1
	movq	16(%rsp), %rax
	subq	(%rsp), %rax
	cvtsi2sdq	%rax, %xmm1
	divsd	.LC5(%rip), %xmm0
	addsd	%xmm1, %xmm0
	cmpl	$9, %r12d
	jbe	.L26
	leal	-1(%r12), %eax
	movsd	(%r14), %xmm3
	movsd	0(%rbp), %xmm2
	movl	%r12d, %edx
	movsd	(%r14,%rax,8), %xmm6
	movq	%rax, %rcx
	movl	%eax, %r9d
	movl	%eax, %r8d
	movsd	0(%rbp,%rax,8), %xmm5
	movsd	0(%r13,%rax,8), %xmm4
	leaq	.LC3(%rip), %rsi
	movl	$1, %edi
	movsd	0(%r13), %xmm1
	movl	$7, %eax
	call	__printf_chk@PLT
.L11:
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L27
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L15:
	.cfi_restore_state
	movl	$10000000, %r12d
.L3:
	xorl	%edi, %edi
	leaq	v1(%rip), %r13
	leaq	v2(%rip), %rbp
	call	time@PLT
	movq	%r13, %rbx
	movq	%rbp, %r14
	movq	%rax, %rdi
	call	srand48@PLT
	leal	-1(%r12), %eax
	leaq	8(%r13), %rdx
	leaq	(%rdx,%rax,8), %r15
	.p2align 4,,10
	.p2align 3
.L7:
	call	drand48@PLT
	addq	$8, %rbx
	addq	$8, %r14
	movsd	%xmm0, -8(%rbx)
	call	drand48@PLT
	movsd	%xmm0, -8(%r14)
	cmpq	%rbx, %r15
	jne	.L7
	jmp	.L6
.L26:
	movl	%r12d, %edx
	movl	$1, %edi
	movl	$1, %eax
	xorl	%ebx, %ebx
	leaq	.LC4(%rip), %rsi
	leaq	.LC2(%rip), %r15
	call	__printf_chk@PLT
	.p2align 4,,10
	.p2align 3
.L10:
	movsd	0(%r13,%rbx,8), %xmm0
	movl	%ebx, %edx
	movl	%ebx, %r8d
	movl	%ebx, %ecx
	movsd	(%r14,%rbx,8), %xmm2
	movsd	0(%rbp,%rbx,8), %xmm1
	movq	%r15, %rsi
	movl	$1, %edi
	movl	$3, %eax
	addq	$1, %rbx
	call	__printf_chk@PLT
	cmpl	%ebx, %r12d
	ja	.L10
	jmp	.L11
.L4:
	movq	%rsp, %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	leaq	16(%rsp), %rsi
	xorl	%edi, %edi
	call	clock_gettime@PLT
	movq	24(%rsp), %rax
	pxor	%xmm0, %xmm0
	xorl	%edx, %edx
	subq	8(%rsp), %rax
	pxor	%xmm1, %xmm1
	movl	$1, %edi
	cvtsi2sdq	%rax, %xmm0
	movq	16(%rsp), %rax
	subq	(%rsp), %rax
	divsd	.LC5(%rip), %xmm0
	cvtsi2sdq	%rax, %xmm1
	leaq	.LC4(%rip), %rsi
	movl	$1, %eax
	addsd	%xmm1, %xmm0
	call	__printf_chk@PLT
	jmp	.L11
.L27:
	call	__stack_chk_fail@PLT
.L25:
	leaq	.LC0(%rip), %rdi
	call	puts@PLT
	orl	$-1, %edi
	call	exit@PLT
	.cfi_endproc
.LFE39:
	.size	main, .-main
	.globl	v3
	.bss
	.align 32
	.type	v3, @object
	.size	v3, 80000000
v3:
	.zero	80000000
	.globl	v2
	.align 32
	.type	v2, @object
	.size	v2, 80000000
v2:
	.zero	80000000
	.globl	v1
	.align 32
	.type	v1, @object
	.size	v1, 80000000
v1:
	.zero	80000000
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	-1717986918
	.long	1069128089
	.align 8
.LC5:
	.long	0
	.long	1104006501
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04.3) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
