	.file	"t1.cpp"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
// define literal string
LC0:
	.ascii "Hello, World!\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
// define funcao 
_main:
LFB12:
//tac begin func
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	
	call	___main
	movl	$LC0, (%esp)
	call	_printf
	movl	$0, %eax
// TAC END FUNC
	leave
	ret
LFE12:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_printf;	.scl	2;	.type	32;	.endef
