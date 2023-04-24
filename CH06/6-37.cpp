#include <vector>
#include <iostream>

using namespace std;

struct tree_node {
	char data;
	tree_node* left, * right;
};

struct input_info {
	char c;
	int l, r;
};

typedef tree_node* tree_stack_t;

class tree_stack {
private:
	int pt;
	tree_stack_t* stack;
	int size;
public:
	tree_stack(const int Size);
	int push(const tree_stack_t& T);
	tree_stack_t pop(void);
	~tree_stack(void);
};

tree_stack::tree_stack(const int Size)
{
	pt = 0;
	stack = new tree_stack_t[Size];
	size = Size;
}

int tree_stack::push(const tree_stack_t& T)
{
	if (pt < size)
	{
		stack[pt++] = T;
		return 0;
	}
	else
		return 1;	//stack overflow
}

tree_stack_t tree_stack::pop()
{
	if (pt > 0)
		return stack[--pt];
	else
		return NULL;//stack empty
}

tree_stack::~tree_stack()
{
	delete[] stack;
}

tree_node** list_of_nodes;

void tree_print_preorder(tree_node* const T);

int main()
{
	vector<input_info> input;
	input_info temp = { '\0', 0, 0 };
	int n;
	int i;

	input.push_back(temp);
	while (cin >> temp.c)
	{
		cin >> temp.l >> temp.r;
		if (temp.l < 0)
			temp.l = 0;
		if (temp.r < 0)
			temp.r = 0;
		input.push_back(temp);
	}
	n = input.size() - 1;
	list_of_nodes = new tree_node * [n + 1];
	list_of_nodes[0] = NULL;
	for (i = 1; i <= n; ++i)
	{
		list_of_nodes[i] = new tree_node;
		list_of_nodes[i]->data = input.at(i).c;
	}
	for (i = 1; i <= n; ++i)
	{
		list_of_nodes[i]->left = list_of_nodes[input.at(i).l];
		list_of_nodes[i]->right = list_of_nodes[input.at(i).r];
	}

	tree_print_preorder(list_of_nodes[1]);
	return 0;
}

void tree_print_preorder(tree_node* const T)
{
	static const int Stack_size = 50;
	tree_node* p;
	tree_stack stack(Stack_size);

	p = T;
	while (1)
	{
		if (p != NULL)
		{
			cout << p->data << ' ';
			stack.push(p);
			p = p->left;
		}
		else
		{
			if ((p = stack.pop()) == NULL)
				return;
			else
				p = p->right;
		}
	}
}