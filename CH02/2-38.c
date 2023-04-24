#include <stdio.h>
#include <stdlib.h>

typedef struct list_node {
	int data;
	struct list_node *last;
	struct list_node *next;
	unsigned int freq;
} lnode;

lnode *list_locate(lnode *lhead, int data);
void list_sort(lnode *lhead);
unsigned int access_order_locate(int dt, unsigned int pt);

unsigned int n;
int *access_order;
unsigned int access_order_pt;

int main()
{
	lnode *lhead, *p;
	int dt;
	char c;
	unsigned int i;

	p = lhead = (lnode *)malloc(sizeof(lnode));
	lhead->last = lhead->next = lhead;

	scanf("%u", &n);
	access_order = (int *)malloc(sizeof(int));

	do {
		scanf("%d%c", &dt, &c);
		p = p->next = (lnode *)malloc(sizeof(lnode));
		p->data = dt;
		p->freq = 0;
		p->last = lhead->last;
		p->next = lhead;
		lhead->last = p;
	} while (c != '\n');

	do {
		scanf("%d%c", &dt, &c);

		p = list_locate(lhead, dt);
		p->freq++;

		for (i = 0; i < access_order_pt; ++i)
			if (access_order[i] == dt)
				break;
		if (i == access_order_pt)
			access_order[access_order_pt++] = dt;

	} while (c == ' ');

	list_sort(lhead);

	for (p = lhead->next; p != lhead; p = p->next)
		printf("%d ", p->data);
	return 0;
}

/* Locate data in lhead. Return lhead if not found. */
lnode *list_locate(lnode *lhead, int data)
{
	lnode *p;

	for (p = lhead->next; p != lhead && p->data != data; p = p->next)
		;
	return p;
}

/* bubble sort */
void list_sort(lnode *lhead)
{
	lnode *h, *t;
	int data_temp;
	unsigned int freq_temp;

	for (t = lhead; t != lhead->next; t = t->last)
		for (h = lhead->next->next; h != t; h = h->next)
			if (h->freq > h->last->freq || h->freq == h->last->freq && access_order_locate(h->data, access_order_pt) < access_order_locate(h->last->data, access_order_pt))
			{
				data_temp = h->data, h->data = h->last->data, h->last->data = data_temp;
				freq_temp = h->freq, h->freq = h->last->freq, h->last->freq = freq_temp;
			}
}

unsigned int access_order_locate(int dt, unsigned int pt)
{
	unsigned int i;

	for (i = 0; i < pt; ++i)
		if (access_order[i] == dt)
			break;
	return i;
}
