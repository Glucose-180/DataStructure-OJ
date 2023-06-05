#include <iostream>

typedef int data_t;

using namespace std;

const unsigned int L = 100008U;

data_t dt[L];

void qsort_g(data_t* const V, const unsigned int L, const unsigned int R);
static void swap_g(data_t* const V, const unsigned int I, const unsigned int J);

int main()
{
	unsigned int i, j;
	data_t temp;

	cin >> temp;

	for (i = 0U; i < L; ++i)
		if (!(cin >> dt[i]))
			break;
	qsort_g(dt, 0, i - 1);
	for (j = 0U; j < i; ++j)
		cout << dt[j] << ' ';
	return 0;
}

void qsort_g(data_t* const V, const unsigned int L, const unsigned int R)
{
	unsigned int i;
	unsigned int last;

	if (L >= R)
		return;
	swap_g(V, L, (L + R) / 2);
	last = L;
	for (i = L + 1; i <= R; ++i)
		if (V[i] < V[L])
			swap_g(V, i, ++last);
	swap_g(V, last, L);
	if (last > 0)
		qsort_g(V, L, last - 1);
	qsort_g(V, last + 1, R);
}

static void swap_g(data_t* const V, const unsigned int I, const unsigned int J)
{
	data_t temp = V[I];
	V[I] = V[J];
	V[J] = temp;
}