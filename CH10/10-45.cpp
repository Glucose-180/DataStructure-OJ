#include <iostream>

typedef int data_t;

using namespace std;

const unsigned int L = 1000U;

data_t dt[L];

static unsigned int swap_g(data_t* const V, const unsigned int I, const unsigned int J)
{
	data_t temp = V[I];
	V[I] = V[J];
	V[J] = temp;
	return 1U;
}

unsigned int radixsort(data_t* const D, const unsigned int N);

int main()
{
	unsigned int i, j;

	for (i = 0U; i < L; ++i)
		if (!(cin >> dt[i]))
			break;
	radixsort(dt, i);
	for (j = 0U; j < i; ++j)
		cout << dt[j] << ' ';
	return 0;
}

// Sort D[0] to D[N-1], from less to greater
// data_t should be unsigned int!
unsigned int radixsort(data_t* const D, const unsigned int N)
{
	const static unsigned int pow10[] = {
		1U,10U,100U,1000U,10000U,100000U,1000000U,
		10000000U,100000000U,1000000000U
	};
	typedef struct list_node {
		data_t data;
		list_node* next;
	} lnode;
	unsigned int ymr = 0U, i, radix, j = 0U;
	lnode* list_head[10], * p, * head, * q;

	if (N <= 0U)
		return ymr;
	for (i = 0U; i < 10U; ++i)
		list_head[i] = NULL;
	for (i = 0U; i < N; ++i)
	{	// Distribute first
		// NOTE: every time, we insert the data in the first,
		// so it may cause instability
		p = new lnode;
		p->data = D[i];
		radix = (p->data) % pow10[j + 1] / pow10[j];
		p->next = list_head[radix];
		list_head[radix] = p;

		++ymr;
	}

	while (true)
	{
		bool flag_unique = false;
		// Collect
		lnode* tail;
		// find the head of new list
		for (i = 0U; i < 10U && list_head[i] == NULL; ++i)
			;
		head = list_head[i];
		list_head[i] = NULL;
		for (tail = head; tail->next != NULL; tail = tail->next)
			;
		for (++i; i < 10U; ++i)
		{
			if (list_head[i] == NULL)
				continue;
			tail->next = list_head[i];
			list_head[i] = NULL;
			for (tail = head; tail->next != NULL; tail = tail->next)
				;

			++ymr;
		}

		++j;
		// Distribute again
		for (p = head; p != NULL; p = q)
		{
			radix = (p->data) % pow10[j + 1] / pow10[j];
			if (list_head[radix] == NULL)
				list_head[radix] = p;
			else
			{
				for (q = list_head[radix]; q->next != NULL; q = q->next)
					;
				q->next = p;
			}
			q = p->next, p->next = NULL;
			// q must keeps p->next temporarily

			++ymr;
		}

		// Check whether there is only one list
		for (i = 0U; i < 10U; ++i)
		{
			if (list_head[i] != NULL)
			{
				if (flag_unique == true)
					break;
				else
					flag_unique = true;
			}
		}
		if (i >= 10U)
			// only one list
			break;
	}

	for (i = 0U; i < 10U; ++i)
		if (list_head[i] != NULL)
			break;
	head = list_head[i];
	// write back
	p = head;
	for (i = 0U; p != NULL; p = q, ++i)
	{
		q = p->next;
		D[i] = p->data;
		delete p;
	}
	return ymr;
}
