#include <stdio.h>

#define L 100

char s[L], t[L];

int strcmp_g(const char* s, const char* t);

int main()
{
	int r;
	scanf("%s%s", s, t);
	if ((r = strcmp_g(s, t)) > 0)
		putchar('1');
	else if (r == 0)
		putchar('0');
	else
		printf("-1");
	return 0;
}

int strcmp_g(const char* s, const char* t)
{
	for (; *s == *t && *s != '\0'; ++s, ++t)
		;
	return *s - *t;
}