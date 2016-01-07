#include <iostream>
#include <string>

#include "graph.cpp"

class Person {
public:
  string name;
  int age;
  LList<string> likes;

  Person() {

  }

  Person(string name, int age, LList<string> likes) {
    this->name = name;
    this->age = age;
    this->likes = likes;
  }

  Person(const Person& other) {
    name = other.name;
    age = other.age;
    likes = other.likes;
  }

  Person& operator=(const Person& other) {
    if (&other != this) {
      name = other.name;
      age = other.age;
      likes = other.likes;
    }
    return *this;
  }

  bool operator==(const Person& other) {
    return this->name == other.name;
  }

  bool operator!=(const Person& other) {
    return this->name != other.name;
  }
};

ostream& operator<<(ostream& out, Person& p) {
  out << p.name << " : " << p.age << endl;
  return out;
}

/*
Имаме ненасочен граф от хора и връзките между тях означават дали са приятели.
Всечи човек има:
  Име
  Възраст
  Списък от интереси (LList<string>)
  Училище

1. За избран човек, да се изведе кои са неговите приятели на същата възраст.
2. За избран човек, да се изведат приятели на неговите приятели, които имат поне 2 общи интереса с него. Хората да се изведат по брой общи интереси в низходящ ред.
3. За избран човек, да се изведат всички хора, на негова възраст, които са учили в същото училище, но не са приятели с него.
3*. Списък от хора да бъде сортиран, по:
  - брой общи приятели низходящо
  - ако е равен на 0, по отдалеченост на познанството (през колко човека се познават)
  - ако е равен, по азбучен ред
4. За избран човек, да се изведат всички приятели на приятели, които имат поне 5 общи приятеля с него.
*/
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

void problem_1(graph<Person> g, Person person) {
  LList<Person> n = neighbours<Person>(g, person);
  n.IterStart();

  elem<Person> * aFriend;
  while ((aFriend = n.Iter())) {
      if ((aFriend->inf).age == person.age) {
        cout << (aFriend->inf) << endl;
      }
  }
}

template<class T>
bool contains(LList<T> list, T& e) {
  list.IterStart();

  elem<T> * p;
  while ((p = list.Iter())) {
    if (p->inf == e) {
      return true;
    }
  }
  return false;
}

/*
2. За избран човек, да се изведат приятели на неговите приятели, които имат поне 2 общи интереса с него. Хората да се изведат по брой общи интереси в низходящ ред.
*/
LList<Person> findFriendsOfFriends(graph<Person> g, Person person) {
  LList<Person> result;

  LList<Person> friends = neighbours<Person>(g, person);
  elem<Person> * pFriend;

  friends.IterStart();
  while ((pFriend = friends.Iter())) {
    LList<Person> friendsFriends = neighbours(g, pFriend->inf);
    elem<Person> * pf;
    friendsFriends.IterStart();
    while ((pf = friendsFriends.Iter())) {
      if (pf->inf == person) {
        continue;
      }
      if (contains(friends, pf->inf)) {
        continue;
      }

      result.ToEnd(pf->inf);
    }
  }

  return result;
}

int numberOfCommonInterests(Person a, Person b) {
  int commonInterests = 0;

  a.likes.IterStart();
  elem<string> * ps;
  while ( (ps = a.likes.Iter()) ) {

    if (contains(b.likes, ps->inf)) {
      commonInterests++;
    }
  }

  return commonInterests;
}

LList<Person> filterByCommonInterests(LList<Person>& people, Person person, int minCommonInterests) {

  LList<Person> result;

  people.IterStart();
  elem<Person> * pff;
  while ((pff = people.Iter())) {
    if (numberOfCommonInterests(person, pff->inf) >= minCommonInterests) {
      result.ToEnd(pff->inf);
    }
  }

  return result;
}

void problem_2(graph<Person> g, Person person) {
  if (person.likes.len() < 2) {
    cout << "You succcccc " << endl;
    return;
  }


  LList<Person> friendsOfFriends = findFriendsOfFriends(g, person);
  LList<Person> result = filterByCommonInterests(friendsOfFriends, person, 2);

  cout << "Friends of Friends:" << endl;
  friendsOfFriends.print();
  cout << endl;
  cout << "Friends of Friends with 2 interests:" << endl;
  result.print();
}

int main() {
  graph<Person> g;

  LList<string> peshoLikes;
  peshoLikes.ToEnd("rakia");
  peshoLikes.ToEnd("salata");
  peshoLikes.ToEnd("musaka");
  peshoLikes.ToEnd("bob");

  LList<string> pepaLikes;
  pepaLikes.ToEnd("nutela");
  pepaLikes.ToEnd("vino");
  pepaLikes.ToEnd("musaka");

  LList<string> draganLikes;
  draganLikes.ToEnd("rakia");
  draganLikes.ToEnd("nutela");
  draganLikes.ToEnd("bob");

  Person pesho("Pesho", 20, peshoLikes);
  Person ivan("Ivan", 25, LList<string>());
  Person petkan("Petkan", 22, LList<string>());
  Person mimi("Mimi", 20, LList<string>());
  Person mariika("Mariika", 22, LList<string>());
  Person pepa("Pepa", 20, pepaLikes);
  Person dragan("Dragan", 20, draganLikes);

  g.addTop(pesho);
  g.addTop(ivan);
  g.addTop(petkan);
  g.addTop(mimi);
  g.addTop(mariika);
  g.addTop(pepa);
  g.addTop(dragan);

  g.addRib(pesho, ivan);
  g.addRib(pesho, petkan);
  g.addRib(pesho, mimi); // result
  g.addRib(pesho, mariika);

  g.addRib(petkan, mimi);
  g.addRib(petkan, mariika);
  g.addRib(petkan, pepa);
  g.addRib(mimi, dragan);

  // neighbours(g, pesho).print();

  // problem_1(g, pesho);
  problem_2(g, pesho);
  return 0;
}
