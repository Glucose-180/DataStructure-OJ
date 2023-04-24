#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define L 100

typedef struct tree_node {
	int data;
	struct tree_node* left, * right;
} tree_node;

char buf1[L], buf2[L];
char* pbuf;

tree_node* create_from_preorder(FILE* fp);
int locate_and_print(tree_node* const T, const int Target);
void reverse(char* s);

int main()
{
	tree_node* ptree;
	int c, d;
	int i;

	ptree = create_from_preorder(stdin);
	while (isspace(c = getchar()))
		;
	while (isspace(d = getchar()))
		;
	pbuf = buf1;
	locate_and_print(ptree, c);
	reverse(buf1);

	pbuf = buf2;
	locate_and_print(ptree, d);
	reverse(buf2);

	for (i = 0; buf1[i] == buf2[i] && buf1[i] != '\0'; ++i)
		;
	if (buf1[i] == '\0' || buf2[i] == '\0')
	{
		if ((i -= 2) < 0)
			i = 0;
	}
	else
		--i;
	putchar(buf1[i]);
	return 0;
}

tree_node* create_from_preorder(FILE* fp)
{
	static const int Null = '^';
	int c;
	tree_node* rt;

	if ((c = fgetc(fp)) == Null || c == EOF)
		return NULL;
	else
	{
		rt = (tree_node*)malloc(sizeof(tree_node));
		if (rt == NULL)
			return NULL;	/* Failed */
		rt->data = c;
		rt->left = create_from_preorder(fp);
		rt->right = create_from_preorder(fp);
		return rt;
	}
}

/* locate Target in tree T, and print the path reversely in pbuf */
int locate_and_print(tree_node* const T, const int Target)
{
	if (T == NULL)
		return 0;	/* not found */
	if (T->data == Target)
	{
		*pbuf++ = T->data;
		return 1;	/* found */
	}
	if (T->left != NULL && locate_and_print(T->left, Target) != 0)
	{
		*pbuf++ = T->data;
		return 1;
	}
	if (T->right != NULL && locate_and_print(T->right, Target) != 0)
	{
		*pbuf++ = T->data;
		return 1;
	}
	return 0;
}

void reverse(char* s)
{
	char* t = s;
	char temp;

	while (*t != '\0')
		++t;
	while (t > s)
	{
		temp = *s;
		*s++ = *--t;
		*t = temp;
	}
}