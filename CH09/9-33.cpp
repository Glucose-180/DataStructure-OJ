#include <iostream>
using namespace std;

typedef int data_t;

struct treenode {
	data_t data;
	treenode* left, * right;
};

treenode* BST_add_node(treenode* const T, const data_t D);
void BST_print_ge(treenode* const T, const data_t M);

static inline int BST_cmp(const data_t D1, const data_t D2)
{
	if (D1 == D2)
		return 0;
	else if (D1 < D2)
		return -1;
	else
		return 1;
}

treenode* BST_add_node(treenode* const T, const data_t D)
{
	treenode* p = T, * q;
	int crt;

	while (p != NULL)
	{
		crt = BST_cmp(D, p->data);
		if (crt == 0)
			return T;	// D already exists
		else if (crt > 0)	// D > p->data
			if (p->right != NULL)
				p = p->right;
			else
				break;
		else
			if (p->left != NULL)
				p = p->left;
			else
				break;
	}
	q = new treenode;
	q->data = D;
	q->left = q->right = NULL;
	if (p == NULL)	// T is NULL
		return q;
	if (crt > 0)
		p->right = q;
	else
		p->left = q;
	return T;
}

int main()
{
	treenode* t = NULL;
	data_t dt, min;
	char c;

	do {
		cin >> dt;
		cin.get(c);
		t = BST_add_node(t, dt);
	} while (c == ' ');
	cin >> min;
	BST_print_ge(t, min);
	return 0;
}

// print nodes greater or equal to M
void BST_print_ge(treenode* const T, const data_t M)
{
	int crt;

	if (T == NULL)
		return;
	BST_print_ge(T->right, M);

	crt = BST_cmp(M, T->data);
	if (crt <= 0)
		cout << T->data << ' ';
	if (crt < 0)
		BST_print_ge(T->left, M);
}