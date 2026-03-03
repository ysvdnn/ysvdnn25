#include "Potion.h"
#include <cstdlib>
#include <ctime>

Potion::Potion() {
    name = "Unknown";
    base = "Unknown";
    volume = 0;
}

Potion::Potion(string n, string b, int v, vector<string> ing) {
    name = n;
    base = b;
    if (v < 0) volume = 0;
    else volume = v;
    ingredients = ing;
}

Potion::Potion(const Potion& other) {
    name = other.name;
    base = other.base;
    volume = other.volume;
    ingredients = other.ingredients;
}

Potion::~Potion() {
    if (!ingredients.empty()) {
        ingredients.clear();
    }
}

Potion& Potion::operator=(const Potion& other) {
    if (this != &other) {
        name = other.name;
        base = other.base;
        volume = other.volume;
        ingredients = other.ingredients;
    }
    return *this;
}

string Potion::getName() const {
    return name;
}

Potion Potion::operator+(const Potion& other) const {
    string newBase;
    if (volume >= other.volume) newBase = base;
    else newBase = other.base;

    int newVolume = volume + other.volume;
    vector<string> newIngredients = ingredients;

    for (int i = 0; i < other.ingredients.size(); i++) {
        string ing = other.ingredients[i];
        bool found = false;
        for (int j = 0; j < newIngredients.size(); j++) {
            if (newIngredients[j] == ing) {
                found = true;
                break;
            }
        }
        if (found) newIngredients.push_back(ing + " доп");
        else newIngredients.push_back(ing);
    }

    return Potion("Результат +", newBase, newVolume, newIngredients);
}

Potion& Potion::operator+=(const Potion& other) {
    name = name + "(обн.)";
    if (other.volume > volume) base = other.base;
    volume = volume + other.volume;

    for (int i = 0; i < other.ingredients.size(); i++) {
        string ing = other.ingredients[i];
        bool found = false;
        for (int j = 0; j < ingredients.size(); j++) {
            if (ingredients[j] == ing) {
                found = true;
                break;
            }
        }
        if (found) ingredients.push_back(ing + " доп");
        else ingredients.push_back(ing);
    }

    return *this;
}

Potion Potion::operator*(const Potion& other) const {
    srand(time(NULL));
    string bases[4] = { "Вода", "Спирт", "Масло", "Земля" };
    string newBase = bases[rand() % 4];
    int newVolume = (volume + other.volume) * 80 / 100;

    vector<string> allCommon;
    for (int i = 0; i < ingredients.size(); i++) {
        for (int j = 0; j < other.ingredients.size(); j++) {
            if (ingredients[i] == other.ingredients[j]) {
                allCommon.push_back(ingredients[i]);
                break;
            }
        }
    }

    vector<string> uniqueCommon;

    for (int i = 0; i < allCommon.size(); i++) {
        bool alreadyAdded = false;

        for (int j = 0; j < uniqueCommon.size(); j++) {
            if (allCommon[i] == uniqueCommon[j]) {
                alreadyAdded = true;
                break;
            }
        }

        if (!alreadyAdded) {
            uniqueCommon.push_back(allCommon[i]);
        }
    }

    uniqueCommon.push_back("хвост");
    uniqueCommon.push_back("вода");

    return Potion("Микс", newBase, newVolume, uniqueCommon);
}

void Potion::printInfo() const {
    cout << "Название: " << name << endl;
    cout << "Основа: " << base << endl;
    cout << "Объем: " << volume << endl;
    cout << "Ингредиенты: ";
    if (ingredients.empty()) cout << "нет";
    else {
        for (int i = 0; i < ingredients.size(); i++) {
            cout << ingredients[i];
            if (i < ingredients.size() - 1) cout << ", ";
        }
    }
}