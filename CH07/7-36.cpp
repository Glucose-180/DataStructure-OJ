// graph_d.h
#ifndef __GRAPH_D__
#define __GRAPH_D__

#include <iostream>
#include <cstring>

typedef char gnode_t;
typedef unsigned int dur_t;	// duration type

// Orthogonal linked list
struct gol_node {
	size_t tail, head;
	gol_node* tnext, * hnext;
	dur_t duration;
};

struct graph_node {
	gnode_t data;
	gol_node* firstout, * firstin;
};

struct graph_d {	// directed graph
	size_t n;		// number of vertices
	graph_node* v;	// vertices
};

graph_d graph_create(const size_t N);
graph_d& gol_insert(graph_d& g, const size_t Tail, const size_t Head, const dur_t Duration);

bool longest_path(const graph_d& G);
#endif

// CriticalPath.cpp
static size_t* tpl_order;
static dur_t* v_earliest, * v_latest;

static bool tpl_sort(const graph_d& G);
static unsigned int* get_indegree(const graph_d& G);
static inline dur_t umax(const dur_t X, const dur_t Y);
static inline dur_t umin(const dur_t X, const dur_t Y);

bool longest_path(const graph_d& G)
{
	size_t i, j;
	size_t end;
	gol_node* p;

	tpl_order = new size_t[G.n];
	v_earliest = new dur_t[G.n];
	v_latest = new dur_t[G.n];
	if (tpl_sort(G) == false)
	{
		delete[] tpl_order;
		delete[] v_earliest;
		delete[] v_latest;
		return false;		// circuit exists, not DAG!
	}
	end = tpl_order[G.n - 1];
	// initialize v_latest
	for (i = 0; i < G.n; ++i)
		v_latest[i] = v_earliest[end];
	while (i > 0)
	{
		j = tpl_order[--i];
		for (p = G.v[j].firstout; p != NULL; p = p->tnext)
			v_latest[j] = umin(v_latest[j], v_latest[p->head] - p->duration);
	}
	for (i = 0; i < G.n; ++i)
	{
		std::cout << v_latest[end] - v_latest[i];
		if (i < G.n - 1)
			std::cout << ',';
	}
	delete[] tpl_order;
	delete[] v_earliest;
	delete[] v_latest;
	return true;
}

// do Topological Sort and get v_earliest
static bool tpl_sort(const graph_d& G)
{
	unsigned int* indeg;
	size_t* indeg0, sp;		// stack of vertices with 0 in-degree
	size_t ymr;				// count
	size_t i, j;
	gol_node* p;

	indeg = get_indegree(G);
	indeg0 = new size_t[G.n];
	sp = 0;
	// let all 0-indeg vertices enter the stack
	// and initialize v_earliest
	for (i = 0; i < G.n; ++i)
	{
		if (indeg[i] == 0)
			indeg0[sp++] = i;
		v_earliest[i] = 0;
	}

	ymr = 0;
	while (sp > 0)
	{
		i = indeg0[--sp];	// get out of the stack
		tpl_order[ymr++] = i;
		for (p = G.v[i].firstout; p != NULL; p = p->tnext)
		{
			j = p->head;
			if (--indeg[j] == 0)
				indeg0[sp++] = j;	// new 0-indeg vertex
			v_earliest[j] = umax(v_earliest[j], v_earliest[i] + p->duration);
		}
	}
	delete[] indeg;
	delete[] indeg0;
	if (ymr < G.n)
		return false;	// a circuit is detected!
	else
		return true;
}

static unsigned int* get_indegree(const graph_d& G)
{
	unsigned int* indeg, ymr;
	size_t i;
	gol_node* p;

	indeg = new unsigned int[G.n];
	for (i = 0; i < G.n; ++i)
	{
		ymr = 0;
		for (p = G.v[i].firstin; p != NULL; p = p->hnext)
			++ymr;
		indeg[i] = ymr;
	}
	return indeg;
}

static inline dur_t umax(const dur_t X, const dur_t Y)
{
	if (X > Y)
		return X;
	else
		return Y;
}

static inline dur_t umin(const dur_t X, const dur_t Y)
{
	if (X < Y)
		return X;
	else
		return Y;
}

// CH4.cpp

using namespace std;

int main()
{
	graph_d g;
	size_t nv;
	size_t vt, vh;
	char c;

	cin >> nv;	// number of vertices
	g = graph_create(nv);
	do {
		cin >> vt >> c >> vh;
		gol_insert(g, vt - 1, vh - 1, 1);
		cin.get(c);
	} while (c == ',');
	if (longest_path(g) == false)
		cerr << "**Error: not a DAG." << endl;
	return 0;
}

graph_d graph_create(const size_t N)
{
	graph_d g;
	size_t i;

	g.n = N;
	g.v = new graph_node[N];
	for (i = 0; i < N; ++i)
	{
		g.v[i].data = i + 'A';
		g.v[i].firstin = g.v[i].firstout = NULL;
	}
	return g;
}

// insert an edge
graph_d& gol_insert(graph_d& g, const size_t Tail, const size_t Head, const dur_t Duration)
{
	gol_node* p;

	p = new  gol_node;
	p->tail = Tail;
	p->head = Head;
	p->tnext = g.v[Tail].firstout;
	p->hnext = g.v[Head].firstin;
	p->duration = Duration;
	g.v[Tail].firstout = g.v[Head].firstin = p;
	return g;
}
