#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int fib(unsigned int k, unsigned int m);

int main()
{
	unsigned int k, m;

	scanf("%u%u", &k, &m);
	printf("%u", fib(k, m));
	return 0;
}

unsigned int fib(unsigned int k, unsigned int m)
{
	unsigned int *pt;
	unsigned int i;

	if (m == k - 1)
		return 1;
	else if (m < k - 1)
		return 0;
	else /* m >= k */
	{
		if ((pt = (unsigned int *)malloc(sizeof(unsigned int) * (k + 1) )) == NULL)
			return -1;
		memset(pt, 0, sizeof(unsigned int) * (k - 1));
		pt[k - 1] = 1;

		for (pt[k] = 0, i = 0; i < k; ++i)
			pt[k] += pt[i];
		while (--m >= k)
		{
			for (i = 0; i < k; ++i)
				pt[i] = pt[i + 1];
			for (pt[k] = 0, i = 0; i < k; ++i)
				pt[k] += pt[i];
		}
		return pt[k];
		/* free!! */
	}
}
