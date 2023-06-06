#include <stdio.h>

#define N 100000

int dt1[N], dt2[N];

unsigned long long n1, n2;

//const char *const Fmt = "%d ";

int get_data(void);
void prt_int(int d);
void merge(void);

int main()
{
	get_data();
	merge();
	return 0;
}

int get_data()
{
	char c;

	do {
		scanf("%d%c", dt1 + n1, &c);
		++n1;
	} while (c == ' ');

	do {
		scanf("%d%c", dt2 + n2, &c);
		++n2;
	} while (c == ' ');
	return n1 + n2;
}

void prt_int(int d)
{
	printf("%d ", d);
}

void merge()
{
	int *p1, *p2, *e1, *e2;

	__asm__ volatile
	(
		"leaq	dt1(%%rip), %0\n\t"
		"leaq	dt2(%%rip), %1\n\t"
		"movq	%0, %2\n\t"
		"movq	%1, %3\n\t"
		"movq	n1(%%rip), %%r11\n\t"
		"movq	n2(%%rip), %%r10\n\t"
		"leaq	(%2,%%r11,4), %2\n\t"
		"leaq	(%3,%%r10,4), %3\n"
		"0:\n\t"
		"cmpq	%2, %0\n\t"
		"jae	2f\n\t"		/* p1 ends */
		"cmpq	%3, %1\n\t"
		"jae	1f\n\t"		/* p2 ends */
		"movslq	(%0), %%rdi\n\t"
		"movslq	(%1), %%r11\n\t"
		"cmpq	%%rdi, %%r11\n\t"
		"cmovl	%%r11, %%rdi\n\t"
		"setl	%%r11b\n\t"
		"setge	%%r10b\n\t"
		"movsbq	%%r11b, %%r11\n\t"
		"movsbq	%%r10b, %%r10\n\t"
		"leaq	(%1,%%r11,4), %1\n\t"
		"leaq	(%0,%%r10,4), %0\n\t"
		"pushq	%0\n\t"
		"pushq	%1\n\t"
		"pushq	%2\n\t"
		"pushq	%3\n\t"
		"call	prt_int\n\t"
		"popq	%3\n\t"
		"popq	%2\n\t"
		"popq	%1\n\t"
		"popq	%0\n\t"
		"jmp	0b\n"
		"1:\n\t"
		"movslq	(%0), %%rdi\n\t"
		"pushq	%0\n\t"
		"pushq	%1\n\t"
		"pushq	%2\n\t"
		"pushq	%3\n\t"
		"call	prt_int\n\t"
		"popq	%3\n\t"
		"popq	%2\n\t"
		"popq	%1\n\t"
		"popq	%0\n\t"
		"addq	$4, %0\n\t"
		"cmpq	%2, %0\n\t"
		"jge	3f\n\t"
		"jmp	1b\n"
		"2:\n\t"
		"movslq	(%1), %%rdi\n\t"
		"pushq	%0\n\t"
		"pushq	%1\n\t"
		"pushq	%2\n\t"
		"pushq	%3\n\t"
		"call	prt_int\n\t"
		"popq	%3\n\t"
		"popq	%2\n\t"
		"popq	%1\n\t"
		"popq	%0\n\t"
		"addq	$4, %1\n\t"
		"cmpq	%3, %1\n\t"
		"jb 	2b\n"
		"3:"
		:"=&r" (p1), "=&r" (p2), "=&r" (e1), "=&r" (e2)
		:
		:"rdi", "r11", "r10"
	);
}
