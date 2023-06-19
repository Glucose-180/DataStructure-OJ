#include <iostream>
#include <climits>

typedef int data_t;

using namespace std;

const unsigned int L = 1000U;

data_t dt[L];

unsigned int qsort_ng(data_t* const D, const unsigned int L, const unsigned int R);

static inline int dt_comp(const data_t X, const data_t Y)
{
	if (X < Y)
		return -1;
	else if (X == Y)
		return 0;
	else
		return 1;
}

static unsigned int swap_g(data_t* const V, const unsigned int I, const unsigned int J)
{
	data_t temp = V[I];
	V[I] = V[J];
	V[J] = temp;
	return 1U;
}


int main()
{
	unsigned int i, j;

	for (i = 0U; i < L; ++i)
		if (!(cin >> dt[i]))
			break;
	qsort_ng(dt, 0, i - 1);
	for (j = 0U; j < i; ++j)
		cout << dt[j] << ' ';
	return 0;
}

// Sort D[L] to D[R], from less to great
// quick sort without recursion
unsigned int qsort_ng(data_t* const D, const unsigned int L, const unsigned int R)
{
	typedef struct stack_t {
		unsigned int l, r;
	} stack_t;

	stack_t* stack;

	unsigned int ymr = 0U,
		sp = 0U;	// stack pointer

	if (R <= L)
		return ymr;
	stack = new stack_t[R - L + 1];
	// push
	stack[sp].l = L, stack[sp].r = R, ++sp;

	while (sp > 0U)
	{
		unsigned int l, r, i, last;
		// pop
		l = stack[--sp].l, r = stack[sp].r;
		if (r <= l)
			continue;
		if (r == l + 1)
		{
			if (dt_comp(D[l], D[r]) > 0)
				ymr += swap_g(D, l, r);
			continue;
		}
		// r - l >= 2U
		ymr += swap_g(D, l, (l + r) / 2U);
		last = l;
		for (i = l + 1U; i <= r; ++i)
			if (dt_comp(D[i], D[l]) < 0)
				ymr += swap_g(D, i, ++last);
		ymr += swap_g(D, last, l);
		// push
		if (last > 0U)
			stack[sp].l = l, stack[sp].r = last - 1U, ++sp;
		stack[sp].l = last + 1U, stack[sp].r = r, ++sp;
	}
	delete[] stack;
	return ymr;
}
