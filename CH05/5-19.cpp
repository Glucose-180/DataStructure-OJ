#include <iostream>
#include <climits>

using namespace std;

int main()
{
	int m, n;
	int i, j, k;
	int** mat;
	int min_v;

	cin >> m >> n;
	mat = new int* [m];
	for (i = 0; i < m; ++i)
		mat[i] = new int[n];
	for (i = 0; i < m; ++i)
		for (j = 0; j < n; ++j)
			cin >> mat[i][j];

	for (i = 0; i < m; ++i)
	{
		min_v = INT_MAX;
		/* find the max value of i-th row */
		for (j = 0; j < n; ++j)
		{
			if (mat[i][j] <= min_v)
				min_v = mat[i][j];
		}

		for (j = 0; j < n; ++j)
		{
			if (mat[i][j] == min_v)
			{
				for (k = 0; k < m; ++k)
					if (mat[k][j] > min_v)
						break;
				if (k == m)
					cout << min_v << ' ';
			}
		}
	}
	return 0;
}
