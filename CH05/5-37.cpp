#include <string>
#include <iostream>
#include <cstring>

#define hp ptr.pt_head
#define tp ptr.pt_tail

using namespace std;

typedef char atom_t;

enum Elem_type { ATOM,LIST };

struct glist_node {
	Elem_type type;
	union {
		atom_t atom;
		struct {
			glist_node* pt_head;
			glist_node* pt_tail;
		} ptr;
	};
};

typedef glist_node* glist;

bool debug_en = false;
char buf[100];
char* pb;

string str_sever(string& str);
glist create_from_str(string str);
void glist_delete(glist& gl, const atom_t X);
void glist_format(glist& gl);
bool glist_isempty(const glist Gl);
void glist_print(const glist Gl);

int main(int argc, char* argv[])
{
	string str;
	char c;
	glist gl;

	if (argc > 1 && strcmp(argv[1], "-d") == 0)
		debug_en = true;
	cin >> str >> c;
	gl = create_from_str(str);
	if (debug_en)
	{
		//glist_print(gl);
		cout << endl;
	}
	glist_delete(gl, c);
	glist_format(gl);
	pb = buf;
	if (gl != NULL)
	{
		glist_print(gl);
		cout << buf;
	}
	else
		cout << -1;
	cout << endl;
	return 0;
}

glist create_from_str(string str)
{
	glist gl, p, q;
	string fs;

	if (str == "()")
		return NULL;
	gl = new glist_node;
	if (str.size() == 1)
	{
		gl->type = ATOM;
		gl->atom = str.at(0);
		return gl;
	}
	gl->type = LIST;
	p = gl;
	str = str.substr(1, str.size() - 2);
	while (1)
	{
		fs = str_sever(str);
		p->hp = create_from_str(fs);
		q = p;
		if (str.empty())
			break;
		q->tp = p = new glist_node;
		p->type = LIST;
	}
	q->tp = NULL;
	return gl;
}

/* return the substr before first ',', and str becomes the remaining */
string str_sever(string& str)
{
	string::size_type i;
	unsigned int bra_ymr; // count brackets
	char c;
	string fs;

	for (bra_ymr = i = 0; i < str.size(); ++i)
	{
		c = str.at(i);
		if (c == '(')
			++bra_ymr;
		else if (c == ')')
			--bra_ymr;
		else if (c == ',' && bra_ymr == 0)
			break;
	}
	fs = str.substr(0, i);
	if (i == str.size())
		str.clear();
	else
		str = str.substr(i + 1);
	return fs;
}

void glist_delete(glist& gl, const atom_t X)
{
	glist h, p;

	if (gl == NULL)
		return;
	h = gl->hp;
	if (h != NULL && h->type == ATOM && h->atom == X)
	{
		p = gl;
		gl = gl->tp;
		delete h;
		delete p;
		glist_delete(gl, X);
	}
	else if (h != NULL && h->type == LIST)
	{
		glist_delete(gl->hp, X);
		glist_delete(gl->tp, X);
	}
	else	// h->type == ATOM but h->atom != X
	{
		glist_delete(gl->tp, X);
	}
}

/* delete all empty sublists */
/* memory leak is possible! */
void glist_format(glist& gl)
{
	if (gl == NULL || gl->type == ATOM)
		return;
	if (glist_isempty(gl))
	{
		delete gl;
		gl = NULL;
		return;
	}
	// not empty
	glist_format(gl->hp);
	glist_format(gl->tp);
}

/* calc whether a sublist has 0 atom */
bool glist_isempty(const glist Gl)
{
	if (Gl == NULL)
		return true;
	if (Gl->type == ATOM)
		return false;
	return glist_isempty(Gl->hp) && glist_isempty(Gl->tp);
}

void glist_print(const glist Gl)
{
	glist p;

	if (Gl == NULL)
	{
		//cout << -1;
		return;
	}
	//cout << '(';
	*pb++ = '(';
	for (p = Gl; p != NULL; p = p->tp)
	{
		if (p->hp != NULL)
		{
			if (p->hp->type == ATOM)
				*pb++ = p->hp->atom;//cout << char(p->hp->atom);
			else
				glist_print(p->hp);
			*pb++ = ',';//cout << ',';
		}
	}
	//cout << '\b' << ')';
	*--pb = ')';
	++pb;
}