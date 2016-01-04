#include <iostream>
#include "llist.cpp"

using namespace std;

// Returns '\0' for not found
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

// Returns '\0' for not found
char atIdx(LList<LList<char> > list, int row, int col) {
  list.IterStart();
  elem<LList<char> > *curr;
  for (int i = 0; i <= col; i++) {
    curr = list.Iter();
    if (curr == NULL) {
      return '\0';
    }
  }

  return atIdx(curr->inf, row);
}
/*
Sample Input:

6
alabala.
alibaba.
lala.
alibali.
liaa.
kak.
ailiak

*/
int main() {
  LList<LList<char> > list;
  int n;
  cout << "Number of words: ";
  cin >> n;
  cout << "Enter that many words with . for end:" << endl;
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
  cout << "Search for word: " ;

  char word[50];
  cin.ignore();
  cin.getline(word, 50);

  int wl = strlen(word);
  int ll = list.len();

  for (int col = 0; col <= ll - wl; col++) {
    for (int row = 0; true; row++) {
      char c = atIdx(list, row, col);
      if (c == '\0') {
        break;
      }

      bool found = true;
      for (int k = 0; k < wl; k++) {
        if (atIdx(list, row, col+k) != word[k]) {
          found = false;
          break;
        }
      }

      if (found) {
        cout << "Found at [row, col]: " << "[" << row << ", " << col << "]" << endl;
        break;
      }
    }
  }

  cout << endl;
  return 0;
}
