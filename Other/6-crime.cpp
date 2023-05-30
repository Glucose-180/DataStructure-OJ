#include <vector>
#include <iostream>
#include <cstring>

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

graph_ud g;
bool* flag_visited;

unsigned int len;

const char* Uncertain = "不确定",
	* Same = "是同一个团伙所为",
	* Dif = "不是同一个团伙所为";

gal_node* gal_insert(gal_node* const F, const size_t N);
bool graph_findpath_DFS(const graph_ud G, const size_t S, const size_t T);

int main()
{
	unsigned int t, m, n;
	char c;
	unsigned int u, v;

	cin >> t;
	while (t--)
	{
		cin >> n >> m;
		// n: number of cases
		// m: number of commands
		g.n = n;
		g.v = new gal_node * [n];
		flag_visited = new bool[n];

		memset(g.v, 0, (n) * sizeof(gal_node*));

		while (m--)
		{
			cin >> c >> u >> v;
			u--;
			v--;
			if (c == 'D')
			{	// made by different gangs
				g.v[u] = gal_insert(g.v[u], v);
				g.v[v] = gal_insert(g.v[v], u);
			}
			else if (c == 'A')
			{
				len = 0U;
				memset(flag_visited, 0, (n) * sizeof(bool));
				if (graph_findpath_DFS(g, u, v) == false)
					cout << Uncertain << endl;
				else
				{
					if (len % 2U == 0)
						cout << Dif << endl;
					else
						cout << Same << endl;
				}
			}
		}

		delete g.v;
		delete flag_visited;
		// may cause memory leak
	}
	return 0;
}

bool graph_findpath_DFS(const graph_ud G, const size_t S, const size_t T)
{
	gal_node* p;

	flag_visited[S] = true;
	if (S == T)
	{
		//cout << S << ',';
		++len;
		return true;
	}
	for (p = G.v[S]; p != NULL; p = p->next)
		if (flag_visited[p->tv_index] == false && graph_findpath_DFS(G, p->tv_index, T) == true)
		{
			//cout << S << ',';
			++len;
			return true;
		}
	return false;
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