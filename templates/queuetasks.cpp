#include <iostream>
#include "queue.cpp"

using namespace std;

int main()
{
  queue<int> a;
  int x = 5;
  a.InsertElem(x);
  a.InsertElem(x + 2);
  a.InsertElem(x + 5);
  a.InsertElem(x + 10);

  cout << a.DeleteElem(x) << " " << x << endl;
  cout << a.DeleteElem(x) << " " << x << endl;

  a.print();
  return 0;
}
