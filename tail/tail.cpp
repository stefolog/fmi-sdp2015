#include <iostream>
#include <fstream>

using namespace std;

void tail(const char * filename, int n) {
    ifstream f(filename);

    f.seekg(0, ios::end);
    streampos size = f.tellg();

    char c;
    bool nr = false;
    for (int i = 1; i < size && n > 0; i++) {
        f.seekg(-i, ios::end);
        f.get(c);
        if (f.fail()) {
            f.clear();
            f.seekg(0, ios:: beg);
            break;
        }
        if (c == '\n' || c == '\r') {
            if (!nr) {
                n--;
            }
            nr = !nr;
        } else {
            nr = false;
        }
    }
    while (f.get(c)) {
        cout << c;
    }

    f.close();
}

void sampleTail() {
    tail("tail-linux.txt", 2);
    cout << endl << endl;
    tail("tail-win.txt", 2);
}

int main()
{
    sampleTail();

    return 0;
}
