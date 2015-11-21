#include <iostream>
#include "stack.cpp"

using namespace std;

const char * input0 = "{(a+b)-[(c+d)*(a+c)]}"; // OK
const char * input1 = "{(a+b})-[(c+d)*(a+c)]}"; // error
const char * input2 = "{(a+b]-[(c+d)*(a+c)]}"; //
const char * input3 = "[(c+d)*(a+c)";
const char * input4 = "}";

bool isCorrect(const char * c) {
  stack<char> s;
  char temp;

  for (int i = 0; c[i]; i++) {
    if ((c[i] == '(') || (c[i] == '[') || (c[i] == '{')) {
      s.push(c[i]);
    } else {
      char expected = 'x';
      if (c[i] == ')') expected = '(';
      if (c[i] == ']') expected = '[';
      if (c[i] == '}') expected = '{';

      if (expected != 'x') {
        if (s.empty()) {
          return false;
        }
        char temp;
        s.pop(temp);
        if (temp != expected) {
          return  false;
        }
      }
    }
  }
  return s.empty();
}

int main() {
  cout << (isCorrect(input0) == true) << endl;
  cout << (isCorrect(input1) == false) << endl;
  cout << (isCorrect(input2) == false) << endl;
  cout << (isCorrect(input3) == false) << endl;
  cout << (isCorrect(input4) == false) << endl;

  return 0;
}
