#include <iostream>
#include "math.h"

#include "tree.cpp"

using namespace std;

/*
  1. Височина на дърво
  2. Дали дървото е:
    - балансирано |H(l) - H(r)| <= 1
    - идеално балансирано
  3. Дали дървото е огледално
          5
         / \
        /   \
       4     4
      / \   / \
     3   2 2   3

  4. Изчислете израза, представен в двоично дърво по следния начин:
  израз: (5 + 2) * (10 -3) * 4 - 5
  представяне:
                -
               /\
              *  5
            /  \
           *    4
         /   \
        +     -
       /\    /\
      5  2 10  3

  5. При зададено дърво и
  получаване на операция (+ или *) и частично покриващо дърво,
  приложете опрецията върху оригиналното дърво използвайки
  най-близкия елемент на покриващото дърво като втори операнд.
  input: tree, operation, delta tree

  tree:
           1
          / \
         /   \
        1     1
       / \   / \
      2   3 2   3
     /       \
    4         5

  operation: *
  operands tree:
       5
      /
     3

  Result:
           5
          / \
         /   \
        3     5
       / \   / \
      6   9 10  15
     /       \
    12        25
*/

int treeHeight(tree<int> t) {
  if (t.empty()) {
    return 0;
  }

  int leftTreeHeight = treeHeight(t.LeftTree());
  int rightTreeHeight = treeHeight(t.RightTree());

  return 1 + max(leftTreeHeight, rightTreeHeight);
}

bool areMirrored(tree<int> l, tree<int> r) {
  if (l.empty() && r.empty()) {
    return true;
  }
  if (l.empty() || r.empty()) {
    return false;
  }
  if (l.RootTree() != r.RootTree()) {
    return false;
  }

  return areMirrored(l.LeftTree(), r.RightTree())
      && areMirrored(l.RightTree(), r.LeftTree());
}

bool isMirrored(tree<int> t) {
  if (t.empty()) {
    return true;
  }
  return areMirrored(t.LeftTree(), t.RightTree());
}


int main()
{
  tree<int> x;
  x.Create();
  cout << treeHeight(x) << endl;
  cout << isMirrored(x) << endl;
  return 0;
}
