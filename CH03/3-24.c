#include <stdio.h>

int fg(int m, int n);

int main()
{
	int m, n;

	scanf("%d,%d", &m, &n);
	printf("%d", fg(m, n));
	return 0;
}

int fg(int m, int n)
{
	if (m == 0)
		return 0;
	else
		return fg(m - 1, 2 * n) + n;
}