#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define L 100

unsigned int strrep(char* s, const char* t, const char* r);

int main(int argc, char* argv[])
{
	char s[L], t[L], r[L] = "";
	unsigned int ymr;

	scanf("%s%s%s", s, t, r);
	ymr = strrep(s, t, r);
	printf("%s", s);
	if (argc > 1)
		printf("\n%u\n", ymr);
	return 0;
}

/* replace t in s with r */
unsigned int strrep(char* s, const char* t, const char* r)
{
	size_t len_t, len_r, i;
	unsigned int ymr = 0;
	char* p, *q;

	len_t = strlen(t);
	len_r = strlen(r);
	while ((s = strstr(s, t)) != NULL)
	{
		if (len_t > len_r)
		{
			for (p = s + len_r, q = s + len_t; *p = *q; ++p, ++q)
				;
		}
		else if (len_t < len_r)
		{
			for (q = s + len_t; *q != '\0'; ++q)
				;
			p = q + (len_r - len_t);
			i = q - s - len_t + 1;
			while (i--)
				*p-- = *q--;
		}
		memcpy(s, r, len_r);
		++ymr;
	}
	return ymr;
}