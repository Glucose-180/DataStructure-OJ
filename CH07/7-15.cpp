#include <string>
#include <cstddef>
#include <vector>
#include <iostream>

using namespace std;

vector<string> graph_matrix;

int main()
{
	string row, ins;
	char temp;
	char c;
	size_t n, i, j;	//number of vertices

	cin >> n;
	for (i = 0; i < n; ++i)
	{
		row.clear();
		do {
			cin >> temp;
			cin.get(c);
			row += temp;
		} while (c == ' ');
		graph_matrix.push_back(row);
	}

	while (cin >> ins)
	{
		if (ins == "DA")
		{
			cin >> i >> j;
			graph_matrix.at(i).at(j) = '0';
			graph_matrix.at(j).at(i) = '0';
		}
		else if (ins == "DV")
		{
			cin >> i;
			graph_matrix.erase(graph_matrix.begin() + i);
			--n;
			for (j = 0; j < n; ++j)
			{
				graph_matrix.at(j).erase(i, 1);
			}
		}
		else if (ins == "IA")
		{
			cin >> i >> j;
			graph_matrix.at(i).at(j) = '1';
			graph_matrix.at(j).at(i) = '1';
		}
		else if (ins == "IV")
		{
			cin >> i;
			for (j = 0; j < n; ++j)
			{
				graph_matrix.at(j).insert(graph_matrix.at(j).begin() + i, '0');
			}
			++n;
			row.assign(n, '0');
			graph_matrix.insert(graph_matrix.begin() + i, row);
		}
		else
			return 1;
	}

	for (i = 0; i < n; ++i)
		for (j = 0; j < n; )
		{
			cout << graph_matrix.at(i).at(j);
			if (++j < n)
				cout << ' ';
			else
				cout << endl;
		}
	return 0;
}
