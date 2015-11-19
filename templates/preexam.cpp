#include<iostream>
#include<fstream>
#include "stack.cpp"
#include "queue.cpp"

using namespace std;

queue<int> readIntsFromTextFile(const char * filename) {
  queue<int> input;

  char c;
  int currentNumber = 0;

  ifstream f (filename);
  while (f) {
    f.get(c); // read a single character
    if ( '0' <= c && c <= '9') {
      currentNumber *= 10;
      currentNumber += (c - '0');
    }
    if ( ',' == c) {
      input.push(currentNumber);
      currentNumber = 0;
    }
  }
  f.close();
  return input;
}

int main() {
  queue<int> input = readIntsFromTextFile("sample.in");

  // write to binary file
  ofstream f ("sample.bin", ios::binary);
  int x;
  while (!input.empty()) {
    input.pop(x);
    f.write((char*)&x, sizeof(int));
  }
  f.close();

  // read from binary file
  ifstream fi ("sample.bin", ios::binary);
  int y;
  while(fi) {
    fi.read((char*)&y, sizeof(int));
    input.push(y);
  }
  fi.close();


}












