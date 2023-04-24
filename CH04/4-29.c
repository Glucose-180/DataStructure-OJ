#include <stdlib.h>
#include <stdio.h>

typedef struct snode {
	char data;
	struct snode* lnext;
} snode;

typedef struct tnode {
	char data;
	struct tnode* lnext;	/* list next */
	struct tnode* cnext;	/* comp next */
} tnode;

int main()
{
	int ls, lt;
	snode* s_head, * s;
	tnode* t_head, * t, * p, * q;
	char c;
	int i;

	scanf("%d%d%*c", &ls, &lt);
	s = s_head = (snode*)malloc(sizeof(snode));
	t = t_head = (tnode*)malloc(sizeof(tnode));
	s_head->lnext = t_head->lnext = t_head->cnext = NULL;

	while ((c = getchar()) != '\n')
	{
		s = s->lnext = (snode*)malloc(sizeof(snode));
		s->data = c;
		s->lnext = NULL;
	}
	while ((c = getchar()) != '\n')
	{
		t = t->lnext = (tnode*)malloc(sizeof(tnode));
		t->data = c;
		t->lnext = t->cnext = NULL;
	}

	t_head->lnext->cnext = t_head;
	/* flag of going one step on s, see 'next_data[0] = -1;' */
	for (p = t_head->lnext; p->lnext != NULL; p = p->lnext)
	{
		q = p;
		c = q->data;
		do {
			q = q->cnext;
			if (q == t_head)
				break;
		} while (c != q->data);
		p->lnext->cnext = q->lnext;
	}

	s = s_head->lnext;
	t = t_head->lnext;
	i = 0;
	while (s != NULL && t != NULL)
	{
		if (t == t_head || s->data == t->data)
			s = s->lnext, t = t->lnext, ++i;
		else
			t = t->cnext;
	}
	if (t == NULL)
	{
		printf("%d\n", i - lt);
	}
	else
		printf("-1\n");
	return 0;
}
