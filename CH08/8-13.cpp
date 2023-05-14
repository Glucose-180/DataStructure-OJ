#include <vector>
#include <iostream>

using namespace std;

struct block {
	int flag;
	int loc;
	int size;
};

// free blocks and occupied blocks
vector<block> fblocks, oblocks;

void insert(block& ot);

int main()
{
	block temp;
	int i;

	while (cin >> temp.flag)
	{
		cin >> temp.loc >> temp.size;
		if (temp.size == 0)
			continue;	// Too SINISTER!!!
		if (temp.flag == 0)
		{	// free
			fblocks.push_back(temp);
		}
		else
		{	// occupied
			oblocks.push_back(temp);
		}
	}
	for (i = 0; i < oblocks.size(); ++i)
	{
		insert(oblocks.at(i));
	}
	for (i = 0; i < fblocks.size(); ++i)
	{
		temp = fblocks.at(i);
		cout << temp.flag << ' ';
		cout << temp.loc << ' ';
		cout << temp.size << endl;
	}
	return 0;
}

// insert ot in fblocks
void insert(block& ot)
{
	int i;
	int n = fblocks.size();

	ot.flag = 0;
	if (n == 0)
	{	// Too SINISTER!!!
		fblocks.push_back(ot);
		return;
	}
	for (i = 0; i < n; ++i)
	{
		if (ot.loc > fblocks.at(i).loc && ot.loc < fblocks.at((i + 1) % n).loc)
			break;
		if (fblocks.at(i).loc >= fblocks.at((i + 1) % n).loc && (ot.loc < fblocks.at((i + 1) % n).loc || ot.loc > fblocks.at(i).loc))
			break;
	}
	if (ot.loc + ot.size == fblocks.at((i + 1) % n).loc)
	{	// merge ot and its right block
		fblocks.at((i + 1) % n).loc = ot.loc;
		fblocks.at((i + 1) % n).size += ot.size;
	}
	else
	{
		if (ot.loc > fblocks.at(n - 1).loc)
			fblocks.insert(fblocks.begin() + n, ot);
		else
			fblocks.insert(fblocks.begin() + (i + 1) % n, ot);
	}
	n = fblocks.size();
	if (fblocks.at(i).loc + fblocks.at(i).size == fblocks.at((i + 1) % n).loc)
	{
		fblocks.at(i).size += fblocks.at(i + 1).size;
		fblocks.erase(fblocks.begin() + i + 1);
	}
}