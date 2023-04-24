#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef struct graph_node {
	char data;
	int l, r;
} graph_node;

graph_node* g;

void graph_print_pos(const int I);

int main()
{
	int n, c, i;
	graph_node* p;

	scanf("%d", &n);
	p = g = (graph_node*)malloc(sizeof(graph_node) * n);
	i = 0;
	while ((c = 0) || scanf("%*c%c", &c) == 1)
	{
		g[i].data = c;
		if (isalpha(c))
		{
			g[i].l = g[i].r = -1;
		}
		else
		{	/* c is operator */
			scanf("%d%d", &(g[i].r), &(g[i].l));
		}
		++i;
	}
	if (i != n)
		return 2;
	graph_print_pos(0);
	putchar('\n');
	return 0;
}

void graph_print_pos(const int I)
{
	if (I >= 0)
	{
		graph_print_pos(g[I].l);
		graph_print_pos(g[I].r);
		putchar(g[I].data);
	}
}