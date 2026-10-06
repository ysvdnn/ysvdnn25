#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>  
#ifdef _WIN32
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#ifndef _O_U16TEXT
#define _O_U16TEXT 0x20000
#endif
#else
#include <locale>
#endif
using namespace std;

#define ANSI_RED     L"\033[31m"
#define ANSI_BLUE    L"\033[34m"
#define ANSI_GREEN   L"\033[32m"
#define ANSI_YELLOW  L"\033[33m"
#define ANSI_RESET   L"\033[0m"

wstring vowels = L"аеёиоуыэюя";
wstring consonants = L"бвгджзйклмнпрстфхцчшщъь";

int arrayMode = 1;   
int colorMode = 1;   

vector< vector<wchar_t> > arrV(4);

wchar_t* rowsM[4] = { NULL, NULL, NULL, NULL };
int sizesM[4] = { 0, 0, 0, 0 };

wchar_t toLow(wchar_t ch) {
    if (ch >= L'А' && ch <= L'Я') return ch + 32;
    if (ch == L'Ё') return L'ё';
    return ch;
}

bool isLatin(wchar_t ch) {
    return (ch >= L'a' && ch <= L'z') || (ch >= L'A' && ch <= L'Z');
}

bool isDigit(wchar_t ch) {
    return ch >= L'0' && ch <= L'9';
}

bool contains(wstring s, wchar_t ch) {
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == ch) return true;
    }
    return false;
}

int getRow(wchar_t ch) {
    if (contains(vowels, ch))     return 0;
    if (contains(consonants, ch)) return 1;
    if (isDigit(ch))              return 2;
    return 3;
}

bool alreadyInVec(int row, wchar_t ch) {
    for (int i = 0; i < (int)arrV[row].size(); i++) {
        if (arrV[row][i] == ch) return true;
    }
    return false;
}

void addToVec(int row, wchar_t ch) {
    if (alreadyInVec(row, ch)) return;
    arrV[row].push_back(ch);
}


bool alreadyInMalloc(int row, wchar_t ch) {
    for (int i = 0; i < sizesM[row]; i++) {
        if (rowsM[row][i] == ch) return true;
    }
    return false;
}

void addToMalloc(int row, wchar_t ch) {
    if (alreadyInMalloc(row, ch)) return;

    if (rowsM[row] == NULL) {

        rowsM[row] = (wchar_t*)malloc(sizeof(wchar_t));
        if (rowsM[row] == NULL) {
            wcout << L"Ошибка: не хватило памяти" << endl;
            exit(1);
        }
    }
    else {

        wchar_t* tmp = (wchar_t*)realloc(rowsM[row], (sizesM[row] + 1) * sizeof(wchar_t));
        if (tmp == NULL) {
            wcout << L"Ошибка: не хватило памяти" << endl;
            exit(1);
        }
        rowsM[row] = tmp;
    }

    rowsM[row][sizesM[row]] = ch;
    sizesM[row]++;
}

void freeMalloc() {
    for (int i = 0; i < 4; i++) {
        free(rowsM[i]);
        rowsM[i] = NULL;
        sizesM[i] = 0;
    }
}

void addToArray(wchar_t ch) {
    if (ch == L'@') return;
    ch = toLow(ch);
    int row = getRow(ch);

    if (arrayMode == 1) {
        addToVec(row, ch);
    }
    else {
        addToMalloc(row, ch);
    }
}

int findRow(wchar_t ch) {
    ch = toLow(ch);
    for (int i = 0; i < 4; i++) {
        if (arrayMode == 1) {
            if (alreadyInVec(i, ch)) return i;
        }
        else {
            if (alreadyInMalloc(i, ch)) return i;
        }
    }
    return -1;
}

void printArray() {
    for (int i = 0; i < 4; i++) {
        if (arrayMode == 1) {
            for (int j = 0; j < (int)arrV[i].size(); j++) {
                wcout << arrV[i][j] << L" ";
            }
        }
        else {
            for (int j = 0; j < sizesM[i]; j++) {
                wcout << rowsM[i][j] << L" ";
            }
        }
        wcout << endl;
    }
}

void setColor(int row) {
    if (colorMode == 1) {
        // ANSI-коды
        if (row == 0)      wcout << ANSI_RED;
        else if (row == 1) wcout << ANSI_BLUE;
        else if (row == 2) wcout << ANSI_GREEN;
        else if (row == 3) wcout << ANSI_YELLOW;
    }
    else {
#ifdef _WIN32
        // WinAPI
        wcout << flush;   
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        WORD attr = 7;    
        if (row == 0)      attr = FOREGROUND_RED | FOREGROUND_INTENSITY;
        else if (row == 1) attr = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        else if (row == 2) attr = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        else if (row == 3) attr = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        SetConsoleTextAttribute(h, attr);
#endif
    }
}

void resetColor() {
    if (colorMode == 1) {
        wcout << ANSI_RESET;
    }
    else {
#ifdef _WIN32
        wcout << flush;   
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 7);
#endif
    }
}


int askVariant(wstring text) {
    wcout << text;
    wstring s;
    getline(wcin, s);
    if (s == L"2") return 2;
    return 1;
}

int main() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
#else
    locale::global(locale(""));
    wcin.imbue(locale());
    wcout.imbue(locale());
#endif

    arrayMode = askVariant(L"Вариант массива (1 - vector, 2 - malloc/realloc): ");
    colorMode = askVariant(L"Вариант раскраски (1 - ANSI-коды, 2 - WinAPI): ");

#ifndef _WIN32
    colorMode = 1;   
#endif

    wcout << L"Введите строку: ";
    wstring line;
    getline(wcin, line);

    if (line.empty()) {
        wcout << L"Ошибка: пустая строка" << endl;
        return 0;
    }

    if (line.size() > 50) {
        wcout << L"Ошибка: строка длиннее 50 символов" << endl;
        return 0;
    }

    for (int i = 0; i < (int)line.size(); i++) {
        if (isLatin(line[i])) {
            wcout << L"Ошибка: латиница не допускается" << endl;
            return 0;
        }
    }

    for (int i = 0; i < (int)line.size(); i++) {
        addToArray(line[i]);
    }

    wcout << L"Массив:" << endl;
    printArray();

    wstring result = line + L"+123АБВ";
    for (int i = 0; i < (int)result.size(); i++) {
        addToArray(result[i]);
    }

    wcout << L"Результат:" << endl;
    for (int i = 0; i < (int)result.size(); i++) {
        wchar_t ch = result[i];

        if (ch == L'@') {
            wcout << ch;    
            continue;
        }

        int row = findRow(ch);
        setColor(row);
        wcout << ch;
        resetColor();
    }
    wcout << endl;

    if (arrayMode == 2) {
        freeMalloc();       
    }

    return 0;
}