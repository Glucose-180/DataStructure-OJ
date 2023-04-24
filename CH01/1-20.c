#include <stdio.h>
#include <stdlib.h>

typedef int pol_t;

pol_t horner(pol_t x0, pol_t *coef, unsigned int deg);

int main()
{
	pol_t x0;
	unsigned int n, i;
	pol_t *coef;

	scanf("%d%u", &x0, &n);
	if ((coef = (pol_t *)malloc(sizeof(pol_t) * (n + 1))) == NULL)
		return 1;
	for (i = 0; i <= n; ++i)
		scanf("%d", coef + i);

	printf("%d", horner(x0, coef, n));
	free(coef);
	return 0;
}

pol_t horner(pol_t x0, pol_t *coef, unsigned int deg)
{
	unsigned int i;

	pol_t rt = coef[deg];
	for (i = 1; i <= deg; ++i)
		rt = rt * x0 + coef[deg - i];
	return rt;
}
