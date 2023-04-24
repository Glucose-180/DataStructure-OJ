#include <stdio.h>

#define L 100

int va[L];
unsigned int pt;  /* pointer, initially 0 */

int main()
{
	unsigned int i;
	int temp;

	while ((scanf("%d", va + pt)) == 1)
		++pt;
	for (i = pt - 1; i > 0 && va[i] < va[i - 1]; --i)
		temp = va[i], va[i] = va[i - 1], va[i - 1] = temp;
	for (i = 0; i < pt; ++i)
		printf("%d ", va[i]);
	return 0;
}
