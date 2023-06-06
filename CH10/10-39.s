	.file	"10-39.c"
	.text
	.comm	dt1,400000,32
	.comm	dt2,400000,32
	.comm	n1,8,8
	.comm	n2,8,8
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	call	get_data
	call	merge
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
.LC0:
	.string	"%d%c"
	.text
	.globl	get_data
	.type	get_data, @function
get_data:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
.L4:
	movq	n1(%rip), %rax
	leaq	0(,%rax,4), %rdx
	leaq	dt1(%rip), %rax
	leaq	(%rdx,%rax), %rcx
	leaq	-9(%rbp), %rax
	movq	%rax, %rdx
	movq	%rcx, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movq	n1(%rip), %rax
	addq	$1, %rax
	movq	%rax, n1(%rip)
	movzbl	-9(%rbp), %eax
	cmpb	$32, %al
	je	.L4
.L5:
	movq	n2(%rip), %rax
	leaq	0(,%rax,4), %rdx
	leaq	dt2(%rip), %rax
	leaq	(%rdx,%rax), %rcx
	leaq	-9(%rbp), %rax
	movq	%rax, %rdx
	movq	%rcx, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movq	n2(%rip), %rax
	addq	$1, %rax
	movq	%rax, n2(%rip)
	movzbl	-9(%rbp), %eax
	cmpb	$32, %al
	je	.L5
	movq	n1(%rip), %rax
	movl	%eax, %edx
	movq	n2(%rip), %rax
	addl	%edx, %eax
	movq	-8(%rbp), %rsi
	xorq	%fs:40, %rsi
	je	.L7
	call	__stack_chk_fail@PLT
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	get_data, .-get_data
	.section	.rodata
.LC1:
	.string	"%d "
	.text
	.globl	prt_int
	.type	prt_int, @function
prt_int:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	prt_int, .-prt_int
	.globl	merge
	.type	merge, @function
merge:
.LFB3:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
#APP
# 47 "10-39.c" 1
	leaq	dt1(%rip), %rsi
	leaq	dt2(%rip), %rcx
	movq	%rsi, %rdx
	movq	%rcx, %rax
	movq	n1(%rip), %r11
	movq	n2(%rip), %r10
	leaq	(%rdx,%r11,4), %rdx
	leaq	(%rax,%r10,4), %rax
0:
	cmpq	%rdx, %rsi
	jae	2f
	cmpq	%rax, %rcx
	jae	1f
	movslq	(%rsi), %rdi
	movslq	(%rcx), %r11
	cmpq	%rdi, %r11
	cmovl	%r11, %rdi
	setl	%r11b
	setge	%r10b
	movsbq	%r11b, %r11
	movsbq	%r10b, %r10
	leaq	(%rcx,%r11,4), %rcx
	leaq	(%rsi,%r10,4), %rsi
	pushq	%rsi
	pushq	%rcx
	pushq	%rdx
	pushq	%rax
	call	prt_int
	popq	%rax
	popq	%rdx
	popq	%rcx
	popq	%rsi
	jmp	0b
1:
	movslq	(%rsi), %rdi
	pushq	%rsi
	pushq	%rcx
	pushq	%rdx
	pushq	%rax
	call	prt_int
	popq	%rax
	popq	%rdx
	popq	%rcx
	popq	%rsi
	addq	$4, %rsi
	cmpq	%rdx, %rsi
	jge	3f
	jmp	1b
2:
	movslq	(%rcx), %rdi
	pushq	%rsi
	pushq	%rcx
	pushq	%rdx
	pushq	%rax
	call	prt_int
	popq	%rax
	popq	%rdx
	popq	%rcx
	popq	%rsi
	addq	$4, %rcx
	cmpq	%rax, %rcx
	jb 	2b
3:
# 0 "" 2
#NO_APP
	movq	%rsi, -32(%rbp)
	movq	%rcx, -24(%rbp)
	movq	%rdx, -16(%rbp)
	movq	%rax, -8(%rbp)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	merge, .-merge
	.ident	"GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
