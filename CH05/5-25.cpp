#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

typedef int mat_t;

struct nz_elem_t {
	mat_t data;
	int i;
	int j;
};	/* Non-zero element */

class matrix {
private:
	int* start_of_row;
public:
	vector<nz_elem_t> nz_elem;
	int row;
	int col;
	matrix(const int Row, const int Col);
	int index_of(const int I, const int J) const;	// in vector nz_elem
	matrix& add_nz_elem(const int Data, const int I, const int J);
	matrix& del_nz_elem(const int I, const int J);
	matrix& operator+=(const matrix& M2);
	matrix& print(void);
	~matrix(void);
};

matrix::matrix(const int Row, const int Col)
{
	if((row = Row)<=0  || (col = Col)<=0)
		exit(1);	/* error */
	start_of_row = new int[row];
	memset(start_of_row, 0, row * sizeof(int));
	nz_elem.clear();
}

matrix::~matrix()
{
	nz_elem.clear();
	delete[] start_of_row;
}

/* return the element whose location is (I,J) */
int matrix::index_of(const int I, const int J) const
{
	int i;

	for (i = start_of_row[I]; i < nz_elem.size() && I == nz_elem.at(i).i && J > nz_elem.at(i).j; ++i)
		;
	if (i < nz_elem.size() && I == nz_elem.at(i).i && J == nz_elem.at(i).j)
		return i;	/* non-zero */
	else
		return -1;	/* (I,J) not found */
}

matrix& matrix::add_nz_elem(const int Data, const int I, const int J)
{
	int i;

	if (I < 0 || I >= row || J < 0 || J >= col)
		exit(2);
	for (i = start_of_row[I]; i < nz_elem.size() && I == nz_elem.at(i).i && J > nz_elem.at(i).j; ++i)
		;
	if (i < nz_elem.size() && I == nz_elem.at(i).i && J == nz_elem.at(i).j)
		nz_elem.at(i).data = Data;
	else
	{
		nz_elem_t temp = { Data,I,J };
		nz_elem.insert(nz_elem.begin() + i, temp);
		for (i = I + 1; i < row; ++i)
			++start_of_row[i];
	}
	return *this;
}

matrix& matrix::del_nz_elem(const int I, const int J)
{
	int i;

	if ((i = index_of(I, J)) < 0)	// not found
		return *this;
	nz_elem.erase(nz_elem.begin() + i);
	for (i = I + 1; i < row; ++i)
		--start_of_row[i];
	return *this;
}

matrix& matrix::operator+=(const matrix& M2)
{
	int i, j;
	nz_elem_t temp;
	mat_t s;

	for (i = 0; i < M2.nz_elem.size(); ++i)		// O(M2.nz_elem.size())
	{
		temp = M2.nz_elem.at(i);
		if ((j = index_of(temp.i, temp.j)) < 0)	// O(M1.nz_elem.size())
			add_nz_elem(temp.data, temp.i, temp.j);
		else if ((s = nz_elem.at(j).data + temp.data) == 0)
			del_nz_elem(temp.i, temp.j);
		else
			nz_elem.at(j).data = s;
	}
	return *this;
}
// Complexity: O(M1.nz * M2.nz), nz: nember of non-zero elements

matrix& matrix::print()
{
	int i, j;
	int temp;

	for (i = 0; i < row; ++i)
	{
		for (j = 0; j < col; ++j)
		{
			cout << '\t' << ((temp = index_of(i, j)) < 0 ? 0 : nz_elem.at(temp).data);
		}
		cout << endl;
	}
	return *this;
}

int main(int argc, char* argv[])
{
	/*matrix m1(3, 4), m2(3, 4);

	m1.add_nz_elem(15, 0, 0);
	m1.add_nz_elem(-6, 1, 1);
	m1.add_nz_elem(22, 0, 3);
	m1.add_nz_elem(91, 2, 0);
	m1.add_nz_elem(-9, 1, 0);
	m1.del_nz_elem(1, 0);
	m1.print();
	cout << endl;
	m2.add_nz_elem(5, 0, 0);
	m2.add_nz_elem(4, 1, 0);
	m2.add_nz_elem(6, 1, 1);
	m2.print();
	cout << endl;
	m1 += m2;
	m1.print();*/
	int m, n;
	int i, j, k = 0;
	mat_t temp;
	char c;
	vector<mat_t> nz_temp;

	cin >> m >> n;
	matrix m1(m, n), m2(m, n);

	do {
		scanf("%d%c", &temp, &c);
		nz_temp.push_back(temp);
	} while (c == ' ');
	for (k = i = 0;i < m; ++i)
		for (j = 0; j < n; ++j)
		{
			cin >> temp;
			if (temp != 0)
				m1.add_nz_elem(nz_temp.at(k++), i, j);
		}
	if (argc > 1)
		m1.print();

	nz_temp.clear();
	do {
		scanf("%d%c", &temp, &c);
		nz_temp.push_back(temp);
	} while (c == ' ');
	for (k = i = 0; i < m; ++i)
		for (j = 0; j < n; ++j)
		{
			cin >> temp;
			if (temp != 0)
				m2.add_nz_elem(nz_temp.at(k++), i, j);
		}
	if (argc > 1)
		m2.print();

	m1 += m2;
	for (i = 0; i < m1.nz_elem.size(); ++i)
	{
		cout << m1.nz_elem.at(i).data;
		if (i < m1.nz_elem.size() - 1)
			cout << ' ';
	}
	cout << endl;
	for (i = 0; i < m1.row; ++i)
		for (j = 0; j < m1.col; ++j)
		{
			cout << (m1.index_of(i, j) < 0 ? '0' : '1') << (j < m1.col - 1 ? ' ' : '\n');
		}
	return 0;
}
