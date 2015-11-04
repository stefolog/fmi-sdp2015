#include <iostream>

using namespace std;

class ASCIILetter {
public:
    static const int letterRows = 6;
    static const int letterCols = 6;

private:
    const char *f[letterCols + 1];
    const char *m[letterCols + 1];
    const char *i[letterCols + 1];

    void init() {
        f[0] = "FFFFFF";
        f[1] = "FF    ";
        f[2] = "FFFFFF";
        f[3] = "FF    ";
        f[4] = "FF    ";
        f[5] = "FF    ";

        m[0] = "M    M";
        m[1] = "MM  MM";
        m[2] = "M MM M";
        m[3] = "M    M";
        m[4] = "M    M";
        m[5] = "M    M";

        i[0] = "IIIIII";
        i[1] = "  II  ";
        i[2] = "  II  ";
        i[3] = "  II  ";
        i[4] = "  II  ";
        i[5] = "IIIIII";
    }

    const char* find_char_line(char c, int line) {
        switch (c) {
        case 'i':
            return i[line];
        case 'm':
            return m[line];
        case 'f':
            return f[line];
        default:
            return "      ";
        }
    }

    char c;

public:
    ASCIILetter() {
        this->c = ' ';
        init();
    }
    ASCIILetter(char c) {
        this->c = c;
        init();
    }

    void print_char_line(int line) {
        cout << find_char_line(this->c, line);
    }
};


class ASCIIConsolePrinter {
private:
    int lettersPerLine;
    int consoleLineSize;
    ASCIILetter* consoleLine;

    // This function will modify the text pointer!
    bool readConsoleLine(const char*& text) {
        // nothing to read
        if (!*text) {
            this->consoleLineSize = 0;
            return false;
        }

        // set to max, and eventually it will be set to smaller number
        this->consoleLineSize = this->lettersPerLine;
        for (int i = 0; i < this->lettersPerLine; i++, text++) {
            this->consoleLine[i] = ASCIILetter(*text);
            if (!*text) {
                // mark preliminary end of line
                this->consoleLineSize = i;
                break;
            }
        }

        // we read at least 1 char
        return true;
    }

    void printConsoleLine() {
        for (int i = 0; i < ASCIILetter::letterRows; i++) {
            for (int j = 0; j < this->consoleLineSize; j++) {
                if (j != 0) {
                        cout << "  ";
                }
                this->consoleLine[j].print_char_line(i);
            }
            cout << endl;
        }
    }

public:
    ASCIIConsolePrinter(int consoleWidth) {
        this->lettersPerLine = (consoleWidth + 2) / 8;
        this->consoleLine = new ASCIILetter[this->lettersPerLine];
    }

    void print(const char* text) {
        while (readConsoleLine(text)) {
            printConsoleLine();
        }
    }
};

void sampleASCII() {
    const int SCREEN_SIZE = 80;

    char line[50];
    cout << "Enter a string: ";
    cin.getline(line, 50);

    ASCIIConsolePrinter asciiPrinter(SCREEN_SIZE);
    asciiPrinter.print(line);
}

int main() {
    sampleASCII();
    return 0;
}

