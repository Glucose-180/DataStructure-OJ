#include <stdio.h>
#include <stdlib.h>

typedef struct list_node {
	int data;
	struct list_node *next;
} list_node;

int main()
{
	list_node *head_a, *head_b, *p;
	int dt;
	char c;

	head_a = (list_node *)malloc(sizeof(list_node));
	head_b = (list_node *)malloc(sizeof(list_node));
	head_a->next = head_b->next = NULL;

	scanf("%*d%*d");

	p = head_a;
	do {
		scanf("%d%c", &dt, &c);
		p->next = (list_node *)malloc(sizeof(list_node));
		p = p->next;
		p->data = dt;
		p->next = NULL;
	} while (c != '\n');

	p = head_b;
	while (scanf("%d", &dt) == 1)
	{
		p->next = (list_node *)malloc(sizeof(list_node));
		p = p->next;
		p->data = dt;
		p->next = NULL;
	}

	/* cat begin */
	p->next = head_a->next;
	free(head_a);

	for (p = head_b->next; p != NULL; p = p->next)
	{
		printf("%d ", p->data);
	}

	/* release */
	while (head_b != NULL)
	{
		p = head_b->next;
		free(head_b);
		head_b = p;
	}

	return 0;
}
