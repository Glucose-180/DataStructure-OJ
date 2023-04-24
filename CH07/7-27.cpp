#include <iostream>
#include <cstring>

using namespace std;

struct gal_node {
	size_t tv_index;	// index of terminal vertex
	gal_node* next;
};

struct graph_ud {	// undirected graph
	size_t n;		// number of vertices
	gal_node** v;
};

graph_ud g;
bool* flag_visited;

gal_node* gal_insert(gal_node* const F, const size_t N);
bool pathdetect_DFS(const graph_ud& G, const size_t S, const size_t T, const size_t Len);

int main()
{
	size_t v, i;
	char c;
	bool zero = false;
	size_t vt, vh;	// tail and head
	size_t start, terminal, len;

	cin >> v >> c >> len;
	cin >> start >> c >> terminal;
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
		g.v[vh] = gal_insert(g.v[vh], vt);	// undirected graph!
		cin.get(c);
	} while (c == ',');

	if (pathdetect_DFS(g, start, terminal, len) == true)
		cout << "yes";
	else
		cout << "no";
	return 0;
}

gal_node* gal_insert(gal_node* const F, const size_t D)
{
	gal_node* p, * q;

	p = new gal_node;
	p->tv_index = D;
	if (F == NULL || D >= F->tv_index)
	{
		p->next = F;
		return p;
	}
	for (q = F; q->next != NULL && q->next->tv_index > D; q = q->next)
		;
	p->next = q->next;
	q->next = p;
	return F;
}

// detect whether simple path of lenth Len exists from S to T
bool pathdetect_DFS(const graph_ud& G, const size_t S, const size_t T, const size_t Len)
{
	gal_node* p;

	if (Len == 0)
	{
		if (S == T)
			return true;
		else
			return false;
	}
	flag_visited[S] = true;
	for (p = G.v[S]; p != NULL; p = p->next)
	{
		if (flag_visited[p->tv_index] == true)
			continue;
		if (pathdetect_DFS(G, p->tv_index, T, Len - 1) == true)
			return true;
	}
	flag_visited[S] = false;
	return false;
}
/*	For all positive integer Len, this algorithm can detect whether simple path exits through all valid(flag is false) vertices (the starting vertex doesn't has this limit).
*	BASIS: when Len = 0, the conclusion is evident.
*	INDUCTION: suppose that for Len = n (positive integer), the conclusion is right, then we can prove that for Len = n + 1 is also right.
*/