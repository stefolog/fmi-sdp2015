#include <iostream>
#include "graph.cpp"
#include "llist.cpp"
#include "tree.cpp"
#include "person.cpp"

/*
1. Списък (int)
  a) Сумата на всеки 2ри елемент
  б) Сумата на елементи с индекси:
    - 1
    - 1 + (числото на позиция 1)
    - (числото на позиция 1) + (числото на (числото на позиция 1))
    - ...
    докато не излезем извън списъка или не направим len/2 сумирания

    вход: 1 2 3 -1 5 2 7 8 9 10 11
    2 + (-1) + 3 + 2 + 8

    вход: 1 2 3 -1 5 2 7 8 9
    2 + (-1) + 3 + 2 // заради len/2

2. Дърво (int)
  а) Сумата на всеки връх на поддърво с нечатна височина.
       7
      /
     5
    / \
   6   4
  / \
 3   1

3 + 1 + 5 + 4
  б) Въвежда се и 2ро дърво със същата структура, но с операции:
       *
      /
     -
    / \
   +   -
  / \
 /   *
  Да се намери сумата на:
  всеки връх на поддърво с нечатна височина
  с приложена съответната операция от второто дърво
  и втори операнд - отдалечеността от върха на дървото
(3 / 3) + (1 * 3) + (5 - 1) + (4 - 2)

3. Граф (Person)
  Дали мога да се запозная с Човек X, през приятели на същата възраст.
  Аз и Човек X сме на една и съща възраст.

*/

int applyOperation(char op, int a, int b) {
  switch (op) {
    case '*':
      return a * b;
    case '+':
      return a + b;
    case '/':
      return b != 0 ? a / b : 0;
    case '-':
      return a - b;
    default:
      return 0;
  }
}

int problem_2b(tree<int> & t, tree<char> & opt, int distanceToRoot, int & h) {
  if (t.empty()) {
    h = 0;
    return 0;
  }

  int hLeft = 0, hRight = 0;

  tree<int> leftTree = t.LeftTree();
  tree<int> rightTree = t.RightTree();

  tree<char> leftOpTree = opt.LeftTree();
  tree<char> rightOpTree = opt.RightTree();

  int sumLeft = problem_2b(leftTree, leftOpTree, distanceToRoot + 1, hLeft);
  int sumRight = problem_2b(rightTree, rightOpTree, distanceToRoot +1, hRight);

  h = 1 + max(hLeft, hRight);

  int sum = 0;
  if (h % 2 == 1) {
    sum = applyOperation(opt.RootTree(), t.RootTree(),distanceToRoot);
  }

  return sum + sumLeft + sumRight;
}

int problem_2a(tree<int> & t, int & h) {
  if (t.empty()) {
    h = 0;
    return 0;
  }

  int hLeft = 0, hRight = 0;
  tree<int> leftTree = t.LeftTree();
  tree<int> rightTree = t.RightTree();
  int sumLeft = problem_2a(leftTree, hLeft);
  int sumRight = problem_2a(rightTree, hRight);

  h = 1 + max(hLeft, hRight);
  if (h % 2 == 1) {
    return t.RootTree() + sumLeft + sumRight;
  } else {
    return sumLeft + sumRight;
  }
}

void problem2() {
  int h;

  tree<int> t;
  t.Create();

  tree<char> opt;
  opt.Create();
  cout << "Result:" << problem_2a(t, h) << endl;
  // 7y5y6y3nny1nny4nnn expected: 13

  cout << "Result:" << problem_2b(t, opt, 0, h) << endl;
  // 7y5y6y3nny1nny4nnn
  // *y-y+y/nny*nny-nnn expected: 10
}

template<class T>
LList<T> neighbours(graph<T> g, T e) {
  if (!g.top(e)) {
    return LList<T>();
  }

  elem<T> * glist = g.point(e);
  LList<T> neighbours;
  while (glist->link != NULL) {
    neighbours.ToEnd(glist->link->inf);
    glist = glist->link;
  }
  return neighbours;
}

bool contains(LList<Person> & list, Person x) {
  list.IterStart();
  elem<Person> * e = list.Iter();
  while (e) {
    if (e->inf == x) {
      return true;
    }
    e = list.Iter();
  }
  return false;
}

bool hasPath(graph<Person> g, Person& from, Person& to, LList<Person>& visited) {
  if (from == to) {
    return true;
  }

  if (contains(visited, from)) {
    return false;
  }

  visited.ToEnd(from);

  LList<Person> friends = neighbours(g, from);
  friends.IterStart();
  elem<Person> * fr = friends.Iter();
  while (fr) {
    Person aFriend = fr->inf;
    if (aFriend.age == from.age) {
      if (hasPath(g, aFriend, to, visited)) {
        cout << aFriend << " <- ";
        return true;
      }
    }
    fr = friends.Iter();
  }

  return false;
}

void problem_3() {
  graph<Person> g;

  Person pesho("Pesho", 20, LList<string>());
  Person ivan("Ivan", 20, LList<string>());
  Person petkan("Petkan", 20, LList<string>());
  Person mimi("Mimi", 20, LList<string>());
  Person mariika("Mariika", 20, LList<string>());
  Person pepa("Pepa", 20, LList<string>());
  Person dragan("Dragan", 20, LList<string>());

  g.addTop(pesho);
  g.addTop(ivan);
  g.addTop(petkan);
  g.addTop(mimi);
  g.addTop(mariika);
  g.addTop(pepa);
  g.addTop(dragan);

  g.addRib(pesho, ivan);
  g.addRib(pesho, petkan);
  g.addRib(pesho, mimi);
  g.addRib(pesho, mariika);

  g.addRib(petkan, mimi);
  g.addRib(petkan, mariika);
  g.addRib(petkan, pepa);
  g.addRib(mimi, dragan);


  LList<Person> visited;
  cout << "Result: " << hasPath(g, pesho, dragan, visited) << endl;
}

int main() {
  problem_3();
  return 0;
}
