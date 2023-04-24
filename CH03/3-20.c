#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct direction {
	short v;
	short h;
};

const struct direction Dir[] = {
	{ -1,0 }, { 1,0 }, { 0,-1 }, { 0,1 }
};

char** graph;
int row, col;	/* size */

void draw(int i0, int j0);

int main()
{
	int i0, j0;		/* start */
	int i, j;

	scanf("%d%d%d%d%*d%*c", &row, &col, &i0, &j0);
	graph = (char**)malloc(sizeof(char*) * row);
	for (i = 0; i < row; ++i)
	{
		graph[i] = (char*)malloc(sizeof(char) * col);
		memset(graph[i], '0', col);
	}
	for (i = 0; i < row; ++i)
		for (j = 0; j < col; ++j)
		{
			if (getchar() == '1')
				graph[i][j] = '1';
			getchar();
		}

	draw(i0, j0);
	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < col; ++j)
			putchar(graph[i][j]);
		putchar('\n');
	}

	return 0;
}

void draw(int i0, int j0)
{
	int i = 0;

	if (graph[i0][j0] == '1')
		graph[i0][j0] = '2';
	else
		return;
	for (; i < 4; ++i)
	{
		if (i0 + Dir[i].v >= 0 && i0 + Dir[i].v < row && j0 + Dir[i].h >= 0 && j0 + Dir[i].h < col)
			draw(i0 + Dir[i].v, j0 + Dir[i].h);
	}
}