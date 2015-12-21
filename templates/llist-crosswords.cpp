#include <iostream>
#include "llist.cpp"

using namespace std;

char atIdx(LList<char> list, int i) {
  list.IterStart();
  elem<char> *c;
  for (int a = 0; a <= i; a++) {
    c = list.Iter();
    if (c == NULL) {
      return '\0';
    }
  }
  return c->inf;
}

// '\0'
char atIdx(LList<LList<char> > list, int i, int j) {
  list.IterStart();
  elem<LList<char> > *curr;
  for (int a = 0; a <= i; a++) {
    curr = list.Iter();
    if (curr == NULL) {
      return '\0';
    }
  }

  return atIdx(curr->inf, j);
}
/*
6
alabala.
alibaba.
lala.
alibali.
liaa.
kak.
*/
int main() {
  LList<LList<char> > list;
  int n;
  cin >> n;
  while (n > 0) {
    LList<char> sublist;
    while (true) {
      char c;
      cin >> c;
      if (c == '.') {
        break;
      }
      sublist.ToEnd(c);
    }
    list.ToEnd(sublist);
    n--;
  }

  cout << endl << endl << endl;
  cout << "XXXX: " ;

  char word[50];
  cin.ignore();
  cin.getline(word, 50);
  cout << "[" << word << "]" << endl;

  int wl = strlen(word);
  int ll = list.len();

  for (int i = 0; i <= ll - wl; i++) {
    for (int j = 0; true; j++) {
      char c = atIdx(list, j, i);
      if (c == '\0') {
        break;
      }

      bool found = true;
      for (int k = 0; k < wl; k++) {
        cout << atIdx(list, j, i+k) << ",";
        if (atIdx(list, j, i+k) != word[k]) {
          found = false;
          break;
        }
      }
      if (found) {
        cout << "[i, j]: " << "[" << j << ", " << i << "]" << endl;
      }
    }
  }

  cout << "resutl:";
  cout << atIdx(list, 0, 0);
  cout << endl;


  return 0;
}
