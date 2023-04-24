#include <iostream>
#include <vector>
#include <cstddef>

using namespace std;

vector<int> L, R;
struct tree_node {
	int data;
	tree_node* left, * right;
};

void swap_children(tree_node* t);

int main()
{
	int t;
	char c;
	size_t n, i;	// the number of nodes
	tree_node** list_of_nodes;

	do {
		cin >> t;
		cin.get(c);
		L.push_back(t);
	} while (c == ' ');
	do {
		cin >> t;
		cin.get(c);
		R.push_back(t);
	} while (c == ' ');
	if ((n = L.size() - 1) != R.size() - 1)
		return 1;
	list_of_nodes = new tree_node * [n + 1];
	list_of_nodes[0] = NULL;
	for (i = 1; i <= n; ++i)
	{
		list_of_nodes[i] = new tree_node;
		list_of_nodes[i]->data = i;
	}
	for (i = 1; i <= n; ++i)
	{
		list_of_nodes[i]->left = list_of_nodes[L.at(i)];
		list_of_nodes[i]->right = list_of_nodes[R.at(i)];
	}
	swap_children(list_of_nodes[1]);
	for (i = 0; i <= n; ++i)
	{
		if (list_of_nodes[i] == NULL)
			cout << '1';
		else
			cout << (list_of_nodes[i]->left == NULL ? '0' : char('0' + list_of_nodes[i]->left->data));
		cout << (i < n ? ' ' : '\n');
	}
	for (i = 0; i <= n; ++i)
	{
		if (list_of_nodes[i] == NULL)
			cout << '1';
		else
			cout << (list_of_nodes[i]->right == NULL ? '0' : char('0' + list_of_nodes[i]->right->data));
		cout << (i < n ? ' ' : '\n');
	}
	return 0;
}

void swap_children(tree_node* t)
{
	tree_node* temp;
	if (t == NULL)
		return;
	temp = t->left;
	t->left = t->right;
	t->right = temp;
	swap_children(t->left);
	swap_children(t->right);
}