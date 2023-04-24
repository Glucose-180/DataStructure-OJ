#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef struct tree_node {
	int data;
	struct tree_node* left, * right;
} tree_node;

tree_node* create_from_preorder(FILE* fp);
void tree_print_inorder(const tree_node* const T);
char priority(const char C, const char D);
int operator_get_index(const char C);

int main()
{
	tree_node* ptree;

	ptree = create_from_preorder(stdin);
	tree_print_inorder(ptree);
	return 0;
}

tree_node* create_from_preorder(FILE* fp)
{
	static const int Null = '#';
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

void tree_print_inorder(const tree_node* const T)
{
	if (T != NULL)
	{
		if (T->left != NULL && !isalnum(T->left->data) && priority(T->left->data, T->data) == '<')
		{
			putchar('(');
			tree_print_inorder(T->left);
			putchar(')');
		}
		else
			tree_print_inorder(T->left);
		putchar(T->data);
		if (T->right != NULL && !isalnum(T->right->data) && priority(T->data, T->right->data) == '>')
		{
			putchar('(');
			tree_print_inorder(T->right);
			putchar(')');
		}
		else
			tree_print_inorder(T->right);
	}
}

char priority(const char C, const char D)
{
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