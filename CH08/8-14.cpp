#ifndef __BUDDYSYSTEM_H__
#define __BUDDYSYSTEM_H__

#include <iostream>
#include <cstdint>

using namespace std;

#ifndef EM
#define EM 14U
#endif

#define SCALE 3

enum Tag_t { FREE = 1, OCCUPIED = 0 };

typedef struct header {
	uint32_t log2size;	/* log_2 (size) */
	int tag;
	struct header* next;
} header;

void bs_init(void);
void* bs_malloc(const uint32_t Size);
int bs_free(void* const P);
void print_freelist(void);
void bubble_sort(uint32_t* v, int n);
void print_for_oj();

#endif

struct {
	uint32_t size;
	header* first;
} freelist[EM + 1];
/* size: 2^0 ~ 2^EM */

/* Memory space to be allocated */
int8_t allocbuf[1U << EM];

static inline header* buddy(header* const P);

void bs_init()
{
	unsigned int i;
	header* p = (header*)allocbuf;

	for (i = 0; i <= EM; ++i)
	{
		freelist[i].size = (1U << i);
		freelist[i].first = NULL;
	}
	/*
	p->log2size = EM;
	p->next = NULL;
	p->tag = FREE;
	freelist[EM].first = p;*/
}

void* bs_malloc(const uint32_t Size)
{
	uint32_t n, i, k;
	header* p, * q;

	n = Size + sizeof(header);
	for (k = 0; k <= EM; ++k)
	{
		if (freelist[k].size >= n && freelist[k].first != NULL)
			break;
	}
	if (k > EM)
		return NULL;
	p = freelist[k].first;
	/* delete p in freelist */
	freelist[k].first = p->next;
	p->tag = OCCUPIED;
	if (k == 0)	/* almost impossible */
		return (void*)p;
	/* insert remaining blocks */
	for (i = k - 1; i > 0 && freelist[i].size >= n; --i)
	{
		q = (header*)((int8_t*)p + (1U << i));
		q->log2size = i;
		q->next = NULL;
		q->tag = FREE;
		freelist[i].first = q;
	}
	p->log2size = i + 1;
	return (void*)(p + 1);
}

int bs_free(void* const P)
{
	header* p = (header*)P - 1, * q;

	p->tag = FREE;
	for (q = buddy(p); (int8_t*)q - allocbuf < sizeof(allocbuf) && q->tag == FREE && q->log2size == p->log2size; p = q, q = buddy(p))
	{
		{	/* delete q from freelist */
			header* p;
			if (freelist[q->log2size].first == q)
				freelist[q->log2size].first = q->next;
			else
			{
				for (p = freelist[q->log2size].first; p != NULL && p->next != q; p = p->next)
					;
				if (p == NULL)
					return 1;	/* error */
				p->next = q->next;
			}
		}
		/* merge p and its buddy q */
		if (p < q)
			q = p;
		q->log2size += 1U;
	}
	/* insert p in freelist */
	p->next = freelist[p->log2size].first;
	freelist[p->log2size].first = p;
	return 0;
}

/* return P's buddy */
static inline header* buddy(header* const P)
{
	uint32_t loc, k;

	loc = (int8_t*)P - allocbuf;
	k = P->log2size;
	if ((loc >> k + 1) << k + 1 == loc)	/* loc MOD 2^(k+1) == 0 */
		return (header*)((uint8_t*)P + (1U << k));
	else
		return (header*)((uint8_t*)P - (1U << k));
}

void print_freelist()
{
	uint32_t i;
	header* p;

	for (i = 0; i <= EM; ++i)
	{
		printf("freelist[%u]: Size is %u\n", i, freelist[i].size);
		for (p = freelist[i].first; p != NULL; p = p->next)
		{
			printf("\tStart: %lld, log2size: %u, End: %lld, Tag: %d;\n", (int8_t*)p - allocbuf, p->log2size, (int8_t*)p - allocbuf + (ptrdiff_t)(1 << p->log2size) - 1, p->tag);
		}
	}
}

void bubble_sort(uint32_t* v, int n)
{
	int i, j;
	uint32_t t;

	for (i = n; i > 0; --i)
	{
		for (j = 1; j < i; ++j)
		{
			if (v[j] < v[j - 1])
				t = v[j], v[j] = v[j - 1], v[j - 1] = t;
		}
	}
}

void print_for_oj()
{
	uint32_t i, j, k;
	header* p;
	uint32_t buf[EM];

	for (i = 0; i <= EM; ++i)
	{
		if (freelist[i].first == NULL)
			continue;
		cout << i - SCALE;
		for (j = 0, p = freelist[i].first; p != NULL; p = p->next)
			buf[j++] = (int8_t*)p - allocbuf;
		bubble_sort(buf, j);
		for (k = 0; k < j; ++k)
			cout << ' ' << (buf[k] >> SCALE);
		cout << endl;
	}
}

int main()
{
	int i;
	char c;
	uint32_t loc;
	header* p;

	bs_init();
	cin.get(c);
	while (c != '\n')
	{
		i = c - '0' + SCALE;
		while (c != '\n')
		{
			cin >> loc;
			loc <<= SCALE;
			cin.get(c);
			p = (header*)(allocbuf + loc);
			p->log2size = i;
			p->tag = FREE;
			p->next = freelist[i].first;
			freelist[i].first = p;
		}
		cin.get(c);
	}

	while (cin >> i)
	{
		cin >> loc;
		loc <<= SCALE;
		i += SCALE;
		p = (header*)(allocbuf + loc);
		p->log2size = i;
		//p->tag = FREE;
		bs_free(p + 1);
	}

	print_for_oj();

	return 0;
}