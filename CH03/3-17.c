#include <stdio.h>

#define STKMAX 100

char stack[STKMAX];

int main()
{
	int i = 0, c;

	while ((c = getchar()) != '&')
	{
		stack[i++] = c;
	}
	while ((c = getchar()) != '@')
	{
		if (i <= 0 || stack[--i] != c)
			break;
	}
	if (c != '@' || i != 0)
		putchar('0');
	else
		putchar('1');
	return 0;
}