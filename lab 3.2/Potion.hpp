#ifndef POTION_HPP
#define POTION_HPP

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Ingredient {
    string name;
    string description;
    string effect;

    Ingredient();
    Ingredient(string n, string d, string e);
    void printInfo() const;
};

struct Base {
    string name;
    string description;
    float multiplier;

    Base();
    Base(string n, string d, float m);
    void printInfo() const;
};

class Potion {
private:
    string name;
    string description;
    int price;
    Base base;
    int volume;
    vector<Ingredient> ingredients;

    void validatePrice(int newPrice);
    void validateVolume(int newVolume);

public:
    Potion();
    Potion(string n, string d, int p, Base b, int v, vector<Ingredient> ing);
    Potion(const Potion& other);

    ~Potion();

    Potion& operator=(const Potion& other);

    string getName() const;
    string getDescription() const;
    int getPrice() const;
    Base getBase() const;
    int getVolume() const;
    vector<Ingredient> getIngredients() const;

    void setName(string n);
    void setDescription(string d);
    void setPrice(int p);
    void setBase(Base b);
    void setVolume(int v);
    void setIngredients(vector<Ingredient> ing);

    void addIngredient(Ingredient ing);
    void changeBase(Base newBase);
    void changeBase();
    void drink();
    void printInfo() const;

    Potion operator+(const Potion& other) const;
    Potion& operator+=(const Potion& other);
    Potion operator*(const Potion& other) const;

    float calculatePower() const;
};

#endif