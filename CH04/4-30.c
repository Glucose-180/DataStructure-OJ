#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define L 100

char str[L], buf[L];

int strnstr(const char* str, const char* pt);

int main(int argc, char* argv[])
{
	int len, slen;	/* length of substring */
	int i;

	scanf("%s", str);
	for (slen = (len = strlen(str)) - 1; slen > 0; --slen)
	{
		buf[slen] = '\0';
		for (i = 0; i <= len - slen; ++i)
		{
			strncpy(buf, str + i, slen);
			if (strnstr(str, buf) > 1)
			{
				slen = -slen;	/* flag of exit the out for */
				break;
			}
		}
	}
	if (slen < 0)
	{
		printf("%s %d", buf, i);
	}
	else
		printf("-1");
	return 0;
}

/* return the times that pt appeared in str */
int strnstr(const char* str, const char* pt)
{
	int ymr = 0;

	if (str == NULL || pt == NULL)
		return -1;
	while ((str = strstr(str, pt)) != NULL)
		++str, ++ymr;
	return ymr;
}