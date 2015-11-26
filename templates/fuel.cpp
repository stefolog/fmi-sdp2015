#include <iostream>
#include <fstream>
#include <math.h>
#include "queue.cpp"

using namespace std;

/*
1 20.15
1 10.12
2 13.42
3 17.00
2 12.07
4 6.88
1 19.7
1 12.12
4 100
*/

struct Gas
{
  int counterId;
  double quantity;
};

int parseInt(ifstream& input) {
  int number = 0;
  while (true) {
    char c;
    input.get(c);
    if ('0' <= c && c <= '9') {
      number *= 10;
      number += c - '0';
    } else {
      return number;
    }
  }
}

double parseDouble(ifstream& input) {
  double a = 0;
  int countDecimalPoints = 0;
  bool isDecimalPart = false;

  while (true) {
    char c;
    input.get(c);
    if ('0' <= c && c <= '9') {
      a *= 10;
      a += c - '0';
      if (isDecimalPart) {
        countDecimalPoints++;
      }
    } else if ('.' == c) {
      isDecimalPart = true;
    } else {
      return a / pow(10, countDecimalPoints);
    }
  }
}

void prepareTestBinaryFile() {
  ofstream output("fuel_sales.sample.bin", ios::binary);
  Gas g;

  g.counterId = 1;
  g.quantity = 20.15;
  output.write((char*)&g, sizeof(g));

  g.counterId = 1;
  g.quantity = 10.12;
  output.write((char*)&g, sizeof(g));

  g.counterId = 2;
  g.quantity = 13.42;
  output.write((char*)&g, sizeof(g));

  g.counterId = 3;
  g.quantity = 17.00;
  output.write((char*)&g, sizeof(g));

  g.counterId = 2;
  g.quantity = 12.07;
  output.write((char*)&g, sizeof(g));

  g.counterId = 4;
  g.quantity = 6.88;
  output.write((char*)&g, sizeof(g));

  g.counterId = 1;
  g.quantity = 19.7;
  output.write((char*)&g, sizeof(g));

  g.counterId = 1;
  g.quantity = 12.12;
  output.write((char*)&g, sizeof(g));

  g.counterId = 4;
  g.quantity = 100;
  output.write((char*)&g, sizeof(g));

  output.close();
}

void inputFromBin() {
  ifstream input("fuel_sales.sample.bin", ios::binary);
  while(true) {
    Gas g;
    if (!input.read((char*)&g, sizeof(Gas))) {
      break;
    }
    cout << g.counterId << " xxx " << g.quantity << endl;
  }
  input.close();
}

void inputFromTxt() {
  ifstream input("fuel_sales.sample.txt");
  while(true) {
    Gas g;
    g.counterId = parseInt(input);
    g.quantity = parseDouble(input);

    if (!input) {
      break;
    }
    cout << g.counterId << " xxx " << g.quantity << endl;
  }
  input.close();
}

double totalForCounter(int counterId, double pricePerLiter) {
  ifstream input("fuel_sales.sample.txt");

  double totalIncome = 0.0;
  while(true) {
    Gas g;
    g.counterId = parseInt(input);
    g.quantity = parseDouble(input);

    if (!input) {
      break;
    }

    if (counterId == g.counterId) {
      totalIncome += g.quantity * pricePerLiter;
    }
  }
  input.close();
  return totalIncome;
}

struct AvgGas
{
  int counterId;
  double quantity;
  int count;
};

void findAvgGasById(queue<AvgGas> & avgs, int id) {
  if (avgs.empty()) {
    AvgGas g;
    g.counterId = id;
    g.quantity = 0.0;
    g.count = 0;
    avgs.push(g);

    return;
  }

  AvgGas g;
  avgs.head(g);

  int firstId = g.counterId;
  if (firstId == id) {
    return;
  }

  while (true) {
    avgs.pop(g);
    avgs.push(g);
    avgs.head(g);
    if (g.counterId == id) {
      return;
    }
    if (g.counterId == firstId) {
      AvgGas ng;
      ng.counterId = id;
      ng.quantity = 0.0;
      ng.count = 0;
      avgs.push(ng);
      findAvgGasById(avgs, id);
      return;
    }
  }
}

void writeAverages() {
  ifstream input("fuel_sales.sample.txt");

  queue<AvgGas> avgs;
  int maxCounterId = 0;

  double totalIncome = 0.0;
  while(true) {
    Gas g;
    g.counterId = parseInt(input);
    g.quantity = parseDouble(input);

    if (!input) {
      break;
    }

    if (g.counterId > maxCounterId) {
      maxCounterId = g.counterId;
    }

    findAvgGasById(avgs, g.counterId);
    AvgGas c;
    avgs.head(c);

    c.quantity += g.quantity;
    c.count++;
  }
  input.close();

  for (int i = 1; i <= maxCounterId; i++) {
    findAvgGasById(avgs, i);
    AvgGas c;
    avgs.head(c);
    cout << c.count;
    cout << c.counterId << " :: " << (c.quantity / c.count) << endl;
  }
}

int main() {
  // inputFromTxt();
  // cout << endl << "==========================" << endl;
  // prepareTestBinaryFile();
  // inputFromBin();
  writeAverages();

  return 0;
}
