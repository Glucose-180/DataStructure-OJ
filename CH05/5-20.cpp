#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct p_item {
	int coef;
	int x_exp;
	int y_exp;
};

inline bool poly_cmp(const p_item& I1, const p_item& I2);

int main(int argc, char* argv[])
{
	int m, n;
	int i, j;
	p_item temp;
	vector<p_item> poly;

	cin >> m >> n;
	for (i = 0; i < m; ++i)
		for (j = 0; j < n; ++j)
		{
			cin >> temp.coef;
			if (temp.coef != 0)
			{
				temp.x_exp = i;
				temp.y_exp = j;
				poly.push_back(temp);
			}
		}
	sort(poly.begin(), poly.end(), poly_cmp);
	for (i = 0; i < poly.size(); ++i)
	{
		if (poly.at(i).coef != 1 || poly.at(i).x_exp == 0 && poly.at(i).y_exp == 0)
			cout << poly.at(i).coef;
		if (poly.at(i).x_exp > 0)
			cout << "xE" << poly.at(i).x_exp;
		if (poly.at(i).y_exp > 0)
			cout << "yE" << poly.at(i).y_exp;
		if (i < poly.size() - 1)
			cout << '+';
	}
	return 0;
}

inline bool poly_cmp(const p_item& I1, const p_item& I2)
{
	/*if (I1.x_exp + I1.y_exp > I2.x_exp + I2.y_exp)
		return true;
	else if (I1.x_exp + I1.y_exp == I2.x_exp + I2.y_exp && I1.x_exp > I2.x_exp)
		return true;
	else
		return false;*/
	return (I1.x_exp > I2.x_exp || I1.x_exp == I2.x_exp && I1.y_exp > I2.y_exp);
}