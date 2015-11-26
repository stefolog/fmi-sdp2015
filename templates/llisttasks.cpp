#include <iostream>
#include "llist.cpp"
#include "stack.cpp"

using namespace std;

void print(LList<int>* list) {
  list->IterStart();

  elem<int> * e = list->Iter();
  while (e) {
    cout << e->inf << " ";
    e = list->Iter();
  }
  cout << endl;
}

void printElemReverse(elem<int> * e) {
  if (e != NULL) {
    printElemReverse(e->link);
    cout << e->inf << " ";
  }
}

void printReverse(LList<int>* list) {
  list->IterStart();
  printElemReverse(list->Iter());
  cout << endl;
}

template <class T>
void printReverseWithStack(LList<T>& list) {
  stack<T> s;
  list.IterStart();
  elem<T> *e = list.Iter();
  while (e) {
    s.push(e->inf);
    e = list.Iter();
  }

  T x;
  while(!s.empty()) {
    s.pop(x);
    cout << x << " ";
  }
  cout << endl;
}

bool hasDuplicate(LList<int>* list) {
  list->IterStart();
  elem<int> * e = list->Iter();
  while (e) {
    elem<int> * p = list->Iter();
    while (p) {
      if (p->inf == e->inf) {
        return true;
      }
      p = list->Iter();
    }
    list->IterStart(e);
    list->Iter();
    e = list->Iter();
  }
  return false;
}

template <class T>
struct OccurenceItem
{
  OccurenceItem() {
    this->count = 1;
  }

  OccurenceItem(const OccurenceItem& item) {
    this->inf = item->inf;
    this->count = item->count;
  }

  T inf;
  int count;
};

template <class T>
void countOccurences(LList<T>& list) {
  LList< OccurenceItem<T> > occurences;

  list.IterStart();
  elem<T> * e = list.Iter();
  while (e) {
    occurences.IterStart();
    elem< OccurenceItem<T> > * p = occurences.Iter();
    bool found = false;
    while (p) {
      if ((p->inf).inf == e->inf) {
        (p->inf).count++;
        found = true;
        break;
      }
      p = occurences.Iter();
    }

    if (!found) {
      OccurenceItem<T> item;
      item.inf = e->inf;
      item.count = 1;
      occurences.ToEnd(item);
    }

    e = list.Iter();
  }

  occurences.IterStart();
  elem<OccurenceItem<T> > * item = occurences.Iter();
  while (item) {
    cout << (item->inf).inf << " : " << (item->inf).count << endl;
    item = occurences.Iter();
  }
}

int main(int argc, char const *argv[])
{
  LList<int> list;
  // initList(list);
  // cout << "hasDuplicate: " << hasDuplicate(&list) << endl;
  print(&list);
  printReverse(&list);
  printReverseWithStack(list);
  countOccurences(list);
  cout << "Done" << endl;
  return 0;
}
