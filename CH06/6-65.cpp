#include <string>
#include <iostream>
#include <cstddef>

using namespace std;

struct tnode {
	char data;
	tnode* left, * right;
};


tnode* create_from_preandin(const string& Preorder, const string& Inorder);
void treeprint_postorder(const tnode* const T);

int main()
{
	string preorder, inorder;
	tnode* t;

	cin >> preorder >> inorder;
	t = create_from_preandin(preorder, inorder);
	treeprint_postorder(t);
	return 0;
}

tnode* create_from_preandin(const string& Preorder, const string& Inorder)
{
	tnode* root;
	size_t loc;
	string sub_pre, sub_in;

	if (Preorder.size() == 0)
		return NULL;
	root = new tnode;
	root->data = Preorder.at(0);
	loc = Inorder.find(root->data);
	sub_in = Inorder.substr(0, loc);
	sub_pre = Preorder.substr(1, loc);
	root->left = create_from_preandin(sub_pre, sub_in);
	sub_in = Inorder.substr(loc + 1);
	sub_pre = Preorder.substr(loc + 1);
	root->right = create_from_preandin(sub_pre, sub_in);
	return root;
}

void treeprint_postorder(const tnode* const T)
{
	if (T != NULL)
	{
		treeprint_postorder(T->left);
		treeprint_postorder(T->right);
		cout << T->data;
	}
}