#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct poly_item {
	int coe;
	int deg;
	struct poly_item *next;
} poly_item;

void poly_add_item(poly_item *polyh, char *item_buf, char sign);
void poly_deri(poly_item *polyh);
void poly_print(poly_item *polyh);

int main()
{
	char sign = +1, c;
	char item_buf[20];
	poly_item *polyh; /* head */

	polyh = (poly_item *)malloc(sizeof(poly_item));
	polyh->next = polyh;

	/* read poly */
	if ((c = getchar()) != '-')
		ungetc(c, stdin);
	else
		sign = -1;
	scanf("%s", item_buf);
	poly_add_item(polyh, item_buf, sign);
	while (scanf("%s", item_buf) == 1)
	{
		if (*item_buf == '+')
			sign = +1;
		else
			sign = -1;
		scanf("%s", item_buf);
		poly_add_item(polyh, item_buf, sign);
	}
	poly_deri(polyh);
	poly_print(polyh);

	return 0;
}

void poly_add_item(poly_item *polyh, char *item_buf, char sign)
{
	int coe, deg;
	char *p;
	poly_item *q, *r;

	if (*item_buf == 'x')
		coe = 1;
	else
		coe = atoi(item_buf) * sign;
	for (p = item_buf; *p != '\0'; ++p)
		if (*p == 'x')
			break;
	if (*p == '\0')
		deg = 0;
	else
	{
		if (*++p == '^')
			deg = atoi(++p);
		else
			deg = 1;
	}

	if (coe == 0)
		return;

	for (q = polyh; q->next != polyh; q = q->next)
		if (q->next->deg < deg)
			break;
	if (q != polyh && q->deg == deg)
	{
		if ((q->coe += coe) == 0)
		{
			/* delete q */
			for (r = polyh; r->next != q; r = r->next)
				;
			{
				r->next = q->next;
				free(q);
			}
		}
	}
	else
	{
		r = q->next;
		q = q->next = (poly_item *)malloc(sizeof(poly_item));
		q->next = r;
		q->deg = deg;
		q->coe = coe;
	}
}

void poly_deri(poly_item *polyh)
{
	poly_item *p, *q;

	for (p = polyh; p->next != polyh; )
	{
		if (p->next->deg != 0)
		{
			p->next->coe *= p->next->deg;
			p->next->deg--;
			p = p->next;
			/* Don't add it in for statement! */
		}
		else
		{
			q = p->next;
			p->next = q->next;
			free(q);
		}
	}
}

void poly_print(poly_item *polyh)
{
	poly_item *p;
	char flag_head = 1;

	if (polyh->next == polyh)
	{
		putchar('0');
		return;
	}
	for (p = polyh->next; p != polyh; p = p->next)
	{
		if (flag_head == 0)
		{
			if (p->coe > 0)
				printf(" + ");
			else
			{
				printf(" - ");
				p->coe *= -1;
			}
			printf("%d", p->coe);
			if (p->deg > 1)
			{
				printf("x^%d", p->deg);
			}
			else if (p->deg == 1)
				printf("x");
		}
		else
		{
			if (p->coe < 0)
			{
				printf("- ");
				p->coe *= -1;
			}
			printf("%d", p->coe);
			if (p->deg > 1)
			{
				printf("x^%d", p->deg);
			}
			else if (p->deg == 1)
				printf("x");
			flag_head = 0;
		}
	}
}
