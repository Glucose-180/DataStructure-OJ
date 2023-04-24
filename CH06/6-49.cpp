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

typedef tree_node* tree_queue_t;

class tree_queue {
private:
	int size;
	tree_queue_t* queue;
	int head, tail;
public:
	tree_queue(const int Size);
	int enter(const tree_queue_t& Q);
	tree_queue_t depart(void);
	~tree_queue(void);
};

tree_queue::tree_queue(const int Size)
{
	queue = new tree_queue_t[Size];
	size = Size;
	head = tail = 0;
}

int tree_queue::enter(const tree_queue_t& Q)
{
	if ((head - tail + size) % size >= size - 1)
		return 1;	// overflow
	queue[tail++] = Q;
	tail %= size;
	return 0;
}

tree_queue_t tree_queue::depart()
{
	int temp;

	if (head == tail)
		return NULL;	// empty
	temp = head++;
	head %= size;
	return queue[temp];
}

tree_queue::~tree_queue()
{
	delete[] queue;
}

tree_node** list_of_nodes;

bool is_complete(tree_node* const T);

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
	if (is_complete(list_of_nodes[1]) == true)
		cout << "Yes";
	else
		cout << "No";
	return 0;
}

bool is_complete(tree_node* const T)
{
	tree_queue queue(30);
	tree_node* p;

	if (T == NULL)
		return true;
	queue.enter(T);
	while (1)
	{
		p = queue.depart();
		if (p->left != NULL)
		{
			queue.enter(p->left);
			if (p->right != NULL)
				queue.enter(p->right);
			else
				break;
		}
		else
		{
			if (p->right != NULL)
				return false;
			else
				break;
		}
	}
	// Once the first Unsaturated node is found,
	// all nodes behind it (in order of level) should not have children
	while ((p = queue.depart()) != NULL)
	{
		if (p->left != NULL || p->right != NULL)
			return false;
	}
	return true;
}