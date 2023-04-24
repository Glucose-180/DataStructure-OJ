#include <stdio.h>
#include <string.h>

char A[201], B[201];

int main()
{
  	int rt;

	scanf("%s%s", A, B);
	if((rt = strcmp(A, B)) < 0)
      	putchar('1');
  	else if(rt == 0)
      	putchar('0');
  	else
      	putchar('2');
  	return 0;
}
