#include <iostream>
#include <vector>
#include <cstddef>

using namespace std;

vector<int> L, R;
struct tree_node {
	int data;
	tree_node* left, * right;
};

bool is_descendant_of(tree_node* u, tree_node* v);

int main()
{
	int t;
	char c;
	size_t n, i;	// the number of nodes
	tree_node** list_of_nodes;
	int u, v;

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
	cin >> u >> v;
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
	if (is_descendant_of(list_of_nodes[u], list_of_nodes[v]) == true)
		cout << '1';
	else
		cout << '0';
	cout << endl;
	return 0;
}

/* judge whether u is descendant of v or not */
bool is_descendant_of(tree_node* u, tree_node* v)
{
	if (v == NULL)
		return false;
	//if (u->left == NULL && u->right == NULL)
	//	return false;
	if (v->left == u || v->right == u)
		return true;
	return (is_descendant_of(u, v->left) || is_descendant_of(u, v->right));
}