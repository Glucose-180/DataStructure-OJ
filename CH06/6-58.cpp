#include <iostream>
#include <vector>
#include <cstddef>

using namespace std;

vector<int> L, R;
struct tree_node {
	int data;
	bool l_isthread, r_isthread;
	tree_node* left, * right;
};

tree_node* inorder_threading(tree_node* const T);
tree_node* inorder_traverse(const tree_node* const Head, const int Target);


int main()
{
	int t;
	char c;
	int target;
	int diff;
	size_t n0, n, i;	// the number of nodes
	tree_node** list_of_nodes;
	tree_node* head, * root, *ptarget, *hti, *rti;// Head/Root of the tree To be Inserted

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
		list_of_nodes[i]->l_isthread = list_of_nodes[i]->r_isthread = false;
	}
	head = inorder_threading(root = list_of_nodes[1]);	// root
	n0 = n;
	L.clear();
	R.clear();
	delete[] list_of_nodes;

	cin >> target;
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
	diff = L.at(0) - 1;
	list_of_nodes = new tree_node * [n + 1];
	list_of_nodes[0] = NULL;
	for (i = 1; i <= n; ++i)
	{
		list_of_nodes[i] = new tree_node;
		list_of_nodes[i]->data = i + diff;
	}
	for (i = 1; i <= n; ++i)
	{
		list_of_nodes[i]->left = list_of_nodes[L.at(i) - diff < 0 ? 0 : L.at(i) - diff];
		list_of_nodes[i]->right = list_of_nodes[R.at(i) - diff < 0 ? 0 : R.at(i) - diff];
		list_of_nodes[i]->l_isthread = list_of_nodes[i]->r_isthread = false;
	}
	hti = inorder_threading(rti = list_of_nodes[1]);

	ptarget = inorder_traverse(head, target);
	{	// Insert
		tree_node* p, *q;

		if (ptarget->l_isthread == true)	// no left child
		{
			q = ptarget->left;
			ptarget->left = rti;
			ptarget->l_isthread = false;
			hti->right->right = ptarget;
			hti->right->r_isthread = true;
			for (p = rti; p->l_isthread == false; p = p->left)
				;
			p->left = q;
			p->l_isthread = true;
		}
		else
		{
			q = ptarget->left;
			ptarget->left = rti;
			ptarget->l_isthread = false;
			hti->right->right = q;
			hti->right->r_isthread = false;
			for (p = rti; p->l_isthread == false; p = p->left)
				;
			for (; q->l_isthread == false; q = q->left)
				;
			p->left = q->left;
			p->l_isthread = true;
			q->left = hti->right;
			q->l_isthread = true;
		}
	}
	inorder_traverse(head, -1);
	return 0;
}

tree_node* inorder_threading(tree_node* const T)
{
	tree_node* head = new tree_node;
	extern tree_node* _plast;
	extern void _inorder_threading(tree_node* const T);

	head->l_isthread = false;
	head->r_isthread = true;
	head->right = head;
	if (T == NULL)
		head->left = head;
	else
	{
		head->left = T;
		_plast = head;
		_inorder_threading(T);
		_plast->right = head;
		_plast->r_isthread = true;
		head->right = _plast;
	}
	return head;
}

void _inorder_threading(tree_node* const T)
{
	extern tree_node* _plast;

	if (T != NULL)
	{
		_inorder_threading(T->left);

		if (T->left == NULL)
		{
			T->left = _plast;
			T->l_isthread = true;
		}
		if (_plast->right == NULL)
		{
			_plast->right = T;
			_plast->r_isthread = true;
		}
		_plast = T;

		_inorder_threading(T->right);
	}
}

tree_node* _plast;	// used for threading

// if Target <= 0, then print; else, search Target
tree_node* inorder_traverse(const tree_node* const Head, const int Target)
{
	tree_node* p;

	for (p = Head->left; p != Head; p = p->right)
	{
		while (p->l_isthread == false)
			p = p->left;
		{	// Visit
			if (Target > 0 && p->data == Target)
				return p;
			else if (Target <= 0)
				cout << p->data << ' ';
		}
		while (p->r_isthread == true && p->right != Head)
		{
			p = p->right;
			{	// Visit
				if (Target > 0 && p->data == Target)
					return p;
				else if (Target <= 0)
					cout << p->data << ' ';
			}
		}
	}
	return NULL;
}
