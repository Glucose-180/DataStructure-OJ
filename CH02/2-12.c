#include <stdio.h>
//#include <stdlib.h>

#define L 100

char A[L + 1], B[L + 1];

int main()
{
	char cd, ct;
	unsigned i = 0, j = 0;

	do {
		scanf("%c%c", &cd, &ct);
		A[i++] = cd;
	} while (ct != '\n');

	do {
		scanf("%c%c", &cd, &ct);
		B[j++] = cd;
	} while (ct != '\n');

	for (i = 0; A[i] == B[i] && A[i] != '\0'; ++i)
		;
	if (A[i] < B[i])
		putchar('1');
	else if (A[i] > B[i])
		putchar('2');
	else
		putchar('0');
	return 0;
}
