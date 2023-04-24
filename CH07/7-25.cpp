#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

struct gal_node {		// adjacency list
	size_t tv_index;	// the index of the terminal vertex
	gal_node* next;
};

struct graph_d {		// directed graph
	size_t n;			// number of vertices
	gal_node** v;		// vertices
};

vector<size_t> s, fst, lst;
graph_d g;
bool* flag_visited, * flag_visited_sametime;

graph_d create_from_ar(const size_t N, const vector<size_t>S, const vector<size_t>Fst, const vector<size_t> Lst);
gal_node* gal_insert(gal_node* const F, const size_t D);
bool is_DAG(const graph_d& G);
bool circuit_exists(const graph_d& G, const size_t Start);

int main()
{
	size_t n;
	size_t temp;
	char c;

	cin >> n;
	do {
		cin >> temp;
		s.push_back(temp);
		cin.get(c);
	} while (c == ' ');

	do {
		cin >> temp;
		fst.push_back(temp);
		cin.get(c);
	} while (c == ' ');

	do {
		cin >> temp;
		lst.push_back(temp);
		cin.get(c);
	} while (c == ' ');

	g = create_from_ar(n, s, fst, lst);
	flag_visited = new bool[n + 1];
	flag_visited_sametime = new bool[n + 1];
	if (is_DAG(g))
		cout << "no";
	else
		cout << "yes";
	return 0;
}

graph_d create_from_ar(const size_t N, const vector<size_t>S, const vector<size_t>Fst, const vector<size_t> Lst)
{
	graph_d g;
	size_t i, j;

	g.n = N;
	g.v = new gal_node * [N + 1];
	g.v[0] = NULL;
	for (i = 1; i <= N; ++i)
	{
		g.v[i] = NULL;
		for (j = Fst.at(i); j < Lst.at(i); ++j)
		{
			g.v[i] = gal_insert(g.v[i], S.at(j));
		}
	}
	return g;
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

bool is_DAG(const graph_d& G)
{
	size_t i;

	memset(flag_visited, false, (G.n + 1) * sizeof(bool));
	for (i = 1; i <= G.n; ++i)
	{
		if (flag_visited[i] == true)
			continue;
		memset(flag_visited_sametime, false, (G.n + 1) * sizeof(bool));
		if (circuit_exists(G, i) == true)
			return false;
	}
	return true;
}

// detect whether any circuit exists from vertex Start using DFS
bool circuit_exists(const graph_d& G, const size_t Start)
{
	gal_node* p;

	flag_visited_sametime[Start] = true;
	flag_visited[Start] = true;
	for (p = G.v[Start]; p != NULL; p = p->next)
	{
		if (flag_visited_sametime[p->tv_index] == true)
			return true;
		if (flag_visited[p->tv_index] == true)
			continue;
		if (circuit_exists(G, p->tv_index) == true)
			return true;
	}
	return false;
}