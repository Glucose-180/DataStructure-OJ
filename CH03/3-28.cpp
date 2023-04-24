#include <iostream>

using namespace std;

struct qnode {
	int data;
	qnode* next;
};

class queue
{
private:
	qnode* tail;
public:
	queue(void);
	void enter(int data);
	int depart(void);
	bool is_empty(void);
};

queue::queue()
{
	tail = NULL;
}

void queue::enter(int data)
{
	qnode* p;

	p = new qnode;
	p->data = data;
	if (!is_empty())
	{
		p->next = tail->next;
		tail->next = p;
	}
	else
	{
		p->next = p;
	}
	tail = p;
}

int queue::depart()
{
	int rt = -1;
	qnode* p;

	if (tail != NULL)
	{
		rt = tail->next->data;
		if (tail->next != tail)	/* more than 1 node */
		{
			p = tail->next;
			tail->next = p->next;
			delete p;
		}
		else
		{
			delete tail;
			tail = NULL;
		}
	}
	return rt;
}

bool queue::is_empty()
{
	if (tail == NULL)
		return true;
	else
		return false;
}

int main()
{
	int n;
	char c;
	queue q;

	cin >> n;
	do {
		cin >> n;
		q.enter(n);
	} while (cin.get(c) && c == ',');

	cout << q.depart();
	while (!q.is_empty())
	{
		cout << ',' << q.depart();
	}
	return 0;
}