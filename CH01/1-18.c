#include <stdio.h>

struct grade {
	unsigned int f;
	unsigned int m;
} college[5]; /* A~E */

int main()
{

	char gender, col_name;
	unsigned int g;

	while ((scanf("%*c %c %c %u%*c", &gender, &col_name, &g)) == 3)
	{
		if (gender == 'F')
			college[col_name - 'A'].f += g;
		else
			college[col_name - 'A'].m += g;
	}
	for (g = 0; g < 5; ++g)
	{
		if (college[g].m != 0)
			printf("%c M %u\n", 'A' + g, college[g].m);
		if (college[g].f != 0)
			printf("%c F %u\n", 'A' + g, college[g].f);
		if (college[g].f + college[g].m != 0)
			printf("%c %u\n", 'A' + g, college[g].f + college[g].m);
	}
	return 0;
}
