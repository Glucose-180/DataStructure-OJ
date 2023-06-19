#include <iostream>
#include <climits>

typedef int data_t;

using namespace std;

const unsigned int L = 1000U;

data_t dt[L];

unsigned int insertionsort_list(data_t* const D, const unsigned int N);
static unsigned int swap_g(data_t* const V, const unsigned int I, const unsigned int J);

int main()
{
	unsigned int i, j;
	data_t temp;

	cin >> temp;

	for (i = 0U; i < L; ++i)
		if (!(cin >> dt[i]))
			break;
	insertionsort_list(dt, i);
	for (j = 0U; j < i; ++j)
		cout << dt[j] << ' ';
	return 0;
}

// Sort H[0] to H[N-1], from less to great
unsigned int insertionsort_list(data_t* const D, const unsigned int N)
{
	unsigned int ymr = 0U;
	unsigned int* next = new unsigned int[N];
	unsigned int head = 0U,	// point to the first data in D
		i, j, k;

	// First: insert
	next[head] = UINT_MAX;	// initialize
	for (i = 1U; i < N; ++i)
	{	// insert D[i]
		if (D[i] < D[head])
			// set it as head
			next[i] = head, head = i;
		else
		{
			for (j = head, k = next[j]; k < UINT_MAX && D[k] < D[i]; j = k, k = next[k])
				;
			next[j] = i, next[i] = k;
		}
	}

	// Then: rearrange
	j = head;
	for (i = 0U; i < N; ++i)
	{
		// find the data that should be set at D[i]
		while (j < i)
			j = next[j];
		// k points to the next data to be arranged
		k = next[j];
		if (j != i)
		{
			unsigned int itemp;
			// swap D[j] and D[i]
			ymr += swap_g(D, i, j);
			itemp = next[j], next[j] = next[i], next[i] = itemp;
			// point to the data just moved
			next[i] = j;
		}
		j = k;
	}
	delete[] next;
	return ymr;
}

static unsigned int swap_g(data_t* const V, const unsigned int I, const unsigned int J)
{
	data_t temp = V[I];
	V[I] = V[J];
	V[J] = temp;
	return 1U;
}
