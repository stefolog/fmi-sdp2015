#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "LList.cpp"

class graph
{
	public:
		void addTop(const T&);
		void deleteTop(const T&);
		void addRib(const T&, const T&);
		void deleteRib(const T&, const T&);
		bool top(const T&);
		bool rib(const T&, const T&);
		bool empty() const;
		elem_link1<T>* point(const T&);
		LList<T> vertexes();
		void print();
	private:
		LList< LList<T> > g;
};

// включва а като връх на неявния граф
template <typename T>
void graph<T>::addTop(const T& a)
{ // създаване на линеен списък, съдържащ елемента a
	LList<T> l;
	l.toEnd(a);
	// включване на върха a към графа
	g.toEnd(l);
}

// изключва върха а на неявния граф
template <typename T>
void graph<T>::deleteTop(const T& a)
{ // обхождане на графа с цел изтриване на всички
	// ребра от произволен връх до върха a
	g.iterStart();
	elem_link1<LList<T> >* p = g.iter(), *r;
	while(p)
	{
		p->inf.iterStart();
		elem_link1<T>* q = p->inf.iter();
		if(rib(q->inf, a)) deleteRib(q->inf, a);
		p = p->link;
	}
	// изтриване на линейния списък, представящ
	// върха a и неговите наследници
	g.iterStart();
	elem_link1<T>* q;
	do
	{
		r = g.iter();
		r->inf.iterStart();
		q = r->inf.iter();
	}
	while(q->inf != a); // a е връх на графа
	LList<T> x;
	g.deleteElem(r, x);
}

// включва ребро от върха a до върха b на неявния граф
template <typename T>
void graph<T>::addRib(const T& a, const T& b)
{ // намиране на указател към върха a на неявния граф
	elem_link1<T>* q = point(a), // намира указател към върха a
		*p;
	// включване на върха b в списъка от наследниците на върха a
	p = new elem_link1<T>;
	assert(p != NULL);
	p->inf = b;
	p->link = q->link;
	q->link = p;
}

// изключва реброто от върха a до върха b на неявния граф
template <typename T>
void graph<T>::deleteRib(const T& a, const T& b)
{
	g.iterStart();
	elem_link1<LList<T> > *p;
	elem_link1<T> *q;
	do
	{
		p = g.iter();
		p->inf.iterStart();
		q = p->inf.iter();
	}
	while(q->inf != a);
	q = q->link;
	// намиране на указател към наследника b на върха a
	while(q->inf != b) q = q->link;
	T x;
	p->inf.deleteElem(q, x);
}

// проверява дали a е връх на неявния граф
template <typename T>
bool graph<T>::top(const T& a)
{
	if(g.empty()) return false;
	g.iterStart();
	elem_link1<LList<T> > *p = g.iter();
	elem_link1<T> *q;
	do
	{
		p->inf.iterStart();
		q = p->inf.iter();
		p = p->link;
	}
	while(q->inf != a && p);

	return q->inf == a;
}

// проверява дали има ребро от върха a до върха b
template <typename T>
bool graph<T>::rib(const T& a, const T& b)
{
	elem_link1<T>* p = point(a); // намира указател към върха a
	p = p->link;
	while(p && p->inf != b) p = p->link;
	return p != NULL;
}

// проверява дали неявният граф е празен
template <typename T>
bool graph<T>::empty() const
{
	return g.empty();
}

// намира указател към върха a на графа
template <typename T>
elem_link1<T>* graph<T>::point(const T& a)
{
	g.iterStart();
	elem_link1<LList<T> > *p;
	elem_link1<T> *q;
	do
	{
		p = g.iter();
		p->inf.iterStart();
		q = p->inf.iter();
	}
	while(q->inf != a);
	return q;
}

// връща списък от върховете на неявния граф
template <typename T>
LList<T> graph<T>::vertexes()
{
	LList<T> l;
	g.iterStart();
	237
		elem_link1<LList<T> > *p = g.iter();
	while(p)
	{
		p->inf.iterStart();
		elem_link1<T>* q = p->inf.iter();
		l.toEnd(q->inf);
		p = p->link;
	}
	return l;
}

// извежда неявния граф
template <typename T>
void graph<T>::print()
{
	g.iterStart();
	elem_link1<LList<T> > *p = g.iter();
	while(p)
	{
		p->inf.print();
		p = p->link;
	}
	cout << endl;
}

#endif // !GRAPH_H_INCLUDED
