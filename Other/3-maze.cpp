#include <vector>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

struct gal_node {
	size_t tv_index;	// index of terminal vertex
	gal_node* next;
};

struct graph_ud {	// undirected
	size_t n;		// number of vertices
	gal_node** v;
};

struct step_t {		// step in queue
	size_t cur;
	size_t last;
};

// path from Entry to Terminal through Key REVERSELY
vector<size_t> path;

graph_ud g;
vector<string> maze;

gal_node* gal_insert(gal_node* const F, const size_t N);
bool graph_findpath_BFS(const graph_ud G, const size_t S, const size_t T);

int main()
{
	size_t m, n;	// size of maze
	size_t i, j;
	size_t entry = 0, key = 0, terminal = 0;// R, Y, C
	string row;

	// read input
	cin >> m >> n;
	cin.get();
	while (getline(cin, row))
		maze.push_back(row);

	// construct graph
	g.n = m * n;
	g.v = new gal_node * [m * n];
	memset(g.v, 0, g.n * sizeof(gal_node*));
	for (i = 0U; i < m; ++i)
	{
		string temp = maze.at(i);
		for (j = 0U; j < n; ++j)
		{
			size_t loc = i * n + j;
			switch (temp.at(j))
			{
			case '1':	// wall
				continue;
				break;
			case 'R':
				entry = loc;
				break;
			case 'Y':
				key = loc;
				break;
			case 'C':
				terminal = loc;
				break;
			}

			// scan 4 directions
			if (j > 0U && temp.at(j - 1) != '1')
				// left
				g.v[loc] = gal_insert(g.v[loc], loc - 1);
			if (i > 0U && maze.at(i - 1).at(j) != '1')
				// up
				g.v[loc] = gal_insert(g.v[loc], loc - n);
			if (j < n - 1 && temp.at(j + 1) != '1')
				// right
				g.v[loc] = gal_insert(g.v[loc], loc + 1);
			if (i < m - 1 && maze.at(i + 1).at(j) != '1')
				// down
				g.v[loc] = gal_insert(g.v[loc], loc + n);
		}
	}

	// find path
	graph_findpath_BFS(g, key, terminal);
	path.pop_back();	// key
	graph_findpath_BFS(g, entry, key);

	// print path
	i = path.size() - 1;
	do {
		size_t temp = path.at(i);
		cout << temp / n + 1;
		cout << ' ';
		cout << temp % n + 1;
		cout << endl;
	} while (i--);
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

bool graph_findpath_BFS(const graph_ud G, const size_t S, const size_t T)
{
	step_t* queue_BFS = new step_t[G.n];
	step_t qtemp;
	size_t head = 0, tail = 0;
	size_t i;
	gal_node* p;

	queue_BFS[tail].cur = S;
	queue_BFS[tail].last = 0;
	++tail;		// enter

	while (head < tail)
	{
		qtemp = queue_BFS[head++];
		if (T == qtemp.cur)
		{		// found
			i = head - 1;
			do {
				//cout << queue_BFS[i].cur << ',';
				path.push_back(queue_BFS[i].cur);
			} while (i > 0 && ((i = queue_BFS[i].last) || true));
			delete[] queue_BFS;
			return true;
		}
		for (p = G.v[qtemp.cur]; p != NULL; p = p->next)
		{
			for (i = 0; i < tail; ++i)
				if (queue_BFS[i].cur == p->tv_index)
					break;
			if (i >= tail)
			{
				queue_BFS[tail].cur = p->tv_index;
				queue_BFS[tail].last = head - 1;
				++tail;
			}
		}
	}
	delete[] queue_BFS;
	return false;
}