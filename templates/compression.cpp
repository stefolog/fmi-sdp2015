#include <iostream>
#include <cstring>
#include <fstream>
#include "stack.cpp"
#include "queue.cpp"

using namespace std;

// A2(BC)
//  f^
// cout << A
// repeat 2, expr [B, C]
//      decompress(f -> , expr = [] )
// get(c)
// A2(BC)
//   f^     expr = [B]
// A2(BC)
//    f^     expr = [B, C]


// A2(BC3(X))
//   f^
// cout << A
// A2(BC3(X))
//  f^ repeat 2, expr [ ], decompress()
//     expr [B, C]
//     A2(BC3(X))
//         f^
//        --repeat 3, expr [ ], decompress()
//        | A2(BC3(X))
//        |       f^
//        |        expr [X]
//        +->repeat 3, expr [X]
//     expr [B, C, X ,X, X]

// 3(X2(B)Y)
//  ^
//   get -> X
// A-Z -> expr
// 2(A-Z) -> expr(A-Z, A-Z)
// ) return
void decompress(ifstream& input, queue<char>& expr) {
  while (input) {
    char c;
    input.get(c);
    if (')' == c) {
      return;

    } else if (c == '\n') {
      expr.push(c);

    } else if ('A' <= c && c <= 'Z') {
      expr.push(c);

    } else if ('0' <= c && c <= '9') {
      int repeat = c - '0';
      while (true) {
        input.get(c);
        if (c == '(') {
          break;
        }
        repeat *= 10;
        repeat += c - '0';
      }

      queue<char> internalRepeat;
      decompress(input, internalRepeat);

      while (repeat--) {
        queue<char> temp = internalRepeat;
        while (!temp.empty()) {
          char repeatChar;
          temp.pop(repeatChar);
          expr.push(repeatChar);
        }
      }
    }
  }
}

void printFile(const char * filename) {
  ifstream input(filename);
  while (input) {
    char c;
    input.get(c);
    cout << c;
  }
  input.close();
}

int main()
{
  // decompress("compression.sample");
  queue<char> expr;
  ifstream input("compression.sample");
  decompress(input, expr);

  while (!expr.empty()) {
    char c;
    expr.pop(c);
    cout << c;
  }

  cout << "EXPECTED =========================" << endl << endl;
  printFile("compression.expected");
  return 0;
}
