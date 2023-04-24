#include <stdio.h>

#define STKMAX 100

char stack[STKMAX];

int main()
{
	int i = 0, c;

	while ((c = getchar()) != '\n' && c != EOF)
	{
		if (c == '(')
			stack[i++] = c;
		else if (c == ')')
		{
			if (i <= 0 || stack[--i] != '(')
				break;
		}
	}
	if (c == ')' || i != 0)
		putchar('0');
	else
		putchar('1');
	return 0;
}