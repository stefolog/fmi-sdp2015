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

void problem_5() {
  tree<string> t;
  t.Create();

  cout << endl << endl;
  t.print();
  cout << endl << endl;
  cout << calculateExpression(t);
  cout << endl << endl;
}

/*
6. При зададено дърво и
получаване на операция (+ или *) и частично покриващо дърво,
приложете опрецията върху оригиналното дърво използвайки
най-близкия елемент на покриващото дърво като втори операнд.
input: tree, operation, delta tree

1 y 1 y 2 y 4 n n n y 3 n n y 1 y 2 n y 5 n n y 3 n n
*
5 y 3 n n n

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

int sum(int a, int b) {
  return a + b;
}

int mult(int a, int b) {
  return a * b;
}

tree<int> _applyOperation(
  tree<int> t, int (*operation)(int, int), tree<int> operands, int lastRootValue) {

  if (t.empty()) {
    return tree<int>();
  }

  int operand;
  tree<int> operandsLeft;
  tree<int> operandsRight;

  if (!operands.empty()) {
    operand = operands.RootTree();
    operandsLeft = operands.LeftTree();
    operandsRight = operands.RightTree();
  } else {
    operand = lastRootValue;
    operandsLeft = operands;
    operandsRight = operands;
  }

  int newRoot = (*operation)(t.RootTree(), operand);
  tree<int> left = _applyOperation(t.LeftTree(), operation, operandsLeft, operand);
  tree<int> right = _applyOperation(t.RightTree(), operation, operandsRight, operand);

  tree<int> result;
  result.Create3(newRoot, left, right);
  return result;
}

tree<int> applyOperation(tree<int> t, char operation, tree<int> operands) {
  if (operands.empty()) {
    // (0/1) | (+/*)
  }

  int (*f)(int, int);
  if (operation == '+') {
    f = sum;
  } else if (operation == '*') {
    f = mult;
  } else {
    throw "Operation not supported";
  }

  return _applyOperation(t, f, operands, operands.RootTree());
}

void problem_6() {
  tree<int> t;
  tree<int> operands;
  char operation;

  t.Create();
  cout << endl << endl << endl;
  cout << "Operation: ";
  cin >> operation;
  operands.Create();

  t = applyOperation(t, operation, operands);

  cout << endl << endl << endl;
  cout << "Result: ";
  t.print();
}

int main() {
  // problem_3();
  // problem_5();
  problem_6();


  return 0;
}






