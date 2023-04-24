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
glist glist_delete(glist gl, const atom_t X);
void glist_format(glist& gl);
bool glist_isempty(const glist Gl);
glist glist_copy(const glist Gl);
void glist_print(const glist Gl);

int main(int argc, char* argv[])
{
	string str;
	char c;
	glist gl, gl_cp;

	if (argc > 1 && strcmp(argv[1], "-d") == 0)
		debug_en = true;
	cin >> str >> c;
	gl = create_from_str(str);
	gl_cp = glist_copy(gl);
	gl = glist_delete(gl_cp, c);
	gl_cp = glist_copy(gl);
	pb = buf;
	if (gl_cp != NULL)
	{
		glist_print(gl_cp);
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

glist glist_delete(glist gl, const atom_t X)
{
	glist p, pre, q;
	bool rt;

	if (gl == NULL)
		return gl;
	if (gl->type == ATOM)
	{
		if (gl->atom == X)
		{
			delete gl;
			gl = NULL;
		}
		return gl;
	}
	// gl is not atom
	pre = p = gl;
	rt = false;
	do {
		q = glist_delete(p->hp, X);
		if (q == NULL)
		{
			q = p->tp;
			delete p;
			p = q;
			if (rt == true)
				pre->tp = p;
			else
				pre = gl = p;
		}
		else
		{
			rt = true;
			p->hp = q;
			pre = p;
			p = p->tp;
		}
	} while (p != NULL);
	return gl;
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

glist glist_copy(const glist Gl)
{
	glist gl;

	if (Gl == NULL)
		return Gl;
	gl = new glist_node;
	if ((gl->type = Gl->type) == ATOM)
		gl->atom = Gl->atom;
	else
	{
		gl->hp = glist_copy(Gl->hp);
		gl->tp = glist_copy(Gl->tp);
	}
	return gl;
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