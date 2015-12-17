#include <iostream>
#include <string>
#include "tree.cpp"
#include "stack.cpp"

using namespace std;

/*
1. Търсене на елемент в двоично наредено дърво
2. Проверка дали съществува път от корена до листо в дърво
- вход: дърво от букви
- вход: низ
- изход: дали има път от корена до листо в дървото, представен от низа
3. Проверка за път равен на сума
- вход: дърво от цели числа
- вход: число, представяващо сумата на търсения път
- изход: път, сумата на чийто възли е равна на въведеното число
4*. Tree-List
- От двойчно наредено дърво, само с промяна на указателите да се направи двойно свързан списък

5. Изчислете израза, представен в двоично дърво по следния начин:
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

6. При зададено дърво и
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

// 3. Проверка за път равен на сума
// - вход: дърво от цели числа
// - вход: число, представяващо сумата на търсения път
// - изход: път, сумата на чийто възли е равна на въведеното число
stack<int> notFound() {
  return stack<int>();
}

stack<int> foundLastElement(tree<int> t) {
  stack<int> s;
  s.push(t.RootTree());
  return s;
}

stack<int> found(stack<int> path, tree<int> t) {
  path.push(t.RootTree());
  return path;
}

stack<int> _findPath(tree<int> t, int sum) {
  if (t.empty()) {
    return notFound();
  }

  if (t.RootTree() == sum) {
    return foundLastElement(t);
  } else if (t.RootTree() > sum) {
    return notFound();
  } else { // t.RootTree() < sum
    stack<int> left = _findPath(t.LeftTree(), sum - t.RootTree());
    if (!left.empty()) {
      return found(left, t);
    }

    stack<int> right = _findPath(t.RightTree(), sum - t.RootTree());
    if (!right.empty()) {
      return found(right, t);
    }

    return notFound();
  }
}

stack<int> findPath(tree<int> t, int sum) {
  if (t.empty()) {
    if (sum == 0) {
      stack<int> s;
      s.push(0);
      return s;
    } else {
      return notFound();
    }
  }
  return _findPath(t, sum);

}

void problem_3() {
  stack<int> s;
  tree<int> t;
  t.Create();

  cout << endl << endl << endl;

  int sum;
  cout << "Sum: ";
  cin >> sum;

  cout << "Path: ";
  findPath(t, sum).print();
  cout << endl;
}

//           -
//          /\
//         *  5
//       /  \
//      *    4
//    /   \
//   +     -
//  /\    /\
// 5  2 10  3

int toInt(string s) {
  return stoi(s);
}

int calculateExpression(tree<string> t) {
  if (t.empty()) {
    return 0;
  }

  string root = t.RootTree();
  if (strchr("*-/+", root[0]) != NULL) {
    int left = calculateExpression(t.LeftTree());
    int right = calculateExpression(t.RightTree());

    switch(root[0]) {
      case '+':
        return left + right;
      case '*':
        return left * right;
      case '-':
        return left - right;
      case '/':
        return left / right;
      default:
        throw 1;
    }
  } else {
    return toInt(root);
  }
}

int main() {
  tree<string> t;
  t.Create();

  cout << endl << endl;
  t.print();
  cout << endl << endl;
  cout << calculateExpression(t);
  cout << endl << endl;

  return 0;
}






