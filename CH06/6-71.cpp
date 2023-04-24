#include <vector>
#include <iostream>

using namespace std;

struct tree_node {
	char data;
	tree_node* firstchild, * nextsibling;
};

struct input {
	char data;
	int firstchild, nextsibling;
};

vector<input> input_buf;

void tree_print(tree_node* const T, const int Level);

int main()
{
	input temp;
	int i, n;
	tree_node** list_of_nodes;

	while (cin >> temp.data)
	{
		cin >> temp.firstchild >> temp.nextsibling;
		if (temp.firstchild < 0)
			temp.firstchild = 0;
		if (temp.nextsibling < 0)
			temp.nextsibling = 0;
		input_buf.push_back(temp);
	}
	n = input_buf.size();
	list_of_nodes = new tree_node * [n + 1];
	list_of_nodes[0] = NULL;
	for (i = 1; i <= n; ++i)
	{
		list_of_nodes[i] = new tree_node;
		list_of_nodes[i]->data = input_buf.at(i - 1).data;
	}
	for (i = 1; i <= n; ++i)
	{
		list_of_nodes[i]->firstchild = list_of_nodes[input_buf.at(i - 1).firstchild];
		list_of_nodes[i]->nextsibling = list_of_nodes[input_buf.at(i - 1).nextsibling];
	}
	tree_print(list_of_nodes[1], 0);
	return 0;
}

void tree_print(tree_node* const T, const int Level)
{
	tree_node* p;
	int i;

	for (p = T; p != NULL; p = p->nextsibling)
	{
		for (i = 0; i < Level; ++i)
			putchar('-');
		putchar(p->data);
		putchar('\n');
		if (p->firstchild != NULL)
			tree_print(p->firstchild, Level + 1);
	}
}