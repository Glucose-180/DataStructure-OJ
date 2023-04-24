#include <iostream>
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
bool* flag_visited;

gal_node* gal_insert(gal_node* const F, const size_t N);
bool graph_DFS(const size_t I, const size_t J);

int main()
{
	size_t v, i, j;
	char c;
	bool zero = false;
	size_t vt, vh;	// tail and head

	cin >> v;
	g.n = v + 1;
	g.v = new gal_node * [v + 1];
	flag_visited = new bool[v + 1];

	memset(g.v, 0, (v + 1) * sizeof(gal_node*));
	for (i = 0; i <= v; ++i)
		flag_visited[i] = false;

	do {
		cin >> vt;
		cin >> c;
		cin >> vh;
		g.v[vt] = gal_insert(g.v[vt], vh);
		cin.get(c);
	} while (c == ',');

	cin >> i >> c >> j;
	if (graph_DFS(i, j) == true)
		cout << "yes";
	else
		cout << "no";
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

bool graph_DFS(const size_t I, const size_t J)
{
	gal_node* p;

	flag_visited[I] = true;
	if (I == J)
		return true;
	for (p = g.v[I]; p != NULL; p = p->next)
	{
		if (flag_visited[p->tv_index])
			continue;
		if (graph_DFS(p->tv_index, J) == true)
			return true;
	}
	return false;
}
