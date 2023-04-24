#include <vector>
#include <iostream>

using namespace std;

struct tree_node {
	int data;
	bool l_isthread, r_isthread;
	tree_node* left, * right;
};

struct input {
	int data;
	int firstchild, nextsibling;
};

vector<input> input_buf;

tree_node* forest2bintree(tree_node** list_of_nodes, const int N);
void thread_clear(tree_node* const T);
void thread_inorder(tree_node* const T);
void thread_preorder(tree_node* const T);
void thread_postorder(tree_node* const T);
void tree_thread_print(tree_node** list_of_nodes, const int N);

int main()
{
	input temp;
	int i, n;
	tree_node** list_of_nodes;
	tree_node* root;

	cin >> n;
	while (cin >> temp.data)
	{
		cin >> temp.firstchild >> temp.nextsibling;
		if (temp.firstchild < 0)
			temp.firstchild = 0;
		if (temp.nextsibling < 0)
			temp.nextsibling = 0;
		input_buf.push_back(temp);
	}
	if (n != input_buf.size())
		return 1;
	list_of_nodes = new tree_node * [n + 1];
	list_of_nodes[0] = NULL;
	for (i = 1; i <= n; ++i)
	{
		list_of_nodes[i] = new tree_node;
		list_of_nodes[i]->data = input_buf.at(i - 1).data;
		list_of_nodes[i]->l_isthread = list_of_nodes[i]->r_isthread = false;
	}
	for (i = 1; i <= n; ++i)
	{
		list_of_nodes[i]->left = list_of_nodes[input_buf.at(i - 1).firstchild];
		list_of_nodes[i]->right = list_of_nodes[input_buf.at(i - 1).nextsibling];
	}

	if ((root = forest2bintree(list_of_nodes, n)) == NULL)
		return 2;
	thread_preorder(root);
	tree_thread_print(list_of_nodes, n);
	thread_clear(root);
	thread_inorder(root);
	tree_thread_print(list_of_nodes, n);
	thread_clear(root);
	thread_postorder(root);
	tree_thread_print(list_of_nodes, n);
	thread_clear(root);
	return 0;
}

tree_node* forest2bintree(tree_node** list_of_nodes, const int N)
{
	tree_node* root = NULL, * pre = NULL;
	int i;
	bool is_root(const int Data);

	for (i = 1; i <= N; ++i)	// find first root
		if (is_root(list_of_nodes[i]->data))
		{
			root = pre = list_of_nodes[i];
			break;
		}
	if (pre == NULL)
		return NULL;	// no root found
	while (++i <= N)
		if (is_root(list_of_nodes[i]->data))
		{
			pre = pre->right = list_of_nodes[i];
		}
	else
		pre->right = NULL;
	return root;
}

bool is_root(const int Data)
{
	int i;

	for (i = 0; i < input_buf.size(); ++i)
		if (input_buf.at(i).firstchild == Data || input_buf.at(i).nextsibling == Data)
			return false;
	return true;
}

void thread_clear(tree_node* const T)
{
	if (T != NULL)
	{
		if (T->l_isthread)
		{
			T->l_isthread = false;
			T->left = NULL;
		}
		if (T->r_isthread)
		{
			T->r_isthread = false;
			T->right = NULL;
		}
		thread_clear(T->left);
		thread_clear(T->right);
	}
}

void thread_inorder(tree_node* const T)
{
	static tree_node* pre = NULL;

	if (T != NULL)
	{
		thread_inorder(T->left);
		if (T->left == NULL)
		{
			T->l_isthread = true;
			T->left = pre;
		}
		if (pre != NULL && pre->right == NULL)
		{
			pre->r_isthread = true;
			pre->right = T;
		}
		pre = T;
		thread_inorder(T->right);
	}
}

void thread_preorder(tree_node* const T)
{
	static tree_node* pre = NULL;

	if (T != NULL)
	{
		if (T->left == NULL)
		{
			T->l_isthread = true;
			T->left = pre;
		}
		pre = T;
		if (T->l_isthread == false)
			thread_preorder(T->left);
		thread_preorder(T->right);
	}
}

void thread_postorder(tree_node* const T)
{
	static tree_node* pre = NULL;

	if (T != NULL)
	{
		thread_postorder(T->left);
		thread_postorder(T->right);
		if (pre != NULL && pre->right == NULL)
		{
			pre->r_isthread = true;
			pre->right = T;
		}
		pre = T;
	}
}

void tree_thread_print(tree_node** list_of_nodes, const int N)
{
	int i;

	// array L
	cout << list_of_nodes[1]->data;
	for (i = 1; i <= N; ++i)
	{
		if (list_of_nodes[i]->left == NULL)
			cout << ' ' << 0;
		else
			cout << ' ' << list_of_nodes[i]->left->data;
	}
	cout << endl;
	// array R
	cout << list_of_nodes[1]->data;
	for (i = 1; i <= N; ++i)
	{
		if (list_of_nodes[i]->right == NULL)
			cout << ' ' << 0;
		else
			cout << ' ' << list_of_nodes[i]->right->data;
	}
	cout << endl;
}