#include <stdio.h>
#include <ctype.h>

#define STKMAX 40

const char End = '\0';

char operator[STKMAX];
int operator_pt;

int exp_inf2pos(FILE* ifp, FILE* ofp);
char operator_gettop(void);
int operator_push(const char C);
char operator_pop(void);
char priority(const char C, const char D);
int operator_get_index(const char C);

int main()
{
	return exp_inf2pos(stdin, stdout);
}

int exp_inf2pos(FILE* ifp, FILE* ofp)
{
	char c;

	c = fgetc(ifp);
	if (!isalnum(c))
		return -1;
	while (c != '\n' && c != End || operator_gettop() != End)
	{
		if (isalnum(c))	/* c is an operand */
		{
			fputc(c, ofp);
			c = fgetc(ifp);
		}
		else
		{	/* c is an operator */
			switch (priority(operator_gettop(), c))
			{
			case '<':
				operator_push(c);
				c = fgetc(ifp);
				break;
			case '=':
				if (operator_pop() != '(')
					return 1;
				c = fgetc(ifp);
				break;
			case '>':
				fputc(operator_pop(), ofp);
				break;
			default:
				return 2;
				break;
			}
		}
	}
	return 0;
}

char operator_gettop()
{
	if (operator_pt > 0)
		return operator[operator_pt - 1];
	else
		return End;
}

int operator_push(const char C)
{
	if (operator_pt < STKMAX)
		operator[operator_pt++] = C;
	else
		return -1;
}

char operator_pop()
{
	if (operator_pt > 0)
	{
		return operator[--operator_pt];
	}
	else
		return End;
}

char priority(const char C, const char D)
{
	/* C appears first */
	static const char Priority[][7] = {
		'>', '>', '<', '<', '<', '>', '>',
		'>', '>', '<', '<', '<', '>', '>',
		'>', '>', '>', '>', '<', '>', '>',
		'>', '>', '>', '>', '<', '>', '>',
		'<', '<', '<', '<', '<', '=', '*', /* * is error */
		'>', '>', '>', '>', '*', '>', '>',
		'<', '<', '<', '<', '<', '*', '='
	};
	return Priority[operator_get_index(C)][operator_get_index(D)];
}

int operator_get_index(const char C)
{
	switch (C)
	{
	case '+':
		return 0;
		break;
	case '-':
		return 1;
		break;
	case '*':
		return 2;
		break;
	case '/':
		return 3;
		break;
	case '(':
		return 4;
		break;
	case ')':
		return 5;
		break;
	default:
		return 6;
		break;
	}
}
