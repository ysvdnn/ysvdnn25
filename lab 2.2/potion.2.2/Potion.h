#ifndef POTION_H
#define POTION_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Potion {
private:
    string name;
    string base;
    int volume;
    vector<string> ingredients;

public:
    Potion();
    Potion(string n, string b, int v, vector<string> ing);
    Potion(const Potion& other);

    ~Potion();

    Potion& operator=(const Potion& other);

    Potion operator+(const Potion& other) const;
    Potion& operator+=(const Potion& other);
    Potion operator*(const Potion& other) const;

    void printInfo() const;
    string getName() const;
};

#endif