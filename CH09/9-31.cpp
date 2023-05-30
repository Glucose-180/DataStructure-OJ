#include <vector>
#include <iostream>

using namespace std;

typedef int data_t;

const data_t Max = 2147483647,
	Min = -Max - 1;

struct treenode {
	data_t data;
	int left, right;
};

vector <treenode> tree;

bool is_BST(const int R, const data_t A = Min, const data_t B = Max);

int main()
{
	treenode temp;

	while (cin >> temp.data >> temp.left >> temp.right)
	{
		tree.push_back(temp);
	}
	if (is_BST(0))
		cout << '1';
	else
		cout << '0';

	return 0;
}

// decide whether a tree whose root is R is a BST greater than A and less than B
bool is_BST(const int R, const data_t A, const data_t B)
{
	data_t d;

	if (R < 0)
		return true;
	if ((d = tree.at(R).data) <= A || d >= B)
		return false;
	return is_BST(tree.at(R).left, A, d) &&
		is_BST(tree.at(R).right, d, B);
}
