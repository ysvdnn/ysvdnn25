#include "Cauldron.hpp"

Cauldron::Cauldron() {
    volume = 10;
    currentBase = Base();
}

Cauldron::Cauldron(int v, Base b) {
    if (v > 0) {
        volume = v;
    }
    else {
        volume = 10;
    }
    currentBase = b;
}

Cauldron::Cauldron(const Cauldron& other) {
    volume = other.volume;
    ingredients = other.ingredients;
    currentBase = other.currentBase;
}

Cauldron::~Cauldron() {
    if (!ingredients.empty()) {
        ingredients.clear();
    }
}

Cauldron& Cauldron::operator=(const Cauldron& other) {
    if (this != &other) {
        volume = other.volume;
        ingredients = other.ingredients;
        currentBase = other.currentBase;
    }
    return *this;
}

int Cauldron::getVolume() const {
    return volume;
}

vector<Ingredient> Cauldron::getIngredients() const {
    return ingredients;
}

Base Cauldron::getCurrentBase() const {
    return currentBase;
}

void Cauldron::setVolume(int v) {
    if (v <= 0) {
        return;
    }
    volume = v;
}

void Cauldron::setCurrentBase(Base b) {
    currentBase = b;
}

void Cauldron::addIngredient(Ingredient ing) {
    if (ingredients.size() >= volume) {
        return;
    }
    ingredients.push_back(ing);
}

void Cauldron::clearIngredients() {
    ingredients.clear();
}

Potion Cauldron::createPotion(string potionName, string potionDescription, int price) {
    if (ingredients.empty()) {
        return Potion();
    }

    int potionVolume = ingredients.size();
    int finalPrice = price * currentBase.multiplier;

    Potion newPotion(potionName, potionDescription, finalPrice,
        currentBase, potionVolume, ingredients);

    clearIngredients();
    return newPotion;
}

void Cauldron::fillFromPotion(const Potion& potion) {
    vector<Ingredient> potionIngs = potion.getIngredients();

    for (int i = 0; i < potionIngs.size(); i++) {
        if (ingredients.size() >= volume) {
            break;
        }
        addIngredient(potionIngs[i]);
    }
}

void Cauldron::printInfo() const {
    cout << "\nКОТЁЛ" << endl;
    cout << "Объём: " << volume << endl;
    cout << "Основа: " << currentBase.name << " (x" << currentBase.multiplier << ")" << endl;
    cout << "Ингредиентов: " << ingredients.size() << "/" << volume << endl;

    if (!ingredients.empty()) {
        cout << "Список:" << endl;
        for (int i = 0; i < ingredients.size(); i++) {
            cout << "  " << (i + 1) << ". " << ingredients[i].name << endl;
        }
    }
}