#include <iostream>
#include <cstddef>
#include <cstring>

using namespace std;

struct gal_node {
	int tv_index;	// index of terminal vertex
	gal_node* next;
};

struct graph_d {
	size_t n;		// number of vertices
	gal_node** v;
};

graph_d g;

gal_node* gal_insert(gal_node* const F, const size_t N);

int main()
{
	size_t v, e, i;
	char c;
	bool zero = false;
	size_t vt, vh;	// tail and head
	gal_node* p;

	cin >> v >> c >> e;
	g.n = v + 1;
	g.v = new gal_node * [v + 1];
	memset(g.v, 0, (v + 1) * sizeof(gal_node*));

	do {
		cin >> vt;
		cin >> c;
		cin >> vh;
		if (vt == 0 || vh == 0)
			zero = true;
		g.v[vt] = gal_insert(g.v[vt], vh);
		cin >> c;
	} while (cin);

	for (i = (zero ? 0 : 1); i < (zero ? v : v + 1); ++i)
	{
		cout << i;
		if ((p = g.v[i]) != NULL)
			cout << ' ';
		for (; p != NULL; p = p->next)
		{
			cout << p->tv_index;
			if (p->next != NULL)
				cout << ',';
		}
		cout << endl;
	}
	return 0;
}

gal_node* gal_insert(gal_node* const F, const size_t N)
{
	gal_node* p, * q;

	p = new gal_node;
	p->tv_index = N;
	if (F == NULL || N >= F->tv_index)
	{
		p->next = F;
		return p;
	}
	for (q = F; q->next != NULL && q->next->tv_index > N; q = q->next)
		;
	p->next = q->next;
	q->next = p;
	return F;
}