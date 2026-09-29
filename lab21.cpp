#include <iostream>
#include <string>
#include <vector>
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

#define RED     L"\033[31m"
#define BLUE    L"\033[34m"
#define GREEN   L"\033[32m"
#define YELLOW  L"\033[33m"
#define RESET   L"\033[0m"

wstring vowels = L"аеёиоуыэюя";
wstring consonants = L"бвгджзйклмнпрстфхцчшщъь";

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

bool alreadyIn(vector<wchar_t>& v, wchar_t ch) {
    for (int i = 0; i < (int)v.size(); i++) {
        if (v[i] == ch) return true;
    }
    return false;
}

int getRow(wchar_t ch) {
    if (contains(vowels, ch))     return 0;
    if (contains(consonants, ch)) return 1;
    if (isDigit(ch))              return 2;
    return 3;
}
void addToArray(vector< vector<wchar_t> >& arr, wchar_t ch) {
    if (ch == L'@') return;
    ch = toLow(ch);
    int row = getRow(ch);
    if (!alreadyIn(arr[row], ch)) {
        arr[row].push_back(ch);
    }
}

int findRow(vector< vector<wchar_t> >& arr, wchar_t ch) {
    ch = toLow(ch);
    for (int i = 0; i < (int)arr.size(); i++) {
        if (alreadyIn(arr[i], ch)) return i;
    }
    return -1;
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

    vector< vector<wchar_t> > arr(4);

    for (int i = 0; i < (int)line.size(); i++) {
        addToArray(arr, line[i]);
    }

    wcout << L"Массив:" << endl;
    for (int i = 0; i < (int)arr.size(); i++) {
        for (int j = 0; j < (int)arr[i].size(); j++) {
            wcout << arr[i][j] << L" ";
        }
        wcout << endl;
    }

    wstring result = line + L"+123АБВ";
    for (int i = 0; i < (int)result.size(); i++) {
        addToArray(arr, result[i]);
    }

    wcout << L"Результат:" << endl;
    for (int i = 0; i < (int)result.size(); i++) {
        wchar_t ch = result[i];

        if (ch == L'@') {
            wcout << ch;
            continue;
        }

        int row = findRow(arr, ch);

        if (row == 0) {
            wcout << RED << ch << RESET;
        }
        else if (row == 1) {
            wcout << BLUE << ch << RESET;
        }
        else if (row == 2) {
            wcout << GREEN << ch << RESET;
        }
        else if (row == 3) {
            wcout << YELLOW << ch << RESET;
        }
        else {
            wcout << ch;
        }
    }
    wcout << endl;

    return 0;
}