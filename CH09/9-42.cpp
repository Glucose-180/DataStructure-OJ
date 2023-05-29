#include <iostream>
#include <string>

using namespace std;

typedef int data_t;

// number of branches
const unsigned int B = 26U;

struct trie_node {
	bool is_data;	// whether terminal node or not
	union {
		data_t data;	// use 0 to represent existence
		trie_node* next[B + 1];
		// next[B] points to terminal
	};
};

trie_node* trie_new_node(void);
trie_node* trie_add_data(trie_node* root, const char* Key);
bool trie_del_data(trie_node* const T, const char* Key);
bool trie_search_data(trie_node* const T, const char* Key);


int main()
{
	trie_node* t = NULL;
	int cmd;
	string key;

	while (cin >> cmd >> key)
	{
		switch (cmd)
		{
		case 1:	// add
			t = trie_add_data(t, key.c_str());
			break;
		case 2:	// del
			trie_del_data(t, key.c_str());
			break;
		case 3:	// search
			if (trie_search_data(t, key.c_str()))
				cout << "True" << endl;
			else
				cout << "False" << endl;
			break;
		}
	}
}

trie_node* trie_new_node()
{
	unsigned int i;

	trie_node* p;
	p = new trie_node;
	p->is_data = false;
	for (i = 0U; i <= B; ++i)
		p->next[i] = NULL;
	return p;
}

trie_node* trie_add_data(trie_node* root, const char* Key)
{
	trie_node* p;
	unsigned int i;

	if (root == NULL)
	{
		root = trie_new_node();
	}
	for (p = root, i = 0U; Key[i] != '\0'; ++i)
	{
		if (p->next[Key[i] - 'a'] == NULL)
			p->next[Key[i] - 'a'] = trie_new_node();
		p = p->next[Key[i] - 'a'];
	}
	p = p->next[B] = trie_new_node();
	p->is_data = true;
	p->data = 0;	// existence
	return root;
}

bool trie_del_data(trie_node* const T, const char* Key)
{
	trie_node* p;
	unsigned int i;

	for (p = T, i = 0U; Key[i] != '\0'; ++i)
	{
		if (p->next[Key[i] - 'a'] == NULL)
			return false;	// not found
		p = p->next[Key[i] - 'a'];
	}
	if (p->next[B] != NULL && p->next[B]->is_data == true)
	{
		delete p->next[B];
		p->next[B] = NULL;
		return true;
	}
	else
		return false;
}

bool trie_search_data(trie_node* const T, const char* Key)
{
	trie_node* p;
	unsigned int i;

	for (p = T, i = 0U; Key[i] != '\0'; ++i)
	{
		if (p->next[Key[i] - 'a'] == NULL)
			return false;	// not found
		p = p->next[Key[i] - 'a'];
	}
	if (p->next[B] != NULL && p->next[B]->is_data == true)
		return true;
	else
		return false;
}