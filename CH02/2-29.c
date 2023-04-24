#include <stdio.h>
#include <stdlib.h>

typedef struct list_node {
	int data;
	struct list_node *next;
} list_node;

int list_search(list_node *head, int data);

int main()
{
	list_node *head_a, *head_b, *head_c, *p, *q;
	char dt;
	char c;

	head_a = (list_node *)malloc(sizeof(list_node));
	head_b = (list_node *)malloc(sizeof(list_node));
    head_c = (list_node *)malloc(sizeof(list_node));
	head_c->next = head_a->next = head_b->next = NULL;

    p = head_a;
    do {
        scanf("%c%c", &dt, &c);
        p = p->next = (list_node *)malloc(sizeof(list_node));
        p->data = dt;
        p->next = NULL;
    } while (c == ',');

    p = head_b;
    do {
        scanf("%c%c", &dt, &c);
        p = p->next = (list_node *)malloc(sizeof(list_node));
        p->data = dt;
        p->next = NULL;
    } while (c == ',');

    p = head_c;
    do {
        scanf("%c%c", &dt, &c);
        p = p->next = (list_node *)malloc(sizeof(list_node));
        p->data = dt;
        p->next = NULL;
    } while (c == ',');

    for (p = head_a; p->next != NULL; )
    {
        if (list_search(head_b, p->next->data) != 0 && list_search(head_c, p->next->data) != 0)
        {
            q = p->next;
            p->next = q->next;
            free(q);
        }
        else
            p = p->next; /* Cannot be set in for loop! */
            /* After a node is deleted, p becomes the prior of the node after the deleted node. So no need for p = p->next! */
    }

    for (p = head_a->next; p->next != NULL; p = p->next)
        printf("%c,", p->data);
    putchar(p->data);
}

int list_search(list_node *head, int data)
{
    for (head = head->next; head != NULL; head = head->next)
        if (head->data == data)
            return 1; /* found */
    return 0;
}
