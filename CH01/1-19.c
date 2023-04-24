#include <stdio.h>

#define NMAX 11
#define L 20

unsigned int ans[L];

unsigned int calc(unsigned int n);

int main()
{
	unsigned int n, arrsize, i;

	scanf("%d%d", &n, &arrsize);
	if (n > arrsize || n > NMAX)
	{
		printf("-1");
		return 0;
	}
	for (i = 0; i < n; ++i)
		ans[i] = calc(i);
	for (i = 0; i < n; ++i)
		printf("%u ", ans[i]);
	return 0;
}

/* calc n!*2^n */
unsigned int calc(unsigned int n)
{
	unsigned int rt = 1;

	if (n == 0)
		return 1;
	n *= 2;
	do {
		rt *= n;
		n -= 2;
	} while (n > 0);
	return rt;
}
