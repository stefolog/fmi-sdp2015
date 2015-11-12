#include <iostream>
#include "stack.cpp"

using namespace std;

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
