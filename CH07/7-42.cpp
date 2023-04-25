// graph_d.h
#ifndef __GRAPH_D_H__
#define __GRAPH_D_H__

#include <iostream>
#include <string>
#include <cmath>

#define WINF INFINITY

typedef char gnode_t;
typedef float len_t;

struct gal_node {
	size_t tv_index;	// index of terminal vertex
	gal_node* next;
	len_t weight;
};

struct graph_node {
	gnode_t data;
	gal_node* adjlist;
};

struct graph_d {	// directed
	size_t n;		// number of vertices
	graph_node* v;
};


extern std::string* path;
extern len_t* len;

graph_d graph_create(const size_t N);
gal_node* gal_insert(gal_node* const F, const size_t N, const len_t Weight);

void shortestpath_dijkstra(const graph_d& G, const size_t S);

#endif

// Dijkstra-Shortestpath.cpp
using std::string;

string* path;
len_t* len;

void shortestpath_dijkstra(const graph_d& G, const size_t S)
{
	bool* flag_done = new bool[G.n];
	size_t* last_renewer = new size_t[G.n];
	size_t i, u, v;
	gal_node* p;

	path = new string[G.n];
	len = new len_t[G.n];
	for (i = 0; i < G.n; ++i)
	{
		len[i] = WINF;
		flag_done[i] = false;
		path[i] = "";
	}
	len[S] = 0;
	path[S] += G.v[S].data;
	while (true)
	{
		for (i = 0; i < G.n; ++i)
			if (flag_done[i] == false)
				break;
		if (i == G.n)
			break;		// done
		{	// find minimum length
			len_t min;
			u = i, min = len[i];
			for (; i < G.n; ++i)
				if (flag_done[i] == false && len[i] < min)
					u = i, min = len[i];
		}
		if (u != S && len[u] < WINF)
			path[u] = path[last_renewer[u]] + G.v[u].data;	// renew path
		flag_done[u] = true;
		for (p = G.v[u].adjlist; p != NULL; p = p->next)
		{
			if (flag_done[v = p->tv_index] == true)
				continue;
			if (len[u] + p->weight < len[v])
			{
				len[v] = len[u] + p->weight;
				last_renewer[v] = u;
			}
		}
	}
	delete[] last_renewer;
	delete[] flag_done;
}

// C2H6.cpp
using namespace std;

int main()
{
	graph_d g;
	size_t nv, s;
	size_t vt, vh;	// tail and head
	char c;
	len_t w;
	size_t i;

	cin >> nv >> s;		// number of vertices and starting
	g = graph_create(nv);
	while (cin >> vt)
	{
		cin >> c >> vh >> w;
		--vt;
		--vh;
		g.v[vt].adjlist = gal_insert(g.v[vt].adjlist, vh, w);
	}
	shortestpath_dijkstra(g, --s);
	for (i = 0; i < g.n; ++i)
	{
		if (i == s)
			continue;
		if (len[i] < WINF)
			cout << len[i];
		if (i < g.n - 1)
			cout << ',';
	}
	return 0;
}
// create an undirected graph with N nodes and 0 edge
graph_d graph_create(const size_t N)
{
	graph_d g;
	size_t i;

	g.n = N;
	g.v = new graph_node[N];
	for (i = 0; i < N; ++i)
	{
		g.v[i].data = 'A' + i;
		g.v[i].adjlist = NULL;
	}
	return g;
}

// insert a node in the adjacency list, whose head has SMALLEST tv_index
gal_node* gal_insert(gal_node* const F, const size_t N, const len_t Weight)
{
	gal_node* p, * q;

	p = new gal_node;
	p->tv_index = N;
	p->weight = Weight;
	if (F == NULL || N <= F->tv_index)
	{
		p->next = F;
		return p;
	}
	for (q = F; q->next != NULL && q->next->tv_index < N; q = q->next)
		;
	p->next = q->next;
	q->next = p;
	return F;
}
