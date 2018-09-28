	.file	"setjmp_vars.c"
	.text
	.local	env
	.comm	env,200,32
	.section	.rodata
	.align 8
.LC0:
	.string	"Inside doJump(): nvar=%d rvar=%d vvar=%d\n"
	.text
	.type	doJump, @function
doJump:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	-12(%rbp), %ecx
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, %esi
	leaq	env(%rip), %rdi
	call	longjmp@PLT
	.cfi_endproc
.LFE5:
	.size	doJump, .-doJump
	.section	.rodata
	.align 8
.LC1:
	.string	"After doJump(): nvar=%d rvar=%d vvar=%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$111, -4(%rbp)
	movl	$222, -24(%rbp)
	movl	$333, -8(%rbp)
	leaq	env(%rip), %rdi
	call	_setjmp@PLT
	testl	%eax, %eax
	jne	.L4
	movl	$777, -4(%rbp)
	movl	$888, %esi
	movl	$999, -8(%rbp)
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%eax, %edi
	call	doJump
	jmp	.L5
.L4:
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	movl	%edx, %ecx
	movl	-24(%rbp), %edx
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L5:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.3.0-16ubuntu3) 7.3.0"
	.section	.note.GNU-stack,"",@progbits
