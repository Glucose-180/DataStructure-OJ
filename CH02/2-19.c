#include <stdio.h>
#include <stdlib.h>

typedef struct list_node {
	int data;
	struct list_node *next;
} list_node;

int main()
{
	list_node *list_head, *p, *q;
	int dt;
	char c;
	int lower, upper;

	p = list_head = (list_node *)malloc(sizeof(list_node));
	list_head->next = NULL;

	do {
		scanf("%d%c", &dt, &c);
		p = p->next = (list_node *)malloc(sizeof(list_node));
		p->next = NULL;
		p->data = dt;
	} while (c != '\n');

	scanf("%d%d", &lower, &upper);
	for (p = list_head; p->next != NULL && p->next->data <= lower; p = p->next)
		;
	while (p->next != NULL && p->next->data < upper)
	{
		q = p->next;
		p->next = q->next;
		free(q);
	}

	for (p = list_head->next; p != NULL; p = p->next)
		printf("%d ", p->data);
	return 0;
}
