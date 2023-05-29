#include <stdio.h>

#define L 50
int buf[L];

void shellsort(int *v, int n);

int main()
{
	int i = 0, j;
	int dt;

	while (scanf("%d", &dt) == 1)
	{
		if (dt >= 0)
			buf[i++] = dt;
	}
	shellsort(buf, i);
	for (j = 0; j < i; ++j)
		printf("%d ", buf[j]);
	return 0;
}

void shellsort(int *v, int n)
{
	int i, j, g;
	int t;

	for (g = n / 2; g > 0; g /= 2)
		for (i = g; i < n; ++i)
			for (j = i - g; j >= 0 && v[j] > v[j + g]; j -= g)
			{
				t = v[j];
				v[j] = v[j + g];
				v[j + g] = t;
			}
}
