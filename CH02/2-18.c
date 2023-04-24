#include <stdio.h>
#include <stdlib.h>

typedef struct list_node {
	int data;
	struct list_node *next;
} list_node;

int main()
{
	char c;
	int dt;

	list_node *list_head, *p, *q;
	scanf("%d%c", &dt, &c);
	p = list_head = (list_node *)malloc(sizeof(list_node));
	list_head->next = NULL;
	list_head->data = dt;

	while (c != '\n')
	{
		scanf("%d%c", &dt, &c);
		p = p->next = (list_node *)malloc(sizeof(list_node));
		p->data = dt;
		p->next = NULL;
	}

	scanf("%d", &dt);
	p = list_head;
	if (dt <= 0)
	{
		list_head = p->next;
		free(p);
	}
	else
	{
		while (--dt)
			p = p->next;
		q = p->next;
		p->next = q->next;
		free(q);
	}

	if (list_head == NULL)
		printf("NULL");
	else
		for (p = list_head; p != NULL; p = p->next)
			printf("%d ", p->data);
	return 0;
}
