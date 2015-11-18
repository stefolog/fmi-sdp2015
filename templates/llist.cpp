#include <iostream>

using namespace std;


template <class T>
struct elem
{
  T inf;
  elem *link;
};


template <class T>
class LList
{
public:
  LList() {
    this->Start = NULL;
    this->End = NULL;
    this->Current = NULL;
  }

  ~LList() {
    if (this->Start != NULL) {
      delete this->Start;
    }
    if (this->End != NULL) {
      delete this->End;
    }
    if (this->Current != NULL) {
      delete this->Current;
    }
  }
  LList(LList const& x) {}
  LList& operator=(LList const & x) {}

  void IterStart(elem<T>* e = NULL) {
    this->Current = (e != NULL) ? e : this->Start;
  }

  elem<T>* Iter() {
    if (this->Current == NULL) {
      return NULL;
    }
    elem<T>* buf = this->Current;
    this->Current = this->Current->link;
    return buf;
  }

  void ToEnd(T const & x) {
    elem<T>* e = new elem<T>();
    e->inf = x;
    e->link = NULL;
    if ( this->End == NULL) {
      this->Start = this->End = e;
      return;
    }
    this->End->link = e;
    this->End = e;
  }

  void InsertAfter(elem<T> * e, T const & value) {
    elem<T>* next = new elem<T>();
    next->inf = value;
    next->link = e->link;
    e->link = next->link;
  }

  void InsertBefore(elem<T> * e, T const & value) {

  }

  int DeleteAfter(elem<T> * e, T & value) {
    if (!e->link) {
      return 0;
    }

    elem<T>* toDelete = e->link;
    if (toDelete == this->End) {
      this->End = e;
    }
    value = toDelete->inf;
    e->link = toDelete->link;
    delete toDelete;

    return 1;
  };

  int DeleteBefore(elem<T> * e, T & value) {
    return 0;
  };

  void DeleteElem(elem<T> * e, T & x) {

  };

  int len() {
    int c = 0;
    this->IterStart();
    while(this->Iter()) {
      c++;
    }
    return c;
  };

 private:
  elem<T> *Start, *End, *Current;
  void DeleteList() {};
  void CopyList(LList<T> const & x) {};
};

void initList(LList<int>* list) {
  while(true) {
    int x;
    cin >> x;
    if (x == 0) { break;}
    list->ToEnd(x);
  }
}
