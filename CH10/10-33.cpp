#include <iostream>

typedef int data_t;

using namespace std;

const unsigned int L = 1000U;

data_t dt[L];

unsigned int selectionsort_list(data_t* const D, const unsigned int N);

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
	selectionsort_list(dt, i);
	for (j = 0U; j < i; ++j)
		cout << dt[j] << ' ';
	return 0;
}

// Sort D[0] to D[N-1], from less to greater
// using linked list
unsigned int selectionsort_list(data_t* const D, const unsigned int N)
{
	typedef struct list_node {
		data_t data;
		list_node* next;
	} lnode;
	lnode* head, * p, * q, * temp;
	unsigned int ymr = 0U, i;

	if (N <= 0U)
		return ymr;
	// head node: it doesnot contain valid data
	head = new lnode;
	head->next = NULL;
	for (i = 0U; i < N; ++i)
	{	// generate a new node
		temp = new lnode;
		temp->data = D[i];
		temp->next = head->next;
		head->next = temp;
	}
	// begin sorting
	for (p = head; p->next != NULL; p = p->next)
	{	//select a node and hang it after p
		temp = p;
		for (q = p; q->next != NULL; q = q->next)
		{	// let temp points to the prior of the minimum node after p
			if (dt_comp(q->next->data, temp->next->data) < 0)
				temp = q;
		}
		q = temp, temp = temp->next;
		// now temp points to the minumum node
		if (p->next != temp)
		{	// hang temp after p
			q->next = temp->next;
			temp->next = p->next;
			p->next = temp;
			++ymr;
		}
	}
	// write back
	p = head->next;
	delete head;
	for (i = 0U; p != NULL; p = q, ++i)
	{
		q = p->next;
		D[i] = p->data;
		delete p;
	}
	return ymr;
}
