#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

typedef int mat_t;

struct nz_elem_t {
	mat_t data;
	int i;
	int j;
	nz_elem_t* right, * down;	/* for Orthogonal linked list */
};	/* Non-zero element */

struct matrix_ol {
	nz_elem_t** row_h;
	nz_elem_t** col_h;	/* head of rows and columns */
	int row;
	int col;	/* size */
};

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
	matrix_ol to_ol(void);
	~matrix(void);
};

matrix_ol& ol_add_nz_elem(matrix_ol& mol, const mat_t Data, const int I, const int J);
matrix_ol& ol_del_nz_elem(matrix_ol& mol, const int I, const int J);
matrix_ol& mat_add(matrix_ol& m1, const matrix_ol& M2);
void matrix_ol_print(const matrix_ol& mat);

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

/* use class to create orthogonal linked list */
matrix_ol matrix::to_ol()
{
	int i;
	nz_elem_t temp;
	struct matrix_ol mol = { NULL,NULL,row,col };

	mol.row_h = new nz_elem_t * [row];
	mol.col_h = new nz_elem_t * [col];
	memset(mol.row_h, 0, sizeof(nz_elem_t*) * row);
	memset(mol.col_h, 0, sizeof(nz_elem_t*) * col);
	for (i = 0; i < nz_elem.size(); ++i)
	{
		temp = nz_elem.at(i);
		ol_add_nz_elem(mol, temp.data, temp.i, temp.j);
	}
	return mol;
}

/* add a non-zero elem to mol */
matrix_ol& ol_add_nz_elem(matrix_ol& mol, const mat_t Data, const int I, const int J)
{
	nz_elem_t * p, * q;

	p = new nz_elem_t;
	p->data = Data;
	p->i = I;
	p->j = J;
	if (mol.row_h[I] == NULL || mol.row_h[I]->j > J)
	{	/* insert this node at the begining of this row */
		p->right = mol.row_h[I];
		mol.row_h[I] = p;
	}
	else
	{
		for (q = mol.row_h[I]; q->right != NULL && q->right->j < J; q = q->right)
			;
		p->right = q->right;
		q->right = p;
	}
	if (mol.col_h[J] == NULL || mol.col_h[J]->i > I)
	{	/* insert this node at the begining of this column */
		p->down = mol.col_h[J];
		mol.col_h[J] = p;
	}
	else
	{
		for (q = mol.col_h[J]; q->down != NULL && q->down->i < I; q = q->down)
			;
		p->down = q->down;
		q->down = p;
	}
	return mol;
}

matrix_ol& ol_del_nz_elem(matrix_ol& mol, const int I, const int J)
{
	nz_elem_t* p, * q, * r;
	//r: point to the node to be deleted
	p = mol.row_h[I], q = mol.col_h[J];
	// delete in row
	if (p != NULL && p->j == J)
	{
		r = p;
		mol.row_h[I] = r->right;
	}
	else if (p == NULL || p->j > J)
		return mol;
	else	// p != NULL && p->j < J
	{
		for (; p->right != NULL && p->right->j < J; p = p->right)
			;
		if (p->right != NULL && p->right->j == J)
		{
			r = p->right;
			p->right = r->right;
		}
		else
			return mol;
	}
	// delete in column
	if (q == r)
	{
		mol.col_h[J] = r->down;
	}
	else
	{
		for (; q->down != NULL && q->down->i < I; q = q->down)
			;
		// q->down->i == I
		q->down = r->down;
	}
	delete r;
	return mol;
}

/* m1 += M2 */
matrix_ol& mat_add(matrix_ol& m1, const matrix_ol& M2)
{
	int i, j;
	nz_elem_t* p1, * p2;
	mat_t s;

	for (i = 0; i < m1.row; ++i)
	{
		for (p1 = m1.row_h[i], p2 = M2.row_h[i]; p2 != NULL; )
		{
			if (p1 == NULL || p1->j > p2->j)
			{
				ol_add_nz_elem(m1, p2->data, i, p2->j);
				p2 = p2->right;
			}
			else if (p1->j < p2->j)
				p1 = p1->right;
			else // p1->j == p2->j
			{
				if ((s = p1->data + p2->data) != 0)
				{
					p1->data = s;
					p1 = p1->right;
				}
				else
				{
					/* delete node p1 */
					j = p1->j;
					p1 = p1->right;
					ol_del_nz_elem(m1, i, j);
				}
				p2 = p2->right;
			}
		}
	}
	return m1;
}

void matrix_ol_print(const matrix_ol& mat)
{
	int i, j;
	nz_elem_t* p;
	int nz_ymr = 0;

	for (i = 0; i < mat.row; ++i)
	{
		for (p = mat.row_h[i]; p != NULL; p = p->right)
			++nz_ymr;
	}
	if (nz_ymr == 0)
		cout << endl;
	else
		for (i = 0; i < mat.row; ++i)
		{
			for (p = mat.row_h[i]; p != NULL; p = p->right)
				cout << p->data << (--nz_ymr > 0 ? ' ' : '\n');
		}
	for (i = 0; i < mat.row; ++i)
	{
		nz_ymr = mat.col;
		for (j = 0, p = mat.row_h[i]; p != NULL; ++j, p = p->right)
		{
			for (; j < p->j; ++j)
			{
				cout << '0' << (--nz_ymr > 0 ? ' ' : '\n');
			}
			cout << '1' << (--nz_ymr > 0 ? ' ' : '\n');
		}
		while (j++ < mat.col)
			cout << '0' << (--nz_ymr > 0 ? ' ' : '\n');
	}
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
	matrix_ol mol1, mol2;

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
/*  for 5-25::
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
*/
	mol1 = m1.to_ol();
	mol2 = m2.to_ol();
	mat_add(mol1, mol2);
	matrix_ol_print(mol1);
	return 0;
}
