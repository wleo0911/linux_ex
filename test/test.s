	.file	"test.c"
	.globl	pData
	.section	.rodata
.LC0:
	.string	"hello World"
	.data
	.align 8
	.type	pData, @object
	.size	pData, 8
pData:
	.quad	.LC0
	.section	.rodata
.LC1:
	.string	"%s %p\n"
.LC2:
	.string	"%p\n"
.LC3:
	.string	"change"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	pData(%rip), %rdx
	movq	pData(%rip), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$200, %edi
	call	malloc
	movq	%rax, pData(%rip)
	movq	pData(%rip), %rax
	movq	%rax, %rsi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movq	pData(%rip), %rax
	movl	$8, %edx
	movl	$.LC3, %esi
	movq	%rax, %rdi
	call	strncpy
	movq	pData(%rip), %rdx
	movq	pData(%rip), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	nop
	movq	-8(%rbp), %rax
	xorq	%fs:40, %rax
	je	.L2
	call	__stack_chk_fail
.L2:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
