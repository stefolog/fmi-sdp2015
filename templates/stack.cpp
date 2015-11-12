#include <iostream>

using namespace std;

template <class T>
class item
{
public:
  item(T x) {
    this->data = x;
  }
  T data;
  item* next;
};

template <class T>
class stack
{
private:
  item<T>* top;
public:
  stack<T>();

  void push(T x);
  int pop(T& result);
  bool empty();
};

template <class T>
stack<T>::stack() {
  top = NULL;
}

template <class T>
void stack<T>::push(T x) {
  item<T> *newTop = new item<T>(x);
  newTop->next = top;
  top = newTop;
}

template <class T>
int stack<T>::pop(T& result) {
  if (this->empty()) {
    return 0;
  }
  result = this->top->data;
  item<T> *oldTop = top;
  top = top->next;
  delete oldTop;
  return 1;
}

template <class T>
bool stack<T>::empty() {
  return top == NULL;
}


int main()
{
  stack<int> a;
  int x = 5;
  a.push(x);
  a.push(x + 1);
  a.push(x + 2);
  a.push(x + 3);
  while (!a.empty()) {
    a.pop(x);
    cout << x << endl;
  }

  return 0;
}
