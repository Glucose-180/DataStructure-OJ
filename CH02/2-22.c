#include <stdio.h>
#include <stdlib.h>

typedef struct list_node {
	int data;
	struct list_node *next;
} list_node;

int list_reverse(list_node *list_head);

int main(int argc, char *argv[])
{
	list_node *list_head, *p;
	char dt;
	int rt;

	list_head = (list_node *)malloc(sizeof(list_node));
	list_head->next = NULL;
	p = list_head;
	while (scanf("%c%*c", &dt) == 1)
	{
		p = p->next = (list_node *)malloc(sizeof(list_node));
		p->data = dt;
		p->next = NULL;
	}
	rt = list_reverse(list_head);

	if (argc > 1)
		printf("%d\n", rt);
	for (p = list_head->next; p != NULL; p = p->next)
	{
		putchar(p->data);
		if (p->next != NULL)
			putchar(',');
	}
	return 0;
}

int list_reverse(list_node *list_head)
{
	list_node *p, *q, *r;
	int ymr = 1;

	if ((p = list_head->next) == NULL)
		return 0;  /* only 0 node */
	if ((q = p->next) == NULL)
		return 1;  /* only 1 node */
	r = q->next;
	p->next = NULL;  /* The first(not head) node becomes tail */
	while (1)
	{
		q->next = p;
		++ymr;
		if (r == NULL)
			break;
		p = q, q = r, r = r->next;
	}
	list_head->next = q;  /* The tail node becomes first */
	return ymr;
}
